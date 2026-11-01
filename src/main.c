#include "student.h"

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int readLine(const char *prompt, char *buffer, size_t size)
{
    size_t length;
    int ch;

    printf("%s", prompt);
    if (fgets(buffer, (int)size, stdin) == NULL) {
        return 0;
    }

    length = strlen(buffer);
    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[length - 1] = '\0';
        return 1;
    }

    while ((ch = getchar()) != '\n' && ch != EOF) {
        /* Vider le reste de la ligne. */
    }
    puts("Erreur : saisie trop longue.");
    return 0;
}

static int readInt(const char *prompt, int *value)
{
    char buffer[128];
    char *end;
    long parsed;

    if (!readLine(prompt, buffer, sizeof(buffer))) {
        return 0;
    }

    errno = 0;
    parsed = strtol(buffer, &end, 10);
    while (*end == ' ' || *end == '\t') {
        end++;
    }

    if (buffer[0] == '\0' || *end != '\0' || errno == ERANGE ||
        parsed < INT_MIN || parsed > INT_MAX) {
        puts("Erreur : veuillez saisir un entier valide.");
        return 0;
    }

    *value = (int)parsed;
    return 1;
}

static int readAverage(const char *prompt, float *average)
{
    char buffer[128];
    char *end;
    float parsed;

    if (!readLine(prompt, buffer, sizeof(buffer))) {
        return 0;
    }

    errno = 0;
    parsed = strtof(buffer, &end);
    while (*end == ' ' || *end == '\t') {
        end++;
    }

    if (buffer[0] == '\0' || *end != '\0' || errno == ERANGE ||
        !(parsed >= 0.0f && parsed <= 20.0f)) {
        puts("Erreur : la moyenne doit être comprise entre 0 et 20.");
        return 0;
    }

    *average = parsed;
    return 1;
}

static void addStudent(Node **head)
{
    Student student;

    if (!readInt("Identifiant : ", &student.id) || student.id <= 0) {
        puts("Erreur : identifiant invalide.");
        return;
    }

    if (findStudent(*head, student.id) != NULL) {
        puts("Erreur : cet identifiant existe déjà.");
        return;
    }

    if (!readLine("Nom complet : ", student.name, sizeof(student.name)) ||
        student.name[0] == '\0') {
        puts("Erreur : nom invalide.");
        return;
    }

    if (!readAverage("Moyenne (0-20) : ", &student.average)) {
        return;
    }

    if (!appendStudent(head, &student)) {
        puts("Erreur : ajout impossible (mémoire insuffisante).");
        return;
    }

    puts("Étudiant ajouté avec succès.");
}

static void searchStudent(Node *head)
{
    int id;
    Node *student;

    if (!readInt("Identifiant à rechercher : ", &id)) {
        return;
    }

    student = findStudent(head, id);
    if (student == NULL) {
        puts("Étudiant introuvable.");
        return;
    }

    printf("\nID : %d\nNom : %s\nMoyenne : %.2f\n",
           student->data.id, student->data.name, student->data.average);
}

static void editStudent(Node *head)
{
    int id;
    char name[NAME_LENGTH];
    float average;

    if (!readInt("Identifiant à modifier : ", &id)) {
        return;
    }

    if (findStudent(head, id) == NULL) {
        puts("Étudiant introuvable.");
        return;
    }

    if (!readLine("Nouveau nom complet : ", name, sizeof(name)) ||
        name[0] == '\0' ||
        !readAverage("Nouvelle moyenne (0-20) : ", &average)) {
        puts("Modification annulée.");
        return;
    }

    if (!updateStudent(head, id, name, average)) {
        puts("Modification impossible.");
        return;
    }

    puts("Informations modifiées avec succès.");
}

static void removeStudent(Node **head)
{
    int id;

    if (!readInt("Identifiant à supprimer : ", &id)) {
        return;
    }

    puts(deleteStudent(head, id)
         ? "Étudiant supprimé avec succès."
         : "Étudiant introuvable.");
}

static void showMenu(void)
{
    puts("\n========== GESTION DES ÉTUDIANTS ==========");
    puts("1. Ajouter un étudiant");
    puts("2. Afficher tous les étudiants");
    puts("3. Rechercher un étudiant");
    puts("4. Modifier un étudiant");
    puts("5. Supprimer un étudiant");
    puts("6. Trier par moyenne décroissante");
    puts("7. Enregistrer les données");
    puts("0. Enregistrer et quitter");
}

int main(void)
{
    Node *head = NULL;
    int choice = -1;

    loadStudents(&head, DATA_FILE);

    while (choice != 0) {
        showMenu();

        if (!readInt("Votre choix : ", &choice)) {
            if (feof(stdin)) {
                puts("\nFin de l'entrée : sauvegarde avant de quitter.");
                saveStudents(head, DATA_FILE);
                break;
            }
            continue;
        }

        switch (choice) {
            case 1: addStudent(&head); break;
            case 2: displayStudents(head); break;
            case 3: searchStudent(head); break;
            case 4: editStudent(head); break;
            case 5: removeStudent(&head); break;
            case 6:
                sortStudents(head);
                puts("Tri effectué.");
                break;
            case 7: saveStudents(head, DATA_FILE); break;
            case 0:
                saveStudents(head, DATA_FILE);
                puts("Au revoir !");
                break;
            default: puts("Option invalide. Réessayez.");
        }
    }

    freeList(&head);
    return 0;
}
