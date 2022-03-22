#ifndef CANVAS_H
#define CANVAS_H

#include <QVector>
#include <iostream>
#include <fstream>

#include "include/vector.h"

class Canvas {
public:
    Canvas(int nWidth, int nHeight);
    void write_pixel(int x, int y, Vector *color);
    Vector *get_pixel(int x, int y);
    void write_ppm();

    int nWidth, nHeight;
    QVector<QVector<Vector*>> aPixels = {};
};

#endif // CANVAS_H
