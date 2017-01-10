#include "rbt.h"
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_COURSE 25

char COURSE[][100] = { "자료구조", "알고리즘", "논리회로", "컴퓨터네트워크", "오토마타", "컴파일러", "확률및통계","일반생물학","일반물리학","일반화학","성균논어",
"심리학입문","영어쓰기","영어발표","컴퓨터그래픽스","캡스톤설계","정보이론","컴퓨터구조","시스템프로그래밍","컴퓨터공학세미나","JAVA","Python","데이터베이스","C++","인공지능" };
float GRADE[] = { 0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5 };//random courses and grades to choose randomly

int logB(double x, double base) {//function for calculating RB tree height
	return log(x) / log(base);
}
void inputNewID(RBT* test, int ID) {//function for input new ID in RB tree
	student* tmp = NULL;
	semester* tmp2 = NULL;
	semester* ltmp2 = NULL;
	course* tmp3 = NULL;
	course* ltmp3 = NULL;
	char data[100];
	int scount = 1;
	int ccount;
	int credit;
	float grade;
	tmp = getStudent();
	tmp->id = ID;
	tmp->name = (char*)malloc(sizeof(char) * 100);
	getchar();
	printf("Input Name:");
	fgets(data, sizeof(data), stdin);
	data[strlen(data) - 1] = '\0';
	fflush(stdin);
	strcpy(tmp->name, data);
	while (1) {
		if (scount == 1) {
			tmp2 = getSemester();
			ltmp2 = tmp2;
		}
		else {
			ltmp2->next = getSemester();
			ltmp2 = ltmp2->next;
		}
		printf("%d's semester\n", scount);
		ccount = 1;
		while (ccount<8) {
			if (ccount == 1) {
				tmp3 = getCourse();
				ltmp3 = tmp3;
			}
			else {
				ltmp3->next = getCourse();
				ltmp3 = ltmp3->next;
			}
			printf("Input course:");
			fflush(stdin);
			fgets(data, "%s", stdin);
			data[strlen(data) - 1] = '\0';
			ltmp3->name = (char*)malloc(sizeof(char) * 100);
			strcpy(ltmp3->name, data);
			fflush(stdin);
			printf("input credit:");
			scanf("%d", &credit);
			ltmp3->Credit = credit;
			fflush(stdin);
			printf("input grade(ex. 4.5):");
			scanf("%f", &grade);
			ltmp3->Grade = grade;
			printf("more courses in this semester?(y/n)\n");
			fflush(stdin);
			scanf("%s", data);
			getchar();
			if (strcmp("y", data)) {
				break;
			}
			else if (ccount == 7) {// if course reaches 7, send message and terminate
				printf("maximum course number is 7 in one semester.\n");
			}
			ccount++;
		}
		ltmp2->courses = tmp3;
		ltmp2->cnum = ccount;
		printf("input next semesters?(y/n)\n");
		scanf("%s", data);
		getchar();
		if (strcmp("y", data)) {
			break;
		}
		scount++;
	}
	tmp->semesters = tmp2;
	RB_insert(test, getNode(tmp));
	printf("New student data created!\n\n");
}

