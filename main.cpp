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

double array_of_variables[26] = {};
int array_of_used_variables[26] = {};

int main() {
    Differentiator_t * dif = DifferentiatorInit();
    dif->meaning = OPERATION;
    dif->value.operation = DIVISION;

    
    dif->left = DifferentiatorNodeInit(dif);
    dif->left->meaning = VARIABLE;
    dif->left->value.variable = 'x';

    dif->right = DifferentiatorNodeInit(dif);
    dif->right->meaning = OPERATION;
    dif->right->value.operation = MULTIPLICATION;//

    dif->right->left = DifferentiatorNodeInit(dif->right);
    dif->right->left->meaning = VARIABLE;
    dif->right->left->value.variable = 'x';

    dif->right->right = DifferentiatorNodeInit(dif->right);
    dif->right->right->meaning = VALUE;
    dif->right->right->value.number = 0;//

    array_of_used_variables['x' - 'a'] = 1;
    printf("array_of_used_variables = %d\n\n", array_of_used_variables['x'-'a']);
    array_of_variables['x' - 'a'] = 10;
    printf("array_of_variables x = %lf\n\n", array_of_variables['x'-'a']);

    Differentiator_t * new_dif = TakeDifferecial(dif, NULL, 'x');


    

    char folder[256];
    GenerateFolder(folder, 256);
    
    FILE * HTML_file = CreateHTML(folder);

    PrintImageHTML(dif, folder, HTML_file);
    dif = CalculateConst(dif);
    dif = RemoveNetral(dif);
    PrintImageHTML(dif, folder, HTML_file);


    PrintImageHTML(new_dif, folder, HTML_file);

    FinalizeHTML(HTML_file);

    double res = CalculateDifferentiator(dif);
    printf("funktion(x = %lf) = %lf \n\n", array_of_variables['x' - 'a'], res);
    res = CalculateDifferentiator(new_dif);
    printf("function'(x = %lf) = %lf \n\n", array_of_variables['x' - 'a'], res);

    

    return 0;
}