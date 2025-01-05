#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main(int argc, char *argv[]) {
    int choiceStudent, choiceMenu, choiceAdmin, choiceTeacher;
    int length = 0; 
    int isAdminLoggedIn = 0; 
    Student students[100];
    Teacher teachers[100];
    do {
        system("cls");
        displayMenu(); 
        scanf("%d", &choiceMenu);
        switch (choiceMenu) {
            case 1:
                if (!isAdminLoggedIn) {
                    system("cls");
                    clearInputBuffer();
                    loginAdmin(); 
                    isAdminLoggedIn = 1;
                }
                do {
                    system("cls");
                    menuAdmin();
                    scanf("%d", &choiceAdmin);
                    switch (choiceAdmin) {
                        case 1: 
                            loadFromFile(students, &length); 
                            do {
                                system("cls");
                                menuStudents();     
                                scanf("%d", &choiceStudent);
                                switch (choiceStudent) {
                                    case 1:
                                    	system("cls");
                                        addStudent(students, &length);
                                        saveToFile(students, length); 
                                        askToGoBack();
                                        break;
                                    case 2:
                                    	system("cls");
                                        printfStudent(students, &length);
                                        askToGoBack();
                                        break;
                                    case 3:
                                    	system("cls");
                                        searchStudentByName(students, &length);
                                        askToGoBack();
                                        break;
                                    case 4:
                                    	system("cls");
                                        editStudent(students, &length);
                                        saveToFile(students, length);
                                        askToGoBack();
                                        break;
                                    case 5:
                                    	system("cls");
                                        deleteStudent(students, &length);
                                        saveToFile(students, length); 
                                        askToGoBack();
                                        break;
                                    case 6:
                                    	system("cls");
                                        sortStudentsByName(students, &length);
                                        askToGoBack();
                                        break;
                                    case 0:
                                        break;
                                    default:
                                        printf("Lua chon khong hop le. Vui long chon lai.\n");
                                }
                            } while (choiceStudent != 0);
                            break;
                        case 3:
                            loadTeacherFromFile(teachers, &length);
                            do {
                                system("cls");
                                menuTeacher(); 
                                scanf("%d", &choiceTeacher);
                                switch (choiceTeacher) {
                                    case 1:
                                    	system("cls");
                                        addTeacher(teachers, &length);
                                        saveTeacherToFile(teachers, length);
                                        askToGoBack();
                                        break;
                                    case 2:
                                    	system("cls");
                                        printfTeacher(teachers, &length);
                                        askToGoBack();
                                        break;
                                    case 3:
                                    	system("cls");
                                    	searchTeacherByName(teachers,&length);
                                    	askToGoBack();
                                    	break;
                                    case 4:
                                    	system("cls");
                                        editTeacher(teachers, &length);
                                        saveTeacherToFile(teachers, length);
                                        askToGoBack();
                                        break;
                                    case 5:
                                    	system("cls");
                                        deleteTeacher(teachers, &length);
                                        saveTeacherToFile(teachers, length);
                                        askToGoBack();
                                        break;
                                    case 0:                                                                                                   
                                        break;
                                    default:
                                        printf("Lua chon khong hop le. Vui long chon lai.\n");
                                }
                            } while (choiceTeacher != 0);
                            break;
                        case 0:
                            isAdminLoggedIn = 0;
                            break;
                        default:
                            printf("Lua chon khong hop le. Vui long chon lai.\n");
                    }
                } while (choiceAdmin != 0);
                break;
            case 0:
                end();
                break;
            default:
                printf("Lua chon khong hop le. Vui long chon lai.\n");
        }
    } while (choiceMenu != 0);

    return 0;
}
