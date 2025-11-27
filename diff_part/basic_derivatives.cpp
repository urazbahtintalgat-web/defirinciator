#include "basic_derivatives.h"

#include "../differentiator.h"
#include "take_diff.h"
#include "../init_destroy/diff_init_destroy.h"

/**
 * @brief эта функция нужна для упрощения работы в производных и в нее передаются уже сразу скопированные left и right
 *         и parent это новая вершина
 */
static inline Differentiator_t * BinFunc(Meaning_t oper, Differentiator_t * left, Differentiator_t * right) {
    Differentiator_t * new_dif = DifferentiatorInit();
    if (new_dif == NULL) return NULL;

    new_dif->meaning = OPERATION;
    new_dif->value.operation = oper;
    new_dif->left = left;
    new_dif->right = right;

    return new_dif;
}
static inline Differentiator_t * UnoFunc(Meaning_t oper, Differentiator_t * left) {
    Differentiator_t * new_dif = DifferentiatorInit();
    if (new_dif == NULL) return NULL;

    new_dif->meaning = OPERATION;
    new_dif->value.operation = oper;
    new_dif->left = left;

    return new_dif;
}
static inline void SetParents(Differentiator_t * dif, Differentiator_t * parent) {
    if (dif == NULL) return;
    if (dif->left != NULL) SetParents(dif->left, dif);
    if (dif->right != NULL) SetParents(dif->right, dif);
    if (parent != NULL) dif->parent = parent;
    return;
}



DerivativeFunction derivative_function_list[] = {
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
    DerFuncADDITION,      //11
    DerFuncSUBTRACTION,   //12
    DerFuncMULTIPLICATION,//13
    DerFuncDIVISION,      //14
    DerFuncPOWER,         //15
    DerFuncLOGARITHM,     //16
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
    DerFuncSIN,//31
    DerFuncCOS,//32
    DerFuncTAN,//33
    DerFuncCOT,//34
    DerFuncEXPONENTIAL,//35
    DerFuncNATURAL_LOGARITHM,//36
    DerFuncDECIMAL_LOGARITHM,//37
    DerFuncSQUARE_ROOT,//38
    DerFuncARCSIN,//39
    DerFuncARCCOS,//40
    DerFuncARCTAN,//41
    DerFuncARCCOT,//42
    DerFuncSIN_HYPERBOLIC,//43
    DerFuncCOS_HYPERBOLIC,//44
    DerFuncTAN_HYPERBOLIC,//45
    NULL,//46
    NULL,//47
    NULL,//48
    NULL,//49
    NULL,//50
};






//---------------------BIN

Differentiator_t * DerFuncADDITION(Differentiator_t * dif, Differentiator_t * new_dif, char x) {
    //производная суммы это сумма производных
    new_dif->value.operation = ADDITION;

    //считаем производную левого поддерева
    new_dif->left = TakeDifferecial(dif->left, new_dif, x);

    //считает производную проваго поддерева
    new_dif->right = TakeDifferecial(dif->right, new_dif, x);

    return new_dif;
}

Differentiator_t * DerFuncSUBTRACTION(Differentiator_t * dif, Differentiator_t * new_dif, char x) {
    //производная разницы это разница производных
    new_dif->value.operation = SUBTRACTION;

    //считаем производную левого поддерева
    new_dif->left = TakeDifferecial(dif->left, new_dif, x);

    //считает производную проваго поддерева
    new_dif->right = TakeDifferecial(dif->right, new_dif, x);

    return new_dif;
}

