#ifndef MAKE_DOT
#define MAKE_DOT

#include "../differentiator.h"

void MakeGraph(FILE * dot_file, Differentiator_t * dif);

void MakeImage(Differentiator_t * dif, char * folder, char ** pointer_for_image_filename);

#endif//MAKE_DOT