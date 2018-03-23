#ifndef OPTIONPANEL_H
#define OPTIONPANEL_H

#include <QDialog>
#include <QScopedPointer>
#include "util/qrutil.h"

namespace Ui {
class OptionPanel;
}

namespace gui {

class OptionPanel : public QDialog
{
    Q_OBJECT
public:
    OptionPanel( QWidget *parent = 0 );
    ~OptionPanel();

    // get QR generating options
    util::QRSettings getOptions() const;
    QString getOptString() const;

private slots:
    void onMinVersionChanged();
    void onMaxVersionChanged();

signals:
    void optionChanged();

private:
    QScopedPointer<Ui::OptionPanel> m_ui;
};

}

#endif // OPTIONPANEL_H
