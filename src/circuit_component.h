#ifndef CIRCUIT_COMPONENT_H
#define CIRCUIT_COMPONENT_H

#define CIRCUIT_COMPONENT_VALUE_MULTIPLIER_FEMTO "f"  // e^-15
#define CIRCUIT_COMPONENT_VALUE_MULTIPLIER_PICO "p"   // e^-12
#define CIRCUIT_COMPONENT_VALUE_MULTIPLIER_NANO "n"   // e^-9
#define CIRCUIT_COMPONENT_VALUE_MULTIPLIER_MICRO "u"  // e^-6
#define CIRCUIT_COMPONENT_VALUE_MULTIPLIER_MILLI "m"  // e^-3
#define CIRCUIT_COMPONENT_VALUE_MULTIPLIER_KILO "k"   // e^3
#define CIRCUIT_COMPONENT_VALUE_MULTIPLIER_MEGA "meg" // e^6
#define CIRCUIT_COMPONENT_VALUE_MULTIPLIER_GIGA "g"   // e^9
#define CIRCUIT_COMPONENT_VALUE_MULTIPLIER_TERA "t"   // e^12

enum CIRCUIT_COMPONENT_TYPE_ENUM {
    CIRCUIT_COMPONENT_TYPE_VOLTAGE_SOURCE,
    CIRCUIT_COMPONENT_TYPE_CURRENT_SOURCE,
    CIRCUIT_COMPONENT_TYPE_RESISTOR,
    CIRCUIT_COMPONENT_TYPE_CAPACITOR,
    CIRCUIT_COMPONENT_TYPE_INDUCTOR,
};

struct circuit_component {
    enum CIRCUIT_COMPONENT_TYPE_ENUM type;
    int id;
    int node_positive;
    int node_negative;
    double value;
};

int circuit_component_is_shorted(struct circuit_component *);
struct circuit_component * circuit_component_new(void);
void circuit_component_free(struct circuit_component *);
double circuit_component_value_scinot(double, char *);

#endif // !CIRCUIT_COMPONENT_H
