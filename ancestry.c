#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ancestry.h"

struct person_t *make_person(char *first_name, char *last_name, int year_born) {
    // TODO: Allokér plads til en `struct person_t`.
    // TODO: Allokér også plads til kopier af `first_name` og `last_name`.
    // TODO: Kopiér indholdet fra `first_name` og `last_name` over i kopierne.
    // TODO: Husk at gøre plads til både alle tegnene i navnene + 1 NUL-byte.
    struct person_t *a = malloc(sizeof(struct person_t));
    //char *cpy_afn = malloc(sizeof(char)+1);
    char *cpy_afn = malloc(strlen(first_name)+1);
    //char *cpy_aln = malloc(sizeof(char)+1);
    char *cpy_aln = malloc(strlen(last_name)+1);

    strcpy(cpy_afn, first_name);
    strcpy(cpy_aln, last_name);

    a->first_name = cpy_afn;
    a->last_name = cpy_aln;
    a->year_born = year_born;

    return a;
}

void free_person(struct person_t *person) {
    // TODO: Der skal være et free()-kald for hver malloc() i make_person().
    // TODO: Du må gerne sætte `first_name` og `last_name` til NULL *EFTER* de er free()'et.
    free(person->first_name);
    person->first_name = NULL;
    free(person->last_name);
    person->last_name = NULL;
    free(person);

}

struct ancestry_node_t *make_tree(struct person_t *person) {
    // TODO: Allokér plads til en `struct ancestry_node_t`.
    // TODO: Sæt `person` til input-personen.
    // TODO: Sæt `mom` og `dad` til NULL.
    struct ancestry_node_t *a = malloc(sizeof(struct ancestry_node_t));
    a->person = person;
    a->mom = NULL;
    a->dad = NULL;

    return a;
}

bool add_mom(struct ancestry_node_t *child_node, struct person_t *mom_person) {
    // TODO: Hvis der allerede er en mor-stamtavle, skal funktionen fejle.
    // TODO: Hvis ikke, skal `mom_person` indsættes i en `mom_node` som først skal allokeres.
    if (child_node->mom != NULL) {
        return false;
    }
    struct ancestry_node_t *n = malloc(sizeof(struct ancestry_node_t));
    n->person = mom_person;
    n->mom=NULL;
    n->dad=NULL;
    child_node->mom=n;

    return true;
}

bool add_dad(struct ancestry_node_t *child_node, struct person_t *dad_person) {
    // TODO: Hvis der allerede er en far-stamtavle, skal funktionen fejle.
    // TODO: Hvis ikke, skal `dad_person` indsættes i en `dad_node` som først skal allokeres.
    if (child_node->dad != NULL) {
        return false;
    }
    struct ancestry_node_t *n = malloc(sizeof(struct ancestry_node_t));
    n->person = dad_person;
    n->mom = NULL;
    n->dad = NULL;
    child_node->dad=n;

    return true;
}

void free_tree(struct ancestry_node_t *node) {
    // TODO: Kald `free_person()` på personen i noden.
    // TODO: Kald `free_tree()` på begge forældre-stamtræer.
    // TODO: Sæt pointerne til NULL efter de er free()'et.
}

void print_tree_recursive(struct ancestry_node_t *node, char *prefix, bool is_last) {
    if (node == NULL) {
        return;
    }

    printf("%s", prefix);
    printf("%s", is_last ? "└── " : "├── ");
    printf("%s %s\n", node->person->first_name, node->person->last_name);

    char new_prefix[1000];
    snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix, is_last ? "    " : "│   ");

    if (node->mom != NULL && node->dad != NULL) {
        print_tree_recursive(node->mom, new_prefix, false);
        print_tree_recursive(node->dad, new_prefix, true);
    } else if (node->mom != NULL) {
        print_tree_recursive(node->mom, new_prefix, true);
    } else if (node->dad != NULL) {
        print_tree_recursive(node->dad, new_prefix, true);
    }
}

void print_tree(struct ancestry_node_t *node) {
    print_tree_recursive(node, "", true);
}
