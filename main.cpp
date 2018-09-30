//This project makes use of a structure to store and visualize student data
//Mario D. Flores
//September 28, 2018

/*timetrack
s1:start(9/28/18 23:52)end(9/29/18 00:58)span(1h 06m)brief(create, add logic, test)
s2:start(9/29/18 18:41)end(9/29/18 19:25)span(0h 44m)brief(finish up, test, debug)
s3:start(9/29/18 20:33)end(9/29/18 21:00)span(0h 27m)brief(documentation)
*/

#include<iostream>
#include<string>
#include<iomanip>

using namespace std;

///<summary>Stores basic information about a student.</summary>
struct Student
{
	std::string name;
	int ID;
	int grades[4];
};

void collectStructData(Student &);
double calculateAverage(Student);
void displayData(const Student*, double);

int prompt_getInt(const char[], bool, const char[]);
int prompt_getInt(const char[], int, int, const char[]);
bool prompt_YesNo(const char[]);
const char* getOrdinalSufix(int);

int main()
{
	Student studentData; //stores the current student data that the user inputs
	double scoreAverage; //stores the average calculated from the scores in studentData
	
	//Initial prompt
	cout << "This program accepts a student's data and four grades. It calcualtes the average and displays it.\n";
	system("pause");

	//Main loop to repeat program
	do
	{ 
		cout << endl;
		collectStructData(studentData);
		scoreAverage = calculateAverage(studentData);
		displayData(&studentData, scoreAverage);
	} while (prompt_YesNo("Do you want to repeat? Otherwise the program will exit."));

	return EXIT_SUCCESS;
}

///<summary>Prompts the user to enter appropriate data to fill a <c>Student</c> struct</summary>
///<param name = "studentData">The <c>Student</c> struct that will store the user's input.</param>
void collectStructData(Student &studentData)
{
	//Contains the array size of Student member 'grades'
	const int SIZE_STUDENT_GRADES = sizeof(Student::grades)/sizeof(int);

	cout << "Enter the student's name: ";
	getline(cin, studentData.name);

	cout << "Enter " << studentData.name << "'s student ID: ";
	studentData.ID = prompt_getInt("",true,"ID has to be a positive non-zero number: ");
	//getline(cin, studentData.ID);

	//collects and stores the grades into the array memeber of the Student struct
	for (int i = 0; i < SIZE_STUDENT_GRADES; i++)
	{
		cout << "Enter the " << i + 1 << getOrdinalSufix(i + 1) << " score: ";
		studentData.grades[i] = prompt_getInt("", 0, 100, "Invalid score. It has to be between %d and %d: ");
	}
}

///<summary>Calculates the average of a <c>Student</c> struct and returns the average all scores but the lowest.</summary>
///<param name = "studentData">The <c>Student</c> struct that contains the student's data.</param>
///<returns>The average</returns>
double calculateAverage(Student studentData)
{
	//Contains the array size of Student member 'grades'
	const int SIZE_STUDENT_GRADES = sizeof(Student::grades) / sizeof(int);
	int lowestGrade, acummulator = 0;

	//Finds lowest grade and adds them all
	for (int i = 0; i < SIZE_STUDENT_GRADES; i++)
	{
		if (!i) //true on first loop
			lowestGrade = studentData.grades[i];
		else if (studentData.grades[i] < lowestGrade)
			lowestGrade = studentData.grades[i];

		acummulator += studentData.grades[i];
	}

	acummulator -= lowestGrade; //gets rid of lower score
	return static_cast<double>(acummulator)/(SIZE_STUDENT_GRADES-1);
}

