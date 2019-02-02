#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../Utility/TraverseHelper.h"
#include "../Utility/ParameterDecorator.h"
#include <regex>
#include <cassert>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <Source/Utility/SerializationUtility.h>
#include <Source/Interface/Memo/AccessMemoInterfaceImpl.h>
#include "../Config/Constants.h"
#include "../Core/MainController.h"
#include "../Utility/Commons.h"

//TODO history,bookmark显示上次显示时间
//TODO 增加删除item选项,新建Memo选项

MainWindow::MainWindow(QWidget *parent)
		:QMainWindow(parent),
		 ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	setWindowTitle("SimpleMemo");
	InitializeInitFunc();
	for(auto &r:initializeFunctions)
		r.operator()();
}

MainWindow::~MainWindow()
{
	delete ui;
}
std::list<MemoData> MemoInterfaceTraverse(AccessMemoInterface *pAccessMemoInterface,
										  std::function<bool(const MemoData &)> function)//注意interface的生命周期
{
	MemoDataTraverseHelperForAnyGetter memoDataTraverseHelperForAnyGetter;
	pAccessMemoInterface->Traverse(
			std::bind(
					&MemoDataTraverseHelperForAnyGetter::operator(),
					&memoDataTraverseHelperForAnyGetter,
					std::placeholders::_1,
					[&](const std::any &input)->bool
					{
						return function(std::any_cast<MemoData>(input));
					}));
	return memoDataTraverseHelperForAnyGetter.getMemoDatas();
}
std::list<MemoBookmarkContent> BookmarkInterfaceTraverse(AccessBookmarkInterface *pAccessBookmarkInterface,
														 std::function<bool(const MemoBookmarkContent &)> function)//注意interface的生命周期
{
	BookmarkTraverseHelperForAnyGetter bookmarkTraverseHelperForAnyGetter;
	pAccessBookmarkInterface->Traverse(
			std::bind(
					&BookmarkTraverseHelperForAnyGetter::operator(),
					&bookmarkTraverseHelperForAnyGetter,
					std::placeholders::_1,
					[&](const std::any &input)->bool
					{
						return function(std::any_cast<MemoBookmarkContent>(input));
					}));
	return bookmarkTraverseHelperForAnyGetter.getBookmarks();
}
void updateBookmarkKeyIndex(AccessBookmarkInterface *interface,const std::string &originalKey,const std::string &newKey)
{
	auto getPreviousRecord=std::bind(BookmarkInterfaceTraverse,interface,[&](const std::any &input)->bool
	{
		return std::any_cast<MemoBookmarkContent>(input).key==originalKey;
	});
	auto previousRecord=getPreviousRecord();
	for(;!previousRecord.empty();)
	{
		interface->Delete(BookmarkInterfaceParameters(previousRecord.front().key));
		interface->Create(BookmarkInterfaceParameters(newKey));
		previousRecord.pop_front();
	}
}
void MainWindow::InitializeInitFunc()
{

	initializeFunctions.emplace_back([this]()->void
									 {
										 QObject::connect(ui->add_button,
														  &QPushButton::clicked,
														  this,
														  &MainWindow::onClickAdd);
										 QObject::connect(ui->delete_button,
														  &QPushButton::clicked,
														  this,
														  &MainWindow::onClickDelete);
										 QObject::connect(ui->search_button,
														  &QPushButton::clicked,
														  this,
														  &MainWindow::onClickSearch);
										 QObject::connect(ui->history_delete_button,
														  &QPushButton::clicked,
														  this,
														  &MainWindow::onClickHistoryDelete);
										 QObject::connect(ui->history_clear_button,
														  &QPushButton::clicked,
														  this,
														  &MainWindow::onClickHistoryClear);
										 QObject::connect(ui->bookmark_delete_button,
														  &QPushButton::clicked,
														  this,
														  &MainWindow::onClickBookmarkDelete);
										 QObject::connect(ui->bookmark_clear_button,
														  &QPushButton::clicked,
														  this,
														  &MainWindow::onClickBookmarkClear);
										 QObject::connect(ui->edit_save_value_button,
														  &QPushButton::clicked,
														  this,
														  &MainWindow::onClickEditSaveValue);
										 QObject::connect(ui->bookmark_cancel_value_button,
														  &QPushButton::clicked,
														  this,
														  &MainWindow::onClickBookmarkCancelValue);
									 });
	initializeFunctions.emplace_back([this]()->void
									 {
										 QObject::connect(ui->search_input_line,
														  &QLineEdit::textChanged,
														  this,
														  &MainWindow::onSearchTextChanged);
										 QObject::connect(ui->search_result_list,
														  &QListWidget::itemClicked,
														  this,
														  &MainWindow::onKeyListItemClicked);
										 QObject::connect(ui->bookmark_list,
														  &QListWidget::itemClicked,
														  this,
														  &MainWindow::onKeyListItemClicked);
										 QObject::connect(ui->history_list,
														  &QListWidget::itemClicked,
														  this,
														  &MainWindow::onKeyListItemClicked);
									 });
	initializeFunctions.emplace_back([this]()->void
									 {
										 QObject::connect(ui->actionLoad,
														  &QAction::triggered,
														  this,
														  &MainWindow::onActionLoad);
										 QObject::connect(ui->actionSave,
														  &QAction::triggered,
														  this,
														  &MainWindow::onActionSave);
										 QObject::connect(ui->actionSaveAs,
														  &QAction::triggered,
														  this,
														  &MainWindow::onActionSaveAs);
										 QObject::connect(ui->actionQuit,
														  &QAction::triggered,
														  this,
														  &MainWindow::onActionQuit);
									 });
	//!涉及UI元素变化的操作以状态机形式存放于此处
	initializeFunctions.emplace_back([this]()->void
									 {
										 this->addHandler(INITIAL_STATE_HANDLER_NAME,[&](EventMonitor *pEventMonitor,std::any &&params)->void
										 {
											 qDebug()<<"Entering InitialState"<<endl;
											 ui->key_input_line->setEnabled(false);
											 ui->key_input_line->clear();
											 ui->value_text->setEnabled(false);
											 ui->value_text->clear();
											 ui->edit_save_value_button->setText("Edit");
											 ui->edit_save_value_button->setEnabled(false);
											 ui->bookmark_cancel_value_button->setText("Bookmark");
											 ui->bookmark_cancel_value_button->setEnabled(false);
											 ui->add_button->setEnabled(true);
											 ui->delete_button->setEnabled(false);
										 });
										 //!params QString last newed item value that has not been saved.
										 this->addHandler(NEW_STATE_HANDLER_NAME,[&](EventMonitor *pEventMonitor,std::any &&params)->void
										 {
											 qDebug()<<"Entering NewState"<<endl;
											 auto value=std::any_cast<QString>(params);
											 ui->key_input_line->setEnabled(true);
											 ui->key_input_line->clear();
											 ui->value_text->setEnabled(true);
											 ui->value_text->clear();
											 ui->value_text->setPlainText(value);
											 ui->edit_save_value_button->setText("Save");
											 ui->edit_save_value_button->setEnabled(true);
											 ui->bookmark_cancel_value_button->setText("Cancel");
											 ui->bookmark_cancel_value_button->setEnabled(true);
											 ui->add_button->setEnabled(false);
											 ui->delete_button->setEnabled(false);
										 });
										 //!params QString item key to show.
										 this->addHandler(DISPLAY_STATE_HANDLER_NAME,[&](EventMonitor *pEventMonitor,std::any &&params)->void
										 {
											 qDebug()<<"Entering DisplayState"<<endl;
											 this->displayKeyAndValue(std::any_cast<QString>(params));
											 ui->key_input_line->setEnabled(false);
											 ui->value_text->setEnabled(false);
											 ui->edit_save_value_button->setText("Edit");
											 ui->bookmark_cancel_value_button->setText("Bookmark");
											 ui->add_button->setEnabled(true);
											 ui->delete_button->setEnabled(true);
										 });

										 this->addHandler(NEWSAVE_STATE_HANDLER_NAME,[&](EventMonitor *pEventMonitor,std::any &&params)->void
										 {
											 qDebug()<<"Entering NewSaveState"<<endl;
											 try
											 {
												 this->memoInterface->Create(MemoInterfaceParameters(ui->key_input_line->text().toStdString(),
																									 "",
																									 ui->value_text->toPlainText().toStdString()));
												 this->stateMachine.transferToState(DISPLAY_STATE_NAME,ui->key_input_line->text());
											 }
											 catch(std::invalid_argument &exception)
											 {
												 ui->statusBar->showMessage(exception.what());
												 stateMachine.transferToState(NEW_STATE_NAME,ui->value_text->toPlainText());
											 }
										 });
										 //!params QString original item key.
										 this->addHandler(EDIT_STATE_HANDLER_NAME,[&](EventMonitor *pEventMonitor,std::any &&params)->void
										 {
											 qDebug()<<"Entering EditState"<<endl;
											 auto key=std::any_cast<QString>(params);
											 pEventMonitor->AddParameter("OriginalKey",key);
											 ui->key_input_line->setEnabled(true);
											 ui->key_input_line->setText(key);//用于从EditSave错误恢复
											 ui->value_text->setEnabled(true);
//											 ui->value_text->setPlainText(
//													 QString::fromStdString(
//															 memoInterface->Retrieve(
//																	 MemoInterfaceParameters(
//																			 key.toStdString())).getValue()));//用于从EditSave错误恢复
											 ui->edit_save_value_button->setText("Save");
											 ui->bookmark_cancel_value_button->setText("Cancel");
											 ui->add_button->setEnabled(false);
											 ui->delete_button->setEnabled(false);
										 });
										 this->addHandler(EDITSAVE_STATE_HANDLER_NAME,[&](EventMonitor *pEventMonitor,std::any &&params)->void
										 {
											 qDebug()<<"Entering EditSaveState"<<endl;
											 QString originalKey=std::any_cast<QString>(pEventMonitor->getParameterByName("OriginalKey"));
											 pEventMonitor->RemoveParameter("OriginalKey");
											 if(ui->key_input_line->text()!=originalKey)
											 {
												 try
												 {
													 this->memoInterface->Update(MemoInterfaceParameters(originalKey.toStdString(),
																										 ui->key_input_line->text().toStdString(),
																										 ui->value_text->toPlainText().toStdString()));

													 //更新history Key
													 updateBookmarkKeyIndex(historyInterface.get(),
																			originalKey.toStdString(),
																			ui->key_input_line->text().toStdString());
													 updateHistory();
													 //更新bookmark Key
													 updateBookmarkKeyIndex(bookmarkInterface.get(),
																			originalKey.toStdString(),
																			ui->key_input_line->text().toStdString());
													 updateBookmark();
													 this->stateMachine.transferToState(DISPLAY_STATE_NAME,ui->key_input_line->text());
												 }
												 catch(std::invalid_argument &exception)
												 {
													 ui->statusBar->showMessage(exception.what());
													 stateMachine.transferToState(EDIT_STATE_NAME,originalKey);
												 }
											 }
											 else
											 {
												 this->memoInterface->Update(MemoInterfaceParameters(originalKey.toStdString(),
																									 "",
																									 ui->value_text->toPlainText().toStdString()));
												 this->stateMachine.transferToState(DISPLAY_STATE_NAME,ui->key_input_line->text());
											 }
										 });
										 this->addHandler(EDITCANCEL_STATE_HANDLER_NAME,[&](EventMonitor *pEventMonitor,std::any &&params)->void
										 {
											 qDebug()<<"Entering EditCancelState"<<endl;
											 QString originalKey=std::any_cast<QString>(pEventMonitor->getParameterByName("OriginalKey"));
											 pEventMonitor->RemoveParameter("OriginalKey");
											 this->stateMachine.transferToState(DISPLAY_STATE_NAME,originalKey);
										 });


										 stateMachine.addState(NEW_STATE_NAME);
										 stateMachine.addState(DISPLAY_STATE_NAME);
										 stateMachine.addState(NEWSAVE_STATE_NAME);
										 stateMachine.addState(EDIT_STATE_NAME);
										 stateMachine.addState(EDITSAVE_STATE_NAME);
										 stateMachine.addState(EDITCANCEL_STATE_NAME);

										 stateMachine.connect(DEFAULT_INITIAL_STATE_NAME,NEW_STATE_NAME);
										 stateMachine.connect(DEFAULT_INITIAL_STATE_NAME,DISPLAY_STATE_NAME);
										 stateMachine.connect(NEW_STATE_NAME,NEWSAVE_STATE_NAME);
										 stateMachine.connect(NEW_STATE_NAME,DEFAULT_INITIAL_STATE_NAME);
										 stateMachine.connect(DISPLAY_STATE_NAME,EDIT_STATE_NAME);
										 stateMachine.connect(DISPLAY_STATE_NAME,NEW_STATE_NAME);
										 stateMachine.connect(DISPLAY_STATE_NAME,DISPLAY_STATE_NAME);
										 stateMachine.connect(DISPLAY_STATE_NAME,DEFAULT_INITIAL_STATE_NAME);
										 stateMachine.connect(NEWSAVE_STATE_NAME,DISPLAY_STATE_NAME);
										 stateMachine.connect(NEWSAVE_STATE_NAME,NEW_STATE_NAME);
										 stateMachine.connect(EDIT_STATE_NAME,EDITSAVE_STATE_NAME);
										 stateMachine.connect(EDIT_STATE_NAME,EDITCANCEL_STATE_NAME);
										 stateMachine.connect(EDITSAVE_STATE_NAME,DISPLAY_STATE_NAME);
										 stateMachine.connect(EDITSAVE_STATE_NAME,EDIT_STATE_NAME);
										 stateMachine.connect(EDITCANCEL_STATE_NAME,DISPLAY_STATE_NAME);


										 stateMachine.
												 addStateActivationHandler(
												 DEFAULT_INITIAL_STATE_NAME,
												 INITIAL_STATE_HANDLER_NAME,
												 this->getEventHandler(INITIAL_STATE_HANDLER_NAME));
										 stateMachine.
												 addStateActivationHandler(
												 NEW_STATE_NAME,
												 NEW_STATE_HANDLER_NAME,
												 this->getEventHandler(NEW_STATE_HANDLER_NAME));
										 stateMachine.
												 addStateActivationHandler(
												 DISPLAY_STATE_NAME,
												 DISPLAY_STATE_HANDLER_NAME,
												 this->getEventHandler(DISPLAY_STATE_HANDLER_NAME));
										 stateMachine.
												 addStateActivationHandler(
												 NEWSAVE_STATE_NAME,
												 NEWSAVE_STATE_HANDLER_NAME,
												 this->getEventHandler(NEWSAVE_STATE_HANDLER_NAME));
										 stateMachine.
												 addStateActivationHandler(
												 EDIT_STATE_NAME,
												 EDIT_STATE_HANDLER_NAME,
												 this->getEventHandler(EDIT_STATE_HANDLER_NAME));
										 stateMachine.
												 addStateActivationHandler(
												 EDITSAVE_STATE_NAME,
												 EDITSAVE_STATE_HANDLER_NAME,
												 this->getEventHandler(EDITSAVE_STATE_HANDLER_NAME));
										 stateMachine.
												 addStateActivationHandler(
												 EDITCANCEL_STATE_NAME,
												 EDITCANCEL_STATE_HANDLER_NAME,
												 this->getEventHandler(EDITCANCEL_STATE_HANDLER_NAME));
									 });
	initializeFunctions.emplace_back([this]()->void
									 {
										 ui->value_text->setEnabled(false);
									 });
	initializeFunctions.emplace_back([this]()->void
									 {
										 this->addListener(UI_LOAD_LISTENER_NAME);
										 this->addListener(UI_SAVE_LISTENER_NAME);
									 });
}
void MainWindow::InitConnection(MainController *mainController)
{
	this->registerHandler(UI_LOAD_LISTENER_NAME,
						  MEMOCORE_LOAD_HANDLER_NAME,
						  mainController->getMemoCore()->getEventHandler(MEMOCORE_LOAD_HANDLER_NAME),
						  COMPARER_FIRST_PRIORITY);
	this->registerHandler(UI_LOAD_LISTENER_NAME,
						  MAINCONTROLLER_LOAD_HANDLER_NAME,
						  mainController->getEventHandler(MAINCONTROLLER_LOAD_HANDLER_NAME),
						  COMPARER_SECOND_PRIORITY);

	this->registerHandler(UI_SAVE_LISTENER_NAME,
						  MEMOCORE_SAVE_HANDLER_NAME,
						  mainController->getMemoCore()->getEventHandler(MEMOCORE_SAVE_HANDLER_NAME),
						  COMPARER_FIRST_PRIORITY);
	this->registerHandler(UI_SAVE_LISTENER_NAME,
						  MAINCONTROLLER_SAVE_HANDLER_NAME,
						  mainController->getEventHandler(MAINCONTROLLER_SAVE_HANDLER_NAME),
						  COMPARER_SECOND_PRIORITY);
}
void MainWindow::InitComponents()
{
	QFile defaultMemo(DEFAULT_MEMO_FILE_NAME.c_str());
	if(defaultMemo.exists())
	{
		this->load(DEFAULT_MEMO_FILE_NAME);
	}
	else
	{
		this->load("");
		ui->statusBar->showMessage("Warning: Default memo file not found.");
	}
}


