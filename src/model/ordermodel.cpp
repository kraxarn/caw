#include "model/ordermodel.hpp"

#include <QAbstractItemModel>
#include <QObject>
#include <QString>
#include <QtTypes>
#include <QVariant>
#include <QVarLengthArray>

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

auto OrderModel::parent([[maybe_unused]] const QModelIndex &child) const -> QModelIndex
{
	return {};
}

auto OrderModel::rowCount(const QModelIndex &parent) const -> int
{
	if (parent.isValid())
	{
		return 0;
	}

	return static_cast<int>(rows.length());
}

auto OrderModel::columnCount([[maybe_unused]] const QModelIndex &parent) const -> int
{
	return channelCount + 1;
}

auto OrderModel::data(const QModelIndex &index, const int role) const -> QVariant
{
	if (role != Qt::DisplayRole)
	{
		return {};
	}

	quint8 value;

	if (index.column() == 0)
	{
		value = static_cast<quint8>(index.row());
	}
	else
	{
		value = rows.at(index.row()).at(index.column() - 1);
	}

	return QStringLiteral("%1").arg(value, 2, 16, QChar::fromLatin1('0'));
}

auto OrderModel::headerData(const int section, [[maybe_unused]] Qt::Orientation orientation,
	const int role) const -> QVariant
{
	if (role != Qt::DisplayRole)
	{
		return {};
	}

	if (section == 0)
	{
		return {};
	}

	return QStringLiteral("C%1").arg(section);
}
