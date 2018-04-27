/*
** main.c
** red black tree
** AJH
*/

#include "movie_rbtree.h"
#include "member_rbtree.h"
#include "movie_linkedlist.h"
#include "member_linkedlist.h"
#include "type.h"

int main(void){
	movieNode *movieRoot = 0; // root of movie RBT
	movieNode *movieTemp = 0;
	
	memberNode *memberRoot = 0; // root of member RBT
	memberNode *memberTemp = 0;


	// �����Է� ����
	int nMenu = 0; // �ָ޴�
	int subMenu = 0; // �θ޴�

	// ȸ�� ����
	char name[50] = ""; // ȸ���̸�
	int idNew = 10000000; // ȸ����ȣ
	int idOld = 0; // �Է¹ޱ����� ����
	int birth = 0; // ȸ���������
	int posX = 0, posY = 0; // �ּ��� (X, Y)
	int depth = 0;

	// ��ȭ ����
	char title[10] = ""; // ��ȭ����
	int cost = 0; // ��û���
	int date = 0; // ��û����

	// ���� �����
	char filename[11] = "";
	FILE *fp;

	printf("movie1 vs movie11 = ");
	printf("%d\n", strcmp("movie1", "movie11"));
	printf("movie1 vs movie10 = ");
	printf("%d\n", strcmp("movie1", "movie10"));
	printf("movie10 vs movie11 = ");
	printf("%d\n", strcmp("movie10", "movie11"));
	printf("movie2 vs movie11 = ");
	printf("%d\n", strcmp("movie2", "movie11"));

	// ���� �Է�
	printf("enter movie file name : ");
	scanf("%s", filename);
	
	// ��ȭ ����
	fp = fopen((const char *)filename, "r");
	
	while (!feof(fp)){
		fscanf(fp, "%s %d", title, &cost);
		movieRoot = movieRBTInsertMain(movieRoot, title, cost);
	}

	fclose(fp);

	printf("enter member file name : ");
	scanf("%s", filename);

	fp = fopen((const char *)filename, "r");

	while (!feof(fp)){
		fscanf(fp, "%s %d %d %d %d %s %d", name, &birth, &posX, &posY, &date, title, &cost);
		memberRoot = memberRBTInsertMain(memberRoot, idNew, name, birth, posX, posY, date, title, cost); // ȸ�� �߰��ϰ�, ȸ���� ��ȭ����Ʈ�� ��ȭ�ֱ�
		movieTemp = movieRBTSearch(movieRoot, title); // ��ȭ ã��
		memberTemp = memberRBTSearch(memberRoot, idNew); // ȸ�� ã��
		movieRoot = memberLinkedInsert(movieRoot, movieTemp, memberTemp); // ��ȭ�� ȸ������Ʈ�� ȸ���ֱ�
		idNew++;
	}

	while (nMenu != 5){
		printf("1: Edit Movie, 2: Search Movie, 3: Edit Member, 4: Search Member, 5: Exit :");
		scanf("%d", &nMenu);

		// edit movie
		if (nMenu == 1){
			subMenu = 0;

			while (subMenu != 3){
				printf("1: edit cost, 2: add movie, 3: exit : ");
				scanf("%d", &subMenu);

				// edit movie
				if (subMenu == 1){
					printf("title : ");
					scanf("%s", title);
					printf("cost : ");
					scanf("%d", &cost);
					movieRoot = movieRBTEdit(movieRoot, title, cost);
				}

				// new movie
				else if (subMenu == 2){
					printf("title : ");
					scanf("%s", title);
					printf("cost : ");
					scanf("%d", &cost);
					movieRoot = movieRBTInsertMain(movieRoot, title, cost);
				}

				// exit
				else if (subMenu == 3){
					break;
				}

				// wrong access
				else{
					printf("wrong access\n");
				}
			}
		}

		// search movie
		else if (nMenu == 2){
			printf("title : ");
			scanf("%s", title);

			movieTemp = movieRBTSearch(movieRoot, title); // ��ȭã��

			if (movieTemp){
				memberLinkedPrint(movieTemp); // ��ȭ�� �� ȸ�� ����ϱ�
			}
		}

		// edit member
		else if (nMenu == 3){
			subMenu = 0;

			while (subMenu != 3){
				printf("1: add movie, 2: new member, 3: exit : ");
				scanf("%d", &subMenu);

				// �߰���û
				if (subMenu == 1){
					printf("id: ");
					scanf("%d", &idOld);
					printf("date: ");
					scanf("%d", &date);
					printf("title: ");
					scanf("%s", title);

					// ã��
					memberTemp = memberRBTSearch(memberRoot, idOld); // ȸ��ã��

					if (memberTemp){ // ȸ���� �����Ѵ�.
						movieTemp = movieRBTSearch(movieRoot, title); // ��ȭã��

						if (movieTemp){ // ��ȭ�� �����Ѵ�.
							// insert to list
							memberRoot = movieLinkedInsert(memberRoot, memberTemp, movieTemp, date); // ȸ���� ��ȭ����Ʈ�� ��ȭ�ֱ�
							movieRoot = memberLinkedInsert(movieRoot, movieTemp, memberTemp); // ��ȭ�� ȸ������Ʈ�� ȸ���ֱ�
						}

						else{
							printf("no movie exist\n");
						}
					}

					else{
						printf("no member exist\n");
					}
				}

				// �ű԰���
				else if (subMenu == 2){
					printf("name : ");
					scanf("%s", name);
					printf("birth (YYYYMMDD): ");
					scanf("%d", &birth);
					printf("posX, posY : ");
					scanf("%d %d", &posX, &posY);
					printf("title : ");
					scanf("%s", title);
					printf("date : ");
					scanf("%d", date);

					// ��ȭã��
					movieTemp = movieRBTSearch(movieRoot, title); // ��ȭ���ã��

					// ȸ�� �߰��ϰ�, ȸ���� ��ȭ����Ʈ�� ��ȭ�ֱ�
					memberRoot = memberRBTInsertMain(memberRoot, idNew, name, birth, posX, posY, date, title, movieTemp->cost);

					// ���ã��
					memberTemp = memberRBTSearch(memberRoot, idNew); // ȸ�����ã��

					// ��ȭ�� ȸ������Ʈ�� ȸ���ֱ�
					movieRoot = memberLinkedInsert(movieRoot, movieTemp, memberTemp);

					idNew++;
				}
			}
		}

		else if (nMenu == 4){
			printf("(1) id: ");
			scanf("%d", &idOld);
			memberTemp = memberRBTSearch(memberRoot, idOld);

			if (memberTemp){
				depth = memberRBTCheckDepth(memberRoot, idOld);
				movieLinkedPrint(memberTemp, depth);
			}
		}

		else if (nMenu == 5){
			break;
		}

		else{
			printf("wrong access\n");
		}
	}

	// ������ ���� ����� ���� �������� ����
	remove("input1.txt");
	remove("input2.txt");

	// ��ȭ���� �����
	fp = fopen("input1.txt", "w");
	fprintfMovie(fp, movieRoot);
	fclose(fp);

	// ȸ������ �����
	fp = fopen("input2.txt", "w");
	fprintfMember(fp, memberRoot);
	fclose(fp);

	return 0;
}

void printmovie(movieNode *root){
	if (root->title){
		printmovie(root->left);
		printmovie(root->right);
		printf("%s %c", root->title, root->color);

		if (root->parent){
			printf("\n");
		}
	}
}