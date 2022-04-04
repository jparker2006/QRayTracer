#include "include/misc/thread.h"

Thread::Thread(int nStart, int nEnd, QMutex *mutex, Vector *data) {
    this->nStart = nStart;
    this->nEnd = nEnd;
    this->mutex = mutex;
    this->data = data;
}

void Thread::run() {
    mutex->lock();
    if (nEnd == 0)
        data->fx = 1;
    if (nEnd == 1)
        data->fy = 1;
    if (nEnd == 2)
        data->fz = 1;
    mutex->unlock();
}
