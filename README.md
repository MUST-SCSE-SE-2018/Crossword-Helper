# Crossword-Helper

> Kennard is a playful boy who is very interested in crossword solving ( a kind of puzzle ), 
> but he is not an expert in remembering English words. Kennard decided to design a 
> software, which could help to solve crossword puzzle.
> 
> ![puzzle](https://kennardwang.github.io/ImageSource/Crossword-Helper/CrosswordsPuzzle.png)

------

### GUI Demo

![demo](https://kennardwang.github.io/ImageSource/Crossword-Helper/CrosswordsDemo.png)

------

### GUI Development Environment

| Description | Specification |
|:---:|:---:|
| System | Windows 10 |
| Language | C++ |
| IDE | Qt Creator 4.8.0 (Enterprise) |

------

### GUI User Manual

1. [Download](https://github.com/KennardWang/Crossword-Helper/releases) the latest GUI version.
2. Run **TextSearch_GUI.exe**.

![um](https://kennardwang.github.io/ImageSource/Crossword-Helper/um1.png)

3. Import ***.txt*** or ***.csv*** file to generate a new dictionary. All the file directories must be English!

![um](https://kennardwang.github.io/ImageSource/Crossword-Helper/um2.png)

4. After importing, you will see a display of generated **newDict.csv** here. For the next time, you can use this dictionary by importing directly.

![um](https://kennardwang.github.io/ImageSource/Crossword-Helper/um3.png)

![um](https://kennardwang.github.io/ImageSource/Crossword-Helper/um4.png)

5. You can also browse it through **Open CSV Dict** function.

![um](https://kennardwang.github.io/ImageSource/Crossword-Helper/um5.png)

6. Search : You can enter a query string in a fixed format to search. For each pattern, please use character and integer number to represent which character in which position, use a comma to split it. Patterns are separated by space. For example, if you want to find the words like ***XXuaXXX*** ( ***u*** is the 3rd character, ***a*** is the 4th character, ***X*** means unknown character ), you need write **u,3 a,4** ( regardless of order between 2 patterns ) in the text field, and click search button.

![um](https://kennardwang.github.io/ImageSource/Crossword-Helper/um6.png)

7. Top-N rank selection: Before searching, you can select to display the Top N results of all the searched words. **Custom** means you can determine any number N by yourself.

![um](https://kennardwang.github.io/ImageSource/Crossword-Helper/um7.png)

8. Click **Exit** to end up the program.

![um](https://kennardwang.github.io/ImageSource/Crossword-Helper/um8.png)

9. If your query operation is incorrect, the display window will be cleared. But do not worry, if you have imported data file and you still do not exit the program, the content is still alive. You just need to enter your query operation again and it will manifest.

------

### GUI Data Structure
+ UI

| Variable / Function Name |	Modifier | Element Type |	Function Return Type | Function Parameter | Description |
|:---:|:---:|:---:|:---:|:---:|:---:|
| MainWindow()	| public | / | / | Qwidget *parent | Constructor |
| ~MainWindow()	| public | / | / | / | Destructor |
| displayCSVFile()	|private|	/|void|	void|	Slot: display the content of **newDict.csv** |
| openFile() | private |	/	| void | string suff |Slot: open file with corresponding suffix ( If the suff is **CSV**, then open ***.csv*** file )|
| on_actionOpen_triggered() | private|	/|	void|	void|	Slot: Execute openFile("csv") |
| on_actionExit_triggered() |	private	|/|	void| void|	Slot: End up the program |
| on_actionImport_TXT_file_triggered() |	private|	/|	void	|void	|Slot: read ***.txt*** file into the new dictionary and display the newDict |
| on_actionImport_CSV_File_triggered() |	private	| /|	void|	void|	Slot: read ***.csv*** file into the new dictionary and display the newDict |
| displayDict() |	private	|/|	void|	unsigned int topN	|Slot: display the final result of searched words |
| On_pushButton_clicked() | private | / |	void |void | Slot: confirm to search |
| ui | private	| Ui:MainWindow* |/| / | UI pointer, can be used to point to any components of the UI |

+ Original Class

| Variable / Function Name |	Modifier | Element Type |	Function Return Type | Function Parameter | Description |
|:---:|:---:|:---:|:---:|:---:|:---:|
| /	| private	| struct Word	| /|	/|	/|
| display	| private |	vector\<Word> |	/|	/|	/|
| c_dict | private | map<string,int>	| /	|/	|Use map data structure: dictionary will be ordered by alphabet of key|
| splitStr() | public |	/	|string* | string str, string token	|/ |
| splitQuery() | public |	/|	vector\<string>|	string str, string token |Used for separating multi-word string like query string line|
| modifyStr()	| public | / |	void	| string &str	| Dealing with problems of unsigned integer: replace -1 with UINT_MAX|
| fill_completions() | public |	/	| void |	string fd	| / |
| importCSV()	| public	| /| 	void|	string fd	|/|
| findWord() |	public	|/|	map<string,int>|	string str	|According to query string ( more than one patterns ) to search correct words |
| rankSort() |	public|	/|	int|	map<string,int> hash	|/|
| fileWrite() |	public|	/|	void	|void	|/|
| main() |	/	|/	|int|	void	|Execute program and show the main window|

------

### GUI Core Algorithm
> Similar to **Console Version**, I replace **hash_map** with **map<string,int>** because map uses **Red Black Tree** to sort key in ASCII order automatically. The complexity of N-word insertion is ***O(NlogN)***, still less than sort ***O(0.01N^2)***. The overall complexity is:
>
> **N x O(1) [read file] + O(NlogN) [insert key] + N x O(1) [write dictionary] + O(N) [search] + O(0.01N^2) [sort] ~= O(0.01N^2)**

------

### GUI Feature:
+ GUI
> Easier for user to use program ( without using command ). All the function can be implemented by mouse event and key board event, and it looks nice as well.

+ ASCII order dictionary
> Most normal dictionaries are in ascii order. Compared to console version, this version has implemented this feature at a very low cost of time.

+ Dictionary display
> My program implements open file function to let you browse your dictionary, and at importing part, the real-time newDict will be displayed when you import a new dictionary to combine with the old one.

+ Top N rank
> Users can choose to display results with N-top rank or without N-top rank, or in custom. However, if the total number is less than N, it will display all the results. If there are no results, the program will prompt you with a message dialog.

+ Exception Detection
> A message dialog will show up to help you while you are doing an incorrect operation.

------

### CLI Development Environment

| Description | Specification |
|:---:|:---:|
| System | Windows 10 |
| Language | C++ |
| IDE | Visual Studio 2017 (Community) |

------

### CLI User Manual
1. Please put the test file ( **test.txt** and **dictionary.csv** ) into the folder **Console_Version**.

![um](https://kennardwang.github.io/ImageSource/Crossword-Helper/um9.png)

2. Open source code via IDE ( Recommend **Visual Studio 2017** ).
3. Run it and enter text file with ***.txt*** suffix.

![um](https://kennardwang.github.io/ImageSource/Crossword-Helper/um10.png)

4. Then enter **CSV** dictionary with ***.csv*** suffix. You must add two files ( 1 ***.txt*** and 1 ***.csv*** ) and then can continue.

![um](https://kennardwang.github.io/ImageSource/Crossword-Helper/um11.png)

5. If your directory is not correct, you will be allowed to input again. 

![um](https://kennardwang.github.io/ImageSource/Crossword-Helper/um12.png)

6. Then you can search words in fixed patterns. Using particular character and position number, as well as a comma between them. Please do not use space. If you want to input more than one pattern, you can type **Y/y** for continuing.

![um](https://kennardwang.github.io/ImageSource/Crossword-Helper/um13.png)

7. The result will be ordered in rank.

![um](https://kennardwang.github.io/ImageSource/Crossword-Helper/um14.png)

------

### CLI Data Structure

| Variable / Function Name |	Modifier | Element Type |	Function Return Type | Function Parameter | Description |
|:---:|:---:|:---:|:---:|:---:|:---:|
| /	| private |	struct Word	| /|	/	|Defined struct with 2 members: **string word** & **int rk** |
| display	|private|	vector\<Word>|	/|	/	|Used for displaying both words and its rank |
| c_dict |	private	|hash_map<string,int>|	/|	/|	Dictionary, used to store word data |
| askForFile() |public|	/|	string	|void	| Read the file directory users have entered|
| splitStr()|public|	/|	string*	|string str, string token	|Split a string to a string array by token |
| modifyStr()	|public	|/|	void	|string &str|	Modify string words by trimming redundant prefix & suffix and transform abbreviation to full word. Change Upper case character to lower case character|
| fill_completions() |	public	|/|	void	|string fd	|Read text file through given file directory, then modify them and store in the dictionary|
| importCSV() |	public|	/|	void	|string fd	|Read CSV dictionary through given file directory, then modify them and store in the dictionary|
| findWord() |public|	/|	hash_map<string,int>	|void	| According to inputted pattern to search correct words from dictionary and return these words|
| rankSort() | public	| /|	int	| hash_map<string,int> | hash	Rearrange those words searched by **findWord()** in rank order, then push them into vector **display** and output them |
| fileWrite() |	public |/|	void	|void|	Generate new dictionary based on **c_dict** |
| main() |	/	|/|	int|	void	|Test function|

------

### CLI Core Algorithm
1. Storage
> I use **hash_map<string,int> c_dict** as a dictionary, this data structure could record key-value pair without duplicate. It is based on hash value and linked list, which means the insertion procedure is very fast. When a new word comes in, we compute the hash value of the key, and then link the key-value pair to the corresponding node, so the complexity is **O(1)**.

2. Word Search
> We let users input fixed patterns including character and its exact position. Like **u,3**, it means we will find the word whose 3rd character is **u**. We use Sequential Search here, which has **O(N)** complexity average （ best case **O(1)**, worst case **O(N)** ）.

3. Rank Sort Complexity ( First Search Last Sort )
> + Selection Sort & Insertion Sort: **O(N^2)**
> + Merge Sort & Heap Sort: **O(NlogN)**
> + Quick Sort: **O(NlnN)**
> 
> All in all, time consumption is correlated to sort complexity, also based on size of N. The smaller N is, the faster the program will be. If we search words first, it will be faster because we know the accurate position of some characters and exclude most cases of words. 

4. Experiment
> We know that 'E' has the highest appearing rate (12.25%) in English words, so we assume we know the exact position of 'E' and count how many words ( allow repetition ).

| Position of E	| 1	| 2	| 3	| 4	| 5	| 6	| 7	| 8	| 9 |
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| Total words 12328	| 550 (4.46%)	| 1925 (15.6%) | 875 (7.1%) |	1542 (12.5%) | 1714 (13.9%)	| 1134 (9.2%)| 1027 (8.3%) | 756 (6.13%) | 527 (4.27%) |

> The result demonstrates clearly that the percentage of matching words has decreased to 10% around. We can compute the overall complexity is **O(N) [search] + O(0.01N^2) [use selection sort]**. However, if we use the original algorithm, the complexity will be **O(N^2) [sort] + O(N) [search]**. When N ~= 10000, our new algorithm is nearly 99 times faster than the old one.

------

### CLI Feature:
1. "Kit Class"
> Based on OOP concept, I design completion class and encapsulate correlated method into it. To solve sustainable problem, I prefer to use "kit class" concept. The class is regarded as a kit, the operation to object could be executed by calling class method, which you do not define function parameters and your main function will look briefly, too.

2. Complexity
> The total complexity is **N x O(1) [read file] + N x O(1) [insert key] + N x O(1) [write dictionary] + O(N) [search] + O(0.01N^2) [sort] ~= O(0.01N^2)**. Although, I do not use faster sort algorithm ( Merge Sort, Heap Sort, Quick Sort etc. ) and search algorithm ( BST ), the high efficiency will be revealed most by "First Search Last Sort" algorithm. Compared to this, I think using faster sort or search algorithms only manifests few advantages.

3. Dictionary Processing
> We retain all the words with hyphen (-) and we also parse most abbreviations to words. For example, **'re** will be regarded as **are**, **'s** will be read as **is**. 

4. Set Timer
> A time consumption record will be displayed after each process ends up, so that you could know how much time this section costs.

5. Exception Detection
> While running program, we are usually facing following situation: There is something wrong with program and the cmd will stop working as dead. Fortunately, the try-catch method in main function resolves this problem, the program will continue to run even if you enter a wrong file directory, simultaneously while loop will ask you to enter again.

------

### License  
+ [MIT License](https://github.com/KennardWang/Crossword-Helper/blob/master/LICENSE)

------

### Author
+ Kennard Wang ( 2020.6.1 )
