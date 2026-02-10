#include <iostream>

using namespace std;

class Node
{
public:
    Node(int val, Node * next=NULL)
        : val_(val), next_(next)
    {}
    int val_;
    Node * next_;
};

int main()
{
    int n;
    cin >> n;

    int i;
    cin >> i;
    Node * node = new Node(i); 
    Node * head = node;
    
    for (int i = 1; i < n; ++i)
    {
        int v;
        cin >> v;
        node->next_ = new Node(v);
        node = node->next_;
    }

    node = head;
    Node * next;
    Node * prev = NULL;
    while (head != NULL)
    {
        next = head->next_;
        head->next_ = prev;
        prev = head;
        head = next;
    }

    node = prev;
    
    while (node != NULL)
    {
        cout << node->val_ << ' ';
        node = node->next_;
    }
    cout << endl;
    
    return 0;
}
