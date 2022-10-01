#include "LList.h"
#include "Node.h"

//the following overloads the list
LList::LList(Node *h) {
    //if list exists then delete it first
    if (head != nullptr){
        while (head)
        {
            Node *cur = head;
            head = head->getNext();
            delete cur;
        }
    }
    
    //the following sets the linked list to the
    //one created in main
    Node *newNode = new Node;
    head = newNode;
    
    *head = *h;
    Node *old = h, *cur = head;
    
    while (old->getNext() != nullptr)
    {
        Node *newNode = new Node;
        
        cur->setNext(newNode);
        *cur->getNext() = *old->getNext();
        cur = cur->getNext();
        old = old->getNext();
    }
}

//this sets head directly (which is the linked list)
void LList::setHead(Node *h)
{
    //make sure it is empty
    if (head != nullptr){
        while (head)
        {
            Node *cur = head;
            head = head->getNext();
            delete cur;
        }
    }
    
    //copy list in main to this list
    Node *newNode = new Node;
    head = newNode;
    
    *head = *h;
    Node *old = h, *cur = head;
    
    while (old->getNext() != nullptr)
    {
        Node *newNode = new Node;
        
        cur->setNext(newNode);
        *cur->getNext() = *old->getNext();
        cur = cur->getNext();
        old = old->getNext();
    }
}

//this sorts based on exponent value
void LList::sort()
{
    Node *cur, *before;
    bool flag;
    
    //bubble sort algorithm based on exponents
    do
    {
        flag = false;
        cur = head;
        before = nullptr;
        
        while (cur->getNext() != nullptr)
        {
            //sees if next node is greater or checks for trig
            if ((((cur->getExp()) < (cur->getNext()->getExp())) && (cur->getNext()->getTrig() == "")) 
                || ((cur->getTrig() != "") && (cur->getNext()->getTrig() == "")))
            {
                Node *temp = cur->getNext();
                
                //the following switches nodes
                cur->setNext(temp->getNext());
                temp->setNext(cur);
                
                if (before == nullptr)
                    head = temp;
                else
                    before->setNext(temp);
                
                before = temp; //since switch, make before equal to temp
                
                flag = true;
            }
            else {  //if no switch then move before and cur
                before = cur;
                cur = cur->getNext();
            }
        }
    }while (flag);
}

//this is used to access linked list based on [] operator
const Node* LList::operator[](const int num)
{
    const Node *cur = head;
    
    //for loop until node is reached
    for (int i = 0; i < num; i++)
    {
        cur = cur->getNext();
    }
    return cur;
}

//this is used to output linked list
std::ostream& operator<<(std::ostream& out, LList& list)
{
    bool firstTime = true;
    char sign;
    int i = 0;
    
    //while list node is not null
    while (list[i])
    {
        //the following outputs based on outer 
        if (firstTime && list[i]->getNext() == nullptr && list[i]->getOuter() == 0)
            out << "0";
        else if (list[i]->getOuter() == 0)
            out << "";
        else if (firstTime) {
            if (list[i]->getOuter() < 0)
                out << "-" << list[i];
            else
                out << list[i];
            firstTime = false;
        }
        //output if above not valid
        else {
            if (list[i]->getOuter() < 0) 
                sign = '-';
            else
                sign = '+';
            
            out << " " << sign << " " << list[i];
        }
        i++;
    }
    out << std::endl;
    
    return out;
}

//this store node into list
void LList::operator>>(Node* &node)
{
    node->setNext(head);
    
    head = node;
}

//this destructor delete linked list
LList::~LList()
{
    Node *cur = head;
    Node *next = nullptr;
    
    while (cur)
    {
        next = cur->getNext();
        free(cur);
        cur = next;
    }
    
    head = nullptr;
}

