#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define FULL_NAME_LEN 22
#define MAX_COURSES 10
#define NUM_OF_GROUPS 3
#define STU_PER_GROUP 6
#define MAX_NAME_LEN 10
#define MAX_FULL_NAME_LEN 30
#define MAX_STU_NUM 18

typedef struct CourseInfo
{
	int courseNum;
	int grade;
} COURSE_INFO;

struct Student
{
	char name[FULL_NAME_LEN];
	int identity;
	int nofCourses; //number of courses taken in semesterA
	COURSE_INFO course_info[MAX_COURSES];
};
typedef struct Student STUDENT;

void printWelcomeMessage();
void getInfo(STUDENT stuData[][STU_PER_GROUP], int groupNum);
void getStuInfo(STUDENT stuData[], int numOfStu);
int getStudentNames(STUDENT stuData[][STU_PER_GROUP], int rows, int cols, int courseNum, char stuNames[][MAX_FULL_NAME_LEN]);
void loisToLane(char stuNames[][MAX_FULL_NAME_LEN], int numOfStu);
void delLex(char stuNames[][MAX_FULL_NAME_LEN], int* numOfStu);
void getStuGrades(STUDENT stuData[][STU_PER_GROUP], int grades[][STU_PER_GROUP + 1], int courseNum);
void printGrades(int grades[]);
void printStuGrades(int grades[]);

void main() {
	STUDENT students[NUM_OF_GROUPS][STU_PER_GROUP];
	char stuNames[MAX_STU_NUM][MAX_FULL_NAME_LEN];
	int courseNum, numOfStu;
	int grades[NUM_OF_GROUPS][STU_PER_GROUP + 1];
	int i;

	printWelcomeMessage();
	getInfo(students, NUM_OF_GROUPS);

	printf("\nEnter a course number: ");
	scanf("%d", &courseNum);

	numOfStu = getStudentNames(students, NUM_OF_GROUPS, STU_PER_GROUP, courseNum, stuNames);
	printf("Names of students in course#%d\n", courseNum);
	for (i = 0; i < numOfStu; i++) {
		printf("%s\n", stuNames[i]);
	}
	printf("\n");

	loisToLane(stuNames, numOfStu);
	printf("Names after changing \"Lois\" to \"Lane\":\n");
	for (i = 0; i < numOfStu; i++) {
		printf("%s\n", stuNames[i]);
	}
	printf("\n");

	delLex(stuNames, &numOfStu);
	printf("Names after deleting names with \"Lex\":\n");
	for (i = 0; i < numOfStu; i++) {
		printf("%s\n", stuNames[i]);
	}
	printf("\n");

	getStuGrades(students, grades, courseNum);
	printf("Grades in course#%d:\n", courseNum);
	printf("GroupA: ");
	printGrades(grades[0]);
	printf("GroupB: ");
	printGrades(grades[1]);
	printf("GroupC: ");
	printGrades(grades[2]);

	printf("\nMaximum grades in course#%d:\n", courseNum);
	printf("GroupA: ");
	printStuGrades(grades[0]);
	printf("GroupB: ");
	printStuGrades(grades[1]);
	printf("GroupC: ");
	printStuGrades(grades[2]);
}

//Print welcome message.
void printWelcomeMessage() {
	printf("********************\n");
	printf("* Welcome Students *\n");
	printf("********************\n");
}

//Gets student's deatils for each student in each group.
void getInfo(STUDENT stuData[][STU_PER_GROUP], int groupNum) {
	char groupChar = 'A';
	for (int i = 0; i < groupNum; i++) {
		printf("Enter students data for GROUP %c:\n\n", groupChar);
		printf("________________________________\n");

		getStuInfo(stuData[i], STU_PER_GROUP);
		groupChar++;
	}
}

//Gets student's deatils
void getStuInfo(STUDENT stuData[], int numOfStu) {
	for (int i = 0; i < numOfStu; i++) {
		//FULL NAME
		char temp[MAX_NAME_LEN + 1] = "0";
		int pointer;
		printf("\nEnter student first name and last name (seperated by spaces): ");
		scanf("%s %s", stuData[i].name, temp);
		pointer = strlen(stuData[i].name);
		stuData[i].name[pointer] = 32;
		strcpy(&stuData[i].name[pointer + 1], temp);

		//ID
		printf("\nEnter student ID: ");
		scanf("%d", &stuData[i].identity);

		//NUM OF COURSES
		printf("\nEnter number of courses taken in semester A:");
		scanf("%d", &stuData[i].nofCourses);

		//COURSE NUMBER AND GRADE
		for (int j = 0; j < stuData[i].nofCourses; j++) {
			printf("Enter course number and grade:\n");
			scanf("%d", &stuData[i].course_info[j].courseNum);
			scanf("%d", &stuData[i].course_info[j].grade);
		}
	}
}

