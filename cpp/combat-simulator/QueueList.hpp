/*********************************************************************
** Program Filename: QueueList.hpp		[HEADER + IMPLEMENTATION]
** Author:           Shawn Hillyer
** Date:             10/29/2015
** Description:      A simple queue list representing a queue ADT.
**                   I implemented using templates. Because of the
**                   complexity in separating the implementation and
**                   header, it's all in one file.
** Input:            Accepts any type values
** Output:           Will store and retrieve/pop values like a queue
********************************************************************/

#ifndef SSHILLYER_QUEUELIST_HPP
#define SSHILLYER_QUEUELIST_HPP

#include <cstddef>
#include <string>

template <class T>
class QueueList
{
protected:
  struct QueueNode
  {
      T value;
      QueueNode* prior;
      QueueNode(const T& value_in, QueueNode* prior_in = NULL)
      {
        value = value_in;
        prior = prior_in;
      }
  }; // End QueueNode

  QueueNode* front;  // Pointer to front of queue
  QueueNode* back; // Pointer to back of queue
public:
  QueueList() { front = NULL; back = NULL;}
  ~QueueList();
  void add(T value);
  T remove();
  bool is_empty();
};


/*********************************************************************
** Function:         void QueueList<T>::add(T value)
** Description:      Add a value to back of the QueueList
** Parameters:       Any type T value of same type as instantiated object
** Pre-Conditions:   None
** Post-Conditions:  Updates all pointers and values as appropriate
********************************************************************/
template <class T>
void QueueList<T>::add(T value)
{
  // Case 1: QueueList empty
  if (back == NULL)
  {
    back = new QueueNode(value, NULL);
    front = back;
  }

  // Case 2: List not empty. Remember old front (which points to prior node) and add new one
  else
  {
    QueueNode* old_back = back;
    back = new QueueNode(value, NULL);
    old_back->prior = back;
    old_back = NULL;
  }
}


/*********************************************************************
** Function:         T QueueList<T>::remove()
** Description:      remove a value to front of the QueueList
** Parameters:       Any type T value of same type as instantiated object
** Pre-Conditions:   None
** Post-Conditions:  Updates all pointers and values as appropriate
********************************************************************/
template <class T>
T QueueList<T>::remove()
{
  // Case 1: List is empty
  if (front == NULL)
  {
    throw std::string("Queue is already empty!\n");
  }

  // Case 2: List has one node
  else if (front->prior == NULL)
  {
    T return_value = front->value;
    delete front;                // same as deleting back, don't do both!
    back = front = NULL;
    return return_value;
  }

  // Case 3: There's more than one node
  else
  {
    // Grab the value before deallocating memory and clearing danglers
    QueueNode* new_front = front->prior; // remember where penultimate node is
    T return_value = front->value;
    delete front;   // Delete the front node on front
    front = new_front;
    new_front = NULL;
    return return_value;
  }
}


/*********************************************************************
** Function:         QueueList<T>::~QueueList()
** Description:      Destructor. Deletes every node of list.
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  All memory for list deleted
********************************************************************/
template <class T>
QueueList<T>::~QueueList()
{
  // Case 1: List not empty. Traverse list and clear memory
  if (front != NULL)
  {
    QueueNode* node_ptr = front;
    QueueNode* garbage_ptr = front;

    // node_ptr moves one ahead of garbage, garbage deletes, then garbage moves up, too
    while (node_ptr->prior != NULL)
    {
      node_ptr = node_ptr->prior;
      delete garbage_ptr;
      garbage_ptr = node_ptr;
    }

    // Once at the front, delete the last node and remove dangling Pointer
    delete garbage_ptr;
    front = back = garbage_ptr = node_ptr = NULL;
  }
}


/*********************************************************************
** Function:         QueueList<T>::is_empty()
** Description:      Returns true if list is empty
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  
********************************************************************/
template <class T>
bool QueueList<T>::is_empty()
{
  bool is_empty = true;
  if (front != NULL)
    is_empty = false;
  return is_empty;
}

#endif
