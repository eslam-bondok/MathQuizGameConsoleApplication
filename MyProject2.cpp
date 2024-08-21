
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

enum enQuestionLevel {Easy = 1, Med = 2, Hard = 3, Mix = 4};
enum enOperationType {Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5};

struct stQuestion
{
	int Number1 = 0;
	int Number2 = 0;
	enOperationType OperationType;
	enQuestionLevel QuestionLevel;
	int CorrectAnswer = 0;
	int PlayerAnswer = 0;
	bool AnswerResult = false;
};

struct stQuizz
{
	stQuestion QuestionList[100];
	short NumberOfQuestions = 0;
	enQuestionLevel QuestionsLevel;
	enOperationType OpType;
	short NumberOfRightAnswers = 0;
	short NumberOfWrongAnswers = 0;
	bool isPass = false;
};

int ReadHowManyQuestions()
{
	int Questions = 0;
	do {

		cout << "How Many Questions You Want to Answer? ";
		cin >> Questions;

	} while (Questions < 1 || Questions > 100);

	return Questions;
}

enQuestionLevel ReadQuestionLevel()
{
	short QuestionLevel;

	do {
		cout << "Enter Questions Level : [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
		cin >> QuestionLevel;
	} while (QuestionLevel < 1 || QuestionLevel > 4);

	return (enQuestionLevel)QuestionLevel;
}

enOperationType ReadOperationType()
{
	short OperationType;

	do {

		cout << "Enter Operation Type : [1] Add, [2] Sub, [3] Mul, [4] Div, [5] MixOp ?  ";
		cin >> OperationType;

	} while (OperationType < 1 || OperationType > 5);

	return (enOperationType)OperationType;
}

int RandomNumber(int From, int To)
{
	int RandNum = rand() % (To - From + 1) + From;
	return RandNum;
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

enOperationType GetRandomOperationType()
{
	short OperationType = RandomNumber(1, 4);
	return (enOperationType)OperationType;
}

int SimpleCalculator(int number1, int number2, enOperationType OperationType)
{
	switch (OperationType)
	{
	case enOperationType::Add:
		return number1 + number2;
	case enOperationType::Sub:
		return number1 - number2;
	case enOperationType::Mul:
		return number1 * number2;
	case enOperationType::Div:
		return number1 / number2;
	default:
		return number1 + number2;


	}
}

stQuestion GenerateQuestion(enQuestionLevel QuestionLevel, enOperationType OperationType)
{
	stQuestion Question;

	if (QuestionLevel == enQuestionLevel::Mix)
	{
		QuestionLevel = (enQuestionLevel)RandomNumber(1, 3);
	}

	if (OperationType == enOperationType::MixOp)
	{
		OperationType = GetRandomOperationType();
	}

	Question.OperationType = OperationType;

	switch (QuestionLevel)
	{
	case enQuestionLevel::Easy:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;

	case enQuestionLevel::Med:
		Question.Number1 = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(10, 50);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;
	case enQuestionLevel::Hard:
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;
	}
}

void GenerateQuizzQuestions(stQuizz &Quizz)
{
	for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++)
		Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionsLevel, Quizz.OpType);
}

string GetOpTypeSympol(enOperationType Operation)
{
	string OperationTypes[5] = { "+", "-", "*", "/" , "Mix"};
	return OperationTypes[Operation - 1];
}

void PrintTheQuestion(stQuizz &Quiz, short QuestionNumber)
{
	cout << "\n";
	cout << "Question [" << QuestionNumber + 1 << "/" << Quiz.NumberOfQuestions << "] \n\n";
	cout << Quiz.QuestionList[QuestionNumber].Number1 << endl;
	cout << Quiz.QuestionList[QuestionNumber].Number2 << " ";
	cout << GetOpTypeSympol(Quiz.QuestionList[QuestionNumber].OperationType) << endl;
	cout << "______________" << endl;
}

int ReadQuestionAnswer()
{
	int Answer;
	cin >> Answer;
	return Answer;
}

void SetScreenColor(bool AnswerResult)
{
	if (AnswerResult)
		system("color 2F");
	else
		system("color 4F");
}

void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber)
{
	if (Quizz.QuestionList[QuestionNumber].CorrectAnswer != Quizz.QuestionList[QuestionNumber].PlayerAnswer)
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = false;
		Quizz.NumberOfWrongAnswers++;

		cout << "Wrong Answer" << endl;
		cout << "The Right Answer is: ";
		cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer << endl;
	}
	else
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = true;
		Quizz.NumberOfRightAnswers++;

		cout << "Right Answer";
	}

	SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}

void AskandCorrectQuestionListAnswers(stQuizz& Quizz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
	{
		PrintTheQuestion(Quizz, QuestionNumber);
		Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();
		CorrectTheQuestionAnswer(Quizz, QuestionNumber);
	}
	Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}

string GetFinalResultsText(bool pass)
{
	if (pass)
		return "Pass";
	else
		return "Fail";
}

string GetQuestionLevelText(enQuestionLevel level)
{
	string Levels[4] = { "Easy", "Med", "Hard", "Mix" };
	return Levels[level - 1];
}

void PrintQuizzResults(stQuizz Quizz)
{
	cout << "\n________________________________\n\n";
	cout << "Final Results is " << GetFinalResultsText(Quizz.isPass);
	cout << "\n________________________________\n\n";

	cout << "Number of Questions     : " << Quizz.NumberOfQuestions << endl;
	cout << "Questions Level         : " << GetQuestionLevelText(Quizz.QuestionsLevel) << endl;
	cout << "Operation Type          : " << GetOpTypeSympol(Quizz.OpType) << endl;
	cout << "Number of Right Answers : " << Quizz.NumberOfRightAnswers << endl;
	cout << "Number of Wrong Answers : " << Quizz.NumberOfWrongAnswers << endl;
	cout << "\n________________________________\n\n";

}

void PlayMathGame()
{
	stQuizz Quizz;

	Quizz.NumberOfQuestions = ReadHowManyQuestions();
	Quizz.QuestionsLevel = ReadQuestionLevel();
	Quizz.OpType = ReadOperationType();

	GenerateQuizzQuestions(Quizz);
	AskandCorrectQuestionListAnswers(Quizz);
	PrintQuizzResults(Quizz);
}

void StartGame()
{
	char PlayAgain = 'Y';

	do {
		ResetScreen();
		PlayMathGame();

		cout << endl << "Do You Want to Play Again? Y/N?";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}