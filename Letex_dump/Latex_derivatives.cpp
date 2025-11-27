#include "Latex_derivatives.h"

LatexFunc Latex_list[] = {
    NULL,//0
    NULL,//1
    NULL,//2
    NULL,//3
    NULL,//4
    NULL,//5
    NULL,//6
    NULL,//7
    NULL,//8
    NULL,//9
    NULL,//10
    LatexADDITION,      //11
    LatexSUBTRACTION,   //12
    LatexMULTIPLICATION,//13
    LatexDIVISION,      //14
    LatexPOWER,         //15
    LatexLOGARITHM,     //16
    NULL,//17
    NULL,//18
    NULL,//19
    NULL,//20
    NULL,//21
    NULL,//22
    NULL,//23
    NULL,//24
    NULL,//25
    NULL,//26
    NULL,//27
    NULL,//28
    NULL,//29
    NULL,//30
    LatexSIN,              //31
    LatexCOS,              //32
    LatexTAN,              //33
    LatexCOT,              //34
    LatexEXPONENTIAL,      //35
    LatexNATURAL_LOGARITHM,//36
    LatexDECIMAL_LOGARITHM,//37
    LatexSQUARE_ROOT,      //38
    LatexARCSIN,           //39
    LatexARCCOS,           //40
    LatexARCTAN,           //41
    LatexARCCOT,           //42
    LatexSIN_HYPERBOLIC,   //43
    LatexCOS_HYPERBOLIC,   //44
    LatexTAN_HYPERBOLIC,   //45
    NULL,//46
    NULL,//47
    NULL,//48
    NULL,//49
    NULL,//50
};

void PrintArg(FILE * Latex_file, Differentiator_t * dif) {
    if (dif->meaning == VALUE) {
        fprintf(Latex_file, "{");//---------------
        fprintf(Latex_file, "%lf", dif->value.number);
        fprintf(Latex_file, "}");//---------------
        return;
    }
    if (dif->meaning == VARIABLE) {
        fprintf(Latex_file, "{");//---------------
        fprintf(Latex_file, "%c", dif->value.variable);
        fprintf(Latex_file, "}");//---------------
        return;
    }

    Meaning_t op = dif->value.operation;
    void (*Func)(Differentiator_t * dif, FILE * Latex_file);
    Func = Latex_list[op];
    fprintf(Latex_file, "{");//---------------
    Func(dif, Latex_file);
    fprintf(Latex_file, "}");//---------------
    return;
}

void PrintFormula(Differentiator_t * dif, FILE * Latex_file) {
    fprintf(Latex_file, "\n$");
    PrintArg(Latex_file, dif);
    fprintf(Latex_file, "$\n");
}


//---------------------------BIN

void LatexADDITION(Differentiator_t * dif, FILE * Latex_file) {
    PrintArg(Latex_file, dif->left);
    fprintf(Latex_file, "+");
    PrintArg(Latex_file, dif->right);
}

void LatexSUBTRACTION(Differentiator_t * dif, FILE * Latex_file) {
    PrintArg(Latex_file, dif->left);
    fprintf(Latex_file, "-");
    PrintArg(Latex_file, dif->right);
}

void LatexMULTIPLICATION(Differentiator_t * dif, FILE * Latex_file) {
    if (dif->left->meaning != OPERATION) PrintArg(Latex_file, dif->left);
    else {
        fprintf(Latex_file, "(");
        PrintArg(Latex_file, dif->left);
        fprintf(Latex_file, ")");
    }

    fprintf(Latex_file, "\\cdot");

    if (dif->right->meaning != OPERATION) PrintArg(Latex_file, dif->right);
    else {
        fprintf(Latex_file, "(");
        PrintArg(Latex_file, dif->right);
        fprintf(Latex_file, ")");
    }
}

void LatexDIVISION(Differentiator_t * dif, FILE * Latex_file) {
    fprintf(Latex_file, "\\frac{");
    PrintArg(Latex_file, dif->left);
    fprintf(Latex_file, "}{");
    PrintArg(Latex_file, dif->right);
    fprintf(Latex_file, "}");
}

