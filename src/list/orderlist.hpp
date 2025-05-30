#pragma once

#include "model/ordermodel.hpp"

#include <QTreeView>

class OrderList final: public QTreeView
{
	Q_OBJECT

public:
	explicit OrderList(QWidget *parent);
};
