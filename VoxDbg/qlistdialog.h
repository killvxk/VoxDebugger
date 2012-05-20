#ifndef QLISTDIALOG_H
#define QLISTDIALOG_H

#include <QDialog>
#include <QtGui/qlistview.h>
#include <QtGui/QTableView.h>
#include <QtGui/QGridLayout>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <qstandarditemmodel.h>
#include <QtGui/qheaderview.h>

class QListDialog : public QDialog
{
	Q_OBJECT

public:
	QListDialog(QWidget *parent, char* title, QStandardItemModel *model);
	~QListDialog();

public:
	QTableView* tableView;
	QGridLayout* gridLayout;
	QSpacerItem* spacerItem;
	QPushButton* selectBtn;
	QPushButton* cancelBtn;
	int curSel;
	private slots:
	void Cancel();
	void Select();
	void OnSelectChange(const QModelIndex& idx);
	void OnDoubleClick(const QModelIndex& idx);
};

#endif // QLISTDIALOG_H
