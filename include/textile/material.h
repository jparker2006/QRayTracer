#ifndef MATERIAL_H
#define MATERIAL_H

#include "include/math/vector.h"
#include "include/render/light.h"
#include "include/textile/pattern.h"
#include "include/math/matrix.h"

class Material {
public:
    Material(Vector *color, float fAmbient, float fDiffuse, float fSpecular, float fShininess);
    Vector *lighting(Light *light, Vector *point, Vector *eye, Vector *normal, bool bShadowed, Matrix *transformation);
    float fAmbient, fDiffuse, fSpecular, fShininess;
    Vector *color;
    Pattern *pattern = nullptr;
    float fReflective = 0, fTransparency = 0, fRefractive_Index = 1;
};

#endif // MATERIAL_H
