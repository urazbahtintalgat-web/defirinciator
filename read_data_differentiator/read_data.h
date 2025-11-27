#ifndef READ_DATA_H
#define READ_DATA_H
#include "../differentiator.h"
#include <stdlib.h>

const int read_data_names_max_length = 30;
static char operation_names[][read_data_names_max_length] {
    "NOTHING",  //0
    "VALUE",    //1
    "VARIABLE", //2
    "OPERATION",//3
    "",//4
    "",//5
    "",//6
    "",//7
    "",//8
    "",//9
    "START_BIN_OPERATIONS",//10
    "ADDITION",//11
    "SUBTRACTION",//12
    "MULTIPLICATION",//13
    "DIVISION",//14
    "POWER",//15
    "LOGARITHM",//16
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
    "END_BIN_OPERATIONS",//29
    "START_UN_OPERATIONS",//30
    "SIN",//31
    "COS",//32
    "TAN",//33
    "COT",//34
    "EXPONENTIAL",//35
    "NATURAL_LOGARITHM",//36
    "DECIMAL_LOGARITHM",//37
    "SQUARE_ROOT",//38
    "ARCSIN",//39
    "ARCCOS",//40
    "ARCTAN",//41
    "ARCCOT",//42
    "SIN_HYPERBOLIC",//43
    "COS_HYPERBOLIC",//44
    "TAN_HYPERBOLIC",//45
    "",//46
    "",//47
    "",//48
    "END_UN_OPERATIONS",//49
    ""//50
};
static char operation_symbols[][read_data_names_max_length] {
    "",//0
    "",//1
    "",//2
    "",//3
    "",//4
    "",//5
    "",//6
    "",//7
    "",//8
    "",//9
    "",//10
    "+",//11
    "-",//12
    "*",//13
    "/",//14
    "^",//15
    "log",//16
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
    "e^",//35
    "ln",//36
    "ln",//37
    "sqrt",//38
    "arcsin",//39
    "arccos",//40
    "arctan",//41
    "arccot",//42
    "sh",//43
    "ch",//44
    "th",//45
    "",//46
    "",//47
    "",//48
    "",//49
    ""//50
};

int read_data_differentiator(Differentiator_t ** dif, FILE * file);

#endif//READ_DATA_H