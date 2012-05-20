#include "moduletab.h"

ModuleTab::ModuleTab(QWidget *parent, char* name)
	: QWidget(parent)
{
	QStandardItemModel *model = new QStandardItemModel(0, 6);
	model->setHeaderData(0, Qt::Horizontal, "Name");
	model->setHeaderData(1, Qt::Horizontal, "Base");
	model->setHeaderData(2, Qt::Horizontal, "Size");
	model->setHeaderData(3, Qt::Horizontal, "Entry Point");
	model->setHeaderData(4, Qt::Horizontal, "Version");
	model->setHeaderData(5, Qt::Horizontal, "Path");

	for (int i = 0; i < Vox::Dbg::modules.size(); i++)
	{
		QList<QStandardItem*> row;

		char name[MAX_PATH], base[100], size[100], entry[100], version[100], path[MAX_PATH];
		strcpy(name, Vox::Dbg::WideToMulti(Vox::Dbg::modules[i].me32.szModule));
		strcpy(base, Vox::Dbg::MakeString("0x%X", Vox::Dbg::modules[i].me32.modBaseAddr));
		strcpy(size, Vox::Dbg::MakeString("0x%X", Vox::Dbg::modules[i].me32.modBaseSize));
		strcpy(entry, Vox::Dbg::MakeString("0x%X", Vox::Dbg::modules[i].me32.modBaseAddr + Vox::Dbg::modules[i].nt_header.OptionalHeader.AddressOfEntryPoint));
		strcpy(version, Vox::Dbg::MakeString("%u.%u", Vox::Dbg::modules[i].nt_header.OptionalHeader.MajorLinkerVersion,
			Vox::Dbg::modules[i].nt_header.OptionalHeader.MinorLinkerVersion));
		strcpy(path, Vox::Dbg::WideToMulti(Vox::Dbg::modules[i].me32.szExePath));
		//printf("%s %s %s %s\n", name, base, size, path);

		DWORD dwBase = (DWORD)Vox::Dbg::modules[i].me32.modBaseAddr;


		row.append(new QStandardItem(name));
		row.append(new QStandardItem(base));
		row.append(new QStandardItem(size));
		row.append(new QStandardItem(entry));
		row.append(new QStandardItem(version));
		row.append(new QStandardItem(path));

		model->appendRow(row);
	}

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

	//Connect event handlers
	connect(tableView, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(OnDoubleClickEntry(const QModelIndex&)));
}

void ModuleTab::OnDoubleClickEntry(const QModelIndex& idx)
{
	emit doubleClickEntry(idx.row());
}

ModuleTab::~ModuleTab()
{

}
