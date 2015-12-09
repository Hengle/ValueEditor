#pragma once
#include <QtGui\QApplication>
#include <QtCore\QAbstractTableModel>
#include <QtGui\QTreeView>
#include <QtGui\QPainter>
#include <QtGui\QMouseEvent>
#include <QtCore\QtDebug>

// simple flat model
class Model : public QAbstractTableModel {
	Q_OBJECT
public:
	enum Roles {
		ConnectedRole = Qt::UserRole + 1
	};

	Model(QObject *parent = 0) : QAbstractTableModel(parent) {}

	int rowCount(const QModelIndex &parent = QModelIndex()) const {
		if (parent.isValid()) return 0;
		return m_keys.size();
	}
	int columnCount(const QModelIndex &parent = QModelIndex()) const {
		return 2;
	}
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const {
		if (!index.isValid()) return QVariant();
		if (index.column() == 0) {
			if (role == Qt::DisplayRole || role == Qt::EditRole) return m_keys.at(index.row());
		}
		if (index.column() == 1) {
			switch (role) {
			case Qt::DisplayRole:
			case Qt::EditRole: return m_values.at(index.row());
			case ConnectedRole: return m_connected.at(index.row());
			default:
				return QVariant();
			}
		}
		return QVariant();
	}
	bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) {
		if (index.column() != 1) return false;
		if (role == ConnectedRole) {
			if (m_connected[index.row()] == value.toBool()) return false;
			m_connected[index.row()] = value.toBool();
			emit dataChanged(index, index);
			return true;
		}
		if (role == Qt::EditRole) {
			m_values[index.row()] = value;
			emit dataChanged(index, index);
			return true;
		}
		return false;
	}

	void appendRow(const QString &key, const QVariant &value, bool conn = false) {
		beginInsertRows(QModelIndex(), m_keys.size(), m_keys.size());
		m_keys << key;
		m_values << value;
		m_connected << conn;
		endInsertRows();
	}

private:
	QStringList m_keys; // store keys
	QVariantList m_values; // store values
	QList<bool> m_connected; // store info about which item is "connected" (whatever that would mean)
};

class Delegate : public QAbstractItemDelegate {
public:
	Delegate(QObject *parent = 0) : QAbstractItemDelegate(parent) {}
	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
	{
		paintConnected(painter, option, index); // every item has a "connected" value, let's paint it

		switch (type(index)) {
		case QVariant::Bool: drawBoolValue(painter, option, index); break;
		case QVariant::Double: drawDoubleValue(painter, option, index); break;
		default: break;
		}

	}
	QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
	{
		return QSize(0, 20);
	}
	bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
	{
		// bools are handled in MouseRelease, dragging has to be handled in MouseMove
		if (event->type() == QEvent::MouseButtonRelease) {
			QMouseEvent *me = static_cast<QMouseEvent*>(event);
			if (checkAndHandleConnected(me, model, option, index)) return true;
			switch (type(index)) {
			case QVariant::Bool: checkAndHandleBoolValue(me, model, option, index); break;
			default: break;
			}
			return true;
		}
		if (event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseMove) {
			QMouseEvent *me = static_cast<QMouseEvent*>(event);
			switch (type(index)) {
			case QVariant::Double: if (checkAndHandleDoubleValue(me, model, option, index)) return true; break;
			default: break;
			}
			return false;
		}
		return QAbstractItemDelegate::editorEvent(event, model, option, index);
	}
protected:
	void paintConnected(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
		QRect connectedRect = QRect(option.rect.topLeft(), QSize(21, option.rect.height()));
		painter->fillRect(connectedRect, Qt::gray);
		// if connected, draw a white circle
		if (index.data(Model::ConnectedRole).toBool()) {
			painter->save();
			painter->setRenderHint(QPainter::Antialiasing);
			painter->setPen(Qt::NoPen);
			painter->setBrush(Qt::white);
			painter->drawEllipse(connectedRect.center(), 3, 3);
			painter->restore();
		}
	}
	bool checkAndHandleConnected(QMouseEvent *me, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) {
		QRect connectedRect = QRect(option.rect.topLeft(), QSize(21, option.rect.height()));
		if (connectedRect.contains(me->pos())) {
			model->setData(index, !index.data(Model::ConnectedRole).toBool(), Model::ConnectedRole);
			return true;
		}
		return false;
	}
	void drawBoolValue(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
		QRect boolRect = QRect(option.rect.topLeft(), QSize(21, option.rect.height())).translated(21, 0);
		painter->fillRect(boolRect, Qt::darkGray);
		if (index.data(Qt::EditRole).toBool()) {
			QRect crossRect = QRect(boolRect.center() - QPoint(4, 4), boolRect.center() + QPoint(5, 5));
			painter->save();
			painter->setRenderHint(QPainter::Antialiasing);
			QPen p;
			p.setWidth(2);
			p.setColor(Qt::white);
			painter->setPen(p);
			painter->drawLine(crossRect.topLeft(), crossRect.bottomRight());
			painter->drawLine(crossRect.topRight(), crossRect.bottomLeft());
			painter->restore();
		}
	}
	bool checkAndHandleBoolValue(QMouseEvent *me, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) {
		QRect boolRect = QRect(option.rect.topLeft(), QSize(21, option.rect.height())).translated(21, 0);
		if (boolRect.contains(me->pos())) {
			model->setData(index, !index.data(Qt::EditRole).toBool(), Qt::EditRole);
			return true;
		}
		return false;
	}

