//
// Created by Carlo Revelli on 2019-04-08.
//
#pragma once

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>

#define MAXNUMQS 16
#define MAXSTRLEN 100

typedef struct treeStruct *TreeType;
typedef struct positionStruct *PositionType;

TreeType InitTree(FILE* treeFile);
TreeType InitTreeHelper(FILE* treeFile, TreeType tree, PositionType pos);
TreeType InitTreeHelperD(FILE* treeFile, int depth);
void PrintTree(TreeType tree);
void PrintTreeHelper(TreeType tree, PositionType pos);
PositionType Top(TreeType tree);
bool IsLeaf(TreeType tree, PositionType pos);
bool Answer(char* question);
char* Question(TreeType tree, PositionType pos);
char* Guess(TreeType tree, PositionType pos);
PositionType YesNode(TreeType tree, PositionType pos);
PositionType NoNode(TreeType tree, PositionType pos);
void ReplaceNode(TreeType tree, PositionType pos, char* newA, char* newQ);
void GetNewInfo(TreeType tree, PositionType pos,char* newA, char* newQ);
bool isVowel(char *word);
char* GetNode(TreeType tree, PositionType pos);
bool WriteTree(TreeType tree, FILE* fileName);
bool WriteTreeHelper(TreeType tree, PositionType pos, FILE* fileName, int depth);
int* DecToBin(int number, int* buffer);
int CalcOffset(int posIndex);
void SetNode(TreeType tree, PositionType pos, char* value);
char* strip(char *word);
void DefaultTree(FILE *treefile);

#if ONE
struct treeStruct {
  char *nodes[MAXNUMQS];
};

struct positionStruct {
  int nodeIndex;
};
#else
struct treeStruct {
  char *string;
  struct treeStruct *left, *right;
};

struct positionStruct {
  struct treeStruct* node;
};
#endif


