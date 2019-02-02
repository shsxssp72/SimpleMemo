#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <functional>
#include <QListWidgetItem>
#include "Source/Core/MemoCore.h"
#include "../Interface/Memo/AccessMemoInterface.h"
#include "../Utility/EventMonitor.h"
#include "../Utility/StateMachine.h"

class MainController;

namespace Ui
{
	class MainWindow;
}

class MainWindow:public QMainWindow,
		public ListenerBase,
		public MonitorBase
{
Q_OBJECT

public:
	explicit MainWindow(QWidget *parent=nullptr);
	~MainWindow();
	void InitializeInitFunc();
	void InitConnection(MainController *mainController);
	void InitComponents();
	void setMemoInterfaceFromProvider(const std::shared_ptr<MemoInterfaceProvider> &provider);
	void setBookmarkInterfaceFromProvider(const std::shared_ptr<BookmarkInterfaceProvider> &provider);
	void setHistoryInterfaceFromProvider(const std::shared_ptr<HistoryInterfaceProvider> &provider);
public slots:
	void updateBookmark();
	void updateHistory();
private slots:
	void onSearchTextChanged(const QString &text);
	void onKeyListItemClicked(QListWidgetItem *item);
	void onClickAdd();
	void onClickDelete();
	void onClickSearch();
	void onClickHistoryDelete();
	void onClickHistoryClear();
	void onClickBookmarkDelete();
	void onClickBookmarkClear();
	void onClickEditSaveValue();
	void onClickBookmarkCancelValue();
	void onActionLoad();
	void onActionSave();
	void onActionSaveAs();
	void onActionQuit();
private:
	void displayKeyAndValue(const QString &key);
	void load(const std::string &filename);
	void save(const std::string &filename);
protected:
	void closeEvent(QCloseEvent *event) override;
private:
	Ui::MainWindow *ui;
	std::list<std::function<void()>> initializeFunctions;
	std::shared_ptr<AccessMemoInterface> memoInterface;
	std::shared_ptr<AccessBookmarkInterface> bookmarkInterface;
	std::shared_ptr<AccessBookmarkInterface> historyInterface;
	StateMachine stateMachine;
};

#endif // MAINWINDOW_H
