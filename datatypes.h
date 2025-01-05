#include <stdbool.h>
// Khai bao kieu du lieu
typedef struct{
	int studentId;
	char name[20];
	char phone[20];
	char email[30];
	int courses;
}Student;

typedef struct{
	int teacherId;
	char classroomId[10];
	char name[30];
	char email[30];
	char phone[20]; 	
}Teacher;
