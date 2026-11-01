#include "student.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int saveStudents(const Node *head, const char *filename)
{
    FILE *file;
    const Node *current;

    if (filename == NULL) {
        return 0;
    }

    file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Impossible d'ouvrir le fichier de sauvegarde");
        return 0;
    }

    current = head;
    while (current != NULL) {
        if (fwrite(&current->data, sizeof(Student), 1, file) != 1) {
            perror("Erreur pendant l'écriture");
            fclose(file);
            return 0;
        }
        current = current->next;
    }

    if (fclose(file) != 0) {
        perror("Erreur pendant la fermeture du fichier");
        return 0;
    }

    printf("Données enregistrées dans %s.\n", filename);
    return 1;
}

int loadStudents(Node **head, const char *filename)
{
    FILE *file;
    Student student;
    size_t loaded = 0;

    if (head == NULL || filename == NULL) {
        return 0;
    }

    file = fopen(filename, "rb");
    if (file == NULL) {
        if (errno != ENOENT) {
            perror("Impossible d'ouvrir le fichier de données");
        }
        return 0;
    }

    while (fread(&student, sizeof(Student), 1, file) == 1) {
        if (student.id <= 0 ||
            memchr(student.name, '\0', sizeof(student.name)) == NULL ||
            student.name[0] == '\0' ||
            !(student.average >= 0.0f && student.average <= 20.0f) ||
            findStudent(*head, student.id) != NULL) {
            fprintf(stderr, "Avertissement : enregistrement invalide ignoré.\n");
            continue;
        }

        if (!appendStudent(head, &student)) {
            fprintf(stderr, "Erreur : mémoire insuffisante.\n");
            fclose(file);
            return (int)loaded;
        }
        loaded++;
    }

    if (ferror(file)) {
        perror("Erreur pendant la lecture du fichier");
    }

    fclose(file);
    printf("%zu étudiant(s) chargé(s).\n", loaded);
    return (int)loaded;
}
