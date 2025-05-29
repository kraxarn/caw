#include "model/ordermodel.hpp"

OrderModel::OrderModel(QObject *parent)
	: QAbstractItemModel(parent)
{
	addRow();
}

void OrderModel::addRow()
{
	rows.append({
		QVarLengthArray<quint8, channelCount>(channelCount, 0x00)
	});
}

auto OrderModel::index(const int row, const int column,
	[[maybe_unused]] const QModelIndex &parent) const -> QModelIndex
{
	return createIndex(row, column);
}

auto OrderModel::parent(const QModelIndex &child) const -> QModelIndex
{
	return {};
}

auto OrderModel::rowCount([[maybe_unused]] const QModelIndex &parent) const -> int
{
	if (parent.isValid())
	{
		return 0;
	}

	return static_cast<int>(rows.length());
}

auto OrderModel::columnCount([[maybe_unused]] const QModelIndex &parent) const -> int
{
	return channelCount;
}

auto OrderModel::data(const QModelIndex &index, const int role) const -> QVariant
{
	if (role != Qt::DisplayRole)
	{
		return {};
	}

	const quint8 val = rows.at(index.row()).at(index.column());
	return QStringLiteral("%1").arg(val, 2, 16, QChar::fromLatin1('0'));
}
