#include "mnistiterator.h"

MnistIterator::MnistIterator() {
}

void MnistIterator::First() {
    current_index_ = 0;
}

void MnistIterator::Next() {
    ++current_index_;
}