Differentiator_t * DerFuncMULTIPLICATION(Differentiator_t * dif, Differentiator_t * new_dif, char x) {
    ////производная произведения это сумма пар производная + обычная форма
    //new_dif->value.operation = ADDITION;
//
    ////левое поддерево это производная левого умножить на правое
    //new_dif->left = DifferentiatorNodeInit(new_dif);//делаем новую вершину для произведения
    //new_dif->left->meaning = OPERATION;
    //new_dif->left->value.operation = MULTIPLICATION;
    ////теперь в новую вершину надо записать производную левого и правое
    //new_dif->left->left = TakeDifferecial(dif->left, new_dif->left, x);
    //new_dif->left->right = DifferentiatorCopy(dif->right, new_dif->left);//правое просто копируем
//
    ////правое поддерево это левое умножить на производную правого
    //new_dif->right = DifferentiatorNodeInit(new_dif);//делаем новею вершину для производных
    //new_dif->right->meaning = OPERATION;
    //new_dif->right->value.operation = MULTIPLICATION;
    ////теперь в новую вершину надо записать левое и производную правого
    //new_dif->right->left = DifferentiatorCopy(dif->left, new_dif->right);//левое просто копируем
    //new_dif->right->right = TakeDifferecial(dif->right, new_dif->right, x);
//
    //return new_dif;

    new_dif->meaning = OPERATION;
    new_dif->value.operation = ADDITION;
    new_dif->left = BinFunc(MULTIPLICATION, TakeDifferecial(dif->left, NULL, x), DifferentiatorCopy(dif->right, NULL));
    new_dif->right = BinFunc(MULTIPLICATION, DifferentiatorCopy(dif->left, NULL), TakeDifferecial(dif->right, NULL, x));
    SetParents(new_dif, NULL);
    return new_dif;
}

Differentiator_t * DerFuncDIVISION(Differentiator_t * dif, Differentiator_t * new_dif, char x) {
    ////производная частного это частное от деления 
    ////(проздводной левого(числителя) * правое(знаминатель) - производное правого(знеминателя) * левое(числитель))
    ////делить на квадрат правого(знаменателя)
    //new_dif->value.operation = DIVISION;
//
    ////левое поддерево (проздводной левого(числителя) * правое(знаминатель) - производное правого(знеминателя) * левое(числитель))
    //new_dif->left = DifferentiatorNodeInit(new_dif);//делаем новую вершину для всей числителя
    //Differentiator_t * chislitel = new_dif->left;
    //chislitel->meaning = OPERATION;
    //chislitel->value.operation = SUBTRACTION;
//
    //{
    //    chislitel->left = DifferentiatorNodeInit(chislitel);
    //    chislitel->left->meaning = OPERATION;
    //    chislitel->left->value.operation = MULTIPLICATION;
    //    chislitel->left->left = TakeDifferecial(dif->left, chislitel->left, x);
    //    chislitel->left->right = DifferentiatorCopy(dif->right, chislitel->left);
//
    //    chislitel->right = DifferentiatorNodeInit(chislitel);
    //    chislitel->right->meaning = OPERATION;
    //    chislitel->right->value.operation = MULTIPLICATION;
    //    chislitel->right->left = TakeDifferecial(dif->right, chislitel->right, x);
    //    chislitel->right->right = DifferentiatorCopy(dif->left, chislitel->right);
    //}
//
    ////правое поддерево квадрат правого(знаменателя)
    //new_dif->right = DifferentiatorNodeInit(new_dif);
    //new_dif->right->meaning = OPERATION;
    //new_dif->right->value.operation = POWER;
    ////левое поддерево это основание степени
    //new_dif->right->left = DifferentiatorCopy(dif->right, new_dif->right);
    ////правое поддерево это степень (2)
    //new_dif->right->right = DifferentiatorNodeInit(new_dif->right);
    //new_dif->right->right->meaning = VALUE;
    //new_dif->right->right->value.number = 2;
//
    //return new_dif;
    new_dif->meaning = OPERATION;
    new_dif->value.operation = DIVISION;
    new_dif->left = BinFunc(SUBTRACTION, 
                            BinFunc(MULTIPLICATION, 
                                    TakeDifferecial(dif->left, NULL, x), 
                                    DifferentiatorCopy(dif->right, NULL)),
                            BinFunc(MULTIPLICATION, 
                                    DifferentiatorCopy(dif->left, NULL), 
                                    TakeDifferecial(dif->right, NULL, x)));
    
    new_dif->right = BinFunc(POWER, 
                             DifferentiatorCopy(dif->right, NULL), 
                             DifferentiatorNodeInitConst(NULL, 2));
    SetParents(new_dif, NULL);
    return new_dif;
}

