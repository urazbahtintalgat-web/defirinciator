#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../differentiator.h"
#include "../graph/make_dot.h"

FILE * CreateHTMLFile(char * folder) {
    assert(folder);

    char HTML_name[256];
    snprintf(HTML_name, sizeof(HTML_name), "%s/HTML.html", folder);
    FILE * HTML_file = fopen(HTML_name, "w");
    return HTML_file;
}

void WriteTitle_akin(FILE * HTML_file) {//pre
    assert(HTML_file);

    fprintf(HTML_file, "<!DOCTYPE html>\n");
    fprintf(HTML_file, "<html lang=\"ru\">\n");

    fprintf(HTML_file, "<head>\n");
    fprintf(HTML_file, "    <meta charset=\"UTF-8\">\n");
    fprintf(HTML_file, "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n");
    fprintf(HTML_file, "    <title>Визуализация Дифференциатора</title>\n");
    fprintf(HTML_file, "    <style>\n");
    fprintf(HTML_file, "        body { font-family: Arial, sans-serif; margin: 20px; background-color: #f5f5f5; }\n");
    fprintf(HTML_file, "        .container { max-width: 1200px; margin: 0 auto; background: white; padding: 20px; border-radius: 8px; box-shadow: 0 2px 10px rgba(0,0,0,0.1); }\n");
    fprintf(HTML_file, "        h1 { color: #333; text-align: center; }\n");
    fprintf(HTML_file, "        .image-container { margin: 30px 0; text-align: center; padding: 15px; border: 1px solid #ddd; border-radius: 8px; background: #f9f9f9; }\n");
    fprintf(HTML_file, "        .image-container img { max-width: 100%%; height: auto; border: 1px solid #ccc; border-radius: 4px; }\n");
    fprintf(HTML_file, "        .caption { margin-top: 10px; font-style: italic; color: #666; }\n");
    fprintf(HTML_file, "        .timestamp { text-align: right; color: #888; font-size: 0.9em; margin-bottom: 20px; }\n");
    fprintf(HTML_file, "    </style>\n");
    fprintf(HTML_file, "</head>\n");
    
    fprintf(HTML_file, "<body>\n");
    fprintf(HTML_file, "    <div class=\"container\">\n");
    fprintf(HTML_file, "        <h1>🌳🌲🌴 Визуализация дерева Дифференциатора 🌴🌲🌳</h1>\n");
}

void WriteEnd_akin(FILE * HTML_file) {
    assert(HTML_file);
    
    fprintf(HTML_file, "    </div>\n");
    fprintf(HTML_file, "</body>\n");
    fprintf(HTML_file, "</html>\n");
}

FILE * CreateHTML(char * folder) {
    assert(folder);

    FILE * HTML_file = CreateHTMLFile(folder);

    WriteTitle_akin(HTML_file);

    return HTML_file;
}

void PrintImageHTML (Differentiator_t * dif, char * folder, FILE * HTML_file) {
    assert(dif);
    assert(folder);

    char * image_filename = NULL;
    MakeImage(dif, folder, &image_filename);

    if (image_filename) {
        fprintf(HTML_file, "        <div class=\"image-container\">\n");
        fprintf(HTML_file, "            <img src=\"../%s\" alt=\"Визуализация дерева Дифференциатора\">\n", image_filename);
        fprintf(HTML_file, "            <div class=\"caption\">Визуализация состояния дерева 🌴🌲🌳</div>\n");
        fprintf(HTML_file, "        </div>\n");
        
        printf("Image added to HTML: %s\n", image_filename);
        free(image_filename);
    } else {
        printf("Error: No image filename returned\n");
    }
}

void FinalizeHTML(FILE * HTML_file) {
    WriteEnd_akin(HTML_file);
    fclose(HTML_file);
}

