#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "differentiator.h"
#include "./diff_part/take_diff.h"
#include "./init_destroy/diff_init_destroy.h"
#include "./graph/make_dot.h"
#include "./folder_names/generate_folder_and_names.h"
#include "./html_SVAGA/make_html.h"
#include "./math_part/calculate.h"
#include "simplification/simplify.h"
#include "./read_data_differentiator/read_data.h"
#include "./Letex_dump/make_Latex.h"
#include "./Letex_dump/Latex_derivatives.h"
#include "./read_data_differentiator/infix_read.h"

inline void SetParents(Differentiator_t * dif, Differentiator_t * parent) {
    if (dif == NULL) return;
    if (dif->left != NULL) SetParents(dif->left, dif);
    if (dif->right != NULL) SetParents(dif->right, dif);
    if (parent != NULL) dif->parent = parent;
    return;
}

double array_of_variables[26] = {};
int array_of_used_variables[26] = {};

int main() {
    //Differentiator_t * dif = DifferentiatorInit();
    //dif->meaning = OPERATION;
    //dif->value.operation = DIVISION;
//
    //
    //dif->left = DifferentiatorNodeInit(dif);
    //dif->left->meaning = VARIABLE;
    //dif->left->value.variable = 'x';
//
    //dif->right = DifferentiatorNodeInit(dif);
    //dif->right->meaning = OPERATION;
    //dif->right->value.operation = ADDITION;//
//
    //dif->right->left = DifferentiatorNodeInit(dif->right);
    //dif->right->left->meaning = VARIABLE;
    //dif->right->left->value.variable = 'x';
//
    //dif->right->right = DifferentiatorNodeInit(dif->right);
    //dif->right->right->meaning = VALUE;
    //dif->right->right->value.number = 6;//

    //Differentiator_t * dif = DifferentiatorInit();
    //dif->meaning = OPERATION;
    //dif->value.operation = POWER;
//
    //dif->left = DifferentiatorNodeInit(dif);
    //dif->left->meaning = VARIABLE;
    //dif->left->value.variable = 'x';
//
    //dif->right = DifferentiatorNodeInit(dif);
    //dif->right->meaning = OPERATION;
    //dif->right->value.operation = POWER;
//
    //dif->right->left = DifferentiatorNodeInit(dif->right);
    //dif->right->left->meaning = VARIABLE;
    //dif->right->left->value.variable = 'x';
    //
    //dif->right->right = DifferentiatorNodeInit(dif->right);
    //dif->right->right->meaning = VARIABLE;
    //dif->right->right->value.variable = 'x';
//
    //dif->right->right = DifferentiatorNodeInit(dif);
    //dif->right->right->meaning = OPERATION;
    //dif->right->right->value.operation = POWER;
    //dif->right->right->left = DifferentiatorNodeInit(dif->right->right);
    //dif->right->right->left->meaning = VARIABLE;
    //dif->right->right->left->value.variable = 'x';
    //dif->right->right->right = DifferentiatorNodeInit(dif->right->right);
    //dif->right->right->right->meaning = VARIABLE;
    //dif->right->right->right->value.variable = 'x';
//
//
    //array_of_used_variables['x' - 'a'] = 1;
    //printf("array_of_used_variables = %d\n\n", array_of_used_variables['x'-'a']);
    //array_of_variables['x' - 'a'] = 3;
    //printf("array_of_variables x = %lf\n\n", array_of_variables['x'-'a']);
//
    //Differentiator_t * new_dif = TakeDifferecial(dif, NULL, 'x');
//
//
    //
//
    // Differentiator_t * dif;
    // dif = DifferentiatorInit();
    // dif->meaning = OPERATION;
    // dif->value.operation = POWER;
    // dif->left = DifferentiatorNodeInit(dif);
    // dif->left->meaning = VARIABLE;
    // dif->left->value.variable = 'x';
    // dif->right = DifferentiatorNodeInit(dif);
    // dif->right->meaning = VARIABLE;
    // dif->right->value.variable = 'x';
    // Differentiator_t * new_dif = TakeDifferecial(dif, NULL, 'x');
    char str[] = "1+2*3*sin(0)$";
    char * s = str;
    Differentiator_t * dif = G(&s);
    //Differentiator_t * new_dif = TakeDifferecial(dif, NULL, 'x');


    char folder[256];
    GenerateFolder(folder, 256);
    
    FILE * HTML_file = CreateHTML(folder);
    FILE * Latex_file = CreateLatex(folder);
    PrintImageLatex(dif, Latex_file, folder);
    //PrintImageLatex(new_dif, Latex_file, folder);
    PrintFormula(dif, Latex_file);
    //PrintFormula(new_dif, Latex_file);
    FinalizeLatex(Latex_file);

    PrintImageHTML(dif, folder, HTML_file);
    dif = CalculateConst(dif);
    dif = RemoveNetral(dif);
    PrintImageHTML(dif, folder, HTML_file);


    //PrintImageHTML(new_dif, folder, HTML_file);
    //new_dif = CalculateConst(new_dif);
    //new_dif = RemoveNetral(new_dif);
    //PrintImageHTML(new_dif, folder, HTML_file);
    //new_dif = CalculateConst(new_dif);
    //new_dif = RemoveNetral(new_dif);
    //PrintImageHTML(new_dif, folder, HTML_file);
    //new_dif = CalculateConst(new_dif);
    //new_dif = RemoveNetral(new_dif);
    //PrintImageHTML(new_dif, folder, HTML_file);

    FinalizeHTML(HTML_file);

    double res = CalculateDifferentiator(dif);
    printf("funktion(x = %lf) = %lf \n\n", array_of_variables['x' - 'a'], res);
    //res = CalculateDifferentiator(new_dif);
    //printf("function'(x = %lf) = %lf \n\n", array_of_variables['x' - 'a'], res);

    

    return 0;
}