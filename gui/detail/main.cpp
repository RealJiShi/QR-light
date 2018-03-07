#include <QApplication>
#include "mainframe.h"

int main( int argc, char **argv ) {
    QApplication app( argc, argv );
    MainFrame main_frame;
    main_frame.show();
    return app.exec();
}

//#include <cstdint>
//#include <cstdlib>
//#include <cstring>
//#include <iostream>
//#include <string>
//#include <vector>
//#include <QImage>
//#include <QColor>
//#include "util/BitBuffer.hpp"
//#include "util/QrCode.hpp"
//#include "util/QrSegment.hpp"

//using std::uint8_t;
//using qrcodegen::QrCode;
//using qrcodegen::QrSegment;

//// Function prototypes
//static void doBasicDemo();
//static void printImage(const QrCode &qr);


//// The main application program.
//int main() {
//    doBasicDemo();
//    return EXIT_SUCCESS;
//}

///*---- Demo suite ----*/
//// Creates a single QR Code, then prints it to the console.
//static void doBasicDemo() {
//    const char *text = "Hello, world!";  // User-supplied text
//    const QrCode::Ecc errCorLvl = QrCode::Ecc::LOW;  // Error correction level

//    // Make and print the QR Code symbol
//    const QrCode qr = QrCode::encodeText(text, errCorLvl);
//    printImage(qr);
//    std::cout << qr.toSvgString(4) << std::endl;
//}

//static void printImage(const QrCode &qr) {
//    int border = 0;
//    QImage img( qr.getSize() + 2 * border, qr.getSize() + 2 * border, QImage::Format_RGB888 );
//    for ( int y = -border; y < qr.getSize() + border; ++y ) {
//        for ( int x = -border; x < qr.getSize() + border; ++x ) {
//            img.setPixel( x + border, y + border, qr.getModule(x, y) ? qRgb(0, 0, 0) : qRgb(255, 255, 255) );
//        }
//    }
//    img = img.scaledToWidth(400);
//    img.save( "img.png" );
//}
