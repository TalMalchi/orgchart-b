#include <iostream>
#include <vector>

using namespace std;

#include "sources/OrgChart.hpp"
using namespace ariel;

int main()
{

    OrgChart org;

    org.add_root("Tal");
    org.add_sub("Tal", "Roni");
    org.add_sub("Tal", "Yoni");
    org.add_sub("Tal", "Yuval");
    org.add_sub("Roni", "Yonatan");
    org.add_sub("Yoni", "Itay");
    org.add_sub("Yuval", "Amit");

    cout << org << endl;
    while (true)
    {
        cout << "------------------------------\n"
             << endl;
        cout << "Choose one of the action you want to do! \n"
                "1 - level order\n"
                "2 - reverse order\n"
                "3 - pre order\n"
                "4 - add root\n"
                "5 - add sub\n";

        int action;
        string name;
        string parent;
        string child;
        cin >> action;
        switch (action)
        {
        case (1):
            for (auto it = org.begin_level_order(); it != org.end_level_order(); ++it)
            {
                cout << (*it) << " ";
            }
            cout << endl;
            break;

        case (2):
            for (auto it = org.begin_reverse_order(); it != org.reverse_order(); ++it)
            {
                cout << (*it) << " ";
            }
            cout << endl;
            break;

        case (3):
            for (auto it = org.begin_preorder(); it != org.end_preorder(); ++it)
            {
                cout << (*it) << " ";
            }
            cout << endl;
            break;

        case (4):

            cout << "Enter the name of the root: ";
            cin >> name;
            org.add_root(name);
            cout << org << endl;
            break;

        case (5):

            cout << "Enter the name of the parent: ";
            cin >> parent;
            cout << "Enter the name of the child: ";
            cin >> child;
            org.add_sub(parent, child);
            cout << org << endl;
            break;

        default:
            cout << "You have entered a wrong number!\n";
            break;
        }
    }
}
