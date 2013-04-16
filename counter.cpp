#include "counter.h"

Counter::Counter(QObject *parent) :
    QObject(parent)
{
    is_init_ = false;
    current_value_ = 0;
    min_value_ = 0;
    max_value_ = 0;
    step_size_ = 0;
}

void Counter::Init(unsigned int min_value, unsigned int max_value) {
    current_value_ = min_value;
    min_value_ = min_value;
    max_value_ = max_value;
    step_size_ = 1;
    is_init_ = true;
    is_looped_ = false;
}

unsigned int Counter::GetValue() {
    return current_value_;
}

unsigned int Counter::GetIndex() {
    return current_value_ - min_value_;
}

unsigned int Counter::MaxValue() {
    return max_value_;
}

unsigned int Counter::MinValue() {
    return min_value_;
}

void Counter::SetLooped(bool looped) {
    is_looped_ = looped;
}

void Counter::SetValue(unsigned int value) {
    if (is_init_) {
        if (max_value_ == min_value_)
            current_value_ = max_value_;
        unsigned int num_elements = Size();
        if (value < min_value_) {
            if (is_looped_)
                current_value_ = max_value_  - ((min_value_ - value) % num_elements) + 1;
            else
                current_value_ = min_value_;
        } else if (value > max_value_) {
            if (is_looped_)
                current_value_ = min_value_  + ((value - max_value_) % num_elements) - 1;
            else
                current_value_ = max_value_;
        } else {
            current_value_ = value;
        }
        emit ValueChanged(current_value_);
    }
}

unsigned int Counter::Size() {
    return max_value_ - min_value_ + 1;
}

void Counter::SetStepSize(unsigned int step_size) {
    if (is_init_) {
        unsigned int num_elements = Size();
        if (num_elements == 0)
            return;
        else
            step_size_ = step_size % num_elements;
    }
}

void Counter::Next() {
    if (is_init_)
        SetValue(current_value_ + step_size_);
}

void Counter::Prev() {
    if (is_init_)
        SetValue(current_value_ - step_size_);
}
