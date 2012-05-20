#include "qlistdialog.h"

QListDialog::QListDialog(QWidget *parent, char* title, QStandardItemModel *model)
	: QDialog(parent)
{
	setFixedSize(500, 300);
	setModal(true);
	setWindowFlags(Qt::Drawer);
	setWindowTitle(title);
		
	gridLayout = new QGridLayout(this);

	tableView = new QTableView(this);
	tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	tableView->setModel(model);
	//Set so you can't select cell by cell
	tableView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
	//1 item
	tableView->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
	tableView->verticalHeader()->setDefaultSectionSize(20);
	tableView->verticalHeader()->hide();
	//left align
	tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
	//smooth scroll
	tableView->setHorizontalScrollMode(QAbstractItemView::ScrollMode::ScrollPerPixel);
	//Autosize cols
	tableView->setVisible(false);
	tableView->resizeColumnsToContents();
	tableView->setVisible(true);

	gridLayout->addWidget(tableView, 0, 0, 1, 6);

	selectBtn = new QPushButton(this);
	gridLayout->addWidget(selectBtn, 1, 2, 1, 1);
	selectBtn->setText(tr("Attach"));

	cancelBtn = new QPushButton(this);
	cancelBtn->setText("Cancel");
	gridLayout->addWidget(cancelBtn, 1, 3, 1, 1);
	connect(selectBtn, SIGNAL(clicked()), this, SLOT(Select()));
	connect(cancelBtn, SIGNAL(clicked()), this, SLOT(Cancel()));
	connect(tableView, SIGNAL(clicked(const QModelIndex &)),this, SLOT(OnSelectChange(const QModelIndex&)));
	connect(tableView, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(OnDoubleClick(const QModelIndex&)));
}

void QListDialog::OnSelectChange(const QModelIndex& idx)
{
	if (!idx.isValid()) return;
	curSel = idx.row();
}

void QListDialog::OnDoubleClick(const QModelIndex& idx)
{
	curSel = idx.row();
	Select();
}

void QListDialog::Cancel()
{
	this->reject();
}

void QListDialog::Select()
{
	this->accept();
}

QListDialog::~QListDialog()
{

}
