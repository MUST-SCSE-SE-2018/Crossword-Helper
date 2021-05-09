#define _CRT_SECURE_NO_WARNINGS
#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<hash_map>
#include<time.h>
using namespace std;

/*
	Project TextSearch
	Author Name: Wang Yuyang (Kennard)
	StuID: 1809853Z-I011-0045
*/


class completion {

private:

	struct Word{
		string word;
		int rk;
	};

	vector<Word> display;
	hash_map<string, int> c_dict; 

public:

	string askForFile() {
		cout << "Please enter the file directory you want to import: " << endl;
		string fd = "";
		getline(cin, fd);
		return fd;
	}

	string *splitStr(string str, string token) {
		int len = str.length();
		int index = str.find(token);
		string* s = new string[2];
		s[0] = str.substr(0, index);
		s[1] = str.substr(index + 1, len - 1 - index);
		return s;
	}

	// use ascii code to modify strings
	void modifyStr(string &str) {

		if (str.find('/') != -1) {
			str = splitStr(str, "/")[0];
		}

		int pos = str.find('-');
		if (pos == 0) { 
			str.erase(0, 1);
			pos = str.find('-');
		}

		if (pos != -1) { 
			int comma = str.find(','); 
			while (comma != -1) { 
				str.erase(comma, 1); 
				comma = str.find(',');
			}
		}
		else {
			for (int i = 0; i < str.length(); ++i) {
				int index = (int)str[i];
				if (index >= 97 && index <= 122);
				else if (index >= 65 && index <= 90) {
					str[i] = str[i] + 32;   // A-Z to a-z
				}
				else if (index == 39) {
					if (str.length() < 5) {
						if (str.compare("'s") == 0) { str = "is"; break; }
						else if (str.compare("'ve") == 0) { str = "have"; break; }
						else if (str.compare("'re") == 0) { str = "are"; break; }
						else if (str.compare("'ll") == 0) { str = "will"; break; }
						else if (str.compare("'m") == 0) { str = "am"; break; }
						else if (str.compare("d'") == 0) { str = "do"; break; }
						else if (str.find("n't") != -1) { str = "not"; break; }
					}
					else if (str.compare("'d [= had]") == 0 || str.compare("'d [= would]") == 0) {
						if (str.compare("'d [= had]") == 0) { str = "had"; break; }
						if (str.compare("'d [= would]") == 0) { str = "would"; break; }
					}
					else {
						str.erase(i, str.length() - i);
						break;
					}
				}  // remove string after ' notation
				else {
					str.erase(i, 1);   // delete other prefix & suffix
					--i;
				}
			}
		}
	}

	void fill_completions(string fd) {

		// start to record time
		clock_t start = clock();

		// open the file
		ifstream fin(fd);

		if (fin.fail()) {
			string err = "Fail to load " + fd + ". Please check your directory!";
			throw invalid_argument(err);
		}


		// read the file
		while (!fin.eof()) {
			string tmpvoc;
			fin >> tmpvoc;		
			modifyStr(tmpvoc); 

			// skip empty string
			if (tmpvoc.length() == 0)
				continue;

			// store the number of appearing string via hash map
			if (c_dict.find(tmpvoc) == c_dict.end()) {
				c_dict[tmpvoc] = 1;  // not find set 1
			}
			else {
				c_dict[tmpvoc]++;	// rank + 1
			}

		}
		fin.close();

		clock_t end = clock();
		double cost = end - start;

		cout << "Load " << fd << " successfully! Time cost: " << cost << " ms." << endl;
		cout << endl;

		fileWrite();
		
	}

	void importCSV(string fd) {

		clock_t start = clock();

		ifstream csvfin(fd);

		if (csvfin.fail()) {
			string err = "Fail to import " + fd + ". Please check your directory!";
			throw invalid_argument(err);
		}

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

		clock_t end = clock();
		double cost = end - start;
		cout << "Import " << fd << " successfully! Time cost: " << cost << " ms." << endl;
		cout << endl;
	
		fileWrite();
		
	}

	hash_map<string, int> findWord() {

		hash_map<string, int> tmp;
		string flag = "";
		
		do{
			cout << "Please input character and its position like 'u,3'" << endl;
			string str = "";
			cin >> str;

			cout << "Continue ? (Y/N)" << endl;
			cin >> flag;

			clock_t start = clock();

			int pos = atoi(splitStr(str, ",")[1].c_str());
			string ch = splitStr(str, ",")[0];

			hash_map<string, int> ::iterator key;

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

			clock_t end = clock();
			double cost = end - start;

			cout << "Search Completed ! Time cost: " << cost << " ms." << endl;
			cout << endl;

		} while (flag.compare("Y") == 0 || flag.compare("y") == 0);

		return tmp;
	}

	void rankSort(hash_map<string, int> hash) {

		hash_map<string, int>::iterator it;
		hash_map<string, int>::iterator key;
		clock_t start = clock();

		if (hash.empty()) {
			cout << "Sorry, our dictionary cannot find that word!" << endl;
		}
		
		while (!hash.empty()) {
			int max = 0;
			it = hash.begin();
			while (it != hash.end()) {
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

			hash.erase(key);
		}

		clock_t end = clock();
		double cost = end - start;
		cout << "Sort Completed ! Time cost: " << cost << " ms." << endl;
		cout << endl;

		for (unsigned i = 0; i < display.size(); ++i)
			cout << display[i].word << ", " << display[i].rk << endl;
		
	}

	void fileWrite() {

		clock_t start = clock();
		ofstream fout("newsDict.csv");
		hash_map<string, int> ::iterator key;
		key = c_dict.begin();

		while (key != c_dict.end()) {
			fout << key->first << "," << key->second << endl;
			key++;
		}

		fout.close();

		clock_t end = clock();
		double cost = end - start;
		cout << "Dictionary Completed ! Time cost: " << cost << " ms." << endl;
		cout << endl;
	}

}; // end the class


// just for testing
int main() {

	// import file
	while (true) {
		try
		{
			completion c;
			c.fill_completions(c.askForFile());
			c.importCSV(c.askForFile());
			c.rankSort(c.findWord());

			break;
		}
		catch (const std::exception& e)
		{
			cerr << e.what() << endl;
			cerr << endl;
		}
	}

	return 0;
} // end the main  
