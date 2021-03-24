// Copyright 2020 ZinaidaCebotari

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100

struct info{
    char *info;
};

struct node {
    char *data;
    struct node *next;
};

struct list {
    struct node *head;
    int size;
};

struct hashtable {
    struct list *buckets;
    int hmax;
};

/* Aceasta functie initializeaza hashtable. */
void init(struct hashtable *h, int max) {
    h->hmax = max;
    h->buckets = malloc(h->hmax * sizeof(struct list));
    for (int i = 0; i < h->hmax; i++) {
        h->buckets[i].head = NULL;
        h->buckets[i].size = 0;
    }
}

/* Aceasta  este functia de hash. */
int hash_function(char v[MAX], int hmax) {
    int index;
    index  = strlen(v) % hmax;
    return index;
}

void put(struct hashtable *h, char v[MAX]) {
    int i = 0, index;
    /* Apelez functia de hash pentru a calcula indexul vectorului, unde 
    ar trebui s-a salvez stringul. */
    index = hash_function(v, h->hmax);

    /* Cat timp bucketul nu este gol, indexul se incrementeaza. */
    while (h->buckets[index].head != NULL) {
        /* Verific daca stringul salvat coincide cu stringul pe care trebuie sa-l adaug,
        * daca este asa, doar trebuie sa incrementez size, care reprezinta numarul de 
        * aparitii a stringului respectiv., retin pozitia in i. */
        if (strcmp(h->buckets[index].head->data, v) == 0) {
            i = index;
            index++;
        } else if (index == h->hmax - 1) {
        /* Daca de la index in colo, s-a cautat un bucket in care nu a fost salvat un string si
        * nu s-a gaist, atunci indexul se egaleaza cu 0 si cauta de la inceputul bucketului. */
            index = 0;
        } else {
            index++;
        }
    }

    /* Verific daca bucketul nu este nul in pozitia i, daca da, atunci incrementez 
    * doar size, altfel, salvez stringul intr-un bucket liber. */
    if (h->buckets[i].head != NULL) {
        h->buckets[i].size = h->buckets[i].size + 1;
    } else {
        h->buckets[index].head = malloc(sizeof(struct node));
        h->buckets[index].head->data = malloc(strlen(v) + 1);
        memcpy(h->buckets[index].head->data, v, strlen(v) + 1);
        h->buckets[index].head->next = NULL;
        h->buckets[index].size = h->buckets[index].size + 1;
    }
}

int main() {
    FILE *f;
    int count = 0;
    char v[MAX];
    struct hashtable *h = malloc(sizeof(struct hashtable));

    f = fopen("in.txt", "w+");

    /* Citesc toate stringurile de la stdin si le salvez intr-un fisier,
    * in paralel numar cate stringuri sunt pentru ca s-a stabilesc valoarea
    * lui hmax. */
    while (fscanf(stdin, "%s", v) != EOF) {
        fprintf(f, "%s%c", v, '\n');
        count++;
    }

    /* Initializez hashtable. */
    init(h, count);
    fseek(f, 0, SEEK_SET);

    /* Citesc fiecare string din fisier si il adaug in hashtable */
    for (int i = 0; i < count; i++) {
        fscanf(f, "%s", v);
        put(h, v);
    }

    /* Afisez stringurile din hashtable si numarul lor. */
    for (int i = 0; i < count; i++) {
        if (h->buckets[i].head != NULL) {
            printf("%s", h->buckets[i].head->data);
            printf(" %d\n", h->buckets[i].size);
        }
    }

    /* Eliberez toata memoria alocata. */
    for (int i = 0; i < h->hmax; i++) {
        if (h->buckets[i].head != NULL) {
            free(h->buckets[i].head->data);
        }

        free(h->buckets[i].head);
    }

    free(h->buckets);
    free(h);
    fclose(f);
    return 0;
}
