#include "application.h"

char *load_templates(char *path);
void activate_template(Grid *G, char *tmplt, int x, int y, int val, int activation);
void highlight_template(Grid *G, char *tmplt, int x, int y);
