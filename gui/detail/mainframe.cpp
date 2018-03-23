#include "mainframe.h"

#include <QAction>
#include <QDockWidget>
#include <QFileDialog>
#include <QIcon>
#include <QLabel>
#include <QMenu>
#include <QMouseEvent>
#include <QPainter>
#include <QTextBrowser>

#include "gui/detail/QrWrapper.h"
#include "gui/detail/OptionPanel.h"
#include "ui_mainframe.h"

namespace gui {

MainFrame::MainFrame( QWidget *parent ) :
    QMainWindow( parent ), m_mode(TEXT_MODE),
    m_textMenu(NULL), m_qrMenu(NULL), m_optPanel(new OptionPanel(this)),
    m_infoDockWgt(new QDockWidget(this)), m_ui(new Ui::MainFrame), m_lbtnPress(false) {
    m_ui->setupUi( this );
    init();
}

MainFrame::~MainFrame() {

}

void MainFrame::mousePressEvent(QMouseEvent *e) {
    // movable widget
    if ( e->button() == Qt::LeftButton ) {
        m_pressPtr = e->globalPos();
        m_lbtnPress = true;
    }

    if ( m_ui->m_textEdit->isHidden() || m_qrImg.isNull() ) {
        return;
    }
    const QRect &area = m_ui->m_textEdit->geometry();
    if ( area.contains( e->pos() ) ) {
        return;
    }

    switchState( QR_MODE );
}

void MainFrame::mouseMoveEvent( QMouseEvent *e ) {
    if ( m_lbtnPress ) {
        setCursor (Qt::ClosedHandCursor );
        m_movePtr = e->globalPos();
        this->move( this->pos() + m_movePtr - m_pressPtr );
        m_pressPtr = m_movePtr;
    }
}

void MainFrame::mouseReleaseEvent(QMouseEvent *e) {
    if ( e->button() == Qt::LeftButton ) {
        m_lbtnPress = false;
        setCursor( Qt::ArrowCursor );
    }
}

void MainFrame::_onEditorTextChanged() {
    if ( m_ui->m_textEdit->toPlainText().isEmpty() ) {
        // disable actions
        m_generateAct->setDisabled( true );
        m_saveAct->setDisabled( true );

        // clear image
        m_qrImg = QImage();

        // restore image label
        m_ui->m_imgLabel->clear();
        return;
    }
    // enable actions
    m_generateAct->setEnabled( true );
    m_saveAct->setEnabled( true );
}

void MainFrame::_generate() {
    const QString &text = m_ui->m_textEdit->toPlainText();
    if ( text.isEmpty() ) return;
    util::QRSettings opt;
    if ( m_optPanel ) {
        opt = m_optPanel->getOptions();
    }
    opt.text = text.toStdString();
    m_qrImg = gui::QrWrapper::generate( opt );
    m_qrImg = m_qrImg.scaledToWidth(m_ui->m_centralwidget->width());

    if ( !m_logoImg.isNull() ) {
        m_qrImg = QrWrapper::addLogo( m_qrImg, m_logoImg );
    }
    m_ui->m_imgLabel->setPixmap( QPixmap::fromImage( m_qrImg ) );

    // switch condition
    QAction *action = qobject_cast<QAction *>(sender());
    if ( action && action->text() == "Generate" ) {
        m_ui->m_textEdit->hide();
        switchState( QR_MODE );
    }
}

void MainFrame::_setOptions() {
    if ( !m_optPanel ) return;
    m_optPanel->show();
}

void MainFrame::_showInfo() {
    if ( !m_optPanel ) return;
    QTextBrowser *browser = qobject_cast<QTextBrowser *>(m_infoDockWgt->widget());
    if ( !browser ) return;

    QString info = QString( "Input: \n" );
    info += "\t" + m_ui->m_textEdit->toPlainText() + "\n";

    if ( m_optPanel ) {
        info += m_optPanel->getOptString();
    }

    browser->setText( info );
    m_infoDockWgt->show();
}

void MainFrame::_save() {
    if ( m_qrImg.isNull() ) return;

    const QString &output = QFileDialog::getSaveFileName( this, "Save QR...", "", "Images (*.png *.xpm *.jpg)" );
    if ( output.isEmpty() ) return;

    if ( !m_logoImg.isNull() ) {
        QImage imgWithLogo = QrWrapper::addLogo( m_qrImg, m_logoImg );
        imgWithLogo.save( output );
    } else {
        m_qrImg.save( output );
    }
}

void MainFrame::_addLogo() {
    if ( m_qrImg.isNull() ) return;
    const QString &logo_path = QFileDialog::getOpenFileName( this, "Select Logo", "/home",
                                                             "Images (*.png *.xpm *.jpg)" );
    if ( logo_path.isEmpty() ) return;
    m_logoImg =  QImage( logo_path );

    QImage imgWithLogo = QrWrapper::addLogo( m_qrImg, m_logoImg );
    if ( imgWithLogo.isNull() ) return;

    m_ui->m_imgLabel->setPixmap( QPixmap::fromImage( imgWithLogo ) );
    m_clearLogoAct->setEnabled( true );
}

void MainFrame::_clearLogo() {
    m_logoImg = QImage();
    m_clearLogoAct->setDisabled( true );
    _generate();
}

void MainFrame::_edit() {
    if ( !m_ui->m_textEdit->isHidden() ) {
        return;
    }
    switchState( TEXT_MODE );
}

void MainFrame::init() {
    initActions();
    initTextMode();
    initQRMode();

    // info widget
    initInfoWgt();

    // signal
    connect( m_ui->m_textEdit, SIGNAL(textChanged()), this, SLOT(_onEditorTextChanged()) );
    connect( m_ui->m_textEdit, SIGNAL(textChanged()), this, SLOT(_generate()) );
    connect( m_ui->m_editBtn, SIGNAL(clicked()), this, SLOT(_edit()) );
    connect( m_ui->m_exitBtn, SIGNAL(clicked()), this, SLOT(close()) );
    connect( m_ui->m_miniBtn, SIGNAL(clicked()), this, SLOT(showMinimized()) );

    if ( m_optPanel ) {
        connect( m_optPanel, SIGNAL(optionChanged()), this, SLOT(_generate()) );
    }

    // attach toolbar
    switchState( TEXT_MODE );
    setWindowFlags( Qt::FramelessWindowHint );
}

QAction *createAction( const QString &act_name, QWidget *parent = NULL,
                       const QString &shortcut = QString(),
                       const QIcon &icon = QIcon() ) {
    QAction *action = new QAction( icon, act_name, parent );
    if ( !shortcut.isEmpty() ) {
        action->setShortcut( QKeySequence( shortcut ) );
    }
    action->setShortcutContext( Qt::WindowShortcut );
    return action;
}

void MainFrame::initActions() {
    m_generateAct = createAction( "Generate", this, "Ctrl+G", QIcon( ":/icon/icons/play.png" ) );
    m_optAct = createAction( "QR Settings", this, "Ctrl+P", QIcon( ":/icon/icons/settings.png" ) );
    m_infoAct = createAction( "QR Info", this, "Ctrl+I", QIcon( ":/icon/icons/information.png" ) );
    m_saveAct = createAction( "Save QR", this, "Ctrl+S", QIcon( ":/icon/icons/save.png" ) );
    m_addLogoAct = createAction( "Add Logo", this, "Ctrl+L", QIcon( ":/icon/icons/add.png" ) );
    m_clearLogoAct = createAction( "Clear Logo", this, "Shift+Ctrl+L",
                                   QIcon(":/icon/icons/eraser.png") );

    m_generateAct->setDisabled( true );
    m_saveAct->setDisabled( true );
    m_clearLogoAct->setDisabled( true );

    connect( m_generateAct, SIGNAL(triggered()), this, SLOT(_generate()) );
    connect( m_optAct, SIGNAL(triggered()), this, SLOT(_setOptions()) );
    connect( m_infoAct, SIGNAL(triggered()), this, SLOT(_showInfo()) );
    connect( m_saveAct, SIGNAL(triggered()), this, SLOT(_save()) );
    connect( m_addLogoAct, SIGNAL(triggered()), this, SLOT(_addLogo()) );
    connect( m_clearLogoAct, SIGNAL(triggered()), this, SLOT(_clearLogo()) );
}

void MainFrame::initTextMode() {
    if ( m_textMenu ) return;

    m_textMenu = new QMenu( this );
    m_textMenu->addAction( m_generateAct );
    m_textMenu->addAction( m_optAct );
    m_textMenu->addSeparator();
    m_textMenu->addAction( m_infoAct );
    m_textMenu->addAction( m_saveAct );
}

void MainFrame::initQRMode() {
    if ( m_qrMenu ) return;

    m_qrMenu = new QMenu( this );
    m_qrMenu->addAction( m_addLogoAct );
    m_qrMenu->addAction( m_clearLogoAct );
    m_qrMenu->addSeparator();
    m_qrMenu->addAction( m_infoAct );
    m_qrMenu->addAction( m_saveAct );
}

void MainFrame::initInfoWgt() {
    QTextBrowser *browser = new QTextBrowser(m_infoDockWgt);
    m_infoDockWgt->setWidget( browser );
    m_infoDockWgt->setFeatures( QDockWidget::DockWidgetClosable );
    addDockWidget( Qt::BottomDockWidgetArea, m_infoDockWgt );
    m_infoDockWgt->hide();
    m_infoDockWgt->setMaximumHeight( 150 );
}

void MainFrame::switchState(MainFrame::DISPLAY_MODE mode) {
    if ( mode == QR_MODE ) {
        m_ui->m_textEdit->hide();
        m_ui->m_editBtn->show();
        m_ui->m_menuBtn->setMenu( m_qrMenu );
        this->setFocus();
    } else {
        m_ui->m_textEdit->show();
        m_ui->m_textEdit->setFocus();
        m_ui->m_editBtn->hide();
        m_ui->m_menuBtn->setMenu( m_textMenu );
    }
}

}  // namespace gui