void MainWindow::updateBookmark()
{
	//TODO 修改为只传key
	auto bookmarkTraverse=std::bind(BookmarkInterfaceTraverse,bookmarkInterface.get(),[&](const std::any &input)->bool
	{
		return true;
	});
	ui->bookmark_list->clear();
	for(auto &r:bookmarkTraverse())
	{
		ui->bookmark_list->addItem(QString::fromStdString(r.key));
	}
}
void MainWindow::updateHistory()
{
	//TODO 修改为只传key
	auto historyTraverse=std::bind(BookmarkInterfaceTraverse,historyInterface.get(),[&](const std::any &input)->bool
	{
		return true;
	});
	ui->history_list->clear();
	for(auto &r:historyTraverse())
	{
		ui->history_list->addItem(QString::fromStdString(r.key));
	}
}
void MainWindow::onSearchTextChanged(const QString &text)
{
	if(!text.isEmpty())
	{
		ui->search_result_list->clear();
		std::regex toMatch(text.toStdString()+".*",std::regex_constants::ECMAScript|std::regex_constants::icase);
		MemoDataTraverseHelperForAnyGetter memoDataTraverseHelperForAnyGetter;
		//TODO 修改为只传key
		auto traverse=encloseReferencePointer(memoInterface.get(),MemoInterfaceTraverse);
		auto realTraverse=std::bind(traverse,[&](const std::any &input)->bool
		{
			return std::regex_match(std::any_cast<MemoData>(input).getKey(),toMatch);
		});
		for(auto &r:realTraverse())
		{
			ui->search_result_list->addItem(QString::fromStdString(r.getKey()));
		}
	}
}
void MainWindow::onKeyListItemClicked(QListWidgetItem *item)
{
	std::string key=item->text().toStdString();
	if(isOneOf(stateMachine.getCurrentStateName(),DEFAULT_INITIAL_STATE_NAME,DISPLAY_STATE_NAME))
	{
		auto getPreviousRecord=std::bind(BookmarkInterfaceTraverse,historyInterface.get(),[&](const std::any &input)->bool
		{
			return std::any_cast<MemoBookmarkContent>(input).key==key;
		});
		auto previousRecord=getPreviousRecord();
		for(;!previousRecord.empty();)
		{
			historyInterface->Delete(BookmarkInterfaceParameters(previousRecord.front().key));
			previousRecord.pop_front();
		}
		historyInterface->Create(BookmarkInterfaceParameters(key));
		updateHistory();
		stateMachine.transferToState(DISPLAY_STATE_NAME,QString::fromStdString(key));
	}
	else
	{
		ui->statusBar->showMessage("Please finish editing first.");
	}
}
void MainWindow::onClickAdd()
{
	qDebug()<<"onClickAdd: current state : "<<stateMachine.getCurrentStateName().c_str()<<endl;
	assert(isOneOf(stateMachine.getCurrentStateName(),DEFAULT_INITIAL_STATE_NAME,DISPLAY_STATE_NAME));
	stateMachine.transferToState(NEW_STATE_NAME,QString());
}
void MainWindow::onClickDelete()
{
	assert(!ui->key_input_line->isEnabled()&&stateMachine.getCurrentStateName()==DISPLAY_STATE_NAME);
	QString key=ui->key_input_line->text();
	memoInterface->Delete(MemoInterfaceParameters(key.toStdString()));

	auto getPreviousRecord=std::bind(BookmarkInterfaceTraverse,bookmarkInterface.get(),[&](const std::any &input)->bool
	{
		return std::any_cast<MemoBookmarkContent>(input).key==key.toStdString();
	});
	auto previousRecord=getPreviousRecord();

	for(;!previousRecord.empty();)
	{
		bookmarkInterface->Delete(BookmarkInterfaceParameters(previousRecord.front().key));
		bookmarkInterface->Create(BookmarkInterfaceParameters(key.toStdString()));
		previousRecord.pop_front();
	}

	bookmarkInterface->Create(BookmarkInterfaceParameters(key.toStdString()));
	updateBookmark();

	stateMachine.transferToState(DEFAULT_INITIAL_STATE_NAME,nullptr);
}
void MainWindow::onClickSearch()
{
	//不涉及字符串匹配
	QString searchText=ui->search_input_line->text();
	if(!searchText.isEmpty())
	{
		try
		{
			auto searchResult=memoInterface->Retrieve(MemoInterfaceParameters(searchText.toStdString()));
			ui->search_result_list->clear();
			ui->search_result_list->addItem(QString::fromStdString(searchResult.getKey()));
		}
		catch(std::invalid_argument &e)
		{
			qDebug()<<"Not Found"<<endl;
			ui->search_result_list->clear();
		}
	}
}
void MainWindow::onClickHistoryDelete()
{
	for(auto &r:ui->history_list->selectedItems())
	{
		historyInterface->Delete(BookmarkInterfaceParameters(r->text().toStdString()));
	}
	updateHistory();
}
void MainWindow::onClickHistoryClear()
{
	for(int i=0;i<ui->history_list->count();i++)
	{
		historyInterface->Delete(BookmarkInterfaceParameters(ui->history_list->item(i)->text().toStdString()));
	}
	updateHistory();
}
void MainWindow::onClickBookmarkDelete()
{
	for(auto &r:ui->bookmark_list->selectedItems())
	{
		bookmarkInterface->Delete(BookmarkInterfaceParameters(r->text().toStdString()));
	}
	updateBookmark();
}
void MainWindow::onClickBookmarkClear()
{
	for(int i=0;i<ui->bookmark_list->count();i++)
	{
		historyInterface->Delete(BookmarkInterfaceParameters(ui->bookmark_list->item(i)->text().toStdString()));
	}
	updateBookmark();
}
void MainWindow::onClickEditSaveValue()
{
	qDebug()<<"onClickEditSaveValue: current state : "<<stateMachine.getCurrentStateName().c_str()<<endl;
	assert(isOneOf(stateMachine.getCurrentStateName(),NEW_STATE_NAME,DISPLAY_STATE_NAME,EDIT_STATE_NAME));
	if(stateMachine.getCurrentStateName()==NEW_STATE_NAME)
	{
		stateMachine.transferToState(NEWSAVE_STATE_NAME,nullptr);
	}
	else if(stateMachine.getCurrentStateName()==DISPLAY_STATE_NAME)
	{
		stateMachine.transferToState(EDIT_STATE_NAME,ui->key_input_line->text());
	}
	else if(stateMachine.getCurrentStateName()==EDIT_STATE_NAME)
	{
		stateMachine.transferToState(EDITSAVE_STATE_NAME,nullptr);
	}
}
void MainWindow::onClickBookmarkCancelValue()
{
	qDebug()<<"onClickBookmarkCancelValue: current state : "<<stateMachine.getCurrentStateName().c_str()<<endl;

	assert(isOneOf(stateMachine.getCurrentStateName(),NEW_STATE_NAME,DISPLAY_STATE_NAME,EDIT_STATE_NAME));
	if(stateMachine.getCurrentStateName()==NEW_STATE_NAME)
	{
		stateMachine.transferToState(DEFAULT_INITIAL_STATE_NAME,nullptr);
	}
	else if(stateMachine.getCurrentStateName()==DISPLAY_STATE_NAME)
	{
		//BookmarkAction
		//书签操作仅当未修改或修改后已保存时才可用，因此不再判断是否保存
		const QString &key=ui->key_input_line->text();
		if(!key.isEmpty())
		{
			auto getPreviousRecord=std::bind(BookmarkInterfaceTraverse,bookmarkInterface.get(),[&](const std::any &input)->bool
			{
				return std::any_cast<MemoBookmarkContent>(input).key==key.toStdString();
			});
			auto previousRecord=getPreviousRecord();

			for(;!previousRecord.empty();)
			{
				bookmarkInterface->Delete(BookmarkInterfaceParameters(previousRecord.front().key));
				previousRecord.pop_front();
			}
			bookmarkInterface->Create(BookmarkInterfaceParameters(key.toStdString()));
			updateBookmark();
		}
	}
	else if(stateMachine.getCurrentStateName()==EDIT_STATE_NAME)
	{
		stateMachine.transferToState(EDITCANCEL_STATE_NAME,nullptr);
	}
}

