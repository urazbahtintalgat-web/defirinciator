#ifndef LATEX_DERIVATIVES_H
#define LATEX_DERIVATIVES_H
#include "../differentiator.h"

void PrintFormula(Differentiator_t * dif, FILE * Latex_file);

typedef void (*LatexFunc) (Differentiator_t * dif, FILE * Latex_file);
extern LatexFunc Latex_list[];


//-------------------------------BIN
void LatexADDITION(Differentiator_t * dif, FILE * Latex_file);
void LatexSUBTRACTION(Differentiator_t * dif, FILE * Latex_file);
void LatexMULTIPLICATION(Differentiator_t * dif, FILE * Latex_file);
void LatexDIVISION(Differentiator_t * dif, FILE * Latex_file);
void LatexPOWER(Differentiator_t * dif, FILE * Latex_file);
void LatexLOGARITHM(Differentiator_t * dif, FILE * Latex_file);
//-------------------------------UNO
void LatexSIN(Differentiator_t * dif, FILE * Latex_file);
void LatexCOS(Differentiator_t * dif, FILE * Latex_file);
void LatexTAN(Differentiator_t * dif, FILE * Latex_file);
void LatexCOT(Differentiator_t * dif, FILE * Latex_file);
void LatexEXPONENTIAL(Differentiator_t * dif, FILE * Latex_file);
void LatexNATURAL_LOGARITHM(Differentiator_t * dif, FILE * Latex_file);
void LatexDECIMAL_LOGARITHM(Differentiator_t * dif, FILE * Latex_file);
void LatexSQUARE_ROOT(Differentiator_t * dif, FILE * Latex_file);
void LatexARCSIN(Differentiator_t * dif, FILE * Latex_file);
void LatexARCCOS(Differentiator_t * dif, FILE * Latex_file);
void LatexARCTAN(Differentiator_t * dif, FILE * Latex_file);
void LatexARCCOT(Differentiator_t * dif, FILE * Latex_file);
void LatexSIN_HYPERBOLIC(Differentiator_t * dif, FILE * Latex_file);
void LatexCOS_HYPERBOLIC(Differentiator_t * dif, FILE * Latex_file);
void LatexTAN_HYPERBOLIC(Differentiator_t * dif, FILE * Latex_file);



#endif//LATEX_DERIVATIVES_H