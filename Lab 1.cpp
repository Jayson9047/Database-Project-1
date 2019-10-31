/*
* FILE : Lab 1.cpp
* PROJECT : Lab 1
* PROGRAMMER : Jayson Ovishek Biswas
* FIRST VERSION : 2019-09-15
* DESCRIPTION : This program is run from the command prompt. The program is able to create and manage a database called "Hello.dat"
				It takes command from the user. It validates the command and execute the right function if the correct command is given.
				This program allows the user to create Find and delete an entry. It is also able to generate random entries and show all
				the entries in the database.

*/
#define Insert			1
#define Delete			2
#define Find			3
#define Random_Insert	4
#define Stop			5
#define Find_All		6
#define Exit			-1
#define Fail			0


#include<iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <exception>
#include <list>
#include <time.h> 


using namespace std;
#pragma warning(disable:4996)

int checkCommand(FILE* ifp, char* commandString, char* argument);
bool checkSpsid(char* spsid);
bool checkfieldID(int fieldID);
bool checkIFuel(int iFuel);
bool checkiProduct(int iProduct);
bool checkproductID(char* productID);
void insert(FILE* ifp, char* spsid, int fielID, int iFuel, int iProduct, char* productId);
void randomInsert(FILE* ifp,int number);
void findString(FILE* ifp,char* param, int number);
void deleteString(FILE* ifp, FILE* ifp1, char* param);
int main(int argc, char* argv[])
{
	char argument[81] = "";
	char input[81] = "";
	char arg[2][81] = { '\0' };
	int checkValue = 0; 
    if (argv[1] == NULL)
	{
	  cout << "Please type 'start' as an argument after the executable file name";
	  
	}
	else if ((stricmp(argv[1], "Start") == 0) && (argc == 2))	//the only command in the command prompt should be "Start", in order to run the program
	{
		FILE* ifp = NULL;
		FILE* ifp2 = NULL;
		FILE* ifp3 = NULL;
		FILE* ifp4 = NULL;
		ifp = fopen("Hello.dat", "a");		
		if (ifp == NULL)				//IF "Hello.dat" doesn't exist, create a new file
		{
			ifp = fopen("Hello.dat", "w");
			fclose(ifp);
			ifp = fopen("Hello.dat", "a");
		}

		char string1[81] = "";
		while (checkValue != Stop)		// The program runs as long as the Stop command is not given 
		{
			printf("\n1.Insert\n2.Delete\n3.Find\n4.Random Insert\n5.Stop\n");
			printf("Type your command: ");
			fgets(string1, 81, stdin);		// take command
			checkValue = checkCommand(ifp,string1, argument);	//validate and execute command
			if (checkValue == Find_All)			//if Find_All is the command 
			{
				ifp2 = fopen("Hello.dat", "r");	//open the database in read mode
				clock_t t;
				t = clock();
				findString(ifp2, string1, Find_All);	//print the database
				t = clock() - t;
				double time_taken = ((double)t);
				cout << "Time taken " << (time_taken) << "ms" << endl;	//show time
				fclose(ifp2);
			}
			else if (checkValue == Find)
			{
				ifp2 = fopen("Hello.dat", "r");
				clock_t t;
				clock_t y;
				t = clock();
				findString(ifp2, argument, Find);
				y = clock();
				t = y - t;
				double time_taken = ((double)t);
				cout << "Time taken " << (time_taken) << "ms" << endl;
				fclose(ifp2);
			}
			else if (checkValue == Delete)
			{
				ifp3 = fopen("Hello.dat", "r");
				ifp4 = fopen("Hi.dat", "w");
				fclose(ifp4);
				ifp4 = fopen("Hi.dat", "a");
				clock_t t;
				clock_t y;
				t = clock();
				deleteString(ifp3, ifp4, argument);	
				fclose(ifp3);
				fclose(ifp4);
				fclose(ifp);
				remove("Hello.dat");
				rename("Hi.dat", "Hello.dat");
				y = clock();
				t = y - t;
				double time_taken = ((double)t);
				cout << "Time taken " << (time_taken) << "ms" <<endl;
				ifp = fopen("Hello.dat", "a");
			}
		}
		fclose(ifp);
		return Exit;
	}

	else
	{
		printf("wrong input");
	}
	return 0;
}


//FUNCTION : checkCommand
//DESCRIPTION : This function validates the user input and executes Insert and Random Insert according to the command.
//PARAMETERS: FILE* ifp			  - Database File Pointer
//			  char* commandString - input command
//			  char* argument	  - pointer to a string
//RETURNS: 
//		int: Integer indicating the action

