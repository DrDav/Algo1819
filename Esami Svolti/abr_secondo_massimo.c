/*
 *
 * Esame del 09/06/2016
 *
 * Testo completo:
 * http://dijkstra.di.unipi.it/#/task/LezEsami_2015-2016Esame20160609c1/statement
 *
 */

#include <stdio.h>
#include <stdlib.h>

/* Nodo di albero (dato dal testo)
 * Contiene chiave intera e puntatori ai figli.
 */
typedef struct _node {
    int key;
    struct _node* left;
    struct _node* right;
} tree_node;

/* Inserimento di una nuova chiave key nell'albero radicato in root.
 * Restituisce la root aggiornata.
 *
 * Tempo: O(h) = O(log n) al caso medio, O(n) al caso pessimo.
 */
tree_node* tree_insert(tree_node* root, int key) {
    if(root == NULL) {
        tree_node* new = malloc(sizeof(tree_node));
        new->key = key;
        new->left = NULL;
        new->right = NULL;
        
        return new;
    }
    
    if(key <= root->key)
        root->left = tree_insert(root->left, key);
    else
        root->right = tree_insert(root->right, key);
    
    return root;
}

/*
 * Dealloca la memoria occupata da un albero, simulandone una visita anticipata.
 */
void free_tree(tree_node* root) {
    if(root == NULL)
        return;
    /* Deallocazione del figlio sinistro */
    if(root->left != NULL)
        free_tree(root->left);
    /* Deallocazione del figlio destro */
    if(root->right != NULL)
        free_tree(root->right);
    /* Deallocazione del nodo corrente */
    free(root);
}

/*
 * Ricerca del nodo contenente il massimo dell'albero radicato in root.
 * Tramite parent restituisce un puntatore al padre del massimo.
 * È necessario che parent sia passato con & dal chiamante, poiché questo verrà
 * modificato all'interno della funzione e vogliamo che le sue modifiche
 * siano visibili anche all'esterno.
 *
 * Tempo: O(h) = O(n)
 */
tree_node* maximum(tree_node* root, tree_node** parent) {
    /* Albero vuoto => nessun massimo */
    if(root == NULL)
        return NULL;
    /* Se siamo arrivati in fondo a destra, il massimo è nel nodo corrente */
    if(root->right == NULL)
        return root;

    /* Altrimenti prima di proseguire a destra, salviamo il nodo attuale
     * in parent, in modo da mantenere il puntatore al padre.
     */
    *parent = root;
    
    return maximum(root->right, parent); // Proseguiamo a destra
}

/*
 * Ricerca il secondo elemento più grande dell'albero radicato in root.
 *
 * Tempo: O(h) = O(n)
 */
int quasi_maximum(tree_node* root) {
    tree_node* parent_max = NULL;
    /* Cerchiamo il massimo di tutto l'albero */
    tree_node* max = maximum(root, &parent_max);

    /* Se il massimo ha un figlio sinistro,
     * il quasi-massimo dell'albero è il nodo più a destra nel suo
     * sottoalbero sinistro.
     */
    if(max != NULL && max->left != NULL)
        return maximum(max->left, &parent_max)->key; // Chiave del massimo
    
    /* Se invece il massimo non ha un figlio sinistro,
     * allora il quasi-massimo è il padre del massimo.
     */    
    return parent_max->key;
}

int main(void) {
    int n;
    int i;
    
    scanf("%i", &n);
    tree_node* root = NULL;
    
    for(i=0;i<n;i++) {
        /* Inserimento degli n valori all'interno dell'ABR */
        int temp;
        scanf("%i", &temp);
        root = tree_insert(root, temp);
    }


    /* Stampiamo il risultato */
    printf("%i\n", quasi_maximum(root));
    
    /* Deallochiamo l'albero */
    free_tree(root);
    
    return 0;
}
