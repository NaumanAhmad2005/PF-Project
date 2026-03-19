#include <iostream>
#include <string>
#include <ctime>
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

struct Teacher
{
    string username;
    string password;
    string designation;
    string contact;
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
struct Admin
{
    string username = "admin";
    string password = "admin";
};

Student students[10];
int studentCount = 0;

Quiz globalQuizzes[10]; // Shared quizzes created by teachers
int globalQuizCount = 0;

Teacher teachers[5];
int teacherCount = 0;

Admin admin;

// these are error fixes
void adminLogin();
void registerTeacher();
void updateTeacherInfo(Teacher &teacher);

// Function to register a teacher
void registerTeacher()
{
    if (teacherCount >= 5)
    {
        cout << "Maximum teachers registered. Cannot add more." << endl;
        return;
    }

    Teacher newTeacher;
    cout << "Enter Username: ";
    cin >> newTeacher.username;
    cout << "Set Password: ";
    cin >> newTeacher.password;
    cout << "Enter Designation: ";
    cin >> newTeacher.designation;
    cout << "Enter Contact: ";
    cin >> newTeacher.contact;
    teachers[teacherCount++] = newTeacher;

    cout << "Teacher registered successfully!" << endl;
}

// Function to update teacher information
void updateTeacherInfo(Teacher &teacher)
{
    int choice;
    cout << "\n---Update Information---\n";
    cout << "1. Update Username\n2. Update Password\n3. Update Designation\n4. Update Contact\n0. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        cout << "Enter new username: ";
        cin >> teacher.username;
        break;
    case 2:
        cout << "Enter new password: ";
        cin >> teacher.password;
        break;
    case 3:
        cout << "Enter new designation: ";
        cin >> teacher.designation;
        break;
    case 4:
        cout << "Enter new contact: ";
        cin >> teacher.contact;
        break;
    case 0:
        cout << "Exiting update menu." << endl;
        return;
    default:
        cout << "Invalid choice. Try again." << endl;
    }

    cout << "Information updated successfully!" << endl;
}

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

// Function to edit a quiz
void editQuiz()
{
    if (globalQuizCount == 0)
    {
        cout << "No quizzes available to edit." << endl;
        return;
    }

    cout << "Available Quizzes:" << endl;
    for (int i = 0; i < globalQuizCount; ++i)
    {
        cout << i + 1 << ". " << globalQuizzes[i].title << endl;
    }

    int quizChoice;
    cout << "Select a quiz to edit by number: ";
    cin >> quizChoice;

    if (quizChoice < 1 || quizChoice > globalQuizCount)
    {
        cout << "Invalid quiz selection." << endl;
        return;
    }

    Quiz &quiz = globalQuizzes[quizChoice - 1];

    cout << "Editing Quiz: " << quiz.title << endl;
    cout << "Enter new title (leave empty to keep current): ";
    cin.ignore();
    string newTitle;
    getline(cin, newTitle);

    if (!newTitle.empty())
    {
        quiz.title = newTitle;
    }

    for (int i = 0; i < quiz.totalQuestions; ++i)
    {
        cout << "Editing Question " << i + 1 << ": " << quiz.questions[i].text << endl;
        cout << "Enter new question text (leave empty to keep current): ";
        string newText;
        getline(cin, newText);

        if (!newText.empty())
        {
            quiz.questions[i].text = newText;
        }

        for (int j = 0; j < 4; ++j)
        {
            cout << "Option " << j + 1 << " (" << quiz.questions[i].options[j] << "): ";
            string newOption;
            getline(cin, newOption);

            if (!newOption.empty())
            {
                quiz.questions[i].options[j] = newOption;
            }
        }

        cout << "Enter new correct option number (1-4, current: " << quiz.questions[i].correctOption << "): ";
        int newCorrectOption;
        cin >> newCorrectOption;
        cin.ignore();

        if (newCorrectOption >= 1 && newCorrectOption <= 4)
        {
            quiz.questions[i].correctOption = newCorrectOption;
        }
    }

    cout << "Quiz updated successfully!" << endl;
}

