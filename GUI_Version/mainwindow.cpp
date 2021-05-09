#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QStandardItem>
#include<QFileDialog>
#include<QMessageBox>
#include<qinputdialog.h>

#include<iostream>
#include<string>
#include<regex>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayCSVFile(){

    // display content
    QStandardItemModel *model = new QStandardItemModel;
    model->setColumnCount(2);
    model->setHeaderData(0,Qt::Horizontal,tr("Word"));
    model->setHeaderData(1,Qt::Horizontal,tr("Rank"));

    ifstream fin("newsDict.csv");

    while(!fin.eof()){
        string str = "";
        getline(fin,str);

        string word = splitStr(str,",")[0];
        string rank = splitStr(str,",")[1];

        // add items into model
        QStandardItem* item1 = new QStandardItem(word.c_str());
        QStandardItem* item2 = new QStandardItem(rank.c_str());
        QList<QStandardItem*> item;
        item << item1 << item2;
        model->appendRow(item);
    }

    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // fill the whole screen

}

void MainWindow::openFile(string suff){
    // create a model
    QStandardItemModel *model = new QStandardItemModel;
    model->setColumnCount(2);
    model->setHeaderData(0,Qt::Horizontal,tr("Word"));
    model->setHeaderData(1,Qt::Horizontal,tr("Rank"));

    // open file
    QString dir = QFileDialog::getOpenFileName(this); // get directory
    QString fileName = QFileInfo(dir).fileName(); // get file name
    string suffix = splitStr(fileName.toStdString(),".")[1];  // get suffix

    if (suffix.compare(suff)!=0)
    {
        QMessageBox::information(nullptr, "Error", "Please choose " + QString::fromStdString(suff) +" file!");
    }
    else
    {
        ifstream fin(dir.toStdString());

        while(!fin.eof()){
            string str = "";
            getline(fin,str);

            string word = splitStr(str,",")[0];
            string rank = splitStr(str,",")[1];

            // add items into model
            QStandardItem* item1 = new QStandardItem(word.c_str());
            QStandardItem* item2 = new QStandardItem(rank.c_str());
            QList<QStandardItem*> item;
            item << item1 << item2;
            model->appendRow(item);

        }

        // display
        ui->tableView->setModel(model);
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }


}

void MainWindow::on_actionOpen_triggered()
{
    openFile("csv");
}

void MainWindow::on_actionExit_triggered()
{
    exit(0);
}

void MainWindow::on_actionImport_TXT_file_triggered()
{
    // open file
    QString dir = QFileDialog::getOpenFileName(this);
    QString fileName = QFileInfo(dir).fileName();
    string suffix = splitStr(fileName.toStdString(),".")[1];  // get suffix txt

    if (suffix.compare("txt")!=0)
    {
        QMessageBox::information(nullptr, "Error", "Please choose TXT file!"); // replace NULL with nullptr
    }
    else
    {
        fill_completions(dir.toStdString()); // read txt
        displayCSVFile();
    }
}

void MainWindow::on_actionImport_CSV_File_triggered()
{
    // open file
    QString dir = QFileDialog::getOpenFileName(this);
    QString fileName = QFileInfo(dir).fileName();
    string suffix = splitStr(fileName.toStdString(),".")[1];  // get suffix csv

    if (suffix.compare("csv")!=0)
    {
        QMessageBox::information(nullptr, "Error", "Please choose CSV file!");
    }
    else
    {
        importCSV(dir.toStdString()); // read csv
        displayCSVFile();
    }
}

void MainWindow::displayDict(unsigned int topN){
    // display content
    QStandardItemModel *model = new QStandardItemModel;
    model->setColumnCount(2);
    model->setHeaderData(0,Qt::Horizontal,tr("Word"));
    model->setHeaderData(1,Qt::Horizontal,tr("Rank"));

    if(!display.empty()){
        unsigned int len = 0;
        if(topN == 0){len = display.size();}
        else if(topN == 7){
            // reference: https://blog.csdn.net/qq_42153903/java/article/details/98518190
            bool ok;
            QString text = QInputDialog::getText(this, "Use Rank","Please enter N", QLineEdit::Normal, nullptr, &ok);

            /* only numbers is valid */
            // reference: https://blog.csdn.net/weixin_42416780/article/details/89791826
            regex pattern("^[1-9][0-9]*");
            smatch result;
            string str = text.toStdString();
            bool ismatch = regex_match(str, result, pattern);
            unsigned int N = 0;

            if (ok && !text.isEmpty() && ismatch){
                N = atoi(str.c_str());
            }
            else{
                QMessageBox::information(nullptr, "Error", "Please enter a number!");
            }

            if(display.size() > N){ len = N; } // display is larger than N
            else{ len = display.size();}
        }
        else{
            if(display.size() > 5*topN){ len = 5*topN; } // display is larger than N
            else{ len = display.size();}
        }

        for(unsigned i = 0; i < len; ++i){

            string word = display[i].word;
            string rank = to_string(display[i].rk);

            // add items into model
            QStandardItem* item1 = new QStandardItem(word.c_str());
            QStandardItem* item2 = new QStandardItem(rank.c_str());
            QList<QStandardItem*> item;
            item << item1 << item2;
            model->appendRow(item);
        }
    }
    else{
        QMessageBox::information(nullptr, "Tips", "Sorry, we cannot find the word in dictionary!");
    }

    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // fill the whole screen

}

void MainWindow::on_pushButton_clicked()
{
   string str = ui->textEdit->toPlainText().toStdString(); // get text content

   // order by rank
   rankSort(findWord(str));

   // get top-n rank
   unsigned int index = ui->comboBox->currentIndex();

   // display
   displayDict(index);

}


