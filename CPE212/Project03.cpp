// CPE 212/02
// 10/3/2023
// Based Dr. James
// Michael Agnew

#include <iostream>
#include <new>
#include "stack.h"

/***************************DESTRUCTOR******************************/
Stack::~Stack()
{ // start of ~stack
    delete[] array;
} // end of ~stack
/**************************CONSTRUCTOR******************************/
Stack::Stack(int n)
{ // start of stack
    array = new int[n]; // dynamic allocation goes brrr
    top = -1; // setting the top of the stack 
    num = n; // input = max size
    
} // end of stack


/**************************TRANSFORMERS*****************************/


void Stack::Push(int n)
{ // start of push
    if (Stack::IsFull()) // make sure the stack is not full
       Resize(n); // resize because you cant fit through the door
    array[++top] = n; // putting n onto the top of the stack

} // end of push

void Stack::Pop()
{ // start of pop
    if (Stack::IsEmpty()) // make sure the stack is not empty
    {
        throw StackEmpty(); // if stack is empty throw exception
    }
    else
    {
        top = top - 1; // decrement the stack because you took the top off 
    }
} // end of pop

void Stack::MakeEmpty() 
{ // start of makeEmpty
    top = -1; // setting the top to -1 because we dont like it anymore

} // end of MakeEmpty

/***************************OBSERVERS*********************************/

bool Stack::IsEmpty() const
{ // start of IsEmpty
    return (top == -1); // return true if the stack is empty 
} // end of IsEmpty

bool Stack::IsFull() const
{ // start of IsFull
    return (top == (num - 1)); // return true if the stack is full
} // end of IsFull


int Stack::Top() const
{ // start of top
    if (Stack::IsEmpty()) // check to see if stack is empty
    {
        throw StackEmpty(); // throw exception if stack empty
    }
    else
    {
        return array[top]; // return the top value of the stack
    }
} // end of top

int Stack::Size() const
{ // start of size
    return (top + 1);
} // end of size

int Stack::Max() const
{ // start of max
    int horse = array[0]; // setting maximum equal to the first element in the stack
    if (Stack::IsEmpty()) // making sure the stack is not empty
    {
        throw StackEmpty(); // throw exception if stack is empty
    }
    else
    {
        
        for (int juan = 0; juan < top; juan++) // loop through the stack until reaching value of top
        {
            if (array[juan] > horse) // check to see if the current index of the stack is bigger than the previous value
            horse = array[juan]; // if so, set the max equal to horse
        }
    }
    return horse; // return the max
} // end of max

int Stack::Min() const
{ // start of min
    int horse = array[0]; // setting the current min to the value of the first element on the stack
    if (Stack::IsEmpty()) // making sure that the stack is not empty
    {
        throw StackEmpty(); // if stack is empty, then throw stack empty exception
    }
    else
    {
        
        for (int juan = 0; juan < top; juan++) // loop through the stack while the index is less than the top
        {
            if (array[juan] < horse) // check to see if the current indexed value is less than the value of the previous element on the stack
            horse = array[juan]; // if so, set the min equal to the current index value
        }
    }
    return horse; // return the min
} // end of min

int Stack::Peek(unsigned int n) const
{ // start of peek
    int peekyboy = top - n; // setting a temporary variable equal to n levels from top
    if (peekyboy < 0 || peekyboy > top) // making sure position top-n actually exists
    {
        throw (StackInvalidPeek()); // throwing exception if not
    }
    return array[peekyboy]; // returning position n from the top
} // end of peek

int Stack::Capacity() const
{ // start of capacity
    return num;
} // end of capacity

void Stack::Resize(int n)
{
    int* please; // new array please work
    int pain = num*2; // doubling the size of the array
    please = new int[pain]; // dynamic allocation

    for (int Jeremy = 0; Jeremy <= (num); Jeremy++) // jeremy
    {
        please[Jeremy] = array[Jeremy]; // inputting old array values into new array
    }
    delete[] array; // deleting the old array for no memory leak
    array = please; // setting temporary array pointer equal to the original array pointer
    num = pain; // pain
    please = NULL; // please dont memory leak
}