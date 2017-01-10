#include "rbt.h"
#include <time.h>
clock_t start, end;
//initialize the node
const node nil_node = {
	.key = NULL,
	.color = BLACK,
	.left = NULL,
	.right = NULL,
	.parent = NULL
};

//initialize RBT
void Init_RBT(RBT* rbt)
{
	rbt->root = &nil_node;
	rbt->nil = &nil_node;
	rbt->cnt_node = 0;
}

// check if 'key' exist
// exist -> return the 'node', NOT exist -> return NULL
node* isKeyExist(node* nd, int key) {
	
	int cur;
	
	if (nd == &nil_node) 
		return NULL;
	cur = nd->key->id;
	if (cur == key) return nd;
	else if (cur > key)
		return isKeyExist(nd->left, key);
	else
		return isKeyExist(nd->right, key);
}

// allocate node
course* getCourse() {
	course* temp = (course*)malloc(sizeof(course));
	temp->next = NULL;
	return temp;
}
semester* getSemester() {
	semester* temp = (semester*)malloc(sizeof(semester));
	temp->next = NULL;
	temp->courses = NULL;
	return temp;
}
student* getStudent() {
	student* temp = (student*)malloc(sizeof(student));
	temp->semesters = NULL;
	return temp;
}
node* getNode(student* key) {
	node* temp = (node*)malloc(sizeof(node));
	temp->key = key;
	temp->color = BLACK;
	temp->left = &nil_node;
	temp->right = &nil_node;
	temp->parent = &nil_node;
	return temp;
}

// left-rotate
void leftRotate(RBT* rbt, node* x) {
	node* y = x->right;

	x->right = y->left;
	if (y->left != rbt->nil) y->left->parent = x;
	y->parent = x->parent;

	if (x->parent == rbt->nil) rbt->root = y;
	else if (x->parent->left == x) x->parent->left = y;
	else x->parent->right = y;

	y->left = x;
	x->parent = y;
}

// right-rotate
void rightRotate(RBT* rbt, node* x) {
	node* y = x->left;

	x->left = y->right;
	if (y->right != rbt->nil) y->right->parent = x;
	y->parent = x->parent;

	if (x->parent == rbt->nil) rbt->root = y;
	else if (x->parent->right == x) x->parent->right = y;
	else x->parent->left = y;

	y->right = x;
	x->parent = y;
}

// insert node
void RB_insert(RBT* T, node* z) {
	double start = clock();
	T->cnt_node++;
	node *y = T->nil;
	node *x = T->root;

	while (x != T->nil)
	{
		y = x;
		if (z->key->id < x->key->id)
			x = x->left;
		else
			x = x->right;
	}
	z->parent = y;
	if (y == T->nil)
		T->root = z;
	else if (z->key->id < y->key->id)
		y->left = z;
	else
		y->right = z;
	z->left = T->nil;
	z->right = T->nil;
	z->color = RED;
	RB_insert_fixUp(T, z);
	double end = clock();
	printf("time for insertion %.30lf sec\n", (double)end-start);
}

