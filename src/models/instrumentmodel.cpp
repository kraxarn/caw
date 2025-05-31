#include "models/instrumentmodel.hpp"

InstrumentModel::InstrumentModel(QObject *parent)
	: QAbstractItemModel(parent)
{
}

auto InstrumentModel::index(const int row, const int column,
	[[maybe_unused]] const QModelIndex &parent) const -> QModelIndex
{
	return createIndex(row, column);
}

auto InstrumentModel::parent(const QModelIndex &child) const -> QModelIndex
{
	return {};
}

auto InstrumentModel::rowCount(const QModelIndex &parent) const -> int
{
	return 0;
}

auto InstrumentModel::columnCount(const QModelIndex &parent) const -> int
{
	return 0;
}

auto InstrumentModel::data(const QModelIndex &index, const int role) const -> QVariant
{
	if (role == Qt::DisplayRole)
	{
		return {};
	}

	return QString();
}

auto InstrumentModel::headerData(const int section, [[maybe_unused]] Qt::Orientation orientation,
	const int role) const -> QVariant
{
	if (role != Qt::DisplayRole)
	{
		return {};
	}

	return QStringLiteral("%1").arg(section);
}
