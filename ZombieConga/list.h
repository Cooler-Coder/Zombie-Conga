/*

Author: Nosakhare Odaro

Date: 11/27/2022

Description: Templated Node class and templated Linked List class header file.

Usage: <exe>
<exe> is the executable.

*/

#pragma once
#ifndef Odaro_List_H
#include <string.h>
#include <iostream>
using namespace std;

template <class T>
class Node {

  private:
    T data;
    
  public:
    Node<T>* prev;
    Node<T>* next;
  
    Node() // New Node Object
    {
      data = (T)sizeof(T);
      prev  = NULL;
      next = NULL;
    }
    T getData() // Get Nodes data
    {
      return data;
    }
    void setData(T data) // Sets Nodes data to parameter data
    {
      this->data = data;
    }
  
};

template <class T>
class LinkedList {
    
  public:     //Change back to protected
    Node<T>* firstNode;
    Node<T>* lastNode;
    
  
    LinkedList() // New ListNode Object
    {
      firstNode = NULL;
      lastNode = NULL;
    }
    
    

    void AddToFront(T data) // - Creates a node containing T data and adds it to the front of the list
    {
      Node<T>* tempNode = new Node<T>();
      tempNode->setData(data);
      if (firstNode == NULL) {
        firstNode = tempNode;
        lastNode = tempNode;
      }
      else {
        tempNode->next = firstNode;
        firstNode->prev = tempNode;
        firstNode = tempNode;
      }
    }

    void AddToEnd(T data) // - Creates a node containing T data and add it to the end of the list.
    {
      Node<T>* tempNode = new Node<T>();
      tempNode->setData(data);
      if (firstNode == NULL || lastNode == NULL) {
        firstNode = tempNode;
        lastNode = tempNode;
        return;
      }
      
      tempNode->prev = lastNode;
      lastNode->next = tempNode;
      lastNode = tempNode;
    }
    bool AddAtIndex(T data, int index) // - Creates a node containing T data and adds it to the list at the index passed.  
    {                                  //The new node containing the data will be the #index node in the list. Return boolean for success or failure 
      Node<T>* currNode = new Node<T>();
      Node<T>* tempNode = new Node<T>();
      currNode = firstNode;
      tempNode->setData(data);
      int nodeIndex = 0;
      int length = Length();
      
      if (index > length) {
        return 0;
      }
      if (index == length) {
        AddAfter(currNode, data);      //Adds after only in case of adding after the last node.
      }

      while (currNode != NULL) {
        if (nodeIndex == index) {
          AddBefore(currNode, data);
        }
        currNode = currNode->next;
        ++nodeIndex;
      }
      
      return 1;
    }

    void AddBefore(Node<T>* nodePassed, T data) // - Creates a node containing T data and adds it before a particular node.
    {
      Node<T>* currNode = new Node<T>();
      currNode->setData(data);
      
      if (nodePassed == NULL) {
        throw "Node pointer passed in is NULL.";
        return;
      }
      if (firstNode == NULL || lastNode == NULL) {
        firstNode = currNode;                    //If list is empty it sets the first and last node to the new node 
        lastNode = currNode;                     //containing data.
        return;
      }
      currNode->next = nodePassed;               //Accounts for all adding before cases.
      if (nodePassed->prev != NULL) {
        nodePassed->prev->next = currNode;
        currNode->prev = nodePassed->prev;
      }
      nodePassed->prev = currNode;
      if (nodePassed == firstNode) {
        firstNode = nodePassed->prev;
      }
    }

    void AddAfter(Node<T>* nodePassed, T data) // - Creates a node containing T data and adds it after a particular node.
    {
      Node<T>* currNode = new Node<T>();
      currNode->setData(data);
      
      if (nodePassed == NULL) {
        throw "Node pointer passed in is NULL.";
        return;
      }
     if (firstNode == NULL || lastNode == NULL) {
        firstNode = currNode;
        lastNode = currNode;
        return;
      }
      currNode->prev = nodePassed;                //Accounts for all adding after cases.
      if (nodePassed->next != NULL) {      
        nodePassed->next->prev = currNode;
        currNode->next = nodePassed->next;
      }
      nodePassed->next = currNode;
      if (nodePassed == lastNode) {
        lastNode = nodePassed->next;
      }
    }

