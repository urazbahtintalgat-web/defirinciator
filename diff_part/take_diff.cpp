#include "take_diff.h"

#include "basic_derivatives.h"
#include "../differentiator.h"
#include "../init_destroy/diff_init_destroy.h"

#include <assert.h>

Differentiator_t * TakeDifferecial(Differentiator_t * dif, Differentiator_t * parent_differential, char x) {
    assert(dif);

    Differentiator_t * new_dif = NULL;
    if (parent_differential == NULL) {
        new_dif = DifferentiatorInit();
    } else new_dif = DifferentiatorNodeInit(parent_differential);

    //если это число то производная 0
    if (dif->meaning == VALUE) {
        new_dif->meaning = VALUE;
        new_dif->value.number = 0;
        return new_dif;
    }

    //если это переменная то смотрим константа или нет
    if (dif->meaning == VARIABLE) {
        //если не константа то производная 1
        if (dif->value.variable == x) {
            new_dif->meaning = VALUE;
            new_dif->value.number = 1;
        } else {
        //если константа то производная 0
            new_dif->meaning = VALUE;
            new_dif->value.number = 0;
        }
        return new_dif;
    }

    //если это не переменная и не число то это операция
    new_dif->meaning = OPERATION;
    Differentiator_t * (*Func) (Differentiator_t * dif, Differentiator_t * new_dif, char x);
    Func = derivative_function_list[dif->value.operation];
    Func(dif, new_dif, x);



    return new_dif;
}