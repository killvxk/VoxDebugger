#ifndef CPUTAB_H
#define CPUTAB_H

#include <QWidget>
#include <QtGui/qlistview.h>
#include <QtGui/QTableView.h>
#include <QtGui/QGridLayout>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <qstandarditemmodel.h>
#include <QtGui/qheaderview.h>
#include <QtGui/qtabwidget.h>
#include "Dbg.h"

class CPUTab : public QWidget
{
	Q_OBJECT

public:
	CPUTab(QWidget *parent, char* name);
	~CPUTab();

	QGridLayout* gridLayout;
	QTableView* tableView;
	QStandardItemModel *model;
	
};

#endif // CPUTAB_H
