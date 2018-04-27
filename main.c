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


	// 질의입력 변수
	int nMenu = 0; // 주메뉴
	int subMenu = 0; // 부메뉴

	// 회원 변수
	char name[50] = ""; // 회원이름
	int idNew = 10000000; // 회원번호
	int idOld = 0; // 입력받기위한 변수
	int birth = 0; // 회원생년월일
	int posX = 0, posY = 0; // 주소지 (X, Y)
	int depth = 0;

	// 영화 변수
	char title[10] = ""; // 영화제목
	int cost = 0; // 시청요금
	int date = 0; // 시청일자

	// 파일 입출력
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

	// 파일 입력
	printf("enter movie file name : ");
	scanf("%s", filename);
	
	// 영화 관리
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
		memberRoot = memberRBTInsertMain(memberRoot, idNew, name, birth, posX, posY, date, title, cost); // 회원 추가하고, 회원의 영화리스트에 영화넣기
		movieTemp = movieRBTSearch(movieRoot, title); // 영화 찾기
		memberTemp = memberRBTSearch(memberRoot, idNew); // 회원 찾기
		movieRoot = memberLinkedInsert(movieRoot, movieTemp, memberTemp); // 영화의 회원리스트에 회원넣기
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

			movieTemp = movieRBTSearch(movieRoot, title); // 영화찾기

			if (movieTemp){
				memberLinkedPrint(movieTemp); // 영화를 본 회원 출력하기
			}
		}

		// edit member
		else if (nMenu == 3){
			subMenu = 0;

			while (subMenu != 3){
				printf("1: add movie, 2: new member, 3: exit : ");
				scanf("%d", &subMenu);

				// 추가시청
				if (subMenu == 1){
					printf("id: ");
					scanf("%d", &idOld);
					printf("date: ");
					scanf("%d", &date);
					printf("title: ");
					scanf("%s", title);

					// 찾기
					memberTemp = memberRBTSearch(memberRoot, idOld); // 회원찾기

					if (memberTemp){ // 회원이 존재한다.
						movieTemp = movieRBTSearch(movieRoot, title); // 영화찾기

						if (movieTemp){ // 영화가 존재한다.
							// insert to list
							memberRoot = movieLinkedInsert(memberRoot, memberTemp, movieTemp, date); // 회원의 영화리스트에 영화넣기
							movieRoot = memberLinkedInsert(movieRoot, movieTemp, memberTemp); // 영화의 회원리스트에 회원넣기
						}

						else{
							printf("no movie exist\n");
						}
					}

					else{
						printf("no member exist\n");
					}
				}

				// 신규가입
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

					// 영화찾기
					movieTemp = movieRBTSearch(movieRoot, title); // 영화노드찾기

					// 회원 추가하고, 회원의 영화리스트에 영화넣기
					memberRoot = memberRBTInsertMain(memberRoot, idNew, name, birth, posX, posY, date, title, movieTemp->cost);

					// 멤버찾기
					memberTemp = memberRBTSearch(memberRoot, idNew); // 회원노드찾기

					// 영화의 회원리스트에 회원넣기
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

	// 파일을 새로 만들기 전에 기존파일 삭제
	remove("input1.txt");
	remove("input2.txt");

	// 영화파일 재생성
	fp = fopen("input1.txt", "w");
	fprintfMovie(fp, movieRoot);
	fclose(fp);

	// 회원파일 재생성
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