/**********************************************************************************
**
** FILENAME : ExistingUser.cpp
**
** DESCRIPTIION : It will validate the Existing User by comparing name and password with the Database.txt file and mask the password with asterick(*).
**
**    CREATED BY                   DATE
**---------------------------------------------------------
** 	Team-1          	24-05-2022
**
********************************************************************************/
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<vector>
#include<fstream>
#include<stdlib.h>
#include<stdio_ext.h>
#include<string>
#include<memory>
#include"ExistingUser.h"
#include"TypeWriter.h"
#include"Password.h"
#include"First.h"
using namespace std;

enum STATUS{FAIL,SUCCESS};
vector<First> eu;

#define BACK 2
#define RETRY '1'

/*********************************************************************
**
** Constructor: ExistingUser() 
**
** DESCRIPTION  : This function retrive the User details such as Name,Password,Mobile for validation from database.txt file.
**
** RETURNS : No return
**
**********************************************************************/
ExistingUser::ExistingUser()
{
	name="NULL";//initialize name to null
	password="NULL";//initialize password to null

	First obj1; //creating the object of class first
	string name1; // to store the name from the database.txt
	string password1; //to store the password from the database.txt
	string mobile1;  //to store mobile number from the database.txt
	ifstream in("./../database/database.txt"); //file open in read mode
	try
	{
		if(in.is_open())
		{
			while(!in.eof())
                         {	
				int age1=0; 
				in>>name1; 
	                        in>>password1; 
                                in>>age1; 
                                in>>mobile1; 
                                if(in.eof()) 
                                    break;
				obj1.setData(name1,password1,age1,mobile1);
				eu.push_back(obj1);
			}
		in.close();
		}
		else
		{
			throw FAIL;
		}
	}

	catch(STATUS x)
	{
		if(x==FAIL)
		{
			cout<<"\t database.txt file not exists"<<endl;
			exit(0);
		}
	}	
}

//existing user login
/*********************************************************************
**
** Function    : nameAndPasswordValidation 
**
** DESCRIPTION : This function validates the given existing user with Password.  
**
** RETURNS: int
**
**********************************************************************/
int ExistingUser::nameAndPasswordValidation()
{
	for(First &d : eu)
	{
		if(d.getName()==this->name)
		{
	
			if(d.getPassword()==this->password)
			{
				cout<<"\n\t*** Login Successful ***"<<endl;
				return SUCCESS;
			}
			else
				return FAIL;
		}

	}
	return FAIL;
}

/*********************************************************************
**
** Function    : ValidateUser
**
** DESCRIPTION : This function validates the Password and mask it from Users as Asterick(*).  
**
** RETURNS: int
**
**********************************************************************/

int ExistingUser::validateUser()
{
	char choice; //choice to retry or exit
	A:cout<<"\n\t\t Login Page.\n\t\t-------------\n"<<endl;
	cout<<"\tEnter UserName     :";
	__fpurge(stdin);
	cin>>this->name;
	__fpurge(stdin);
	password=getpass("\tEnter Password     :",true);
	if(SUCCESS==nameAndPasswordValidation())
	{
		unique_ptr<TypeWriter>t(new TypeWriter);
		if(FAIL==t->typeCheckReport())
		{
			return FAIL;
		}
		else
		{
			return SUCCESS;
		}
	}
	else
	{
		cout<<"\t*** Invalid Login Credentials ***"<<endl;
		cout<<"\t 1. To Try again \n press any key to exit"<<endl;
		scanf("%c",&choice);
		__fpurge(stdin);
		if(choice==RETRY)
			goto A;
		else
		{ 
			cout<<"choice :"<<choice<<endl;
			return BACK;
		}
	
	}
}

