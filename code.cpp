#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <stdio.h>
constexpr auto N = 54555; //TOTAL 54555
using namespace std;

//TREAP CLASS
//REFERENCE[2]
typedef struct ctreenode *ctree;

struct ctreenode{
	vector<string> key; //USER DATA
	int fix; //PRIORITY
	ctree left, right;
};

ctree nullnode, root;

class CTree{
public:
	void initialize();
	void sigrotl(ctree &);
	void sigrotr(ctree &);
	void insert(ctree &, vector<string>);
	bool find(ctree, vector<string>);
	CTree() {}
};

//INITIALIZE
void CTree::initialize(){
	nullnode = new ctreenode;
	nullnode->left = nullnode->right = nullnode;
	root = nullnode;
}

//ROTATE LEFT
void CTree::sigrotl(ctree& k1){
	ctree k2;
	k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	k1 = k2;
}

//ROTATE RIGHT
void CTree::sigrotr(ctree& k1){
	ctree k2;
	k2 = k1->left;
	k1->left = k2->right;
	k2->right = k1;
	k1 = k2;
}

//INSERT
void CTree::insert(ctree& t, vector<string> x){
	if (t == nullnode){
		t = new ctreenode;
		t->left = t->right = nullnode;
		t->key = x;
		t->fix = rand();
	} 
	else{
		if (t->key[0] == x[0]){
			for (int i = 0; i < x.size(); i++) {
				t->key.push_back(x[i]);
			}
			return;
		} 
		else{
			if (x < t->key){
				insert(t->left, x);
				if (t->left->fix > t->fix)
					sigrotr(t);
			}
			else{
				insert(t->right, x);
				if (t->right->fix > t->fix)
					sigrotl(t);
			}
		}
	}
}

//FIND AND DISPLAY
bool CTree::find(ctree t, vector<string> x){
	if (t == nullnode) {
		cout << "Word not found in dictionary!" << endl;
		return false;
	}
	if (t->key[0] == x[0]){
		int i = 0;
		while (i < t->key.size()) {
			std::cout << t->key[i] << endl;
			i++;
		}
		cout << endl;
		return true;
	}
	else{
		if (x[0] < t->key[0])
			return find(t->left, x);
		else
			return find(t->right, x);
	}
}

//SPLIT STRING
vector<string> split(const string& str, const string& delim){	
	//REFERENCE [1]
	vector<string> tokens;
	size_t prev = 0, pos = 0;
	do{
		pos = str.find(delim, prev);
		if (pos == string::npos) pos = str.length();
		string token = str.substr(prev, pos - prev);
		if (!token.empty()) tokens.push_back(token);
		prev = pos + delim.length();
	} while (pos < str.length() && prev < str.length());
	return tokens;
}

//MAIN
int main() {

	CTree dict;
	dict.initialize();
	ifstream file("data.txt");
	string line,tempQ;
	cout << "Enter a word: ";
	cin >> tempQ;
	vector<string> query = {tempQ};


	if (file.is_open()) {
		for (int i = 0; i < N ; i++) {
			getline(file, line);
			vector<string> check = split(line, "	");
			dict.insert(root, check);
		}
		dict.find(root, query);
		cout << "Finished!" << endl;
		file.close();
	}
	else {
		cout << "Error: File not open!";
	}
	return 0;
}

//REFERENCES
//[1] https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
//[2] https://www.sanfoundry.com/cpp-program-implement-treap/
