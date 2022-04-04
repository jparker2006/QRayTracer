#ifndef LIGHT_H
#define LIGHT_H

#include "include/math/vector.h"

class Light {
public:
    Light(Vector *intensity, Vector *position);
    Vector *intensity, *position;
};

#endif // LIGHT_H
