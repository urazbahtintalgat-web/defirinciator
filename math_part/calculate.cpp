#include "calculate.h"

#include "../differentiator.h"
#include "../double_compare/double_compare.h"

#include "math.h"
#include <assert.h>
const double EPSILON = 1e-9;

CalculateFunction function_list[] = {
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
    FuncADDITION,      //11
    FuncSUBTRACTION,   //12
    FuncMULTIPLICATION,//13
    FuncDIVISION,      //14
    FuncPOWER,         //15
    FuncLOGARITHM,     //16
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
    FuncSIN,              //31
    FuncCOS,              //32
    FuncTAN,              //33
    FuncCOT,              //34
    FuncEXPONENTIAL,      //35
    FuncNATURAL_LOGARITHM,//36
    FuncDECIMAL_LOGARITHM,//37
    FuncSQUARE_ROOT,      //38
    FuncARCSIN,           //39
    FuncARCCOS,           //40
    FuncARCTAN,           //41
    FuncARCCOT,           //42
    FuncSIN_HYPERBOLIC,   //43
    FuncCOS_HYPERBOLIC,   //44
    FuncTAN_HYPERBOLIC,   //45
    NULL,//46
    NULL,//47
    NULL,//48
    NULL,//49
    NULL,//50
};

double CalculateDifferentiator(Differentiator_t * dif) {
    assert(dif);

    if (dif->meaning == VALUE) return dif->value.number;
    if (dif->meaning == VARIABLE) {
        char var = dif->value.variable;
        if ('a' <= var && var <= 'z') {
            if (array_of_used_variables[var - 'a'] == 1) {
                return array_of_variables[var - 'a'];
            } else {
                printf("ERROR: that variable was not used %c.    %s:%d\n", var, __FILE__, __LINE__);
                return 0;
            }
        } else {
            printf("ERROR: illigal variable %c.      %s:%d\n", var, __FILE__, __LINE__);
            return 0;
        }
    }

    double (*Func)(Differentiator_t * dif);
    Func = function_list[dif->value.operation];
    if (Func == NULL) {
        printf("ERROR: NULL function for code %s:%d\n", __FILE__, __LINE__);
        return 0;
    }
    return Func(dif);
}





//----------------------HELP

/**
 * @brief В эту функцию уже отправляется какое-то из поддеревьев для вычисления аргумента для функции откуда она вызывается
 * 
 * @param dif указатель на поддерево из которого надо вытащить аргумент или вычислить его
 * 
 * @return возвращает аргумент поддерева (если это переменная то залезает в массив хранящий их значения)
 */
double GetArg(Differentiator_t * dif) {
    switch (dif->meaning)
    {
    case VALUE:
        return dif->value.number;
        break;

    case VARIABLE: {
        char var = dif->value.variable;
        if ('a' <= var && var <= 'z') {
            if (array_of_used_variables[var - 'a'] == 0) {
                printf("ERROR: that variable was not declared - %c.   %s:%d\n", var, __FILE__, __LINE__);
                return 0;
            }
            return array_of_variables[var - 'a'];
        } else {
            printf("ERROR: entered illigal variable - %c   %s:%d\n", var, __FILE__, __LINE__);
            return 0;
        }
        break;
    }

    case OPERATION: {
        double (*Func)(Differentiator_t *);
        Func = function_list[dif->value.operation];
        if (Func == NULL) {
            printf("ERROR: NULL function for code %s:%d\n", __FILE__, __LINE__);
            return 0;
        }
        return Func(dif);
    }
        
    
    default:
        printf("ERROR: not found function %s:%d\n", __FILE__, __LINE__);
        return 0;
        break;
    }
}


//---------------------BIN

double FuncADDITION(Differentiator_t * dif) {
    if (dif->left == NULL || dif->right == NULL) {
        printf("ERROR: ADDITION requires two operands %s:%d\n", __FILE__, __LINE__);
        return 0;
    }

    double x = 0;
    x = GetArg(dif->left);
    double y = 0;
    y = GetArg(dif->right);
    return x + y;
}

double FuncSUBTRACTION(Differentiator_t * dif) {
    if (dif->left == NULL || dif->right == NULL) {
        printf("ERROR: SUBTRACTION requires two operands %s:%d\n", __FILE__, __LINE__);
        return 0;
    }

    double x = 0;
    x = GetArg(dif->left);
    double y = 0;
    y = GetArg(dif->right);
    return x - y;
}

double FuncMULTIPLICATION(Differentiator_t * dif) {
    if (dif->left == NULL || dif->right == NULL) {
        printf("ERROR: MULTIPLICATION requires two operands %s:%d\n", __FILE__, __LINE__);
        return 0;
    }

    double x = 0;
    x = GetArg(dif->left);
    double y = 0;
    y = GetArg(dif->right);
    return x * y;
}