    T RemoveFromFront() // - Deletes the first item of the list and returns its contents (data).
    {
      T result;
      if (firstNode == NULL) {
        return (T)sizeof(T);   //Static T cast for size of data as T unknown.
      }
      result = firstNode->getData();
      Node<T>* tempNode = firstNode->next;
      if (firstNode->next != NULL) {
        firstNode->next->prev = NULL;
      }
      firstNode->next = NULL;
      firstNode = NULL;
      firstNode = tempNode;    //Sets the first node to the second node in the list.
      return result;
    }

    T RemoveFromEnd() // - Delete last item and return its contents
    {
      T result;
      if (lastNode == NULL) {
        throw "List is empty.";
      }
      result = lastNode->getData();
      Node<T>* tempNode = lastNode->prev;
      if (lastNode->prev != NULL) {
        lastNode->prev->next = NULL;
      }
      lastNode->prev = NULL;
      lastNode = NULL;
      lastNode = tempNode;   //Sets the last node to the second node in the list.
      return result;
    }

    void RemoveTheFirst(T data) // - find first instance of T data and remove it
    {
      Node<T>* currNode = firstNode;
      while (currNode != NULL && !(currNode->getData() == data)) {
        currNode = currNode->next;
      }
      if (currNode == NULL) {                    //Accounts for NULL and all positions and cases.
        return;
      }
      if (currNode->prev != NULL) {
        currNode->prev->next = currNode->next;
      }
      if (currNode->next != NULL) {
        currNode->next->prev = currNode->prev;
      }
      if (currNode == firstNode) {
        firstNode = currNode->next;
      }
      if (currNode == lastNode) {
        lastNode = currNode->prev;
      }
      currNode->prev = NULL;                    //Completely removes the current node.
      currNode->next = NULL;
      currNode = NULL;
    }

    void RemoveAllOf(T data) // - find each instance of T data and remove it
    {
      Node<T>* currNode = new Node<T>();
      Node<T>* tempNode = new Node<T>();
      currNode = firstNode;
      while (currNode != NULL) {
        if (currNode->getData() == data) {
          if (currNode->prev != NULL) {
            currNode->prev->next = currNode->next;
          }
          if (currNode->next != NULL) {
            currNode->next->prev = currNode->prev;
          }
          if (currNode == firstNode) {
            firstNode = currNode->next;
          }
          if (currNode == lastNode) {
            lastNode = currNode->prev;
          }
          tempNode = currNode->prev;           //Saves previous node.
          currNode->prev = NULL;               //Completely removes the current node.
          currNode->next = NULL;
          currNode = NULL;    
          currNode = tempNode;                 //Sets the current node to the saved previous node to continue.
        }
        if (currNode == NULL) {
          return;
        }
        currNode = currNode->next;
      }
    }

    T RemoveBefore(Node<T>* nodePasssed) // - Deletes the node before a particular node and return its data contents.
    {                                    //   It accounts for all cases of null pointers
      Node<T>* tempNode;
      T nodeContent;
      if (nodePasssed == NULL) {
        throw "Node passed is a null pointer.";          //Throws exception if null pointer passed in.
      }
      if (nodePasssed->prev == NULL) {                  
        throw "Node passed previous is a null pointer."; //Throws exception if node to be removed is a null pointer.
      }
      nodeContent = nodePasssed->prev->getData();
      if (nodePasssed->prev->prev != NULL) {
        nodePasssed->prev->prev->next = nodePasssed;
      }
      if (nodePasssed->prev == firstNode) {
        firstNode = nodePasssed;
      }
      tempNode = nodePasssed->prev->prev;
      nodePasssed->prev->prev = NULL;
      nodePasssed->prev->next = NULL;
      nodePasssed->prev = NULL;
      nodePasssed->prev = tempNode;
      return nodeContent;                                //Returns the saved data contents of the removed node.
    }

