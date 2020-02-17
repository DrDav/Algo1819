# Corso di Algoritmica A.A. 2019/20 - Laboratorio
Questa repository contiene materiale utile per (principalmente la parte di laboratorio del) corso di Algoritmica dell'Università di Pisa.

### (!) Tutti i file qui presenti possono essere portati _stampati_ all'esame di _laboratorio_.

Sono presenti alcuni esercizi interessanti svolti più altre risorse utili per apprendere e padroneggiare al meglio gli algoritmi e la loro implementazione C.  
Le cartelle `Lezione*` contengono alcuni esercizi significativi svolti dal [portale degli esercizi di laboratorio](http://algo1819.dijkstra.di.unipi.it).

Tutti i codici sono compilabili con il solo `gcc` senza bisogno di altri tool o IDE.

## Temi d'Esame ed Esercizi Svolti
Nella cartella principale del repository ci sono alcuni file in formato PDF che contengono circa 40 esercizi svolti e commentati del modulo di _teoria_ (suddivisi in prima parte, che comprende tutti gli algoritmi di ordinamento, e seconda parte, dall'hashing fino alla fine del corso). Inoltre sono presenti le soluzioni in pseudocodice di alcuni esami di laboratorio, volti a favorire una migliore comprensione della loro implementazione che a sua volta si trova nella cartella **Esami Svolti**.

## Algoritmi Base
La cartella _Algoritmi Base_ contiene la trascrizione C di molti degli pseudocodici visti a lezione. Si consiglia di leggere tutti i commenti presenti nel codice per una migliore comprensione di tutti i dettagli e scelte implementative.
### Sorting
Per gli algoritmi di _Sorting_ sono forniti anche tre file .txt per testarli su esempi grandi e provare le diverse complessità in tempo al caso medio, ottimo e pessimo (quando queste sono diverse tra loro). Questi file contengono
- Una permutazione casuale degli interi in \[1, 100000\] (file _input_shuffled.txt_)
- Gli interi in \[1, 100000\] già ordinati (file _input_sorted.txt_) 
- Gli interi in \[1, 100000\] ordinati al contrario (file _input_reversed.txt_)

Per eseguirli con gli input da file, utilizzate `./programma < nome_del_file`.
Per cronometrarne l'esecuzione usate `time ./programma < nome_del_file`.
### Liste ed Hashing
Per le _Tabelle Hash_ forniamo due librerie che contengono le implementazioni sia della variante con liste di trabocco (`chained_hash`) sia della variante ad indirizzamento aperto (`open_hash`).

Per le _Liste_ forniamo una libreria che contiene l'implementazione delle operazioni di base su liste _monodirezionali_.

Per poter utilizzare queste librerie nei vostri esercizi:
1. Includere il file `.h` desiderato nel file del proprio esercizio con `#include "nome_file.h"`
1. Compilare il proprio esercizio con `gcc -Wall -pedantic vostro_esercizio.c file_di_libreria.c -o vostro_esercizio`.

# Link Utili
Lasciateci un feedback, proponete esercizi o argomenti da trattare al prossimo ricevimento in modo da poter preparare in anticipo del materiale utile: http://bit.ly/Algo1819A (**Corso A**), http://bit.ly/Algo1819B (**Corso B**)

Email per chiedere chiarimenti o proporre esercizi:
- n.manini@studenti.unipi.it
- d.rucci1@studenti.unipi.it
- andrealisi.12lj [chiocciola] gmail [punto] com: :octocat: [Profilo Github](https://github.com/0Alic), :duck: [Pagina personale](https://0alic.github.io/)
- c.baraglia@studenti.unipi.it


A cura di Chiara B., Andrea L., Nicolas M., Davide R.
