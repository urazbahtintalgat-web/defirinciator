#ifndef DIFFERENTIATOR_INIT_DESTROY
#define DIFFERENTIATOR_INIT_DESTROY
#include "../differentiator.h"

#include <stdio.h>
#include <stdlib.h>

Differentiator_t * DifferentiatorInit(void);

void DifferentiatorDestroy(Differentiator_t ** dif);

Differentiator_t * DifferentiatorNodeInit(Differentiator_t * parent);

Differentiator_t * DifferentiatorCopy(Differentiator_t * dif, Differentiator_t * copy_parent);

Differentiator_t * DifferentiatorNodeInitConst(Differentiator_t * parent, double value);

void EnterMeaning(Differentiator_t * dif, Meaning_t meaning);
void EnterValueNumber(Differentiator_t * dif, double value);
void EnterValueOperation(Differentiator_t * dif, Meaning_t operation);
void EnterValueVariable(Differentiator_t * dif, char variable);

#endif//DIFFERENTIATOR_INIT_DESTROY