#ifndef PARSER_H
#define PARSER_H

#include <QString>
#include <QVector>

#include "include/vector.h"
#include "include/group.h"
#include "include/triangle.h"

class Parser {
public:
    Parser();
    char *LoadFile(const char *source);
    Group* parse_file(QString sFilePath);
    QVector<Triangle *> fan_triangulation(QVector<Vector *> vertices, QList<QString> indices);
};

#endif // PARSER_H
