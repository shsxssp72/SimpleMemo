//
// Created by 星落_月残 on 2019/1/23.
//

#ifndef SIMPLEMEMO_MAINCONTROLLER_H
#define SIMPLEMEMO_MAINCONTROLLER_H

#include "../Utility/EventMonitor.h"
#include "MemoCore.h"


class MainWindow;

class MainController:public MonitorBase
{
public:
	MainController();
	void Init();
	std::shared_ptr<MemoCore> getMemoCore() const;
	std::shared_ptr<MainWindow> getMainWindow() const;
	void Run();
private:
	std::shared_ptr<MemoCore> memoCore;
	std::shared_ptr<MainWindow> mainWindow;

};


#endif //SIMPLEMEMO_MAINCONTROLLER_H
