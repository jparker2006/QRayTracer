#include "include/material.h"

Material::Material(Vector *color, float fAmbient, float fDiffuse, float fSpecular, float fShininess) {
    this->color = color;
    this->fAmbient = fAmbient;
    this->fDiffuse = fDiffuse;
    this->fSpecular = fSpecular;
    this->fShininess = fShininess;
}

Vector* Material::lighting(Light *light, Vector *point, Vector *eye, Vector *normal, bool bShadowed, Matrix *transformation) {
    if (this->pattern)
        this->color = this->pattern->pattern_at(point, transformation);
    Vector *effective_color = this->color->ew_multiply(light->intensity);
    Vector *vAmbient = effective_color->scalar_multiply(this->fAmbient);
    if (bShadowed)
        return vAmbient;
    Vector *v_ab_Light = light->position->ew_subtract(point);
    Vector *vLight = v_ab_Light->normalize();
    delete v_ab_Light;
    float flight_dot_normal = vLight->dot_product(normal);
    Vector *vDiffuse, *vSpecular;
    if (flight_dot_normal < 0) {
        vDiffuse = new Vector(0.0, 0.0, 0.0, 0.0);
        vSpecular = new Vector(0.0, 0.0, 0.0, 0.0);
    }
    else {
        vDiffuse = effective_color->scalar_multiply(this->fDiffuse * flight_dot_normal);
        Vector *vnegLight = vLight->negate();
        Vector *vReflect = vnegLight->reflect(normal);
        delete vnegLight;
        float freflect_dot_eye = vReflect->dot_product(eye);
        if (freflect_dot_eye <= 0)
            vSpecular = new Vector(0.0, 0.0, 0.0, 0.0);
        else {
            float factor = qPow(freflect_dot_eye, this->fShininess);
            vSpecular = light->intensity->scalar_multiply(this->fSpecular * factor);
        }
        delete vReflect;
        delete effective_color;
    }
    Vector *final = vAmbient->ew_add(vDiffuse->ew_add(vSpecular));
    delete vAmbient;
    delete vDiffuse;
    delete vSpecular;
    return final;
}