//Checks if selected course is studied by student.
int getStudentNames(STUDENT stuData[][STU_PER_GROUP], int rows, int cols, int courseNum, char stuNames[][MAX_FULL_NAME_LEN]) {
	int numOfStu = 0, NumOfCourses;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			NumOfCourses = stuData[i][j].nofCourses;
			for (int l = 0; l < NumOfCourses; l++) {
				if (stuData[i][j].course_info[l].courseNum == courseNum) {
					switch (i) {
					case 0:
						strcpy(stuNames[numOfStu], "GroupA ");
						strcpy(&stuNames[numOfStu][7], stuData[i][j].name);
						break;
					case 1:
						strcpy(stuNames[numOfStu], "GroupB ");
						strcpy(&stuNames[numOfStu][7], stuData[i][j].name);
						break;
					case 2:
						strcpy(stuNames[numOfStu], "GroupC ");
						strcpy(&stuNames[numOfStu][7], stuData[i][j].name);
						break;
					}
					numOfStu++;
				}
			}
		}
	}
	return numOfStu;
}

//Search for string 'Lois' and replace with 'Lane'.
void loisToLane(char stuNames[][MAX_FULL_NAME_LEN], int numOfStu) {
	for (int i = 0; i < numOfStu; i++) {
		int j = 0;
		while (stuNames[i][j] != '\0') {
			if (stuNames[i][j] == 'L' && stuNames[i][j + 1] == 'o' && stuNames[i][j + 2] == 'i' && stuNames[i][j + 3] == 's') {
				stuNames[i][j] = 'L';
				stuNames[i][j + 1] = 'a';
				stuNames[i][j + 2] = 'n';
				stuNames[i][j + 3] = 'e';
			}
			j++;
		}
	}
}

//Search for string 'Lex' and delete it.
void delLex(char stuNames[][MAX_FULL_NAME_LEN], int* numOfStu) {
	int temp = *numOfStu;
	for (int i = 0; i < *numOfStu; i++) {
		int j = 0;
		while (stuNames[i][j + 2] != '\0') {
			if (stuNames[i][j] == 'L' && stuNames[i][j + 1] == 'e' && stuNames[i][j + 2] == 'x') {
				for (int k = i; k < temp - 1; k++) {
					strcpy(stuNames[k], stuNames[k + 1]);
				}
				stuNames[temp - 1][2] = '\0';
				i--;
				temp--;
				break;
			}
			j++;
		}
	}
	*numOfStu = temp;
}

//Insert student's grades to a new array.
void getStuGrades(STUDENT stuData[][STU_PER_GROUP], int grades[][STU_PER_GROUP + 1], int courseNum) {
	int gradesInA = 0, gradesInB = 0, gradesInC = 0;
	grades[0][1] = 0;
	grades[1][1] = 0;
	grades[2][1] = 0;
	for (int i = 0; i < NUM_OF_GROUPS; i++) {
		for (int j = 0; j < STU_PER_GROUP; j++) {
			for (int k = 0; k < stuData[i][j].nofCourses; k++) {
				if (stuData[i][j].course_info[k].courseNum == courseNum) {
					switch (i) {
					case 0:
						grades[0][gradesInA + 1] = stuData[i][j].course_info[k].grade;
						gradesInA++;
						break;
					case 1:
						grades[1][gradesInB + 1] = stuData[i][j].course_info[k].grade;
						gradesInB++;
						break;
					case 2:
						grades[2][gradesInC + 1] = stuData[i][j].course_info[k].grade;
						gradesInC++;
						break;
					}
				}
			}
		}
	}
	*grades[0] = gradesInA;
	*grades[1] = gradesInB;
	*grades[2] = gradesInC;
}

//Print grades in default order.
void printGrades(int grades[]) {
	for (int i = 1; i <= grades[0]; i++) {
		printf("%d ", grades[i]);
	}
	printf("\n");
}

//Find and print the best and second best grades and print them.
void printStuGrades(int grades[]) {
	int GOne, GTow, temp;
	if (grades[0] == 0)
		printf("no grades found in group");
	if (grades[0] == 1)
		printf("max grade is: %d (no second max found)", grades[1]);
	if (grades[0] > 1) {
		if (grades[1] > grades[2]) {
			GOne = grades[1];
			GTow = grades[2];
		}
		else {
			GOne = grades[2];
			GTow = grades[1];
		}
		for (int i = 3; i <= grades[0]; i++) {
			if (grades[i] > GTow && grades[i] <= GOne) {
				GTow = grades[i];
			}
			if (grades[i] > GTow && grades[i] > GOne) {
				temp = GOne;
				GOne = grades[i];
				GTow = temp;
			}
		}
		printf("max grade is: %d and second max is: %d", GOne, GTow);
	}
	printf("\n");
}
