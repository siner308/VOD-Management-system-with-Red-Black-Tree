#include "member_linkedlist.h"

movieNode *memberLinkedInsert(movieNode *movieRoot, movieNode *movie, memberNode *member){
	memberList *newMember = CREATE_MEMBER_LIST;
	memberList *temp = movie->next;

	newMember->id = member->id;
	newMember->name = strdup(member->name);
	newMember->birth = member->birth;
	newMember->posX = member->posX;
	newMember->posY = member->posY;

	if (movie->next){
		// firstid
		if (movie->next->id > newMember->id){
			newMember->next = movie->next;
			movie->next = newMember;
		}

		else{
			// temp->next is not tail
			while (temp->next != NULL){

				if (temp->next->id < newMember->id){
					temp = temp->next;
				}

				else if (temp->next->id > newMember->id){
					newMember->next = temp->next;
					temp->next = newMember;
				}

				else{
					printf("%d is already exist\n", newMember->id);
				}
			}

			// temp->next is tail
			if (temp->next == NULL){
				temp->next = newMember;
			}
		}
	}

	else{
		movie->next = newMember;
	}

	return movieRoot;
} // end of memberLinkedInsert

void memberLinkedPrint(movieNode *movie){
	memberList *temp = movie->next;

	int date = 0;
	int year = 0;
	int month = 0;
	int day = 0;
	int cost = 0;
	int cnt = 0;

	while (temp){
		temp = temp->next;
		cnt++;
	}

	printf("total cost : %dwon\n", (movie->cost) * cnt);
	printf("total member : %d\n", cnt);

	temp = movie->next;

	while (temp){
		date = temp->birth;
		day = date % 100;
		date /= 100;
		month = date % 100;
		date /= 100;
		year = date;

		printf("%d %s %dy %dm %dd (%d, %d)\n", temp->id, temp->name, year, month, day, temp->posX, temp->posY);
		temp = temp->next;
	}
} // end if memberLinkedPrint
