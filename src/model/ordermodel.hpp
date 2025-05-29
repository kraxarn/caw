#pragma once

#include <QAbstractItemModel>
#include <QList>
#include <QVarLengthArray>

class OrderModel final: public QAbstractItemModel
{
	Q_OBJECT

public:
	explicit OrderModel(QObject *parent);

	void addRow();

	[[nodiscard]]
	auto index(int row, int column, const QModelIndex &parent) const -> QModelIndex override;

	[[nodiscard]]
	auto parent(const QModelIndex &child) const -> QModelIndex override;

	[[nodiscard]]
	auto rowCount(const QModelIndex &parent) const -> int override;

	[[nodiscard]]
	auto columnCount(const QModelIndex &parent) const -> int override;

	[[nodiscard]]
	auto data(const QModelIndex &index, int role) const -> QVariant override;

private:
	static constexpr qsizetype channelCount = 8; // TBD

	QList<QVarLengthArray<quint8, channelCount>> rows;
};
