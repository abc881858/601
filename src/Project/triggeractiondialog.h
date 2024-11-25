#pragma once

#include <QDialog>
#include <QTreeWidgetItem>

namespace Ui {
class TriggerActionDialog;
}

class TriggerActionDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TriggerActionDialog(QWidget *parent = nullptr);
    ~TriggerActionDialog();
    QString result_name();
    int result_id();
    void selectItemByButtonId(int buttonId);
    QString name_from_id(int targetButtonId);
    void selectItemByPath(const QString &path);
private:
    Ui::TriggerActionDialog *ui;
    QString m_result_name;
    int m_result_id{0};
public slots:
    void handleItemChanged(QTreeWidgetItem *item, int column);
private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
};
