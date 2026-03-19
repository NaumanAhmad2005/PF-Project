#include <iostream>
#include <cmath>
#include <string>
using namespace std;

struct Teacher
{
    string username;
    string password;
    string designation;
    string contact;
};

struct Question
{
    string text;
    string options[4];
    int correct;
};

struct Quiz
{
    string subject;
    Question q[10]; // Fixed size array for questions
};

struct Class
{
    string class_name;
    Quiz assigned_quiz; // Each class gets one quiz
};

void t_login(Teacher t[], int size);
void update_info(Teacher &t);
int create_quiz(Quiz quiz[], int count, int no_quiz);
void editQuiz(Quiz quizzes[], int quizCount);
void editQuestion(Question &question);
void assign_quiz(Class classes[], int class_count, Quiz quizzes[], int quiz_count);

int main()
{
    Teacher t[5];
    Quiz quiz[3]; // Total 3 quizzes
    Class classes[3]; // Total 3 classes
    int q_count = 0;
    int choice = -1;
    do
    {
        cout << "\n---Teacher portal---\n";
        cout << "\n1-Login\n2-Update Information\n3-Create Quiz\n4-Edit existing quiz\n5-Assign Quiz to specific class\n6-Result and grading\n0-exit\n";
        cout << "\nEnter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            t_login(t, 5);
            break;
        case 2:
            update_info(t[0]);
            break;
        case 3:
            q_count = create_quiz(quiz, q_count, 3);
            break;
        case 4:
            editQuiz(quiz, q_count);
            break;
        case 5:
            assign_quiz(classes, 3, quiz, 3); // Assign quizzes to classes
            break;
        case 6:
            // result();
            break;
        case 0:
            cout << "Exiting....!\n";
            break;
        default:
            cout << "Invalid choice, try again..\n";
        }
    } while (choice != 0);

    return 0;
}

void assign_quiz(Class classes[], int class_count, Quiz quizzes[], int quiz_count)
{
    // Allow the teacher to manually assign each quiz to a class
    for (int i = 0; i < class_count; ++i)
    {
        cout << "Assign a quiz to " << classes[i].class_name << ":\n";
        cout << "Available Quizzes:\n";
        for (int j = 0; j < quiz_count; ++j)
        {
            cout << j + 1 << ". " << quizzes[j].subject << endl;
        }
        
        int choice;
        cout << "Enter the quiz number to assign: ";
        cin >> choice;

        // Validate choice
        if (choice < 1 || choice > quiz_count)
        {
            cout << "Invalid choice. No quiz assigned.\n";
        }
        else
        {
            classes[i].assigned_quiz = quizzes[choice - 1]; // Assign selected quiz to the class
            cout << "Quiz assigned to " << classes[i].class_name << ": " << classes[i].assigned_quiz.subject << "\n";
        }
    }
}

// Other functions for login, updating info, quiz creation, etc. should go here...