int checkCommand(FILE* ifp, char* commandString, char* argument)
{
	char command[81] = "";
	char arg[81] = "";
	char spsid[81] = "";
	int fieldID = 0;
	int iFuel = 0;
	int iProduct = 0;
	char productId[81] = "";
	int random = 0;
	bool valid = true;
	char* pSpace1 = strchr(commandString, ' '); //Find the 1st space character.
	char* pFirst = commandString; //Pointer to the 1st letter
	char* pLast = strchr(commandString, '\n');
	if (pSpace1 == NULL)	//If there is no space in the input
	{
		strncpy(command, commandString, pLast - pFirst);
		if (stricmp(command, "Stop") == 0)	//check if stop is the command, else send error message
		{
			return Stop;
		}
		else
		{
			printf("wrong Command");
			return Fail;
		}
	}
	strncpy(command, commandString, pSpace1 - pFirst); //Copy the First word before space in a char array
	strcpy(arg, pSpace1 + 1);

		if (stricmp(command, "Insert") == 0)	//check if insert is the command
		{
			if (sscanf(pSpace1, " %s %d %d %d %s", &spsid, &fieldID, &iFuel, &iProduct, &productId) != 5)	//check the input string format
			{
				printf("Wrong Input");
				return Fail;
			}
			else
			{
				if ((checkSpsid(spsid) == true) && (checkfieldID(fieldID) == true) && (checkIFuel(iFuel) == true) &&
					(checkiProduct(iProduct) == true) && (checkproductID(productId) == true))	// check if all the input value is correct
				{
					strcpy(argument, arg);
					FILE* ifp2 = fopen("Hello.dat", "a");
					clock_t t;
					clock_t y;
					t = clock();
					insert(ifp2,spsid,fieldID,iFuel,iProduct,productId);	//insert the entry
					y = clock();
					t = y - t;
					double time_taken = ((double)t) ;
					cout << "Time taken "<<(time_taken) <<"ms" << endl;
					fclose(ifp2);
					return Insert;
				}
				else
				{
					return Fail;
				}
			}
		}
		else if (stricmp(command, "Delete") == 0)	//check if Delete is the command
		{
			if (sscanf(pSpace1, " %s", &spsid) != 1) //There should be only one parameter to Delete command
			{
				printf("Wrong Input");
				return Fail;
			}
			else
			{
				if (checkSpsid(spsid) == true)
				{
					strcpy(argument, arg);
					return Delete;		// if given input is correct return Delete
				}
				else
				{
					return Fail;
				}
			}

		}
		else if (stricmp(command, "Find") == 0)	
		{
			if (sscanf(pSpace1, " %s", &spsid) != 1)	//There should be only one parameter to Delete command
			{
				printf("Wrong Input");
				return Fail;
			}
			else
			{
				if (stricmp(spsid, "All") == 0)
				{
					return Find_All;	// if given input is correct return Find_All
				}
				else
				{
					if (checkSpsid(spsid) == true)
					{
						strcpy(argument, arg);
						return Find;		// if given input is correct return Find
					}
					else
					{
						return Fail;
					}
				}
			}
			
		}
		else if (stricmp(command, "Random") == 0)
		{
			if (sscanf(pSpace1, " %d", &random) != 1)
			{
				printf("Wrong Input");
				return Fail;
			}
			else
			{
				FILE* ifp2 = fopen("Hello.dat", "a");
				clock_t t;
				clock_t y;
				t = clock();
				randomInsert(ifp, random);		//If the given command is valid about random, do the random insert
				y = clock();
				t = y - t;
				double time_taken = ((double)t);
				cout << "Time taken " << (time_taken) << "ms" << endl;
				fclose(ifp2);
				return Random_Insert;
			}		
		}

		else
		{
			printf("wrong Command");	//if the given command is not in the menu send error message
			return Fail;
		}

}

//FUNCTION : checkSpsid
//DESCRIPTION : This function validates the given SPSID.
//PARAMETERS: char* spsid	  - pointer to a string that contains the given spsid
//RETURNS: 
//		bool: True if valid
//			  False if invalid

bool checkSpsid(char* spsid)
{
	char validSpsid[5][25] = { "JDR0423", "NHSP310F", "STARA3100AR", "HAGIESTS16", "CASE4430" };
	int record = -1;
	//check if the spsid is no more than 24 characters
	if (strlen(spsid) > 24)
	{
		printf("Wrong SPSID");
		return false;
	}
	//match the given spsid with the valid spsid
	for (int i = 0; i < 5; i++)
	{
		if (stricmp(spsid, validSpsid[i]) == 0)
		{
			record = i; //if matched record the index number
		}
	}
	if (record == -1)  //if not matched send error message 
	{
		printf("Wrong SPSID\n");
		return false;
	}
	return true;
}

//FUNCTION : checkfieldID
//DESCRIPTION : This function validates the given fieldID.
//PARAMETERS: int fieldID	  - the given fieldID
//RETURNS: 
//		bool: True if valid
//			  False if invalid
bool checkfieldID(int fieldID)
{
	//If the fieldID is less than 1 or more than 255 show error
	if ((fieldID < 1) || (fieldID > 255))
	{
		printf("Wrong FieldID");
		return false;
	}
	return true;
}

