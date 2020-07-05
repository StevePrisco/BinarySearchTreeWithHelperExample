/*
* File: scoresAgain.c
* Author: Steve Prisco
* Description: This file is to be compiled with 'bst.c'. This just takes user data and calls functions detailed in bst.c to add data to the tree
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "bst.h"

int main(void) // This function takes user data and calls insert - detailed in the file bst.c - and when it's done taking user input, it calls printTree and deallocate
{              // Both of these functions are also located in bst.c
 int score1, score2;
 char player1[35], player2[35];
 int length = 0;

 while ((length = scanf(" %s %d %s %d", player1, &score1, player2, &score2)) != EOF)
 {
 
  if (length != 4)
  {
   fprintf(stderr, "ERROR: invalid input - exiting\n");
   exit(1);
  }

  insert(player1, score1, player2, score2);
 }


 printTree();
 deallocate();
 return 0;
}
