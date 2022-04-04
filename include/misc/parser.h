#ifndef PARSER_H
#define PARSER_H

#include <QString>
#include <QVector>

#include "include/math/vector.h"
#include "include/bodies/group.h"
#include "include/bodies/triangle.h"
#include "include/bodies/smoothtriangle.h"

class Parser {
public:
    Parser();
    QVector<Body *> parse_file(QString sFilePath, Material *mat);
    char *LoadFile(const char *source);
    QVector<Triangle *> fan_triangulation(QVector<Vector *> vertices, QList<QString> indices);
    QVector<SmoothTriangle *> fan_smooth_triangulation(QVector<Vector *> vertices, QVector<Vector *> normals,  QList<QString> v_indices,  QList<QString> n_indices);
    Material *mat = nullptr;
};

#endif // PARSER_H
