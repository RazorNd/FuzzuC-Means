#ifndef XIMAGE_H
#define XIMAGE_H

#include <QImage>
#include <FuzzuCMeans.h>

namespace RzrNd {
namespace fcm {

template<>
size_t getSize(const QImage& X)
{
    return static_cast<size_t>(X.width() * X.height());
}

template<>
X_t getValue(const QImage& X, size_t k)
{
    size_t width = static_cast<size_t>(X.width());
    const int y = static_cast<int>(k / width),
            x = static_cast<int>(k % width);

    QRgb rgb = X.pixel(x, y);

    return X_t {
        qRed(rgb)   / 255.0,
        qGreen(rgb) / 255.0,
        qBlue(rgb)  / 255.0
    };
}

} /// fcm   namespace
} /// RzrNd namespace


#endif // XIMAGE_H
