#include <iostream>
#include <cmath>
#include <string>
using namespace std;

void s_menu();
void s_update();
void s_view_assigned();
void s_take_quiz();
void s_submit();
void s_view_result();
void s_grade();

struct student{
    string username;
    string password;
    string id;
};

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
            // t_menu();
            break;
        case 3:
            s_menu();
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

void s_menu()
{
    int choice = -1;
    do
    {
        cout << "\n---Teacher portal---\n";
        cout << "\n1-Update information\n2-View assigned Quiz\n3-Taking Quiz\n4-Submit Quiz\n5-View Result\n6-View result of each Quiz\n0-exit\n";
        cout << "\nEnter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            s_update();
            break;
        case 2:
            s_view_assigned();
            break;
        case 3:
            s_take_quiz();
            break;
        case 4:
            s_submit();
            break;
        case 5:
            s_view_result();
            break;
        case 6:
            s_grade();
            break;
        case 0:
            cout << "Exiting....!";
            break;
        default:
            cout << "Invalid choice, try again..!\n\n";
        }
    } while (choice != 0);
}