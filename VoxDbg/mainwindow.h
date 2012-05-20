#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QMessageBox>
#include "ui_mainwindow.h"
#include "Dbg.h"
#include "qlistdialog.h"
#include "moduletab.h"
#include "cputab.h"
#include <QtGui/qdockwidget.h>
#include <QtGui/QToolButton>

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MainWindow();

private slots:
	//Menu Triggers
	void Trigger_AttachToProcess();
	void Trigger_StopBtn();
	void Trigger_PlayBtn();
	void Trigger_PauseBtn();

	//Other
	void OnDoubleClickModule(int idx);
private:
	Ui::MainWindowClass ui;
	ModuleTab* moduleTab;
	CPUTab* cpuTab;

	//Toolbar buttons
	QToolButton* playBtn;
	QToolButton* pauseBtn;
	QToolButton* stopBtn;
	QToolButton* attachBtn;
	QToolButton* openFileBtn;
};

#endif // MAINWINDOW_H
