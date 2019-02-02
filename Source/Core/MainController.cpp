//
// Created by 星落_月残 on 2019/1/23.
//

#include "MainController.h"
#include "../Config/Constants.h"
#include "../UI/mainwindow.h"


MainController::MainController()
		:memoCore(std::make_shared<MemoCore>()),
		 mainWindow(std::make_shared<MainWindow>(nullptr))
{
	this->addHandler(MAINCONTROLLER_LOAD_HANDLER_NAME,
					 [this](EventMonitor *monitor,std::any &&params)
					 {
						 this->mainWindow->setMemoInterfaceFromProvider(this->memoCore);
						 this->mainWindow->setBookmarkInterfaceFromProvider(this->memoCore);
						 this->mainWindow->setHistoryInterfaceFromProvider(this->memoCore);
					 });
	this->addHandler(MAINCONTROLLER_SAVE_HANDLER_NAME,
					 [this](EventMonitor *monitor,std::any &&params)
					 {

					 });
}
void MainController::Init()
{
	mainWindow->InitConnection(this);
	mainWindow->InitComponents();
}
void MainController::Run()
{
	mainWindow->show();
}
std::shared_ptr<MemoCore> MainController::getMemoCore() const
{
	return memoCore;
}
std::shared_ptr<MainWindow> MainController::getMainWindow() const
{
	return mainWindow;
}

