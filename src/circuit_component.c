#include "circuit_component.h"
#include <stdlib.h>

int circuit_component_is_shorted(struct circuit_component *comp) {
    if (!comp) {
        return -1;
    }
    return (comp->node_positive == comp->node_negative);
}

struct circuit_component *circuit_component_new(void) {
    struct circuit_component *component = malloc(sizeof(struct circuit_component));
    if (!component) {
        return NULL;
    }
    return component;
}

void circuit_component_free(struct circuit_component *component) {
    free(component);
}
