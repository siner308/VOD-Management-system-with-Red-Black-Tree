#include "member_rbtree.h"

// n : new memberNode
// p : parent (parent of new)
// g : grandparent (parent of parent and uncle)
// u : uncle (another child of grandparent)

memberNode *memberRBTInsertMain(memberNode *root, int id, char *name, int birth, int posX, int posY, int date, char *title, int cost){
	memberNode *n = CREATE_MEMBER_NODE;
	movieList *list = CREATE_MOVIE_LIST;
	memberNode *leafL = CREATE_MEMBER_NODE;
	memberNode *leafR = CREATE_MEMBER_NODE;
	memberNode *tempRoot = root;
	memberNode *temp = root;

	// init new
	n->left = leafL;
	n->right = leafR;
	n->id = id;
	n->name = strdup(name);
	n->birth = birth;
	n->posX = posX;
	n->posY = posY;
	n->color = 'R';
	n->next = list;

	list->title = strdup(title);
	list->date = date;
	list->cost = cost;
	list->next = NULL;

	// init leaves
	// left leaf
	leafL->parent = n;
	leafL->left = NULL;
	leafL->right = NULL;
	leafL->id = 0;
	leafL->name = 0;
	leafL->birth = 0;
	leafL->posX = 0;
	leafL->posY = 0;
	leafL->color = 'B';
	leafL->next = NULL;


	// right leaf
	leafR->parent = n;
	leafR->left = NULL;
	leafR->right = NULL;
	leafR->id = 0;
	leafR->name = 0;
	leafR->birth = 0;
	leafR->posX = 0;
	leafR->posY = 0;
	leafR->color = 'B';
	leafR->next = NULL;

	// first insert
	if (temp == NULL){
		root = n;
	}

	// not first insert
	else{
		// find leaf
		while (temp->id != 0){
			// go to left
			if (n->id < temp->id){
				temp = temp->left;
			}

			// go to right
			else if (n->id > temp->id){
				temp = temp->right;
			}

			else if (n->id == temp->id){
				printf("%d is already exist\n", temp->id);
				free(leafL);
				free(leafR);
				free(n);
				return root;
			}

			else{
				printf("wrong access (insert key)\n");
			}
		}

		// link to parent
		n->parent = temp->parent;

		// link to left
		if (temp->parent->left == temp){
			temp->parent->left = n;
		}

		// link to right
		else{
			temp->parent->right = n;
		}

		free(temp);
	}

	tempRoot = memberRBTInsertCase1(root, n);

	while (tempRoot->parent != NULL){
		tempRoot = tempRoot->parent;
	}

	root = tempRoot;

	return root;
} // end of memberRBTInsertMain

memberNode *memberRBTInsertCase1(memberNode *root, memberNode *n){
	//printf("1 ");
	// n is root
	if (n->parent == NULL){

		// root is black
		n->color = 'B';
	}

	// n is not root
	else{
		memberRBTInsertCase2(root, n);
	}

	return root;
} // end of memberRBTInsertCase1

memberNode *memberRBTInsertCase2(memberNode *root, memberNode *n){
	//printf("2 ");
	// p is red (grandparent is exist)
	if (n->parent->color == 'R'){
		memberRBTInsertCase3(root, n);
	}

	return root;
} // end of memberRBTInsertCase2

memberNode *memberRBTInsertCase3(memberNode *root, memberNode *n){
	//printf("3 ");
	memberNode *u = memberRBTUncle(n);
	memberNode *g = memberRBTGrandparent(n);

	// u is red
	if (u->color == 'R'){
		n->parent->color = 'B';
		u->color = 'B';
		g->color = 'R';
		memberRBTInsertCase1(root, g);
	}

	// u is black (or leaf)
	else{
		memberRBTInsertCase4(root, n);
	}

	return root;
} // end of memberRBTInsertCase3

memberNode *memberRBTUncle(memberNode *n){
	//printf("u ");
	memberNode *g = memberRBTGrandparent(n);

	// p is not root
	if (g != NULL){

		// p is left from g
		if (g->left == n->parent){
			return g->right;
		}

		// p is right from g
		else{
			return g->left;
		}
	}

	// parent is root
	else{
		return NULL;
	}
} // end of memberRBTUncle

memberNode *memberRBTGrandparent(memberNode *n){
	//printf("g ");
	// n is not root
	if (n->parent != NULL){
		return n->parent->parent;
	}

	// n is root
	else{
		return NULL;
	}
} // end of memberRBTGrandparent

