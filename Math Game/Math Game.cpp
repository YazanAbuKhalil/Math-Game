
#pragma warning(disable : 4996)

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

enum enQuestionLevel { Easy = 1, Med = 2, Hard = 3, Mix = 4 };

enum enOpType { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5 };

struct stQuestion {
    int Number1 = 0;
    int Number2 = 0;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool AnswerResult = false;
    enQuestionLevel QuestionLevel;
    enOpType OpType;

};

struct stQuizz {
    stQuestion QuestionsList[100];
    short NumberOfQuestions = 0;
    enQuestionLevel QuestionLevel;
    enOpType OpType;
    short NumberOfRightAnswers = 0;
    short NumberOfWrongAnswers = 0;
    bool IsPass = false;
};

int RandomNumber(int From, int To) {

    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}

short ReadHowManyQuestion() {
    short NumberOfQuestions = 0;
    cout << "How many questions do you want to answer ? ";
    cin >> NumberOfQuestions;

    return NumberOfQuestions;
}

enQuestionLevel ReadQuestionsLevel() {
    short QuestionLevel = 0;

    do {
        cout << "Enter Questions level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
        cin >> QuestionLevel;
    } while (QuestionLevel < 1 || QuestionLevel > 4);


    return (enQuestionLevel)QuestionLevel;
}

enOpType ReadOperationType() {
    short OpType = 0;
    do {
        cout << "Enter Operation type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
        cin >> OpType;
    } while (OpType < 1 || OpType > 5);


    return (enOpType)OpType;

}

void ResetScreen() {
    system("cls");
    system("color 0F");
}

int GetCorrectAnswer(int Number1, int Number2, enOpType OpType) {



    switch (OpType) {
    case enOpType::Add:
        return Number1 + Number2;

    case enOpType::Sub:
        return Number1 - Number2;

    case enOpType::Mul:
        return Number1 * Number2;

    case enOpType::Div:
        return Number1 / Number2;
    }

}

int ReadPlayerAnswer() {
    int Answer = 0;
    cin >> Answer;
    return Answer;
}

bool CheckAnswer(int PlayerAnswer, int CorrectAnswer) {
    return PlayerAnswer == CorrectAnswer;
}

string GetOperationSympol(enOpType OpType) {
    if (OpType == enOpType::Add)
        return "+";
    else if (OpType == enOpType::Sub)
        return "-";
    else if (OpType == enOpType::Mul)
        return "*";
    else if (OpType == enOpType::Div)
        return "/";
    else {
        return "Mix";
    }
}

string StringQuestionLevel(enQuestionLevel QuestionLevel) {

    string arrQuestionLevel[4] = { "Easy", "Med", "Hard", "Mix" };
    return arrQuestionLevel[QuestionLevel - 1];
}

void PrintTheQuestion(stQuizz& Quizz, short QuestionNumber) {
    cout << "\nQuestion [" << QuestionNumber + 1 << "]\n\n";
    cout << Quizz.QuestionsList[QuestionNumber].Number1 << endl;
    cout << Quizz.QuestionsList[QuestionNumber].Number2 << " " << GetOperationSympol(Quizz.QuestionsList[QuestionNumber].OpType) << endl;
    cout << "\n-----------\n";
}

void SetScreenColor(bool AnswerResult) {

    if (AnswerResult)
        system("color 2F");
    else
        system("color 4F");
}

void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber) {

    if (Quizz.QuestionsList[QuestionNumber].PlayerAnswer != Quizz.QuestionsList[QuestionNumber].CorrectAnswer) {
        Quizz.QuestionsList[QuestionNumber].AnswerResult = false;
        Quizz.NumberOfWrongAnswers++;

        cout << "\nWrong Answer :-(\n";
        cout << "The right answer is : " << Quizz.QuestionsList[QuestionNumber].CorrectAnswer;
        cout << "\a";
    }
    else {
        Quizz.QuestionsList[QuestionNumber].AnswerResult = true;
        Quizz.NumberOfRightAnswers++;

        cout << "\nRight Answer :-)\n";

    }
    cout << endl;
    SetScreenColor(Quizz.QuestionsList[QuestionNumber].AnswerResult);
}

