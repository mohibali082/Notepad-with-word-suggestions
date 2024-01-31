#include<iostream>
#include<fstream>
#include<string>
#include"Piro.h"
#include<stack>

using namespace std;

stack<int>stk;

Node::Node()
{
	for (int i = 0; i < 26; i++)
	{
		next[i] = NULL;
	}
}

Tree::Tree()
{
	root = new Node;
}

void Tree::insert(string str)
{
	Node* tmp = root;
	int size = str.size();
	bool found = 0;
	int j;

	for (int i = 0; i < size; i++)
	{
		found = 0;
		j = 0;
		for (; j < 26 && tmp->next[j] != NULL; j++)
		{
			if (str[i] == tmp->next[j]->dat)
			{
				found = 1;
				tmp = tmp->next[j];
			}
		}
		if (found == 0)
		{
			tmp->next[j] = new Node;
			tmp->next[j]->dat = str[i];
			tmp = tmp->next[j];
		}
	}
}

void Tree::Load()
{
	string str;
	ifstream in;
	in.open("dictionary.txt");

	while (!in.eof())
	{
		getline(in, str);
		if (!in.eof())
		{
			insert(str);
		}
	}
}

void Tree::finder(string str,string strArr[10])
{
	for (int k = 0; k < 10; k++)
	{
		Node* ptr = root;
		for (int i = 0; i < str.size(); i++)
		{
			for (int j = 0; j < 26; j++)
			{
				if (ptr->next[j] != NULL && str[i] == ptr->next[j]->dat)
				{
					strArr[k] += ptr->next[j]->dat;
					ptr = ptr->next[j];
					break;
				}
			}
		}
		suggest(ptr, strArr[k]);
	}
	callOkZero();
}

void Tree::callOkZero()
{
	okZero(root);
}

void Tree::okZero(Node*tmp)
{
	if (tmp != NULL)
	{
		tmp->ok = 0;
		for (int i = 0; i < 26; i++)
		{
			okZero(tmp->next[i]);
		}
	}
	return;
}

void Tree::suggest(Node* rr,string &newStr)
{
	int count = 0;
	Node* tmp = rr;
	bool flag = 0;
	while (tmp != NULL)
	{
		int j = 0;
		flag = 1;
		for (; j < 26; j++)
		{
			if (tmp->next[j] != NULL && tmp->next[j]->ok == 0)
			{
				flag = 0;
				tmp->ok = 1;
				tmp = tmp->next[j];
				break;
			}
		}
		if (flag == 1)
			tmp = tmp->next[0];

		if (tmp != NULL)
			newStr += tmp->dat;
	}
	
}

//void Tree::suggest(string str)
//{
//	Node* tmp = root;
//	bool found = 0;
//	int si = str.size();
//
//	for (int i = 0; i < si; i++)
//	{
//		found = 0;
//		for (int j = 0; j < 26 && tmp->next[0] != NULL; j++)
//		{
//			if (tmp->next[j]->dat == str[i])
//			{
//				found = 1;
//				tmp = tmp->next[j];
//			}
//		}
//		if (!found)
//			cout << "No Suggestions!";
//	}
//	while (tmp->end != 1)
//	{
//		str += tmp->dat;
//		tmp = tmp->next[0];
//	}
//	cout<<str;
//}

//bool Tree::check(Node* tmp, bool flag = 1)
//{
//	if (tmp != NULL)
//	{
//		if (tmp->end == 1 && tmp->ok != 1)
//			flag = 0;
//		for (int i = 0; i < 26; i++)
//		{
//			flag = check(tmp->next[i], flag);
//		}
//	}
//	return flag;
//}

//void suggester(Node* tmp, string str[10], int i = 0)
//{
//	if (tmp != NULL)
//	{
//		for (int j = 0; j < 26; j++)
//		{
//			str[i] += tmp->dat;
//		}
//	}
//}

void Tree::display(Node* tmp)
{
	cout << tmp->dat;
	if (tmp->end == 1 && tmp->ok == 0)
	{
		tmp->ok = 1;
		return;
	}
	else
	{
		display(tmp->next[0]);
	}
}



//BST

huffman::huffman()
{
	head = NULL;
}

int huffman::size()
{
	int count = 0;
	node* tmp = head;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		count++;
	}
	return count;
}

void huffman::inviN(char alpha)
{
	node* tmp = head;
	if (tmp->alpha == alpha)
	{
		head = head->next;
	}
	else
	{
		while (tmp->next != NULL && tmp->next->alpha == alpha)
		{
			tmp = tmp->next;
		}
		tmp->next = tmp->next->next;
	}
}

void huffman::huff()
{
	int nfreq;
	node* tmp;
	node* tmp1, *tmp2;
	sortList();
	cout << "\n\nHUFFMAN SORT 1\n\n";
	displayList();
	int count = size();
	for (int i = 1; i < count; i++)
	{
		tmp1 = head;
		
		tmp2 = tmp1->next;

		nfreq = tmp1->freq + tmp2->freq;
		tmp = new node;
		tmp->alpha = '-';
		tmp->freq = nfreq;

		if (tmp1->freq < tmp2->freq)
		{
			tmp->left = tmp1;
			tmp->right = tmp2;
		}
		else
		{
			tmp->left = tmp2;
			tmp->right = tmp1;
		}

		inviN(tmp1->alpha);
		inviN(tmp2->alpha);

		insertNode(tmp);
		sortList();
		cout << "\n\nHUFFMAN\n\n";
		displayList();
	}
}

