//
// Created by Carlo Revelli on 2019-04-15.
//

#include "common.c"
#include "animal.h"


PositionType YesNode(TreeType tree, PositionType pos) {
    PositionType newPos = malloc(sizeof(struct positionStruct));
    newPos->node = pos->node->left;
    return newPos;
}

PositionType NoNode(TreeType tree, PositionType pos) {
    PositionType newPos = malloc(sizeof(struct positionStruct));
    newPos->node = pos->node->right;
    return newPos;
}

char* GetNode(TreeType tree, PositionType pos) {
    if (pos->node == NULL) {
        return "";
    } else {
        return pos->node->string;
    }
}

void SetNode(TreeType tree, PositionType pos, char *string) {
    pos->node->string = string;
}

PositionType Top(TreeType tree) {
    PositionType newPos = malloc(sizeof(struct positionStruct));
    newPos->node = tree;
    return newPos;
}

TreeType InitTree(FILE *treeFile)
{
    return InitTreeHelperD(treeFile, 1);
}

TreeType InitTreeHelperD(FILE *fileToRead, int depth) {
    if (depth >= MAXNUMQS) {
        return NULL;
    }
    int offset = CalcOffset(depth);
    char *string = malloc(MAXSTRLEN * sizeof(char));
    fseek(fileToRead, offset, SEEK_SET);
    fread(string, MAXSTRLEN, 1, fileToRead);
    string = strip(string);
    TreeType node = malloc(sizeof(struct treeStruct));
    node->string = string;
    if (string[0] != '\0') {
        node->left = InitTreeHelperD(fileToRead, depth * 2);
        node->right = InitTreeHelperD(fileToRead, depth * 2 + 1);
    } else {
        node->left = NULL;
        node->right = NULL;
    }

    return node;
}
