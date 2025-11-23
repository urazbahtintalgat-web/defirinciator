#include "basic_derivatives.h"

#include "../differentiator.h"
#include "take_diff.h"
#include "../init_destroy/diff_init_destroy.h"




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
    //DerFuncPOWER,         //15
    //DerFuncLOGARITHM,     //16
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
    //производная произведения это сумма пар производная + обычная форма
    new_dif->value.operation = ADDITION;

    //левое поддерево это производная левого умножить на правое
    new_dif->left = DifferentiatorNodeInit(new_dif);//делаем новую вершину для произведения
    new_dif->left->meaning = OPERATION;
    new_dif->left->value.operation = MULTIPLICATION;
    //теперь в новую вершину надо записать производную левого и правое
    new_dif->left->left = TakeDifferecial(dif->left, new_dif->left, x);
    new_dif->left->right = DifferentiatorCopy(dif->right, new_dif->left);//правое просто копируем

    //правое поддерево это левое умножить на производную правого
    new_dif->right = DifferentiatorNodeInit(new_dif);//делаем новею вершину для производных
    new_dif->right->meaning = OPERATION;
    new_dif->right->value.operation = MULTIPLICATION;
    //теперь в новую вершину надо записать левое и производную правого
    new_dif->right->left = DifferentiatorCopy(dif->left, new_dif->right);//левое просто копируем
    new_dif->right->right = TakeDifferecial(dif->right, new_dif->right, x);

    return new_dif;
}

Differentiator_t * DerFuncDIVISION(Differentiator_t * dif, Differentiator_t * new_dif, char x) {
    //производная частного это частное от деления 
    //(проздводной левого(числителя) * правое(знаминатель) - производное правого(знеминателя) * левое(числитель))
    //делить на квадрат правого(знаменателя)
    new_dif->value.operation = DIVISION;

    //левое поддерево (проздводной левого(числителя) * правое(знаминатель) - производное правого(знеминателя) * левое(числитель))
    new_dif->left = DifferentiatorNodeInit(new_dif);//делаем новую вершину для всей числителя
    Differentiator_t * chislitel = new_dif->left;
    chislitel->meaning = OPERATION;
    chislitel->value.operation = SUBTRACTION;

    {
        chislitel->left = DifferentiatorNodeInit(chislitel);
        chislitel->left->meaning = OPERATION;
        chislitel->left->value.operation = MULTIPLICATION;
        chislitel->left->left = TakeDifferecial(dif->left, chislitel->left, x);
        chislitel->left->right = DifferentiatorCopy(dif->right, chislitel->left);

        chislitel->right = DifferentiatorNodeInit(chislitel);
        chislitel->right->meaning = OPERATION;
        chislitel->right->value.operation = MULTIPLICATION;
        chislitel->right->left = TakeDifferecial(dif->right, chislitel->right, x);
        chislitel->right->right = DifferentiatorCopy(dif->left, chislitel->right);
    }

    //правое поддерево квадрат правого(знаменателя)
    new_dif->right = DifferentiatorNodeInit(new_dif);
    new_dif->right->meaning = OPERATION;
    new_dif->right->value.operation = POWER;
    //левое поддерево это основание степени
    new_dif->right->left = DifferentiatorCopy(dif->right, new_dif->right);
    //правое поддерево это степень (2)
    new_dif->right->right = DifferentiatorNodeInit(new_dif->right);
    new_dif->right->right->meaning = VALUE;
    new_dif->right->right->value.number = 2;

    return new_dif;
}

//Differentiator_t * DerFuncPOWER(Differentiator_t * dif, Differentiator_t * new_dif, char x) {
//    new_dif->meaning = OPERATION;
//    Differentiator_t * base = dif->left;
//    Differentiator_t * degree = dif->right;
//
//    //f(x)^g(x) * (g'(x)*ln(f(x)) + g(x)*f'(x)/f(x))
//    new_dif->value.operation = ADDITION;
//    {
//        //f(x)^g(x) * (g'(x)*ln(f(x))
//        new_dif->left = DifferentiatorNodeInit(new_dif);
//        new_dif->left = OPERATION;
//        new_dif->left = 
//    }
//
//}



//---------------------------UNO

Differentiator_t * DerFuncSIN(Differentiator_t * dif, Differentiator_t * new_dif, char x) {
    return NULL;
}

Differentiator_t * DerFuncCOS(Differentiator_t * def, Differentiator_t * new_dif, char x) {
    return NULL;
}