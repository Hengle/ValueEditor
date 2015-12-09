#pragma once
#include <QTCore\QObject>
#include <QTCore\QVariant>

#include <vector>

// The base item for the view-side of the equation.
// A BaseViewItem essentially represents a row in the
// treeview.  The base class handles communicating with
// the core, and should be implemented to handle specific
// UI duties (ie, showing widgets, etc).  

class BaseViewItem :
	public QObject
{
	Q_OBJECT

	QString m_name;

public:
	BaseViewItem(QString name);
	~BaseViewItem(void);

	virtual size_t NumChildren() = 0;
	virtual BaseViewItem* GetChild(size_t index) = 0;

	virtual QWidget* BuildWidgets(bool expanded) = 0;

	const QString& GetName() { return m_name; }

	virtual QVariant GetValue() = 0;

public slots:

	// Implement this slot to update the UI when the
	// core value changes.
	virtual void UpdateValue(QVariant value) = 0;

signals:

	// When this items widgets change, it should emit this signal
	void ValueChanged(QVariant value, const QString& name);
};

