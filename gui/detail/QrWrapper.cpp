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

static const unsigned int LOGO_SIZE = 150;
QImage QrWrapper::addLogo( const QImage &image, const QImage &logo ) {
    if ( image.isNull() || logo.isNull() ) {
        return QImage();
    }

    QImage img(image);
    QImage logo_img = logo.scaled( LOGO_SIZE, LOGO_SIZE );

    unsigned int _x_offset = (img.width()- LOGO_SIZE) / 2;
    unsigned int _y_offset = (img.height() - LOGO_SIZE) / 2;

    for ( int w = 0; w < logo_img.width(); ++w ) {
        for ( int h = 0; h < logo_img.height(); ++h ) {
            img.setPixel( _x_offset + w, _y_offset + h, logo_img.pixel( w, h ) );
        }
    }
    return img;
}

}
