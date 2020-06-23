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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionExit;
    QAction *actionImport_TXT_file;
    QAction *actionImport_CSV_File;
    QWidget *centralWidget;
    QPushButton *pushButton;
    QLabel *label;
    QTableView *tableView;
    QTextEdit *textEdit;
    QComboBox *comboBox;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuGenerate_New_Dict;
    QMenu *menuSystem;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(570, 480);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionImport_TXT_file = new QAction(MainWindow);
        actionImport_TXT_file->setObjectName(QString::fromUtf8("actionImport_TXT_file"));
        actionImport_CSV_File = new QAction(MainWindow);
        actionImport_CSV_File->setObjectName(QString::fromUtf8("actionImport_CSV_File"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(470, 380, 61, 31));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 370, 71, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("Malgun Gothic Semilight"));
        font.setPointSize(11);
        label->setFont(font);
        tableView = new QTableView(centralWidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(40, 20, 491, 351));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(110, 380, 241, 31));
        comboBox = new QComboBox(centralWidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(370, 380, 87, 21));
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 570, 26));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuGenerate_New_Dict = new QMenu(menuFile);
        menuGenerate_New_Dict->setObjectName(QString::fromUtf8("menuGenerate_New_Dict"));
        menuSystem = new QMenu(menuBar);
        menuSystem->setObjectName(QString::fromUtf8("menuSystem"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuSystem->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(menuGenerate_New_Dict->menuAction());
        menuFile->addSeparator();
        menuGenerate_New_Dict->addAction(actionImport_TXT_file);
        menuGenerate_New_Dict->addAction(actionImport_CSV_File);
        menuSystem->addAction(actionExit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionOpen->setText(QApplication::translate("MainWindow", "Open CSV Dict", nullptr));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", nullptr));
        actionImport_TXT_file->setText(QApplication::translate("MainWindow", "Import TXT File", nullptr));
        actionImport_CSV_File->setText(QApplication::translate("MainWindow", "Import CSV File", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "Search", nullptr));
        label->setText(QApplication::translate("MainWindow", "Patterns:", nullptr));
        comboBox->setItemText(0, QApplication::translate("MainWindow", "Top-N", nullptr));
        comboBox->setItemText(1, QApplication::translate("MainWindow", "5", nullptr));
        comboBox->setItemText(2, QApplication::translate("MainWindow", "10", nullptr));
        comboBox->setItemText(3, QApplication::translate("MainWindow", "15", nullptr));
        comboBox->setItemText(4, QApplication::translate("MainWindow", "20", nullptr));
        comboBox->setItemText(5, QApplication::translate("MainWindow", "25", nullptr));
        comboBox->setItemText(6, QApplication::translate("MainWindow", "30", nullptr));
        comboBox->setItemText(7, QApplication::translate("MainWindow", "custom", nullptr));

        menuFile->setTitle(QApplication::translate("MainWindow", "Dictionary", nullptr));
        menuGenerate_New_Dict->setTitle(QApplication::translate("MainWindow", "Generate New Dict", nullptr));
        menuSystem->setTitle(QApplication::translate("MainWindow", "System", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
