#include "circuit_network.h"
#include "clist.h"
#include "spice.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    const char *file_name;
    FILE *file;
    struct clist *circuit_components;

    if (argc < 2) {
        printf("cayenne.c :: main :: no spice file path provided.\n");
    }

    file_name = argv[1];

    file = fopen(file_name, "r");
    if (file == NULL) {
        printf("cayenne.c :: main :: could not open file %s\n.", file_name);
        return -1;
    }

    circuit_components = spice_parse_file(file);
    fclose(file);

    struct circuit_network *circuit_network = circuit_network_new(circuit_components);
    if (!circuit_network) {
        printf("could not build circuit network\n");
        circuit_network_free(circuit_network);
        clist_free(circuit_components);
        return -1;
    }

    circuit_network_free(circuit_network);
    clist_free(circuit_components);
    return 0;
}
