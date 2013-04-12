#ifndef MNISTDATASET_H
#define MNISTDATASET_H
#include "imagedata.h"
#include <cstdio>

class MnistDataset
{
public:
    MnistDataset();
    bool Load(const char* images_path, const char* labels_path);
    /// Функции интерфейса агрегатора
    unsigned int Count() const;
    ImageData Get(unsigned int index);



private:
    /// Размер каждой картинки
    /// Значения magic number базы MNIST
    static const int kMagicTrainLabels = 0x00000801;//2049
    static const int kMagicTrainImages = 0x00000803;//2051
    static const int kMagicTestLabels = 0x00000801;//2049
    static const int kMagicTestImages = 0x00000803;//2051;
    int labels_magic_number;
    int images_magic_number;
    int num_labels_;
    int num_images_;
    int num_rows_;
    int num_cols_;
    /// Чтение меток из файла
    bool LoadLabels(const char* labels_path);
    /// Чтение данных изображения из файла
    bool LoadImages(const char* images_path);
    /// Изменение порядка байтов little-endian <--> big-endian
    inline void SwapEndian(int &value);
    std::vector<ImageData> mnist_images;
    std::vector<unsigned char> mnist_labels;


};

#endif // MNISTDATASET_H
