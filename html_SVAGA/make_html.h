#ifndef MAKE_HTML_H
#define MAKE_HTML_H
#include "stdio.h"
#include "../differentiator.h"

FILE * CreateHTML(char * folder);

void PrintImageHTML (Differentiator_t * dif, char * folder, FILE * HTML_file);

void FinalizeHTML(FILE * HTML_file);

#endif//MAKE_HTML_H