void addinID(node* t) {// function for adding courses and grades in existing student
	int response = 0;
	semester * tmp = NULL;
	course * ltmp2 = NULL;
	course * tmp2;
	int scount;
	int ccount;
	int credit;
	float grade;
	char data[100];
	while (response != 1 && response != 2) {
		printf("1. Add course & grade for existing semester   2. Add new semester : ");//choosing between 2 options
		scanf("%d", &response);
		getchar();
		switch (response)
		{
		case 1://case1
			scount = 0;
			tmp = t->key->semesters;
			while (tmp != NULL) {
				tmp = tmp->next;
				scount++;
			}
			printf("Now %d semesters in data.\n", scount);
			printf("In Which semester do you want to add?\n");
			scanf("%d", &response);
			getchar();
			if (scount < response || response < 1)
			{
				printf("There is no %d' semester\n", response);
				break;
			}
			for (int i = 0; i < response; i++) {
				if (i == 0)
					tmp = t->key->semesters;
				else tmp = tmp->next;
			}
			ltmp2 = tmp->courses;
			while (ltmp2->next != NULL)
				ltmp2 = ltmp2->next;
			while (tmp->cnum < 7) {
				tmp2 = getCourse();
				ltmp2->next = tmp2;
				ltmp2 = tmp2;
				printf("Input course:");
				fflush(stdin);
				fgets(data, "%s", stdin);
				data[strlen(data) - 1] = '\0';
				tmp2->name = (char*)malloc(sizeof(char) * 100);
				strcpy(tmp2->name, data);
				fflush(stdin);
				printf("Input credit:");
				scanf("%d", &credit);
				tmp2->Credit = credit;
				fflush(stdin);
				printf("Input grade(ex. 4.5):");
				scanf("%f", &grade);
				tmp2->Grade = grade;
				tmp->cnum++;
				printf("More courses to add?(y/n)\n");
				fflush(stdin);
				scanf("%s", data);
				getchar();
				if (strcmp("y", data)) {
					printf("Course and Grades are newly added!\n");
					break;
				}
				else if (tmp->cnum == 7) {
					printf("maximum course number is 7 in one semester.\n");
				}
			}
			break;
		case 2://case2
			scount = 2;
			tmp = t->key->semesters;
			while (tmp->next != NULL) {
				tmp = tmp->next;
				scount++;
			}
			printf("%d' semester\n", scount);
			tmp->next = getSemester();
			tmp = tmp->next;
			ccount = 0;
			while (ccount<7) {
				if (ccount == 0) {
					tmp2 = getCourse();
					ltmp2 = tmp2;
				}
				else {
					ltmp2->next = getCourse();
					ltmp2 = ltmp2->next;
				}
				printf("Input course:");
				fflush(stdin);
				fgets(data, "%s", stdin);
				data[strlen(data) - 1] = '\0';
				ltmp2->name = (char*)malloc(sizeof(char) * 100);
				strcpy(ltmp2->name, data);
				fflush(stdin);
				printf("Input credit:");
				scanf("%d", &credit);
				ltmp2->Credit = credit;
				fflush(stdin);
				printf("Input grade(ex. 4.5):");
				scanf("%f", &grade);
				ltmp2->Grade = grade;
				printf("More courses in this semester?(y/n)\n");
				fflush(stdin);
				scanf("%s", data);
				getchar();
				if (strcmp("y", data)) {
					break;
				}
				else if (ccount == 6) {
					printf("Maximum course number is 7 in one semester.\n");
				}
				ccount++;
			}
			tmp->courses = tmp2;
			tmp->cnum = ccount;
			break;
		default:
			break;
		}
	}
}

void isNewID(RBT* test, int ID) {//check if ID is new or not
	char response[5];
	node* tstudent = isKeyExist(test->root, ID);
	if (tstudent == NULL) {//not exists
		printf("Student ID %d is not in data.\nCreate new student data? ( y / n )\n", ID);
		scanf("%s", response);
		if (!strcmp("y", response)) {
			inputNewID(test, ID);
			GPA(isKeyExist(test->root, ID));//GPA calculate to output
		}
		else
			return;
	}
	else {//exists
		RB_PRINT_NODE(tstudent);
	}
}
student stu_arr[300];
int cnt_stu = 0;

float calculate_GPA(student* st) // Calculate GPA, Credits earned and puts data in 'student' structure
{
	float sum = 0, sum_score = 0;
	semester* sem_tmp = NULL;
	course* cour_tmp = NULL;

	sem_tmp = st->semesters;
	while (sem_tmp != NULL) {
		cour_tmp = sem_tmp->courses;

		while (cour_tmp != NULL) {
			sum += cour_tmp->Credit;
			sum_score += (cour_tmp->Credit)*(cour_tmp->Grade);
			cour_tmp = cour_tmp->next;
		}
		sem_tmp = sem_tmp->next;
	}
	st->credit = sum;
	return sum_score / sum;
}

