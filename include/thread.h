#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <QMutex>
#include <QDebug>

#include "include/vector.h"

class Thread: public QThread {
public:
    Thread(int nStart, int nEnd, QMutex *mutex, Vector *data);
    void run();
    int nStart, nEnd;
    QMutex *mutex;
    Vector *data;
};

#endif // THREAD_H
