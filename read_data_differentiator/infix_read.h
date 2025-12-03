#ifndef INFIC_READ_H
#define INFIC_READ_H
#include "../differentiator.h"



Differentiator_t * G(char ** s);
static const int max_uno_operation_name_length = 30;
static char uno_operation_names[][max_uno_operation_name_length] {
    "",//0
    "",//1
    "", //2
    "",//3
    "",//4
    "",//5
    "",//6
    "",//7
    "",//8
    "",//9
    "",//10
    "",//11
    "",//12
    "",//13
    "",//14
    "",//15
    "",//16
    "",//17
    "",//18
    "",//19
    "",//20
    "",//21
    "",//22
    "",//23
    "",//24
    "",//25
    "",//26
    "",//27
    "",//28
    "",//29
    "",//30
    "sin",//31
    "cos",//32
    "tan",//33
    "cot",//34
    "exp",//35
    "ln",//36
    "lg",//37
    "sqrt",//38
    "arcsin",//39
    "arccos",//40
    "arctan",//41
    "arccot",//42
    "sinh",//43
    "cosh",//44
    "tanh",//45
    "",//46
    "",//47
    "",//48
    "",//49
    ""//50
};
static int uno_operation_amount = sizeof(uno_operation_names) / sizeof(uno_operation_names[0]);




#endif//INFIC_READ_H