memberNode *memberRBTInsertCase4(memberNode *root, memberNode *n){
	//printf("4 ");
	memberNode *p = n->parent;
	memberNode *g = memberRBTGrandparent(n);

	// p is left from g && n is right from p
	if ((g->left == p) && (p->right == n)){
		memberRBTRotateLeft(root, n);
		n = n->left;
	}

	else if ((g->right == p) && (p->left == n)){
		memberRBTRotateRight(root, n);
		n = n->right;
	}

	memberRBTInsertCase5(root, n);

	return root;
} // end of memberRBTInsertCase4

memberNode *memberRBTRotateLeft(memberNode *root, memberNode *n){
	//printf("rL ");
	memberNode *g = memberRBTGrandparent(n);
	memberNode *p = n->parent;

	p->right = n->left;
	n->left->parent = p;

	n->left = p;
	p->parent = n;

	g->left = n;
	n->parent = g;

	return root;
} // end of memberRBTRotateLeft

memberNode *memberRBTRotateRight(memberNode *root, memberNode *n){
	//printf("rR ");
	memberNode *g = memberRBTGrandparent(n);
	memberNode *p = n->parent;

	p->left = n->right;
	n->right->parent = p;

	n->right = p;
	p->parent = n;

	g->right = n;
	n->parent = g;

	return root;
} // end of memberRBTRotateRight

memberNode *memberRBTInsertCase5(memberNode *root, memberNode *n){
	//printf("5 ");
	memberNode *g = memberRBTGrandparent(n);
	memberNode *u = memberRBTUncle(n);
	memberNode *p = n->parent;
	memberNode *temp = 0;

	// rotate right
	if (p->left == n){
		// g is not root
		if (g->parent){
			// p <- g's parent
			if (g->parent->right == g){
				g->parent->right = p;
			}

			else{
				g->parent->left = p;
			}
			// p -> g's parent
			p->parent = g->parent;
		}

		else{
			p->parent = NULL;
		}

		// g -> p's right (leaf)
		g->left = p->right;
		// g <- p's right (leaf)
		p->right->parent = g;
		// g -> p
		g->parent = p;
		// g <- p
		p->right = g;
	}

	// rotate left
	else{
		// g is not root
		if (g->parent){
			// p <- g's parent
			if (g->parent->right == g){
				g->parent->right = p;
			}

			else{
				g->parent->left = p;
			}
			// p -> g's parent
			p->parent = g->parent;
		}
		else{
			p->parent = NULL;
		}

		// g -> p's right (leaf)
		g->right = p->left;
		// g <- p's right (leaf)
		p->left->parent = g;
		// g -> p
		g->parent = p;
		// g <- p
		p->left = g;
	}

	g->color = 'R';
	p->color = 'B';
	u->color = 'B';
	n->color = 'R';

	return root;
} // end of memberRBTInsertCase5

memberNode *memberRBTSearch(memberNode *root, int id){
	memberNode *temp = root;

	while (temp->id != 0){
		if (id < temp->id){
			temp = temp->left;
		}
		else if (id > temp->id){
			temp = temp->right;
		}
		else{
			return temp;
		}
	}

	if (temp->id == 0){
		printf("%d is not exist\n", id);
		return NULL;
	}

	else{
		printf("wrong access\n");
		return NULL;
	}
} // end of memberRBTSearch

int memberRBTCheckDepth(memberNode *memberRoot, int idOld){
	memberNode *temp = memberRoot;
	int cnt = 0;

	while (temp->id != 0){

		if (temp->id > idOld){
			temp = temp->left;
			cnt++;
		}

		else if (temp->id < idOld){
			temp = temp->right;
			cnt++;
		}

		else{
			return cnt;
		}
	}

	if (temp->id == 0){
		return 0;
	}
} // end of memberRBTCheckDepth

void fprintfMember(FILE *fp, memberNode *memberRoot){
	if (memberRoot->id != 0){
		fprintfMember(fp, memberRoot->left);
		fprintfMember(fp, memberRoot->right);
		fprintf(fp, "%s %d %d %d %d %s %d", memberRoot->name, memberRoot->birth, memberRoot->posX, memberRoot->posY, memberRoot->next->date, memberRoot->next->title, memberRoot->next->cost);

		if (memberRoot->parent){
			fprintf(fp, "\n");
		}
	}
} // end of fprintmember