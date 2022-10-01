
//header gaurd
#ifndef LLIST_H
#define LLIST_H

#include "Node.h"

class LList
{
    private:
        Node *head = nullptr;
    public:
        //default constructor
        LList() {head = nullptr;}
        
        //overloaded constructor
        LList(Node *); 
        
        //destructor
        ~LList();
        
        //mutator
        void setHead(Node *);
        
        //accessor
        Node* getHead() const {return head;}
        
        //sort list
        void sort();
        
        //overloaded [] operator
        const Node* operator[](const int);
        
        //overloaded << operator
        friend std::ostream& operator<<(std::ostream&, LList&);
        
        //overloaded >> operator
        void operator>>(Node *&);
};
#endif