    T RemoveAfter(Node<T>* nodePasssed) // - Deletes the node after a particular node and return its data contents.
    {
      Node<T>* tempNode;
      T nodeContent;
      if (nodePasssed == NULL) {
        throw "Node passed is a null pointer.";
      }
      if (nodePasssed->next == NULL) {
        throw "Node passed next is a null pointer."; //Throws exception if node to be removed is a null pointer.
      }
      nodeContent = nodePasssed->next->getData();
      if (nodePasssed->next->next != NULL) {
        nodePasssed->next->next->prev = nodePasssed;
      }
      if (nodePasssed->next == lastNode) {           //Account for all removal cases and changes the 
        lastNode = nodePasssed;                      //last node accordingly.
      } 
      tempNode = nodePasssed->next->next;
      nodePasssed->next->prev = NULL;
      nodePasssed->next->next = NULL;
      nodePasssed->next = NULL;
      nodePasssed->next = tempNode;
      return nodeContent;
    }
 
    bool ElementExists(T data) // - Returns a T/F if element exists in list
    {
      Node<T>* currNode = firstNode;      //Current node is the first node.
      while (currNode != NULL) {
        if (currNode->getData() == data) {
          return true;
        }
        currNode = currNode->next;        //Walks the list.
      }
      return false;
    }

    Node<T>* Find(T data) // - Look for data in the list, return a pointer to its node
    {
     Node<T>* currNode = firstNode;
      while (currNode != NULL) {
        if (currNode->getData() == data) {
          return currNode;
        }
        currNode = currNode->next;
      }
      return NULL;                        //Returns NULL if not data is not found in the list.
    }


    int IndexOf(T data) // - Returns an index of the item in the list with the data which is zero-based.
    {
      Node<T>* currNode = firstNode;
      int indexOfData = 0;
      while (currNode != NULL) {
        if (currNode->getData() == data) {
          return indexOfData;
        }
        currNode = currNode->next;
        ++indexOfData;
      }
      return -1;                           //Item not in list returns -1.
    }

    T RetrieveFront() // - Returns the data contained in the lists first node and does not delete node. 
    {
      return firstNode->getData();
    }
    
    T RetrieveEnd() // - Returns the data contained in the lists last node and does not delete node.
    {
      return lastNode->getData();
    }
    T Retrieve(int index) // - Returns the data contained in node index number, does not delete the node, and
    {                     //   throws an "index out of bounds" exception if the index does not exist or is negative.
      Node<T>* currNode = firstNode;
      int nodeIndex = 0;
      while (currNode != NULL && nodeIndex < index) {
        currNode = currNode->next;
        ++nodeIndex;
      }
      if (index < 0 || (currNode == NULL || nodeIndex < index)) {
        throw "index out of bounds"; 
      }
      return currNode->getData();
    }
    
     Node<T>* RetrieveNode(int index) // - Returns the node at the int index, does not delete the node,
    {                                 //   throws an "index out of bounds" exception if the index does not exist or is negative.
      Node<T>* currNode = firstNode;
      int nodeIndex = 0;
      while (currNode != NULL && nodeIndex < index) {
        currNode = currNode->next;
        ++nodeIndex;
      }
      if (index < 0 || (currNode == NULL || nodeIndex < index)) {
        throw "index out of bounds"; 
      }
      return currNode;
    }

    void PrintList() // - Loops through each node in the list and print the data contents of the nodes.
    {
      Node<T>* currNode = firstNode;
      if (currNode == NULL) {
        return;
      }
      while(currNode != NULL) {
        std::cout << "[" << currNode->getData() << "] ";   //Puts the data of each node between [].
        currNode = currNode->next;
      }
    }

    void Empty() // - Empties out the list and deletes everything in it.
    {
      Node<T>* currNode = firstNode;
      while(currNode != NULL) {
        Node<T>* tempNode = currNode->next;
        delete currNode;
        currNode = tempNode;
      }
      firstNode = NULL;
      lastNode = NULL;
    }

    int Length() // - Returns the number of elements in the list
    {
      Node<T>* currNode = firstNode;
      int nodeIndex = 0;
      if (currNode == NULL) {
        return 0;
      }
      while (currNode != NULL) {
        currNode = currNode->next;
        ++nodeIndex;
      }
      return nodeIndex;
    }
};

#endif