Differentiator_t * DerFuncPOWER(Differentiator_t * dif, Differentiator_t * new_dif, char x) {
    //new_dif->meaning = OPERATION;
    //Differentiator_t * base = dif->left;//f(x)
    //Differentiator_t * degree = dif->right;//g(x)
//
    ////f(x)^g(x) * (g'(x)*ln(f(x)) + g(x)*f'(x)/f(x))
    //new_dif->meaning = OPERATION;
    //new_dif->value.operation = MULTIPLICATION;
    //{
    //    //f(x)^g(x)
    //    new_dif->left = DifferentiatorCopy(dif, new_dif);
    //}
    //new_dif->right = DifferentiatorNodeInit(new_dif);
    //{
    //    //g'(x)*ln(f(x)) + g(x)*f'(x)/f(x)
    //    new_dif->right->meaning = OPERATION;
    //    new_dif->right->value.operation = ADDITION;
    //    new_dif->right->left = DifferentiatorNodeInit(new_dif->right);
    //    {
    //        //g'(x)*ln(f(x))
    //        new_dif->right->left->meaning = OPERATION;
    //        new_dif->right->left->value.operation = MULTIPLICATION;
    //        //g'(x)
    //        new_dif->right->left->left = TakeDifferecial(degree, new_dif->right->left, x);
    //        new_dif->right->left->right = DifferentiatorNodeInit(new_dif->right->left);
    //        {
    //            //ln(f(x))
    //            new_dif->right->left->right->meaning = OPERATION;
    //            new_dif->right->left->right->value.operation = NATURAL_LOGARITHM;
    //            new_dif->right->left->right->left = DifferentiatorCopy(base, new_dif->right->left->right);
    //        }
    //    }
    //    new_dif->right->right = DifferentiatorNodeInit(new_dif->right);
    //    {
    //        //g(x)*f'(x)/f(x)
    //        new_dif->right->right->meaning = OPERATION;
    //        new_dif->right->right->value.operation = MULTIPLICATION;
    //        //g(x)
    //        new_dif->right->right->left = DifferentiatorCopy(degree, new_dif->right->right);
    //        new_dif->right->right->right = DifferentiatorNodeInit(new_dif->right->right);
    //        {
    //            //f'(x)/f(x)
    //            new_dif->right->right->right->meaning = OPERATION;
    //            new_dif->right->right->right->value.operation = DIVISION;
    //            //f'(x)
    //            new_dif->right->right->right->left = TakeDifferecial(base, new_dif->right->right->right, x);
    //            //f(x)
    //            new_dif->right->right->right->right = DifferentiatorCopy(base, new_dif->right->right->right);
    //        }
    //    }
    //}
//
    //return new_dif;

    new_dif->meaning = OPERATION;
    new_dif->value.operation = MULTIPLICATION;
    //f(x)^g(x)
    Differentiator_t * f = dif->left;
    Differentiator_t * g = dif->right;
    new_dif->left = BinFunc(POWER,
                            DifferentiatorCopy(f, NULL),
                            DifferentiatorCopy(g, NULL));
    new_dif->right = BinFunc(ADDITION,
                             BinFunc(MULTIPLICATION,
                                     TakeDifferecial(g, NULL, x),
                                     UnoFunc(NATURAL_LOGARITHM, DifferentiatorCopy(f, NULL))),
                             BinFunc(MULTIPLICATION,
                                     DifferentiatorCopy(g, NULL),
                                     BinFunc(DIVISION,
                                             TakeDifferecial(f, NULL, x),
                                             DifferentiatorCopy(f, NULL))));
    SetParents(new_dif, NULL);
    return new_dif;
}

