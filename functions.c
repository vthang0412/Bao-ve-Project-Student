#include <stdio.h>
#include <string.h>
#include "functions.h"
#include <stdlib.h>
// Logic ham

// Menu Ten He Thong
void displayMenu(void){
	printf("\n***Student Management System Using C***\n");
	printf("CHOOSE YOUR ROLE\n");
	printf("===================\n");
	printf("[1]: Admin.\n");
	printf("[2]: Student.\n");
	printf("[3]: Teacher.\n");
	printf("[0]: Exit the Program.\n");
	printf("===================\n");
	printf("Enter The Choice: ");
}
// Menu Admin
void menuAdmin(void){
	printf("\n***Student Management System Using C***\n");
	printf("			Menu\n");
	printf("==============================\n");
	printf("[1]: Students management.\n");
	printf("[2]: ClassRooms managemment.(Chua duoc tao)\n");
	printf("[3]: Teacher management.\n");
	printf("[4]: User Guideline.(Chua duoc tao)\n");
	printf("[5]: About Us.(Chua duoc tao)\n");
	printf("[0]: Exit the Program. \n");
	printf("Enter The Choice: ");
}
// Menu Sinh vien
void menuStudents(void){
	printf("\n***Student Management System Using C***\n");
	printf("		Student Menu\n");
	printf("==============================\n");
	printf("[1]: Add a new students.\n");
	printf("[2]: Show all students.\n");
	printf("[3]: Search a students.\n");
	printf("[4]: Edit a students.\n");
	printf("[5]: Delete a student.\n");
	printf("[6]: Sort Students By Name student.\n") ;
	printf("[0]: Exit the Program.\n");
	printf("Enter The Choice: ");
}
// Menu Giao vien
void menuTeacher(void){
	printf("\n***Student Management System Using C***\n");
	printf("		Teacher Menu\n");
	printf("==============================\n");
	printf("[1]: Add a new teacher.\n");
	printf("[2]: Show all teacher.\n");
	printf("[3]: Search a teacher.\n");
	printf("[4]: Edit a teacher.\n");
	printf("[5]: Delete a teacher.\n");
	printf("[0]: Exit the Program.\n");
	printf("Enter The Choice: ");
}
//Lam sach bo nho dem
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
// Bo khoang trang khi dang nhap 
void removeSpaces(char *str) {
    int i = 0, j = 0;
    while (str[i]) {
        if (str[i] != ' ') {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
}
// Login Admin
void loginAdmin() {
    char email[50];
    const char correctEmail[] = "vthang041206@gmail.com";  
    const char correctPassword[] = "041206";  
    char password[50];
    while (1) {
        printf("**** STUDENT MANAGEMENT ****\n");
        printf("\n\t    LOGIN \n");
        printf("Nhap Email: ");
        if (fgets(email, sizeof(email), stdin) == NULL) {
            printf("Loi khi nhap Email.\n");
            continue;
        }
        email[strcspn(email, "\n")] = '\0'; 
        removeSpaces(email);
        printf("Nhap Mat Khau: ");
        if (fgets(password, sizeof(password), stdin) == NULL) {
            printf("Loi khi nhap Mat Khau.\n");
            continue;
        }
        password[strcspn(password, "\n")] = '\0';
        removeSpaces(password);
        
        if (strcmp(email, correctEmail) == 0 && strcmp(password, correctPassword) == 0) {
            printf("Dang nhap thanh cong.\n");
            break;
        } else {
            printf("Email hoac mat khau sai, vui long nhap lai.\n");
        }
    }
}

// Ham them sinh vien
void addStudent(Student students[], int *length) {
    int quantity;
    int i, j;
    printf("\t **** Add A New Student ****\n");
    printf("Nhap so luong sinh vien: ");
    scanf("%d", &quantity);
    getchar();
    for (i = 0; i < quantity; i++) {
        printf("Nhap thong tin cho sinh vien %d:\n", i + 1);
        int id;
        do {
            printf("Nhap ID sinh vien: ");
            scanf("%d", &id);
            getchar();
            if (id <= 0) {
                printf("ID phai la so duong. Vui long nhap lai.\n");
            } else if (isDuplicateID(students, *length, id)) {
                printf("ID %d da ton tai. Vui long nhap ID khac.\n", id);
            } else {
                break; 
            }
        } while (1);
        students[*length].studentId = id;
        char email[100];
        do {
            printf("Nhap email sinh vien (@gmail.com): ");
            fgets(email, sizeof(email), stdin);
            email[strcspn(email, "\n")] = '\0';
            const char *gmailSuffix = "@gmail.com";
            int len = strlen(email);
            int suffixLen = strlen(gmailSuffix);
            if (len < suffixLen || strcmp(email + len - suffixLen, gmailSuffix) != 0) {
                printf("Email phai co dang '@gmail.com'. Vui long nhap lai.\n");
            } else if (isDuplicateEmailStudent(students, *length, email)) {
                printf("Email %s da ton tai. Vui long nhap email khac.\n", email);
            } else {
                break; 
            }
        } while (1);
        strcpy(students[*length].email, email);
        char phone[20];
        do {
            printf("Nhap so dien thoai sinh vien: ");
            fgets(phone, sizeof(phone), stdin);
            phone[strcspn(phone, "\n")] = '\0';
            int len = strlen(phone);
            int valid = 1;
            if (len < 10 || len > 11) {
                printf("So dien thoai phai co tu 10 den 11 chu so. Vui long nhap lai.\n");
                valid = 0;
            }
            for (j = 0; j < len; j++) {
                if (!isdigit(phone[j])) {
                    printf("So dien thoai chi duoc chua chu so. Vui long nhap lai.\n");
                    valid = 0;
                    break;
                }
            }
            if (valid && isDuplicatePhoneStudent(students, *length, phone)) {
                printf("So dien thoai %s da ton tai. Vui long nhap so dien thoai khac.\n", phone);
                valid = 0;
            }
            if (valid) {
                break; 
            }
        } while (1);
        strcpy(students[*length].phone, phone);
        
        printf("Nhap khoa hoc cho sinh vien: ");
        scanf("%d", &students[*length].courses);
        getchar();

        (*length)++; 
        printf("Da them sinh vien thanh cong!\n");
    }
}
// Ham sua sinh vien
void editStudent(Student students[], int *length) {
    if (*length == 0) {
        printf("Danh sach sinh vien hien dang trong. Khong co gi de sua.\n");
        return;
    }
    int id;
    printf("\t **** Edit A Student ****\n");
    printf("Nhap ID sinh vien muon sua: ");
    scanf("%d", &id);
    getchar();    
    int found = -1;
    int i; 
    for (i = 0; i < *length; i++) {
        if (students[i].studentId == id) {
            found = i;
            break;
        }
    }
    if (found == -1) {
        printf("Khong tim thay sinh vien voi ID: %d\n", id);
        return;
    }
    printf("\nThong tin hien tai cua sinh vien:\n");
    printf("ID: %d\n", students[found].studentId);
    printf("Ho Va Ten: %s\n", students[found].name);
    printf("So Dien Thoai: %s\n", students[found].phone);
    printf("Email: %s\n", students[found].email);

    char input[100];
    int valid;
    int isChanged = 0;
    do {
        printf("Ho Va Ten (Nhap so 0 de bo qua): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        if (strcmp(input, "0") == 0) break; 
        valid = 1;
        for (i = 0; input[i]; i++) {
            if (!isalpha(input[i]) && !isspace(input[i])) {
                valid = 0;
                printf("Ten khong hop le. Vui long nhap lai (chi chu va khoang trang).\n");
                break;
            }
        }
        if (valid && strcmp(students[found].name, input) != 0) {
            strcpy(students[found].name, input);
            isChanged = 1;
        }
    } while (!valid);
    do {
        printf("So Dien Thoai (Nhap so 0 de bo qua): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        if (strcmp(input, "0") == 0) break; 
        valid = 1;
        int len = strlen(input);
        if (len < 10 || len > 11) {
            valid = 0;
            printf("So dien thoai khong hop le. Vui long nhap lai (do dai 10-11 ky tu).\n");
        } else {
            for (i = 0; i < len; i++) {
                if (!isdigit(input[i])) {
                    valid = 0;
                    printf("So dien thoai chi duoc chua so. Vui long nhap lai.\n");
                    break;
                }
            }
        }
        if (valid) {
            for (i = 0; i < *length; i++) {
                if (i != found && strcmp(students[i].phone, input) == 0) {
                    valid = 0;
                    printf("So dien thoai %s da ton tai. Vui long nhap so dien thoai khac.\n", input);
                    break;
                }
            }
        }
        if (valid && strcmp(students[found].phone, input) != 0) {
            strcpy(students[found].phone, input);
            isChanged = 1;
        }
    } while (!valid);
	do {
	    printf("Nhap Email (Nhap so 0 de bo qua): ");
	    fgets(input, sizeof(input), stdin);
	    input[strcspn(input, "\n")] = '\0'; 
	    if (strcmp(input, "0") == 0) break;
	    const char *gmailSuffix = "@gmail.com";
	    int len = strlen(input);
	    int suffixLen = strlen(gmailSuffix); 
	    if (len < suffixLen || strcmp(input + len - suffixLen, gmailSuffix) != 0) {
	        printf("Email phai co dang '@gmail.com'. Vui long nhap lai.\n");
	    } 
	    else {
	        break;
	    }
	} while (1);
	if (strcmp(input, "0") != 0) {
	    strcpy(students[*length].email, input);
	}
}
// Ham in sinh vien
void printfStudent(Student students[], int *length) {
    if (*length == 0) {
        printf("\nKhong co sinh vien trong danh sach.\n");
        return;
    }
    printf("\t **** Show All Students ****\n") ;
    printf("\t----------***All Students***----------\n");
    printf("|==========|====================|========================|====================|============|\n");
    printf("|    ID    |        Name        |          Email         |        Phone       |  NO.Course |\n");
    printf("|==========|====================|========================|====================|============|\n");
	int i;
    for (i = 0; i < *length; i++) {
        printf("| %-8d | %-18s | %-22s | %-18s | %-10d |\n", 
               students[i].studentId, 
               students[i].name, 
               students[i].email, 
               students[i].phone, 
               students[i].courses);
        printf("|==========|====================|========================|====================|============|\n");
    }
    printf("\t \t---------------------\n");
}
// Ham xoa sinh vien
void deleteStudent(Student students[], int *length) {
    int id, i, found = -1;
// Nhap id sinh vien muon xoa
    printf("\t **** Delete A Student ****\n") ;
    printf("Nhap ID sinh vien muon xoa: ");
    scanf("%d", &id);
// Tim sinh vien co ID trong danh sach
    for (i = 0; i < *length; i++) {
        if (students[i].studentId == id) {
            found = i;
            break;
        }
    }
// Neu khong tim thay sinh vien
    if (found == -1) {
        printf("Khong tim thay sinh vien voi ID: %d\n", id);
        return;
    }
// Hien thi thong tin sinh vien can xoa
    printf("\nThong tin sinh vien can xoa:\n");
    printf("ID: %d\n", students[found].studentId);
    printf("Ho Va Ten: %s\n", students[found].name);
    printf("Email: %s\n", students[found].email);
    printf("So Dien Thoai: %s\n", students[found].phone);
    printf("So Khoa Hoc: %d\n", students[found].courses);
// Yeu cau xac nhan xoa
    char confirm;
    printf("\nBan co chac chan muon xoa sinh vien nay (y/n)? ");
    getchar();  
    scanf("%c", &confirm);
    if (confirm == 'y' || confirm == 'y') {
// Xoa sinh vien
        for (i = found; i < *length - 1; i++) {
            students[i] = students[i + 1]; 
        }
        (*length)--; 
        printf("Sinh vien da duoc xoa thanh cong.\n");
    } else {
        printf("Huy thao tac xoa sinh vien.\n");
    }
}
// Ham Sap xep sinh vien 
void sortStudentsByName(Student students[], int *length) {
    if (*length == 0) {
        printf("Danh sach sinh vien trong. Khong co gi de sap xep.\n");
        return;
    }
    int choiceSort;
    printf("\t **** Sort Students By Name ****\n") ;
    printf("Chon thu tu sap xep danh sach:\n");
    printf("1. Tang dan theo ten\n");
    printf("2. Giam dan theo ten\n");
    printf("Nhap lua chon (1 hoac 2): ");
    scanf("%d", &choiceSort);
    getchar(); 
    if (choiceSort!= 1 && choiceSort != 2) {
        printf("Lua chon khong hop le. Quay lai menu chinh.\n");
        return;
    }
// Sap xep 
    int i,j;
    for (i = 0; i < *length - 1; i++) {
        for (j = i + 1; j < *length; j++) {
            int compare = strcmp(students[i].name, students[j].name);
            if ((choiceSort == 1 && compare > 0) || (choiceSort == 2 && compare < 0)){
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
    printf("Danh sach ten sinh vien da duoc sap xep ");
	if (choiceSort == 1) {
	    printf("Tang dan.\n");
	} else {
	    printf("Giam dan.\n");
	}
    printf("\t----------***All Students***----------\n");
    printf("|==========|====================|========================|====================|============|\n");
    printf("|    ID    |        Name        |          Email         |        Phone       |  NO.Course |\n");
    printf("|==========|====================|========================|====================|============|\n");
    for (i = 0; i < *length; i++) {
        printf("| %-8d | %-18s | %-22s | %-18s | %-10d |\n", 
               students[i].studentId, 
               students[i].name, 
               students[i].email, 
               students[i].phone, 
               students[i].courses);
        printf("|==========|====================|========================|====================|============|\n");
    }
    printf("\t \t---------------------\n");
}
// Ham tim kiem sinh vien
void searchStudentByName(Student students[], int *length) {
    if (*length == 0) {
        printf("Danh sach sinh vien hien dang trong. Khong co gi de tim kiem.\n");
        return;
    }
    char searchName[50];
    clearInputBuffer();
    printf("\t **** Search A Student ****\n");
    printf("Nhap ten sinh vien muon tim kiem: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0'; 
    
    if (strlen(searchName) == 0) {
        printf("Ten sinh vien khong duoc de trong. Vui long nhap lai.\n");
        return searchStudentByName(students, length);
    }
    printf("\nKet qua tim kiem cho chuoi: \"%s\"\n", searchName);
    int found = 0;
    int i; 
    for (i = 0; i < *length; i++) {
        if (strstr(students[i].name, searchName)) {
            if (!found) {
                found = 1;
                printf("\t----------***All Students***----------\n");
                printf("|==========|====================|========================|====================|============|\n");
                printf("|    ID    |        Name        |          Email         |        Phone       |  NO.Course |\n");
                printf("|==========|====================|========================|====================|============|\n");
            }
            printf("| %-8d | %-18s | %-22s | %-18s | %-10d |\n", 
                   students[i].studentId, 
                   students[i].name, 
                   students[i].email, 
                   students[i].phone, 
                   students[i].courses);
        }
    }
    if (!found) {
        printf("Khong tim thay sinh vien nao voi ten chua chuoi: \"%s\"\n", searchName);
    } else {
        printf("|==========|====================|========================|====================|============|\n");
    }
    printf("\t \t---------------------\n");
}

// Ham luu file sinh vien 
void saveToFile(Student students[],int length) {
    FILE *fptr = fopen("studentsData.dat", "wb");
    if (fptr == NULL) {
        printf("Khong the mo tep de ghi.\n");
        return;
    }
    fwrite(&length, sizeof(int), 50, fptr); 
    fwrite(students, sizeof(Student), length, fptr);
    printf("Du lieu sinh vien duoc luu thanh cong.\n");
    fclose(fptr);
}
// Ham doc file sinh vien 
void loadFromFile(Student students[],int *length) {
    FILE *fptr = fopen("studentsData.dat", "rb");
    if (fptr == NULL) {
        printf("Khong tim thay du lieu.\n");
        *length = 0;
        return;
    }
    fread(length, sizeof(int), 50, fptr);
    fread(students, sizeof(Student), *length, fptr);
    fclose(fptr);
    printf("Du lieu sinh vien duoc tai thanh cong.\n");
    system("cls");
}

// Ham them giao vien
void addTeacher(Teacher teachers[], int *length) {
    int quantityTeacher, i, j;
    printf("\t **** Add A New Teacher ****\n");
    printf("Nhap so luong giang vien: ");
    scanf("%d", &quantityTeacher);
    getchar();
    for (i = 0; i < quantityTeacher; i++) {
        printf("Nhap thong tin cho giang vien thu %d\n", i + 1);
        int id;
        do {
            printf("Nhap ID giang vien: ");
            if (scanf("%d", &id) != 1) {
                printf("ID khong hop le. Vui long nhap lai.\n");
                while (getchar() != '\n');
                continue;
            }
            getchar();
            int isDuplicate = 0;
            for (j = 0; j < *length; j++) {
                if (teachers[j].teacherId == id) {
                    printf("ID %d da ton tai. Vui long nhap ID khac.\n", id);
                    isDuplicate = 1;
                    break;
                }
            }
            if (id <= 0) {
                printf("ID phai la so duong. Vui long nhap lai.\n");
                isDuplicate = 1;
            }
            if (!isDuplicate) break;
        } while (1);
        teachers[*length].teacherId = id;
        do {
            printf("Nhap ten giang vien: ");
            fgets(teachers[*length].name, sizeof(teachers[*length].name), stdin);
            teachers[*length].name[strcspn(teachers[*length].name, "\n")] = '\0';
            int valid = 1;
            for (j = 0; teachers[*length].name[j]; j++) {
                if (!isalpha(teachers[*length].name[j]) && !isspace(teachers[*length].name[j])) {
                    printf("Ten khong hop le. Vui long chi nhap chu cai va dau cach.\n");
                    valid = 0;
                    break;
                }
            }
            if (valid) break;
        } while (1);
        char email[100];
        do {
            printf("Nhap email giang vien (@gmail.com): ");
            fgets(email, sizeof(email), stdin);
            email[strcspn(email, "\n")] = '\0';
            const char *gmailSuffix = "@gmail.com";
            int len = strlen(email);
            int suffixLen = strlen(gmailSuffix);
            int isDuplicate = 0;
            if (len < suffixLen || strcmp(email + len - suffixLen, gmailSuffix) != 0) {
                printf("Email phai co dang '@gmail.com'. Vui long nhap lai.\n");
            } else {
                for (j = 0; j < *length; j++) {
                    if (strcmp(teachers[j].email, email) == 0) {
                        printf("Email %s da ton tai. Vui long nhap email khac.\n", email);
                        isDuplicate = 1;
                        break;
                    }
                }
                if (!isDuplicate) break;
            }
        } while (1);
        strcpy(teachers[*length].email, email);
        char phone[20];
        do {
            printf("Nhap so dien thoai giang vien: ");
            fgets(phone, sizeof(phone), stdin);
            phone[strcspn(phone, "\n")] = '\0';
            int len = strlen(phone);
            int valid = 1;

            if (len < 10 || len > 11) {
                printf("So dien thoai phai co do dai tu 10 den 11 chu so.\n");
                valid = 0;
            } else {
                for (j = 0; j < len; j++) {
                    if (!isdigit(phone[j])) {
                        printf("So dien thoai chi duoc chua chu so.\n");
                        valid = 0;
                        break;
                    }
                }
            }
            if (valid) {
                int isDuplicate = 0;
                for (j = 0; j < *length; j++) {
                    if (strcmp(teachers[j].phone, phone) == 0) {
                        printf("So dien thoai %s da ton tai. Vui long nhap so dien thoai khac.\n", phone);
                        isDuplicate = 1;
                        break;
                    }
                }
                if (!isDuplicate) break;
            }
        } while (1);
        strcpy(teachers[*length].phone, phone);
        printf("Nhap lop giang day: ");
        fgets(teachers[*length].classroomId, sizeof(teachers[*length].classroomId), stdin);
        teachers[*length].classroomId[strcspn(teachers[*length].classroomId, "\n")] = '\0';

        (*length)++; 
        printf("Da them giang vien thanh cong!\n");
    }
}
// Ham in giao vien
void printfTeacher(Teacher teachers[], int *length) {
    if (*length == 0) {
        printf("\nKhong co giang vien trong danh sach.\n");
        return;
    }
    printf("\t **** Show All Teachers ****\n");
    printf("\t----------***All Teachers***----------\n");
    printf("|==========|====================|========================|====================|============|\n");
    printf("|    ID    |        Name        |          Email         |        Phone       |  ID Class  |\n");
    printf("|==========|====================|========================|====================|============|\n");

    int i;
    for (i = 0; i < *length; i++) {
        printf("| %-8d | %-18s | %-22s | %-18s | %-10s |\n", 
               teachers[i].teacherId, 
               teachers[i].name, 
               teachers[i].email, 
               teachers[i].phone, 
               teachers[i].classroomId);
        printf("|==========|====================|========================|====================|============|\n");
    }
    printf("\t \t---------------------\n");
}
// Ham sua giao vien
void editTeacher(Teacher teachers[], int *length) {
    if (*length == 0) {
        printf("Danh sach giao vien hien dang trong. Khong co gi de sua.\n");
        return;
    }
    int id;
    printf("\t **** Edit A Teacher ****\n");
    printf("Nhap ID giao vien muon sua: ");
    scanf("%d", &id);
    getchar();    
    int found = -1;
    int i; 
    for (i = 0; i < *length; i++) {
        if (teachers[i].teacherId == id) {
            found = i;
            break;
        }
    }
    if (found == -1) {
        printf("Khong tim thay giao vien voi ID: %d\n", id);
        return;
    }
    printf("\nThong tin hien tai cua giao vien:\n");
    printf("ID: %d\n", teachers[found].teacherId);
    printf("Ho Va Ten: %s\n", teachers[found].name);
    printf("So Dien Thoai: %s\n", teachers[found].phone);
    printf("Email: %s\n", teachers[found].email);

    char input[100];
    int valid;
    int isChanged = 0;
    do {
        printf("Ho Va Ten (Nhap so 0 de bo qua): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        if (strcmp(input, "0") == 0) break; 
        valid = 1;
        for (i = 0; input[i]; i++) {
            if (!isalpha(input[i]) && !isspace(input[i])) {
                valid = 0;
                printf("Ten khong hop le. Vui long nhap lai (chi chu va khoang trang).\n");
                break;
            }
        }
        if (valid && strcmp(teachers[found].name, input) != 0) {
            strcpy(teachers[found].name, input);
            isChanged = 1;
        }
    } while (!valid);

    do {
        printf("So Dien Thoai (Nhap so 0 de bo qua): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        if (strcmp(input, "0") == 0) break; 
        valid = 1;
        int len = strlen(input);
        if (len < 10 || len > 11) {
            valid = 0;
            printf("So dien thoai khong hop le. Vui long nhap lai (do dai 10-11 ky tu).\n");
        } else {
            for (i = 0; i < len; i++) {
                if (!isdigit(input[i])) {
                    valid = 0;
                    printf("So dien thoai chi duoc chua so. Vui long nhap lai.\n");
                    break;
                }
            }
        }
        if (valid) {
            for (i = 0; i < *length; i++) {
                if (i != found && strcmp(teachers[i].phone, input) == 0) {
                    valid = 0;
                    printf("So dien thoai %s da ton tai. Vui long nhap so dien thoai khac.\n", input);
                    break;
                }
            }
        }
        if (valid && strcmp(teachers[found].phone, input) != 0) {
            strcpy(teachers[found].phone, input);
            isChanged = 1;
        }
    } while (!valid);

    do {
        printf("Nhap Email (Nhap so 0 de bo qua): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; 
        if (strcmp(input, "0") == 0) break;
        const char *gmailSuffix = "@gmail.com";
        int len = strlen(input);
        int suffixLen = strlen(gmailSuffix); 
        if (len < suffixLen || strcmp(input + len - suffixLen, gmailSuffix) != 0) {
            printf("Email phai co dang '@gmail.com'. Vui long nhap lai.\n");
        } 
        else {
            break;
        }
    } while (1);

    if (strcmp(input, "0") != 0) {
        strcpy(teachers[found].email, input);
    }
}
// Ham xoa giao vien
void deleteTeacher(Teacher teachers[], int *length) {
    int id, i, found = -1;
// Nhap id giao vien muon xoa
    printf("\t **** Delete A Teacher ****\n") ;
    printf("Nhap ID giao vien muon xoa: ");
    scanf("%d", &id);
// Tim giao vien co ID trong danh sach
    for (i = 0; i < *length; i++) {
        if (teachers[i].teacherId == id) {
            found = i;
            break;
        }
    }
// Neu khong tim thay giao vien
    if (found == -1) {
        printf("Khong tim thay giao vien voi ID: %d\n", id);
        return;
    }
// Hien thi thong tin giao vien can xoa
    printf("\nThong tin giao vien can xoa:\n");
    printf("ID: %d\n", teachers[found].teacherId);
    printf("Ho Va Ten: %s\n", teachers[found].name);
    printf("Email: %s\n", teachers[found].email);
    printf("So Dien Thoai: %s\n", teachers[found].phone);
    printf("ID Class: %s\n", teachers[found].classroomId);
// Yeu cau xac nhan xoa
    char confirm;
    printf("\nBan co chac chan muon xoa giao vien nay (y/n)? ");
    getchar();  
    scanf("%c", &confirm);
    if (confirm == 'y' || confirm == 'y') {
// Xoa giao vien
        for (i = found; i < *length - 1; i++) {
            teachers[i] = teachers[i + 1]; 
        }
        (*length)--; 
        printf("Giao vien da duoc xoa thanh cong.\n");
    } else {
        printf("Huy thao tac xoa giao vien.\n");
    }
}
// Ham tim kiem giao vien
void searchTeacherByName(Teacher teachers[], int *length) {
    if (*length == 0) {
        printf("Danh sach giao vien hien dang trong. Khong co gi de tim kiem.\n");
        return;
    }
    char searchName[50];
    clearInputBuffer();
    printf("\t **** Search A Teacher ****\n");
    printf("Nhap ten giao vien muon tim kiem: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0'; 
    if (strlen(searchName) == 0) {
        printf("Ten giao vien khong duoc de trong. Vui long nhap lai.\n");
        return searchTeacherByName(teachers, length);
    }
    printf("\nKet qua tim kiem cho chuoi: \"%s\"\n", searchName);
    int found = 0;
    int i; 
    for (i = 0; i < *length; i++) {
        if (strstr(teachers[i].name, searchName)) {
            if (!found) {
                found = 1;
                printf("\t **** Show All Teachers ****\n");
    			printf("\t----------***All Teachers***----------\n");
                printf("|==========|====================|========================|====================|============|\n");
                printf("|    ID    |        Name        |          Email         |        Phone       |  ID Class  |\n");
                printf("|==========|====================|========================|====================|============|\n");
            }
            printf("| %-8d | %-18s | %-22s | %-18s | %-10s |\n", 
                   teachers[i].teacherId, 
	               teachers[i].name, 
	               teachers[i].email, 
	               teachers[i].phone, 
	               teachers[i].classroomId);
        }
    }
    if (!found) {
        printf("Khong tim thay giao vien nao voi ten chua chuoi: \"%s\"\n", searchName);
    } else {
        printf("|==========|====================|========================|====================|============|\n");
    }
    printf("\t \t---------------------\n");
}

// Ham chuc nang back hoac end chuong trinh
void askToGoBack() {
    char choice;
    printf("\nGo Back (b) or Exit (0): ");
    choice = getchar();
    getchar(); 
	fflush(stdin);  
    if (choice == 'b' || choice == 'B') {
        return;  
    } else if (choice == '0') {
    	system("cls");
        end();
		exit(0); 
	}
}
// Ham end chuong trinh
void end(){
	printf("=========Thank You=========\n");
	printf("=========See You Soon======\n");
}

// Ham luu file giao vien 
void saveTeacherToFile(Teacher teachers[],int length) {
    FILE *fptr = fopen("teachersData.dat", "wb");
    if (fptr == NULL) {
        printf("Khong the mo tep de ghi.\n");
        return;
    }
    fwrite(&length, sizeof(int), 50, fptr); 
    fwrite(teachers, sizeof(Teacher), length, fptr);
    printf("Du lieu giao vien duoc luu thanh cong.\n");
    fclose(fptr);
}
// Ham doc file giao vien 
void loadTeacherFromFile(Teacher teachers[],int *length) {
    FILE *fptr = fopen("teachersData.dat", "rb");
    if (fptr == NULL) {
        printf("Khong tim thay du lieu.\n");
        *length = 0;
        return;
    }
    fread(length, sizeof(int), 50, fptr);
    fread(teachers, sizeof(Teacher), *length, fptr);
    fclose(fptr);
    printf("Du lieu giao vien duoc tai thanh cong.\n");
}

// Ham kiem tra neu ID trung lap 
int isDuplicateID(Student students[], int length, int id) {
	int i; 
    for (i = 0; i < length; i++) {
        if (students[i].studentId == id) {
            return 1;
        }
    }
    return 0;
}
// Ham kiem tra neu email sinh vien trung lap 
int isDuplicateEmailStudent(Student students[], int length, const char *email) {
	int i; 
    for (i = 0; i < length; i++) {
        if (strcmp(students[i].email, email) == 0) {
            return 1;
        }
    }
    return 0;
}
// Ham kiem tra neu email giao vien trung lap
int isDuplicateEmailTeacher(Teacher teachers[], int length, const char *email) {
	int i; 
    for (i = 0; i < length; i++) {
        if (strcmp(teachers[i].email, email) == 0) {
            return 1; 
        }
    }
    return 0;
}
// Ham kiem tra sdt sinh vien
int isDuplicatePhoneStudent(Student students[], int length, const char *phone) {
	int i; 
    for (i = 0; i < length; i++) {
        if (strcmp(students[i].phone, phone) == 0) {
            return 1;
        }
    }
    return 0;
}
// Ham kiem tra sdt giao vien 
int isDuplicatePhoneTeacher(Teacher teachers[], int length, const char *phone) {
	int i; 
    for (i = 0; i < length; i++) {
        if (strcmp(teachers[i].phone, phone) == 0) {
            return 1;
        }
    }
    return 0;
}
