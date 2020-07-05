.PHONY: clean all

all : scores

scores : scoresAgain.c bst.c bst.h 
	gcc scoresAgain.c bst.c -o scores

clean :
	rm -f scores *.out *.ref *.diff *.in *.o
