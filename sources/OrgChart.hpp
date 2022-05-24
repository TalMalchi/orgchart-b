#include <iostream>
using namespace std;
#include <string>
#include <iterator>
#include <algorithm>
#include <stack>
#include <queue>
#include <deque>
#include <vector>

namespace ariel
{

    class OrgChart
    {

        struct Node
        {
            string data;
            Node *parent;
            vector<Node *> children;
            //  constructor
            Node(const string &v, Node *n, vector<Node *> children)
                : data(v), parent(n), children(move(children)) {}
        };
        Node *root;
        Node *find_node(Node *n, const string &name); // find if a node in the OrgChart

        // iterator type
        enum iterator_type
        {
            level,
            reverse,
            preorder
        };

        /*-----------------Inner Class------------------- */

        class Iterator
        {

        private:
            Node *root;
            queue<Node *> my_queue1; // defualt queue
            queue<Node *> my_queue2; // level order
            stack<Node *> my_stack;  // reverse
            queue<Node *> my_queue3; // reverse

            iterator_type it_type;

        public:
            // constructor
            Iterator(Node *p, iterator_type type) : root(p), it_type(type)
            {
                init(p); // initilize the iterator
            }

            Iterator()
            {
                root = nullptr;
                it_type = level;
            };
            // constructor
            Iterator(Node *n)
            {
                root = n;
                it_type = level;
            }

            // operator
            Iterator &operator++();

            // equality operator
            bool operator==(const Iterator &other) const;

            bool operator!=(const Iterator &other) const;
            // acssess to the current node
            string &operator*();
            // access to the value of the current node
            string *operator->();

            void init(Node *p);
        };

    public:
        // constructor
        OrgChart() : root(nullptr){};

        ~OrgChart()
        {

            delete_chart(root);
        }
        // delete the whole OrgChart
        void delete_chart(Node *n);

      
        OrgChart &operator=(const OrgChart &other)= default;
        OrgChart &operator=(OrgChart &&other) noexcept= default;
        
        //copy constructor
        OrgChart(const OrgChart &other)
        {
            root = new Node(other.root->data, nullptr, other.root->children);
            for (Node *n : other.root->children)
            {
                root->children.push_back(new Node(n->data, root, n->children));
            }
        }
        //move constructor
        OrgChart(OrgChart &&other) noexcept
        {
            root = other.root;
            other.root = nullptr;
        }
     

        friend ostream &operator<<(ostream &os, const OrgChart &org);

        OrgChart &add_root(const string &name);                       // add a root to the org chart, if there is a root already, he will be replaced
        OrgChart &add_sub(const string &parent, const string &child); // child is under parent in the org chart. if parent not in the org chart, it will be added, throws an exception if child already in the org chart
        Iterator begin_level_order();
        Iterator end_level_order();
        Iterator begin_reverse_order();
        Iterator reverse_order();
        Iterator begin_preorder();
        Iterator end_preorder();
        Iterator begin();
        Iterator end();
    };

};
