#pragma once

#include "BaseViewItem.h"
#include "QVariantRTVal.h"

class RTValViewItem : public BaseViewItem
{
	Q_OBJECT

	// Cache the val for easier reconstruction.  Why?  cause why not?
	FabricCore::RTVal m_val; 

	std::vector<BaseViewItem*> m_children;

	QWidget* m_parentWidget;

	FabricCore::Client m_client;

public:
	RTValViewItem(QString name);
	~RTValViewItem();

	virtual size_t NumChildren() override;

	virtual BaseViewItem* GetChild(size_t index) override;

	virtual QWidget* BuildWidgets(bool expanded) override;

	virtual void UpdateViewValue(QVariant value) override;

	virtual QVariant GetValue() override;

	// Stuff...
	void AddChild(BaseViewItem* pChild);

public slots:
	void OnChildChanged(QVariant value, QString name);
};