Differentiator_t * DerFuncLOGARITHM(Differentiator_t * dif, Differentiator_t * new_dif, char x) {
    //new_dif->value.operation = DIVISION;
    //Differentiator_t * base = dif->left;//a
    //Differentiator_t * argument = dif->right;//f(x)
    //if (base->meaning != VALUE || (base->meaning == VARIABLE && base->value.variable == x)) {
    //    printf("ERROR: base of LOGARITHM is not depends on x or is operatiron %s:%d\n", __FILE__, __LINE__);
    //    return NULL;
    //}
    ////f'(x) / (f(x)*ln(a))
    ////f'(x)
    //new_dif->left = TakeDifferecial(argument, new_dif->left, x);
    //new_dif->right = DifferentiatorNodeInit(new_dif);
    //{
    //    //(f(x)*ln(a))
    //    new_dif->right->meaning = OPERATION;
    //    new_dif->right->value.operation = MULTIPLICATION;
    //    //f(x)
    //    new_dif->right->left = DifferentiatorCopy(argument, new_dif->right);
    //    new_dif->right->right = DifferentiatorNodeInit(new_dif->right);
    //    {
    //        //ln(a)
    //        new_dif->right->right->meaning = OPERATION;
    //        new_dif->right->right->value.operation = NATURAL_LOGARITHM;
    //        new_dif->right->right->left = DifferentiatorCopy(base, new_dif->right->right);
    //    }
    //}
    //return new_dif;

    new_dif->meaning = OPERATION;
    new_dif->value.operation = DIVISION;
    Differentiator_t * base = dif->left;//a
    Differentiator_t * argument = dif->right;//f(x)
    if (base->meaning == OPERATION || (base->meaning == VARIABLE && base->value.variable == x)) {
        printf("ERROR: base of LOGARITHM is cannot depends on x or is operatiron %s:%d\n", __FILE__, __LINE__);
        return NULL;
    }
    new_dif->left = TakeDifferecial(argument, NULL, x);
    new_dif->right = BinFunc(MULTIPLICATION,
                             DifferentiatorCopy(argument, NULL),
                             UnoFunc(NATURAL_LOGARITHM, DifferentiatorCopy(base, NULL)));
    
    SetParents(new_dif, NULL);
    
    return new_dif;
}

//---------------------------UNO

Differentiator_t * DerFuncSIN(Differentiator_t * dif, Differentiator_t * new_dif, char x) {
    //new_dif->meaning = OPERATION;
    //new_dif->value.operation = MULTIPLICATION;
    //Differentiator_t * argument = dif->left;
    //new_dif->left = DifferentiatorNodeInit(new_dif);
    //{
    //    new_dif->left->meaning = OPERATION;
    //    new_dif->left->value.operation = COS;
    //    new_dif->left->left = DifferentiatorCopy(argument, new_dif->left);
    //}
    //new_dif->right = TakeDifferecial(argument, new_dif, x);
    //return new_dif;

    Differentiator_t * argument = dif->left;
    new_dif->meaning = OPERATION;
    new_dif->value.operation = MULTIPLICATION;
    new_dif->left = UnoFunc(COS, DifferentiatorCopy(argument, NULL));
    new_dif->right = TakeDifferecial(argument, NULL, x);

    SetParents(new_dif, NULL);
    
    return new_dif;
}

