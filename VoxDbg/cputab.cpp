#include "cputab.h"

CPUTab::CPUTab(QWidget *parent, char* name)
	: QWidget(parent)
{
	model = new QStandardItemModel(0, 1);
	model->setHeaderData(0, Qt::Horizontal, "Disassembly");
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
}

CPUTab::~CPUTab()
{

}
