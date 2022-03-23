#ifndef MATERIAL_H
#define MATERIAL_H

#include "include/vector.h"
#include "include/light.h"

class Material {
public:
    Material(Vector *color, float fAmbient, float fDiffuse, float fSpecular, float fShininess);
    Vector *lighting(Light *light, Vector *point, Vector *eye, Vector *normal);
    float fAmbient, fDiffuse, fSpecular, fShininess;
    Vector *color;
};

#endif // MATERIAL_H
