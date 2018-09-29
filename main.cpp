//This project makes use of a structure to store and visualize student data
//Mario D. Flores
//September 28, 2018

/*timetrack
s1:start(9/28/18 23:52)end()span()brief()
*/

#include<iostream>

using namespace std;

struct Student
{
	std::string name;
	std::string ID;
	int grades[4];
};

int prompt_getInt(const char[], int, int, const char[]);
bool prompt_YesNo(const char[]);
const char* getOrdinalSufix(int);

int main()
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
		printf("%s %d and %d: ", notValidMessage, min, max);
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