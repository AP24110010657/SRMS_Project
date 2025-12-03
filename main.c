#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STUDENT_FILE "students.txt"
#define CREDENTIAL_FILE "credentials.txt"

struct Student {
    int roll;
    char name[50];
    float marks;
};

char currentRole[10];
char currentUser[50];

// Function Prototypes
int loginSystem();
void mainMenu();
void adminMenu();
void staffMenu();
void userMenu();
void guestMenu();

void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

int main() {
    while(1) {  // Infinite loop for login menu
        if(loginSystem()) {   // Ask for username/password
            mainMenu();       // Show role-based menu
        } else {
            printf("\nAccess Denied. Try again.\n");
        }
    }
    return 0;
}


int loginSystem() {
    char username[50], password[50];
    char fileUser[50], filePass[50], fileRole[10];

    printf("===== Login =====\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    FILE *fp = fopen(CREDENTIAL_FILE, "r");
    if(!fp) {
        printf("Error: credentials.txt not found!\n");
        return 0;
    }

    while(fscanf(fp, "%s %s %s", fileUser, filePass, fileRole) == 3) {
        if(strcmp(username, fileUser) == 0 && strcmp(password, filePass) == 0) {
            strcpy(currentRole, fileRole);
            strcpy(currentUser, fileUser);
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void mainMenu() {
    if(strcmp(currentRole, "ADMIN") == 0)
        adminMenu();
    else if(strcmp(currentRole, "STAFF") == 0)
        staffMenu();
    else if(strcmp(currentRole, "USER") == 0)
        userMenu();
    else
        guestMenu();
}

void adminMenu() {
    int choice;
    do {
        printf("\n===== ADMIN MENU =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: return;
            default: printf("Invalid choice!\n");
        }
    } while(1);
}

void staffMenu() {
    int choice;
    while(1) {   // Keep showing menu
        printf("\n===== STAFF MENU =====\n");
        printf("1. View Students\n");
        printf("2. Search Student\n");
        printf("3. Update Student\n");
        printf("4. Delete Student\n");
        printf("5. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

       switch(choice) {
            case 1: displayStudents(); break;
            case 2: searchStudent(); break;
            case 3: updateStudent(); break;  // STAFF can update
            case 4: deleteStudent(); break;  // STAFF can delete
            case 5: 
                printf("Logging out...\n");
                return;  // exits staff menu → back to login
            default: printf("Invalid choice!\n");
        }
    }
} 
    
void userMenu() {
    int choice;
    while(1) {   // Keep showing menu until logout
        printf("\n===== USER MENU =====\n");
        printf("1. View Students\n");
        printf("2. Search Student\n");
        printf("3. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: displayStudents(); break;  // view all info
            case 2: searchStudent(); break;    // search by roll
            case 3:
                printf("Logging out...\n");
                return;   // exit menu → back to login
            default: printf("Invalid choice!\n");
        }
    }
}

void guestMenu() {
    int choice;
    while(1) {
        printf("\n===== GUEST MENU =====\n");
        printf("Guest can ONLY VIEW students.\n");
        
        displayStudents();  // show students automatically

        printf("\n1. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if(choice == 1) {
            printf("Logging out...\n");
            return;  // exit guest menu → back to login
        } else {
            printf("Invalid choice! Please enter 1 to logout.\n");
        }
    }
}


void addStudent() {
    struct Student s;
    FILE *fp = fopen(STUDENT_FILE, "a");

    printf("Enter Roll: ");
    scanf("%d", &s.roll);
    printf("Enter Name: ");
    scanf("%s", s.name);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fprintf(fp, "%d %s %.2f\n", s.roll, s.name, s.marks);
    fclose(fp);

    printf("Student Added Successfully!\n");
}

void displayStudents() {
    struct Student s;
    FILE *fp = fopen(STUDENT_FILE, "r");

    if(!fp) {
        printf("No student records found!\n");
        return;
    }

    printf("\nRoll\tName\tMarks\n");
    while(fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) != EOF) {
        printf("%d\t%s\t%.2f\n", s.roll, s.name, s.marks);
    }
    fclose(fp);
}

void searchStudent() {
    int roll, found = 0;
    struct Student s;

    printf("Enter roll to search: ");
    scanf("%d", &roll);

    FILE *fp = fopen(STUDENT_FILE, "r");
    if(!fp) {
        printf("No records!\n");
        return;
    }

    while(fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) != EOF) {
        if(s.roll == roll) {
            printf("FOUND: %d %s %.2f\n", s.roll, s.name, s.marks);
            found = 1;
            break;
        }
    }
    fclose(fp);

    if(!found) printf("Student not found!\n");
}

void updateStudent() {
    int roll, found = 0;
    struct Student s;
    FILE *fp = fopen(STUDENT_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    printf("Enter roll to update: ");
    scanf("%d", &roll);

    while(fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) != EOF) {
        if(s.roll == roll) {
            found = 1;
            printf("Enter new name: ");
            scanf("%s", s.name);
            printf("Enter new marks: ");
            scanf("%f", &s.marks);
        }
        fprintf(temp, "%d %s %.2f\n", s.roll, s.name, s.marks);
    }

    fclose(fp);
    fclose(temp);

    remove(STUDENT_FILE);
    rename("temp.txt", STUDENT_FILE);

    if(found) printf("Updated Successfully!\n");
    else printf("Student not found!\n");
}

void deleteStudent() {
    int roll, found = 0;
    struct Student s;
    FILE *fp = fopen(STUDENT_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    printf("Enter roll to delete: ");
    scanf("%d", &roll);

    while(fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) != EOF) {
        if(s.roll != roll) {
            fprintf(temp, "%d %s %.2f\n", s.roll, s.name, s.marks);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove(STUDENT_FILE);
    rename("temp.txt", STUDENT_FILE);

    if(found) printf("Deleted Successfully!\n");
    else printf("Student not found!\n");
}
