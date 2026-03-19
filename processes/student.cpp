#include <iostream>
#include <string>

using namespace std;

struct Question
{
    string text;
    string options[4];
    int correctOption;
};

struct Quiz
{
    string title;
    Question questions[10]; // Maximum 10 questions
    int totalQuestions;
    int correctAnswers;
};

struct Student
{
    string username;
    string password;
    string contact;
    string grades;
    Quiz assignedQuizzes[10]; // Maximum 10 quizzes
    int quizCount;
};

Student students[10];
int studentCount = 0;

Quiz globalQuizzes[10]; // Shared quizzes created by teachers
int globalQuizCount = 0;

// Function to create a quiz (for teacher use)
void createQuiz()
{
    if (globalQuizCount >= 10)
    {
        cout << "Maximum number of quizzes reached." << endl;
        return;
    }

    Quiz newQuiz;
    cout << "Enter Quiz Title: ";
    cin.ignore();
    getline(cin, newQuiz.title);

    cout << "Enter Number of Questions (max 10): ";
    cin >> newQuiz.totalQuestions;

    for (int i = 0; i < newQuiz.totalQuestions; ++i)
    {
        cout << "Enter Question " << i + 1 << ": ";
        cin.ignore();
        getline(cin, newQuiz.questions[i].text);

        for (int j = 0; j < 4; ++j)
        {
            cout << "Option " << j + 1 << ": ";
            getline(cin, newQuiz.questions[i].options[j]);
        }

        cout << "Enter the correct option number (1-4): ";
        cin >> newQuiz.questions[i].correctOption;
    }

    globalQuizzes[globalQuizCount++] = newQuiz;
    cout << "Quiz created successfully!" << endl;
}

// Function to assign a quiz to a student
void assignQuizToStudent()
{
    if (studentCount == 0 || globalQuizCount == 0)
    {
        cout << "No students or quizzes available to assign." << endl;
        return;
    }

    cout << "Available Students:" << endl;
    for (int i = 0; i < studentCount; ++i)
    {
        cout << i + 1 << ". " << students[i].username << endl;
    }

    int studentChoice;
    cout << "Select a student by number: ";
    cin >> studentChoice;

    if (studentChoice < 1 || studentChoice > studentCount)
    {
        cout << "Invalid student selection." << endl;
        return;
    }

    Student &selectedStudent = students[studentChoice - 1];

    cout << "Available Quizzes:" << endl;
    for (int i = 0; i < globalQuizCount; ++i)
    {
        cout << i + 1 << ". " << globalQuizzes[i].title << endl;
    }

    int quizChoice;
    cout << "Select a quiz by number: ";
    cin >> quizChoice;

    if (quizChoice < 1 || quizChoice > globalQuizCount)
    {
        cout << "Invalid quiz selection." << endl;
        return;
    }

    if (selectedStudent.quizCount >= 10)
    {
        cout << "This student already has the maximum number of quizzes assigned." << endl;
        return;
    }

    selectedStudent.assignedQuizzes[selectedStudent.quizCount++] = globalQuizzes[quizChoice - 1];
    cout << "Quiz assigned successfully to " << selectedStudent.username << "!" << endl;
}

// Function to take a quiz
void takeQuiz(Student &student)
{
    if (student.quizCount == 0)
    {
        cout << "No quizzes assigned to take." << endl;
        return;
    }

    int choice;
    cout << "Enter the quiz number you want to take: ";
    cin >> choice;

    if (choice < 1 || choice > student.quizCount)
    {
        cout << "Invalid quiz number." << endl;
        return;
    }

    Quiz &quiz = student.assignedQuizzes[choice - 1];
    int correct = 0;
    cout << "Taking Quiz: " << quiz.title << endl;

    for (int i = 0; i < quiz.totalQuestions; ++i)
    {
        cout << "Question " << i + 1 << ": " << quiz.questions[i].text << endl;
        for (int j = 0; j < 4; ++j)
        {
            cout << j + 1 << ". " << quiz.questions[i].options[j] << endl;
        }

        int answer;
        cout << "Your answer: ";
        cin >> answer;

        if (answer == quiz.questions[i].correctOption)
        {
            ++correct;
        }
    }

    quiz.correctAnswers = correct;
    cout << "Quiz completed! Correct Answers: " << correct << "/" << quiz.totalQuestions << endl;
}

// Main menu
void mainMenu()
{
    int choice;
    do
    {
        cout << "\nMain Menu:\n";
        cout << "1. Register Student\n2. Create Quiz (Teacher)\n3. Assign Quiz to Student\n4. Student Login\n0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            registerStudent();
            break;
        case 2:
            createQuiz();
            break;
        case 3:
            assignQuizToStudent();
            break;
        case 4:
        {
            int studentIndex = studentLogin();
            if (studentIndex != -1)
            {
                studentMenu(students[studentIndex]);
            }
            break;
        }
        case 0:
            cout << "Exiting program..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
}

int main()
{
    mainMenu();
    return 0;
}
