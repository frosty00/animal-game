//
// Created by Carlo Revelli on 2019-04-09.
//

#include "animal.h"


bool Answer(char* question) {
    char answer[MAXSTRLEN];
    printf("%s\n", question);
    scanf("%s", answer);
    char firstLetter = answer[0];
    return firstLetter == 'y' || firstLetter == 'Y';
}

bool isVowel(char *word) {
    return strchr("aeiou", word[0]) != '\0';
}

bool IsLeaf(TreeType tree, PositionType pos) {
    PositionType yesNode = YesNode(tree, pos);
    PositionType noNode = NoNode(tree, pos);
    bool result = GetNode(tree, yesNode)[0] == '\0'
            && GetNode(tree, noNode)[0] == '\0';
    free(yesNode);
    free(noNode);
    return result;
}

bool WriteTree(TreeType tree, FILE *file) {
    bool result = WriteTreeHelper(tree, Top(tree), file, 0);
    return result;
}

bool WriteTreeHelper(TreeType tree, PositionType pos, FILE *fileDescriptor, int depth) {
    char format[20];
    char *node = GetNode(tree, pos);
    char emptyLine[MAXSTRLEN + 1];
    memset(emptyLine, ' ', sizeof(emptyLine));
    emptyLine[MAXSTRLEN] = '\0';
    if (node[0] != '\0') {
        sprintf(format, "%%-%ds\n", MAXSTRLEN - depth);
        char *leftString = &emptyLine[MAXSTRLEN - depth];
        printf("%s", leftString);
        printf(format, node);
        fprintf(fileDescriptor, "%s", leftString);
        fprintf(fileDescriptor, format, node);
    } else {
        printf("%s\n", emptyLine);
        fprintf(fileDescriptor, "%s\n", emptyLine);
    }
    if (depth < log2(MAXNUMQS) - 1) {
        return WriteTreeHelper(tree, YesNode(tree, pos), fileDescriptor, depth + 1)
            && WriteTreeHelper(tree, NoNode(tree, pos), fileDescriptor, depth + 1);
    } else {
        return true;
    }

}

char* Question(TreeType tree, PositionType pos) {
    static char questionMemory[MAXSTRLEN];
    char *node = GetNode(tree, pos);
    questionMemory[0] = '\0';
    char lastLetter = node[strlen(node) - 1];
    strcat(questionMemory, "Does it ");
    if (lastLetter == 's') {
        strcat(questionMemory, "have ");
    }
    strcat(questionMemory, node);
    strcat(questionMemory, "?");
    return questionMemory;
}

char* Guess(TreeType tree, PositionType pos) {
    static char guessMemory[MAXSTRLEN];
    char *node = GetNode(tree, pos);
    char *preposition = isVowel(node) ? "n ": " ";
    guessMemory[0] = '\0';
    strcat(guessMemory, "Are you thinking of a");
    strcat(guessMemory, preposition);
    strcat(guessMemory, node);
    strcat(guessMemory, "?");
    return guessMemory;
}


int *DecToBin(int n, int *buffer) {
    if (n > 1) {
        *(buffer+2) = -1;
        DecToBin(n >> 1, buffer+1);
    }
    *buffer = n & 1;
    return buffer;
}


int CalcOffset(int n) {
    // i made up this algorithm to select a line in a tree
    static int size = 32;
    int binary[size];
    DecToBin(n, binary);
    bool began = false;
    int offset = 0;
    int depth = 0;
    for (int i = size - 1; i > -1; i--) {
        if (binary[i] == -1) {
            began = true;
            i--;
            continue;
        }
        if (!began) {
            continue;
        }
        depth++;
        if (binary[i]) {
            // no
            offset += (int) (MAXNUMQS / pow(2, depth));
        } else {
            // yes
            offset++;
        }
    }
    return offset * (MAXSTRLEN + 1);
}

void ReplaceNode(TreeType tree, PositionType pos, char* newA, char* newQ) {
    char *oldAnswer = GetNode(tree, pos);
    SetNode(tree, pos, newQ);
    SetNode(tree, YesNode(tree, pos), newA);
    SetNode(tree, NoNode(tree, pos), oldAnswer);
}

void GetNewInfo(TreeType tree, PositionType pos, char* newA, char* newQ) {
  printf("Oopsie, I don't know that animal?\nPlease enter the animal you are thinking of: ");
  scanf("%s", newA);
  printf("\n");
  char *animal = GetNode(tree, pos);
  char *prep1 = isVowel(newA) ? "an" : "a";
  char *prep2 = isVowel(animal) ? "an" : "a";
  while ((getchar()) != '\n'); // clear input buffer
  printf("What is a (verb) question that is yes for %s %s and no for %s %s?\n", prep1, newA, prep2, animal);
  scanf("%[^\n]", newQ);
}

char* strip(char *word) {
    if (word[0] == '\0') {
        return word;
    }
    while (isspace(*word)) {
        word++;
    }
    int end = 0;
    while (end < MAXSTRLEN && !(isspace(*(word+end)) && isspace(*(word+end+1)))) {
        end++;
    }
    word[end] = '\0';
    return word;
}

void DefaultTree(FILE *treefile) {
    #if ONE
    char *treeArray[MAXNUMQS] = {
    "", // 0
    "wings", // 1
    "fly", // 2
    "two legs", // 3
    "pigeon", // 4
    "ostrich", // 5
    "human", // 6
    "more than four legs", // 7
    "", // 8
    "", // 9
    "", // 10
    "", // 11
    "", // 12
    "", // 13
    "insect", // 14
    "cow", // 15
    };
    TreeType tree = malloc(sizeof(struct treeStruct));
    for (int i = 0; i < MAXNUMQS; i++) {
    tree->nodes[i] = treeArray[i];
    }
    WriteTree(tree, treefile);
    #endif
}