// Function to assign a quiz to a student
void assignQuizToStudent()
{
    if (studentCount == 0 || globalQuizCount == 0)
    {
        cout << "No students or quizzes available to assign." << endl;
        return;
    }

    cout << "\nAvailable Students:" << endl;
    for (int i = 0; i < studentCount; ++i)
    {
        cout << i + 1 << ". " << students[i].username << endl;
    }

    int studentChoice;
    cout << "\nSelect a student by number: ";
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

// Function for teacher login
void teacherLogin()
{
    string username, password;
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;

    for (int i = 0; i < teacherCount; ++i)
    {
        if (teachers[i].username == username && teachers[i].password == password)
        {
            cout << "\nWelcome, " << teachers[i].username << "!" << endl;
            int choice;
            do
            {
                cout << "\n---Teacher Menu---\n";
                cout << "\n1. Create Quiz\n2. Edit Quiz\n3. Assign Quiz to Student\n4. Update Information\n0. Logout\n";
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice)
                {
                case 1:
                    createQuiz();
                    break;
                case 2:
                    editQuiz();
                    break;
                case 3:
                    assignQuizToStudent();
                    break;
                case 4:
                    updateTeacherInfo(teachers[i]);
                    break;
                case 0:
                    cout << "Logging out...\n";
                    break;
                default:
                    cout << "Invalid choice. Try again." << endl;
                }
            } while (choice != 0);

            return;
        }
    }

    cout << "Invalid username or password." << endl;
}

// Function to register a student
void registerStudent()
{
    if (studentCount >= 10)
    {
        cout << "Maximum students registered. Cannot add more." << endl;
        return;
    }

    Student newStudent;
    cout << "Enter Username: ";
    cin >> newStudent.username;
    cout << "Set Password: ";
    cin >> newStudent.password;
    cout << "Enter Contact: ";
    cin >> newStudent.contact;
    newStudent.quizCount = 0;
    students[studentCount++] = newStudent;

    cout << "Student registered successfully!" << endl;
}

// Function for student login
int studentLogin()
{
    string username, password;
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;

    for (int i = 0; i < studentCount; ++i)
    {
        if (students[i].username == username && students[i].password == password)
        {
            cout << "Login successful! Welcome, " << students[i].username << "!" << endl;
            return i;
        }
    }

    cout << "Invalid username or password." << endl;
    return -1;
}

// Function to view assigned quizzes
void viewAssignedQuizzes(const Student &student)
{
    if (student.quizCount == 0)
    {
        cout << "No quizzes assigned yet." << endl;
        return;
    }

    cout << "Assigned Quizzes:\n";
    for (int i = 0; i < student.quizCount; ++i)
    {
        cout << i + 1 << ". " << student.assignedQuizzes[i].title << endl;
    }
}