///<summary>Prints a formatted report of the data stored in <c>studentData</c> to the standard output device.</summary>
///<param name = "studentData">The <c>Student</c> struct that contains the student's data.</param>
///<param name = "scoreAverage">The calculated average of the scores stored in <c>studentData</c></param>
void displayData(const Student *studentData, double scoreAverage)
{
	//Contains the array size of Student member 'grades'
	const int SIZE_STUDENT_GRADES = sizeof(Student::grades) / sizeof(int);
	const char SEPARATOR[55] = "------------------------------------------------------"; //54 dashes
	const int TAB_SIZE = 30; //Output column width

	cout << SEPARATOR << endl;
	cout << setw(TAB_SIZE) << left << "Student's name:" << studentData->name << endl;
	cout << setw(TAB_SIZE) << left << "Student's ID:" << studentData->ID << endl;
	cout << setw(TAB_SIZE) << left << "Student's grades:" << "{";

	//prints the values contained on the 'grades' memeber of the Student struct
	for (int i = 0; i < SIZE_STUDENT_GRADES; i++)
	{
		cout << studentData->grades[i] << (i < SIZE_STUDENT_GRADES - 1?",":"");
	}

	cout << "}" << endl;
	cout << setw(TAB_SIZE) << left << "Average (of 3 highest):" <<
		setprecision(2) << fixed << showpoint << scoreAverage << endl;
	cout << SEPARATOR << endl;
}

///<summary>Shows a prompt to the user, accepts an integer input, and then returns the number to the caller.</summary>
///<param name = "message">Prompt that will be shown before requesting the input.</param>
///<param name = "onlyNatural">If true this function will only accept non-zero positive values.</param>
///<param name = "notValidMessage">Prompt that will be shown after an invalid input.</param>
///<returns>Returns the integer value entered by user.</returns>
int prompt_getInt(const char message[], bool onlyNatural, const char notValidMessage[])
{
	int retInt;

	//validation
	while ((std::cout << message)			//return is irrelevant, it's here to loop the message
		&& !(std::cin >> retInt)			//return is null when input is not valid
		|| (retInt < 1 && onlyNatural))		//true when outside of valid range
	{
		std::cout << notValidMessage << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	return retInt;
}

///<summary>Shows a prompt to the user, accepts an integer input within a given range, and then returns the number to the caller.</summary>
///<param name = "message">Prompt that will be shown before requesting the input.</param>
///<param name = "min">Numbers below this value won't be valid.</param>
///<param name = "max">Numbers above this value won't be valid.</param>
///<param name = "notValidMessage">Prompt that will be shown after an invalid input.</param>
///<returns>Returns the integer value entered by user.</returns>
int prompt_getInt(const char message[], int min, int max, const char notValidMessage[])
{
	int retInt;

	//validation
	while ((std::cout << message)			//return is irrelevant, it's here to loop the message
		&& !(std::cin >> retInt)			//return is null when input is not valid
		|| (retInt > max || retInt < min))	//true when outside of valid range
	{
		printf(notValidMessage, min, max);
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	return retInt;
}

///<summary>Promts the user to input either 'y' (yes) or 'n' (no). Input is not case sensitive.</summary>
///<param name = "message">The initial custom prompt that will be shown.</param>
///<returns>Returns true is the user entered 'y' and false if input is 'n'.</returns>
bool prompt_YesNo(const char message[])
{
	char userInput;

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //avoid buffer jumping coming from caller
	std::cout << message << std::endl << "[y/n]: "; //prints caller's message

													//validation
	while (!(std::cin >> userInput)			//return is null when input is not valid
		|| (tolower(userInput) != 'n'		//true as long as it's not letter n or N
			&& tolower(userInput) != 'y'))	//true as long as it's not letter y or Y
	{
		std::cout << "'" << userInput << "' is not a valid command" << std::endl << "[y/n]: ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //avoid buffer jumping going to the caller

	//resolve return
	switch (tolower(userInput))
	{
	case 'y':
		return true;
		break;
	case 'n':
		return false;
		break;
	default:
		return false; //should never happen but it's here just in case
		break;
	}
}

///<summary>Returns the appropriate ordinal sufix for any given positive integer.</summary>
///<param name = "numInput">Number which suffix needs to be known.</param>
///<returns>Returns a C-String that contains the suffix.</returns>
const char* getOrdinalSufix(int numInput)
{
	switch (numInput % 10)
	{
	case 1:
		return "st";
		break;
	case 2:
		return "nd";
		break;
	case 3:
		return "rd";
		break;
	default:
		return "th";
		break;
	}
}