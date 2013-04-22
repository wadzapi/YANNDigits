#ifndef MNISTDATASET_H
#define MNISTDATASET_H
#include "imagedata.h"
#include <cstdio>

enum MnistType {
    kMnistTrain,
    kMnistTest
};

class MnistDataset
{
public:
    MnistDataset();
    ~MnistDataset();
    void Load(const char* images_path, const char* labels_path);
    /// Функции интерфейса агрегатора
    int ImagesCount() const;
    int LabelsCount() const;
    ImageData* GetImage(int index);
    unsigned char GetLabel(int index);
    /// Чтение меток из файла
    bool LoadLabels(const char* labels_path);
    /// Чтение данных изображения из файла
    bool LoadImages(const char* images_path);
    bool IsImagesLoaded();
    bool IsLabelsLoaded();
    int Rows();
    int Cols();


private:
    void DeleteImages();
    void DeleteLabels();
    /// Значения magic number базы MNIST
    static const int kMagicTrainLabels = 0x00000801;//2049
    static const int kMagicTrainImages = 0x00000803;//2051
    static const int kMagicTestLabels = 0x00000801;//2049
    static const int kMagicTestImages = 0x00000803;//2051;
    /// Изменение порядка байтов little-endian <--> big-endian
    inline void SwapEndian(int &value);
    /// Информация из заголовочных файлов
    int images_magic_number;
    int labels_magic_number;
    int num_labels_;
    int num_images_;
    int num_rows_;
    int num_cols_;
    /// Массив данных
    ImageData** images_;
    unsigned char* labels_;
    bool is_images_loaded;
    bool is_labels_loaded;
};

#endif // MNISTDATASET_H
