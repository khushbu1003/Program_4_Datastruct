//************************************  PROGRAM IDENTIFICATION  ***************************************
//*                                                                                                   *
//*   PROGRAM FILE NAME:  Source1.cpp          ASSIGNMENT #:  4             Grade: _________          *
//*                                                                                                   *
//*   PROGRAM AUTHOR:                                                                                 *
//*                   ___________________________________________________                             *
//*                                   Khushbu Shah                                                    *
//*                                                                                                   *
//*   COURSE #:  CSC 24400 11                              DUE DATE: November 5, 2019                 *
//*                                                                                                   *
//*****************************************************************************************************

//***********************************  PROGRAM DESCRIPTION  *******************************************
//*                                                                                                   *
//*   PROCESS: This program is designed to readfile into pointer array with four test scores          * 
//*		using readfile function, the sort the data in alphabetic order then calculate                 * 
//*             the avearge and grades into function and sort again according average from            *
//*             high to low. and call all function in order to get output                             *
//*   USER DEFINED                                                                                    *
//*    MODULES     : Readfile – reads the student names and test scores into a pointer array          *
//*                  Printfile – prints a listing of all students with their name and test scores     *
//*		             sortname - sort the data in alphabetic order from A through Z             	      *
//*		             highestGrade - searches for the student with the highest grade	                  *
//*		             AvgHightoLow - calculates the average of all test scores			              *
//*		             Gradcalc - calculates the grades according to the average                        *
//*										                                                              *
//*****************************************************************************************************
   //preprocessor directives
   #include <iostream>                     //for output and Input streams
   #include<string>                       // to Insert thie string
   #include<iomanip>                     //to formate the output
   #include<fstream>                    //for inserting a file and outputting it
   using namespace std;                //namespace to use in program

   //prototypes declared to 
   //tell compiler the parameters
   //which datatype should be returned
   //and the order in which they occures
    void Header(ofstream&);                     
    void Footer(ofstream&);            
    void ReadFile(ifstream& dataInput, char* nameList[50], float scores[50][5]);   
    void printfile(ofstream& outfile1, char* nameList[50], float scores[][5], int checkAvg);  
    void sortName(char* nameList[50], float scores[50][5]);
    void AvgHighToLow(float scores[50][5], char* nameList[50], char grade[50]);
    char Gradcalc(float scores);

    int main()
    {

    //recieves- It has output in formtting way and function calling demending on the order
    //task- declare varibales and function calling, output and input file
    //returns- it returns the result by the order of formatting and function calling and closes the file
	ifstream infile1("DATA4.TXT", ios::in);      //Tells the processor where to find the input file
	ofstream outfile1("results.txt", ios::out);  // to outstream the result file

	char* nameList[50] = { NULL };              //initilize pointer array to NULL
	float scores[50][5] = { NULL };            //initialize score array to NULL
	char grade[50];                            // declare a single array named grade
	int checkAvg = 0;                         // useful for checkAvg condition to set a condition later

	Header(outfile1);                         //prints the header to the outfile

	ReadFile(infile1, nameList, scores);       //reading data into the readfile function

	outfile1 << "The original Student Data is:" << endl;
	outfile1 << "  First          Last      Test 1  Test 2  Test 3  Test 4" << endl;
	outfile1 << "----------    ----------   ------  ------  ------  ------" << endl;

	printfile(outfile1, nameList, scores,checkAvg);    //function calling of printfile
	sortName(nameList, scores);                       // sorts name by lastnames of students  
	outfile1 << "The list of students sorted A thru Z by Last Name is : " << endl;
	outfile1 << "Student Name" << endl;
	outfile1 << "First          Last        Test 1  Test 2  Test 3  Test 4" << endl;
	outfile1 << "----------   ----------    ------  ------  ------  ------" << endl;


	printfile(outfile1, nameList, scores,checkAvg);    //function calling of the function printfile after sorting

	outfile1 << "The list of students with their test average and course grade is :" << endl;
	outfile1 << "Student Name" << endl;
	outfile1 << "First       Last          Test 1  Test 2  Test 3  Test 4 Average  Grade" << endl;
	outfile1 << "----------    ----------    ------  ------  ------  ------  ------ - ------" << endl;

	checkAvg ==1;                                     //assigning 1 to checkAvg variable declared earlier

	printfile(outfile1, nameList, scores, checkAvg);  //function calling of printfile
	
	outfile1 << "The list of students sorted by test average high to low is :" << endl;
	outfile1 << "Student Name    First       Last     Test 1  Test 2  Test 3  Test 4  Average  Grade" << endl;
	outfile1 << "   ----------    ----------    ------  ------  ------  ------  ------ - ------ -------" << endl;

	Gradcalc(scores[50][5]);                     // sorts the data after average high to low
	printfile(outfile1, nameList, scores, checkAvg);    //prints scores name, average and grades into right format

	AvgHighToLow(scores, nameList, grade);      //sorts student data from high average to low

	Footer(outfile1);                          //prints the footer to the outfile
	//closes the files
	infile1.close();
	outfile1.close();
	cin.ignore();

    }

