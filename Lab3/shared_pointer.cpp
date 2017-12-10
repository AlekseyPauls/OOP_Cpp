#include "shared_pointer.h"

namespace wf {

    SharedPointer::SharedPointer() : ptr(nullptr), counter(nullptr) {}

    template <typename T>
    SharedPointer::SharedPointer(T * p) : ptr(p) {
        counter = new int(1);
    }

    template <typename T>
    SharedPointer::SharedPointer(SharedPointer sp) {
        ptr = sp.ptr;
        counter = sp.counter;
        (*counter)++;
    }

    SharedPointer::~SharedPointer() {
        (*counter)--;
        if (*counter == 0) {
            delete ptr;
            delete counter;
        }
    }

    SharedPointer& SharedPointer::operator=(const SharedPointer &sp) {
        if(ptr != sp.ptr) {
            (*counter--);
            if (*counter == 0) {
                delete ptr;
                delete counter;
            }
            ptr = sp.ptr;
            counter = sp.counter;
            (*counter)++;
        }
        return *this;
    }

    template <typename T>
    T& SharedPointer::operator*() {
        return *ptr;
    }

}
