#include "mainwindow.h"

using namespace Vox;

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	statusBar()->showMessage("Ready.");

	QWidget* spacer = new QWidget;
	spacer->setFixedWidth(40);
	attachBtn = new QToolButton;
	openFileBtn = new QToolButton;
	playBtn = new QToolButton;
	pauseBtn = new QToolButton;
	stopBtn = new QToolButton;
	
	//Disable some
	playBtn->setDisabled(true);
	pauseBtn->setDisabled(true);
	stopBtn->setDisabled(true);

	attachBtn->setIcon(QIcon(":/Icons/bug.png"));
	openFileBtn->setIcon(QIcon(":/Icons/folder_explore.png"));
	playBtn->setIcon(QIcon(":/Icons/control_play_blue.png"));
	pauseBtn->setIcon(QIcon(":/Icons/control_pause_blue.png"));
	stopBtn->setIcon(QIcon(":/Icons/control_stop_blue.png"));

	//Events
	connect(attachBtn, SIGNAL(clicked()), this, SLOT(Trigger_AttachToProcess()));
	connect(playBtn, SIGNAL(clicked()), this, SLOT(Trigger_PlayBtn()));
	connect(stopBtn, SIGNAL(clicked()), this, SLOT(Trigger_StopBtn()));
	connect(pauseBtn, SIGNAL(clicked()), this, SLOT(Trigger_PauseBtn()));
	//Add
	ui.toolBar->addWidget(attachBtn);
	ui.toolBar->addSeparator();
	ui.toolBar->addWidget(openFileBtn);
	ui.toolBar->addSeparator();
	ui.toolBar->addWidget(playBtn);
	ui.toolBar->addSeparator();
	ui.toolBar->addWidget(pauseBtn);
	ui.toolBar->addSeparator();
	ui.toolBar->addWidget(stopBtn);

	//Initialize event handlers
	connect(ui.actionAttach_to_Process, SIGNAL(triggered()), this, SLOT(Trigger_AttachToProcess()));

	//Debug
	AllocConsole();
	freopen("CONOUT$", "w", stdout);

	Vox::Dbg::Init();

	//Make sure we actually do this
	bool bFirstRun = false;
	if (bFirstRun)
	{
		QMessageBox::information(NULL, "First Run", "This appears to be your first run. Please open a file"
			" or attach VoxDbg to a process.");
	}
}

void MainWindow::Trigger_StopBtn()
{
	Dbg::StopDebugging();
	playBtn->setDisabled(true);
	pauseBtn->setDisabled(true);
	stopBtn->setDisabled(true);
	setWindowTitle("Voxation Debugger");
	//ui.tabs->clear();
	Dbg::Init();
}

void MainWindow::Trigger_PlayBtn()
{
	DEBUG_EVENT evt;
	playBtn->setDisabled(true);
	pauseBtn->setDisabled(false);
	WaitForDebugEvent(&evt, INFINITE);
}

void MainWindow::Trigger_PauseBtn()
{
	playBtn->setDisabled(false);
	pauseBtn->setDisabled(true);
}

void MainWindow::Trigger_AttachToProcess()
{
	if (Dbg::mode != None)
	{
		int ret = QMessageBox::warning(NULL, "Already Debugging", "You are already debugging/analyzing a file. Close it?",
		QMessageBox::StandardButton::Ok, QMessageBox::StandardButton::No);

		if (ret == QMessageBox::No) return;
		
		Dbg::mode = Vox::None;
		Dbg::Init();
		//ui.tabs->clear();
		this->setWindowTitle("Voxation Debugger");
	}
	QStandardItemModel *model = new QStandardItemModel(0, 3);
	model->setHeaderData(0, Qt::Horizontal, "PID");
	model->setHeaderData(1, Qt::Horizontal, "Name");
	model->setHeaderData(2, Qt::Horizontal, "Path");
	
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot == INVALID_HANDLE_VALUE)
	{
		printf("Error getting snapshot.\n");
		return;
	}

	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof PROCESSENTRY32;
	if( !Process32First( hSnapshot, &pe32 ) )
	{
		printf("Error getting process info.\n");
		return;
	}
	do
	{
		QList<QStandardItem*> entry;
		char pid[10];
		sprintf(pid, "%X", pe32.th32ProcessID);
		entry.append(new QStandardItem(pid));
		char name[256];
		wcstombs(name, pe32.szExeFile, 256);
		entry.append(new QStandardItem(name));
		HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
		if (hProc == NULL)
		{
			printf("Warning: error opening process %s || LastError = %u\n", name, GetLastError());
			continue;
		}
		wchar_t wPath[MAX_PATH];
		char szPath[MAX_PATH];
		if (GetModuleFileNameEx(hProc, NULL, wPath, MAX_PATH) == 0)
		{
			//Continue instead; we won't be able to call Module32Next anways, even if we keep it.
			continue;
			//strcpy(szPath, name);
		}
		else
		{
			wcstombs(szPath, wPath, MAX_PATH);
		}
		entry.append(new QStandardItem(szPath));
		CloseHandle(hProc);
		model->appendRow(entry);
	} while (Process32Next(hSnapshot, &pe32));


	QListDialog* processList = new QListDialog(this, "Select process to attach to", model);
	processList->setFocus();
	if (processList->exec() == QDialog::Accepted)
	{
	}
	else
	{
		return;
	}
	auto res = model->item(processList->curSel, 0);
	DWORD pid = 0;
	sscanf(res->text().toStdString().c_str(), "%X", &pid);
	res = model->item(processList->curSel, 1);
	char name[100];
	strcpy(name, res->text().toStdString().c_str());
	char newTitle[256];
	sprintf(newTitle, "Voxation Debugger :: %s", name);
	bool ret = Dbg::AttachToProcess(pid);
	if (!ret)
	{
		playBtn->setDisabled(true);
		pauseBtn->setDisabled(true);
		stopBtn->setDisabled(true);
		return;
	}
	ret = Dbg::EnumModules();

	if (!ret)
	{
		Dbg::Init();
		playBtn->setDisabled(true);
		pauseBtn->setDisabled(true);
		stopBtn->setDisabled(true);
		return;
	}

	this->setWindowTitle(newTitle);

	moduleTab = new ModuleTab(this, "Modules");
	Dbg::ModuleTabOpen = true;
	connect(moduleTab, SIGNAL(doubleClickEntry(int)), this, SLOT(OnDoubleClickModule(int)));
	ui.tabs->addTab(moduleTab, "Modules");

	Dbg::StartDebugging();
	playBtn->setDisabled(false);
	pauseBtn->setDisabled(true);
	stopBtn->setDisabled(false);
}

void MainWindow::OnDoubleClickModule(int idx)
{
	printf("Double clicked %d\n", idx);
	if (!Dbg::CPUTabOpen)
	{
		cpuTab = new CPUTab(this, "CPU");
		ui.tabs->addTab(cpuTab, "CPU");
		Dbg::CPUTabOpen = true;
	}
	int index = ui.tabs->indexOf(cpuTab);
	ui.tabs->setCurrentIndex(index);
	
	cpuTab->tableView->resizeColumnsToContents();
}

MainWindow::~MainWindow()
{
	
}
