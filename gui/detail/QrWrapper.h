#ifndef QRWRAPPER_H
#define QRWRAPPER_H

#include <QImage>
#include "util/qrutil.h"

namespace gui {

// wrapper Qr to QImage
class QrWrapper
{
public:
    static QImage generate( const util::QRSettings &settings );
};

} // namespace gui


#endif // QRWRAPPER_H
