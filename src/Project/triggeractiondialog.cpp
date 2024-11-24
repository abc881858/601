#include "triggeractiondialog.h"
#include "ui_triggeractiondialog.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTreeWidgetItem>

// 递归函数：将 JSON 中的节点添加到 QTreeWidgetItem
void parseJsonToTree(const QJsonObject &jsonObject, QTreeWidgetItem *parentItem)
{
    // 创建当前节点
    QString name = jsonObject["name"].toString();
    int buttonId = jsonObject["buttonId"].toInt();
    parentItem->setText(0, name);
    parentItem->setCheckState(0, Qt::Unchecked);
    parentItem->setData(0, Qt::UserRole, buttonId);

    // 处理子节点
    if (jsonObject.contains("children"))
    {
        QJsonArray children = jsonObject["children"].toArray();
        for (const QJsonValue &childValue : children)
        {
            if (childValue.isObject())
            {
                QTreeWidgetItem *childItem = new QTreeWidgetItem();
                parseJsonToTree(childValue.toObject(), childItem);
                parentItem->addChild(childItem);
            }
        }
    }
}

TriggerActionDialog::TriggerActionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TriggerActionDialog)
{
    ui->setupUi(this);

    connect(ui->treeWidget, &QTreeWidget::itemChanged, this, &TriggerActionDialog::handleItemChanged);

    // 读取 JSON 文件
    QFile file("4.json");
    if (!file.open(QIODevice::ReadOnly))
    {
        qCritical() << "无法打开文件:" << file.errorString();
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    // 解析 JSON
    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
    if (!jsonDoc.isObject())
    {
        qCritical() << "JSON 格式错误";
        return;
    }

    QJsonObject rootObject = jsonDoc.object();
    if (rootObject.contains("buttons")) {
        QJsonArray buttons = rootObject["buttons"].toArray();
        for (const QJsonValue &buttonValue : buttons) {
            if (buttonValue.isObject()) {
                QTreeWidgetItem *buttonItem = new QTreeWidgetItem(ui->treeWidget);
                parseJsonToTree(buttonValue.toObject(), buttonItem);
            }
        }
    }
}

// 槽函数：处理叶子节点只能选中一个
void TriggerActionDialog::handleItemChanged(QTreeWidgetItem *item, int column)
{
    if (!item || column != 0 || item->checkState(0) != Qt::Checked) {
        return;
    }

    // 遍历整个树，取消所有其他项的选中状态
    QTreeWidgetItemIterator it(ui->treeWidget);
    while (*it)
    {
        QTreeWidgetItem *currentItem = *it;
        if (currentItem != item)
        {
            currentItem->setCheckState(0, Qt::Unchecked);
        }
        ++it;
    }
    m_result_id = item->data(0, Qt::UserRole).toInt();

    // 获取并打印当前节点及其所有父节点的 displayRole
    QStringList path;
    QTreeWidgetItem *currentItem = item;
    while (currentItem)
    {
        path.prepend(currentItem->text(0));  // 添加当前节点的文本到路径前面
        currentItem = currentItem->parent();  // 继续向上遍历父节点
    }
    m_result_name = path.join(" - ");

    // 输出选中节点的 `buttonId`
    qDebug() << "Selected node buttonId:" << m_result_id;

    // 打印选中节点的 'name'
    qDebug() << "Selected node name:" << m_result_name;
}

// 通过 buttonId 选中对应的节点
void TriggerActionDialog::selectItemByButtonId(int buttonId)
{
    QTreeWidgetItemIterator it(ui->treeWidget);
    while (*it) {
        QTreeWidgetItem *currentItem = *it;
        int currentButtonId = currentItem->data(0, Qt::UserRole).toInt();
        if (currentButtonId == buttonId) {
            currentItem->setCheckState(0, Qt::Checked);
            return;
        }
        ++it;
    }
    qDebug() << "No item found with buttonId:" << buttonId;
}

TriggerActionDialog::~TriggerActionDialog()
{
    delete ui;
}

QString TriggerActionDialog::result_name()
{
    return m_result_name;
}

int TriggerActionDialog::result_id()
{
    return m_result_id;
}

void TriggerActionDialog::on_buttonBox_accepted()
{
    accept();
}

void TriggerActionDialog::on_buttonBox_rejected()
{
    reject();
}
