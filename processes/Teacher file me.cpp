#include <iostream>
#include <cmath>
#include <string>

using namespace std;
// yarr ye sare structures hain simple se, teacher ke lie
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
    Question q[10]; // yani, aik quiz me maximum 10 questions hu ge
};
struct Class
{
    string class_name;
    Quiz assigned_quiz; // Each class gets one quiz
};

// ye sub teacher ke lie hain
void t_menu();
void t_login(Teacher t[], int size);
void update_info(Teacher &t);
int create_quiz(Quiz quiz[], int count, int no_quiz);
void editQuiz(Quiz quizzes[], int quizCount);
// void assign_quiz(Class class[], int size, Quiz quiz[]);
// void results();

int main()
{
    int choice = -1;
    cout << "\n1-Admin\n2-Teacher\n3-student";
    cout << "\nEnter your choice: ";
    cin >> choice;
    do
    {
        switch (choice)
        {
        case 1:
            // admin();
            break;
        case 2:
            t_menu();
            break;
        case 3:
            // s_menu();
            break;
        case 0:
            cout << "Exiting....";
            break;
        default:
            cout << "Invalid choice, try again..!\n\n";
            break;
        }
    } while (choice != 0);
}
// yar mane menu is me dal dia ha, bad me jab code combine karna ha wahain ye cheez help kare gi.
void t_menu()
{
    Teacher t[5];
    Quiz quiz[3];
    Class classes[3];
    int q_count = 0;
    int choice = -1;
    do
    {
        cout << "\n---Teacher portal---\n";
        cout << "\n1-Login\n2-Update Information\n3-Creat Quiz\n4-Edit existing quiz\n5-Assign Quiz to specific class\n6-Result and gradding\n0-exit\n";
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
            // assign_quiz(classes, 3, quiz);
            break;
        case 6:
            // results();
            break;
        case 0:
            cout << "Exiting....!";
            break;
        default:
            cout << "Invalid choice, try again..!\n\n";
        }
    } while (choice != 0);
}
// is me teacher login kare ga, admin ne teacher add karne hain or un ko id password b assign karne hain
// vo id passwords struct me save hu ge, us me se atch karain ge hum
void t_login(Teacher t[], int size)
{
    string user, pass;
    cout << "\n---Login---\n";
    cout << "\nEnter your username: ";
    cin >> user;
    cout << "Enter Your Password: ";
    cin >> pass;
    bool found = false;
    for (int i = 0; i < size; i++)
    {
        if (t[i].username == user && t[i].password == pass)
        {
            cout << "\nWelcome to teacher's portal\n";
            found = true;
            break;
        }
    }
    if ((!found))
    {
        cout << "\nInvalid username or password\n";
    }
}
// is me updation honi ha, simple sa ha ye
void update_info(Teacher &t)
{
    int choice;
    cout << "\n---Update Information---\n";
    cout << "\n1-Username\n2-Password\n3-Designation\n4-Contact\n0-Exit\n";
    cout << "\nSelect from the above: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        cout << "Enter your new User name: ";
        cin >> t.username;
        cout << "\nRecord successfully updated\n";
        break;
    case 2:
        cout << "Enter your new  password: ";
        cin >> t.password;
        cout << "\nRecord successfully updated\n";
        break;
    case 3:
        cout << "Enter your new Designation: ";
        cin >> t.designation;
        cout << "\nRecord successfully updated\n";
        break;
    case 4:
        cout << "Enter your new Contact: ";
        cin >> t.contact;
        cout << "\nRecord successfully updated\n";
        break;
    case 0:
        cout << "Exiting......!";
        break;
    default:
        cout << "Invalid choice, try again..!\n";
    }
}
// achaw yar is me outer loop me hum question manage karin ge or intenal me options, baki simple ha
// is me aik temp ka banaya ha pahle, bad ke question ke index se match kar ke use temp assign kari gaya hu
int create_quiz(Quiz quiz[], int count, int no_quiz)
{
    if (count >= no_quiz)
    {
        cout << "Maximum no of questions reached.";
        return 3;
    }

    int len = 0;
    Quiz temp;
    cout << "\n---Creat Quiz---\n\n";
    cout << "Enter Subject of Quiz: ";
    cin >> temp.subject;
    cout << "Enter Total Questions: ";
    cin >> len;
    for (int i = 0; i < len; i++)
    {
        cout << "Enter question " << (i + 1) << " text: ";
        cin >> temp.q[i].text;
        for (int j = 0; j < 4; j++)
        {
            cout << "Option " << j + 1 << ": ";
            cin >> temp.q[i].options[j];
        }
        cout << "Enter correct option number: ";
        cin >> temp.q[i].correct;
    }
    quiz[count] = temp;
    count++;
    cout << "\nQuiz Created successfully\n";
    return count;
}
// ye edit quiz ka he part ha, jo niche define hua hua ha, ye alag se banwa lia ha, ku ke pura quiz he replace karwana ha, is se pahle niche wala function perh le, ye b samaj aa jai gi
void replace(Quiz quiz[], int to_edit)
{
    Quiz temp;
    int len = 0;
    cout << "Enter Subject of Quiz: ";
    cin >> quiz[to_edit].subject;
    cout << "Enter Total Questions: ";
    cin >> len;
    for (int i = 0; i < len; i++)
    {
        cout << "Enter question " << (i + 1) << " text: ";
        cin >> temp.q[i].text;
        for (int j = 0; j < 4; j++)
        {
            cout << "Option " << j + 1 << ": ";
            cin >> temp.q[i].options[j];
        }
        cout << "Enter correct option number: ";
        cin >> temp.q[i].correct;
    }
    quiz[to_edit] = temp;
}
// ye edit quiz ka he part ha, achaww ye b simple ha bilkul, is me pahle user se puvha ha ke kon sa quiz edit karna ha
// phir vo wala pura index he utha laya hu, is me single question edit nai ho raha tha mare se, phir mane pure ka pura quiz he dubara banwa lia, itna he bohat ha yar
void editQuiz(Quiz quizz[], int count)
{
    int to_edit;
    if (count < 1)
    {
        cout << "\nNo Quiz to edit\n";
        return;
    }
    cout << "\nEnter the quiz number you want to edit (1-" << count << "): ";
    cin >> to_edit;
    if (to_edit > count)
    {
        cout << "Such a quiz does not exist!";
        return;
    }
    replace(quizz, to_edit);
}
// is wale part me error aa rahe hain :) ise dekh le yarr aik barr, logic lag gai thi per is ki calling me errors hain, logic dekh, samajaa jai ga
// acha ma filhal ise comment kar raha hu, baki dekh le, us ke bad ise b dekhin, muje is ki bilkul b samaj nai aa rahi, na gpt error bata raha ha, ajeeb pagal kia hua ha, tu dekh aik bar

/*void assign_quiz(Class clas[], int size, Quiz quiz[])
{
    for (int i = 0; i < size; ++i)
    {
        cout << "Assign a quiz to " << clas[i].class_name << ":\n";
        cout << "Available Quizzes:\n";
        for (int j = 0; j < size; ++j)
        {
            cout << j + 1 << ". " << quiz[j].subject << endl;
        }

        int choice;
        cout << "Enter the quiz number to assign: ";
        cin >> choice;

        // Validate choice
        if (choice < 1 || choice > size)
        {
            cout << "Invalid choice. No quiz assigned.\n";
        }
        else
        {
            class[i].assigned_quiz = quiz[choice - 1]; // Assign selected quiz to the class
            cout << "Quiz assigned to " << class[i].class_name << ": " << class[i].assigned_quiz.subject << "\n";
        }
    }
}*/

// is ke niche result rah gaya ha bus per vo stydent ke bad banna ha is lie mane abhi nai banaya

// is ke age se student a menu banane laga hu