Differentiator_t * DerFuncCOS(Differentiator_t * dif, Differentiator_t * new_dif, char x) {
    //new_dif->meaning = OPERATION;
    //new_dif->value.operation = MULTIPLICATION;
    //Differentiator_t * argument = dif->left;
    //new_dif->left = DifferentiatorNodeInit(new_dif);
    //{
    //    new_dif->left->meaning = OPERATION;
    //    new_dif->left->value.operation = MULTIPLICATION;
    //    new_dif->left->left = DifferentiatorNodeInitConst(new_dif->left, -1);
    //    new_dif->left->right = DifferentiatorNodeInit(new_dif->left);
    //    {
    //        new_dif->left->right->meaning = OPERATION;
    //        new_dif->left->right->value.operation = SIN;
    //        new_dif->left->right->left = DifferentiatorCopy(argument, new_dif->left->right);
    //    }
    //}
    //new_dif->right = TakeDifferecial(argument, new_dif, x);
    //return new_dif;

    Differentiator_t * arg = dif->left;
    new_dif->meaning = OPERATION;
    new_dif->value.operation = MULTIPLICATION;
    new_dif->left = BinFunc(MULTIPLICATION,
                            DifferentiatorNodeInitConst(NULL, -1),
                            UnoFunc(SIN, DifferentiatorCopy(arg, NULL)));
    new_dif->right = TakeDifferecial(arg, NULL, x);

    SetParents(new_dif, NULL);

    return new_dif;
}

Differentiator_t * DerFuncTAN(Differentiator_t * dif, Differentiator_t * new_dif, char x) {
    //new_dif->meaning = OPERATION;
    //new_dif->value.operation = DIVISION;
    //Differentiator_t * argument = dif->left;
    //new_dif->left = TakeDifferecial(argument, new_dif, x);
    //new_dif->right = DifferentiatorNodeInit(new_dif);
    //{
    //    new_dif->right->meaning = OPERATION;
    //    new_dif->right->value.operation = POWER;
    //    new_dif->right->left = DifferentiatorNodeInit(new_dif->right);
    //    {
    //        new_dif->right->left->meaning = OPERATION;
    //        new_dif->right->left->value.operation = COS;
    //        new_dif->right->left->left = DifferentiatorCopy(argument, new_dif->right->left);
    //    }
    //    new_dif->right->right = DifferentiatorNodeInitConst(new_dif->right, 2);
    //}
    //return new_dif;

    Differentiator_t * arg = dif->left;
    new_dif->meaning = OPERATION;
    new_dif->value.operation = DIVISION;
    new_dif->left = TakeDifferecial(arg, NULL, x);
    new_dif->right = BinFunc(POWER,
                             UnoFunc(COS, DifferentiatorCopy(arg, NULL)),
                             DifferentiatorNodeInitConst(NULL, 2));
    
    SetParents(new_dif, NULL);
    
    return new_dif;
}

Differentiator_t * DerFuncCOT(Differentiator_t * dif, Differentiator_t * new_dif, char x) {
    //new_dif->meaning = OPERATION;
    //new_dif->value.operation = MULTIPLICATION;
    //Differentiator_t * argument = dif->left;
    //new_dif->left = DifferentiatorNodeInit(new_dif);
    //{
    //    new_dif->left->meaning = VALUE;
    //    new_dif->left->value.number = -1;
    //}
    //new_dif->right = DifferentiatorNodeInit(new_dif);
    //{
    //    new_dif->right->meaning = OPERATION;
    //    new_dif->right->value.operation = DIVISION;
    //    new_dif->right->left = TakeDifferecial(argument, new_dif->right, x);
    //    new_dif->right->right = DifferentiatorNodeInit(new_dif->right);
    //    {
    //        new_dif->right->right->meaning = OPERATION;
    //        new_dif->right->right->value.operation = POWER;
    //        new_dif->right->right->left = DifferentiatorNodeInit(new_dif->right->right);
    //        {
    //            new_dif->right->right->left->meaning = OPERATION;
    //            new_dif->right->right->left->value.operation = SIN;
    //            new_dif->right->right->left->left = DifferentiatorCopy(argument, new_dif->right->right->left);
    //        }
    //        new_dif->right->right->right = DifferentiatorNodeInit(new_dif->right->right);
    //        {
    //            new_dif->right->right->right->meaning = VALUE;
    //            new_dif->right->right->right->value.number = 2;
    //        }
    //    }
    //}
    //return new_dif;

    Differentiator_t * arg = dif->left;
    new_dif->meaning = OPERATION;
    new_dif->value.operation = MULTIPLICATION;
    new_dif->left = DifferentiatorNodeInitConst(NULL, -1);
    new_dif->right = BinFunc(DIVISION,
                             TakeDifferecial(arg, NULL, x),
                             BinFunc(POWER,
                                     UnoFunc(SIN, DifferentiatorCopy(arg, NULL)),
                                     DifferentiatorNodeInitConst(NULL, 2)));
    
    SetParents(new_dif, NULL);

    return new_dif;
}

