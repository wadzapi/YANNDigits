#include "mnistdataset.h"

MnistDataset::MnistDataset() {

}

unsigned int MnistDataset::Count() const {
    return images_loaded_;
}

inline void MnistDataset::SwapEndian(unsigned int &value) {
    value = (value >> 24) | ((value << 8) & 0x00FF0000) | ((vlaue >> 8) & 0x0000FF00) | (value << 24);
}



