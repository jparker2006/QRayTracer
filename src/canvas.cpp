#include "include/canvas.h"

Canvas::Canvas(int nWidth, int nHeight) {
    this->nWidth = nWidth;
    this->nHeight = nHeight;
    for (int i=0; i<nWidth; i++) {
        QVector<Vector*> curr_vec = {};
        for (int j=0; j<nHeight; j++) {
            curr_vec.push_back(new Vector(0.0, 0.0, 0.0, 0.0));
        }
        this->aPixels.push_back(curr_vec);
    }
}

void Canvas::write_pixel(int x, int y, Vector *color) {
    this->aPixels[x][y] = color;
}

Vector* Canvas::get_pixel(int x, int y) {
    return this->aPixels[x][y];
}

void Canvas::write_ppm() {
    QString sFile = "";
    sFile += "P3\n" + QString::number(this->nWidth) + " " + QString::number(this->nHeight) + "\n255\n"; // heading
    for (int i=0; i<this->nHeight; i++) {
        for (int j=0; j<this->nWidth; j++) {
            // this should be more elegant
            float r = this->aPixels[j][i]->fx;
            float g = this->aPixels[j][i]->fy;
            float b = this->aPixels[j][i]->fz;
            r  = r > 1 ? 1 : r;
            g  = g > 1 ? 1 : g;
            b  = b > 1 ? 1 : b;
            sFile += QString::number(qRound(r * 255.0)) + " ";
            sFile += QString::number(qRound(g * 255.0)) + " ";
            sFile += QString::number(qRound(b * 255.0)) + " ";
        }
        sFile += "\n";
    }
    std::ofstream f_ppm;
    f_ppm.open("image.ppm");
    f_ppm << sFile.toStdString();
    f_ppm.close();
}