Differentiator_t * DerFuncEXPONENTIAL(Differentiator_t * dif, Differentiator_t * new_dif, char x) {
    //new_dif->meaning = OPERATION;
    //new_dif->value.operation = MULTIPLICATION;
    //Differentiator_t * argument = dif->left;
    //new_dif->left = DifferentiatorCopy(dif, new_dif);
    //new_dif->right = TakeDifferecial(argument, new_dif, x);
    //return new_dif;

    Differentiator_t * arg = dif->left;
    new_dif->meaning = OPERATION;
    new_dif->value.operation = MULTIPLICATION;
    new_dif->left = UnoFunc(EXPONENTIAL, DifferentiatorCopy(arg, NULL));
    new_dif->right = TakeDifferecial(arg, NULL, x);

    SetParents(new_dif, NULL);

    return new_dif;
}

Differentiator_t * DerFuncNATURAL_LOGARITHM(Differentiator_t * dif, Differentiator_t * new_dif, char x) {
    //new_dif->meaning = OPERATION;
    //new_dif->value.operation = DIVISION;
    //Differentiator_t * argument = dif->left;
    //new_dif->left = TakeDifferecial(argument, new_dif, x);
    //new_dif->right = DifferentiatorCopy(argument, new_dif);
    //return new_dif;

    Differentiator_t * arg = dif->left;
    new_dif->meaning = OPERATION;
    new_dif->value.operation = DIVISION;
    new_dif->left = TakeDifferecial(arg, NULL, x);
    new_dif->right = DifferentiatorCopy(arg, NULL);

    SetParents(new_dif, NULL);

    return new_dif;
}

Differentiator_t * DerFuncDECIMAL_LOGARITHM(Differentiator_t * dif, Differentiator_t * new_dif, char x) {
    //new_dif->meaning = OPERATION;
    //new_dif->value.operation = DIVISION;
    //Differentiator_t * argument = dif->left;
    //new_dif->left = TakeDifferecial(argument, new_dif, x);
    //new_dif->right = DifferentiatorNodeInit(new_dif);
    //{
    //    new_dif->right->meaning = OPERATION;
    //    new_dif->right->value.operation = MULTIPLICATION;
    //    new_dif->right->left = DifferentiatorCopy(argument, new_dif->right);
    //    new_dif->right->right = DifferentiatorNodeInit(new_dif->right);
    //    {
    //        new_dif->right->right->meaning = OPERATION;
    //        new_dif->right->right->value.operation = NATURAL_LOGARITHM;
    //        new_dif->right->right->left = DifferentiatorNodeInit(new_dif->right->right);
    //        {
    //            new_dif->right->right->left->meaning = VALUE;
    //            new_dif->right->right->left->value.number = 10;
    //        }
    //    }
    //}
    //return new_dif;

    Differentiator_t * arg = dif->left;
    new_dif->meaning = OPERATION;
    new_dif->left = TakeDifferecial(arg, NULL, x);
    new_dif->right = BinFunc(MULTIPLICATION,
                             DifferentiatorCopy(arg, NULL),
                             UnoFunc(NATURAL_LOGARITHM, DifferentiatorNodeInitConst(NULL, 10)));
    
    SetParents(new_dif, NULL);

    return new_dif;
}
//сделал f'/(2 * sqrt(f))
Differentiator_t * DerFuncSQUARE_ROOT(Differentiator_t * dif, Differentiator_t * new_dif, char x) {
    //new_dif->meaning = OPERATION;
    //new_dif->value.operation = DIVISION;
    //Differentiator_t * argument = dif->left;
    //new_dif->left = DifferentiatorNodeInit(new_dif);
    //{
    //    new_dif->left->meaning = OPERATION;
    //    new_dif->left->value.operation = MULTIPLICATION;
    //    new_dif->left->left = DifferentiatorNodeInit(new_dif->left);
    //    {
    //        new_dif->left->left->meaning = VALUE;
    //        new_dif->left->left->value.number = 0.5;
    //    }
    //    new_dif->left->right = TakeDifferecial(argument, new_dif->left, x);
    //}
    //new_dif->right = DifferentiatorNodeInit(new_dif);
    //{
    //    new_dif->right->meaning = OPERATION;
    //    new_dif->right->value.operation = SQUARE_ROOT;
    //    new_dif->right->left = DifferentiatorCopy(argument, new_dif->right);
    //}
    //return new_dif;

    Differentiator_t * arg = dif->left;
    new_dif->meaning = OPERATION;
    new_dif->value.operation = DIVISION;
    new_dif->left = TakeDifferecial(arg, NULL, x);
    new_dif->right = BinFunc(MULTIPLICATION,
                             DifferentiatorNodeInitConst(NULL, 2),
                             UnoFunc(SQUARE_ROOT, DifferentiatorCopy(arg, NULL)));

    SetParents(new_dif, NULL);

    return new_dif;
}