double FuncDIVISION(Differentiator_t * dif) {
    if (dif->left == NULL || dif->right == NULL) {
        printf("ERROR: DIVISION requires two operands %s:%d\n", __FILE__, __LINE__);
        return 0;
    }

    double x = 0;
    x = GetArg(dif->left);
    double y = 0;
    y = GetArg(dif->right);
    if (fabs(y) < EPSILON) {
        printf("ERROR: division by zero 0 %s:%d\n", __FILE__, __LINE__);
        return 0;
    }
    return x / y;
}

double FuncPOWER(Differentiator_t * dif) {
    if (dif->left == NULL || dif->right == NULL) {
        printf("ERROR: POWER requires two operands %s:%d\n", __FILE__, __LINE__);
        return 0;
    }

    double x = 0;
    x = GetArg(dif->left);
    if (DoubleCompare(x, 0) == 0) x = 0;
    double y = 0;
    y = GetArg(dif->right);
    if (x < 0) {
        printf("ERROR: basis of POWER is negative %s:%d\n", __FILE__, __LINE__);
        return 0;
    }

    return pow(x, y);
}

double FuncLOGARITHM(Differentiator_t * dif) {
    if (dif->left == NULL || dif->right == NULL) {
        printf("ERROR: LOGARITHM requires two operands %s:%d\n", __FILE__, __LINE__);
        return 0;
    }

    double x = 0;
    x = GetArg(dif->left);
    double y = 0;
    y = GetArg(dif->right);
    if (x < EPSILON || fabs(x - 1) < EPSILON) {
        printf("ERROR: base of LOGARITHM is negative or = 0 or = 1 %s:%d\n", __FILE__, __LINE__);
        return 0;
    }
    if (y < EPSILON) {
        printf("ERROR: argument of LOGARITHM is negative or = 0 %s:%d\n", __FILE__, __LINE__);
        return 0;
    }

    return log(y) / log(x);
}

//-------------------UNO

double FuncSIN(Differentiator_t * dif) {
    double x = 0;
    x = GetArg(dif->left);
    return sin(x);
}

double FuncCOS(Differentiator_t * dif) {
    double x = 0;
    x = GetArg(dif->left);
    return cos(x);
}

double FuncTAN(Differentiator_t * dif) {
    double x = 0;
    x = GetArg(dif->left);
    return tan(x);
}

double FuncCOT(Differentiator_t * dif) {
    double x = 0;
    x = GetArg(dif->left);
    return 1 / tan(x);
}

double FuncEXPONENTIAL(Differentiator_t * dif) {
    double x = 0;
    x = GetArg(dif->left);
    return exp(x);
}

double FuncNATURAL_LOGARITHM(Differentiator_t * dif) {
    double x = 0;
    x = GetArg(dif->left);
    if (x < EPSILON) {
        printf("ERROR: argument of NATURAL_LOGARITHM is negative of = 0 %s:%d\n", __FILE__, __LINE__);
        return 0;
    }
    return log(x);
}

double FuncDECIMAL_LOGARITHM(Differentiator_t * dif) {
    double x = 0;
    x = GetArg(dif->left);
    if (x < EPSILON) {
        printf("ERROR: argument of DECIMAL_LOGARITHM is negative of = 0 %s:%d\n", __FILE__, __LINE__);
        return 0;
    }
    return log10(x);
}

double FuncSQUARE_ROOT(Differentiator_t * dif) {
    double x = 0;
    x = GetArg(dif->left);
    if (fabs(x) < EPSILON) x = 0;
    if (x < 0) {
        printf("ERROR: argument of SQUARE_ROOT is negative %s:%d\n", __FILE__, __LINE__);
        return 0;
    }
    return sqrt(x);
}

double FuncARCSIN(Differentiator_t * dif) {
    double x = 0;
    x = GetArg(dif->left);
    if (fabs(fabs(x) - 1) > EPSILON && fabs(x) > 1) {
        printf("ERROR: argument of ARCSIN is illigal %s:%d\n", __FILE__, __LINE__);
        return 0;
    }
    return asin(x);
}

double FuncARCCOS(Differentiator_t * dif) {
    double x = 0;
    x = GetArg(dif->left);
    if (fabs(fabs(x) - 1) > EPSILON && fabs(x) > 1) {
        printf("ERROR: argument of ARCCOS is illigal %s:%d\n", __FILE__, __LINE__);
        return 0;
    }
    return acos(x);
}

double FuncARCTAN(Differentiator_t * dif) {
    double x = 0;
    x = GetArg(dif->left);
    return atan(x);
}

double FuncARCCOT(Differentiator_t * dif) {
    double x = 0;
    x = GetArg(dif->left);
    return atan(1 / x);
}

double FuncSIN_HYPERBOLIC(Differentiator_t * dif) {
    double x = 0;
    x = GetArg(dif->left);
    return sinh(x);
}

double FuncCOS_HYPERBOLIC(Differentiator_t * dif) {
    double x = 0;
    x = GetArg(dif->left);
    return cosh(x);
}

double FuncTAN_HYPERBOLIC(Differentiator_t * dif) {
    double x = 0;
    x = GetArg(dif->left);
    return tanh(x);
}