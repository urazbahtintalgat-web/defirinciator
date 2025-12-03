#include "infix_read.h"

#include "../differentiator.h"
#include "../init_destroy/diff_init_destroy.h"

#include <ctype.h>
#include <math.h>
#include <string.h>

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
static inline Differentiator_t * SetValue(double value) {
    Differentiator_t * new_dif = DifferentiatorInit();

    new_dif->meaning = VALUE;
    new_dif->value.number = value;

    return new_dif;
}
static int ReadUnoFunc(char ** s, char * buffer, int buffer_size) {
    buffer_size = buffer_size * 1;
    int i = 0;
    while ('a' <= **s && **s <= 'z') {
        buffer[i++] = **s;
        (*s)++;
    }
    return i;
}
static Differentiator_t * CheckFunc(char * buffer);

Differentiator_t * G(char ** s);
Differentiator_t * E(char ** s);
Differentiator_t * T(char ** s);
Differentiator_t * P(char ** s);
Differentiator_t * N(char ** s);
Differentiator_t * V(char ** s);
//Differentiator_t * F(char ** s);

#define SYNAX_ERROR printf("ERROR\n in file %s:%d in func %s\n", __FILE__, __LINE__, __func__)
/*
diff * G = E'$'
diff * E = T{[+ -]T}*
diff * T = P{[* /]P}*
diff * P = '('E')' | N | V | F
diff * N = ['0'-'9']+
diff * V = ['a'-'z']*
diff * F = ["sin", "cos",...]'(' E ')'
*/

Differentiator_t * G (char ** s) {
    Differentiator_t * dif = E(s);
    if (**s != '$') {
        SYNAX_ERROR;
        DifferentiatorDestroy(&dif);
        return NULL;
    }
    return dif;
}

Differentiator_t * E(char ** s) {
    Differentiator_t * dif = T(s);
    while (**s == '+' || **s == '-') {
        Meaning_t op = ADDITION;
        if (**s == '-') op = SUBTRACTION;
        (*s)++;
        Differentiator_t * new_dif = T(s);
        dif = BinFunc(op, DifferentiatorCopy(dif, NULL), new_dif);
    }
    return dif;
}

Differentiator_t * T(char ** s) {
    Differentiator_t * dif = P(s);
    while (**s == '*' || **s == '/') {
        Meaning_t op = MULTIPLICATION;
        if (**s == '/') op = DIVISION;
        (*s)++;
        Differentiator_t * new_dif = P(s);
        dif = BinFunc(op, DifferentiatorCopy(dif, NULL), new_dif);
    }
    return dif;
}

Differentiator_t * P(char ** s) {
    if (**s == '(') {
        (*s)++;
        Differentiator_t * dif = E(s);
        if (**s != ')') {
            SYNAX_ERROR;
            DifferentiatorDestroy(&dif);
            return NULL;
        }
        (*s)++;
        return dif;
    }

    Differentiator_t * dif = N(s);
    return dif;
}

Differentiator_t * N(char ** s) {
    if (isalpha(**s)) {
        Differentiator_t * dif = V(s);
        return dif;
    }

    double val = 0;
    int minus = 1;
    if (**s == '-') {
        minus = -1;
        (*s)++;
    }
    while (isdigit(**s)) {
        val = val * 10 + (**s - '0');
        (*s)++;
    }
    if (**s == '.') {
        double des = 0;
        int step = 0;
        (*s)++;
        while (isdigit(**s)) {
            step++;
            des = des * 10 + (**s - '0');
            (*s)++;
        }
        val = val + des / (pow(10, step));
    }
    val *= minus;
    Differentiator_t * dif = SetValue(val);

    return dif;
}

Differentiator_t * V(char ** s) {
    int siz = 16;
    char * buffer = (char *) calloc (siz, sizeof(char));
    int i = 0;
    buffer[i++] = **s;
    (*s)++;

    if (!isalpha(buffer[0])) {
        SYNAX_ERROR;
        free(buffer);
        return NULL;
    }

    while (isalnum(**s) || **s == '_') {
        buffer[i++] = **s;
        (*s)++;
        if (i == siz - 1) {
            siz *= 2;
            buffer = (char *) realloc (buffer, siz);
            for (int j = i; j < siz; j++) {
                buffer[j] = 0;
            }
        }
    }

    Differentiator_t * dif = CheckFunc(buffer);
    if (dif) {
        if (**s != '(') {
            SYNAX_ERROR;
            DifferentiatorDestroy(&dif);
            return NULL;
        }
        (*s)++;
        dif->left = E(s);
        if (**s != ')') {
            SYNAX_ERROR;
            DifferentiatorDestroy(&dif);
            return NULL;
        }
        (*s)++;
        free(buffer);
        return dif;
    }

    //если не функция значит переменная У МЕНЯ ПОКА ЧТО ЭТО ПРОСТО ЧАР
    if (i == 1) {
        dif = DifferentiatorInit();
        dif->meaning = VARIABLE;
        dif->value.variable = buffer[0];
    } else {
        SYNAX_ERROR;
        free(buffer);
        return NULL;
    }
    free(buffer);
    return dif;
}

static Differentiator_t * CheckFunc(char * buffer) {
    for (int i = 0; i < uno_operation_amount; i++) {
        if (strcmp(buffer, uno_operation_names[i]) == 0) {
            return UnoFunc((Meaning_t) i, NULL);
        }
    }
    return NULL;
}
