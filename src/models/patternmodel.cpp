#include "models/patternmodel.hpp"
#include "format.hpp"

PatternModel::PatternModel(const quint8 channelCount, QObject *parent)
	: QAbstractItemModel(parent),
	channelCount(channelCount)
{
	for (quint8 i = 0; i < patternLength; i++)
	{
		rows.append(QList<Note>(channelCount, Note()));
	}
}

auto PatternModel::index(const int row, const int column,
	[[maybe_unused]] const QModelIndex &parent) const -> QModelIndex
{
	return createIndex(row, column);
}

auto PatternModel::parent([[maybe_unused]] const QModelIndex &child) const -> QModelIndex
{
	return {};
}

auto PatternModel::rowCount(const QModelIndex &parent) const -> int
{
	if (parent.isValid())
	{
		return 0;
	}

	return static_cast<int>(rows.length());
}

auto PatternModel::columnCount(const QModelIndex &parent) const -> int
{
	return channelCount + 1;
}

auto PatternModel::data(const QModelIndex &index, const int role) const -> QVariant
{
	if (role != Qt::DisplayRole)
	{
		return {};
	}

	if (index.column() == 0)
	{
		return Format::hex(index.row());
	}

	const Note &note = rows.at(index.row()).at(index.column() - 1);
	return QStringLiteral("......"); // TODO
}

auto PatternModel::headerData(const int section, [[maybe_unused]] Qt::Orientation orientation,
	const int role) const -> QVariant
{
	if (role != Qt::DisplayRole || section == 0)
	{
		return {};
	}

	return QStringLiteral("Ch. %1").arg(section);
}
