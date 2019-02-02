/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLoad;
    QAction *actionSave;
    QAction *actionExit;
    QAction *actionQuit;
    QAction *actionSaveAs;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QSplitter *splitter;
    QWidget *widget;
    QVBoxLayout *verticalLayout_6;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_2;
    QLabel *search_label;
    QHBoxLayout *horizontalLayout;
    QLineEdit *search_input_line;
    QPushButton *search_button;
    QListWidget *search_result_list;
    QTabWidget *history_and_bookmark_tabs;
    QWidget *history_tab;
    QVBoxLayout *verticalLayout_3;
    QListWidget *history_list;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *history_delete_button;
    QPushButton *history_clear_button;
    QWidget *bookmark_tab;
    QVBoxLayout *verticalLayout_5;
    QListWidget *bookmark_list;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *bookmark_delete_button;
    QPushButton *bookmark_clear_button;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout;
    QLabel *key_label;
    QHBoxLayout *horizontalLayout_7;
    QLineEdit *key_input_line;
    QPushButton *add_button;
    QPushButton *delete_button;
    QLabel *value_label;
    QPlainTextEdit *value_text;
    QVBoxLayout *verticalLayout_7;
    QLabel *opeartion_label;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *edit_save_value_button;
    QPushButton *bookmark_cancel_value_button;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(848, 797);
        QFont font;
        font.setFamily(QString::fromUtf8("Consolas"));
        MainWindow->setFont(font);
        actionLoad = new QAction(MainWindow);
        actionLoad->setObjectName(QString::fromUtf8("actionLoad"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionSaveAs = new QAction(MainWindow);
        actionSaveAs->setObjectName(QString::fromUtf8("actionSaveAs"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        widget = new QWidget(splitter);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        verticalLayout_6 = new QVBoxLayout(widget);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        widget_3 = new QWidget(widget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(3);
        sizePolicy1.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy1);
        horizontalLayout_5 = new QHBoxLayout(widget_3);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        search_label = new QLabel(widget_3);
        search_label->setObjectName(QString::fromUtf8("search_label"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Consolas"));
        font1.setPointSize(9);
        search_label->setFont(font1);

        verticalLayout_2->addWidget(search_label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        search_input_line = new QLineEdit(widget_3);
        search_input_line->setObjectName(QString::fromUtf8("search_input_line"));

        horizontalLayout->addWidget(search_input_line);

        search_button = new QPushButton(widget_3);
        search_button->setObjectName(QString::fromUtf8("search_button"));
        search_button->setFont(font);

        horizontalLayout->addWidget(search_button);


        verticalLayout_2->addLayout(horizontalLayout);

        search_result_list = new QListWidget(widget_3);
        search_result_list->setObjectName(QString::fromUtf8("search_result_list"));

        verticalLayout_2->addWidget(search_result_list);


        horizontalLayout_5->addLayout(verticalLayout_2);


        verticalLayout_6->addWidget(widget_3);

        history_and_bookmark_tabs = new QTabWidget(widget);
        history_and_bookmark_tabs->setObjectName(QString::fromUtf8("history_and_bookmark_tabs"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(2);
        sizePolicy2.setHeightForWidth(history_and_bookmark_tabs->sizePolicy().hasHeightForWidth());
        history_and_bookmark_tabs->setSizePolicy(sizePolicy2);
        history_and_bookmark_tabs->setFont(font);
        history_tab = new QWidget();
        history_tab->setObjectName(QString::fromUtf8("history_tab"));
        verticalLayout_3 = new QVBoxLayout(history_tab);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        history_list = new QListWidget(history_tab);
        history_list->setObjectName(QString::fromUtf8("history_list"));

        verticalLayout_3->addWidget(history_list);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        history_delete_button = new QPushButton(history_tab);
        history_delete_button->setObjectName(QString::fromUtf8("history_delete_button"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(history_delete_button->sizePolicy().hasHeightForWidth());
        history_delete_button->setSizePolicy(sizePolicy3);

        horizontalLayout_3->addWidget(history_delete_button);

        history_clear_button = new QPushButton(history_tab);
        history_clear_button->setObjectName(QString::fromUtf8("history_clear_button"));
        sizePolicy3.setHeightForWidth(history_clear_button->sizePolicy().hasHeightForWidth());
        history_clear_button->setSizePolicy(sizePolicy3);

        horizontalLayout_3->addWidget(history_clear_button);


        verticalLayout_3->addLayout(horizontalLayout_3);

        history_and_bookmark_tabs->addTab(history_tab, QString());
        bookmark_tab = new QWidget();
        bookmark_tab->setObjectName(QString::fromUtf8("bookmark_tab"));
        verticalLayout_5 = new QVBoxLayout(bookmark_tab);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        bookmark_list = new QListWidget(bookmark_tab);
        bookmark_list->setObjectName(QString::fromUtf8("bookmark_list"));

        verticalLayout_5->addWidget(bookmark_list);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        bookmark_delete_button = new QPushButton(bookmark_tab);
        bookmark_delete_button->setObjectName(QString::fromUtf8("bookmark_delete_button"));
        sizePolicy3.setHeightForWidth(bookmark_delete_button->sizePolicy().hasHeightForWidth());
        bookmark_delete_button->setSizePolicy(sizePolicy3);

        horizontalLayout_4->addWidget(bookmark_delete_button);

        bookmark_clear_button = new QPushButton(bookmark_tab);
        bookmark_clear_button->setObjectName(QString::fromUtf8("bookmark_clear_button"));
        sizePolicy3.setHeightForWidth(bookmark_clear_button->sizePolicy().hasHeightForWidth());
        bookmark_clear_button->setSizePolicy(sizePolicy3);

        horizontalLayout_4->addWidget(bookmark_clear_button);


        verticalLayout_5->addLayout(horizontalLayout_4);

        history_and_bookmark_tabs->addTab(bookmark_tab, QString());

        verticalLayout_6->addWidget(history_and_bookmark_tabs);

        splitter->addWidget(widget);
        widget_2 = new QWidget(splitter);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(2);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy4);
        verticalLayout = new QVBoxLayout(widget_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        key_label = new QLabel(widget_2);
        key_label->setObjectName(QString::fromUtf8("key_label"));

        verticalLayout->addWidget(key_label);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        key_input_line = new QLineEdit(widget_2);
        key_input_line->setObjectName(QString::fromUtf8("key_input_line"));

        horizontalLayout_7->addWidget(key_input_line);

        add_button = new QPushButton(widget_2);
        add_button->setObjectName(QString::fromUtf8("add_button"));

        horizontalLayout_7->addWidget(add_button);

        delete_button = new QPushButton(widget_2);
        delete_button->setObjectName(QString::fromUtf8("delete_button"));

        horizontalLayout_7->addWidget(delete_button);


        verticalLayout->addLayout(horizontalLayout_7);

        value_label = new QLabel(widget_2);
        value_label->setObjectName(QString::fromUtf8("value_label"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(1);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(value_label->sizePolicy().hasHeightForWidth());
        value_label->setSizePolicy(sizePolicy5);

        verticalLayout->addWidget(value_label);

        value_text = new QPlainTextEdit(widget_2);
        value_text->setObjectName(QString::fromUtf8("value_text"));

        verticalLayout->addWidget(value_text);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        opeartion_label = new QLabel(widget_2);
        opeartion_label->setObjectName(QString::fromUtf8("opeartion_label"));

        verticalLayout_7->addWidget(opeartion_label);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        edit_save_value_button = new QPushButton(widget_2);
        edit_save_value_button->setObjectName(QString::fromUtf8("edit_save_value_button"));

        horizontalLayout_6->addWidget(edit_save_value_button);

        bookmark_cancel_value_button = new QPushButton(widget_2);
        bookmark_cancel_value_button->setObjectName(QString::fromUtf8("bookmark_cancel_value_button"));

        horizontalLayout_6->addWidget(bookmark_cancel_value_button);


        verticalLayout_7->addLayout(horizontalLayout_6);


        verticalLayout->addLayout(verticalLayout_7);

        splitter->addWidget(widget_2);

        horizontalLayout_2->addWidget(splitter);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 848, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionLoad);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSaveAs);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);

        retranslateUi(MainWindow);

        history_and_bookmark_tabs->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionLoad->setText(QApplication::translate("MainWindow", "Load", nullptr));
        actionSave->setText(QApplication::translate("MainWindow", "Save", nullptr));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", nullptr));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", nullptr));
        actionSaveAs->setText(QApplication::translate("MainWindow", "Save as", nullptr));
        search_label->setText(QApplication::translate("MainWindow", "Search:", nullptr));
        search_button->setText(QApplication::translate("MainWindow", "Search", nullptr));
        history_delete_button->setText(QApplication::translate("MainWindow", "Delete", nullptr));
        history_clear_button->setText(QApplication::translate("MainWindow", "Clear", nullptr));
        history_and_bookmark_tabs->setTabText(history_and_bookmark_tabs->indexOf(history_tab), QApplication::translate("MainWindow", "History", nullptr));
        bookmark_delete_button->setText(QApplication::translate("MainWindow", "Delete", nullptr));
        bookmark_clear_button->setText(QApplication::translate("MainWindow", "Clear", nullptr));
        history_and_bookmark_tabs->setTabText(history_and_bookmark_tabs->indexOf(bookmark_tab), QApplication::translate("MainWindow", "Bookmark", nullptr));
        key_label->setText(QApplication::translate("MainWindow", "Key:", nullptr));
        add_button->setText(QApplication::translate("MainWindow", "Add", nullptr));
        delete_button->setText(QApplication::translate("MainWindow", "Delete", nullptr));
        value_label->setText(QApplication::translate("MainWindow", "Value:", nullptr));
        opeartion_label->setText(QApplication::translate("MainWindow", "Operation:", nullptr));
        edit_save_value_button->setText(QApplication::translate("MainWindow", "Edit", nullptr));
        bookmark_cancel_value_button->setText(QApplication::translate("MainWindow", "Bookmark", nullptr));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