//FUNCTION : checkIFuel
//DESCRIPTION : This function validates the given fieldID.
//PARAMETERS: int iFuel	  - the given iFuel
//RETURNS: 
//		bool: True if valid
//			  False if invalid
bool checkIFuel(int iFuel)
{
	//If the iFuel is less than 1 or more than 350 show error
	if ((iFuel < 1) || (iFuel > 350))
	{
		printf("Wrong IFuel quantity");
		return false;
	}
	return true;
}

//FUNCTION : checkiProduct
//DESCRIPTION : This function validates the given iProduct.
//PARAMETERS: int iProduct	  - the given iProduct
//RETURNS: 
//		bool: True if valid
//			  False if invalid
bool checkiProduct(int iProduct)
{
	//If the iProduct is less than 1 or more than 1200 show error
	if ((iProduct < 1) || (iProduct > 1200))
	{
		printf("Wrong IProduct quantity");
		return false;
	}
	return true;
}

//FUNCTION : checkproductID
//DESCRIPTION : This function validates the given productID.
//PARAMETERS: char* productID	  - pointer to a string that contains the given productID
//RETURNS: 
//		bool: True if valid
//			  False if invalid
bool checkproductID(char* productID)
{
	int record = -1;
	char validProductId[3][25] = { "DUPCurzate","BAYScala","SYNMaxim" };
	//check if the Product id is no more than 24 characters
	if (strlen(productID) > 24)
	{
		printf("Wrong SPSID");
		return false;
	}
	
	//match the given Product id with the valid spsid
	for (int i = 0; i < 3; i++)
	{
		if (stricmp(productID, validProductId[i]) == 0)
		{
			record = i; //if matched record the index number
		}
	}
	if (record == -1) //if not matched send error message 
	{
		printf("Wrong ProductID");
		return false;
	}
	return true;
}

//FUNCTION : insert
//DESCRIPTION : Inserts the given input to the database as an entry
//PARAMETERS: FILE* ifp			  - Database File Pointer
//			  char* spsid		  - The given spsid
//			  int fieldID		  - the given fieldID
//			  int iFuel			  - the given iFuel
//			  int iProduct		  - the given iProduct
//			  char* productID	  - pointer to a string that contains the given productID
//RETURNS: none

void insert(FILE* ifp, char* spsid, int fieldID, int iFuel, int iProduct, char* productId)
{
	fprintf(ifp, "%s\t%d\t%d\t%d\t%s\n", spsid,fieldID,iFuel,iProduct,productId);
}

//FUNCTION : randomInsert
//DESCRIPTION : Inserts Random entries in the database.
//PARAMETERS: FILE* ifp			  - Database File Pointer
//			  int number		  - The number of entries that has to be done
//RETURNS: none
void randomInsert(FILE* ifp, int number)
{
	char validSpsid[5][25] = { "JDR0423 ", "NHSP310F", "STARA3100AR", "HAGIESTS16", "CASE4430" };
	char validProductId[3][25] = { "DUPCurzate","BAYScala","SYNMaxim" };
	int spsidIndex = 0;
	int productIdIndex = 0;
	int fieldId = 0;
	int iFuel = 0;
	int iProduct = 0;

	for (int count = 0; count < number; count++)	//generate random entries and put it into the database
	{
		int r = rand();
		spsidIndex = (r % 5);
		productIdIndex = (r % 3);
		fieldId = r % 255;
		iFuel = r % 350;
		iProduct = r % 1200;
		insert(ifp, validSpsid[spsidIndex], fieldId, iFuel, iProduct, validProductId[productIdIndex]);
	}

}

//FUNCTION : findString
//DESCRIPTION : Searches for the entries based on the SPSID and show all the found entries.
//PARAMETERS: FILE* ifp			  - Database File Pointer
//			  char*	param		  - Pointer to a string that indicates the given parameter
//			  int number		  - The number of entries that has to be done
//RETURNS: none
void findString(FILE* ifp,char* param, int number)
{
	char input[81] = "";
	int num = strlen(param);
	while (fgets(input, 81, ifp) != NULL)
	{
		if (number == Find_All)
		{
			printf("%s", input);	//if find all is the command, print all the entries
		}
		else if (number == Find)
		{
			if (strnicmp(input, param, (num - 1)) == 0)
			{
				cout << input;		//if find all is the command, print only the found entries
			}	
		}
	}

}

//FUNCTION : deleteString
//DESCRIPTION : Deletes the entries based on the SPSID.
//PARAMETERS: FILE* ifp			  - Database File Pointer
//			  FILE*	ifp1		  - New Databes File Pointer
//			  char*	param		  - Pointer to a string that indicates the given parameter
//RETURNS: none
void deleteString(FILE* ifp, FILE* ifp1, char* param)
{
	char input[81] = "";
	int num = strlen(param);

	//print all the entries into a new database except the ones that has to be deleted
	while (fgets(input, 81, ifp) != NULL)
	{
		if (strnicmp(input, param, (num - 1)) != 0)	
		{
			fprintf(ifp1, input);
		}
	}
}

