// SampleApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <ViewItemFactory.h>
//#include "..\..\DefaultViewItem.h"
//#include "..\..\FloatViewItemCreator.h"
//#include "..\..\RTValViewItemCreator.h"
//#include "..\..\Vec3ViewItemCreator.h"
#include "SampleModel.h"
#include <VETreeWidget.h>

static QTime myTimer;
void SetStylesheet(const char* filename)
{
	QFile File(filename);
	File.open(QFile::ReadOnly);
	QString StyleSheet = QLatin1String(File.readAll());

	qApp->setStyleSheet(StyleSheet);
}

class MainWindow : public QMainWindow
{
  typedef QMainWindow Super;

public:

	MainWindow( BaseViewItem *rootViewItem )
	{
		VETreeWidget *treeWidget = new VETreeWidget( rootViewItem );

		setCentralWidget( treeWidget );
	}

	virtual void showEvent(QShowEvent *ev) /*override*/
	{
		Super::showEvent(ev);
		int elapsed = myTimer.elapsed();
		printf("elapsed: %i\n", elapsed);
	}
};

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SetStylesheet("styles.qss");

  // We create a FabricInstance in order to test
  FabricCore::Initialize();

  FabricCore::Client::CreateOptions createOptions;
  memset( &createOptions, 0, sizeof( createOptions ) );
  createOptions.guarded = true;

  FabricCore::Client client( NULL, NULL, &createOptions );

	BaseModelItem* pSampleModel = BuildSampleModel( client );
	
	ViewItemFactory* pFactory = ViewItemFactory::GetInstance();
	BaseViewItem* pViewLayer = pFactory->BuildView(pSampleModel);


	myTimer.start();
	MainWindow w(pViewLayer);

	// Now everything is connected up, try modifying a model value
	BaseModelItem* pAModel = pSampleModel->GetChild(1);
	SampleModelItem* pFloatModel = dynamic_cast<SampleModelItem*>(pAModel);
	if (pFloatModel)
	{
		QVariant anotherValue(45.43f);
		pFloatModel->SetValueDirect(anotherValue);
	}
	w.show();
	return a.exec();
}
