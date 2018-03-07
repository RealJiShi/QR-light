#include "QrWrapper.h"

namespace gui {

QImage QrWrapper::generate( const util::QRSettings &settings ) {
    if ( settings.text.empty() ) {
        return QImage();
    }

    // validation check
    if ( settings.min_version < qrcodegen::QrCode::MIN_VERSION ||
         settings.min_version > qrcodegen::QrCode::MAX_VERSION ||
         settings.max_version < qrcodegen::QrCode::MIN_VERSION ||
         settings.max_version > qrcodegen::QrCode::MAX_VERSION ||
         settings.max_version < settings.min_version ) {
        return QImage();
    }

    const util::QRResult &result = util::QRutil::generate( settings );
    unsigned int img_size = result.result.getSize();
    QImage img( img_size, img_size, QImage::Format_RGB888 );
    for ( unsigned int y = 0; y < img_size; ++y ) {
        for ( unsigned int x = 0; x < img_size; ++x ) {
            img.setPixel( x, y, result.result.getModule(x, y) ? qRgb(0, 0, 0) : qRgb( 255, 255, 255 ) );
        }
    }
    return img;
}

}

