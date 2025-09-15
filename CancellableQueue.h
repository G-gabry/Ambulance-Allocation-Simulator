#pragma once
#include "LinkedQueue.h"
#include "Patient.h"

template <typename T>
class CancellableQueue : public LinkedQueue<T> {
public:
    bool cancel(int PID) {
        if (this->isEmpty()) {
            return false;
        }
        LinkedQueue<T> tempQueue;
        T currentItem;
        bool found = false;
        while (this->dequeue(currentItem)) {
            if (currentItem->getPID() == PID) {  
                found = true;
            }
            else {
                tempQueue.enqueue(currentItem);  
            }
        }
        while (tempQueue.dequeue(currentItem)) {
            this->enqueue(currentItem);
        }
        return found;  
    }
};