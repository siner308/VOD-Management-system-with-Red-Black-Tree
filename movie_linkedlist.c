#include "movie_linkedlist.h"

memberNode *movieLinkedInsert(memberNode *memberRoot, memberNode *member, movieNode *movie, int date){
	movieList *newMovie = CREATE_MOVIE_LIST;
	movieList *temp = member->next;

	newMovie->date = date;
	newMovie->title = strdup(movie->title);
	newMovie->cost = movie->cost;

	// firstdate
	if (member->next->date > date){
		newMovie->next = member->next;
		member->next = newMovie;
	}

	else{
		// temp->next is not tail
		while (temp->next->next != NULL){

			if (temp->next->next->date < date){
				temp = temp->next;
			}

			else{
				newMovie->next = temp->next->next;
				temp->next->next = newMovie;
			}
		}

		// temp->next is tail
		if (temp->next->next == NULL){
			temp->next->next = newMovie;
		}
	}

	return memberRoot;
} // end if movieLinkedInsert

void movieLinkedPrint(memberNode *member, int depth){
	movieList *temp = member->next;
	char index = 'a';
	int date = 0;
	int day = 0;
	int month = 0;
	int year = 0;
	int totalCost = 0;

	date = member->birth;
	day = date % 100;
	date /= 100;
	month = date % 100;
	date /= 100;
	year = date;

	printf("(2) name : %s\n", member->name);
	printf("(3) birth : %dy %dm %dd\n", year, month, day);
	printf("(4) pos: (%d, %d)\n", member->posX, member->posY);
	printf("(5) record\n");

	while (temp){
		date = temp->date;
		day = date % 100;
		date /= 100;
		month = date % 100;
		date /= 100;
		year = date;
		totalCost += temp->cost;
		printf("(%c) %dy %dm %dd, %s, %dwon\n", index++, year, month, day, temp->title, temp->cost);
		temp = temp->next;
	}

	printf("(6) total cost: %dwon\n", totalCost);
	printf("(7) node depth: %d\n", depth);
} // end of movieLinkedPrint