//
// Created by Carlo Revelli on 2019-04-09.
//
#include "common.c"
#include "animal.h"

TreeType InitTree(FILE *treeFile)
{
    TreeType tree = malloc(sizeof(struct treeStruct));
    tree->nodes[0] = "";
    for (int i = 0; i < MAXNUMQS; i++) {
        tree->nodes[i] = malloc(MAXSTRLEN * sizeof(char));
    }

    PositionType top = Top(tree);
    InitTreeHelper(treeFile, tree, top);
    return tree;
}

TreeType InitTreeHelper(FILE *fileToRead, TreeType tree, PositionType pos) {
    // represent tree as a heap
    if (pos->nodeIndex >= MAXNUMQS) {
        return tree;
    }
    char *read = GetNode(tree, pos);
    int offset = CalcOffset(pos->nodeIndex);
    fseek(fileToRead, offset, SEEK_SET);
    fread(read, MAXSTRLEN, 1, fileToRead);
    read = strip(read);
    SetNode(tree, pos, read);
    InitTreeHelper(fileToRead, tree, YesNode(tree, pos));
    return InitTreeHelper(fileToRead, tree, NoNode(tree, pos));
}


PositionType Top(TreeType treffe) {
    PositionType top = malloc(sizeof(struct positionStruct));
    top->nodeIndex = 1;
    return top;
}


char* GetNode(TreeType tree, PositionType pos) {
    if (pos->nodeIndex >= MAXNUMQS) {
        return "";
    }
    return tree->nodes[pos->nodeIndex];
}

void SetNode(TreeType tree, PositionType pos, char *value) {
    tree->nodes[pos->nodeIndex] = value;
}

PositionType YesNode(TreeType tree, PositionType pos) {
    PositionType newPos = malloc(sizeof(struct positionStruct));
    newPos->nodeIndex = pos->nodeIndex * 2;
    return newPos;
}

PositionType NoNode(TreeType tree, PositionType pos) {
    PositionType newPos = malloc(sizeof(struct positionStruct));
    newPos->nodeIndex = pos->nodeIndex * 2 + 1;
    return newPos;
}