void GPA(node* T) {//saving GPA informations

	float gpa;
	if (T->key == NULL)
		return;
	GPA(T->left);
	gpa = calculate_GPA(T->key);
	T->key->GPA = gpa;

	stu_arr[cnt_stu].id = T->key->id;
	stu_arr[cnt_stu].GPA = gpa;
	stu_arr[cnt_stu].credit = T->key->credit;
	cnt_stu++;

	GPA(T->right);
}

void sorting_GPA(student stu[])//sorting in GPA order based on bubble sort
{
	int i, j;
	int tmp_id, tmp_credit;
	float tmp_GPA;

	for (i = 0; i < cnt_stu; i++) {
		for (j = i + 1; j < cnt_stu; j++) {
			if (stu[i].GPA < stu[j].GPA) {
				tmp_id = stu[i].id;
				stu[i].id = stu[j].id;
				stu[j].id = tmp_id;

				// TODO : SWAP

				tmp_credit = stu[i].credit;
				stu[i].credit = stu[j].credit;
				stu[j].credit = tmp_credit;

				tmp_GPA = stu[i].GPA;
				stu[i].GPA = stu[j].GPA;
				stu[j].GPA = tmp_GPA;
			}
		}
	}

	print_SORTED(stu_arr);
}

void sorting_StudentID(student stu[])//sorting in ID order
{
	int i, j;
	int tmp_id, tmp_credit;
	float tmp_GPA;

	for (i = 0; i < cnt_stu; i++) {
		for (j = i + 1; j < cnt_stu; j++) {
			if (stu[i].id > stu[j].id) {
				tmp_id = stu[i].id;
				stu[i].id = stu[j].id;
				stu[j].id = tmp_id;

				// TODO : SWAP

				tmp_credit = stu[i].credit;
				stu[i].credit = stu[j].credit;
				stu[j].credit = tmp_credit;

				tmp_GPA = stu[i].GPA;
				stu[i].GPA = stu[j].GPA;
				stu[j].GPA = tmp_GPA;
			}
		}
	}

	print_SORTED(stu_arr);
}

void sorting_Credits(student stu[])// sorting in credit order
{
	int i, j;
	int tmp_id, tmp_credit;
	float tmp_GPA;

	for (i = 0; i < cnt_stu; i++) {
		for (j = i + 1; j < cnt_stu; j++) {
			if (stu[i].credit < stu[j].credit) {
				tmp_id = stu[i].id;
				stu[i].id = stu[j].id;
				stu[j].id = tmp_id;

				// TODO : SWAP

				tmp_credit = stu[i].credit;
				stu[i].credit = stu[j].credit;
				stu[j].credit = tmp_credit;

				tmp_GPA = stu[i].GPA;
				stu[i].GPA = stu[j].GPA;
				stu[j].GPA = tmp_GPA;
			}
		}
	}

	print_SORTED(stu_arr);
}
void print_SORTED(student result[])//printing sorted result
{
	int i;
	printf("Student ID   GPA   CreditsEarned\n");
	printf("---------------------------------\n");
	for (i = 0; i < cnt_stu; i++) {
		printf("%d   %.2f   %d\n", result[i].id, result[i].GPA, result[i].credit);
	}
}
int randomRange(int n1, int n2) { //making random range of all values needed
	return (int)(rand() % (n2 - n1 + 1)) + n1;
}
int create_ID(node* test)//creating ID based on random number
{
	int ID;
	int check_re = 1;

	while (check_re == 1) {
		ID = randomRange(2013, 2016) * 1000000 + randomRange(000, 999) * 1000 + randomRange(000, 999);
		check_re = check_ID(test, ID);
	}
	return ID;
}

int check_ID(node* test, int ID)//checking duplicates of ID
{
	node* result = isKeyExist(test, ID);
	if (result == NULL)
		return -1; // not exist
	else {
		return 1; // exist
	}
}

