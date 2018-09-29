//This project makes use of a structure to store and visualize student data
//Mario D. Flores
//September 28, 2018

/*timetrack
s1:start(9/28/18 23:52)end(9/29/18 00:58)span(1h 06m)brief(create, add logic, test)
*/

#include<iostream>
#include<string>

using namespace std;

///<summary>Stores basic information about a student.</summary>
struct Student
{
	std::string name;
	std::string ID;
	int grades[4];
};

void collectStructData(Student &);
double calculateAverage(Student);
void displayData(const Student*, int);

int prompt_getInt(const char[], int, int, const char[]);
bool prompt_YesNo(const char[]);
const char* getOrdinalSufix(int);

int main()
{
	Student studentData;
	double scoreAverage;
	
	do
	{ 
		collectStructData(studentData);
		//start of loop
			//collect data into struct - void return, receives struct by ref 
			//calculate highest grade (drop lowest grade) - Returns average, recieves struct by val
			//display data - void return, receives struct by static ref, receives average score
		//end of loop - ask user is they want to repeat
	} while (prompt_YesNo("Do you want to repeat? Otherwise the program will exit."));

	return EXIT_SUCCESS;
}

void collectStructData(Student &studentData)
{
	const int SIZE_STUDENT_GRADES = sizeof(Student::grades)/sizeof(int);

	cout << "Enter the student's name: ";
	getline(cin, studentData.name);
	cout << "Enter " << studentData.name << "'s student ID: ";
	getline(cin, studentData.ID);

	for (int i = 0; i < SIZE_STUDENT_GRADES; i++)
	{
		cout << "Enter the " << i + 1 << getOrdinalSufix(i + 1) << " score: ";
		studentData.grades[i] = prompt_getInt("", 0, 100, "Invalid score. It has to be between %d and %d: ");
	}
}

double calculateAverage(Student studentData)
{
	const int SIZE_STUDENT_GRADES = sizeof(Student::grades) / sizeof(int);
	int lowestGrade, acummulator = 0;

	for (int i = 0; i < SIZE_STUDENT_GRADES; i++)
	{
		if (i)
			lowestGrade = studentData.grades[i];
		else if (studentData.grades[i] < lowestGrade)
			lowestGrade = studentData.grades[i];

		acummulator += studentData.grades[i];
	}

	acummulator -= lowestGrade;
	return acummulator/(SIZE_STUDENT_GRADES-1);
}

void displayData(const Student *studentData, int scoreAverate)
{

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