void huffman::encrypt(string str)
{
	ofstream out;
	out.open("encrypt.txt");

	if (out.is_open())
	{
		for (int i = 0; i < str.length(); i++)
		{
			insertnext(str[i]);
		}

		treeIntoFile();
		huff();

		for (int i = 0; i < str.length(); i++)
		{
			if (str[i] != ' ')
			{
				asciiDis(head, str[i]);
				while (!stk.empty())
				{
					out << stk.top();
					stk.pop();
				}
			}
			else
				out << "111111";
			out << ' ';
		}
	}
}

void huffman::treeIntoFile()
{
	ofstream out;
	out.open("tree.txt");
	node* tmp = head;
	while (tmp != NULL)
	{
		out << tmp->alpha << tmp->freq << endl;
		tmp = tmp->next;
	}
	out.close(); 
}

void huffman::decrypt()
{
	treeFromFile();
	sortList();
	huff();

	string para;
	ifstream in;
	in.open("encrypt.txt");
	string str = "", alpha;

	getline(in, alpha);
	for (int i = 0; i < alpha.size(); i++)
	{
		if (alpha[i] != ' ')
		{
			str += alpha;
		}
		else
		{
			if (str == "11111")
			{
				para += ' ';
				str = "";
			}
			else
			{
				para += strOut(head, str, str.size());
				str = "";
			}
		}
	}

	cout << "\n\nDisplay Decrypted  :  " << para;
	
}

char huffman::strOut(node* ptr, string arr, int size, int i)
{
	if (i < size)
	{
		if (arr[i] == '1')
		{
			strOut(ptr->right, arr, size, ++i);
		}
		if (arr[i] == '0')
		{
			strOut(ptr->left, arr, size, ++i);
		}
	}
	else
		return ptr->alpha;
}

void huffman::treeFromFile()
{
	ifstream in;
	node* temp;
	char alpha;
	int freq;
	in.open("tree.txt");
	head = NULL;
	while (!in.eof())
	{
		temp = head;
		in >> alpha >> freq;
		if (!in.eof())
		{
			if (temp == NULL)
			{
				head = new node;
				head->alpha = alpha;
				head->freq = freq;
				head->next = NULL;
			}
			else
			{
				while (temp->next != NULL)
				{
					temp = temp->next;
				}
				temp->next = new node;
				temp->next->freq = freq;
				temp->next->alpha = alpha;
				temp->next->next = NULL;
			}
		}
	}
	in.close();
}

void huffman::sortList()
{
	bool flag = 1;
	int tfreq;
	char talpha;
	node* tmp1;
	while (flag == 1)
	{
		flag = 0;
		tmp1 = head;
		while (tmp1 != NULL)
		{
			if (tmp1->next != NULL && tmp1->freq > tmp1->next->freq)
			{
				talpha = tmp1->alpha;
				tfreq = tmp1->freq;
				tmp1->freq = tmp1->next->freq;
				tmp1->alpha = tmp1->next->alpha;
				tmp1->next->alpha = talpha;
				tmp1->next->freq = tfreq;
				flag = 1;
			}
			tmp1 = tmp1->next;
		}
	}
}

void huffman::insertNode(node* tmp)
{
	node* temp = head;
	if (head == NULL)
	{
		head = tmp;
		head->next = NULL;
	}
	else
	{
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = tmp;
		temp->next->next = NULL;
	}
}

void huffman::displayList()
{
	node* tmp = head;
	while (tmp != NULL)
	{
		cout << tmp->alpha << ":" << tmp->freq << "\t";
		tmp = tmp->next;
	}
}

void huffman::insertnext(char alpha)
{
	if (alpha != ' ')
	{
		if (head == NULL)
		{
			head = new node;
			head->alpha = alpha;
			head->next = NULL;
			head->freq++;
		}
		else
		{
			bool flag = 0;
			node* tmp;
			tmp = head;

			while (tmp->next != NULL)
			{
				if (tmp->alpha == alpha)
				{
					tmp->freq++;
					flag = 1;
					break;
				}
				tmp = tmp->next;
			}
			if (tmp->alpha == alpha && flag == 0)
			{
				tmp->freq++;
				flag = 1;
			}

			if (flag == 0)
			{
				node* newnode;
				newnode = new node;
				newnode->alpha = alpha;
				newnode->freq++;
				newnode->next = NULL;
				tmp->next = newnode;
			}
		}
	}
}

void huffman::callAsciiDis(char alpha)
{
	asciiDis(head,alpha);
	while (!stk.empty())
	{
		cout << stk.top();
		stk.pop();
	}
}
bool huffman::asciiDis(node* tmp, char alpha)
{
	if (tmp != NULL)
	{
		if (tmp->alpha == alpha)
			return 1;
		if (asciiDis(tmp->right, alpha))
		{
			stk.push(1);
			return 1;
		}
		else if (asciiDis(tmp->left, alpha))
		{
			stk.push(0); 
			return 1;
		}
	}
	return 0;
}