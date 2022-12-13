/*

Author: Nosakhare Odaro

Date: 11/27/2022

Description: Zombie class header file.

Usage: <exe>
<exe> is the executable.

*/

#pragma once
#ifndef Zombie_H
#include <iostream>
using namespace std;

class Zombie {

  private:
    char color;
    
  public:
    /*
    Name: Zombie
    Params: nothing
    Returns: Zombie pointer
    Description: Defualt constructor of Zombie class which randomly creates Zombie object by choosing a random color.
    */
    Zombie()                 // Defualt constructor
    {
      int randNum = 1 + (int)(6 * ((double)rand() / ((double)RAND_MAX + 1))); //Random integer between 1 and 6 using int cast
                                                                              //for ints 0 to 5 than adding 1.
      if (randNum == 1) {
        this->color = 'R';   //Red
      }
      else if (randNum == 2) {
        this->color = 'Y';   //Yellow
      }
      else if (randNum == 3) {
        this->color = 'G';   //Green
      }
      else if (randNum == 4) {
        this->color = 'B';   //Blue
      }
      else if (randNum == 5) {
        this->color = 'M';   //Magenta
      }
      else {
        this->color = 'C';   //Cyan
      }
    }
    
    /*
    Name: Zombie
    Params: char color
    Returns: Zombie pointer
    Description: Constructor of Zombie class which creates a Zombie object with the color char passed in and points to it.
    */
    
    Zombie(char color) // New Zombie Object with specific color.
    {
      this->color = color;
    }
    
    /*
    Name: getColor
    Params: nothing
    Returns: char
    Description: Getter for private data member color which returns the color char.
    */
    
    char getColor()   // Gets Zombies color.
    {
      return this->color;
    }
    
    bool operator == (const Zombie &zombieObj)   //Overloading of the == operator for comparing Zombie objects.
    {
      if (color == zombieObj.color) {
        return true;
      }
      else {
        return false;
      }
    }
    friend std::ostream& operator<<(std::ostream& out, const Zombie& zombieObj) //Overloading of the << operator for printing Zombie objects.
    {
      out << zombieObj.color;  //Prints the color.
      return out;
    }
};
#endif