//********************************************************************************************************************
//*****************************************************FUNCTION READFILE***********************************************
    void ReadFile(ifstream& infile1, char* nameList[50], float scores[50][5])
    {
	// Receives - student names and test scores 
	// Task - read student names and test scores and populate into arrays
	// Returns - student names and test scores 

	char* newPtr = 0;				          // Hold temp name pointer and intitialize to zero
	char fullName[35] = { NULL };	          // Hold students' whole names and initialize to null 
	char firstName[15] = { NULL };           // Hold students' first names and initialize to null 
	char lastName[15] = { NULL };           // Hold students' last names and initialize to null 

	char sentinel[] = { "No            More          " };		// Hold sentinal 

	float total = 0;                       // Hold total scores & initialize to zero the test score 

    int i = 0, j = 0;                          // Hold j for col. count & initialize to zero the count of elements used 

   infile1.getline(firstName, 15);            // read and store first name 
   infile1.getline(lastName, 15);             // read and store last name 


   strcpy_s(fullName, firstName);		       // copy first name  
   strcat_s(fullName, lastName);	           // get full name


   while (strcmp(fullName, sentinel) != 0)     // Process while name doesn't equal sentinel

   {
   newPtr = new char[30];			         // initialize new pointer to array
	memcpy(newPtr, fullName, 30);	         //newPtr holds fullName
	nameList[i] = newPtr;			         // place pointer into array

	for (j = 0; j < 4; j++)                  // Populate array
	{
		infile1 >> scores[i][j];			 // Populate array from input
		total += scores[i][j];				 // Keep running total of scores per student
	}

	infile1.getline(firstName, 1);			// Pull the null char from the end of the line
	scores[i][4] = total / 4;		        // Calculate scores averages

										   // read the next student name
	infile1 >> ws;
	infile1.getline(firstName, 15);	      // read and store first name
	infile1.getline(lastName, 15);		  // read and store last name


	strcpy_s(fullName, firstName);		// copy first name
	strcat_s(fullName, lastName);      // get full name


	total = 0;		                   // set total score amount to zero
	i++;			                  // Increment the count of elements used
   }

   return;
    }
	//********************************************************************************************************************


   //******************************************************FUNCTION PRINTFILE***********************************************
    void printfile(ofstream& outfile1, char* nameList[50], float scores[][5], int checkAvg)
    {
	  //Receives- namelist adress, sentinel value and scores
	  //task-    output the data from a file into the arrays
	  //returns- the names of students with four scores into an array

	int i = 0, j = 0;                // Hold j for col. count & initialize to zero the count of elements used 

	while (nameList[i] != NULL)      // set condition for while loop
	{
		outfile1 << setw(8) << nameList[i];  //printing names
		outfile1.precision(2);               // setting decimals to 2 decimal place
		outfile1 << fixed;                   //test scores to 1 decimal place
		outfile1 << right << setw(5);        //setting width to format

		for (j = 0; j < 4; ++j)
		{
			outfile1 << setw(8) << scores[i][j];
		}

		if (checkAvg == 1)               //check if there is an average
		{
			outfile1.precision(2);      //setting decimals to 2 decimal place
			outfile1 << fixed;          //test scores to one decimal place
			outfile1 << setw(6) << scores[i][4];     //output the scores of students
			outfile1 << setw(6) << Gradcalc(scores[i][4]);     //output the grade letter
		}
			outfile1 << endl;	 // Print a space  
			i++;	// Increment the count of elements
	}

		outfile1 << endl;	// Print a space return; 


}

	//********************************************************************************************************************

   //******************************************************FUNCTION SORTNAME***********************************************

    void sortName(char* nameList[50], float scores[50][5])
    {
	  //Receives - namelist adress, sentinel valueand scores
	  //task-    output the data from a file into the arrays
	  //returns- the names of students with four scores into an array

	int i = 0, size, j, k; // Declare size,k, j, & initialize to zero the end of array we start at  
	int check = 1;        // set check to 1 to start first pass     
	char* temp;          // declare temp pointer  
	char tempName2[16], tempName3[16];     // declare temp name arrays  
	float tempGrades[5];     // declare temp grade array    

	for (i = 0; i < 50; i++)   // Loop through array 
	{
		if (nameList[i] == NULL) // While there are elements in array  
		{
			size = i; // Set size of array
			i = 50; // get out of loop  
		}
	}

	for (i = 1; (i <= size) && check; i++) // control how many we pass thru array  
	{
		check = 0; // reset flag  

		for (j = 0; j < (size - 1); j++) // begin looping thru array at beginning         
		{
			memcpy(tempName2, nameList[j + 1] + 14, 16); // put last name into temp       
			memcpy(tempName3, nameList[j] + 14, 16); // put last name into temp

			if (strcmp(tempName2, tempName3) < 0) // elements are compared and swapped if needed
			{
				temp = nameList[j]; // swap elements                   
				nameList[j] = nameList[j + 1]; // swap elements                   
				nameList[j + 1] = temp; // swap elements                   
				check = 1;  // indicate that a swap occurred    
						   //switching grades 

				for (k = 0; k < 5; k++) // Loop through columns     
				{
					tempGrades[k] = scores[j][k]; // Assign array element temporarily   
				}

				for (k = 0; k < 5; k++) // Loop through columns    
				{
					scores[j][k] = scores[j + 1][k]; // Assign max array element 
																 //to current index
				}

				for (k = 0; k < 5; k++) // Loop through columns     
				{
					scores[j + 1][k] = tempGrades[k]; // Assign array element temporarily
				}

			}
		}
	}
	return;
}
	//********************************************************************************************************************

   //******************************************************FUNCTION GRADCALC**********************************************
	char Gradcalc(float scores)
	{
		//receives- the data of the array scores and test average
		//Task- calculates the average test score for each student
		//return- the test average from each student

		//calculates the average scores for students

		int checkAvg = 1;
		char grade = ' ';
		
		for (int i = 0; i < 50; i++)                           //sets the grade to A for 90 or more than 90
		{
			if (scores >= 90)
				grade = 'A';

		}
		for (int i = 0; i < 50; i++)                           //sets the grade between 80 to 90
		{
			if (scores>= 80 && scores < 90)
				grade = 'B';

		}
		for (int i = 0; i < 50; i++)                           //sets the grade between 70 to 80
		{
			if (scores >= 70 && scores< 80)
				grade = 'C';

		}
		for (int i = 0; i < 50; i++)                           //sets the grade between 60 to 70
		{
			if (scores >= 60 && scores< 70)
				grade = 'D';

		}
		for (int i = 0; i < 50; i++)                           //sets the grade between 60 to 70
		{
			if (scores < 60)
				grade = 'F';

		}
		return grade;
	}
		
	//********************************************************************************************************************


   //******************************************************FUNCTION AVGHIGHTOLOW******************************************

	void AvgHighToLow(float scores[50][5], char* nameList[50], char grade[50])
	{
		//Receives - the data of the arrays student ID, scores and the value of test averages
		//Task- sorts the data by average from high to low
		// Returns- A list of sorted data by average from high to low

		float tempGrades[5];	// Hold grade array  
		int i = 0, size, j, k;	// Initialize to zero the end of array we start at  
		int flag = 1;		    // set flag to 1 to start first pass  
		char* temp;			    // declare temp pointer    

		for (i = 0; i < 50; i++)    // Loop through array  
		{
			if (nameList[i] == NULL)		// While there are elements in array
			{
				size = i;	// Set size of array 
				i = 50;		// get out of loop 
			}
		}

		for (i = 1; (i <= size) && flag; i++)	// count controls how many times we pass thru the array 
		{
			flag = 0;	//reset flag  

			for (j = 0; j < (size - 1); j++)	 // begin looping thru array at beginning  
			{
				if (scores[j + 1][4] > scores[j][4])	// elements are compared and    
																			// swapped if needed   
				{
					flag = 1;		// indicate that a swap occurred   

					for (k = 0; k < 5; k++)	// Loop through columns    
					{
						tempGrades[k] = scores[j][k];		// Assign array element temporarily    
					}
					for (k = 0; k < 5; k++)	// Loop through columns   
					{
						scores[j][k] = scores[j + 1][k];	// Assign max array element 
																			// to current index
					}
					for (k = 0; k < 5; k++)	// Loop through columns    
					{
						scores[j + 1][k] = tempGrades[k];	 // Assign array element temporarily   
					}

					temp = nameList[j];				 // swap elements    
					nameList[j] = nameList[j + 1];	 // swap elements    
					nameList[j + 1] = temp;			 // swap elements   
				}
			}
		}
		return;
	}


//****************************************************************************************************************************

//******************************************************FUNCTION HEADER********************************************************
	void Header(ofstream& outfile1)
	{
		//Receives - the output file
		// task - Prints the output premble
		// Returns - Nothing
		outfile1 << setw(30) << "Khushbu Shah";
		outfile1 << setw(17) << "CSC 24400";
		outfile1 << setw(15) << "Section 11" << endl;
		outfile1 << setw(30) << "FALL 2019";
		outfile1 << setw(20) << "Assignment 3" << endl;
		outfile1 << setw(35) << "--------------------------------------------";
		outfile1 << setw(35) << "--------------------------------------------" << endl << endl;

		return;
	}
//*****************************************************************************************************************************

//******************************************************FUNCTION FOOTER********************************************************

	void Footer(ofstream& outfile1)

	{
		//receives- the output file
		//Task- Prints the output salutation
		//Returns- Nothing

		outfile1 << endl;

		outfile1 << setw(35) << "--------------------------------------------" << endl;

		outfile1 << setw(35) << "|         END OF PROGRAM OUTPUT             |" << endl;

		outfile1 << setw(35) << "--------------------------------------------" << endl;

		return;

	}

//***********************************************************************************************************************************
