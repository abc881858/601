#include "questionnairebankmodel.h"

QuestionnaireBankModel::QuestionnaireBankModel(QSqlTableModel *sourceModel, QObject *parent)
    : QAbstractTableModel(parent), m_sourceModel(sourceModel)
{
}

QVariant QuestionnaireBankModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
    {
        return {};
    }
    if (orientation == Qt::Horizontal)
    {
        switch (section) {
        case 0: return "序号";
        case 1: return "类型";
        case 2: return "题干";
        case 3: return "指标";
        case 4: return "题目打分人数";
        case 5: return "题目平均分";
        }
    }
    return QAbstractTableModel::headerData(section, orientation, role);
}

int QuestionnaireBankModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return 0;
    }
    return m_sourceModel->rowCount();
}

int QuestionnaireBankModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return 0;
    }
    return 6;
}

QVariant QuestionnaireBankModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) return {};

    int row = index.row();
    int col = index.column();

    switch (col) {
    case 0: // 第一列：questionbank的第一列
        return m_sourceModel->record(row).value(0);
    case 1: { // 第二列：根据questionbank的第二列映射显示
        int typeValue = m_sourceModel->record(row).value(1).toInt();
        switch (typeValue) {
        case 1: return "打分题";
        case 2: return "选择题";
        case 3: return "主观题";
        }
    }
    case 2: { // 题干
        int typeValue = m_sourceModel->record(row).value(1).toInt();
        switch (typeValue) {
        case 1: return m_sourceModel->record(row).value(2).toString();
        case 2: return m_sourceModel->record(row).value(3).toString();
        case 3: return m_sourceModel->record(row).value(4).toString();
        }
    }
    case 3: { // 指标
        return m_sourceModel->record(row).value(5).toString();
    }
    case 4: { // 题目打分人数
        return m_sourceModel->record(row).value(6).toInt();
    }
    case 5: { // 题目平均分
        return m_sourceModel->record(row).value(7).toInt();
    }
    }
    return {};
}
