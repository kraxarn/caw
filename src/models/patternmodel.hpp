#pragma once

#include "synth/note.hpp"

#include <QAbstractItemModel>
#include <QList>

class PatternModel final: public QAbstractItemModel
{
	Q_OBJECT

public:
	PatternModel(quint8 channelCount, QObject *parent);

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

	[[nodiscard]]
	auto headerData(int section, Qt::Orientation orientation, int role) const -> QVariant override;

private:
	static constexpr quint8 patternLength = 32;

	quint8 channelCount;

	QList<QList<Note>> rows;
};
