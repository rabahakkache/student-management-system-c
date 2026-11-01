#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LENGTH 100
#define FILE_NAME "students.dat"

typedef struct {
    int id;
    char name[NAME_LENGTH];
    float average;
} Student;

typedef struct Node {
    Student data;
    struct Node *next;
} Node;

Node *head = NULL;

Node *findStudent(int id) {
    Node *current = head;

    while (current != NULL) {
        if (current->data.id == id) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

void addStudent(void) {
    Student student;
    Node *newNode;
    Node *current;

    printf("\nEnter student ID: ");
    if (scanf("%d", &student.id) != 1) {
        printf("Invalid ID.\n");
        while (getchar() != '\n');
        return;
    }

    if (findStudent(student.id) != NULL) {
        printf("A student with this ID already exists.\n");
        return;
    }

    printf("Enter student name: ");
    scanf(" %99[^\n]", student.name);

    printf("Enter student average (0-20): ");
    if (scanf("%f", &student.average) != 1 ||
        student.average < 0 || student.average > 20) {
        printf("Invalid average.\n");
        while (getchar() != '\n');
        return;
    }

    newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    newNode->data = student;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    } else {
        current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }

    printf("Student added successfully.\n");
}

void displayStudents(void) {
    Node *current = head;

    if (head == NULL) {
        printf("\nNo students found.\n");
        return;
    }

    printf("\n%-10s %-30s %-10s\n", "ID", "Name", "Average");
    printf("------------------------------------------------------\n");

    while (current != NULL) {
        printf("%-10d %-30s %-10.2f\n",
               current->data.id,
               current->data.name,
               current->data.average);
        current = current->next;
    }
}

void searchStudent(void) {
    int id;
    Node *student;

    printf("\nEnter student ID to search: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid ID.\n");
        while (getchar() != '\n');
        return;
    }

    student = findStudent(id);

    if (student == NULL) {
        printf("Student not found.\n");
    } else {
        printf("\nStudent found:\n");
        printf("ID: %d\n", student->data.id);
        printf("Name: %s\n", student->data.name);
        printf("Average: %.2f\n", student->data.average);
    }
}

void updateStudent(void) {
    int id;
    Node *student;

    printf("\nEnter student ID to update: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid ID.\n");
        while (getchar() != '\n');
        return;
    }

    student = findStudent(id);

    if (student == NULL) {
        printf("Student not found.\n");
        return;
    }

    printf("Enter new name: ");
    scanf(" %99[^\n]", student->data.name);

    printf("Enter new average (0-20): ");
    if (scanf("%f", &student->data.average) != 1 ||
        student->data.average < 0 || student->data.average > 20) {
        printf("Invalid average. Update cancelled.\n");
        while (getchar() != '\n');
        return;
    }

    printf("Student updated successfully.\n");
}

void deleteStudent(void) {
    int id;
    Node *current = head;
    Node *previous = NULL;

    printf("\nEnter student ID to delete: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid ID.\n");
        while (getchar() != '\n');
        return;
    }

    while (current != NULL && current->data.id != id) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Student not found.\n");
        return;
    }

    if (previous == NULL) {
        head = current->next;
    } else {
        previous->next = current->next;
    }

    free(current);
    printf("Student deleted successfully.\n");
}

void sortStudents(void) {
    Node *i;
    Node *j;
    Student temp;

    if (head == NULL || head->next == NULL) {
        printf("Not enough students to sort.\n");
        return;
    }

    for (i = head; i->next != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->data.average < j->data.average) {
                temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }

    printf("Students sorted by average (highest first).\n");
}

void saveStudents(void) {
    FILE *file = fopen(FILE_NAME, "wb");
    Node *current = head;

    if (file == NULL) {
        printf("Could not open file for saving.\n");
        return;
    }

    while (current != NULL) {
        if (fwrite(&current->data, sizeof(Student), 1, file) != 1) {
            printf("Error while writing student data.\n");
            fclose(file);
            return;
        }
        current = current->next;
    }

    fclose(file);
    printf("Students saved successfully.\n");
}

void loadStudents(void) {
    FILE *file = fopen(FILE_NAME, "rb");
    Student student;
    Node *newNode;
    Node *tail = NULL;

    if (file == NULL) {
        return; /* The file may not exist on the first run. */
    }

    while (fread(&student, sizeof(Student), 1, file) == 1) {
        newNode = malloc(sizeof(Node));

        if (newNode == NULL) {
            printf("Memory allocation failed while loading data.\n");
            fclose(file);
            return;
        }

        newNode->data = student;
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
        } else {
            tail->next = newNode;
        }

        tail = newNode;
    }

    fclose(file);
}

void freeList(void) {
    Node *current = head;
    Node *nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    head = NULL;
}

int main(void) {
    int choice;

    loadStudents();

    do {
        printf("\n========== STUDENT MANAGEMENT SYSTEM ==========\n");
        printf("1. Add student\n");
        printf("2. Display all students\n");
        printf("3. Search for a student\n");
        printf("4. Update student\n");
        printf("5. Delete student\n");
        printf("6. Sort students by average\n");
        printf("7. Save students\n");
        printf("0. Save and exit\n");
        printf("Choose an option: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid choice. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                sortStudents();
                break;
            case 7:
                saveStudents();
                break;
            case 0:
                saveStudents();
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid option. Try again.\n");
        }

    } while (choice != 0);

    freeList();
    return 0;
}