Differentiator_t * DerFuncARCSIN(Differentiator_t * dif, Differentiator_t * new_dif, char x) {
    //Differentiator_t * argument = dif->left;
    //new_dif->meaning = OPERATION;
    //new_dif->value.operation = DIVISION;
    //new_dif->left = TakeDifferecial(argument, new_dif, x);
    //new_dif->right = DifferentiatorNodeInit(new_dif);
    //{
    //    new_dif->right->meaning = OPERATION;
    //    new_dif->right->value.operation = SQUARE_ROOT;
    //    new_dif->right->left = DifferentiatorNodeInit(new_dif->right);
    //    {
    //        new_dif->right->left->meaning = OPERATION;
    //        new_dif->right->left->value.operation = SUBTRACTION;
    //        new_dif->right->left->left = DifferentiatorNodeInit(new_dif->right->left);
    //        {
    //            new_dif->right->left->left->meaning = VALUE;
    //            new_dif->right->left->left->value.number = 1;
    //        }
    //        new_dif->right->left->right = DifferentiatorNodeInit(new_dif->right->left);
    //        {
    //            new_dif->right->left->right->meaning = OPERATION;
    //            new_dif->right->left->right->value.operation = POWER;
    //            new_dif->right->left->right->left = DifferentiatorCopy(argument, new_dif->right->left->right);
    //            new_dif->right->left->right->right = DifferentiatorNodeInit(new_dif->right->left->right);
    //            {
    //                new_dif->right->left->right->right->meaning = VALUE;
    //                new_dif->right->left->right->right->value.number = 2;
    //            }
    //        }
    //    }
    //}
    //return new_dif;

    Differentiator_t * arg = dif->left;
    new_dif->meaning = OPERATION;
    new_dif->value.operation = MULTIPLICATION;
    new_dif->left = TakeDifferecial(arg, NULL, x);
    new_dif->right = UnoFunc(SQUARE_ROOT, BinFunc(SUBTRACTION,
                                                  DifferentiatorNodeInitConst(NULL, 1),
                                                  BinFunc(POWER,
                                                          DifferentiatorCopy(arg, NULL),
                                                          DifferentiatorNodeInitConst(NULL, 2))));
                                
    SetParents(new_dif, NULL);

    return new_dif;
}

