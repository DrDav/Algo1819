/*
 *
 * Esame del 25/01/2017
 *
 * Testo completo:
 * http://dijkstra.di.unipi.it/#/task/LezEsami_2015-2016Esame20170125c1/statement
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

/* Nodo di albero binario.
 * Contiene la chiave (che è una stringa)
 * e i puntatori ai figli.
 */
typedef struct _tree_node {
    char* str;
    struct _tree_node* left;
    struct _tree_node* right;
} tree_node_t;

/* Inserimento di una nuova chiave key nell'albero radicato in root.
 * Restituisce la root aggiornata.
 *
 * Tempo: O(h) = O(log n) al caso medio, O(n) al caso pessimo.
 */
tree_node_t* tree_insert(tree_node_t* root, char* key) {
    if(root == NULL) {
        tree_node_t* new = malloc(sizeof(tree_node_t));
        new->str = key;
        new->left = NULL;
        new->right = NULL;
        
        return new;
    }
    
    if(strncmp(key, root->str, MAX_LENGTH) <= 0)
        root->left = tree_insert(root->left, key);
    else
        root->right = tree_insert(root->right, key);
    
    return root;
}

/*
 * Dealloca la memoria occupata da un albero, simulandone una visita anticipata.
 */
void free_tree(tree_node_t* root) {
    if(root == NULL)
        return;
    /* Deallocazione del figlio sinistro */
    if(root->left != NULL)
        free_tree(root->left);
    /* Deallocazione del figlio destro */
    if(root->right != NULL)
        free_tree(root->right);
    /* Deallocazione del nodo corrente */
    
    free(root->str); // Dealloca anche la stringa
    free(root);
}

/*
 * Restituisce la chiave più piccola (il minimo)
 * contenuta nel sottoalbero radicato in u.
 *
 * Tempo: O(h) = O(log n) al caso medio, O(n) al caso pessimo.
 */
char* m(tree_node_t* u) {
    if(u == NULL)
        return NULL;
    
    if(u->left == NULL)
        return u->str;
    
    return m(u->left);
}

/*
 * Stampa tutti i nodi dell'albero radicato in root
 * che hanno, come prefisso della loro chiave, la chiave minima loro sottoalbero.
 *
 * Tempo: O(n^2) [inefficiente]
 */
void prefix_ineff(tree_node_t* root) {
    if(root != NULL) {
        /* Stampa tutti i prefissi del sottoalbero sinistro */
        prefix_ineff(root->left);
        
        /* Elaborazione del nodo corrente */
        char* min = m(root); // Prendiamo il minimo del nostro sottoalbero
        int len_min = strlen(min);
        int len_str = strlen(root->str);
        if(len_min <= len_str) { // Se la condizione (1) del testo è verificata
            int i = 0;
            while(i < len_min) { // Verifichiamo che sia effettivamente un prefisso
                if(min[i] != root->str[i])
                    break;
                i++;
            }
            if(i == len_min) // Se m(u) è prefisso di u allora stampiamo u->str
                printf("%s\n", root->str);
        }
        /* Stampa tutti i prefissi del sottoalbero destro */
        prefix_ineff(root->right);
    }
}

/*
 * Versione efficiente.
 * Il gioco sta nel calcolare più cose in una sola chiamata ricorsiva,
 * in particolare ogni chiamata ricorsiva restituisce anche il minimo del
 * sottoalbero radicato in root, in modo da ottenerlo con una sola visita
 * dell'albero e non con una ricerca del minimo per ogni nodo, come invece
 * avveniva sopra.
 *
 * Tempo: O(n)
 */
char* prefix(tree_node_t* root) {
    /* Se l'albero è vuoto non c'è un minimo. */
    if(root == NULL)
        return NULL;
    
    char* min;
    
    /* Il minimo del sottoalbero radicato in root
     * è il suo nodo più a sinistra.
     */
    min = prefix(root->left);
    
    if(min == NULL) {
        /* Se min è NULL vuol dire che siamo su una foglia.
         * In questo caso, secondo il testo dell'esercizio,
         * bisogna comunque stampare la chiave del nodo
         * (che è prefissa di se stessa)
         */
        printf("%s\n", root->str);
    }
    else {
        /* Se invece non siamo su una foglia, verifichiamo
         * se il minimo è prefisso di questo nodo.
         */
        int len_min = strlen(min);
        int len_str = strlen(root->str);
        if(len_min <= len_str) { // Condizione (1)
            int i = 0;
            while(i < len_min) { // Condizione (2)
                if(min[i] != root->str[i])
                    break;
                i++;
            }
            /* Se con i abbiamo esaurito min, allora min è davvero prefisso. */
            if(i == len_min)
                printf("%s\n", root->str);
        }
    }
    
    /* Proseguiamo la visita nel sottoalbero destro */
    prefix(root->right);
    
    /* Se siamo arrivati su una foglia, root è il minimo di questo sottoalbero. */
    if(root->left == NULL)
        return root->str;
    
    /* Altrimenti restituiamo il minimo alle chiamate ricorsive. */
    return min;
}

int main(void) {
    int n;
    int i;
    
    scanf("%i", &n);
    
    /* L'albero inizialmente vuoto è NULL */
    tree_node_t* root = NULL;
    
    for(i=0;i<n;i++) {
        /*
         * È importante che temp sia allocata con la malloc, in quanto poi
         * il suo puntatore viene memorizzato all'interno dell'albero.
         * Se invece allocassimo temp come array sullo stack (char temp[MAX_LENGTH])
         * questo verrebbe distrutto ad ogni nuova iterazione del ciclo
         * e non potremmo quindi salvarlo nell'albero.
         * Se invece dichiarassimo fuori dal for la variabile temp,
         * otteremo come risultato un albero contenente sempre la stessa stringa,
         * in questo caso l'ultima data in input.
         */
        char* temp = malloc((MAX_LENGTH + 1) * sizeof(char));
        
        scanf("%s", temp);
        /* Inserimento della chiave nell'albero */
        root = tree_insert(root, temp);
    }
    
    /* Stampa dei prefissi */
    prefix(root);
    
    /* Deallocazione dell'albero e delle stringhe che contiene. */
    free_tree(root);
    
    return 0;
}
