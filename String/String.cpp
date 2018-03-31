#include <bits/stdc++.h>
using namespace std;

class String
{
	char *word;
	int length;
	public:
		String(char const *tempWord="")
		{
			this->length = strlen(tempWord);
			this->word = new char[length];
			strcpy(this->word,tempWord);
		}
		
		String operator+(char const *tempWord);
		String operator+(String &refobj);
		char & operator[](int index);
		friend String operator+(char const *tempWord,String &refobj);
		
		bool operator>(char const *tempWord);
		bool operator<(char const *tempWord);
		bool operator==(char const *tempWord);
			
		friend bool operator>(char const *string1,String &tempobj);
		friend bool operator<(char const *string1,String &tempobj);
		friend bool operator==(char const *string1,String &tempobj);
		
		friend bool operator>(String &string1,String &string2);
		friend bool operator<(String &string1,String &string2);
		friend bool operator==(String &string1,String &string2);
		
		friend istream & operator>>(istream &in,String &string);
		friend ostream & operator<<(ostream &out,String &string);
		friend ostream & operator<<(ostream &out,bool &result);
		
		friend istream & operator<<(istream &in,bool &result);
		
		//static String operator+(char const *string1,char const *string2);
};


String String :: operator+(char const *tempWord)
{
	String tempObj;
	tempObj.word = new char[this->length + strlen(tempWord)];
	strcpy(tempObj.word,this->word);
	strcat(tempObj.word,tempWord);
	return(tempObj);
	
}

String String :: operator+(String &refobj) 
{
	String tempObj;
	tempObj.word = new char[this->length + refobj.length];
	strcpy(tempObj.word,this->word);
	strcat(tempObj.word,refobj.word);
	return(tempObj);
}

bool String :: operator>(char const *tempWord)
{
	int result;
	result = strcmp(this->word,tempWord);
	if(result>0)
		return(true);
	else
		return(false);
}

bool String :: operator<(char const *tempWord)
{
	int result;
	result = strcmp(this->word,tempWord);
	if(result<0)
		return(true);
	else
		return(false);
}

bool String :: operator==(char const *tempWord)
{
	int result;
	result = strcmp(this->word,tempWord);
	if(result==0)
		return(true);
	else
		return(false);
}

char & String :: operator[](int index)
{
	if(index >= this->length)
	{
		cout<<"Index Out Of Bound!";
		return(this->word[index]);
	}
	else
	{
		return(this->word[index]);
	}
}

String operator+(char const *tempWord,String &refobj)
{
	String tempObj;
	tempObj.word = new char[refobj.length + strlen(tempWord)];
	strcpy(tempObj.word,tempWord);
	//strcat(tempObj.word," ");
	strcat(tempObj.word,refobj.word);
	return(tempObj);
}

bool operator>(char const *string1 ,String &tempobj)
{
	int result;
	result = strcmp(string1,tempobj.word);
	if(result > 0)
		return(true);
	else
		return(false);
}

bool operator>(String &tempobj1 ,String &tempobj2)
{
	int result;
	result = strcmp(tempobj1.word,tempobj2.word);
	if(result > 0)
		return(true);
	else
		return(false);
}

bool operator<(char const *string1 ,String &tempobj)
{
	int result;
	result = strcmp(string1,tempobj.word);
	if(result < 0)
		return(true);
	else
		return(false);
}

bool operator<(String &tempobj1 ,String &tempobj2)
{
	int result;
	result = strcmp(tempobj1.word,tempobj2.word);
	if(result < 0)
		return(true);
	else
		return(false);
}

bool operator==(char const *string1 ,String &tempobj)
{
	int result;
	result = strcmp(string1,tempobj.word);
	if(result == 0)
		return(true);
	else
		return(false);
}

bool operator==(String &tempobj1 ,String &tempobj2)
{
	int result;
	result = strcmp(tempobj1.word,tempobj2.word);
	if(result == 0)
		return(true);
	else
		return(false);
}

istream & operator>>(istream &in,String &string)
{
	char *tempWord,ch;
	tempWord = new char[10000];
	int offset = 0,tempLength = 0,counter;
	while((ch = fgetc(stdin))!='\n')
	{
		tempWord[offset++] = ch;
		tempLength++;
	}
	string.word = new char[tempLength+1];
	for(counter=0;counter<tempLength;counter++)
	{
		string.word[counter] = tempWord[counter];
	}
	string.word[counter] = '\0';
	free(tempWord);
	return(in);
}

ostream & operator <<(ostream &out,String &string)
{
	out<<string.word;
	return(out);
}


