#ifndef PIRO_H
#define PIRO_H

class node
{
public:
	char alpha;
	int freq = 0;
	node* next;
	node* left, *right;
};

class huffman
{
	node *head;
public:
	huffman();
	void insertnext(char alpha);
	int size();
	void huff();
	void sortList();
	void displayList();
	void inviN(char alpha);
	void insertNode(node* tmp);
	void callAsciiDis(char alpha);
	bool asciiDis(node* tmp, char alpha);
	void treeIntoFile();
	void treeFromFile();
	void encrypt(std::string str);
	void decrypt();
	char strOut(node* ptr, std::string arr, int size, int i = 0);
};

class Node
{
public:
	bool end = 0, ok = 0;
	int loc;
	char dat;
	Node* next[26];
	Node();
};

class Tree
{
public:
	Node *root;
	void suggester(Node* tmp, std::string str[10], int i = 0);
	void insert(std::string str);
	Tree();
	void Load();
	void callOkZero();
	void okZero(Node* tmp);
	void display(Node* tmp);
	void suggest(Node* rr,std::string& );
	bool check(Node* tmp, bool flag = 1);
	void finder(std::string str, std::string strArr[10]);
};

#endif // !PIRO_H

