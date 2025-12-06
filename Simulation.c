#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STUDENT_FILE "students.txt"
#define CREDENTIAL_FILE "credentials.txt"

// Student Structure
struct Student {
    int roll;
    char name[50];
    float marks;
};

// Linked List Node (Stack Node)
struct Node {
    struct Student data;
    struct Node *next;
};

struct Node *top = NULL;  // Stack top pointer

char currentRole[10];
char currentUser[50];

// Function Prototypes
int loginSystem();
void loadStudents();
void saveStudents();

void mainMenu();
void adminMenu();
void staffMenu();
void userMenu();
void guestMenu();

void pushStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

struct Node* createNode(struct Student s);
void push(struct Student s);
void deleteByRoll(int roll);

// ================= MAIN =================
int main() {
    while(1) {
        if(loginSystem()) {
            loadStudents();
            mainMenu();
            saveStudents();
        } else {
            printf("\nAccess Denied. Try again.\n");
        }
    }
    return 0;
}

// =============== LOGIN SYSTEM ===============

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

// =============== LOAD / SAVE LINKED LIST ===============

void loadStudents() {
    FILE *fp = fopen(STUDENT_FILE, "r");
    if(!fp) return;

    top = NULL;
    struct Student s;

    while(fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) == 3) {
        push(s);  // push into stack
    }
    fclose(fp);
}

void saveStudents() {
    FILE *fp = fopen(STUDENT_FILE, "w");
    if(!fp) return;

    struct Node *temp = top;

    while(temp != NULL) {
        fprintf(fp, "%d %s %.2f\n",
                temp->data.roll,
                temp->data.name,
                temp->data.marks);
        temp = temp->next;
    }

    fclose(fp);
}

// =============== MAIN MENU ===============

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
        printf("1. Push Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: pushStudent(); break;
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
    while(1) {
        printf("\n===== STAFF MENU =====\n");
        printf("1. Display Students\n");
        printf("2. Search Student\n");
        printf("3. Update Student\n");
        printf("4. Delete Student\n");
        printf("5. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: displayStudents(); break;
            case 2: searchStudent(); break;
            case 3: updateStudent(); break;
            case 4: deleteStudent(); break;
            case 5: return;
            default: printf("Invalid choice!\n");
        }
    }
}

void userMenu() {
    int choice;
    while(1) {
        printf("\n===== USER MENU =====\n");
        printf("1. Display Students\n");
        printf("2. Search Student\n");
        printf("3. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: displayStudents(); break;
            case 2: searchStudent(); break;
            case 3: return;
            default: printf("Invalid choice!\n");
        }
    }
}

void guestMenu() {
    int choice;
    while(1) {
        printf("\n===== GUEST MENU =====\n");
        displayStudents();
        printf("\n1. Logout\n");
        scanf("%d", &choice);
        if(choice == 1) return;

        printf("Invalid choice!\n");
    }
}

// =============== LINKED LIST OPERATIONS ===============

struct Node* createNode(struct Student s) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = s;
    newNode->next = NULL;
    return newNode;
}

// PUSH (Add at top)
void push(struct Student s) {
    struct Node *newNode = createNode(s);
    newNode->next = top;
    top = newNode;
}

// Add student (wrapper for push)
void pushStudent() {
    struct Student s;

    printf("Enter Roll: ");
    scanf("%d", &s.roll);

    printf("Enter Name: ");
    scanf("%s", s.name);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    push(s);
    printf("Student pushed to stack successfully!\n");
}

// DISPLAY all
void displayStudents() {
    if(top == NULL) {
        printf("No student records!\n");
        return;
    }

    struct Node *temp = top;

    printf("\nRoll\tName\tMarks\n");
    while(temp != NULL) {
        printf("%d\t%s\t%.2f\n",
            temp->data.roll,
            temp->data.name,
            temp->data.marks);
        temp = temp->next;
    }
}

// SEARCH by roll
void searchStudent() {
    int roll;
    printf("Enter roll to search: ");
    scanf("%d", &roll);

    struct Node *temp = top;

    while(temp != NULL) {
        if(temp->data.roll == roll) {
            printf("FOUND: %d %s %.2f\n",
                   temp->data.roll,
                   temp->data.name,
                   temp->data.marks);
            return;
        }
        temp = temp->next;
    }

    printf("Student not found!\n");
}

// UPDATE student by roll
void updateStudent() {
    int roll;
    printf("Enter roll to update: ");
    scanf("%d", &roll);

    struct Node *temp = top;

    while(temp != NULL) {
        if(temp->data.roll == roll) {
            printf("Enter new name: ");
            scanf("%s", temp->data.name);

            printf("Enter new marks: ");
            scanf("%f", &temp->data.marks);

            printf("Updated successfully!\n");
            return;
        }
        temp = temp->next;
    }

    printf("Student not found!\n");
}

// DELETE by roll
void deleteByRoll(int roll) {
    if(top == NULL) return;

    // If top node is the one
    if(top->data.roll == roll) {
        struct Node *temp = top;
        top = top->next;
        free(temp);
        return;
    }

    // Search in list
    struct Node *prev = top;
    struct Node *curr = top->next;

    while(curr != NULL) {
        if(curr->data.roll == roll) {
            prev->next = curr->next;
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

// DELETE student
void deleteStudent() {
    int roll;
    printf("Enter roll to delete: ");
    scanf("%d", &roll);

    struct Node *temp = top;
    while(temp != NULL) {
        if(temp->data.roll == roll) {
            deleteByRoll(roll);
            printf("Deleted successfully!\n");
            return;
        }
        temp = temp->next;
    }

    printf("Student not found!\n");
}
