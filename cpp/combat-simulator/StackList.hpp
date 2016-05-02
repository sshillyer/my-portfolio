/*********************************************************************
** Program Filename: StackList.hpp		[HEADER + IMPLEMENTATION]
** Author:           Shawn Hillyer
** Date:             11/13/2015
** Description:      A simple linked list representing a stack ADT.
**                   I implemented using templates. Because of the
**                   complexity in separating the implementation and
**                   header, it's all in one file.
** Input:            Accepts any type values
** Output:           Will store and retrieve/pop values like a stack
********************************************************************/

#ifndef SSHILLYER_STACKLIST_HPP
#define SSHILLYER_STACKLIST_HPP

#include <cstddef>
#include <string>

template <class T>
class StackList
{
protected:
  struct StackNode
  {
      T value;
      StackNode* next;
      StackNode(const T& value_in, StackNode* next_in = NULL)
      {
        value = value_in;
        next = next_in;
      }
  }; // End StackNode

  StackNode* top;  // Pointer to top of stack
public:
  StackList() { top = NULL; }
  ~StackList();
  void add(T value);
  T remove();
  bool is_empty();
};


/*********************************************************************
** Function:         void StackList<T>::add(T value)
** Description:      remove a value from the top of the StackList
** Parameters:       Any type T value of same type as instantiated object
** Pre-Conditions:   None
** Post-Conditions:  Updates all pointers and values as appropriate
********************************************************************/
template <class T>
void StackList<T>::add(T value)
{
  // Case 1: StackList empty
  if (top == NULL)
  {
    top = new StackNode(value, NULL);
  }

  // Case 2: List not empty. Remember old top (which points to prior node) and add new one
  else
  {
    StackNode* old_top = top; // used to remember last node
    top = new StackNode(value, old_top);
    old_top = NULL;
  }
}


/*********************************************************************
** Function:         T StackList<T>::remove()
** Description:      remove a value from the top of the StackList
** Parameters:       Any type T value of same type as instantiated object
** Pre-Conditions:   None
** Post-Conditions:  Updates all pointers and values as appropriate
********************************************************************/
template <class T>
T StackList<T>::remove()
{
  // Case 1: List is empty
  if (top == NULL)
  {
    throw std::string("Stack is already empty!\n");
  }

  // Case 2: List has one node
  else if (top->next == NULL)
  {
    T return_value = top->value;
    delete top;
    top = NULL;
    return return_value;
  }

  // Case 3: There's more than one node
  else
  {
    // Grab the value before deallocating memory and clearing danglers
    StackNode* new_top = top->next; // remember where penultimate node is
    T return_value = top->value;
    delete top;   // Delete the top node on stack
    top = new_top;
    new_top = NULL;
    return return_value;
  }
}


/*********************************************************************
** Function:         StackList<T>::~StackList()
** Description:      Destructor. Deletes every node of list.
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  All memory for list deleted
********************************************************************/
template <class T>
StackList<T>::~StackList()
{
  // Case 1: List not empty. Traverse list and clear memory
  if (top != NULL)
  {
    StackNode* node_ptr = top;
    StackNode* garbage_ptr = top;

    // node_ptr moves one ahead of garbage, garbage deletes, then garbage moves up, too
    while (node_ptr->next != NULL)
    {
      node_ptr = node_ptr->next;
      delete garbage_ptr;
      garbage_ptr = node_ptr;
    }

    // Once at the top, delete the last node and remove dangling Pointer
    delete garbage_ptr;
    top = garbage_ptr = node_ptr = NULL;
  }
}


/*********************************************************************
** Function:         StackList<T>::is_empty()
** Description:      Returns true if list is empty
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:
********************************************************************/
template <class T>
bool StackList<T>::is_empty()
{
  bool is_empty = true;
  if (top != NULL)
    is_empty = false;
  return is_empty;
}

#endif
