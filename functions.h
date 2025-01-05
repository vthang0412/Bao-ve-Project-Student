#include "datatypes.h"
// Khai bao nguyen mau ham
//Menu admin 
void displayMenu(void);
void menuAdmin(void);
void loginAdmin();
void removeSpaces(char *str);
void clearInputBuffer();

//Menu sinh vien 
void menuStudents(void);

//Chuc nang cua Admin ve sinh vien 
void addStudent(Student students[], int *length);
void printfStudent(Student students[], int *length);
void searchStudentByName(Student students[], int *length);
void editStudent(Student students[], int *length);
void deleteStudent(Student students[], int *length);
void sortStudentsByName(Student students[], int *length);
void saveToFile(Student students[],int length);
void loadFromFile(Student students[],int *length);

void askToGoBack();
void end();

//Menu giao vien 
void menuTeacher(void);

//Chuc nang cua Admin ve giao vien 
void menuTeacher(void);
void addTeacher(Teacher teacher[], int *length);
void printfTeacher(Teacher teachers[], int *length);
void editTeacher(Teacher teachers[], int *length);
void deleteTeacher(Teacher teachers[], int *length);
void searchTeacherByName(Teacher teachers[], int *length);
void saveTeacherToFile(Teacher teachers[],int length);
void loadTeacherFromFile(Teacher teachers[],int *length);

//Kiem tra co bi trung lap khong 
int isDuplicateID(Student students[], int length, int id);
int isDuplicateEmailStudent(Student students[], int length, const char *email);
int isDuplicateEmailTeacher(Teacher teachers[], int length, const char *email);
int isDuplicatePhoneStudent(Student students[], int length, const char *phone); 
int isDuplicatePhoneTeacher(Teacher teachers[], int length, const char *phone);
	
