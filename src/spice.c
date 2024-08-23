#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "circuit_component.h"
#include "clist.h"
#include "spice.h"

static void ignore_inline_comments(char *line) {
    char *comment_start;

    comment_start = strchr(line, '%');
    if (comment_start)
        *comment_start = '\0';

    comment_start = strchr(line, '#');
    if (comment_start)
        *comment_start = '\0';

    comment_start = strchr(line, ';');
    if (comment_start)
        *comment_start = '\0';
}

struct clist *spice_parse_file(FILE *file) {
    struct clist *list;
    char buff[MAX_FILE_LINE_BUFFER_SIZE];

    if (file == NULL) {
        printf("spice.c :: spice_parse_file :: file provided is NULL.\n");
        return NULL;
    }

    list = clist_new();
    if (!list)
        return NULL;

    int line_count = 0;
    while (fgets(buff, MAX_FILE_LINE_BUFFER_SIZE, file)) {
        if (spice_parse_line(buff, list) == -1) {
            printf("spice.c :: spice_parse_file :: unabled to parse line "
                   "number %d from file.\n",
                   line_count + 1);
            return NULL;
        }
        line_count++;
    }
    return list;
}

int spice_parse_line(char *line, struct clist *list) {
    ignore_inline_comments(line);
    char *start;
    char *end;
    struct circuit_component *component;

    if (!list)
        return -1;

    start = line;
    while (isspace((unsigned char)*start)) {
        start++;
    }

    if (strlen(start) == 0) {
        return -1;
    }

    end = start + strlen(start) - 1;
    while (end > start && isspace((unsigned char)*end)) {
        end--;
    }
    end[1] = '\0';

    for (char *p = start; *p; p++) {
        *p = tolower(*p);
    }

    component = parse_circuit_component(start);
    if (!component)
        return -1;

    if (clist_append(list, component) == -1) {
        printf("spice.c :: spice_parse_line :: failed to append new circuit "
               "element to circuit elements list.\n");
        return -1;
    }

    return 0;
}

struct circuit_component *parse_circuit_component(char *line) {
    char value_multiplier[3] = {0};
    double value_parsed;
    struct circuit_component *component;
    int items_parsed;

    component = malloc(sizeof(struct circuit_component));
    if (!component)
        return NULL;

    switch (line[0]) {
    case 'v':
        component->type = CIRCUIT_COMPONENT_TYPE_VOLTAGE_SOURCE;
        items_parsed = sscanf(
            line, "v%d %d %d %lf%s", &component->id, &component->node_positive,
            &component->node_negative, &value_parsed, value_multiplier);
        break;
    case 'i':
        component->type = CIRCUIT_COMPONENT_TYPE_CURRENT_SOURCE;
        items_parsed = sscanf(
            line, "i%d %d %d %lf%s", &component->id, &component->node_positive,
            &component->node_negative, &value_parsed, value_multiplier);

        break;

    case 'r':
        component->type = CIRCUIT_COMPONENT_TYPE_RESISTOR;
        items_parsed = sscanf(
            line, "r%d %d %d %lf%s", &component->id, &component->node_positive,
            &component->node_negative, &value_parsed, value_multiplier);
        break;

    case 'c':
        component->type = CIRCUIT_COMPONENT_TYPE_CAPACITOR;
        items_parsed = sscanf(
            line, "c%d %d %d %lf%s", &component->id, &component->node_positive,
            &component->node_negative, &value_parsed, value_multiplier);
        break;

    case 'l':
        component->type = CIRCUIT_COMPONENT_TYPE_INDUCTOR;
        items_parsed = sscanf(
            line, "l%d %d %d %lf%s", &component->id, &component->node_positive,
            &component->node_negative, &value_parsed, value_multiplier);
        break;

    default:
        printf("spice.c :: parse_circomp :: unsupported circuit component");
        break;
    }
    printf("%s\n", value_multiplier);
    component->value = circuit_component_value_scinot(value_parsed, value_multiplier);
    return component;
}


double circuit_component_value_scinot(double value, char *multiplier) {
    if (strcmp(multiplier, CIRCUIT_COMPONENT_VALUE_MULTIPLIER_FEMTO) == 0) {
        return value * pow(10, -15);
    } else if (strcmp(multiplier, CIRCUIT_COMPONENT_VALUE_MULTIPLIER_PICO) == 0) {
        return value * pow(10, -12);
    } else if (strcmp(multiplier, CIRCUIT_COMPONENT_VALUE_MULTIPLIER_NANO) == 0) {
        return value * pow(10, -9);
    } else if (strcmp(multiplier, CIRCUIT_COMPONENT_VALUE_MULTIPLIER_MICRO) ==
               0) {
        return value * pow(10, -6);
    } else if (strcmp(multiplier, CIRCUIT_COMPONENT_VALUE_MULTIPLIER_MILLI) ==
               0) {
        return value * pow(10, -3);
    } else if (strcmp(multiplier, CIRCUIT_COMPONENT_VALUE_MULTIPLIER_KILO) == 0) {
        return value * pow(10, 3);
    } else if (strcmp(multiplier, CIRCUIT_COMPONENT_VALUE_MULTIPLIER_MEGA) == 0) {
        return value * pow(10, 6);
    } else if (strcmp(multiplier, CIRCUIT_COMPONENT_VALUE_MULTIPLIER_GIGA) == 0) {
        return value * pow(10, 9);
    } else if (strcmp(multiplier, CIRCUIT_COMPONENT_VALUE_MULTIPLIER_TERA) == 0) {
        return value * pow(10, 12);
    } else {
        return value;
    }
}
