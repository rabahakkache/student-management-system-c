# Système de gestion des étudiants en C

Application en ligne de commande développée en langage C pour gérer une liste d'étudiants à l'aide d'une **liste simplement chaînée** et sauvegarder les données dans un **fichier binaire**.

## Fonctionnalités

- Ajouter un étudiant avec un identifiant unique, un nom et une moyenne.
- Afficher la liste des étudiants.
- Rechercher un étudiant par identifiant.
- Modifier ses informations.
- Supprimer un étudiant.
- Trier les étudiants par moyenne décroissante.
- Enregistrer et charger les données avec `fwrite` et `fread`.
- Vérifier les saisies et libérer la mémoire à la fermeture.

## Organisation du projet

```text
student-management-system-c/
├── include/
│   └── student.h
├── src/
│   ├── main.c
│   ├── student.c
│   └── storage.c
├── .gitignore
├── Makefile
└── README.md
```

- `student.h` : structures et prototypes des fonctions.
- `student.c` : opérations sur la liste chaînée.
- `storage.c` : lecture et écriture du fichier binaire.
- `main.c` : menu, saisie et interaction avec l'utilisateur.

## Compilation

### Avec GCC

Depuis le dossier du projet :

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic -Iinclude src/main.c src/student.c src/storage.c -o student_manager
```

### Avec Make

```bash
make
```

## Exécution

Sous Linux :

```bash
./student_manager
```

Sous Windows (MinGW) :

```bash
student_manager.exe
```

Les données sont sauvegardées dans `students.dat` dans le répertoire depuis lequel le programme est lancé. Ce fichier est créé automatiquement à la première sauvegarde.

## Concepts utilisés

- Structures (`struct`)
- Pointeurs et allocation dynamique (`malloc`, `free`)
- Listes simplement chaînées
- Fonctions et fichiers d'en-tête (`.h`)
- Séparation du programme en plusieurs fichiers source (`.c`)
- Manipulation des fichiers binaires (`fopen`, `fread`, `fwrite`, `fclose`)
- Recherche, suppression et tri

## Auteur

Rabah Akkache
