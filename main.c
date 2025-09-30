#include <stdio.h>
#include "ancestry.h"

void small_stack_allocated_tree();
void large_heap_allocated_tree();

int main(void) {
    //small_stack_allocated_tree();
    large_heap_allocated_tree();

    return 0;
}

void small_stack_allocated_tree() {
    // A small stack-allocated ancestry tree; does not use any helper functions.

    // Først laver jeg person struct'erne
    struct person_t anne_p = { "Anne", "Person", 1990 };
    struct person_t annemor = { "Annemor", "Person", 1970 };
    struct person_t annefar = { "Annefar", "Person", 1969 };

    // Så laver jeg stamtavle struct'erne
    struct ancestry_node_t anne_tree;
    struct ancestry_node_t annemor_tree;
    struct ancestry_node_t annefar_tree;

    // Så udfylder jeg stamtavlerne med pointere til de stak-allokerede struct'er
    // Fordi det er stak-allokerede struct'er skal jeg bruge & foran variablene
    anne_tree.person = &anne_p;
    anne_tree.mom = &annemor_tree;
    anne_tree.dad = &annefar_tree;

    annemor_tree.person = &annemor;
    annemor_tree.mom = NULL;
    annemor_tree.dad = NULL;

    annefar_tree.person = &annefar;
    annefar_tree.mom = NULL;
    annefar_tree.dad = NULL;

    print_tree(&anne_tree);
}

void large_heap_allocated_tree() {
    // A large heap-allocated ancestry tree; relies heavily on helper functions.
    struct person_t *anne_p = make_person("Anne", "Person", 1990);
    struct ancestry_node_t *anne_tree = make_tree(anne_p);

    // Parents
    add_mom(anne_tree, make_person("Annemor", "Person", 1970));
    add_dad(anne_tree, make_person("Annefar", "Person", 1969));

    // Grandparents on mom's side
    add_mom(anne_tree->mom, make_person("Annemormor", "Person", 1950));
    add_dad(anne_tree->mom, make_person("Annemorfar", "Person", 1945));

    // Grandparents on dad's side
    add_mom(anne_tree->dad, make_person("Annefarmor", "Person", 1949));
    add_dad(anne_tree->dad, make_person("Annepharphar", "Person", 1944));

    print_tree(anne_tree);
}