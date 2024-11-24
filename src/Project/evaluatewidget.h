#pragma once

#include <QWidget>

namespace Ui {
class EvaluateWidget;
}

class EvaluateWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EvaluateWidget(QWidget *parent = nullptr);
    ~EvaluateWidget();
private:
    Ui::EvaluateWidget *ui;
private slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_detail_clicked();
    void on_export_word_clicked();
    void on_export_pdf_clicked();
    void on_analyze_clicked();
    void on_subjective_return_clicked();
};
