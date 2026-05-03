#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "poligono.h"

#include "../estruturas/fila.h"
#include "../formas/linha.h"

typedef struct {
    double x;
    double y;
} Vertice;

typedef struct {
    FILA vertices;
    int n;
} PoligonoSt;

POLIGONO criarPoligono (){
    PoligonoSt *p = malloc(sizeof(PoligonoSt));
    if (!p) return NULL;

    p->vertices = criarFila();
    p->n = 0;

    return p;
}

int insertVertice_Poligono (POLIGONO p, double x, double y) {
    if (!p)
        return -1;

    PoligonoSt *pol = (PoligonoSt *) p;

    Vertice *v = malloc (sizeof(Vertice));
        if (!v)
            return -1;

    v->x = x;
    v->y = y;

    pushFila (pol->vertices, v);
    pol->n++;

    return 1;
}

int removePrimeiroVertice_Poligono (POLIGONO p, double *x, double *y) {
    if (!p || !x || !y)
        return -1;

    PoligonoSt *pol = (PoligonoSt *) p;

    if (filaVazia (pol->vertices))
        return -1;

    Vertice *v = popFila (pol->vertices);
    
    *x = v->x;
    *y = v->y;

    free (v);
    pol->n--;

    return 1;
}

int getNumeroVertices_Poligono (POLIGONO p) {
    if (!p)
        return -1;

    return ((PoligonoSt *) p)->n;
}

int estaVazio_Poligono (POLIGONO p) {
    if (!p)
        return -1;

    return ((PoligonoSt *) p)->n == 0;
}



int getBoundingBox_Poligono (POLIGONO p, double *x, double *y, double *w, double *h) {
    if (!p || !x || !y || !w || !h)
        return -1;

    PoligonoSt *pol = (PoligonoSt *) p;
        if (filaVazia(pol->vertices))
            return -1;

    FILA temp = criarFila();

    Vertice *v = popFila(pol->vertices);

    double xmin = v->x;
    double xmax = v->x;
    double ymin = v->y;
    double ymax = v->y;

    pushFila (temp, v);

    while (!filaVazia (pol->vertices)) {
        v = popFila (pol->vertices);

        if (v->x < xmin) xmin = v->x;
        if (v->x > xmax) xmax = v->x;
        if (v->y < ymin) ymin = v->y;
        if (v->y > ymax) ymax = v->y;

        pushFila(temp, v);
    }

    while (!filaVazia (temp)) {
        pushFila (pol->vertices, popFila (temp));
    }

    killFila (temp);
    
    *x = xmin;
    *y = ymin;
    *w = xmax - xmin;
    *h = ymax - ymin;

    return 1;
}

int produzBorda_Poligono (POLIGONO p, FILA f) {
    if (!p || !f)
        return -1;

    PoligonoSt *pol = (PoligonoSt *) p;
    
    if (pol->n < 2)
        return -1;

    FILA temp = criarFila ();

    Vertice *primeiro = popFila (pol->vertices);
    Vertice *anterior = primeiro;
    pushFila (temp, primeiro);


    while (!filaVazia (pol->vertices)) {
        Vertice *atual = popFila (pol->vertices);

        double x1 = anterior->x, x2 = atual->x;
        double y1 = anterior->y, y2 = atual->y;

        LINHA l = criaLinha (0, x1, y1, x2, y2, "black");
    
        pushFila (f, l);

        pushFila (temp, atual);
        anterior = atual;
    }

    LINHA l = criaLinha(0, anterior->x, anterior->y, primeiro->x, primeiro->y, "black");
    
    pushFila (f, l);

    while (!filaVazia (temp)) {
        pushFila (pol->vertices, popFila (temp));
    }

    killFila (temp);
    
    return pol->n;
}

int hachura_Poligono (POLIGONO p, double d, char* corp, FILA f) {
    if (!p || !f) return -1;

    double x, y, w, h;
    if (getBoundingBox_Poligono(p, &x, &y, &w, &h) != 1)
        return -1;

    double yscan = y + d;

    while (yscan < y + h) {

        double intersecoes[100];
        int n = 0;

        FILA temp = criarFila();
        PoligonoSt *pol = (PoligonoSt*) p;

        Vertice *v1 = popFila(pol->vertices);
        Vertice *primeiro = v1;
        pushFila(temp, v1);

        while (!filaVazia(pol->vertices)) {
            Vertice *v2 = popFila(pol->vertices);

            if (((v1->y > yscan) != (v2->y > yscan))) {
                double xint = v1->x + (yscan - v1->y) *
                    (v2->x - v1->x) / (v2->y - v1->y);

                intersecoes[n++] = xint;
            }

            pushFila(temp, v2);
            v1 = v2;
        }

        // fechar
        Vertice *v2 = primeiro;
        if (((v1->y > yscan) != (v2->y > yscan))) {
            double xint = v1->x + (yscan - v1->y) *
                (v2->x - v1->x) / (v2->y - v1->y);

            intersecoes[n++] = xint;
        }

        // restaurar fila
        while (!filaVazia(temp))
            pushFila(pol->vertices, popFila(temp));

        killFila(temp);

        // ordenar interseções
        for (int i = 0; i < n-1; i++) {
            for (int j = i+1; j < n; j++) {
                if (intersecoes[i] > intersecoes[j]) {
                    double tmp = intersecoes[i];
                    intersecoes[i] = intersecoes[j];
                    intersecoes[j] = tmp;
                }
            }
        }

        // desenhar pares
        for (int i = 0; i < n; i += 2) {
            if (i+1 < n) {
                LINHA l = criaLinha(0,
                    intersecoes[i], yscan,
                    intersecoes[i+1], yscan,
                    corp);

                pushFila(f, l);
            }
        }

        yscan += d;
    }

    return 1;
}

int isInside_Poligono (POLIGONO p, double x, double y) {
    if (!p) return -1;

    PoligonoSt *pol = (PoligonoSt*) p;
    if (pol->n < 3) return 0;

    FILA temp = criarFila();

    Vertice *v1 = popFila(pol->vertices);
    Vertice *primeiro = v1;

    int intersecoes = 0;

    pushFila(temp, v1);

    while (!filaVazia(pol->vertices)){
        Vertice *v2 = popFila(pol->vertices);

        // teste de interseção com linha horizontal
        if (((v1->y > y) != (v2->y > y)) &&
            (x < (v2->x - v1->x) * (y - v1->y) / (v2->y - v1->y) + v1->x))
        {
            intersecoes++;
        }

        pushFila(temp, v2);
        v1 = v2;
    }

    // fechar polígono
    Vertice *v2 = primeiro;

    if (((v1->y > y) != (v2->y > y)) &&
        (x < (v2->x - v1->x) * (y - v1->y) / (v2->y - v1->y) + v1->x))
    {
        intersecoes++;
    }

    while (!filaVazia(temp))
        pushFila(pol->vertices, popFila(temp));

    killFila(temp);

    return (intersecoes % 2);
}

void limparPoligono (POLIGONO p) {
    if (!p)
        return;

    PoligonoSt *pol = (PoligonoSt *) p;

    while (!filaVazia (pol->vertices)) {
        Vertice *v = popFila (pol->vertices);
        free (v);
    }

    pol->n = 0;

    return;
}

int kill_Poligono (POLIGONO p) {
    if (!p)
        return -1;

    PoligonoSt *pol = (PoligonoSt *) p;

    limparPoligono (p);

    killFila (pol->vertices);

    free (pol);

    return 1;
}