// insert and balance the tree
void RB_insert_fixUp(RBT* T, node* z) {
	
	node* y;

	while (z->parent->color == RED)
	{
		if (z->parent == z->parent->parent->left) {
			y = z->parent->parent->right;
			//case 1
			if (y->color == RED)
			{
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else
			{
				//case 2
				if (z == z->parent->right)
				{
					z = z->parent;
					leftRotate(T, z);
				}
				//case 3
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				rightRotate(T, z->parent->parent);
			}
		}		
		else {
			y = z->parent->parent->left;
			//case 1
			if (y->color == RED)
			{
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else
			{
				//case 2
				if (z == z->parent->left)
				{
					z = z->parent;
					rightRotate(T, z);
				}
				//case 3
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				leftRotate(T, z->parent->parent);
			}
		}
	}
	T->root->color = BLACK;
}

// delete node
void RB_delete(RBT* T, node* z){
	double start = clock();
	T->cnt_node--;
	node* x;
	node* y = z;
	int y_original_color = y->color;
	if (z->left == T->nil) {
		x = z->right;
		RB_transplant(T, z, z->right);
	}
	else if (z->right == T->nil) {
		x = z->left;
		RB_transplant(T, z, z->left);
	}
	else {
		y = minimum(z->right);
		y_original_color = y->color;
		x = y->right;

		if (x != T->nil && y->parent == z)
			x->parent = y;
		else {
			RB_transplant(T, y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}

		RB_transplant(T, z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
	if (y_original_color == BLACK)
		RB_delete_fixup(T, x);
	free(z);
	double end = clock();
	printf("time for insertion %lf sec\n", (double)(end - start));
}

// delete and balance the node
void RB_delete_fixup(RBT* T, node* x)
{
	node* w;
	while (x != T->root && x->color == BLACK)
	{
		if (x == x->parent->left) {
			w = x->parent->right;
			//case 1
			if (w->color == RED)
			{
				w->color = BLACK;
				x->parent->color = RED;
				leftRotate(T, x->parent);
				w = x->parent->right;
			}
			//case 2
			if (w->left->color == BLACK && w->right->color == BLACK)
			{
				w->color = RED;
				x = x->parent;
			}
			else
			{
				//case 3
				if (w->right->color == BLACK)
				{
					w->left->color = BLACK;
					w->color = RED;
					rightRotate(T, w);
					w = x->parent->right;
				}
				//case 4
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				leftRotate(T, x->parent);
				x = T->root;
			}


		}	
		else
		{
			w = x->parent->left;
			//case 1
			if (w->color == RED)
			{
				w->color = BLACK;
				x->parent->color = RED;
				rightRotate(T, x->parent);
				w = x->parent->left;
			}
			//case 2
			if (w->right->color == BLACK && w->left->color == BLACK)
			{
				w->color = RED;
				x = x->parent;
			}
			else
			{
				//case 3
				if (w->left->color == BLACK)
				{
					w->right->color = BLACK;
					w->color = RED;
					leftRotate(T, w);
					w = x->parent->left;
				}
				//case 4
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;
				rightRotate(T, x->parent);
				x = T->root;
			}
		}
	}
	x->color = BLACK;
}

node* minimum(node* x) {
	node* tmp = x;
	while (tmp->left != &nil_node)
		tmp = tmp->left;
	return tmp;
}

void RB_transplant(RBT* T, node* u, node* v)
{
	if (u->parent == T->nil)
		T->root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;
	
	if (v != T->nil)
		v->parent = u->parent;
}
 
// free all nodes
void RB_free_all_nodes(node* nd)
{
	if (nd == &nil_node) 
		return;
	RB_free_all_nodes(nd->left);
	RB_free_all_nodes(nd->right);
	free(nd);
}

void RB_free(node* t) // free 1 node
{
	semester* tmp = NULL;
	semester* ltmp = NULL;
	course* tmp2 = NULL;
	course* ltmp2 = NULL;
	tmp = t->key->semesters;
	while (tmp != NULL) {
		tmp2 = tmp->courses;
		while (tmp2 != NULL) {
			free(tmp2->name);
			ltmp2 = tmp2;
			tmp2 = tmp2->next;
			free(tmp2);
		}
		ltmp = tmp;
		tmp = tmp->next;
		free(tmp);
	}
	free(t->key->name);
	free(t->key);
	free(t);
}

// print all the information in RBT -> in-order traversal (Testing function)
void RB_PRINT(node *T) {
	if (T->key == NULL) {
		return;
	}
	RB_PRINT(T->left);
	printf("\n%d : %s\n", T->key->id, T->key->name);
	semester* tmp = NULL;
	course* tmp2 = NULL;
	tmp = T->key->semesters;
	int i = 1;
	while (tmp != NULL) {
		printf("%d' semester\n", i++);
		tmp2 = tmp->courses;
		while (tmp2 != NULL) {
			printf("\[%s\](%d):%.1f\n", tmp2->name, tmp2->Credit, tmp2->Grade);
			tmp2 = tmp2->next;
		}
		printf("\n");
		tmp = tmp->next;
	}
	RB_PRINT(T->right);
}

// search student and print the information about that student
node* searchstudent(node* T, int key) {
	if (T->key == NULL) {
		return;
	}

	printf("\n%d : %s\n", isKeyExist(T, key)->key->id, isKeyExist(T, key)->key->name);
	semester* tmp = NULL;
	course* tmp2 = NULL;
	tmp = T->key->semesters;
	int i = 1;
	while (tmp != NULL) {
		printf("%d' semester\n", i++);
		tmp2 = tmp->courses;
		while (tmp2 != NULL) {
			printf("\[%s\](%d):%.1f\n", tmp2->name, tmp2->Credit, tmp2->Grade);
			tmp2 = tmp2->next;
		}
		printf("\n");
		tmp = tmp->next;

	}
	GPA(isKeyExist(T, key));
	int tmpcredit = 0;
	tmpcredit = 140 - T->key->credit;
	printf("GPA : %.2f   Credits Left : %d", T->key->GPA, tmpcredit);
}

// print 1 node
void RB_PRINT_NODE(node *t)
{
	printf("\n%d : %s\n", t->key->id, t->key->name);
	printf("Credit : %d   GPA : %.2f\n", t->key->credit, t->key->GPA);
	printf("Remain Credit for graduation : %d\n", 140 - t->key->credit);
	semester* tmp = NULL;
	course* tmp2 = NULL;
	tmp = t->key->semesters;
	int i = 1;
	while (tmp != NULL) {
		printf("%d' semester\n", i++);
		tmp2 = tmp->courses;
		while (tmp2 != NULL) {
			printf("\[%s\](%d):%.1f\n", tmp2->name, tmp2->Credit, tmp2->Grade);
			tmp2 = tmp2->next;
		}
		printf("\n");
		tmp = tmp->next;
	}
}