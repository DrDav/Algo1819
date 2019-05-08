/*
 * Esame del 25/07/2016
 *
 * Testo dell'esame completo:
 * http://dijkstra.di.unipi.it/#/task/LezEsami_2015-2016Esame20160725c1/statement
 */

#include <stdio.h>
#include <stdlib.h>

/* Nodo di un albero:
 * Contiene la chiave (key),
 * un puntatore al figlio sinistro (left),
 * un puntatore al figlio destro (right).
 */
typedef struct _tree_node {
    int key; // Chiave
    struct _tree_node* left; // Figlio sinistro
    struct _tree_node* right; // Figlio destro
} tree_node_t;

/*
 * Procedura ricorsiva per l'inserimento di k
 * nell'albero la cui radice è root.
 *
 * Tempo: O(log n) al caso medio, O(n) al caso pessimo.
 */
tree_node_t* abr_insert(tree_node_t* root, int k) {
    /* Se l'albero è vuoto restituiamo il nuovo (e unico) nodo. */
    if(root == NULL) {
        tree_node_t* new = malloc(sizeof(tree_node_t));
        new->key = k;
        new->left = NULL;
        new->right = NULL;
        return new;
    }
    
    if(k <= root->key) {
        /* Se k è minore della radice, appendiamo k alla sua sinistra. */
        root->left = abr_insert(root->left, k);
    }
    else {
        /* Altrimenti a destra */
        root->right = abr_insert(root->right, k);
    }
    /* Restituiamo la radice modificata con il nuovo figlio */
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
    free(root);
}

/*
 * Procedura ricorsiva per estrarre la mediana da un albero binario di ricerca.
 *
 * La mediana sarà contenuta nel parametro output (passato come puntatore)
 * perché la funzione deve utilizzare il meccanismo di return per calcolare
 * il numero di nodi finora visitati.
 * La strategia infatti è quella di sfruttare il fatto che la visita simmetrica
 * di un ABR produce la sequenza di chiavi ordinate. Poiché, se le chiavi sono
 * ordinate, la loro mediana è l'(n/2)-esimo elemento, bisogna tener traccia
 * tramite un parametro (count) del numero di nodi visitati.
 * La chiave da restituire è quella che corrisponde al (n/2)-esimo nodo visitato.
 *
 * Tempo: O(n) perché ogni nodo viene visitato una volta sola.
 * Spazio: O(n) per la ricorsione.
 */
int mediana(tree_node_t* root, int count, int n, int* output) {
    /* Se abbiamo già visto più della metà dei nodi non è necessario proseguire */
    if(count > n/2 || count < 0)
        return -1;
    
    /* Visita simmetrica: contiamo prima il numero di nodi contenuti nel
     * sottoalbero sinistro.
     */
    if(root->left != NULL) {
        count = mediana(root->left, count, n, output);
    }
    /* Se il nodo corrente è il (n/2)-esimo abbiamo trovato la soluzione.
     * Restituiamo quindi la chiave di questo nodo tramite il puntatore output
     * e restituiamo (tramite return) n/2 + 1, in modo da far terminare tutte
     * le altre chiamate ricorsive ed evitare che altre chiamate passino
     * da questo if.
     */
    if(count == n/2) {
        *output = root->key;
        return count + 1;
    }
    /* Arrivati qua aggiorniamo count,
     * perché abbiamo appena visitato un nodo in più.
     */
    count++;
    
    /*
     * Visita simmetrica: proseguiamo la visita a destra aggiornando
     * count col numero di nodi nel sottoalbero destro.
     */
    if(root->right != NULL) {
        count = mediana(root->right, count, n, output);
    }
    
    return count;
}

int main(void) {
    int n;
    int i;
    
    scanf("%i", &n);
    tree_node_t* root = NULL;
    
    for(i=0;i<n;i++) {
        /* Inserimento degli n valori all'interno dell'ABR */
        int temp;
        scanf("%i", &temp);
        root = abr_insert(root, temp);
    }
    
    int result;
    /* Poiché non ci serve conoscere il numero di nodi nell'albero,
     * invochiamo mediana senza salvare il valore che restituisce.
     */
    mediana(root, 0, n, &result);
    
    /* Stampiamo la mediana */
    printf("%i\n", result);
    
    /* Deallochiamo l'albero */
    free_tree(root);
    
    return 0;
}
