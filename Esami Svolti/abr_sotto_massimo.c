/*
 *
 * Esame del 05/04/2016
 *
 * Testo completo:
 * http://dijkstra.di.unipi.it/#/task/LezEsami_2015-2016Esame20160405c1/statement
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

/* Nodo di albero binario.
 * Contiene la chiave (una stringa),
 * un valore (intero)
 * e i puntatori ai figli.
 */
typedef struct _tree_node {
    char* key;
    int value;
    struct _tree_node* left;
    struct _tree_node* right;
} tree_node_t;

/* Inserimento di una nuova chiave key nell'albero radicato in root.
 * Restituisce la root aggiornata.
 *
 * Tempo: O(h) = O(log n) al caso medio, O(n) al caso pessimo.
 */
tree_node_t* tree_insert(tree_node_t* root, char* key, int val) {
    if(root == NULL) {
        tree_node_t* new = malloc(sizeof(tree_node_t));
        new->key = key;
        new->value = val;
        new->left = NULL;
        new->right = NULL;
        
        return new;
    }
    /* La proprietà di ricerca è solo rispetto alla chiave */
    if(strncmp(key, root->key, MAX_LENGTH) <= 0)
        root->left = tree_insert(root->left, key, val);
    else
        root->right = tree_insert(root->right, key, val);
    
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
    
    free(root->key); // Dealloca anche la stringa
    free(root);
}

/*
 * Ricerca della chiave s nell'albero root.
 * Segue la proprietà di ricerca dell'albero.
 *
 * Tempo: O(h) = O(n), dove h è l'altezza di tutto l'albero.
 */
tree_node_t* find_key(tree_node_t* root, char* s) {
    if(root == NULL)
        return NULL;
    
    /* Salviamo il risultato del confronto tra s e la chiave corrente
     * per non doverlo ripetere nell'else
     */
    int cmp = strncmp(s, root->key, MAX_LENGTH);
    
    if(cmp < 0)
        return find_key(root->left, s);
    else if(cmp > 0)
        return find_key(root->right, s);
    else // Se cmp == 0 allora le due stringhe sono uguali
        return root;
}

/*
 * Ricerca del massimo valore contenuto nel sottoalbero radicato nel nodo u.
 * Si noti che questo algoritmo ignora qualsiasi proprietà dell'albero
 * (a parte quella di essere binario).
 *
 * Tempo: O(n)
 */
int find_max(tree_node_t* u) {
    if(u == NULL)
        return -1;
    
    /* Calcoliamo il massimo nei sottoalberi sinistro e destro */
    int max_left = find_max(u->left);
    int max_right = find_max(u->right);
    int max;
    /* Calcoliamo il massimo globale */
    if(max_left > max_right)
        max = max_left;
    else
        max = max_right;
    /* Confrontiamo il nostro valore col massimo del nostro sottoalbero */
    if(u->value > max)
        return u->value;
    
    return max;
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
        char* temp = malloc((MAX_LENGTH + 1) * sizeof(char)); // Chiave
        int temp_val; // Valore
        
        scanf("%s", temp);
        scanf("%i", &temp_val);
        /* Inserimento della chiave nell'albero */
        root = tree_insert(root, temp, temp_val);
    }
    
    /* Stampa del risultato */
    char s[MAX_LENGTH + 1];
    scanf("%s", s);
    
    printf("%i\n", find_max(find_key(root, s)));
    
    /* Deallocazione dell'albero e delle stringhe che contiene. */
    free_tree(root);
    
    return 0;
}
