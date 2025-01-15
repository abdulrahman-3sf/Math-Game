// #####################################################################################

//                                Abdulrahman Alassaf
//                              github: @abdulrahman-3sf

//                                Math Game Project.
//                                  Solved with C++

// #####################################################################################


#include <iostream>
#include <cstdlib> // random number
using namespace std;

// Public methods, that used frequently
int readPositiveNumber(string msg) {
	int number;

	do {
		cout << msg;
		cin >> number;
	} while (number < 0);

	return number;
}
int randomNumber(int from, int to) {
	return rand() % (to - from + 1) + from;
}

enum enLevel { easy = 1, midd = 2, hard = 3, mixLevel = 4 };
enum enOperationType { add = 1, sub = 2, mult = 3, divi = 4, mixOperationType = 5 };
struct stQuizzInfo {
	int numberOfQuestions = 0;

	enLevel level;
	enOperationType operationType;
	int number1 = 0;
	int number2 = 0;

	int right = 0;
	int wrong = 0;
};
stQuizzInfo mathGameInfo() {
	stQuizzInfo person;

	person.numberOfQuestions = readPositiveNumber("How many questions do you want?\n=> ");
	person.level = (enLevel) readPositiveNumber("Level of questions? [1]easy [2]mid [3]hard [4]Mix\n=> ");
	person.operationType = (enOperationType)readPositiveNumber("Operation type of questions? [1]+ [2]- [3]x [4]/ [5]Mix\n=> ");

	return person;
}
void getNumbersDependingOnLevel(stQuizzInfo& person) {

	int number1, number2, questionLevel;
	questionLevel = person.level;

	if (questionLevel == enLevel::mixLevel)
		questionLevel = (enLevel)randomNumber(1, 3);

	switch (questionLevel) {
	case enLevel::easy:
		person.number1 = randomNumber(1, 10);
		person.number2 = randomNumber(1, 10);
		break;
	case enLevel::midd:
		person.number1 = randomNumber(11, 50);
		person.number2 = randomNumber(11, 50);
		break;
	case enLevel::hard:
		person.number1 = randomNumber(51, 100);
		person.number2 = randomNumber(51, 100);
		break;
	}
}
float calculateAnswer(stQuizzInfo& person, enOperationType currentOperationType) {
	float results;


	switch (currentOperationType) {
	case enOperationType::add:
		results = person.number1 + person.number2;
		break;
	case enOperationType::sub:
		results = person.number1 - person.number2;
		break;
	case enOperationType::mult:
		results = person.number1 * person.number2;
		break;
	case enOperationType::divi:
		results = (float)person.number1 / person.number2;
		break;
	}

	return results;
}
string getOperationSymbol(enOperationType operationType) {
	switch (operationType) {
	case enOperationType::add:
		return "+";
	case enOperationType::sub:
		return "-";
	case enOperationType::mult:
		return "x";
	case enOperationType::divi:
		return "/";
	}
}
float getAnswerFormUser(stQuizzInfo person, enOperationType currentOperationType) {
	float results;

	cout << endl << person.number1 << endl << person.number2 << "  " << getOperationSymbol(currentOperationType) << endl << "_____________\n";
	cin >> results;

	return results;
}
void checkAnswer(stQuizzInfo& person) {
	float calculatedAnswer;
	float userAnswer;
	enOperationType currentOperationType;

	currentOperationType = person.operationType;

	if (currentOperationType == enOperationType::mixOperationType) {
		currentOperationType = (enOperationType)randomNumber(1, 4);
	}

	calculatedAnswer = calculateAnswer(person, currentOperationType);
	userAnswer = getAnswerFormUser(person, currentOperationType);

	if (userAnswer == calculatedAnswer) {
		person.right += 1;
		cout << "\nRight Answer :)\n";
	}
	else {
		person.wrong += 1;
		cout << "\nWrong Answer :(\n";
		cout << "The right answer is: " << calculatedAnswer << endl;
	}
}
void finalResult(stQuizzInfo person) {

	string finalResult;

	if (person.right >= person.wrong)
		finalResult = "Pass";
	else
		finalResult = "Fail";

	cout << "\n\n\t\t---------------------------------------------\n";
	cout << "\t\t\tFinal Results is " << finalResult;
	cout << "\n\t\t---------------------------------------------\n";
	cout << "\t\tNumber of Questions\t\t: " << person.numberOfQuestions << endl;
	cout << "\t\tQuestions Level\t\t\t: " << person.level << endl;
	cout << "\t\tOperation Type\t\t\t: " << person.operationType << endl;
	cout << "\t\tNumber of Right Answers\t\t: " << person.right << endl;
	cout << "\t\tNumber of Wrong Answers\t\t: " << person.wrong << endl << endl;
}

void startMathGame() {
	int again;
	stQuizzInfo person;
	
	do {
		system("cls");

		person = mathGameInfo();

		for (int i = 1; i <= person.numberOfQuestions; i++) {
			cout << "\n---------- Question [" << i << '/' << person.numberOfQuestions << "] ----------";
			getNumbersDependingOnLevel(person);
			checkAnswer(person);
		}

		finalResult(person);

		again = readPositiveNumber("\nDo you want to play again? [0]No, [1]Yes\n=> ");
	} while (again == 1);
}

int main() {
	// Seeds the random number generator in C++, called only once
	srand((unsigned)time(NULL));

	startMathGame();
}