#include "movie_rbtree.h"

// n : new movieNode
// p : parent (parent of new)
// g : grandparent (parent of parent and uncle)
// u : uncle (another child of grandparent)

movieNode *movieRBTInsertMain(movieNode *root, char *newTitle, int newCost){
	movieNode *n = CREATE_MOVIE_NODE;
	movieNode *leafL = CREATE_MOVIE_NODE;
	movieNode *leafR = CREATE_MOVIE_NODE;
	movieNode *temp = root;
	movieNode *tempRoot = root;

	// init new
	n->title = strdup(newTitle);
	n->cost = newCost;
	n->left = leafL;
	n->right = leafR;
	n->color = 'R';

	// init leaves
	// left leaf
	leafL->parent = n;
	leafL->left = NULL;
	leafL->right = NULL;
	leafL->cost = 0;
	leafL->title = 0;
	leafL->color = 'B';

	// right leaf
	leafR->parent = n;
	leafR->left = NULL;
	leafR->right = NULL;
	leafL->cost = 0;
	leafR->title = 0;
	leafR->color = 'B';

	// first insert
	if (temp == NULL){
		root = n;
	}

	// not first insert
	else{
		// find leaf
		while (temp->cost != 0){

			// go to left
			if (strcmp(n->title, temp->title) < 0){
				temp = temp->left;
			}

			// go to right
			else if (strcmp(n->title, temp->title) > 0){
				temp = temp->right;
			}

			// error handling: if title is already exist
			else if (strcmp(n->title, temp->title) == 0){
				printf("%s is already exist\n", n->title);
				free(leafL);
				free(leafR);
				free(n);
				return root;
			}

			else{
				printf("wrong access (insert title)\n");
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

	tempRoot = movieRBTInsertCase1(root, n);

	// set root to real root
	while (tempRoot->parent != NULL){
		tempRoot = tempRoot->parent;
	}

	root = tempRoot;

	return root;
} // end of movieRBTInsertMain

movieNode *movieRBTInsertCase1(movieNode *root, movieNode *n){
	//printf("1 ");
	// n is root
	if (n->parent == NULL){
		// root is black
		n->color = 'B';
	}

	// n is not root
	else{
		movieRBTInsertCase2(root, n);
	}

	return root;
} // end of movieRBTInsertCase1

movieNode *movieRBTInsertCase2(movieNode *root, movieNode *n){
	//printf("2 ");
	// p is red (grandparent is exist)
	if (n->parent->color == 'R'){
		movieRBTInsertCase3(root, n);
	}

	return root;
} // end of movieRBTInsertCase2

movieNode *movieRBTInsertCase3(movieNode *root, movieNode *n){
	//printf("3 ");
	movieNode *u = movieRBTUncle(n);
	movieNode *g = movieRBTGrandparent(n);

	// u is red
	if (u->color == 'R'){
		n->parent->color = 'B';
		u->color = 'B';
		g->color = 'R';
		movieRBTInsertCase1(root, g);
	}

	// u is black (or leaf)
	else{
		movieRBTInsertCase4(root, n);
	}

	return root;
} // end of movieRBTInsertCase3

movieNode *movieRBTUncle(movieNode *n){
	//printf("u ");
	movieNode *g = movieRBTGrandparent(n);

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
} // end of movieRBTUncle

movieNode *movieRBTGrandparent(movieNode *n){
	//printf("g ");
	// n is not root
	if (n->parent != NULL){
		return n->parent->parent;
	}

	// n is root
	else{
		return NULL;
	}
} // end of movieRBTGrandparent

movieNode *movieRBTInsertCase4(movieNode *root, movieNode *n){
	//printf("4 ");
	movieNode *p = n->parent;
	movieNode *g = movieRBTGrandparent(n);

	// p is left from g && n is right from p
	if ((g->left == p) && (p->right == n)){
		movieRBTRotateLeft(root, n);
		n = n->left;
	}

	else if ((g->right == p) && (p->left == n)){
		movieRBTRotateRight(root, n);
		n = n->right;
	}

	movieRBTInsertCase5(root, n);

	return root;
} // end of movieRBTInsertCase4

movieNode *movieRBTRotateLeft(movieNode *root, movieNode *n){
	//printf("rL ");
	movieNode *g = movieRBTGrandparent(n);
	movieNode *p = n->parent;

	p->right = n->left;
	n->left->parent = p;

	n->left = p;
	p->parent = n;

	g->left = n;
	n->parent = g;

	return root;
} // end of movieRBTRotateLeft

movieNode *movieRBTRotateRight(movieNode *root, movieNode *n){
	//printf("rR ");
	movieNode *g = movieRBTGrandparent(n);
	movieNode *p = n->parent;

	p->left = n->right;
	n->right->parent = p;

	n->right = p;
	p->parent = n;

	g->right = n;
	n->parent = g;

	return root;
} // end of movieRBTRotateRight

movieNode *movieRBTInsertCase5(movieNode *root, movieNode *n){
	//printf("5 ");
	movieNode *g = movieRBTGrandparent(n);
	movieNode *u = movieRBTUncle(n);
	movieNode *p = n->parent;
	movieNode *temp = 0;


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

	// rotate right
	if (p->left == n){
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
} // end of movieRBTInsertCase5

movieNode *movieRBTEdit(movieNode *movieRoot, char *title, int cost){
	movieNode *temp = 0;

	temp = movieRBTSearch(movieRoot, title);

	temp->cost = cost;
} // end of movieRBTEdit

movieNode *movieRBTSearch(movieNode *movieRoot, char *title){
	movieNode *temp = movieRoot;

	while (temp->title != 0){
		if (strcmp(title, temp->title) < 0){
			temp = temp->left;
		}
		else if (strcmp(title, temp->title) > 0){
			temp = temp->right;
		}
		else{
			return temp;
		}
	}

	if (temp->title == 0){
		printf("%s is not exist\n", title);
		return NULL;
	}

	else{
		printf("wrong access\n");
		return NULL;
	}
} // end of movieRBTSearch

void fprintfMovie(FILE *fp, movieNode *movieRoot){
	if (movieRoot->title){
		fprintfMovie(fp, movieRoot->left);
		fprintfMovie(fp, movieRoot->right);
		fprintf(fp, "%s %d", movieRoot->title, movieRoot->cost);

		if (movieRoot->parent){
			fprintf(fp, "\n");
		}
	}
} // end of fprintfMovie