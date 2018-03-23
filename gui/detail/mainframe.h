#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QMainWindow>
#include <QScopedPointer>

class QAction;
class QMenu;
class QTextBrowser;
class QDockWidget;

namespace Ui {
class MainFrame;
}

namespace gui {

class OptionPanel;
class MainFrame : public QMainWindow
{
    Q_OBJECT

    enum DISPLAY_MODE {
        TEXT_MODE,
        QR_MODE
    };

public:
    explicit MainFrame(QWidget *parent = 0);
    ~MainFrame();

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private slots:
    void _onEditorTextChanged();
    void _generate();
    void _setOptions();
    void _showInfo();
    void _save();
    void _addLogo();
    void _clearLogo();
    void _edit();

private:
    void init();
    void initActions();
    void initTextMode();
    void initQRMode();
    void initInfoWgt();
    void switchState(DISPLAY_MODE mode);

private:
    DISPLAY_MODE m_mode;

    // data
    QImage m_qrImg;
    QImage m_logoImg;

    // ui
    // menu
    QMenu *m_textMenu;
    QMenu *m_qrMenu;

    // action
    QAction *m_saveAct;
    QAction *m_addLogoAct;
    QAction *m_clearLogoAct;
    QAction *m_infoAct;
    QAction *m_generateAct;
    QAction *m_optAct;

    // widgets
    OptionPanel *m_optPanel;
    QDockWidget *m_infoDockWgt;
    QScopedPointer<Ui::MainFrame> m_ui;

    // mainwindow drag event
    bool m_lbtnPress;
    QPoint m_pressPtr;
    QPoint m_movePtr;
};

} // namespace gui

#endif // MAINFRAME_H
