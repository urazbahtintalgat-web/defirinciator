#ifndef SIMPLIFY_H
#define SIMPLIFY_H
#include "../differentiator.h"

Differentiator_t * CalculateConst(Differentiator_t * dif);
Differentiator_t * RemoveNetral(Differentiator_t * dif);

typedef Differentiator_t * (*SimplificationFunction) (Differentiator_t * dif);

extern SimplificationFunction simplification_functions_list[];


#endif//SIMPLIFY_H