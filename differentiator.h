#ifndef DIFFERENTIATOR_H
#define DIFFERENTIATOR_H

#include <stdio.h>

extern double array_of_variables[26];
extern int    array_of_used_variables[26];

typedef enum Meaning_t {
    NOTHING = 0,
    /////////////////////////////////
    VALUE = 1,
    /////////////////////////////////
    VARIABLE = 2,
    /////////////////////////////////
    OPERATION = 3,//:
    //BIN
    START_BIN_OPERATIONS = 10,
    ADDITION             = 11,
    SUBTRACTION          = 12,
    MULTIPLICATION       = 13,
    DIVISION             = 14,
    POWER                = 15,
    LOGARITHM            = 16,
    END_BIN_OPERATIONS   = 29,
    //UNO
    START_UN_OPERATIONS  = 30,
    SIN                  = 31,
    COS                  = 32,
    TAN                  = 33,
    COT                  = 34,
    EXPONENTIAL          = 35,
    NATURAL_LOGARITHM    = 36,
    DECIMAL_LOGARITHM    = 37,
    SQUARE_ROOT          = 38,
    ARCSIN               = 39,
    ARCCOS               = 40,
    ARCTAN               = 41,
    ARCCOT               = 42,
    SIN_HYPERBOLIC       = 43,
    COS_HYPERBOLIC       = 44,
    TAN_HYPERBOLIC       = 45,
    END_UN_OPERATIONS    = 49
} Meaning_t;

const int max_name_length = 30;
static char Meaning_strings[][max_name_length] {
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
    "ADDITION(+)",//11
    "SUBTRACTION(-)",//12
    "MULTIPLICATION(*)",//13
    "DIVISION(/)",//14
    "POWER(^)",//15
    "LOGARITHM(log_a(b))",//16
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






typedef struct Differentiator_t {
    Meaning_t meaning;
    union value {
        double number;
        Meaning_t operation;
        char variable;
    } value;
    struct Differentiator_t * parent;
    struct Differentiator_t * left;
    struct Differentiator_t * right;
} Differentiator_t;

//CALCULATE

//

//READ_DATA

//

//


#endif//DIFFERENTIATOR_H