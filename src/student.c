#include "student.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node *findStudent(Node *head, int id)
{
    Node *current = head;

    while (current != NULL) {
        if (current->data.id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

int appendStudent(Node **head, const Student *student)
{
    Node *new_node;
    Node *current;

    if (head == NULL || student == NULL || findStudent(*head, student->id) != NULL) {
        return 0;
    }

    new_node = malloc(sizeof(*new_node));
    if (new_node == NULL) {
        return 0;
    }

    new_node->data = *student;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
        return 1;
    }

    current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
    return 1;
}

void displayStudents(const Node *head)
{
    const Node *current = head;

    if (current == NULL) {
        puts("\nAucun étudiant enregistré.");
        return;
    }

    printf("\n%-10s %-30s %-10s\n", "ID", "Nom", "Moyenne");
    puts("------------------------------------------------------");

    while (current != NULL) {
        printf("%-10d %-30s %-10.2f\n",
               current->data.id, current->data.name, current->data.average);
        current = current->next;
    }
}

int updateStudent(Node *head, int id, const char *name, float average)
{
    Node *student = findStudent(head, id);

    if (student == NULL || name == NULL || name[0] == '\0' ||
        average < 0.0f || average > 20.0f) {
        return 0;
    }

    if (strlen(name) >= NAME_LENGTH) {
        return 0;
    }

    strcpy(student->data.name, name);
    student->data.average = average;
    return 1;
}

int deleteStudent(Node **head, int id)
{
    Node *current;
    Node *previous = NULL;

    if (head == NULL) {
        return 0;
    }

    current = *head;
    while (current != NULL && current->data.id != id) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        return 0;
    }

    if (previous == NULL) {
        *head = current->next;
    } else {
        previous->next = current->next;
    }

    free(current);
    return 1;
}

void sortStudents(Node *head)
{
    Node *i;
    Node *j;
    Student temporary;

    for (i = head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->data.average < j->data.average) {
                temporary = i->data;
                i->data = j->data;
                j->data = temporary;
            }
        }
    }
}

void freeList(Node **head)
{
    Node *current;

    if (head == NULL) {
        return;
    }

    current = *head;
    while (current != NULL) {
        Node *next_node = current->next;
        free(current);
        current = next_node;
    }
    *head = NULL;
}