void LatexPOWER(Differentiator_t * dif, FILE * Latex_file) {
    PrintArg(Latex_file, dif->left);
    fprintf(Latex_file, "^");
    PrintArg(Latex_file, dif->right);
}

void LatexLOGARITHM(Differentiator_t * dif, FILE * Latex_file) {
    fprintf(Latex_file, "log_");
    PrintArg(Latex_file, dif->left);
    fprintf(Latex_file, "(");
    PrintArg(Latex_file, dif->right);
    fprintf(Latex_file, ")");
}


//--------------------UNO

void LatexSIN(Differentiator_t * dif, FILE * Latex_file) {
    fprintf(Latex_file, "sin(");
    PrintArg(Latex_file, dif->left);
    fprintf(Latex_file, ")");
}

void LatexCOS(Differentiator_t * dif, FILE * Latex_file) {
    fprintf(Latex_file, "cos(");
    PrintArg(Latex_file, dif->left);
    fprintf(Latex_file, ")");
}

void LatexTAN(Differentiator_t * dif, FILE * Latex_file) {
    fprintf(Latex_file, "tan(");
    PrintArg(Latex_file, dif->left);
    fprintf(Latex_file, ")");
}

void LatexCOT(Differentiator_t * dif, FILE * Latex_file) {
    fprintf(Latex_file, "cot(");
    PrintArg(Latex_file, dif->left);
    fprintf(Latex_file, ")");
}

void LatexEXPONENTIAL(Differentiator_t * dif, FILE * Latex_file) {
    fprintf(Latex_file, "e^");
    PrintArg(Latex_file, dif->left);
}

void LatexNATURAL_LOGARITHM(Differentiator_t * dif, FILE * Latex_file) {
    fprintf(Latex_file, "ln(");
    PrintArg(Latex_file, dif->left);
    fprintf(Latex_file, ")");
}

void LatexDECIMAL_LOGARITHM(Differentiator_t * dif, FILE * Latex_file) {
    fprintf(Latex_file, "lg(");
    PrintArg(Latex_file, dif->left);
    fprintf(Latex_file, ")");
}

void LatexSQUARE_ROOT(Differentiator_t * dif, FILE * Latex_file) {
    fprintf(Latex_file, "\\sqrt");
    PrintArg(Latex_file, dif->left);
}

void LatexARCSIN(Differentiator_t * dif, FILE * Latex_file) {
    fprintf(Latex_file, "arcsin(");
    PrintArg(Latex_file, dif->left);
    fprintf(Latex_file, ")");
}

void LatexARCCOS(Differentiator_t * dif, FILE * Latex_file) {
    fprintf(Latex_file, "arccos(");
    PrintArg(Latex_file, dif->left);
    fprintf(Latex_file, ")");
}

void LatexARCTAN(Differentiator_t * dif, FILE * Latex_file) {
    fprintf(Latex_file, "arctan(");
    PrintArg(Latex_file, dif->left);
    fprintf(Latex_file, ")");
}

void LatexARCCOT(Differentiator_t * dif, FILE * Latex_file) {
    fprintf(Latex_file, "arccot(");
    PrintArg(Latex_file, dif->left);
    fprintf(Latex_file, ")");
}

void LatexSIN_HYPERBOLIC(Differentiator_t * dif, FILE * Latex_file) {
    fprintf(Latex_file, "sh(");
    PrintArg(Latex_file, dif->left);
    fprintf(Latex_file, ")");
}

void LatexCOS_HYPERBOLIC(Differentiator_t * dif, FILE * Latex_file) {
    fprintf(Latex_file, "ch(");
    PrintArg(Latex_file, dif->left);
    fprintf(Latex_file, ")");
}

void LatexTAN_HYPERBOLIC(Differentiator_t * dif, FILE * Latex_file) {
    fprintf(Latex_file, "th(");
    PrintArg(Latex_file, dif->left);
    fprintf(Latex_file, ")");
}