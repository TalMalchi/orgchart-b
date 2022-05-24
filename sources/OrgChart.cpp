#include <iostream>
#include <queue>
using namespace std;
#include "OrgChart.hpp"

namespace ariel
{


    OrgChart &OrgChart::add_root(const string &name)
    {
        if(name.empty())
        {
            throw "empty name";
        }

        if (root != nullptr) // if there is a root already, he will be replaced
        {
            Node *new_root = new Node(name, nullptr, root->children);
            delete root;
            root = new_root;
        }

        else
        {
            root = new Node(name, nullptr, vector<Node *>());
        }

        return *this;
    }
    // child is under parent in the org chart. if parent not in the org chart, it will be added, throws an exception if child already in the org chart
    OrgChart &OrgChart::add_sub(const string &parent, const string &child)
    {
        if(parent.empty() || child.empty())
        {
            throw "empty name";
        }
        Node *parent_node = find_node(root, parent);
        if (parent_node == nullptr)
        {
            throw "parent not in the org chart";
        }

        Node *new_child = new Node(child, parent_node, vector<Node *>());
        parent_node->children.push_back(new_child);

        return *this;
    }
    OrgChart::Iterator OrgChart::begin_level_order()
    {
        if (this->root == nullptr)
        {
            throw "the org chart is empty";
        }

        return Iterator(root, level);
    }
    OrgChart::Iterator OrgChart::end_level_order()
    {
        if (this->root == nullptr)
        {
            throw "the org chart is empty";
        }
        return Iterator(nullptr);
    }
    OrgChart::Iterator OrgChart::begin_reverse_order()
    {
        if (this->root == nullptr)
        {
            throw "the org chart is empty";
        }
        return Iterator(root, reverse);
    }
    OrgChart::Iterator OrgChart::reverse_order()
    {
        if (this->root == nullptr)
        {
            throw "the org chart is empty";
        }
        return Iterator(nullptr);
    }
    OrgChart::Iterator OrgChart::begin_preorder()
    {
        if (this->root == nullptr)
        {
            throw "the org chart is empty";
        }
        return Iterator(root, preorder);
    }
    OrgChart::Iterator OrgChart::end_preorder()
    {
        if (this->root == nullptr)
        {
            throw "the org chart is empty";
        }
        return Iterator(nullptr);
    }
    OrgChart::Iterator OrgChart::begin()
    {
        if (this->root == nullptr)
        {
            throw "the org chart is empty";
        }
        return Iterator(root, level);
    }
    OrgChart::Iterator OrgChart::end()
    {
        if (this->root == nullptr)
        {
            throw "the org chart is empty";
        }
        return Iterator(nullptr);
    }

    void OrgChart::delete_chart(OrgChart::Node *n)
    {
        if (n == nullptr)
        {
            return;
        }
        // delete the children
        for (Node *child : n->children)
        {
            delete_chart(child);
        }
        delete n;
    }


    OrgChart::Iterator &OrgChart::Iterator::operator++()
    {
        if (!my_queue1.empty())
        {
            // pop the first node
            my_queue1.pop();
        }
        if (my_queue1.empty())
        {
            *this = Iterator(nullptr);
        }
        return *this;
    }
    bool OrgChart::Iterator::operator==(const Iterator &other) const
    {
        return root == other.root;
    }
    bool OrgChart::Iterator::operator!=(const Iterator &other) const
    {
        if (my_queue1.empty())
        {   //im in the end
            return false;
        }

        return !(*this == other);
    }
            // access to the value of the current node
    string *OrgChart::Iterator::operator->()
    {
        return &my_queue1.front()->data;
    }
               // acssess to the current node
    string &OrgChart::Iterator::operator*()
    {
        return my_queue1.front()->data;
    }

    void OrgChart::Iterator::init(OrgChart::Node *p)
    {
        if (it_type == level)
        {
            //push the root to the queue
            my_queue2.push(p);
            while (!my_queue2.empty())
            {
                //go over the first element children
                for (Node *n : my_queue2.front()->children)
                {
                    my_queue2.push(n);
                }
                //push the first element to the queue1
                my_queue1.push(my_queue2.front());
                my_queue2.pop();
            }
        }

        else if (it_type == reverse)
        {
            //push the root 
            my_queue3.push(p);

            while (!my_queue3.empty())
            {
                stack<Node *> temp;
                for (Node *n : my_queue3.front()->children)
                {
                    //push the children to the stack
                    temp.push(n);
                }
                while (!temp.empty())
                {
                    my_queue3.push(temp.top());
                    temp.pop();
                }
                my_stack.push(my_queue3.front());
                my_queue3.pop();
            }
            // pass the stack to the defualt queue
            while (!my_stack.empty())
            {
                my_queue1.push(my_stack.top());
                my_stack.pop();
            }
        }
        else if (it_type == preorder)
        {
            // implement preorder
            my_stack.push(p);
            while (!my_stack.empty())
            {
                Node *temp = my_stack.top();
                my_queue1.push(temp); // push to defualt queue
                my_stack.pop();
                stack<Node *> temp_stack;
                for (Node *n : temp->children)
                {
                    temp_stack.push(n);
                }
                while (!temp_stack.empty())
                {
                    my_stack.push(temp_stack.top());
                    temp_stack.pop();
                }
            }
        }
    }

    OrgChart::Node *OrgChart::find_node(Node *n, const string &name)
    {
        if (n == nullptr)
        {
            return NULL;
        }

        if (n->data == name)
        {
            return n;
        }

        for (size_t i = 0; i < n->children.size(); i++)
        {
            Node *temp = find_node(n->children.at(i), name);
            if (temp != nullptr)
            {
                return temp;
            }
        }

        return NULL;
    }

    ostream &operator<<(ostream &os, const OrgChart &org)
    {
        // pretty print for the OrgChart
        queue<OrgChart::Node *> my_queue;
        my_queue.push(org.root);
        while (!my_queue.empty())
        {
            OrgChart::Node *temp = my_queue.front();
            my_queue.pop();
            if (temp->children.empty())
            {
                // print the parent
                os << temp->data << ":-------i have no children------\n";
            }
            else
            {
                os << temp->data << ": ----my child are-----";
                // print the children
                for (OrgChart::Node *child : temp->children)
                {

                    os << child->data << " ";
                }
                os << endl;
                // push the children to the queue
                for (OrgChart::Node *child : temp->children)
                {
                    my_queue.push(child);
                }
            }
        }
        return os;
    }
}