/*
 *
 * Esame del 04/07/2016
 *
 * Testo completo:
 * http://dijkstra.di.unipi.it/#/task/LezEsami_2015-2016Esame20160704c1/statement
 *
 */

#include <stdio.h>
#include <stdlib.h>

/* Nodo di albero binario (come dato dal testo).
 * Contiene la chiave e i puntatori ai figli.
 */
typedef struct n {
    int key;
    struct n* left;
    struct n* right;
} node;

/* Inserimento di una nuova chiave key nell'albero radicato in root.
 * Restituisce la root aggiornata.
 *
 * Tempo: O(h) = O(log n) al caso medio, O(n) al caso pessimo.
 */
node* tree_insert(node* root, int key) {
    if(root == NULL) {
        node* new = malloc(sizeof(node));
        new->key = key;
        new->left = NULL;
        new->right = NULL;
        
        return new;
    }
    
    if(key < root->key)
        root->left = tree_insert(root->left, key);
    else
        root->right = tree_insert(root->right, key);
    
    return root;
}

/*
 * Dealloca la memoria occupata da un albero, simulandone una visita anticipata.
 */
void free_tree(node* root) {
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

/* Lowest Common Ancestor.
 * Assume che x e y siano presenti nell'albero.
 *
 * Tempo: O(h)
 */
int lca(node* root, int x, int y) {
    if (root == NULL)
        return -1;

    /* L'LCA di x e y è il primo nodo incontrato che ha chiave compresa tra x e y.
     * Per questo scendiamo a sinistra se x e y sono maggiori della chiave,
     * oppure a destra se x e y sono minori della chiave.
     */
    if (root->key > x && root->key > y)
        return lca(root->left, x, y);
    
    if (root->key < x && root->key < y)
        return lca(root->right, x, y);
    
    /* Se le condizioni sopra non sono verificate allora
     * ci troviamo nel nodo (più profondo) che ha chiave compresa tra x e y
     * e che quindi è l'LCA cercato.
     */
    return root->key;
}

int main(void) {
    int n;
    
    scanf("%i", &n);
    
    /* L'albero inizialmente vuoto deve essere NULL */
    node* root = NULL;
    int i;
    
    /* Inserimento delle chiavi nell'albero */
    for(i=0;i<n;i++) {
        int tmp;
        scanf("%i", &tmp);
        root = tree_insert(root, tmp);
    }
    
    /* Lettura di x e y */
    int x, y;
    scanf("%i %i", &x, &y);
    
    /* Stampa del LCA tra x e y */
    printf("%i\n", lca(root, x, y));
    
    /* Deallocazione dell'albero */
    free_tree(root);
}
