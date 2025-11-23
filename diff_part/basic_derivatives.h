#ifndef BASIC_DERIVATIVES_H
#define BASIC_DERIVATIVES_H
#include "../differentiator.h"

 typedef Differentiator_t * (*DerivativeFunction)(Differentiator_t * dif, Differentiator_t * new_dif, char x);
//---------------------------------BIN
Differentiator_t * DerFuncADDITION      (Differentiator_t * dif, Differentiator_t * new_dif, char x);
Differentiator_t * DerFuncSUBTRACTION   (Differentiator_t * dif, Differentiator_t * new_dif, char x);
Differentiator_t * DerFuncMULTIPLICATION(Differentiator_t * dif, Differentiator_t * new_dif, char x);
Differentiator_t * DerFuncDIVISION      (Differentiator_t * dif, Differentiator_t * new_dif, char x);
Differentiator_t * DerFuncPOWER         (Differentiator_t * dif, Differentiator_t * new_dif, char x);

//---------------------------------UNO
Differentiator_t * DerFuncSIN(Differentiator_t * dif, Differentiator_t * new_dif, char x);
Differentiator_t * DerFuncCOS(Differentiator_t * dif, Differentiator_t * new_dif, char x);





extern DerivativeFunction derivative_function_list[];


#endif//BASIC_DERIVATIVES_H