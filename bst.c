/*
* File: bst.c
* Author: Steve Prisco
* Description: This file is to be compiled with scoresAgain.c. This file contains all the functions for the Binary Tree that is needed for the 'scores' program.
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Player
{
 char * name;
 int wins;
 int losses;
} Player;

typedef struct node
{
 struct Player * player;
 struct node *left;
 struct node *right;
} node;

node * root = NULL;

node * findNode(char * name) // returns a pointer to a node that already exists in the tree, or NULL if it does not
{
 if (!root)
 { 
  return root;
 }
 
 node *current;
 current = root;

 while (current)
 {

  if ((strcmp(name, current->player->name)) < 0)
  {
   current = current->left;
  }else if ((strcmp(name, current->player->name)) > 0)
  {
   current = current->right;
  }else
  {
   return current;
  }
 }

 return current;
}

void addNode(char *name, int result) // This function adds a node to the tree. It allocates memory for the new data, and assigns the node to its proper location in the tree
{
 node * tempNode = (node *)malloc(sizeof(node));
 Player * tempPlayer = (Player *)malloc(sizeof(Player));
 
 if (!tempNode || !tempPlayer)
 {
  fprintf(stderr,"ERROR: no available memory - exiting\n");
  exit(1);
 }

 tempPlayer->name = strdup(name);
 if (result > 0)
 {
  tempPlayer->wins = 1;
  tempPlayer->losses = 0;
 }else
 {
  tempPlayer->wins = 0;
  tempPlayer->losses = 1;
 } 

  tempNode->player = tempPlayer;
  tempNode->left = NULL;
  tempNode->right = NULL;

 if (!root)
 {
  root = tempNode;
  root->player = tempPlayer;
 }else
 {  
  node *current;
  current = root;
  
  while (current)
  {
   if ((strcmp(name, current->player->name)) < 0)
   {
    if (current->left)
    {
     current = current->left;
    }else
    {
     current->left = tempNode;
     break;
    }
   }else if ((strcmp(name, current->player->name)) > 0)
   {
    if (current->right)
    {
     current = current->right;
    }else
    {
     current->right = tempNode;
     break;
    }
   }
  }
 }
}

void updateNode(char *name, int result) // This function updates the data in an existing node within the tree
{
 node *current;
 current = findNode(name);

 
 if (result > 0)
 {
  current->player->wins += 1;
 }else
 {
  current->player->losses += 1;
 }
}

void insert(char *player1, int score1, char *player2, int score2) // This function parses user data and calls either updateNode or addNode to put the data in the tree
{
 if (strcmp(player1, player2) == 0)
 {
  fprintf(stderr,"ERROR: players cannot play against themselves - exiting\n");
  exit(1);
 }
 
 node *current;
 
 int result1 = 0, result2 = 0;

 if (score1 > score2)
 {
  result1 = 1;
  result2 = -1;
 }else if (score1 < score2)
 { 
  result1 = -1;
  result2 = 1;
 }else
 {
  fprintf(stderr,"ERROR: players are not allowed to tie, ask them to play again - exiting\n");
  exit(1);
 }

 current = findNode(player1);

 if (!current)
 {
  addNode(player1, result1);
 }else
 {
  updateNode(player1, result1);
 }

 current = findNode(player2);

 if (!current)
 {
  addNode(player2, result2);
 }else
 {
  updateNode(player2, result2);
 }
}

void printHelper(node * tempNode) // recursive helper for printTree, in-order traversal
{
 if (tempNode)
 {
  printHelper(tempNode->left);
  printf("%s, %d, %d\n", tempNode->player->name, tempNode->player->wins, tempNode->player->losses);
  printHelper(tempNode->right);
 }
}

void printTree() // calls printHelper to print contents of the tree in order
{
 node * tempNode = root;
 printHelper(tempNode);
}

void deallocateHelper(node *tempNode) // recursive helper for deallocate, post-order traversal
{
 if (!tempNode)
 {
  return;
 }

 deallocateHelper(tempNode->left);
 deallocateHelper(tempNode->right);
 free(tempNode->player->name);
 free(tempNode->player);
 free(tempNode);
}

void deallocate() // calls deallocateHelper to free the memory taken up by the tree
{
 node *tempNode = root;
 deallocateHelper(tempNode);
}
