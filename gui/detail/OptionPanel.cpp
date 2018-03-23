#include "OptionPanel.h"
#include "ui_OptionPanel.h"

namespace gui {

OptionPanel::OptionPanel(QWidget *parent) : QDialog(parent), m_ui(new Ui::OptionPanel) {
    m_ui->setupUi(this);
    this->setWindowFlags( windowFlags() & ~Qt::WindowContextHelpButtonHint );

    connect( m_ui->m_errorLowRB, SIGNAL(clicked()), this, SIGNAL(optionChanged()) );
    connect( m_ui->m_errorMidRB, SIGNAL(clicked()), this, SIGNAL(optionChanged()) );
    connect( m_ui->m_errorQuaRB, SIGNAL(clicked()), this, SIGNAL(optionChanged()) );
    connect( m_ui->m_errorHighRB, SIGNAL(clicked()), this, SIGNAL(optionChanged()) );
    connect( m_ui->m_minRangeSB, SIGNAL(valueChanged(int)), this, SIGNAL(optionChanged()) );
    connect( m_ui->m_maxRangeSB, SIGNAL(valueChanged(int)), this, SIGNAL(optionChanged()) );
    connect( m_ui->m_minRangeSB, SIGNAL(valueChanged(int)), this, SLOT(onMinVersionChanged()) );
    connect( m_ui->m_maxRangeSB, SIGNAL(valueChanged(int)), this, SLOT(onMaxVersionChanged()) );
    connect( m_ui->m_maskPatternSB, SIGNAL(valueChanged(int)), this, SIGNAL(optionChanged()) );
}

OptionPanel::~OptionPanel() {}

util::QRSettings OptionPanel::getOptions() const {
    util::QRSettings option;

    // get error correction
    if ( m_ui->m_errorLowRB->isChecked() ) {
        option.quality = util::QR_LOW;
    } else if ( m_ui->m_errorMidRB->isChecked() ) {
        option.quality = util::QR_MEDIUM;
    } else if ( m_ui->m_errorQuaRB->isChecked() ) {
        option.quality = util::QR_QUARTILE;
    } else if ( m_ui->m_errorHighRB->isChecked() ) {
        option.quality = util::QR_HIGH;
    }

    // get version range: min & max
    option.min_version = m_ui->m_minRangeSB->value();
    option.max_version = m_ui->m_maxRangeSB->value();

    // get mask pattern
    option.mask = static_cast<util::MaskLevel>(m_ui->m_maskPatternSB->value());

    return option;
}

QString OptionPanel::getOptString() const {
    QString summary;
    // get error correction
    summary += "Error Correction: \n";
    if ( m_ui->m_errorLowRB->isChecked() ) {
        summary += "\tLevel Low\n";
    } else if ( m_ui->m_errorMidRB->isChecked() ) {
        summary += "\tLevel Medium\n";
    } else if ( m_ui->m_errorQuaRB->isChecked() ) {
        summary += "\tLevel Quartile\n";
    } else if ( m_ui->m_errorHighRB->isChecked() ) {
        summary += "\tLevel High\n";
    }

    // get version range: min & max
    summary += "Version range: \n";
    summary += "\tMinimum range: " + QString::number(m_ui->m_minRangeSB->value()) + "\n";
    summary += "\tMaximum range: " + QString::number(m_ui->m_maxRangeSB->value()) + "\n";

    // get mask pattern
    summary += "Mask pattern: " + QString::number(m_ui->m_maskPatternSB->value()) + "\n";
    return summary;
}

void OptionPanel::onMinVersionChanged() {
    const int min_v = m_ui->m_minRangeSB->value();
    m_ui->m_maxRangeSB->setMinimum( min_v );
}

void OptionPanel::onMaxVersionChanged() {
    const int max_v = m_ui->m_maxRangeSB->value();
    m_ui->m_minRangeSB->setMaximum( max_v );
}

}