void AskAndCorrectQuestionListAnswers(stQuizz& Quizz) {

    for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++) {

        PrintTheQuestion(Quizz, QuestionNumber);
        Quizz.QuestionsList[QuestionNumber].PlayerAnswer = ReadPlayerAnswer();
        CorrectTheQuestionAnswer(Quizz, QuestionNumber);
    }

    Quizz.IsPass = Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers;
}

stQuestion GenerateQuestion(enQuestionLevel QuestionLevel, enOpType OpType) {

    stQuestion Question;

    Question.OpType = OpType;
    Question.QuestionLevel = QuestionLevel;

    if (OpType == enOpType::MixOp) {
        Question.OpType = (enOpType)RandomNumber(1, 4);
    }
    if (QuestionLevel == enQuestionLevel::Mix) {
        Question.QuestionLevel = (enQuestionLevel)RandomNumber(1, 3);
    }


    switch (Question.QuestionLevel) {

    case enQuestionLevel::Easy:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);
        Question.CorrectAnswer = GetCorrectAnswer(Question.Number1, Question.Number2, Question.OpType);
        return Question;


    case enQuestionLevel::Med:
        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);
        Question.CorrectAnswer = GetCorrectAnswer(Question.Number1, Question.Number2, Question.OpType);
        return Question;

    case enQuestionLevel::Hard:
        Question.Number1 = RandomNumber(50, 100);
        Question.Number2 = RandomNumber(50, 100);
        Question.CorrectAnswer = GetCorrectAnswer(Question.Number1, Question.Number2, Question.OpType);
        return Question;
    }
}

void GenerateQuizzQuestions(stQuizz& Quizz) {

    stQuestion Question;

    for (short i = 0; i < Quizz.NumberOfQuestions; i++) {
        Quizz.QuestionsList[i] = GenerateQuestion(Quizz.QuestionLevel, Quizz.OpType);
    }
}

string GetFinalResultsText(bool IsPass) {

    if (IsPass)
        return "Pass :-)";
    else
        return "Fail :-(";
}

void SetFinalScreenColor(bool IsPass) {

    if (IsPass)
        system("color 2F");
    else
        system("color 4F");

}

void PrintQuizzResults(stQuizz Quizz) {

    cout << "\n";
    cout << "\n---------------------------\n";
    cout << "Final Results is " << GetFinalResultsText(Quizz.IsPass);
    cout << "\n---------------------------\n";

    cout << "\nNumber of Questions: " << Quizz.NumberOfQuestions << endl;
    cout << "Questions level      :" << StringQuestionLevel(Quizz.QuestionLevel) << endl;
    cout << "OpType               :" << GetOperationSympol(Quizz.OpType) << endl;
    cout << "Number of right answers: " << Quizz.NumberOfRightAnswers << endl;
    cout << "Number of wrong answers: " << Quizz.NumberOfWrongAnswers << endl;

    cout << "\n---------------------------\n";

    SetFinalScreenColor(Quizz.IsPass);
}

void PlayGame() {

    stQuizz Quizz;

    Quizz.NumberOfQuestions = ReadHowManyQuestion();
    Quizz.QuestionLevel = ReadQuestionsLevel();
    Quizz.OpType = ReadOperationType();

    GenerateQuizzQuestions(Quizz);
    AskAndCorrectQuestionListAnswers(Quizz);
    PrintQuizzResults(Quizz);

}

void StartGame() {

    char PlayAgain = 'y';
    do {
        ResetScreen();
        PlayGame();

        cout << "\nDo you want to play again y/n ?";
        cin >> PlayAgain;
    } while (PlayAgain == 'y' || PlayAgain == 'Y');
}

int main()
{

    // Seeds the random number generator in C++, called only once
    srand((unsigned)time(NULL));

    StartGame();

    return 0;

}



