#ifndef COUNTER_H
#define COUNTER_H

#include <QObject>

class Counter : public QObject
{
    Q_OBJECT
public:
    explicit Counter(QObject *parent = 0);
    unsigned int GetValue();
    unsigned int GetIndex();
    void Init(unsigned int min_value, unsigned int max_value);
    bool IsInit();
    unsigned int MaxValue();
    unsigned int MinValue();
    unsigned int Size();
    void SetLooped(bool looped);
    void SetStepSize(unsigned int step_size);
private:
    unsigned int current_value_;
    unsigned int max_value_;
    unsigned int min_value_;
    unsigned int step_size_;
    bool is_looped_;
    bool is_init_;
signals:
    void ValueChanged(unsigned int new_value);
public slots:
    void SetValue(unsigned int value);
    void Next();
    void Prev();
};

#endif // COUNTER_H
