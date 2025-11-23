#ifndef CALCULATE_H
#define CALCULATE_H
#include "../differentiator.h"

typedef double (*CalculateFunction)(Differentiator_t * dif);
//---------------------------------BIN
double FuncADDITION         (Differentiator_t * dif);
double FuncSUBTRACTION      (Differentiator_t * dif);
double FuncMULTIPLICATION   (Differentiator_t * dif);
double FuncDIVISION         (Differentiator_t * dif);
double FuncPOWER            (Differentiator_t * dif);
double FuncLOGARITHM        (Differentiator_t * dif);

//---------------------------------UNO
double FuncSIN              (Differentiator_t * dif);
double FuncCOS              (Differentiator_t * dif);
double FuncTAN              (Differentiator_t * dif);
double FuncCOT              (Differentiator_t * dif);
double FuncEXPONENTIAL      (Differentiator_t * dif);
double FuncNATURAL_LOGARITHM(Differentiator_t * dif);
double FuncDECIMAL_LOGARITHM(Differentiator_t * dif);
double FuncSQUARE_ROOT      (Differentiator_t * dif);
double FuncARCSIN           (Differentiator_t * dif);
double FuncARCCOS           (Differentiator_t * dif);
double FuncARCTAN           (Differentiator_t * dif);
double FuncARCCOT           (Differentiator_t * dif);
double FuncSIN_HYPERBOLIC   (Differentiator_t * dif);
double FuncCOS_HYPERBOLIC   (Differentiator_t * dif);
double FuncTAN_HYPERBOLIC   (Differentiator_t * dif);





double CalculateDifferentiator(Differentiator_t * dif);

extern CalculateFunction function_list[];
extern double array_of_variables[26];
extern int    array_of_used_variables[26];

#endif//CALCULATE_H