#ifndef STUDENT_H
#define STUDENT_H

#include <stddef.h>

#define NAME_LENGTH 100
#define DATA_FILE "students.dat"

typedef struct {
    int id;
    char name[NAME_LENGTH];
    float average;
} Student;

typedef struct Node {
    Student data;
    struct Node *next;
} Node;

/* Gestion de la liste chaînée */
Node *findStudent(Node *head, int id);
int appendStudent(Node **head, const Student *student);
void displayStudents(const Node *head);
int updateStudent(Node *head, int id, const char *name, float average);
int deleteStudent(Node **head, int id);
void sortStudents(Node *head);
void freeList(Node **head);

/* Persistance dans un fichier binaire */
int loadStudents(Node **head, const char *filename);
int saveStudents(const Node *head, const char *filename);

#endif