void MainWindow::onActionLoad()
{
	QString filePath=QFileDialog::getOpenFileName(this,tr("Open File"),".");
	if(!filePath.isEmpty())
	{
		this->load(filePath.toStdString());
	}
}
void MainWindow::onActionSave()
{
	this->save(DEFAULT_MEMO_FILE_NAME);
	this->statusBar()->showMessage("Saved.");
}
void MainWindow::onActionSaveAs()
{
	QString filePath=QFileDialog::getSaveFileName(this,tr("Save File"),".","xml");
	if(!filePath.isEmpty())
	{
		this->save(filePath.toStdString());
		this->statusBar()->showMessage("Saved as "+filePath);
	}
}
void MainWindow::onActionQuit()
{

	this->close();
}
void MainWindow::setMemoInterfaceFromProvider(const std::shared_ptr<MemoInterfaceProvider> &provider)
{
	MainWindow::memoInterface=std::move(provider->getMemoInterface());
}
void MainWindow::setBookmarkInterfaceFromProvider(const std::shared_ptr<BookmarkInterfaceProvider> &provider)
{
	MainWindow::bookmarkInterface=std::move(provider->getBookmarkInterface());
}
void MainWindow::setHistoryInterfaceFromProvider(const std::shared_ptr<HistoryInterfaceProvider> &provider)
{
	MainWindow::historyInterface=std::move(provider->getHistoryInterface());
}
void MainWindow::displayKeyAndValue(const QString &key)
{
	std::string keyResult=key.toStdString();
	std::string valueResult=memoInterface->Retrieve(MemoInterfaceParameters(keyResult)).getValue();
	ui->value_text->setPlainText(QString::fromStdString(valueResult));
	ui->key_input_line->setText(key);
}

void MainWindow::load(const std::string &filename)
{
	this->onTriggered(UI_LOAD_LISTENER_NAME,filename);

	updateBookmark();
	updateHistory();

}
void MainWindow::save(const std::string &filename)
{
	this->onTriggered(UI_SAVE_LISTENER_NAME,filename);
}
void MainWindow::closeEvent(QCloseEvent *event)
{
	QMessageBox::StandardButton standardButton=QMessageBox::information(this,
																		tr("Question"),
																		tr("Do you want to save the memo ?"),
																		QMessageBox::Yes|QMessageBox::No,
																		QMessageBox::Yes);
	if(standardButton==QMessageBox::Yes)
	{
		onActionSaveAs();
	}
	QWidget::closeEvent(event);
}
