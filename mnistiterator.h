#ifndef MNISTITERATOR_H
#define MNISTITERATOR_H
#include "mnistdataset.h"
#include "imagedata.h"

class MnistIterator
{
public:
    MnistIterator(MnistDataset &mnist);
    void First();
    void Next();
    ImageData CurrentItem();
    bool isDone();

private:
    unsigned int current_index_;
};

#endif // MNISTITERATOR_H
