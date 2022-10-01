#include "Node.h"

//the following outputs node
std::ostream& operator<<(std::ostream &out, const Node *node)
{
    int outer;
    
    //make sure outer is not zero
    if (node->getOuter() != 0)
    {
        //check if outer is negative or not
        if (node->getOuter() < 0)
            outer = (node->getOuter()) * (-1);
        else 
            outer = node->getOuter();
        
        //do following if trig exists
        if (node->getTrig() != "") {
            if (outer == 1)
                out << node->getTrig();
            else
                out << outer << node->getTrig();
            
            if (node->getInner() != 1)
                out << " " << node->getInner() << "x";
            else
                out << " x";
        }
        //if exponent is zero then only output outer
        else if (node->getExp() == 0) {
                out << outer;
        }
        //if exponent is 1 do not output it
        else if (node->getExp() == 1) {
            if (node->getOuter() != 1)
                out << outer << "x";
            else
                out << "x";
        }
        //do following if exists outer and exponent
        else {
            if (node->getOuter() != 1)
                out << outer << "x^" << node->getExp();
            else 
                out << "x^" << node->getExp();
        }
    }
    //output nothing if outer is zero
    else {
        out << "";
    }
    
    return out;
}