#include<iostream>
#include<conio.h>
#include<string>
#include"Piro.h"
#include<windows.h>
#include<fstream>

using namespace std;

void intoFile(string para)
{
	ofstream out;
	out.open("text.txt");
	out << para;
	out.close();
}

bool check(string strArr[10], string str, int in)
{
	for (int i = in - 1; i >= 0; i--)
	{
		if (strArr[i] == str)
			return 0;
	}
	return 1;
}

void displaySug(string strArr[10],int brac)
{
	for (int i = 0; i < 10; i++)
	{
		if (check(strArr, strArr[i], i))
		{
			cout << i+1 << ". " << strArr[i];
			if (i == brac % 10)
				cout << "<--";
			cout << endl;
		}
	}
}

void nullStr(string str[10])
{
	for (int i = 0; i < 10; i++)
	{
		str[i] = "";
	}
}

int main()
{
	bool semi = 0;
	string para = "";
	Tree obj;
	string strArr[10];
	obj.Load();
	int brac = 0;
	string str;
	char inp = 0;

	while (!_kbhit() && inp != '=')
	{
		while (inp != ';' && inp != '=')
		{
			cout << "Paragraph Until Now  :  " << para << endl << endl;
			nullStr(strArr);
			cout << "\nEnter ch  :  ";
			inp = _getch();
			cout << endl << endl;
			if ((inp >= 65 && inp <= 90) || (inp >= 97 && inp <= 122))
			{
				brac = 0;
				str += inp;
			}
			else if (inp == '/')
			{
				brac++;
			}
			else if (inp == ';')
			{
				semi = 1;
			}
			else if (inp == 8)
			{
				str[str.size() - 1] = '\0';
			}
			system("CLS");
			cout << "Original Word : " << str << endl;
			cout << "\nSuggestion  :  \n\n";
			obj.finder(str, strArr);
			displaySug(strArr, brac);
			cout << endl;
		}

		if (semi == 1)
		{
			para += strArr[brac % 10];
			para += " ";
			str = "";
			brac = 0;
			semi = 0;
			inp = 0;
			system("CLS");
		}
	}

	system("CLS");
	cout << "Your All Text  :  ";
	cout << para << endl << endl;

	intoFile(para);
	
	system("PAUSE");
	return 0;
}