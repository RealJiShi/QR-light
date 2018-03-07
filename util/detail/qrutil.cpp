#include "util/qrutil.h"
#include "util/detail/QrCode.hpp"

namespace util {

using namespace qrcodegen;
QRResult QRutil::generate(const QRSettings &settings) {
    QRResult result;
    if ( settings.text.empty() ) {
        return result;
    }

    // parsing settings
    qrcodegen::QrCode::Ecc ecc = static_cast<qrcodegen::QrCode::Ecc>(settings.quality - QR_LOW);
    int mask = settings.mask;
    int min_version = settings.min_version;
    int max_version = settings.max_version;

    // encoding
    std::vector<QrSegment> segs = QrSegment::makeSegments( settings.text.c_str() );
    result.result = QrCode::encodeSegments( segs, ecc, min_version, max_version,
                                            mask, true );
    return result;
}

} // namespace util
