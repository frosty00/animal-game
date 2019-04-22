
#define ONE 1
#define filePath "/Users/carlorevelli/Documents/School Work/Computer Science/Self Pace/spring/proj4/tree.txt"

#include "animal.h"

#if ONE
#include "animal1.c"
#else
#include "animal2.c"
#endif

/*
 *  Play the "animal" game, in which the program attempts to guess an animal
 *  that the user is thinking of by asking yes or no questions. Eventually,
 *  the program either will guess the user's animal or run out of questions
 *  to ask. In the latter case, the program will ask the user to provide a
 *  yes-or-no question that would distinguish between the user's animal and
 *  the program's best guess.
 *  The data structure of questions and guesses is essentially a binary tree,
 *  with each internal node having a "yes" branch and a "no" branch. Leaves
 *  of the tree represent animals to be guessed by the program. If the program
 *  fails to guess the user's animal, it replaces one of the leaves of the tree
 *  by a node containing the new question, whose children are the program's
 *  best guess and the animal provided by the user.
 *  The structure of the program is simple. It initializes the question/guess
 *  data structure, then plays games as long as the user is interested. In each
 *  game, the program starts at the top of the tree (the root) and progresses 
 *  toward the bottom (the leaves) depending on the user's responses. Once it
 *  reaches a leaf, it either has won or lost, and handles the situation as
 *  described above.
 */


int main (int argc, char *argv[]) {
	FILE *treefile = fopen(filePath, "r");
	if (treefile == NULL) {
        perror("Invalid tree file");
        exit(100);
    }
	TreeType tree;
	PositionType pos, prevPos;
	char newQuestion[MAXSTRLEN], newAnswer[MAXSTRLEN];
	//DefaultTree(treefile);
	tree = InitTree (treefile);
	WriteTree(tree, treefile);
	printf("%s", "Think of an animal. I will try to guess what is.\n"
					 "Please answer my questions with yes or no.\n");
	while (true) {
		pos = Top (tree);
		while (!IsLeaf (tree, pos)) {
			prevPos = pos;
			pos = Answer (Question (tree, pos))?
				YesNode (tree, pos): NoNode (tree, pos);
			free(prevPos);
		}
		if (Answer (Guess (tree, pos))) {
			printf ("I got it right!\n");
		} else {
			GetNewInfo (tree, pos, newAnswer, newQuestion);
			ReplaceNode (tree, pos, newAnswer, newQuestion);
			//WriteTree(tree, treefile);
		}
		if (!Answer ("Want to play again? ")) {
			WriteTree(tree, treefile);
			fclose(treefile);
			treefile = fopen(filePath, "r");
			return 0;
		}
	}
}