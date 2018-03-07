#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QMainWindow>
#include <QScopedPointer>

class QMenu;

namespace Ui {
class MainFrame;
}

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

private slots:
    void _generate();
    void _setOptions();
    void _showInfo();
    void _save();
    void _open();
    void _addLogo();
    void _edit();

private:
    void init();
    void initTextMode();
    void initQRMode();

private:
    DISPLAY_MODE m_mode;

    // data
    QImage m_qrImg;

    // ui
    QMenu *m_textMenu;
    QMenu *m_qrMenu;
    QScopedPointer<Ui::MainFrame> m_ui;
};

#endif // MAINFRAME_H
