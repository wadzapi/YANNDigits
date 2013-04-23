#ifndef IMGFRAME_H
#define IMGFRAME_H

#include <QFrame>
#include <QImage>
#include <QColor>
#include <QPoint>
#include <QSize>
#include <QString>

class ImgFrame : public QFrame
{
    Q_OBJECT
public:
    explicit ImgFrame(QWidget *parent = 0);
    QImage GetImage() const;
    QImage GetResizedImage(unsigned int width, unsigned int height, unsigned int border);
    void SetImage(const QImage &image);
    void SetPenColor(const QColor &color);
    void SetPenWidth(int width);
    bool SaveImage(const QString &file_name, const char *format);
    bool OpenImage(const QString &file_name);
    QSize GetSize() const;
    QRect GetBounds() const;
    bool is_editable_;


protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    void InitImage();
    void InitFrame();
    void PaintToImage();
    QImage image_;
    bool is_painting_;
    bool is_erasing_;
    QColor background_color_;
    QColor pen_color_;
    int pen_width_;
    QPoint start_point_;
    QPoint end_point_;


signals:   
public slots:
    void ClearFrame();
    
};

#endif // IMGFRAME_H
