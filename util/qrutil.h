#ifndef UTIL_QRUTIL_H
#define UTIL_QRUTIL_H

#include "util/detail/QrCode.hpp"

namespace util {

enum MaskLevel {
    Mask_Automatic = -1,
    Mask_0,
    Mask_1,
    Mask_2,
    Mask_3,
    Mask_4,
    Mask_5,
    Mask_6,
    Mask_7
};

enum QRQuality {
    QR_LOW = 0,
    QR_MEDIUM = 1,
    QR_QUARTILE = 2,
    QR_HIGH = 3
};

// settings for QR generator
struct QRSettings {
    QRSettings(std::string input) : text(input) {}

    std::string text;
    QRQuality quality = QR_LOW;
    MaskLevel mask = Mask_Automatic;
    int min_version = 1;
    int max_version = 40;
};

// result for QR
struct QRResult {
    QRResult() {}
    qrcodegen::QrCode result;
    std::string err;
};

class QRutil
{
public:
    static QRResult generate( const QRSettings &settings );
};

} // namespace util

#endif // UTIL_QRUTIL_H
