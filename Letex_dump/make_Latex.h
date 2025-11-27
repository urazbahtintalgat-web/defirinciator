#ifndef MAKE_LATEX_H
#define MAKE_LATEX_H
#include <stdlib.h>
#include "../differentiator.h"

FILE * CreateLatex(char * folder);
void FinalizeLatex(FILE * Latex_file);
void PrintImageLatex(Differentiator_t * dif, FILE * Latex_file, char * folder);



#endif//MAKE_LATEX_H