int check(node* test, int id)//check weather ID exist in RB tree or note
{
	node* temp = isKeyExist(test, id);
	if (temp == NULL)
		return NULL;
	else {
		return id;
	}
}

int count(node *tree)//counting all nodes in RB tree
{
	int c = 1;             //Node itself should be counted
	if (tree == NULL)
		return 0;
	else
	{
		c += count(tree->left);
		c += count(tree->right);
		return c;
	}
}

unsigned int getLeafCount(node* node)//counting Leaf nodes in RB tree
{
	if (node == NULL)
		return 0;
	if (node->left == NULL && node->right == NULL)
		return 1;
	else
		return getLeafCount(node->left) +
		getLeafCount(node->right);
}

//Main function
int main(void)
{
	RBT test;
	student* tmp = NULL;
	semester* tmp2 = NULL;
	semester* ltmp2 = NULL;
	course* tmp3 = NULL;
	course* ltmp3 = NULL;
	char data1[100];
	FILE *fp;
	fp = fopen("FakeName.txt", "r");// load 200 fake names from file 
	srand(time(NULL));
	int i = 0;
	Init_RBT(&test);//initialize
	while (fgets(&data1, 100, fp) != NULL) {//give values to each students allocating nodes(grade, course, semseter, credit)
		tmp = getStudent();
		tmp->id = create_ID(test.root);
		tmp->name = (char*)malloc(sizeof(char) * 100);
		strcpy(tmp->name, data1);
		int j = (2016 - (tmp->id / 1000000)) * 2 + randomRange(1, 2);
		for (int k = 0; k < j; k++) {
			if (k == 0) {
				tmp2 = getSemester();
				ltmp2 = tmp2;
			}
			else {
				ltmp2->next = getSemester();
				ltmp2 = ltmp2->next;
			}
			int ncourse = randomRange(3, 7);
			ltmp2->cnum = ncourse;
			int isc[MAX_COURSE] = { 0 };
			for (int l = 0; l < ncourse; l++) {
				if (l == 0) {
					tmp3 = getCourse();
					ltmp3 = tmp3;
				}
				else {
					ltmp3->next = getCourse();
					ltmp3 = ltmp3->next;
				}
				ltmp3->name = (char*)malloc(sizeof(char) * 100);
				ltmp3->Credit = 3;
				int idx = rand() % 10;
				ltmp3->Grade = GRADE[idx];
				int rcnum = randomRange(0, MAX_COURSE - 1);
				while (isc[rcnum]) {
					rcnum = randomRange(0, MAX_COURSE - 1);
				}
				isc[rcnum] = 1;
				strcpy(ltmp3->name, COURSE[rcnum]);
			}
			ltmp2->courses = tmp3;
		}
		tmp->semesters = tmp2;
		RB_insert(&test, getNode(tmp));
	}
	
	GPA(test.root, stu_arr);
	// GAP calculation and input
	// UI part of main function
	printf("%80s", "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
	printf("%81s", "|                                        |\n");
	printf("%81s", "| Welcome to Student Information System  |\n");
	printf("%81s", "|                                        |\n");
	printf("%80s", "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
	printf("\n");
	printf("%70s", "Please select a menu\n\n");
	while (1) {
		while (1) {
			int choice = 0;
			int num;
			printf("%113s", "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
			printf("%114s", "|   1. Find student  |  2. Add new / Grade student  |  3. Delete student  |  4. Rank students  |  5. Quit  |\n");
			printf("%113s", "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
			printf("%99s", "- Extra functions  7. List all   8. Clear window   9. Check RBT structure -\n\n");
			scanf("%d", &choice);

			if (choice < 1 || choice > 5 && choice != 9 && choice !=7)
			{
				printf("\nYou have entered wrong number. Please enter the correct number\n");
			}
			printf("\n");

			switch (choice) {
			case 1:
				while (1) {

					int id = 0;
					printf("\nPlease enter the valid Student ID : ");
					scanf("%d", &id);
					printf("\n");
					if (check(test.root, id) == NULL)
					{
						printf("No matching student. 1. Keep Searching   2. Return to Menu : ");
						int search = 0;
						scanf("%d", &search);
						printf("\n");
						if (search == 1) {
							continue;
						}
						else {
							printf("\n");
							break;
						}
					}
					else {
						RB_PRINT_NODE(isKeyExist(test.root, id));
						printf("\n\n1. Keep Searching   2. Return to Menu : ");
						int search = 0;
						scanf("%d", &search);
						printf("\n");
						if (search == 1) {
							continue;
						}
						else {
							printf("\n");
							break;
						}
					}
				}
				break;
			case 2:
				while (1) {
					int id = 0;
					printf("\nPlease enter the Student ID : ");
					scanf("%d", &id);
					printf("\n");
					if (check(test.root, id) == NULL) {
						isNewID(&test, id);
						printf("RB Tree Structure Info\n");
						printf("Number of Nodes : %d\n", count(test.root));
						printf("Number of Leaves : %d\n", getLeafCount(test.root));
						printf("Height of Tree : %d\n\n", logB(count(test.root), 2));
						break;
					}
					else {
						addinID(isKeyExist(test.root, id));
						GPA(isKeyExist(test.root, id));
						break;
					}
				}
				break;
			case 3:
				while (1) {
					int id = 0;
					printf("\nPlease enter the valid Student ID : ");
					scanf("%d", &id);
					printf("\n");
					if (check(test.root, id) == NULL)
					{
						printf("\nNo matching student. 1. Try again   2. Return to Menu : ");
						int select = 0;
						scanf("%d", &select);
						printf("\n");
						if (select == 1)
							continue;
						else
							break;
					}
					else {
						RB_PRINT_NODE(isKeyExist(test.root, id));
						printf("\nDeleting Current Student information?  1. Yes   2. No : ");
						int yn = 0;
						scanf("%d", &yn);
						printf("\n");
						if (yn == 1) {
							RB_delete(&test, isKeyExist(test.root, id));
							printf("Deletion Complete!\n");
							printf("RB Tree Structure Info\n");
							printf("Number of Nodes : %d\n", count(test.root));
							printf("Number of Leaves : %d\n", getLeafCount(test.root));
							printf("Height of Tree : %d\n\n", logB(count(test.root), 2));
							continue;
						}
						else
							break;
					}
				}
				break;
			case 4:
				while (1) {
					int rank = 0;
					int ranking = 0;
					printf("Choose Input Rank Factor\n1. ID\n2. GPA\n3. Credit hours earned\n4. Return to Menu\n");
					scanf("%d", &rank);
					printf("\n");
					switch (rank) {
					case 1:
						sorting_StudentID(stu_arr);
						printf("\n1. Keep Ranking   2. Return to Menu : ");
						scanf("%d", &ranking);
						printf("\n");
						if (ranking == 1)
							continue;
						else
							break;
					case 2:
						sorting_GPA(stu_arr);
						printf("\n1. Keep Ranking   2. Return to Menu : ");
						scanf("%d", &ranking);
						printf("\n");
						if (ranking == 1)
							continue;
						else
							break;
					case 3:
						sorting_Credits(stu_arr);
						printf("\n1. Keep Ranking   2. Return to Menu : ");
						scanf("%d", &ranking);
						printf("\n");
						if (ranking == 1)
							continue;
						else
							break;
					case 4:
						break;
					}
					break;
				}
				break;
			case 5:
				exit(1);
				break;
			case 7:
				RB_PRINT(test.root);
				// printing all the information of students
				break;
			case 8:
				system("cls");
				break;
			case 9:
				printf("RB Tree Structure Info\n");
				printf("Number of Nodes : %d\n", count(test.root));
				printf("Number of Leaves : %d\n", getLeafCount(test.root));
				printf("Height of Tree : %d\n\n", logB(count(test.root), 2));
				break;
			}
			break;
		}
	}
	fclose(fp);//closing file
	return 0;
}