Differentiator_t * DerFuncARCCOS(Differentiator_t * dif, Differentiator_t * new_dif, char x) {
    Differentiator_t * arg = dif->left;
    new_dif->meaning = OPERATION;
    new_dif->value.operation = MULTIPLICATION;
    new_dif->left = DifferentiatorNodeInitConst(NULL, -1);
    new_dif->right = BinFunc(DIVISION,
                             TakeDifferecial(arg, NULL, x),
                             UnoFunc(SQUARE_ROOT, BinFunc(SUBTRACTION,
                                                          DifferentiatorNodeInitConst(NULL, 1),
                                                          BinFunc(POWER,
                                                                  DifferentiatorCopy(arg, NULL),
                                                                  DifferentiatorNodeInitConst(NULL, 2)))));

    SetParents(new_dif, NULL);
    
    return new_dif;
}

Differentiator_t * DerFuncARCTAN(Differentiator_t * dif, Differentiator_t * new_dif, char x) {
    Differentiator_t * arg = dif->left;
    new_dif->meaning = OPERATION;
    new_dif->value.operation = DIVISION;
    new_dif->left = TakeDifferecial(arg, NULL, x);
    new_dif->right = BinFunc(ADDITION,
                             DifferentiatorNodeInitConst(NULL, 1),
                             BinFunc(POWER,
                                     DifferentiatorCopy(arg, NULL),
                                     DifferentiatorNodeInitConst(NULL, 2)));
                
    SetParents(new_dif, NULL);

    return new_dif;
}

Differentiator_t * DerFuncARCCOT(Differentiator_t * dif, Differentiator_t * new_dif, char x) {
    Differentiator_t * arg = dif->left;
    new_dif->meaning = OPERATION;
    new_dif->value.operation = MULTIPLICATION;
    new_dif->left = DifferentiatorNodeInitConst(NULL, -1);
    new_dif->right = BinFunc(DIVISION,
                             TakeDifferecial(arg, NULL, x),
                             BinFunc(ADDITION,
                                     DifferentiatorNodeInitConst(NULL, 1),
                                     BinFunc(POWER,
                                             DifferentiatorCopy(arg, NULL),
                                             DifferentiatorNodeInitConst(NULL, 2))));

    SetParents(new_dif, NULL);
    
    return new_dif;
}

Differentiator_t * DerFuncSIN_HYPERBOLIC(Differentiator_t * dif, Differentiator_t * new_dif, char x) {
    Differentiator_t * arg = dif->left;
    new_dif->meaning = OPERATION;
    new_dif->value.operation = MULTIPLICATION;
    new_dif->left = UnoFunc(COS_HYPERBOLIC, DifferentiatorCopy(arg, NULL));
    new_dif->right = TakeDifferecial(arg, NULL, x);

    SetParents(new_dif, NULL);

    return new_dif;
}

Differentiator_t * DerFuncCOS_HYPERBOLIC(Differentiator_t * dif, Differentiator_t * new_dif, char x) {
    Differentiator_t * arg = dif->left;
    new_dif->meaning = OPERATION;
    new_dif->value.operation = MULTIPLICATION;
    new_dif->left = UnoFunc(SIN_HYPERBOLIC, arg);
    new_dif->right = TakeDifferecial(arg, NULL, x);

    SetParents(new_dif, NULL);

    return new_dif;
}

Differentiator_t * DerFuncTAN_HYPERBOLIC(Differentiator_t * dif, Differentiator_t * new_dif, char x) {
    Differentiator_t * arg = dif->left;
    new_dif->meaning = OPERATION;
    new_dif->value.operation = MULTIPLICATION;
    new_dif->left = TakeDifferecial(arg, NULL, x);
    new_dif->right = BinFunc(POWER,
                             UnoFunc(COS_HYPERBOLIC, DifferentiatorCopy(arg, NULL)),
                             DifferentiatorNodeInitConst(NULL, 2));

    SetParents(new_dif, NULL);

    return new_dif;
}



