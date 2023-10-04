//Progama realizado como Trabalho 1 da disciplina de Anáslise de Algoritimos da Universidade Federal de Itajubá
//Feito por: Henry Matherus Hagemann e Lucas Moura
//Itajubá, MG, Brasil, 2023.
//
//O programa realiza benchmarks do tempo decorrido para a ordenação de vetores contendo palavras aleatórias do dicionário Aurélio.
//São realizados 11 benchmarks por rodada, sendo que o primeiro deve ser ignorado (causa ainda não estabelecida)
//Algoritimos testados: Bubble Sort, Selection Sort, Insertion Sort, Shell Sort, Merge Sort e Quick Sort
//Foram usados vetors de 1k, 5k, 10k, 20k, 30k e 40k de palavras.
//


#include<string>
#include<ctime>
#include<iostream>
#include <fstream>
#include <chrono>

#define TAM 10

using namespace std; //má pratica, prefirir std::

void initializeVector(string *vec, std::ifstream& file ,int tam){
  int i = 0;
  if(file.is_open()){
    while((i < tam) && (file.good())){
      std::getline(file, vec[i]);
      //file >> vec[i];
      i++;
    }
  }
}

void imprime(string *vet, int tam){
    for(int i = 0; i<tam;i++){
        cout << vet[i] << ", ";
    }
}

void bubbleSort(string *vet, int n){
    string aux;
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

void selectionSort(string *vet, int n){
    int menor;
    string aux;
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

void insertionSort(string *vet, int n){
    string aux;
    int j;
    for(int i = 1; i < n; i++){
        aux = vet[i];
        for(j=i-1; (j >=0) && (vet[j] > aux); j--){
            vet[j+1] = vet[j];
        }
        vet[j+1] = aux;
    }
}

void shellSort(string *vet, int n){
    string aux;
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


void mergeIntercala(string *vet,string *aux,int ini,int meio,int fin){
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

void mergeDivide(string *vet, string *aux, int ini, int fin){
    int meio;
    if(fin > ini){
        meio = (fin+ini)/2;
        mergeDivide(vet,aux,ini,meio);
        mergeDivide(vet,aux,meio+1,fin);
        mergeIntercala(vet,aux,ini,meio+1,fin);
    }
}
void mergeSort(string *vet, int n){
    string aux[n];
    mergeDivide(vet, aux,0,n-1);
}


int particiona(string *vet, int esq, int dir){
    int i, j;
    string aux, pivo;
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
void quickSort(string *vet, int esq, int dir){
    if(esq < dir){
        int pivo = particiona(vet,esq,dir);
        quickSort(vet,esq,pivo-1);
        quickSort(vet,pivo+1,dir);
    }
}
int main(void){
    //abrindo o arquivo
    std::ifstream aurelio;
    aurelio.open("arquivos/aurelio40000.txt");

    //inicialização dos vetores
     string vet1k[1000], vet5k[5000], vet10k[10000]
      ,vet20k[20000], vet30k[30000], vet40k[40000];
    initializeVector(vet1k, aurelio, 1000);
    initializeVector(vet5k, aurelio, 5000);
    initializeVector(vet10k, aurelio, 10000);
    initializeVector(vet20k, aurelio, 20000);
    initializeVector(vet30k, aurelio, 30000);
    initializeVector (vet40k, aurelio, 40000);

    //sorts com bubbleSort
    std::cout << "====BUBBLE SORT 1k====" << std::endl;
    for (int i = 0; i <= 10; i++){
      std::cout << "Benchmark " << i << ": ";

      //recolhe 2 timestamps: um antes e um após o retorno da funcao, 
      //a duracao da funcao eh a diferenca dos 2
      auto begin = std::chrono::high_resolution_clock::now();
      bubbleSort(vet1k, 1000);
      auto end  = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
      std::cout << duration.count() << " microseconds" << std::endl;
    }

    std::cout << "====BUBBLE SORT 5k====" << std::endl;
    for (int i = 0; i <= 10; i++){
      std::cout << "Benchmark " << i << ": ";

      auto begin = std::chrono::high_resolution_clock::now();
      bubbleSort(vet5k, 5000);
      auto end  = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
      std::cout << duration.count() << " microseconds" << std::endl;
    }
    std::cout << "====BUBBLE SORT 10k====" << std::endl;
    for (int i = 0; i <= 10; i++){
      std::cout << "Benchmark " << i << ": ";

      auto begin = std::chrono::high_resolution_clock::now();
      bubbleSort(vet10k, 10000);
      auto end  = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
      std::cout << duration.count() << " microseconds" << std::endl;
    }

    std::cout << "====BUBBLE SORT 20k====" << std::endl;
    for (int i = 0; i <= 10; i++){
      std::cout << "Benchmark " << i << ": ";

      auto begin = std::chrono::high_resolution_clock::now();
      bubbleSort(vet20k, 20000);
      auto end  = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
      std::cout << duration.count() << " microseconds" << std::endl;
    }

    std::cout << "====BUBBLE SORT 30k====" << std::endl;
    for (int i = 0; i <= 10; i++){
      std::cout << "Benchmark " << i << ": ";

      auto begin = std::chrono::high_resolution_clock::now();
      bubbleSort(vet30k, 30000);
      auto end  = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
      std::cout << duration.count() << " microseconds" << std::endl;
    }

    std::cout << "====BUBBLE SORT 40k====" << std::endl;
    for (int i = 0; i <= 10; i++){
      std::cout << "Benchmark " << i << ": ";

      auto begin = std::chrono::high_resolution_clock::now();
      bubbleSort(vet40k, 40000);
      auto end  = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
      std::cout << duration.count() << " microseconds" << std::endl;
    }
    //bubbleSort(vet, TAM);
    //selectionSort(vet, TAM);
    //insertionSort(vet,TAM);
    //shellSort(vet,TAM);// -- ta bichado
    //mergeSort(vet,TAM);
    //quickSort(vet,0,TAM-1);
    


    return 0;
}
