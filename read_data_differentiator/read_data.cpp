#include "read_data.h"

#include "../differentiator.h"
#include "../init_destroy/diff_init_destroy.h"
#include <string.h>
#include <ctype.h>

static void skip_spases(FILE * file) {
    int c = 0;
    while ((c = getc(file)) != EOF) {
        if (!isspace(c)) {
            ungetc(c, file);
            return;
        }
    }
}

static void get_word(FILE * file, char * buffer, int buffer_size) {
    char c = getc(file);
    while (isspace(c)) c = getc(file);
    if (c == EOF) return;

    for (int i = 0; i < buffer_size - 1; i++) {
        buffer[i] = c;
        c = getc(file);
        if (isspace(c) || c == '(' || c == ')') {
            ungetc(c, file);
            return;
        }
    }
}

int read_data_differentiator(Differentiator_t ** dif, FILE * file) {
    if (dif == NULL || file == NULL) {
        printf("ERROR: NULL pointer were transfered %s:%d\n", __FILE__, __LINE__);
        return 1;
    }

    skip_spases(file);

    int chr = fgetc(file);
    if (chr == EOF) {
        printf("ERROR: unexpected EOF %s:%d\n", __FILE__, __LINE__);
        return 1;
    }
    ungetc(chr, file);

    if (chr != '(' && chr != 'n') {
        printf("ERROR: expected '(' but got '%c' %s:%d\n", chr, __FILE__, __LINE__);
        return 1;
    }

    if (chr == '(') getc(file);

    skip_spases(file);

    char string[sizeof(operation_names[0])] = {};
    get_word(file, string, sizeof(string));

    if (strcmp(string, "nil") == 0) {
        *dif = NULL;
        skip_spases(file);
        return 0;
        //chr = getc(file);
        //if (chr == ')') return 0;
        //ungetc(chr, file);
        //return 0;
    }

    *dif = DifferentiatorInit();
    if (*dif == NULL) return 1;

    for (unsigned long i = 0; i < sizeof(operation_names)/sizeof(operation_names[0]); i++) {
        if (operation_names[i][0] == '\0') continue;

        if (strcmp(string, operation_names[i]) == 0 || strcmp(string, operation_symbols[i]) == 0) {
            (*dif)->meaning = OPERATION;
            (*dif)->value.operation = (Meaning_t) i;
            break;
        }
    }

    if ((*dif)->meaning != OPERATION) {
        if (strlen(string) == 1 && 'a' <= string[0] && string[0] <= 'z') {
            (*dif)->meaning = VARIABLE;
            (*dif)->value.variable = string[0];
            array_of_used_variables[string[0] - 'a'] = 1;
        } else if (isdigit(string[0]) || string[0] == '-' || string[0] == '.') {
            (*dif)->meaning = VALUE;
            (*dif)->value.number = atof(string);
        } else {
            printf("ERROR: invalid string '%s' %s:%d\n",string, __FILE__, __LINE__);
            return 1;
        }
    }

    skip_spases(file);

    if (read_data_differentiator(&(*dif)->left, file) != 0) {
        DifferentiatorDestroy(dif);
        return 1;
    }

    skip_spases(file);

    if (read_data_differentiator(&(*dif)->right, file) != 0) {
        DifferentiatorDestroy(dif);
        return 1;
    }

    skip_spases(file);

    chr = getc(file);
    if (chr != ')') {
        printf("ERROR: expexted ')' but got '%c' %s:%d\n", chr, __FILE__, __LINE__);
        DifferentiatorDestroy(dif);
        return 1;
    }

    return 0;
}