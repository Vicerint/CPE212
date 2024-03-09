// ****************************************
// Program Title: Project04
// Project File: list.cpp
// Name: Michael Agnew
// Course Section: CPE-212-02
// ****************************************

#include <iostream>
#include <new>
#include "list.h"

using namespace std;

// default constructor
List::List()
{ // begin List

    int pain = 0;
    head = NULL;

} // end List

// destructor because we no likey no mo'
List::~List()
{ // begin ~List

    Node* temp;
    while (head != NULL)
    {
        temp = head->next;
        delete temp;
        head = temp;
    }

} // end ~List


// adding data to the list 
void List::Append(string newword)
{ // begin Append
    Node* temp; // making a new node temp
    try 
    {
        temp = new Node; 
    }
    catch (bad_alloc)
    {
        throw ListFull();
    }
    
    temp->word = newword; // using node temp to store newword in word
    temp->next = NULL; // setting the node after temp equal to NULL
    if (head == NULL) // verifying if the list is empty
    {
        head = temp; // if the list is empty, set head equal to the newword stored in temp
    }
    else
    {
        Node* last = head; // initializing new node "last" to store head
        while (last->next != NULL) // while the node after last is not NULL
        {
            last = last->next; // move last one increment down the list
        }
        last->next = temp; // set last.next to temp, which holds newword

    }
    
} // end Append

// adding data to the list at a particular point 
void List::InsertAt(int pos, string newword)
{ // begin InsertAt
    if (pos > Length() || pos < 0) // if the position of the word is out of the interval, throw listbadposition
    {
        throw ListBadPosition();
    }

    else // otherwise 
    {

        Node* in; // declare a new pointer
        try
        {
            in = new Node;

        }
        catch (bad_alloc)
        {
            throw ListFull(); // if it catches bad_alloc, then throw list is full

        }

        in->word = newword; // set the node in to point to newword

        if (head == NULL || pos == 0) // if head is null and pos is 0, then the word needs to be inserted at the beginning of the list
        {
            in->next = head; // make the value after new equal head
            head = in;  // make in the new head
        }
        else
        {
            Node* temp = head; // make a new node temp that equals head

            Node* prev = NULL; // make a new node prev that equals null

            for (int jeremy = 0; jeremy < pos; jeremy++) // loop through list until reaching the end 
            {
                prev = temp; // move previous to the next node
                temp = temp->next; // move temp to the next node
            }

            in->next = temp; // after loop, set the element after in to temp
            prev->next = in; // set the element after prev to in

        }
        num++; // add one to the length of the list
    }
} // end InsertAt

// deleting the contents of the list 
void List::Delete(string someword)
{ // begin Delete


    Node* juan; // funny node name
    juan = head;
    Node* prev;
    prev = NULL; // sets prev to null

    if (head != NULL) // while the head of the list is not null
    {
        // while temp and temp.next are not null, move previous and temp over one
        while (juan->word != someword && juan->next != NULL) // iterate through the list until juan = someword
        {
            prev = juan;
            juan = juan->next;
        }

        if (juan->word == someword) // once someword is found
        {
            if (prev == NULL)
            {
                head = juan->next; // setting head equal to the list element after juan
                delete juan;
            }
            else
            {
                prev->next = juan->next; // leapfrog juan and set prev to the one after juan
                delete juan;
            }
            

            num--; // subtract one from the length
        }
        else // if someword is not in the list then throw listnotfound
        throw ListNotFound();

    }

}

// replacing a value inside of the list 
void List::Replace(string oldword, string newword)
{ // Begin Replace

    if (head != NULL) // if the list is not empty
    {
        Node* replace = head; // make a new node that is equal to head


        while(replace->next != NULL && oldword != replace->word) // iterate through the list until finding the word
            replace = replace->next;


        if (oldword == replace->word)
        replace->word = newword; // replacing the oldword with the newword

        else
            throw ListNotFound(); // if the old word is not found then throw not found
    }
    else
        throw ListEmpty(); // if head is null then throw list is empty

} // end Replace

// finding the length of the list 
int List::Length() const
{ // begin Length
    int yuh = 0;
    Node* temp = head;
    while (temp != NULL) // iterating through the list and counting the number of elements
    {
        yuh++;
        temp = temp->next;
    }
    return yuh; // returning the length
} // end Length


// finding a data value inside of the list
bool List::Find(string someword) const
{ // begin Find
    Node* current = head; // setting a current node equal to head
    while (current != NULL)
    {
        if (current->word == someword) // iterating through the list to see if someword is in list
        {
            return true; // return true if the word is found
        }
        current = current->next;
    }
    return false; // return false if the word is not in the list
} // end find