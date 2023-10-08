#include "sortingFunctions.h"

int particiona(std::string*, int, int);

void bubbleSort(std::string *vet, int n){
    std::string aux;
    for(int i = 0; i<n;i++){
        for(int j = 0; j < n-i-1; j++){
            if(vet[j+1] < vet[j]){
                aux = vet[j];
                vet[j] = vet[j+1];
                vet[j+1] = aux;
            }
        }
    }
}

void selectionSort(std::string *vet, int n){
    int menor;
    std::string aux;
    for(int i = 0; i < n-1; i++){
        menor = i;
        for(int j = (i+1); j < n; j++){
            if(vet[j] < vet[menor]){
                menor = j;
            }
        }
        aux = vet[i];
        vet[i] = vet[menor];
        vet[menor] = aux;
    }
}

void insertionSort(std::string *vet, int n){
    std::string aux;
    int j;
    for(int i = 1; i < n; i++){
        aux = vet[i];
        for(j=i-1; (j >=0) && (vet[j] > aux); j--){
            vet[j+1] = vet[j];
        }
        vet[j+1] = aux;
    }
}

void shellSort(std::string *vet, int n){
    std::string aux;
    int h,j;
    h = n/2;
    while(h >= 1){
        for(int i = 1; i < n; i++){
            aux = vet[i];
            for(j=i-h; (j >=0) && (vet[j] > aux); j-=h){
                vet[j+h] = vet[j];
            }
            vet[j+h] = aux;
        }
        h = h/2;
    }
}


void mergeIntercala(std::string *vet,std::string *aux,int ini,int meio,int fin){
    int atual, finEsq, n;
    atual = ini;
    finEsq = meio-1;
    n = fin - ini + 1;

    while((ini <= finEsq) && (meio <= fin)){
        if(vet[ini] <= vet[meio]){
            aux[atual++] = vet[ini++];
        }else{
            aux[atual++] = vet[meio++];
        }
    }
    while(ini<=finEsq){
        aux[atual++] = vet[ini++];
    }
    while(meio <= fin){
        aux[atual++] = vet[meio++];
    }
    for(int i = 0; i<n;i++){
        vet[fin] = aux[fin];
        fin--;
    }
}

void mergeDivide(std::string *vet, std::string *aux, int ini, int fin){
    int meio;
    if(fin > ini){
        meio = (fin+ini)/2;
        mergeDivide(vet,aux,ini,meio);
        mergeDivide(vet,aux,meio+1,fin);
        mergeIntercala(vet,aux,ini,meio+1,fin);
    }
}
void mergeSort(std::string *vet, int n){
    std::string aux[n];
    mergeDivide(vet, aux,0,n-1);
}


int particiona(std::string *vet, int esq, int dir){
    int i, j;
    std::string aux, pivo;
    i = esq;
    j = dir;
    pivo = vet[esq];
    while(i<j){
        while((vet[i] <= pivo)&&(i < dir)){
            i++;
        }
        while((vet[j] >= pivo)&&(j>esq)){
            j--;
        }
        if(i<j){
            aux = vet[j];
            vet[j] = vet[i];
            vet[i] = aux;
        }
    }
    vet[esq] = vet[j];
    vet[j] = pivo;
    return j;
}

void quickSort(std::string *vet, int esq, int dir){
    if(esq < dir){
        int pivo = particiona(vet,esq,dir);
        quickSort(vet,esq,pivo-1);
        quickSort(vet,pivo+1,dir);
    }
}
