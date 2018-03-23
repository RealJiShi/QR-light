#include <QApplication>
#include <QFile>
#include "mainframe.h"


int main( int argc, char **argv ) {
    QApplication app( argc, argv );

    // for QSS style sheet
    QFile qss( ":/style/style.qss" );
    qss.open( QFile::ReadOnly );
    qApp->setStyleSheet( qss.readAll() );

    gui::MainFrame main_frame;
    main_frame.show();

    return app.exec();
}
