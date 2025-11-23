#include "simplify.h"

#include "../differentiator.h"
#include "../math_part/calculate.h"
#include "../init_destroy/diff_init_destroy.h"
#include "../double_compare/double_compare.h"

#include <stdlib.h>
#include <math.h>

static const double EPSILON = 1e-9;

Differentiator_t * SimplifyADDITION(Differentiator_t * dif) {
    if (dif->left->meaning == VALUE && DoubleCompare(dif->left->value.number, 0) == 0) {
        Differentiator_t * new_dif = dif->right;
        new_dif->parent = dif->parent;
        free(dif->left);
        free(dif);
        return new_dif;
    }
    if (dif->right->meaning == VALUE && DoubleCompare(dif->right->value.number, 0) == 0) {
        Differentiator_t * new_dif = dif->left;
        new_dif->parent = dif->parent;
        free(dif->right);
        free(dif);
        return new_dif;
    }
    return dif;
}

Differentiator_t * SimplifySUBTRACTION(Differentiator_t * dif) {
    if (dif->left->meaning == VALUE && DoubleCompare(dif->left->value.number, 0) == 0) {
        Differentiator_t * new_dif = dif->right;
        new_dif->parent = dif->parent;
        free(dif->left);
        free(dif);
        return new_dif;
    }
    if (dif->right->meaning == VALUE && DoubleCompare(dif->right->value.number, 0) == 0) {
        Differentiator_t * new_dif = dif->left;
        new_dif->parent = dif->parent;
        free(dif->right);
        free(dif);
        return new_dif;
    }
    return dif;
}

Differentiator_t * SimplifyMULTIPLICATION(Differentiator_t * dif) {
    if (dif->left->meaning == VALUE) {
        if (DoubleCompare(dif->left->value.number, 1) == 0) {
            Differentiator_t * new_dif = dif->right;
            new_dif->parent = dif->parent;
            free(dif->left);
            free(dif);
            return new_dif;
        }
        if (DoubleCompare(dif->left->value.number, 0) == 0) {
            Differentiator_t * new_dif = dif->left;
            new_dif->parent = dif->parent;
            DifferentiatorDestroy(&dif->right);
            free(dif);
            return new_dif;
        }
    }
    if (dif->right->meaning == VALUE) {
        if (DoubleCompare(dif->right->value.number, 1) == 0) {
            Differentiator_t * new_dif = dif->left;
            new_dif->parent = dif->parent;
            free(dif->right);
            free(dif);
            return new_dif;
        }
        if (DoubleCompare(dif->right->value.number, 0) == 0) {
            Differentiator_t * new_dif = dif->right;
            new_dif->parent = dif->parent;
            DifferentiatorDestroy(&dif->left);
            free(dif);
            return new_dif;
        }
    }
    return dif;
}

Differentiator_t * SimplifyDIVISION(Differentiator_t * dif) {
    if (dif->right->meaning == VALUE && DoubleCompare(dif->right->value.number, 1) == 0) {
        Differentiator_t * new_dif = dif->left;
        new_dif->parent = dif->parent;
        free(dif->right);
        free(dif);
        return new_dif;
    }
    return dif;
}

Differentiator_t * SimplifyPOWER(Differentiator_t * dif) {
    if (dif->left->meaning == VALUE && (DoubleCompare(dif->left->value.number, 1) == 0 || DoubleCompare(dif->left->value.number, 0) == 0)) {
        Differentiator_t * new_dif = dif->left;
        new_dif->parent = dif->parent;
        DifferentiatorDestroy(&dif->right);
        free(dif);
        return new_dif;
    }
    if (dif->right->meaning == VALUE && DoubleCompare(dif->right->value.number, 0) == 0) {
        Differentiator_t * new_dif = DifferentiatorNodeInit(dif->parent);
        new_dif->meaning = VALUE;
        new_dif->value.number = 1;
        DifferentiatorDestroy(&dif);
        return new_dif;
    }
    if (dif->right->meaning == VALUE && DoubleCompare(dif->right->value.number, 1) == 0) {
        Differentiator_t * new_dif = dif->left;
        new_dif->parent = dif->parent;
        free(dif->right);
        free(dif);
        return new_dif;
    }
    return dif;
}


SimplificationFunction simplification_functions_list[] = {
    NULL,//0
    NULL,//1
    NULL,//2
    NULL,//3
    NULL,//4
    NULL,//5
    NULL,//6
    NULL,//7
    NULL,//8
    NULL,//9
    NULL,//10
    SimplifyADDITION,      //11
    SimplifySUBTRACTION,   //12
    SimplifyMULTIPLICATION,//13
    SimplifyDIVISION,      //14
    SimplifyPOWER,         //15
    NULL,//16
    NULL,//17
    NULL,//18
    NULL,//19
    NULL,//20
    NULL,//21
    NULL,//22
    NULL,//23
    NULL,//24
    NULL,//25
    NULL,//26
    NULL,//27
    NULL,//28
    NULL,//29
    NULL,//30
    NULL,//31
    NULL,//32
    NULL,//33
    NULL,//34
    NULL,//35
    NULL,//36
    NULL,//37
    NULL,//38
    NULL,//39
    NULL,//40
    NULL,//41
    NULL,//42
    NULL,//43
    NULL,//44
    NULL,//45
    NULL,//46
    NULL,//47
    NULL,//48
    NULL,//49
    NULL,//50
};
//----------------------------------------------------------------

Differentiator_t * CalculateConst(Differentiator_t * dif) {
    if (dif == NULL) return NULL;
    if (dif->meaning == VARIABLE) return dif;
    if (dif->meaning == VALUE) return dif;

    dif->left =  CalculateConst(dif->left );
    dif->right = CalculateConst(dif->right);

    if (dif->left != NULL && (dif->left->meaning == VARIABLE || dif->left->meaning == OPERATION)) return dif;
    if (dif->right!= NULL && (dif->right->meaning== VARIABLE || dif->right->meaning== OPERATION)) return dif;

    double (*Func)(Differentiator_t * dif);
    Func = function_list[dif->value.operation];
    double ans = Func(dif);
    Differentiator_t * new_dif = (Differentiator_t *) calloc (1, sizeof(Differentiator_t));

    new_dif->meaning = VALUE;
    new_dif->value.number = ans;
    new_dif->parent = dif->parent;
    new_dif->left = NULL;
    new_dif->right = NULL;

    free(dif->left);
    free(dif->right);
    free(dif);

    return new_dif;
}


Differentiator_t * RemoveNetral(Differentiator_t * dif) {
    if (dif == NULL) return NULL;
    if (dif->meaning == VARIABLE) return dif;
    if (dif->meaning == VALUE) return dif;

    dif->left = RemoveNetral(dif->left);
    dif->right = RemoveNetral(dif->right);

    if (simplification_functions_list[dif->value.operation] == NULL) return dif;

    Differentiator_t * (*Func) (Differentiator_t * dif);
    Func = simplification_functions_list[dif->value.operation];
    return Func(dif);
}