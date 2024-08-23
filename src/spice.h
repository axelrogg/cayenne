#ifndef SPICE_H

#include "circuit_component.h"
#include <stdio.h>

#define MAX_FILE_LINE_BUFFER_SIZE 256

struct clist *spice_parse_file(FILE *);
int spice_parse_line(char *, struct clist *);
struct circuit_component *parse_circuit_component(char *);

#endif // !SPICE_H
