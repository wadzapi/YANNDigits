#ifndef MNISTDATASET_H
#define MNISTDATASET_H
#include "imagedata.h"
#include "mnistiterator.h"
#include <cstdio>

class MnistDataset
{
public:
    MnistDataset();
    bool LoadTrainingSet(const char* labels_path, const char* images_path);
    bool LoadTestSet(const char* labels_path, const char* images_path);
    void ReadNext();
    /// Функции интерфейса агрегатора
    unsigned int Count() const;
    ImageData Get(unsigned int index);
    MnistIterator CreateIterator();



private:
    /// Размер каждой картинки
    /// Значения magic number базы MNIST
    static const unsigned int kMagicTrainLabels = 0x00000801;//2049
    static const unsigned int kMagicTrainImages = 0x00000803;//2051
    static const unsigned int kMagicTestLabels = 0x00000801;//2049
    static const unsigned int kMagicTestImages = 0x00000803;//2051;
    /// Данные, получаемые из заголовка MNIST файла
    unsigned int magic_number_;
    unsigned int num_images_;
    unsigned int num_rows_;
    unsigned int num_cols_;
    /// Чтение меток из файла
    bool ReadLabels(const char* labels_path);
    /// Чтение данных изображения из файла
    bool ReadImageData(const char* images_path);
    bool ReadHeader();

    inline void SwapEndian(unsigned int& value);
    unsigned char read_buffer_;
    unsigned int images_loaded_;
    //bool is_loaded_;


};

#endif // MNISTDATASET_H
