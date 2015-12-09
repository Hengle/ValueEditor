//#include "main.h"
//
//#include "moc_main.cpp"
//
//int main(int argc, char *argv[])
//{
//	QApplication a(argc, argv);
//	QTreeView w;
//	Model m;
//	m.appendRow("x", 1.0);
//	m.appendRow("y", 1.0);
//	m.appendRow("z", 1.0);
//	m.appendRow("Selectability", true, true);
//
//	w.setModel(&m);
//	w.setItemDelegateForColumn(1, new Delegate(&w));
//	w.show();
//
//	return a.exec();
//}

#include <QtGui/QtGui>
#include <QtGui/QFileDialog>

const QString s1 = "Docs/Testing/textFile1.txt";
const QString s2 = "Docs/Testing/textFile2.txt";
const QString s3 = "Docs/Testing/textFile3.txt";
const QString s4 = "Docs/Testing/AnotherFolder/textFile4.txt";
const QString s5 = "ThisIsGonnaBeCrazy/WholeNewFolder/AndAnother/file.pdf";
const QString s6 = "ThisIsGonnaBeCrazy/file.doc";

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

		for (int i = 0; i < 2000; ++i) {
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
};

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}