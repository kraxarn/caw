#pragma once

#include "model/ordermodel.hpp"

#include <QTreeView>

class Order final: public QTreeView
{
	Q_OBJECT

public:
	explicit Order(QWidget *parent);
};
