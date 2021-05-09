#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QMainWindow>
#include<QMessageBox>

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<map>
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public: 
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void displayCSVFile();

    void displayDict(unsigned int topN);

    void openFile(string suff);

    void on_pushButton_clicked();

    void on_actionOpen_triggered();

    void on_actionExit_triggered();

    void on_actionImport_TXT_file_triggered();

    void on_actionImport_CSV_File_triggered();

private:
    Ui::MainWindow *ui;

// original class completion
private:

    // word-rank pair
    struct Word{
        string word;
        int rk;
    };

    vector<Word> display;  // for display
    map<string, int> c_dict;  // real dictionary, ordered by key


public:

    // mainly used for separating comma in one word
    string *splitStr(string str, string token) {
        unsigned int len = str.length();  // attention: length() in Qt return unsigned pointer
        unsigned int index = str.find(token);
        string* s = new string[2];
        s[0] = str.substr(0, index);
        s[1] = str.substr(index + 1, len - 1 - index);
        return s;
    }

    // used for separating multi-word string
    vector<string> splitQuery(string str, string token){
        vector<string> v;
        unsigned index = str.find(token);

        while(index!=UINT_MAX){
            v.push_back(str.substr(0,index));
            str.erase(0,index + 1); // delete token
            index = str.find(token);
        }
        v.push_back(str);

        return v;
    }

    // use ascii code to modify strings
    void modifyStr(string &str) {

        if (str.find('/') != UINT_MAX) {
            str = splitStr(str, "/")[0];  // use UINT_MAX instead of -1
        }

        // delete redundant hyphen
        unsigned int pos = str.find('-');
        while (pos == 0) {
            str.erase(0, 1);
            pos = str.find('-');
        }

        // retain the string who has the hyphen
        if (pos != UINT_MAX) {
            unsigned int comma = str.find(',');
            while (comma != UINT_MAX) {
                str.erase(comma, 1);   // clear the comma
                comma = str.find(',');
            }
        }

        else{
            for (unsigned int i = 0; i < str.length(); ++i) {
                int index = str[i];
                if (index >= 97 && index <= 122);
                else if (index >= 65 && index <= 90) {
                    str[i] = str[i] + 32;   // A-Z to a-z
                }
                else if (index == 39) {
                    if (str.length() < 5) {
                        // transformation for short words
                        if (str.compare("'s") == 0) { str = "is"; break; }
                        else if (str.compare("'ve") == 0) { str = "have"; break; }
                        else if (str.compare("'re") == 0) { str = "are"; break; }
                        else if (str.compare("'ll") == 0) { str = "will"; break; }
                        else if (str.compare("'m") == 0) { str = "am"; break; }
                        else if (str.compare("'em") == 0) { str = "them"; break; }
                        else if (str.compare("d'") == 0) { str = "do"; break; }
                        else if (str.compare("n't") == 0) { str = "not"; break; }
                        else{str.erase(i, str.length() - i); break;}
                    }
                    else if (str.compare("'d [= had]") == 0 || str.compare("'d [= would]") == 0) {
                        // 2 special cases
                        if (str.compare("'d [= had]") == 0) { str = "had"; break; }
                        if (str.compare("'d [= would]") == 0) { str = "would"; break; }
                    }
                    else {
                        str.erase(i, str.length() - i);
                        break;
                    }

                }  // case '
                else {
                    str.erase(i, 1);   // delete other prefix & suffix
                    --i;
                } // remove string after ' notation
            }// end for
        }
    }

    void fill_completions(string fd) {

        // open the file
        ifstream fin(fd);

        // read the file
        while (!fin.eof()) {
            string tmpvoc;
            fin >> tmpvoc;
            modifyStr(tmpvoc);

            // skip empty string
            if (tmpvoc.length() == 0)
                continue;

            // use array insertion: store the number of appearing string
            if (c_dict.find(tmpvoc) == c_dict.end()) {
                c_dict[tmpvoc] = 1;  // not find set 1
            }
            else {
                c_dict[tmpvoc]++;	// rank + 1
            }

        }
        fin.close();

        fileWrite();

    }

    void importCSV(string fd) {

        ifstream csvfin(fd);

        // read csv file
        while (!csvfin.eof()) {
            string rowdata = "";
            getline(csvfin, rowdata);

            string vocabulary = splitStr(rowdata, ",")[0];
            int times = atoi(splitStr(rowdata, ",")[1].c_str());

            modifyStr(vocabulary);

            // skip empty string
            if (vocabulary.length() == 0)
                continue;

            // store the number of appearing string via hash map
            if (c_dict.find(vocabulary) == c_dict.end()) {
                c_dict[vocabulary] = times; // not find set 1
            }
            else {
                c_dict[vocabulary] += times;	// rank + 1
            }

        }
        csvfin.close();

        fileWrite();

    }

    map<string, int> findWord(string str) {

        map<string, int> tmp;

        if(c_dict.empty()){
            QMessageBox::information(nullptr,"Tips","Please import dictionary first!");
        }
        else{

            if (str.empty()) {
                QMessageBox::information(nullptr, "Tips", "Please enter query string!");
            }
            else{

                vector<string> v;
                v = splitQuery(str," ");
                unsigned int len = v.size();

                for(unsigned int i = 0; i < len; ++i){

                    string ch = splitStr(v[i], ",")[0];
                    unsigned long int pos = strtoul(splitStr(v[i], ",")[1].c_str(),nullptr,0); // str to unsigned long (cstring, pointer, digit type)

                    map<string, int> ::iterator key;

                    if (tmp.empty()) {
                        key = c_dict.begin();
                        while (key != c_dict.end()) {
                            if (key->first.length() >= pos && key->first.substr(pos - 1, 1).compare(ch) == 0) {
                                tmp[key->first] = key->second;
                            }
                            ++key;
                        }
                    }
                    else {
                        key = tmp.begin();
                        while (key != tmp.end()) {
                            if (key->first.length() >= pos) {
                                if (key->first.substr(pos - 1, 1).compare(ch) == 0) { key++; }
                                else { tmp.erase(key++); }
                            }
                            else {
                                tmp.erase(key++);
                            }
                        }
                    }
                }
            }

        }

        return tmp;
    }

    void rankSort(map<string, int> m) {

        // clear display
        display.clear();

        map<string, int>::iterator it;
        map<string, int>::iterator key;

        while (!m.empty()) {
            int max = 0;
            it = m.begin();
            while (it != m.end()) {
                if (it->second > max) {
                    max = it->second;
                    key = it;
                }
                it++;
            }

            Word w;
            w.word = key->first;
            w.rk = key->second;

            display.push_back(w);

            m.erase(key);
        }

    }

    void fileWrite() {

        ofstream fout("newsDict.csv");
        map<string, int> ::iterator key;
        key = c_dict.begin();

        while (key != c_dict.end()) {
            fout << key->first << "," << key->second << endl;
            key++;
        }

        fout.close();
    }

};

#endif // MAINWINDOW_H
