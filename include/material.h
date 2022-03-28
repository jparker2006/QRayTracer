#ifndef MATERIAL_H
#define MATERIAL_H

#include "include/vector.h"
#include "include/light.h"
#include "include/pattern.h"
#include "include/matrix.h"

class Material {
public:
    Material(Vector *color, float fAmbient, float fDiffuse, float fSpecular, float fShininess);
    Vector *lighting(Light *light, Vector *point, Vector *eye, Vector *normal, bool bShadowed, Matrix *transformation);
    float fAmbient, fDiffuse, fSpecular, fShininess;
    Vector *color;
    Pattern *pattern;
};

#endif // MATERIAL_H
