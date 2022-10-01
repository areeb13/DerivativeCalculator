#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include "LList.h"
#include "Node.h"
using namespace std;

void parseEquation(string, Node*&);
void deleteList(Node* &);
void calcDeriv(LList &list);

int main()
{
    string inFile;
    //get input file and open
    cin >> inFile;
    ifstream inputFile;
    inputFile.open(inFile);
    
    //if input file opens then do following
    if (inputFile)
    {
        string line;
        Node *head = nullptr;
        
        //get each equation from file
        while (getline(inputFile, line))
        {
            //parse equation into nodes
            parseEquation(line, head);
            //create list and store created linked list
            LList list(head);
            //calc deriv of each node
            calcDeriv(list);
            //sort greatest to least by exponents
            list.sort();
            //output list
            cout << list;
            //delete list created
            deleteList(head);
        }
    }
    //close file
    inputFile.close();
}

//parse equation and store variables in linked list
void parseEquation(string line, Node* &head)
{
    int sign = 1;
    string command;
    bool firstTime = true;
    
    //do following until line is empty
    while (line.length() > 0)
    {
        
        Node *newNode = new Node;
        
        //when there exists minus sign at very beginning
        if (firstTime && (line.at(0) == '-')) {
            line = line.substr(1);
            sign = -1;
            newNode->setOuter(-1);
        }
        //find + - sign in equation
        int indexPlus = (int)line.find(" +");
        int indexMinus = (int)line.find(" -");
        int index = -1;
        
        //make sure if we find both then we choose the closet one and assing to index
        if (indexPlus != -1 || indexMinus != -1) {
            if (indexPlus != -1 && indexMinus != -1) {
                if (indexPlus < indexMinus)
                    index = indexPlus;
                else
                    index = indexMinus;
            }
            else if (indexPlus != -1)
                index = indexPlus;
            else
                index = indexMinus;
        }
        
        //find space and use that as index and delete value from line
        if (indexPlus != -1 || indexMinus != -1) {
            command = line.substr(0, index);
            line = line.substr(index + 1);
        }
        //when last part do following
        else {
            command = line;
            line = "";
        }
        
        //change sign based on first index if exists
        if (command.at(0) == '-' || command.at(0) == '+') {
            if (command.at(0) == '-') {
                sign = -1;
                newNode->setOuter(-1);
            }
            else
                sign = 1;
            
            command = command.substr(2);
        }
        
        //if there is only an x then it just enters 1 to outer
        if (command != "x")
        {
            //this gets outer num if exists
            if (isdigit(command.at(0))){
                int n = 1;
                //this is for if digit is greater than 9
                if (command.length() > 1) {
                    while ((n < (int)command.size()) && isdigit(command.at(n)))
                        n++;
                }
                //set outer in node
                string outer = command.substr(0, n);
                newNode->setOuter(stoi(outer) * sign);
                
                command = command.substr(n);
            }
            
            //make sure command is not empty now
            if (command.length() > 0)
            {
                //if there exists a trig
                if (isalpha(command.at(0)) && command.at(0) != 'x')
                {
                    newNode->setInner(1);
                    
                    //store based on which trig
                    if(command.at(0) == 's')
                        newNode->setTrig("sin");
                    else if(command.at(0) == 'c')
                        newNode->setTrig("cos");
                    else if(command.at(0) == 't')
                        newNode->setTrig("tan");
                    
                    command = command.substr(4);
                    
                    //if there is inner value
                    if (isdigit(command.at(0)))
                    {
                        int counter = 1;
                        
                        //if digit greater than 9
                        while (counter < command.size() && isdigit(command.at(counter)))
                            counter++;
                              
                        //store inner value in node  
                        string innerString = command.substr(0, counter);
                        int inner = stoi(innerString);
                        
                        newNode->setInner(inner);
                        command = command.substr(counter);
                    }
                }
                
                //getting and setting exponent
                if (command.at(0) == 'x')
                {
                    //if there exists exponent then do following
                    if (command.length() > 2)
                    {
                        if (isdigit(command.at(2)) || command.at(2) == '-')
                        {
                            int exp = stoi(command.substr(2));
                            newNode->setExp(exp);
                        }
                    }
                    else
                        newNode->setExp(1);
                    
                    command = "";
                }
            }
        }
        else {
            //when only x do following
            newNode->setOuter(1 * newNode->getOuter());
            newNode->setExp(1);
        }
        
        //the following connects node to list
        Node *cur = head;
            
        if (firstTime){
            head = newNode;
            firstTime = false;
        }
        else
        {
            while(cur->getNext() != nullptr)
                cur = cur->getNext();
            
            cur->setNext(newNode);
        }
    }
}

//delete list created
void deleteList(Node* &head)
{
    Node *cur = head;
    Node *next = nullptr;
    
    //delete each individual node until nothing left
    while (cur)
    {
        next = cur->getNext();
        free(cur);
        cur = next;
    }
    //make head point ot null
    head = nullptr;
}

//calculate derivative
void calcDeriv(LList &list)
{
    Node *cur = list.getHead();
    
    while (cur)
    {
        //compute trig derivative if exists
        if (cur->getTrig() != "") 
        {
            if (cur->getTrig() == "sin")
                cur->setTrig("cos");
            else if (cur->getTrig() == "cos") {
                cur->setTrig("sin");
                cur->setOuter(cur->getOuter() * (-1));
            }
            else if (cur->getTrig() == "tan")
                cur->setTrig("sec^2");
            
            cur->setOuter(cur->getInner() * cur->getOuter());
        }
        //computer normal derivative if no trig
        else
        {
            //if there is a exponent
            if (cur->getExp() != 0)
            {
                cur->setOuter(cur->getExp() * cur->getOuter());
                cur->setExp(cur->getExp() - 1);
            }
            //if there is no exponent
            else
                cur->setOuter(0);
        }
        
        cur = cur->getNext();
    }
}



