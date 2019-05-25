#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH 100

/* Elemento contenuto nella tabella hash (coppia <nome oggetto, valore affettivo>) */
typedef struct _item {
    char* name; // Nome dell'oggetto
    int value; // Valore affettivo dell'oggetto
} item;

/* Lista di trabocco: contiene un puntatore all'elemento che contiene
 * e un puntatore all'elemento successivo nella lista.
 */
typedef struct _itemlist {
    item* info; // Elemento contenuto (chiave + valore)
    struct _itemlist *next; // Successore
} itemlist;

/* Funzione hash richiesta dal testo */
int hash(char* key, int N) {
    int i = 0, sum = 0;
    while(key[i] != '\0') {
		sum += (unsigned int) key[i];
		i++;
	}
    
    return sum % (2 * N); // 2*N è la dimensione della tabella hash richiesta dal testo
}

/* Ricerca nella tabella hash dell'elemento di chiave key.
 * Restituisce NULL se l'elemento cercato non è presente nella tabella,
 * altrimenti il valore associato alla chiave cercata.
 */
item* hash_search(itemlist **table, char* key, int N){
    itemlist *curr = table[hash(key, N)];
    /* Scorriamo la lista di trabocco alla ricerca della chiave key, se c'è */
    while(curr != NULL && strncmp(curr->info->name, key, MAX_LENGTH) != 0)
        curr = curr->next;
    
    /* Se curr è diventato NULL, la chiave non è presente in tabella */
    if(curr == NULL)
        return NULL;
    
    return curr->info;
}

/* Inserimento di un nuovo elemento nella tabella hash table.
 * Si noti che viene ricevuta in input una variabile di tipo item,
 * cioè la coppia (chiave, valore)
 */
void hash_insert(itemlist **table, item *elem, int N) {
    /* Prima di tutto controlliamo se l'elemento era già presente in tabella */
    item *temp = hash_search(table, elem->name, N);
    /* Se non c'era lo inseriamo */
    if (temp == NULL) {
        /* Creazione di un nuovo blocco di lista, contenente il nuovo elemento */
        itemlist *e = malloc(sizeof(itemlist));
        e->info = elem;
        /* Inseriamo in testa, quindi il successore del nuovo elemento sarà
         * la vecchia testa, ottenibile accedendo alla tabella in posizione
         * hash(chiave)
         */
        e->next = table[hash(elem->name, N)];
        /* La nuova lista di trabocco adesso parte dal nuovo blocco */
        table[hash(elem->name, N)] = e;
    }
    else if (temp->value < elem->value) {
        /* Se l'elemento era già presente, ma con un valore affettivo più basso,
         * cambiamo solo il valore con quello nuovo.
         * Si noti che bisogna deallocare la memoria puntata dalla variabile
         * elem, perché questa è stata allocata dal main ma non viene
         * effettivamente inserita in tabella.
         */
        temp->value = elem->value;
        free(elem->name); // Liberiamo anche la stringa chiave
        free(elem);
    }
    else {
        /* Se stiamo inserendo un elemento con la stessa chiave ma con
         * valore affettivo più basso, non dobbiamo fare niente.
         * Quindi liberiamo la memoria allocata dal main per il nuovo elemento
         * (che non è stato inserito).
         */
        free(elem->name); // Liberiamo anche la stringa chiave
        free(elem);
    }
}

/* Funzione di utilità che copia tutte le liste di trabocco della tabella table
 * in un'array di coppie (chiave, valore)
 * in modo da poterle successivamente ordinare
 */
int table_to_array(itemlist** table, item* arr, int N){
    int i, j = 0;
    itemlist *curr;
    for(i = 0; i < 2*N; i++){
        curr = table[i];
        while(curr != NULL) {
            arr[j].name = curr->info->name;
            arr[j].value = curr->info->value;
            j++;
            curr = curr->next;
        }
    }
    /* Restituisce la lunghezza dell'array arr, ovvero il numero di
     * elementi distinti nell'input
     */
    return j;
}

/* Funzione di confronto tra due elementi di tipo item (per qsort).
 * Confronta gli elementi per campo "value" (quindi per valore affettivo)
 * e in caso questi siano uguali restituisce il risultato del confronto
 * lessicografico
 */
int cmpfunc(const void* a, const void* b){
    item val_a = *(item*)a;
    item val_b = *(item*)b;
    
    int res =  val_b.value - val_a.value ;
    if (res == 0)
        res = strncmp(val_a.name, val_b.name, MAX_LENGTH);
    
    return res;
}

int main()
{
    int i, count, N;
    item *elem;
    itemlist **table;
    char *in_str;
   
    scanf("%d", &N);
    table = malloc(sizeof(itemlist*) * 2 * N);
    
    /* Azzeramento della memoria per la tabella hash.
     * Previene i "conditional jump error" in Valgrind
     * (su alcuni sistemi operativi può anche dare segmentation fault
     * se non viene fatto questo ciclo.
     */
    for(i = 0; i < 2 * N; i++)
        table[i] = NULL;
    
    /* Lettura dell'input */
    for(i = 0; i < N; i++) {
        elem = malloc(sizeof(item)); // Nuovo elemento della lista di trabocco
        in_str = malloc(sizeof(char) * (MAX_LENGTH + 1)); // +1 per il '\0'
        
        scanf("%s", in_str);
        elem->name = in_str; // Chiave
        scanf("%d", &elem->value); // Valore (affettivo)
        
        hash_insert(table, elem, N);
    }

    /* La variabile elem viene riutilizzata per creare un array
     * in cui verranno copiate tutte le liste di trabocco
     * per poi ordinarle successivamente.
     */
    elem = (item*)malloc(sizeof(item) * N);
    
    /* Trascrive tutte le liste di trabocco (tutta la tabella hash)
     * nell'array elem. Dentro count si trova la lunghezza effettiva dell'array,
     * ovvero il numero di elementi distinti che erano contenuti nell'input.
     */
    count = table_to_array(table, elem, N);
    
    /* Ordina l'array elem per valore effettivo,
     * a parità di questo in ordine lessicografico.
     */
    qsort(elem, count, sizeof(item), cmpfunc);
    
    /* Stampa dei primi 15 elementi più importanti.
     * Se ci sono meno di 15 elementi ce ne possiamo accorgere controllando
     * che i sia < count.
     */
    for(i = 0; i < 15 && i < count; i++)
        printf("%s\n", elem[i].name);
    
    /* Deallocazione della memoria */
    for(i = 0; i < 2 * N; i++) {
        itemlist* curr = table[i];
        while(curr != NULL) {
            itemlist* tmp = curr; // Salva l'elemento corrente della lista
            item* tmp_info = curr->info; // Salva la coppia (chiave, val) corrente
            curr = curr->next; // Avanza nella lista di trabocco
            free(tmp_info->name); // Dealloca la stringa (chiave)
            free(tmp_info); // Dealloca la coppia
            free(tmp); // Dealloca l'elemento della lista
        }
    }
        
    free(table); // Dealloca la tabella hash
    free(elem); // Dealloca l'array utilizzato per ordinare le coppie

    return 0;
}
