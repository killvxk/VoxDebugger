#ifndef MODULETAB_H
#define MODULETAB_H

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

class ModuleTab : public QWidget
{
	Q_OBJECT

public:
	ModuleTab(QWidget *parent, char* name);
	~ModuleTab();

public:
	QGridLayout* gridLayout;
	QTableView* tableView;
signals:
	void doubleClickEntry(int idx);
private slots:
	void OnDoubleClickEntry(const QModelIndex& idx);
};

#endif // MODULETAB_H
