#include "include/material.h"

Material::Material(Vector *color, float fAmbient, float fDiffuse, float fSpecular, float fShininess) {
    this->color = color;
    this->fAmbient = fAmbient;
    this->fDiffuse = fDiffuse;
    this->fSpecular = fSpecular;
    this->fShininess = fShininess;
}

Vector* Material::lighting(Light *light, Vector *point, Vector *eye, Vector *normal, bool bShadowed, Matrix *transformation) {
    if (bShadowed)
        return new Vector(0.10, 0.10, 0.10, 0.0);
    if (this->pattern)
        this->color = this->pattern->pattern_at(point, transformation);
    Vector *effective_color = this->color->ew_multiply(light->intensity);
    Vector *vLight = light->position->ew_subtract(point)->normalize();
    Vector *vAmbient = effective_color->scalar_multiply(this->fAmbient);
    float flight_dot_normal = vLight->dot_product(normal);
    Vector *vDiffuse, *vSpecular;
    if (flight_dot_normal < 0) {
        vDiffuse = new Vector(0.0, 0.0, 0.0, 0.0);
        vSpecular = new Vector(0.0, 0.0, 0.0, 0.0);
    }
    else {
        vDiffuse = effective_color->scalar_multiply(this->fDiffuse * flight_dot_normal);
        Vector *vReflect = vLight->negate()->reflect(normal);
        float freflect_dot_eye = vReflect->dot_product(eye);
        if (freflect_dot_eye <= 0)
            vSpecular = new Vector(0.0, 0.0, 0.0, 0.0);
        else {
            float factor = qPow(freflect_dot_eye, this->fShininess);
            vSpecular = light->intensity->scalar_multiply(this->fSpecular * factor);
        }
    }
    return vAmbient->ew_add(vDiffuse->ew_add(vSpecular));
}
