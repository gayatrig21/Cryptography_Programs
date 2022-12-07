#include<bits/stdc++.h>

using namespace std;

string getText(string text)
{
	string x="";
	for(int i=0;i<text.length();i++)
	{
		if(text[i] >='a' && text[i]<='z')
			x += (text[i]-'a')+'A';
		else
			x += text[i];
	}
	return x;
}

string encryption(string text,int key)
{
	char rail[key][(text.length())];
	text = getText(text);
	for(int i=0;i<key;i++)
	{
		for(int j=0;j<text.length();j++)
			rail[i][j] = '^';
	}
	
	bool dir_down = false;
	int row=0,col=0;
	for(int i=0;i<text.length();i++)
	{
		if(row==0 || row==key-1)
			dir_down = !dir_down;
		rail[row][col++] = text[i];
		
		dir_down ? row++ : row--;
	}
	
	string result;
	for(int i=0;i<key;i++)
	{
		for(int j=0;j<text.length();j++)
		{
			if(rail[i][j] != '^')
				result.push_back(rail[i][j]);
		}
	}
	
	return result;
}

string decryption(string text,int key)
{
	char rail[key][(text.length())];
	text = getText(text);
	for(int i=0;i<key;i++)
	{
		for(int j=0;j<text.length();j++)
			rail[i][j] = '\n';
	}
	
	bool dir_down;
	int row=0,col=0;
	for(int i=0;i<text.length();i++)
	{
		if(row==0)
			dir_down = true;
		if(row == key-1)
			dir_down = false;
			
		rail[row][col++] = '*';
		
		dir_down ? row++ : row--;
	}
	
	int index=0;
	for(int i=0;i<key;i++)
	{
		for(int j=0;j<text.length();j++)
		{
			if(rail[i][j] == '*' && index<text.length())
				rail[i][j] = text[index++];
		}
	}
	
	string result;
	row = 0;
	col = 0;
	for(int i=0;i<text.length();i++)
	{
		if(row == 0)
			dir_down = true;
		if(row == key-1)
			dir_down = false;
		if(rail[row][col] != '*')
			result.push_back(rail[row][col++]);
		dir_down ? row++ : row--;
	}
	
	return result;
}

int main() 
{
	int choice;
	int datachoice;
	string sample;
	int key;
	while(1)
	{
		cout << "Rail Fence Cipher\n 1. Encryption \n 2. Decryption\n 3. Exit\nEnter Choice: ";
		cin>>choice;
		if(choice>2)
			break;
		switch(choice)
		{
			case 1:
				cout << "Data is from\n 1. Manual Entering \n 2. File \nEnter Choice: ";
				cin>>datachoice;
				if(datachoice == 1)
				{
					cout<<"Enter data to be Encrypted:\n";
					cin.ignore();
					getline(cin,sample);
					cout<<"Enter the key: ";
					cin>>key;
					cout<<"Encrypted String:\n";
					cout<<encryption(sample,key)<<endl;
				}
				else
				{
					cout<<"Enter File Name:\n";
					cin.ignore();
					getline(cin,sample);
					cout<<"Enter the key: ";
					cin>>key;
					fstream myfile;
					myfile.open(sample.c_str());
					string str,s;
					if(!myfile.is_open())
						cout << "Error while Opening File";
					while(getline(myfile,str))
						s+=str;
					myfile.close();
					s=encryption(s,key);
					myfile.open("CipherText.txt",ios_base::out);
					if(myfile.is_open())
						myfile.write(s.data(),s.size());
					cout<<"File Encrypted\n";
					myfile.close();
				}
				break;
			case 2:
				cout << "Data is from\n 1. Manual Entering \n 2. File \nEnter Choice: ";
				cin>>datachoice;
				if(datachoice == 1)
				{
					cout<<"Enter data to be Decrypted:\n";
					cin.ignore();
					getline(cin,sample);
					cout<<"Enter the key: ";
					cin>>key;
					cout<<"Decrypted String:\n";
					cout<<decryption(sample,key)<<endl;;
				}
				else
				{
					cout<<"Enter File Name:\n";
					cin.ignore();
					getline(cin,sample);
					cout<<"Enter the key: ";
					cin>>key;
					fstream myfile;
					myfile.open(sample.c_str());
					string str,s;
					if(!myfile.is_open())
						cout << "Error while Opening File";
					while(getline(myfile,str))
						s+=str;
					myfile.close();
					s=decryption(s,key);
					myfile.open("PlainText.txt",ios_base::out);
					if(myfile.is_open())
						myfile.write(s.data(),s.size());
					cout<<"File Decrypted\n";
					myfile.close();
				}
				break;
		}
	}
	return 0;
}
