#include "Source/UI/mainwindow.h"
#include <QApplication>
#include <QStyleFactory>
#include <QDebug>
#include "Source/Config/Constants.h"
#include "Source/Core/MainController.h"
#include "Source/Utility/ParameterDecorator.h"


//TODO 测试LoadArchive
int main(int argc,char *argv[])
{

	QApplication a(argc,argv);
	a.setStyle(QStyleFactory::create("Fusion"));


	auto controller=std::make_shared<MainController>();
		controller->Init();
//	controller->Run();



//	auto mainWindow=controller->getMainWindow();
//	mainWindow->InitConnection(controller.get());
//	auto memoCore=controller->getMemoCore();
//
//
//	auto coreFunc=memoCore->getEventHandler(MEMOCORE_LOAD_HANDLER_NAME);
//	auto controllerFunc=controller->getEventHandler(MAINCONTROLLER_LOAD_HANDLER_NAME);

	printf("====================\n");
//	coreFunc->operator()(DEFAULT_MEMO_FILE_NAME);
//	controllerFunc->operator()(DEFAULT_MEMO_FILE_NAME);

//	memoCore->Load(nullptr,DEFAULT_MEMO_FILE_NAME);
//	controller->Load(nullptr,DEFAULT_MEMO_FILE_NAME);

//	std::function<void(EventMonitor *,std::any &&)> controllerFunctionReady=std::bind(&MainController::Load,controller.get(),std::placeholders::_1,std::placeholders::_2);
//	std::function<void(EventMonitor *,std::any &&)> coreFunctionReady=std::bind(&MemoCore::Load,memoCore.get(),std::placeholders::_1,std::placeholders::_2);

//	std::function<void(std::any &&)> controllerFunction=encloseReferencePointer(&controller.get()->eventMonitor,controllerFunctionReady);
//	std::function<void(std::any &&)> coreFunction=encloseReferencePointer(&memoCore.get()->eventMonitor,coreFunctionReady);
//
//
//	auto controllerHandler=std::make_shared<EventHandler>("controller",
//														  controllerFunction,
//														  &controller.get()->eventMonitor);
//	auto coreHandler=std::make_shared<EventHandler>("core",
//													coreFunction,
//													&memoCore.get()->eventMonitor);

//Correct Before


	EventMonitor ControllerMonitor;
	EventMonitor CoreMonitor;
//	ControllerMonitor.AddEventHandler("controller",controllerFunctionReady);
//	CoreMonitor.AddEventHandler("core",coreFunctionReady);


//	std::function<void(std::any &&)> controllerFunction_loc=encloseReferencePointer(&ControllerMonitor,controllerFunctionReady);
//	std::function<void(std::any &&)> coreFunction_loc=encloseReferencePointer(&CoreMonitor,coreFunctionReady);

//	auto controllerHandler=std::make_shared<EventHandler>("controller",
//														  controllerFunction_loc,
//														  &ControllerMonitor);
//	auto coreHandler=std::make_shared<EventHandler>("core",
//													coreFunction_loc,
//													&CoreMonitor);
//	using MAP=std::map<std::string,
//			 EventHandler *,
//			 AbstractAscendingComparer<std::string>>;
//	auto addHandler=[](MAP &map,
//					   EventMonitor *monitor,
//					   const std::string &handlerName,
//					   std::function<void(EventMonitor *,std::any &&)> toExec)
//	{
//		auto handler=new EventHandler(handlerName,
//													std::bind(toExec,monitor,std::placeholders::_1),
//													monitor);
//		map.emplace(handlerName,
//					handler
//		);
//		printf("=====Inner Function Exec Start=====\n");
//		handler->operator()(DEFAULT_MEMO_FILE_NAME);
//		printf("=====Inner Function Exec End=====\n");
//		return handler;
//	};
//
//
//	MAP eventHandlerMap;
////	eventHandlerMap.emplace("controller",controllerHandler);
////	eventHandlerMap.emplace("core",coreHandler);
//
//	auto h1=addHandler(eventHandlerMap,&CoreMonitor,"core",coreFunctionReady);
//	auto h2=addHandler(eventHandlerMap,&ControllerMonitor,"controller",controllerFunctionReady);
//
//	printf("=====Outer Start 1=====\n");
//	h1->operator()(DEFAULT_MEMO_FILE_NAME);
//	printf("=====Outer End 1=====\n");
//	printf("=====Outer Start 2=====\n");
//	h2->operator()(DEFAULT_MEMO_FILE_NAME);
//	printf("=====Outer End 2=====\n");




//	auto h3=std::make_shared<EventHandler>("core",
//										   encloseReferencePointer(&CoreMonitor,coreFunctionReady),
//										   &CoreMonitor);
//	auto h4=std::make_shared<EventHandler>("controller",
//										   encloseReferencePointer(&ControllerMonitor,controllerFunctionReady),
//										   &ControllerMonitor);
//
//
//	h3->operator()(DEFAULT_MEMO_FILE_NAME);
//	h4->operator()(DEFAULT_MEMO_FILE_NAME);


//	EventListener Listener;
//	Listener.Register("core",coreHandler,0);
//	Listener.Register("controller",controllerHandler,1);

//	Listener.Register("core",eventHandlerMap.at("core"),0);
//	Listener.Register("controller",eventHandlerMap.at("controller"),1);

//	Listener.Register("controller",ControllerMonitor.getEventHandlerByName("controller"));
//	Listener.Register("core",CoreMonitor.getEventHandlerByName("core"));


//===================
//	MonitorBase ControllerMonitorBase;
//	MonitorBase CoreMonitorBase;
//	ControllerMonitorBase.addHandler("controller",controllerFunctionReady);
//	CoreMonitorBase.addHandler("core",coreFunctionReady);
//
//	ListenerBase listenerBase;
//	listenerBase.addListener("load");
//	listenerBase.registerHandler("load","controller",ControllerMonitorBase.getEventHandler("controller"));
//	listenerBase.registerHandler("load","core",CoreMonitorBase.getEventHandler("core"));
//
//
//	EventListener eventListener;
//	eventListener.Register("core",CoreMonitorBase.getEventHandler("core"));
//	eventListener.Register("controller",ControllerMonitorBase.getEventHandler("controller"));


	printf("====================\n");


//	coreFunctionReady.operator()(nullptr,DEFAULT_MEMO_FILE_NAME);
//	controllerFunctionReady.operator()(nullptr,DEFAULT_MEMO_FILE_NAME);

//	coreHandler->operator()(DEFAULT_MEMO_FILE_NAME);
//	controllerHandler->operator()(DEFAULT_MEMO_FILE_NAME);

////auto func=[](EventMonitor *p,std::any &&params)->void
////	{
////		printf("1\n");
////	};
////	CoreMonitor.AddEventHandler("1",func);
////
////	std::function<void(std::any &&)> func1=encloseReferencePointer(&CoreMonitor,func);
////	auto handler=std::make_shared<EventHandler>("1",func1,&CoreMonitor);
////
////	handler->operator()(0);
////
////	EventHandlerMap eventHandlerMap;
////	eventHandlerMap.emplace("1",handler);
////
////	auto b(eventHandlerMap.at("1"));
////	auto c(b);
////	c->operator()(0);
////
////
////	CoreMonitor.getEventHandlerByName("1")->operator()(0);

//	coreFunctionReady.operator()(nullptr,DEFAULT_MEMO_FILE_NAME);
//	controllerFunctionReady.operator()(nullptr,DEFAULT_MEMO_FILE_NAME);

//	coreHandler->operator()(DEFAULT_MEMO_FILE_NAME);
//	controllerHandler->operator()(DEFAULT_MEMO_FILE_NAME);

//	Listener.onTriggered(DEFAULT_MEMO_FILE_NAME);





//	CoreMonitor.getEventHandlerByName("core")->operator()(DEFAULT_MEMO_FILE_NAME);
//	ControllerMonitor.getEventHandlerByName("controller")->operator()(DEFAULT_MEMO_FILE_NAME);


//	CoreMonitorBase.getEventHandler("core")->operator()(DEFAULT_MEMO_FILE_NAME);
//	ControllerMonitorBase.getEventHandler("controller")->operator()(DEFAULT_MEMO_FILE_NAME);



//	auto h1=*CoreMonitorBase.getEventHandler("core");
//	h1.operator()(DEFAULT_MEMO_FILE_NAME);
//	auto h2=*ControllerMonitorBase.getEventHandler("controller");
//	h2.operator()(DEFAULT_MEMO_FILE_NAME);


//	eventListener.onTriggered(DEFAULT_MEMO_FILE_NAME);
//	listenerBase.onTriggered("load",DEFAULT_MEMO_FILE_NAME);


	printf("\n======Contrast======\n\n");

//	coreFunc->operator()(DEFAULT_MEMO_FILE_NAME);
//	controllerFunc->operator()(DEFAULT_MEMO_FILE_NAME);











	printf("====================\n");
	controller->Run();



//	std::shared_ptr<MemoStorage> memoStorage=std::make_shared<MemoStorage>();
//	std::shared_ptr<AccessMemoInterface> accessMemoInterface=std::make_shared<AccessMemoInterfaceImpl>(memoStorage);
//	//Test
//	accessMemoInterface->Create(MemoInterfaceParameters("1","","1"));
//	accessMemoInterface->Create(MemoInterfaceParameters("12","","12"));
//	accessMemoInterface->Create(MemoInterfaceParameters("123","","123"));
//	accessMemoInterface->Create(MemoInterfaceParameters("1234","","1234"));
//	accessMemoInterface->Create(MemoInterfaceParameters("12345","","12345"));
//	accessMemoInterface->Create(MemoInterfaceParameters("123456","","123456"));
//	//TODO 利用EventMonitor构建解耦的UI——业务交互
//
//	MainWindow w(nullptr,nullptr);
//
//
//	w.show();

	return a.exec();

}

/** 测试总结
 *  独立构造的Handler单独测试通过
 *  独立构造的Handler放置于Listener测试通过
 *  独立构造的Handler先放置于Map后注册到Listener通过
 *  解决了listener优先级问题
 *  委托构造得到Handler未通过
 *  通过函数构造并保存Handler至map未通过
 *  通过函数构造并返回的Handler未通过
 *
 *
 */
//TODO 修改使得仅仅对Listener采用优先级

