#pragma once

#include <QAbstractTableModel>
#include <QSqlTableModel>
#include <QSqlRecord>

class QuestionnaireBankModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit QuestionnaireBankModel(QSqlTableModel *sourceModel, QObject *parent = nullptr);
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
private:
    QSqlTableModel *m_sourceModel;
};
