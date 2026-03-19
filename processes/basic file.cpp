#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// Structures for Teacher, Quiz, and Question
struct Teacher
{
    string username;
    string password;
    string designation;
    string contact;
};

// Structure for Question
struct Question
{
    string text;
    string options[4]; // Fixed size array for options
    int correctOption;
};

// Structure for Quiz
struct Quiz
{
    string title;
    string description;
    string subjectTag;
    Question questions[10]; // Fixed size array for questions
};

// Teacher's Dashboard
void loginTeacher(Teacher teachers[], int teacherCount);
void updateTeacherInfo(Teacher &teacher);
void createQuiz(Quiz quizzes[], int &quizCount, int maxQuizzes);
void editQuiz(Quiz quizzes[], int quizCount);
void editQuestion(Question &question);
void assignQuiz(Quiz quizzes[], int quizCount);
void viewResults();

int main()
{
    Teacher teachers[5];
    Quiz quizzes[5];
    int quizCount = 0; // Initial count is 0, will increment as quizzes are created

    int choice;
    do
    {
        cout << "\n--- Teacher's Dashboard ---\n";
        cout << "1. Login\n2. Update Info\n3. Create Quiz\n4. Edit Quiz\n5. Assign Quiz\n6. View Results\n0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            loginTeacher(teachers, 5);
            break;
        case 2:
            if (teachers[0].username != "") // Assuming a single teacher for now
                updateTeacherInfo(teachers[0]);
            else
                cout << "No teacher data available.\n";
            break;
        case 3:
            createQuiz(quizzes, quizCount, 5);
            break;
        case 4:
            editQuiz(quizzes, quizCount);
            break;
        case 5:
            assignQuiz(quizzes, quizCount);
            break;
        case 6:
            viewResults();
            break;
        case 0:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}

// Implementing the Teacher's login
void loginTeacher(Teacher teachers[], int teacherCount)
{
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    bool found = false;
    for (int i = 0; i < teacherCount; ++i)
    {
        if (teachers[i].username == username && teachers[i].password == password)
        {
            cout << "Login successful!\n";
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "Invalid username or password.\n";
    }
}

// Updating teacher's information
void updateTeacherInfo(Teacher &teacher)
{
    cout << "Enter new username: ";
    cin >> teacher.username;
    cout << "Enter new password: ";
    cin >> teacher.password;
    cout << "Enter new designation: ";
    cin >> teacher.designation;
    cout << "Enter new contact information: ";
    cin >> teacher.contact;
    cout << "Teacher information updated successfully.\n";
}

// Creating a new quiz
void createQuiz(Quiz quizzes[], int &quizCount, int maxQuizzes)
{
    if (quizCount >= maxQuizzes)
    {
        cout << "Maximum number of quizzes reached.\n";
        return;
    }

    Quiz newQuiz;
    cout << "Enter quiz title: ";
    cin >> newQuiz.title;
    cout << "Enter quiz description: ";
    cin >> newQuiz.description;
    cout << "Enter subject tag: ";
    cin >> newQuiz.subjectTag;

    for (int i = 0; i < 2; ++i) // Assuming each quiz can have 10 questions
    {
        cout << "Enter question " << (i + 1) << " text: ";
        cin >> newQuiz.questions[i].text;
        for (int j = 0; j < 4; ++j) // 4 options for each question
        {
            cout << "Enter option " << (j + 1) << ": ";
            cin >> newQuiz.questions[i].options[j];
        }
        cout << "Enter correct option number (1-4): ";
        cin >> newQuiz.questions[i].correctOption;
    }
    quizzes[quizCount] = newQuiz;
    quizCount++; // Increment quiz count after adding new quiz
    cout << "Quiz created successfully!\n";
}

// Editing an existing quiz
void editQuiz(Quiz quizzes[], int quizCount)
{
    int quizIndex;
    cout << "Enter the quiz number to edit (1-" << quizCount << "): ";
    cin >> quizIndex;

    if (quizIndex < 1 || quizIndex > quizCount)
    {
        cout << "Invalid quiz number.\n";
        return;
    }

    quizIndex--; // Adjust for zero-based indexing

    cout << "Editing quiz: " << quizzes[quizIndex].title << "\n";
    cout << "Enter new title: ";
    cin >> quizzes[quizIndex].title;
    cout << "Enter new description: ";
    cin >> quizzes[quizIndex].description;
    cout << "Enter new subject tag: ";
    cin >> quizzes[quizIndex].subjectTag;
}

// Editing a specific question
void editQuestion(Question &question)
{
    // Display the current question details
    cout << "Current question text: " << question.text << "\n";
    cout << "Current options:\n";
    for (int i = 0; i < 4; ++i) // Display current options
    {
        cout << "Option " << (i + 1) << ": " << question.options[i] << "\n";
    }
    cout << "Current correct option number: " << question.correctOption << "\n";

    // Prompt for new question text
    cout << "Enter new question text (or press Enter to keep current): ";
    string newText;
    cin.ignore(); // Clear the input buffer
    getline(cin, newText); // Use getline to allow spaces in the input
    if (!newText.empty()) // Only update if new text is provided
    {
        question.text = newText;
    }

    // Prompt for new options
    for (int i = 0; i < 4; ++i) // Editing options for the question
    {
        cout << "Enter new option " << (i + 1) << " (or press Enter to keep current): ";
        string newOption;
        getline(cin, newOption); // Use getline to allow spaces in the input
        if (!newOption.empty()) // Only update if new option is provided
        {
            question.options[i] = newOption;
        }
    }

    // Prompt for new correct option
    cout << "Enter new correct option number (1-4, or 0 to keep current): ";
    int newCorrectOption;
    cin >> newCorrectOption;
    if (newCorrectOption >= 1 && newCorrectOption <= 4) // Update if valid input is provided
    {
        question.correctOption = newCorrectOption;
    }

    cout << "Question updated successfully.\n";
}

// Assigning a quiz (Placeholder function)
void assignQuiz(Quiz quizzes[], int quizCount)
{
    cout << "Assigning quizzes. (This feature is a placeholder for now.)\n";
    for (int i = 0; i < quizCount; ++i)
    {
        cout << "Quiz " << (i + 1) << ": " << quizzes[i].title << "\n";
    }
}

// Viewing quiz results (Placeholder function)
void viewResults()
{
    cout << "Viewing quiz results. (This feature is a placeholder for now.)\n";
}
