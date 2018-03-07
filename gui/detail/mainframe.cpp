#include "mainframe.h"

#include <QAction>
#include <QPainter>
#include <QMenu>
#include <QLabel>

#include "gui/detail/QrWrapper.h"
#include "ui_mainframe.h"

MainFrame::MainFrame( QWidget *parent ) :
    QMainWindow( parent ), m_mode(TEXT_MODE),
    m_textMenu(NULL), m_qrMenu(NULL), m_ui( new Ui::MainFrame ) {
    m_ui->setupUi( this );
    init();
}

MainFrame::~MainFrame() {

}

void MainFrame::mousePressEvent(QMouseEvent *e) {
    if ( m_ui->m_textEdit->isHidden() ) {
        return;
    }
    m_ui->m_textEdit->hide();
    m_ui->m_menuBtn->setMenu( m_qrMenu );
}

void MainFrame::_generate() {
    util::QRSettings settings( m_ui->m_textEdit->toPlainText().toStdString() );
    settings.quality = util::QR_HIGH;
    settings.mask = util::Mask_Automatic;
    settings.min_version = 40;
    settings.max_version = 40;
    m_qrImg = gui::QrWrapper::generate( settings );
    m_qrImg = m_qrImg.scaledToWidth(m_ui->m_centralwidget->width());
    m_ui->m_imgLabel->setPixmap( QPixmap::fromImage( m_qrImg ) );
}

void MainFrame::_setOptions() {

}

void MainFrame::_showInfo() {

}

void MainFrame::_save() {

}

void MainFrame::_open() {

}

void MainFrame::_addLogo() {

}

void MainFrame::_edit() {
    if ( !m_ui->m_textEdit->isHidden() ) {
        return;
    }
    m_ui->m_textEdit->show();
    m_ui->m_menuBtn->setMenu( m_textMenu );
}

void MainFrame::init() {
    initTextMode();
    initQRMode();

    // signal
    connect( m_ui->m_textEdit, SIGNAL(textChanged()), this, SLOT(_generate()) );

    // attach toolbar
    m_ui->m_menuBtn->setMenu( m_textMenu );
}

void MainFrame::initTextMode() {
    if ( m_textMenu ) return;

    m_textMenu = new QMenu( this );
    m_textMenu->addAction( "Generate", this, SLOT(_generate()), QKeySequence("Ctrl+G") );
    m_textMenu->addAction( "QR Settings", this, SLOT(_setOptions()), QKeySequence("Ctrl+P") );
    m_textMenu->addAction( "Info", this, SLOT(_showInfo()), QKeySequence("Ctrl+I") );
    m_textMenu->addAction( "Save", this, SLOT(_save()), QKeySequence("Ctrl+S") );
    m_textMenu->addAction( "Open", this, SLOT(_open()), QKeySequence("Ctrl+O") );
}

void MainFrame::initQRMode() {
    if ( m_qrMenu ) return;

    m_qrMenu = new QMenu( this );
    m_qrMenu->addAction( "Save", this, SLOT(_save()), QKeySequence("Ctrl+S") );
    m_qrMenu->addAction( "Add logo", this, SLOT(_addLogo()), QKeySequence("Ctrl+L") );
    m_qrMenu->addAction( "Edit", this, SLOT(_edit()), QKeySequence("Ctrl+E") );
}
