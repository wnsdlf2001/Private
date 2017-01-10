#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RED 0
#define BLACK 1
#define TRUE 1
#define FALSE 0

typedef struct _course course; //course structure
typedef struct _course {
	course *next;
	char* name;
	float Grade;
	int Credit;
}course;

typedef struct _semester semester; //semester structure
typedef struct _semester {
	semester *next;
	course *courses;
	int cnum;
}semester;

typedef struct _student student; //student structure
typedef struct _student {
	unsigned id;
	char *name;
	float GPA;
	int credit;
	semester *semesters;
}student;

typedef struct _node node;
typedef struct _node {
	student *key; // unique key value for each student
	int color;
	node  *left, *right;
	node  *parent;
}node;

//RB tree
typedef struct _rbtree {
	node* root;
	node* nil;
	int cnt_node;
} RBT;

void Init_RBT(RBT* rbt);
node* isKeyExist(node* nd, int key);
node* getNode(student* key);
student* getStudent();
semester* getSemester();
course* getCourse();
void leftRotate(RBT* rbt, node* x);
void rightRotate(RBT* rbt, node* x);
void RB_insert(RBT* T, node* z);
void RB_insert_fixUp(RBT* T, node* z);
node* minimum(node* x);
void RB_transplant(RBT* T, node* u, node* v);
void RB_delete(RBT* T, node* z);
void RB_delete_fixup(RBT* T, node* x);
void RB_free_all_nodes(node* nd);
void RB_PRINT(node *T);
void RB_PRINT_NODE(node *t);
void RB_free(node* t);
node* searchstudent(node* nd, int key);
float calculate_GPA(student* st);
void GPA(node* T);
void sorting_GPA(student stu[]);
void sorting_StudentID(student stu[]);
void sorting_Credits(student stu[]);
void print_SORTED(student result[]);
int randomRange(int n1, int n2);
int create_ID(node* test);
int check_ID(node* test, int ID);
void inputNewID(RBT* test, int ID);
void isNewID(RBT* test, int ID);