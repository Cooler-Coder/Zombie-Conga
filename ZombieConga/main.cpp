/*

Author: Nosakhare Odaro

Date: 11/27/2022

Description: Program is designed to be the main cpp file to run the templated Linked List file and the problem which is Conga
parties with Zombies.

Usage: <exe>
<exe> is the executable.

*/

#include <iostream>
#include <time.h>
#include "odaro_list.h"
#include "zombie.h"
#include "conga.h"
using namespace std;

// Forward declaring of functions: program, frand, actionChooser, and roundOutput.

void program(int argc, char** argv);
double frand();
Conga actionChooser(Conga congaParty);
Conga roundOutput(Conga congaParty, int roundNum);

/*
Name: main
Params: int argc (an integer)  and char** argv (an array of strings)
Returns: An integer 0 (program stops running)
Description: This is the main function of the program. It delegates the main computing of the program to the function program.
*/

int main(int argc, char** argv) 
{
  srand(time(NULL));                              //Seeds random Generator
  program(argc, argv);  
  return 0;
}

/*
Name: program
Params: int argc (an integer)  and char** argv (an array of strings)
Returns: nothing
Description: This function delegates from the main function to organize the program. It simulates the Conga party with Zombies
and prompts users for input.
*/

void program(int argc, char** argv)
{
  Conga congaParty;
  Zombie zombieObj;                                   //Creates randomZombie object/
  int numOfRounds = 0;
  char continueParty = 'y';
  int randInitialActions = 2 + (int)(4 * frand());    //Random number between 2 and 5 using int cast for ints 0 to 3 then adding 2

  int index = 0;
  congaParty.RainbowBrains(zombieObj);
  for (index = 0; index < randInitialActions; ++index) {  //Initial Conga party actions.
    congaParty.Brains(zombieObj);
  }
  while (continueParty == 'y') {                      //While the party continues the prompts code loops.
    printf("\nEnter the number of rounds you want to run: ");
    scanf("%d", &numOfRounds);

    while (numOfRounds < 0) {
      printf("\nEnter the number of rounds you want to run: ");
      scanf("%d", &numOfRounds);
    }
    printf("\n");

    for (index = 0; index < numOfRounds; ++index) {  //Conga party starts from round 0.
      congaParty = roundOutput(congaParty, index);
      if (congaParty.congaList.Length() == 0) {
        printf("\nThe party is over!\n");
        break;
      }
      if (index == numOfRounds - 1) {                     //Prompts the user if they want ot continue the Conga party.
        printf("\nEnter 'y' or 'n' (yes or no) if you want to continue the party or not: ");
        scanf(" %c", &continueParty);
      }
    }
  }
  return;
}

/*
Name: frand
Params: nothing
Returns: double
Description: This function returns a random doouble number between 0 and 1 utilizing the rand() function.
*/

double frand() {
  return (double)rand() / ((double)RAND_MAX + 1);
}

/*
Name: actionChooser
Params: Conga congaParty
Returns: Conga object
Description: This function creates a random Zombie object, chooses a rondom action for the Conga party, and also prints to the 
terminal the Zombie objects color and the action picked. It also uses the frand function to help with the randomness it achieves.
*/

Conga actionChooser(Conga congaParty) {
  int randNum = 1 + (int)(9 * frand());              //Random integer between 1 and 9 using int cast for ints 0 to 8 then adding 1.
  Zombie zombObj;                               
  std::cout << zombObj.getColor();                   //Prints Zombies color.
                                                     //The following are what the zombie is doing:
  if (randNum == 1) {  
    congaParty.Engine(zombObj);
    printf(" zombie jumps in the front of the line! (ENGINE)\n");
  }
  else if (randNum == 2) {
    congaParty.Caboose(zombObj);
    printf(" zombie pulls up the rear! (CABOOSE)\n");
  }
  else if (randNum == 3) {
    congaParty.JumpInTheLine(zombObj, (int)(congaParty.congaList.Length() * frand()) + 1); //Index >= 1 and  Index <= length.
    printf(" zombie jumps into the line at a random position! (JUMPS IN THE LINE)\n");   
  }                                    
  else if (randNum == 4) {
    congaParty.EveryoneOut(zombObj);
    printf(" zombie gets all its friends kicked out of the party! (EVERYONE OUT)\n");
  }
  else if (randNum == 5) {
    congaParty.YouAreDone(zombObj);
    printf(" zombie gets first found friend kicked out of the party! (YOU ARE DONE)\n");
  }
  else if (randNum == 6) {
    congaParty.Brains(zombObj);
    printf(" zombie brings its friends to the party (BRAINS!)\n");
  }
  else if (randNum == 7) {
    congaParty.RainbowBrains(zombObj);
    printf(" zombie brought a whole party itself! (RAINBOW BRAINS!)\n");
  }
  else if (randNum == 8) {
    congaParty.MakingNewFriends(zombObj);
    printf(" zombie makes a friend with a same color zombie and joins next to it! (MAKING NEW FRIENDS)\n");
  }
  else {
    congaParty.UnstableZombie(zombObj);
    printf(" zombie gets first found friend kicked out of the party and others before it split! (UNSTABLE ZOMBIE)\n");
  }
  return congaParty;
}

/*
Name: roundOutput
Params: Conga congaParty and int roundNum
Returns: Conga object
Description: The roundOutput function runs and outputs the simulation of each round of the Conga party. It calls on actionChooser
and returns the changed Conga object.
*/

Conga roundOutput(Conga congaParty, int roundNum) {
  printf("Round: %d", roundNum);
  printf("\nThe Zombie Party keeps on groaning!");
  printf("\nSize : %d :: ", congaParty.congaList.Length());
  congaParty.congaList.PrintList();
  printf("\n");
  congaParty = actionChooser(congaParty);
  printf("The conga line is now: ");
  printf("\nSize : %d :: ", congaParty.congaList.Length());
  congaParty.congaList.PrintList();
  printf("\n*******************\n\n");
  return congaParty;
}