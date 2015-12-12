// SampleApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

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
public:
	MainWindow()
	{
		//QTreeWidget *treeWidget = new QTreeWidget;

		//QStringList fileNames;
		//fileNames << s1 << s2 << s3 << s4 << s5 << s6;

		//QTreeWidgetItem *topLevelItem = NULL;
		//foreach(const QString &fileName, fileNames)
		//{
		//	QStringList splitFileName = fileName.split("/");

		//	// add root folder as top level item if treeWidget doesn't already have it
		//	if (treeWidget->findItems(splitFileName[0], Qt::MatchFixedString).isEmpty())
		//	{
		//		topLevelItem = new QTreeWidgetItem;
		//		topLevelItem->setText(0, splitFileName[0]);
		//		treeWidget->addTopLevelItem(topLevelItem);
		//	}

		//	QTreeWidgetItem *parentItem = topLevelItem;

		//	// iterate through non-root directories (file name comes after)
		//	for (int i = 1; i < splitFileName.size() - 1; ++i)
		//	{
		//		// iterate through children of parentItem to see if this directory exists
		//		bool thisDirectoryExists = false;
		//		for (int j = 0; j < parentItem->childCount(); ++j)
		//		{
		//			if (splitFileName[i] == parentItem->child(j)->text(0))
		//			{
		//				thisDirectoryExists = true;
		//				parentItem = parentItem->child(j);
		//				break;
		//			}
		//		}

		//		if (!thisDirectoryExists)
		//		{
		//			parentItem = new QTreeWidgetItem(parentItem);
		//			parentItem->setText(0, splitFileName[i]);
		//		}
		//	}

		//	QTreeWidgetItem *childItem = new QTreeWidgetItem(parentItem);
		//	childItem->setText(0, splitFileName.last());
		//}
		//setCentralWidget(treeWidget);

		QTreeWidget* tree = new QTreeWidget;
		tree->setColumnCount(2);

		for (int i = 0; i < 1000; ++i) {
			QTreeWidgetItem* item = new QTreeWidgetItem;
			item->setText(0, QString::number(i));
			tree->addTopLevelItem(item);

			//create a layout with parent
			QWidget* w = new QWidget;
			QHBoxLayout *layout = new QHBoxLayout(w);
			//widgets that will be contained in QWidget
			QLabel* label1 = new QLabel("Label 1");
			QLabel* label2 = new QLabel("Label 2");
			layout->addWidget(label1); //add contained widgets to layout
			layout->addWidget(label2);
			layout->addWidget(new QSpinBox());


			tree->setItemWidget(item, 1, w);


		}
		setCentralWidget(tree);
	}

	virtual void showEvent(QShowEvent *ev) override
	{
		__super::showEvent(ev);
		int elapsed = myTimer.elapsed();
		printf("elapsed: %i", elapsed);
	}


};

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SetStylesheet("styles.qss");
	myTimer.start();
	MainWindow w;
	w.show();
	return a.exec();
}