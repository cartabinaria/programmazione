#include <iostream>
using namespace std;

struct list {
    char nome[50];
    int quantita;
    double prezzo;
    list *next;
};

typedef list *plist;

plist rimuovi_quantita(plist magazzino, char nome[]) {
    plist p = magazzino;
    plist prec = NULL;
    bool found = false;
    while (p != NULL && !found) {
        if (strcmp(p->nome, nome) == 0) {
            found = true;
        } else {
            prec = p;
            p = p->next;
        }
    }
    if (found) {
        p->quantita--;
        if (p->quantita == 0) {
            if (prec == NULL) {
                magazzino = p->next; // faccio puntare la testa al secondo elemento
            } else {
                prec->next = p->next; // faccio puntare il precedente al successivo
            }
            delete p; // elimino l'elemento in memoria
        }
    }
    return magazzino;
}

double valore_magazzino(plist magazzino) {
    double valore = 0;
    plist p = magazzino;
    while (p != NULL) {
        valore += p->quantita * p->prezzo;
        p = p->next;
    }
    return valore;
}

void nome_prodotto(plist magazzino, char nome[]) {
    plist p = magazzino;
    int max = 0;
    while (p != NULL) {
        if (p->quantita > max) {
            max = p->quantita;
            strcpy(nome, p->nome);
        }
        p = p->next;
    }
}