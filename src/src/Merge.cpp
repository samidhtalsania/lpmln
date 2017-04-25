#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#include<stdio.h>
#include<stdlib.h>
void main()
{
	clrscr();
	ifstream ifiles1, ifiles2;
	ofstream ifilet;
	char ch, fname1[20], fname2[20], fname3[30];
	cout<<"Enter first file name (with extension like file1.txt) : ";
	gets(fname1);
	cout<<"Enter second file name (with extension like file2.txt) : ";
	gets(fname2);
	cout<<"Enter name of file (with extension like file3.txt) which will store the contents of the two files (fname1 and fname1) : ";
	gets(fname3);
	ifiles1.open(fname1);
	ifiles2.open(fname2);
	if(ifiles1==NULL || ifiles2==NULL)
	{
		perror("Error Message ");
		cout<<"Press any key to exit...\n";
		getch();
		exit(EXIT_FAILURE);
	}
	ifilet.open(fname3);
	if(!ifilet)
	{
		perror("Error Message ");
		cout<<"Press any key to exit...\n";
		getch();
		exit(EXIT_FAILURE);
	}
	while(ifiles1.eof()==0)
	{
		ifiles1>>ch;
		ifilet<<ch;
	}
	while(ifiles2.eof()==0)
	{
		ifiles2>>ch;
		ifilet<<ch;
	}
	cout<<"The two files were merged into "<<fname3<<" file successfully..!!";
	ifiles1.close();
	ifiles2.close();
	ifilet.close();
	getch();
}