	void drawDoubleValue(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
		// paint the background first
		QRect doubleRect = option.rect.adjusted(21, 0, 0, 0);
		painter->fillRect(doubleRect, Qt::darkGray);
		// consists of a "slider" and the value itself

		// let the slider be of constant width of 50 (for simplicity)
		QRect sliderRect = doubleRect;
		sliderRect.setWidth(50);
		sliderRect.adjust(0, 0, 0, -1);
		painter->save();
		QPen p;
		p.setWidth(1);
		p.setColor(Qt::black);
		painter->setPen(p);
		painter->setBrush(Qt::gray);
		painter->drawRect(sliderRect);
		// I don't know the logic, so I'll assume the value to be between 0 and 1
		double val = index.data(Qt::EditRole).toDouble();
		QRect valueRect = sliderRect.adjusted(1, 1, -1, -1);
		// 2/48 = val/widthToPaint => widthToPaint = val * 48 / 2
		double widthToPaint = val * 24.0;
		valueRect.setWidth(widthToPaint);
		painter->fillRect(valueRect, Qt::lightGray);
		painter->restore();
		// paint the value text with precision 6, right adjusted
		painter->setPen(Qt::white);
		QRect textRect = doubleRect;
		textRect.setLeft(sliderRect.right() + 1);
		// leave some margin
		textRect.adjust(1, 1, -1, -1);
		painter->drawText(textRect, Qt::AlignRight | Qt::AlignVCenter, QString::number(val, 'f', 6));
	}
	bool checkAndHandleDoubleValue(QMouseEvent *me, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) {
		QRect doubleRect = option.rect.adjusted(21, 0, 0, 0);
		QRect sliderRect = doubleRect;
		sliderRect.setWidth(50);
		sliderRect.adjust(1, 1, 1, -2);
		if (!sliderRect.contains(me->pos())) return false;
		// we've hit the slider
		int width = me->pos().x() - sliderRect.left();
		// 2/48 = val/width => val = 2*width/48
		double val = 2 * width / 48.0;
		model->setData(index, val, Qt::EditRole);
		return true;
	}


	Model *model(const QModelIndex &index) const {
		return const_cast<Model*>(qobject_cast<const Model*>(index.model()));
	}
	QVariant::Type type(const QModelIndex &index) const {
		return index.data(Qt::DisplayRole).type();
	}
};