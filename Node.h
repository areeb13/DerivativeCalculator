
//header gaurd
#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>

class Node 
{
    private:
        int outer;
        int inner;
        int exp;
        std::string trig;
        Node *next;
        
    public:
        //default constructor
        Node() {outer = 1; inner = 0; exp = 0; trig = ""; next = nullptr;}
        
        //overloaded constructor
        Node(int o, int i, int e, std::string t, Node *n) 
        {outer = o; inner = i; exp = e; trig = t; next = n;}
        
        //mutuator
        void setOuter(int o) {outer = o;}
        void setInner(int i) {inner = i;}
        void setExp(int e) {exp = e;}
        void setTrig(std::string t) {trig = t;}
        void setNext(Node *n) {next = n;}
        
        //accessor
        int getOuter() const {return outer;}
        int getInner() const {return inner;}
        int getExp() const {return exp;}
        std::string getTrig() const {return trig;}
        Node* getNext() const {return next;}
        
        //overloaded << operator
        friend std::ostream& operator << (std::ostream &, const Node *);
};
#endif