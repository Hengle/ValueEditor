#pragma once

#pragma once

#include "BaseViewItem.h"
#include <QtGui/QLineEdit.h>
#include <QtGui/QVector3D.h>

class Vec3ViewItem : public BaseViewItem
{
	Q_OBJECT

private:

	// WE cache the value, and print it out.  This is so if this class is
	// used for something it should not be, it will at least be printed
	// out (and we can see what type it should be).
	QVector3D m_vec3dValue;

	// Cache widgets
	QWidget *m_widget;
	QLayout *m_layout;
	QLineEdit* m_xEdit;
	QLineEdit* m_yEdit;
	QLineEdit* m_zEdit;

	// Child routing
	ChildRouter *m_childRouters[3];

public:

	Vec3ViewItem(
		QString const &name,
	  QVariant const &value
	  );
	~Vec3ViewItem();

	virtual QWidget *getWidget() /*override*/;

	virtual void onModelValueChanged( QVariant const &value ) /*override*/;
	
	virtual void onChildViewValueChanged(
		int index,
		QVariant const &value,
		bool commit
		) /*override*/;

  virtual bool hasChildren() const { return true; }

  virtual QList<BaseViewItem *> createChildViewItems() const;

public slots:

	void onTextEditXChanged();
	void onTextEditYChanged();
	void onTextEditZChanged();
};
