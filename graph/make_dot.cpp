#include "make_dot.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>

#include "../differentiator.h"
#include "../folder_names/generate_folder_and_names.h"

char * ChooseColor(Differentiator_t * dif) {
    if (dif->meaning == VALUE) {
        return strdup("white");
    }
    if (dif->meaning == VARIABLE) {
        return strdup("grey");
    }
    if (START_BIN_OPERATIONS < dif->value.operation && dif->value.operation < END_BIN_OPERATIONS) {
        return strdup("lightblue");
    }
    return strdup("purple");
}

void PrintNode(FILE * dot_file, Differentiator_t * dif) {
    //printf("meaning = %d\n", dif->meaning);
    //printf("%s\n", Meaning_strings[dif->meaning]);
    //printf("operation = %d\n", dif->value.operation);
    //printf("%s\n", Meaning_strings[dif->value.operation]);

    char * color = ChooseColor(dif);

    fprintf(dot_file, "    Node_%p [shape=Mrecord, style=filled, fillcolor=%s", (void*) dif, color);
    fprintf(dot_file, ", label=\"{<pointer> Node_%p | <meaning> meaning = %s | ", (void*) dif, Meaning_strings[dif->meaning]);
    if (dif->meaning == OPERATION) {
        fprintf(dot_file ,"<value> operation = %s | ", Meaning_strings[dif->value.operation]);
    } else if (dif->meaning == VARIABLE) {
        fprintf(dot_file, "<value> varigable = %c | ", dif->value.variable);
    } else if (dif->meaning == VALUE) {
        fprintf(dot_file, "<value> value = %lf | ", dif->value.number);
    }
    fprintf(dot_file, "{<left> left = Node_%p | <right> right = Node_%p}}\"]\n", dif->left, dif->right);

    free(color);
    return;
}

void PrintArrows(FILE * dot_file, Differentiator_t * dif) {
    if (dif->left != NULL) {
        PrintNode(dot_file, dif->left);
        fprintf(dot_file, "Node_%p:left -> Node_%p [color=green]\n", (void *) dif, (void *) dif->left);
        PrintArrows(dot_file, dif->left);
    }
    if (dif->right != NULL) {
        PrintNode(dot_file, dif->right);
        fprintf(dot_file, "Node_%p:right -> Node_%p [color=red]\n", (void *) dif, (void *) dif->right);
        PrintArrows(dot_file, dif->right);
    }
}

void MakeGraph(FILE * dot_file, Differentiator_t * dif) {
    assert(dot_file);
    assert(dif);


    fprintf(dot_file, "digraph differenciator {\n");
    fprintf(dot_file, "rankdir=TB\n");
    fprintf(dot_file, "node [shape=star, style=filled, fillcolor=red, color=red]\n");
    fprintf(dot_file, "\n");

    PrintNode(dot_file, dif);
    PrintArrows(dot_file, dif);

    fprintf(dot_file, "}");
    fclose(dot_file);
    return;
}

void MakeImage(Differentiator_t * dif, char * folder, char ** pointer_for_image_filename) {
    assert(dif);
    assert(folder);

    char image_filename[256];
    GenerateFilename(image_filename, 256, folder);

    char dot_filename[256];
    strcpy(dot_filename, image_filename);
    char * png_ptr = strstr(dot_filename, ".svg");
    strcpy(png_ptr, ".dot");

    FILE * dot_file = fopen(dot_filename, "w");
    MakeGraph(dot_file, dif);

    char comand[256];
    snprintf(comand, sizeof(comand), "dot -Tsvg \"%s\" -o \"%s\"", dot_filename, image_filename);

    if (system(comand) == 0) {
        printf("Differentiator tree image made: %s\n", image_filename);
    }

    *pointer_for_image_filename = strdup(image_filename);
    remove(dot_filename);
    return;
}