// Function to view grades
void viewGrades(const Student &student)
{
    if (student.grades.empty())
    {
        cout << "No grades available yet." << endl;
    }
    else
    {
        cout << "Grades: " << student.grades << endl;
    }
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

// Function to display the student menu
void studentMenu(Student &student)
{
    int choice;
    do
    {
        cout << "\n---Student Menu---\n";
        cout << "1. View Assigned Quizzes\n2. Take Quiz\n3. View Grades\n0. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            viewAssignedQuizzes(student);
            break;
        case 2:
            takeQuiz(student);
            break;
        case 3:
            viewGrades(student);
            break;
        case 0:
            cout << "Logging out..." << endl;
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 0);
}

// Main menu
void mainMenu()
{
    int choice;
    do
    {
        cout << "\nMain Menu:\n";
        cout << "\n1- Admin Login\n2. Teacher Login\n3. Student Login\n0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            adminLogin();
            break;
        case 2:
            teacherLogin();
            break;
        case 3:
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
//this function is to update admin.
void updateAdmin()
{
    int choice;
    cout << "\n---Update Admin's Information---\n";
    cout << "\n1- Username\n2- Password\nEnter your choice: ";
    cin >> choice;
    // do
    // {
    switch (choice)
    {
    case 1:
        cout << "Enter new username: ";
        cin >> admin.username;
        break;
    case 2:
        cout << "Enter new password: ";
        cin >> admin.password;
        break;
    default:
        cout << "Invalid choice. Please try again." << endl;
        break;
    }
    // } while (choice != 1 || choice != 2);
}
void registerUser()
{
    int choice;
    cout << "\n---Register User---\n";
    cout << "\n1- Teacher\n2- Student\nenter your Choice: ";
    cin >> choice;
    // do
    // {
    switch (choice)
    {
    case 1:
        registerTeacher();
        break;
    case 2:
        registerStudent();
        break;
    default:
        cout << "Invalid choice. Please try again." << endl;
        break;
    }
    // } while (choice != 1 || choice != 2);
}
void searchUser()
{
    int choice;
    cout << "\n---Search user---\n";
    cout << "\n1. Teacher \n2. Student\nEnter your choice: ";
    cin >> choice;

    if (choice == 1) // Search Teacher
    {
        string username;
        cout << "Enter the teacher's username to search: ";
        cin >> username;

        for (int i = 0; i < teacherCount; ++i)
        {
            if (teachers[i].username == username)
            {
                cout << "Teacher found:\n";
                cout << "Username: " << teachers[i].username << "\n";
                cout << "Designation: " << teachers[i].designation << "\n";
                cout << "Contact: " << teachers[i].contact << "\n";
                return;
            }
        }
        cout << "Teacher not found." << endl;
    }
    else if (choice == 2) // Search Student
    {
        string username;
        cout << "Enter the student's username to search: ";
        cin >> username;

        for (int i = 0; i < studentCount; ++i)
        {
            if (students[i].username == username)
            {
                cout << "Student found:\n";
                cout << "Username: " << students[i].username << "\n";
                cout << "Contact: " << students[i].contact << "\n";
                cout << "Grades: " << students[i].grades << "\n";
                return;
            }
        }
        cout << "Student not found." << endl;
    }
    else
    {
        cout << "Invalid choice." << endl;
    }
}

// Function to delete a teacher or student
void deleteUser()
{
    int choice;
    cout << "---Delete user---";
    cout << "Delete: \n1. Teacher \n2. Student\nEnter your choice: ";
    cin >> choice;

    if (choice == 1) // Delete Teacher
    {
        string username;
        cout << "Enter the teacher's username to delete: ";
        cin >> username;

        for (int i = 0; i < teacherCount; ++i)
        {
            if (teachers[i].username == username)
            {
                for (int j = i; j < teacherCount - 1; ++j)
                {
                    teachers[j] = teachers[j + 1];
                }
                --teacherCount;
                cout << "Teacher deleted successfully." << endl;
                return;
            }
        }
        cout << "Teacher not found." << endl;
    }
    else if (choice == 2) // Delete Student
    {
        string username;
        cout << "Enter the student's username to delete: ";
        cin >> username;

        for (int i = 0; i < studentCount; ++i)
        {
            if (students[i].username == username)
            {
                for (int j = i; j < studentCount - 1; ++j)
                {
                    students[j] = students[j + 1];
                }
                --studentCount;
                cout << "Student deleted successfully." << endl;
                return;
            }
        }
        cout << "Student not found." << endl;
    }
    else
    {
        cout << "Invalid choice." << endl;
    }
}
void adminLogin()
{
    string username, password;
    cout << "Enter admin username: ";
    cin >> username;
    cout << "Enter admin password: ";
    cin >> password;

    if (admin.username == username && admin.password == password)
    {
        cout << "\nWelcome, " << admin.username << "!" << endl;
        int choice;
        do
        {
            cout << "\n---Admin's menu---\n";
            cout << "\n1. Update information \n2. Register user\n3. Search user\n4. Delete user\n0. Logout\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                updateAdmin();
                break;
            case 2:
                registerUser();
                break;
            case 3:
                searchUser();
                break;
            case 4:
                deleteUser();
                break;
            case 0:
                cout << "Logging out...\n";
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
            }
        } while (choice != 0);
    }
    else
        cout << "Invalid username or password." << endl;
}

int main()
{
    mainMenu();
    return 0;
}