#include "make_Latex.h"

#include "../differentiator.h"
#include "../graph/make_dot.h"

#include <stdlib.h>
#include <assert.h>

static FILE * MakeLatex(char * folder) {
    assert(folder);
    char Latex_name[256];
    snprintf(Latex_name, sizeof(Latex_name), "%s/Latex.tex", folder);
    FILE * Latex_file = fopen(Latex_name, "w");
    return Latex_file;
}

static void WriteTitle(FILE * Latex_file) {
    assert(Latex_file);

    fprintf(Latex_file, "\\documentclass[12pt]{article}\n");
    fprintf(Latex_file, "\\usepackage{amsmath,amssymb,amsthm,geometry}\n");
    fprintf(Latex_file, "\\usepackage[utf8]{inputenc}\n");
    fprintf(Latex_file, "\\usepackage[T2A]{fontenc}\n");
    fprintf(Latex_file, "\\usepackage[russian]{babel}\n");
    fprintf(Latex_file, "\\usepackage{graphicx}\n");
    fprintf(Latex_file, "\\geometry{a4paper,margin=2.5cm}\n");
    fprintf(Latex_file, "\\setlength{\\parskip}{0.5em}\n");
    fprintf(Latex_file, "\\setlength{\\parindent}{0pt}\n");

    fprintf(Latex_file, "\\begin{document}\n");

    fprintf(Latex_file, "\\begin{center}\n");
    fprintf(Latex_file, "\\textbf{LATEX DUMP DIFFERENTIATOR} \\\\\n");
    fprintf(Latex_file, "\\end{center}\n");
}

static void WriteEnd(FILE * Latex_file) {
    assert(Latex_file);

    fprintf(Latex_file, "\\end{document}");
}

FILE * CreateLatex(char * folder) {
    assert(folder);
    FILE * Latex_file = MakeLatex(folder);
    WriteTitle(Latex_file);
    return Latex_file;
}

void FinalizeLatex(FILE * Latex_file) {
    assert(Latex_file);
    WriteEnd(Latex_file);
    fclose(Latex_file);
}


void PrintImageLatex(Differentiator_t * dif, FILE * Latex_file, char * folder) {
    assert(dif);
    assert(Latex_file);
    assert(folder);

    char * image_name = NULL;
    MakeImage(dif, folder, &image_name);

    if (image_name) {
        fprintf(Latex_file, "\\begin{center}\n");
        fprintf(Latex_file, "\\includegraphics[width=0.8\\linewidth]{%s}\n", image_name);
        fprintf(Latex_file, "\\end{center}\n");
        
        printf("Image added to Latex file: %s\n", image_name);
        free(image_name);
    } else {
        printf("ERROR: no image file returned\n");
    }
}