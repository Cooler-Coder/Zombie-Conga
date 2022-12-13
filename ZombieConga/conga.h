/*

Author: Nosakhare Odaro

Date: 11/27/2022

Description: Conga class in header file.

Usage: <exe>
<exe> is the executable.

*/

#pragma once
#ifndef Conga_H
#include "odaro_list.h"
#include "zombie.h"
using namespace std;

class Conga {

  public:
    LinkedList<Zombie> congaList;  //Calls defualt constructor
 
    void Engine(Zombie zombieObj) // - This zombie becomes the first Zombie in the conga line
    {
      congaList.AddToFront(zombieObj);
    }
    
    void Caboose(Zombie zombieObj) // - This zombie becomes the last zombie in the conga line
    {
      congaList.AddToEnd(zombieObj);
    }
  
    void JumpInTheLine(Zombie zombieObj, int index) // - This zombie joins the conga line at position X where X <= length of the linked list
    {
      congaList.AddAtIndex(zombieObj, index - 1);
    }
    
    void EveryoneOut(Zombie zombieObj) // - Removes all matching zombies from the linked list
    {
      congaList.RemoveAllOf(zombieObj);
    }

    void YouAreDone(Zombie zombieObj) // - Remove the first matching zombie from the linked list
    {
      congaList.RemoveTheFirst(zombieObj);
    }
    
    void Brains(Zombie zombieObj) // - Generates two more matching Zombies and add one to the front,
    {                        //   one to the end and one to the middle (round down).
      int middleIndex = (congaList.Length() - 1)/2;   //Rounds down since integer division and - 1 for index
      Zombie *zombieObj1 = new Zombie(zombieObj.getColor());
      Zombie *zombieObj2 = new Zombie(zombieObj.getColor());
      congaList.AddAtIndex(zombieObj, middleIndex);
      congaList.AddToFront(*zombieObj1);
      congaList.AddToEnd(*zombieObj2);
    }

    void RainbowBrains(Zombie zombieObj) // - Add this zombie to the front,
    {                                    //   then add one of each zombie color to the end of the conga line.
      Zombie* zombieObj1 = new Zombie('R');
      Zombie* zombieObj2 = new Zombie('Y');
      Zombie* zombieObj3 = new Zombie('G');
      Zombie* zombieObj4 = new Zombie('B');
      Zombie* zombieObj5 = new Zombie('M');
      Zombie* zombieObj6 = new Zombie('C');

      congaList.AddToFront(zombieObj);
      congaList.AddToEnd(*zombieObj1);
      congaList.AddToEnd(*zombieObj2);
      congaList.AddToEnd(*zombieObj3);
      congaList.AddToEnd(*zombieObj4);
      congaList.AddToEnd(*zombieObj5);
      congaList.AddToEnd(*zombieObj6);
    }

    void MakingNewFriends(Zombie zombieObj) // - Finds the first Zombie of this color in line.
    {                                       //   “Flips a coin” 50% chance of adding before or after that zombie. 
      Node<Zombie>* congaNode;              //    If no Zombie of that color exists, it adds this one before the Tail zombie.
      double randNum = (double)rand() / ((double)RAND_MAX + 1);  //Random number (double) between 0 (inclusive) an 1 (not inclusive).
      if (!congaList.ElementExists(zombieObj)) {
        congaList.AddAtIndex(zombieObj, congaList.Length() - 1);
      }

      congaNode = congaList.Find(zombieObj);
      if (randNum < 0.5) {                                       //Decides whether to add before of after.
        congaList.AddBefore(congaNode, zombieObj);
      }
      else {
        congaList.AddAfter(congaNode, zombieObj);
      }
    }

    void UnstableZombie(Zombie zombieObj) // - Walks the list to locate the first Zombie of this color in line and remove it.
    {                                     //   While walking the list: all the zombies of other colors before the
      int index = 0;                      //   target zombie splits and adds a new zombie before them.
      int length = congaList.Length();
      Zombie currZombie = congaList.RetrieveFront();
      while (!(currZombie.getColor() == zombieObj.getColor()) && index < length) {
        Zombie* currZombie1 = new Zombie(currZombie.getColor());
        congaList.AddBefore(congaList.RetrieveNode(index), *currZombie1);  //RetrieveNode retrieves node at index. 
        index += 2;
        ++length;
        if (index < length) {
          currZombie = congaList.Retrieve(index);                          //This retrieve is for the next zombie check.
        }
      }
      congaList.RemoveTheFirst(zombieObj);
    }

};
#endif