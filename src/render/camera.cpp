#include "include/render/camera.h"

Camera::Camera(float fhsize, float fvsize, float fov, Matrix *transformation) {
    this->fhsize = fhsize;
    this->fvsize = fvsize;
    this->fov = fov;
    this->transformation = transformation;
    this->fpixel_size = this->pixel_size();
}

float Camera::pixel_size() {
    float fhalf_view = qTan(this->fov / 2.0);
    float faspect_ratio = this->fhsize / this->fvsize;
    if (faspect_ratio >= 1.0) {
        this->half_width = fhalf_view;
        this->half_height = fhalf_view / faspect_ratio;
    }
    else {
        this->half_width = fhalf_view * faspect_ratio;
        this->half_height = fhalf_view;
    }
    return this->half_width * 2.0 / this->fhsize;
}

Ray *Camera::ray_for_pixel(float fx, float fy) {
    float fxoff = (fx + 0.5) * this->fpixel_size;
    float fyoff = (fy + 0.5) * this->fpixel_size;
    float world_x = this->half_width - fxoff;
    float world_y = this->half_height - fyoff;
    Matrix *mInverse = this->transformation->inverse();
    Vector *vPixel = mInverse->vector_multiply(new Vector(world_x, world_y, -1, 1));
    Vector *vOrigin = mInverse->vector_multiply(new Vector(0, 0, 0, 1));
    delete mInverse;
    Vector *vDirection = vPixel->ew_subtract(vOrigin);
    Vector *nvDirection = vDirection->normalize();
    delete vPixel;
    delete vDirection;
    return new Ray(vOrigin, nvDirection);
}
