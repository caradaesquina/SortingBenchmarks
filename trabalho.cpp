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

    std::ofstream output;
    output.open("arquivos/output.txt", std::ofstream::out | std::ofstream::trunc ); //TODO: deleta os contudos do ultimo teste
    if (output.is_open()){
      std::cout << "Output funcionando." << std::endl;
    }


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
    output << "====BUBLE SORT 1k====\n";
    for (int i = 0; i <= 10; i++){
      std::cout << "Benchmark " << i << ": ";

      //recolhe 2 timestamps: um antes e um após o retorno da funcao, 
      //a duracao da funcao eh a diferenca dos 2
      auto begin = std::chrono::high_resolution_clock::now();
      bubbleSort(vet1k, 1000);
      auto end  = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
      std::cout << duration.count() << " microseconds" << std::endl;
      if(i > 0) output << duration.count() << "\n";
    }

    std::cout << "====BUBBLE SORT 5k====" << std::endl;
    output << "====BUBBLE SORT 5k====\n";
    for (int i = 0; i <= 10; i++){
      std::cout << "Benchmark " << i << ": ";

      auto begin = std::chrono::high_resolution_clock::now();
      bubbleSort(vet5k, 5000);
      auto end  = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
      std::cout << duration.count() << " microseconds" << std::endl;
      if(i > 0) output << duration.count() << "\n";
    }
    std::cout << "====BUBBLE SORT 10k====" << std::endl;
    output << "====BUBBLE SORT 10k====\n";
    for (int i = 0; i <= 10; i++){
      std::cout << "Benchmark " << i << ": ";

      auto begin = std::chrono::high_resolution_clock::now();
      bubbleSort(vet10k, 10000);
      auto end  = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
      std::cout << duration.count() << " microseconds" << std::endl;
      if (i>0) output << duration.count() << "\n";
    }

    std::cout << "====BUBBLE SORT 20k====" << std::endl;
    output<<"====BUBBLE SORT 20k =====\n"; 
    for (int i = 0; i <= 10; i++){
      std::cout << "Benchmark " << i << ": ";

      auto begin = std::chrono::high_resolution_clock::now();
      bubbleSort(vet20k, 20000);
      auto end  = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
      std::cout << duration.count() << " microseconds" << std::endl;
      if(i > 0) output << duration.count() << "\n";
    }

    std::cout << "====BUBBLE SORT 30k====" << std::endl;
    output<<"====BUBBLE SORT 30k =====\n";
    for (int i = 0; i <= 10; i++){
      std::cout << "Benchmark " << i << ": ";

      auto begin = std::chrono::high_resolution_clock::now();
      bubbleSort(vet30k, 30000);
      auto end  = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
      std::cout << duration.count() << " microseconds" << std::endl;
      if(i > 0) output << duration.count() << "\n";
    }

    std::cout << "====BUBBLE SORT 40k====" << std::endl;
    output << "====BUBBLE SORT 40k====\n";
    for (int i = 0; i <= 10; i++){
      std::cout << "Benchmark " << i << ": ";

      auto begin = std::chrono::high_resolution_clock::now();
      bubbleSort(vet40k, 40000);
      auto end  = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
      std::cout << duration.count() << " microseconds" << std::endl;
      if(i > 0) output << duration.count() << "\n";
    }
    initializeVector(vet1k, aurelio, 1000);
    initializeVector(vet5k, aurelio, 5000);
    initializeVector(vet10k, aurelio, 10000);
    initializeVector(vet20k, aurelio, 20000);
    initializeVector(vet30k, aurelio, 30000);
    initializeVector (vet40k, aurelio, 40000);

    //selectionSort
    std::cout << "====SELECTION SORT 1k====" << std::endl;
    output << "====SELECTION SORT 1k====\n";
    for (int i = 0; i<= 10; i++){
      std::cout << "Benchmark " << i << ": ";

      auto begin = std::chrono::high_resolution_clock::now();
      selectionSort(vet1k, 1000);
      auto end = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
      std::cout << duration.count() << "microseconds" << std::endl;
      if(i > 0) output << duration.count() << "\n";
    }
    std::cout << "====SELECTION SORT 5k====" << std::endl;
    output << "====SELECTION SORT 5k====\n";
    for (int i = 0; i<= 10; i++){
      std::cout << "Benchmark " << i << ": ";

      auto begin = std::chrono::high_resolution_clock::now();
      selectionSort(vet5k, 5000);
      auto end = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
      std::cout << duration.count() << "microseconds" << std::endl;
      if(i > 0) output << duration.count() << "\n";
    }
    std::cout << "====SELECTION SORT 10k====" << std::endl;
    output << "====SELECTION SORT 10k====\n";
    for (int i = 0; i<= 10; i++){
      std::cout << "Benchmark " << i << ": ";

      auto begin = std::chrono::high_resolution_clock::now();
      selectionSort(vet10k, 10000);
      auto end = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
      std::cout << duration.count() << "microseconds" << std::endl;
      if(i > 0) output << duration.count() << "\n";
    }
    std::cout << "====SELECTION SORT 20k====" << std::endl;
    output << "====SELECTION SORT 20k====\n";
    for (int i = 0; i<= 10; i++){
      std::cout << "Benchmark " << i << ": ";

      auto begin = std::chrono::high_resolution_clock::now();
      selectionSort(vet20k, 20000);
      auto end = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
      std::cout << duration.count() << "microseconds" << std::endl;
      if(i > 0) output << duration.count() << "\n";
    }
    std::cout << "====SELECTION SORT 30k====" << std::endl;
    output << "SELECTION SORT 30k====\n";
    for (int i = 0; i<= 10; i++){
      std::cout << "Benchmark " << i << ": ";

      auto begin = std::chrono::high_resolution_clock::now();
      selectionSort(vet30k, 30000);
      auto end = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
      std::cout << duration.count() << "microseconds" << std::endl;
      if(i > 0) output << duration.count() << "\n";
    }
    std::cout << "====SELECTION SORT 40k====" << std::endl;
    output << "====SELECTION SORT 40k====\n";
    for (int i = 0; i<= 10; i++){
      std::cout << "Benchmark " << i << ": ";

      auto begin = std::chrono::high_resolution_clock::now();
      selectionSort(vet40k, 40000);
      auto end = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
      std::cout << duration.count() << "microseconds" << std::endl;
      if(i > 0) output << duration.count() << "\n";
    }
    initializeVector(vet1k, aurelio, 1000);
    initializeVector(vet5k, aurelio, 5000);
    initializeVector(vet10k, aurelio, 10000);
    initializeVector(vet20k, aurelio, 20000);
    initializeVector(vet30k, aurelio, 30000);
    initializeVector (vet40k, aurelio, 40000);

    //insertionSort
    std::cout << "====INSERTION SORT 1k====" << std::endl;
    output << "====INSERTION SORT 1k\n";
    for (int i = 0; i<= 10; i++){
      std::cout << "Benchmark " << i << ": ";

      auto begin = std::chrono::high_resolution_clock::now();
      insertionSort(vet1k, 1000);
      auto end = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
      std::cout << duration.count() << "microseconds" << std::endl;
      if(i > 0) output << duration.count() << "\n";
    }
    std::cout << "====INSERTION SORT 5k====" << std::endl;
    output << "====INSERTION SORT 5k\n";
    for (int i = 0; i<= 10; i++){
      std::cout << "Benchmark " << i << ": ";

      auto begin = std::chrono::high_resolution_clock::now();
      insertionSort(vet5k, 5000);
      auto end = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
      std::cout << duration.count() << "microseconds" << std::endl;
      if(i > 0) output << duration.count() << "\n";
    }
    std::cout << "====INSERTION SORT 10k====" << std::endl;
    output << "====INSERTION SORT 10k\n";
    for (int i = 0; i<= 10; i++){
      std::cout << "Benchmark " << i << ": ";

      auto begin = std::chrono::high_resolution_clock::now();
      insertionSort(vet10k, 10000);
      auto end = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
      std::cout << duration.count() << "microseconds" << std::endl;
      if(i > 0) output << duration.count() << "\n";
    }
    std::cout << "====INSERTION SORT 20k====" << std::endl;
    output << "====INSERTION SORT 20k\n";
    for (int i = 0; i<= 10; i++){
      std::cout << "Benchmark " << i << ": ";

      auto begin = std::chrono::high_resolution_clock::now();
      insertionSort(vet20k, 20000);
      auto end = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
      std::cout << duration.count() << "microseconds" << std::endl;
      if(i > 0) output << duration.count() << "\n";
    }
    std::cout << "====INSERTION SORT 30k====" << std::endl;
    output << "====INSERTION SORT 30k\n";
    for (int i = 0; i<= 10; i++){
      std::cout << "Benchmark " << i << ": ";

      auto begin = std::chrono::high_resolution_clock::now();
      insertionSort(vet30k, 30000);
      auto end = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
      std::cout << duration.count() << "microseconds" << std::endl;
      if(i > 0) output << duration.count() << "\n";
    }
    std::cout << "====INSERTION SORT 40k====" << std::endl;
    output << "====INSERTION SORT 40k\n";
    for (int i = 0; i<= 10; i++){
      std::cout << "Benchmark " << i << ": ";

      auto begin = std::chrono::high_resolution_clock::now();
      insertionSort(vet40k, 40000);
      auto end = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
      std::cout << duration.count() << "microseconds" << std::endl;
      if(i > 0) output << duration.count() << "\n";
    }
    initializeVector(vet1k, aurelio, 1000);
    initializeVector(vet5k, aurelio, 5000);
    initializeVector(vet10k, aurelio, 10000);
    initializeVector(vet20k, aurelio, 20000);
    initializeVector(vet30k, aurelio, 30000);
    initializeVector (vet40k, aurelio, 40000);

    //shellSort
    std::cout << "====SHELL SORT 1k====" << std::endl;
    output << "====SHELL SORT 1k\n";
    for (int i = 0; i<= 10; i++){
      std::cout << "Benchmark " << i << ": ";

      auto begin = std::chrono::high_resolution_clock::now();
      shellSort(vet1k, 1000);
      auto end = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
      std::cout << duration.count() << "microseconds" << std::endl;
      if(i > 0) output << duration.count() << "\n";
    }
    std::cout << "====SHELL SORT 5k====" << std::endl;
    output << "====SHELL SORT 5k\n";
    for (int i = 0; i<= 10; i++){
      std::cout << "Benchmark " << i << ": ";

      auto begin = std::chrono::high_resolution_clock::now();
      shellSort(vet5k, 5000);
      auto end = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
      std::cout << duration.count() << "microseconds" << std::endl;
      if(i > 0) output << duration.count() << "\n";
    }
    std::cout << "====SHELL SORT 10k====" << std::endl;
    output << "====SHELL SORT 10k\n";
    for (int i = 0; i<= 10; i++){
      std::cout << "Benchmark " << i << ": ";

      auto begin = std::chrono::high_resolution_clock::now();
      shellSort(vet10k, 10000);
      auto end = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
      std::cout << duration.count() << "microseconds" << std::endl;
      if(i > 0) output << duration.count() << "\n";
    }
    std::cout << "====SHELL SORT 20k====" << std::endl;
    output << "====SHELL SORT 20k\n";
    for (int i = 0; i<= 10; i++){
      std::cout << "Benchmark " << i << ": ";

      auto begin = std::chrono::high_resolution_clock::now();
      shellSort(vet20k, 20000);
      auto end = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
      std::cout << duration.count() << "microseconds" << std::endl;
      if(i > 0) output << duration.count() << "\n";
    }
    std::cout << "====SHELL SORT 30k====" << std::endl;
    output << "====SHELL SORT 30k\n";
    for (int i = 0; i<= 10; i++){
      std::cout << "Benchmark " << i << ": ";

      auto begin = std::chrono::high_resolution_clock::now();
      shellSort(vet30k, 30000);
      auto end = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
      std::cout << duration.count() << "microseconds" << std::endl;
      if(i > 0) output << duration.count() << "\n";
    }
    std::cout << "====SHELL SORT 40k====" << std::endl;
    output << "====SHELL SORT 40k\n";
    for (int i = 0; i<= 10; i++){
      std::cout << "Benchmark " << i << ": ";

      auto begin = std::chrono::high_resolution_clock::now();
      shellSort(vet40k, 40000);
      auto end = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
      std::cout << duration.count() << "microseconds" << std::endl;
      if(i > 0) output << duration.count() << "\n";
    }
    initializeVector(vet1k, aurelio, 1000);
    initializeVector(vet5k, aurelio, 5000);
    initializeVector(vet10k, aurelio, 10000);
    initializeVector(vet20k, aurelio, 20000);
    initializeVector(vet30k, aurelio, 30000);
    initializeVector (vet40k, aurelio, 40000);

    //mergeSort
    std::cout << "====MERGE SORT 1k====" << std::endl;
    output << "====MERGE SORT 1k\n";
    for (int i = 0; i<= 10; i++){
      std::cout << "Benchmark " << i << ": ";

      auto begin = std::chrono::high_resolution_clock::now();
      mergeSort(vet1k, 1000);
      auto end = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
      std::cout << duration.count() << "microseconds" << std::endl;
      if(i > 0) output << duration.count() << "\n";
    }
    std::cout << "====MERGE SORT 5k====" << std::endl;
    output << "====MERGE SORT 5k\n";
    for (int i = 0; i<= 10; i++){
      std::cout << "Benchmark " << i << ": ";

      auto begin = std::chrono::high_resolution_clock::now();
      mergeSort(vet5k, 5000);
      auto end = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
      std::cout << duration.count() << "microseconds" << std::endl;
      if(i > 0) output << duration.count() << "\n";
    }
    std::cout << "====MERGE SORT 10k====" << std::endl;
    output << "====MERGE SORT 10k\n";
    for (int i = 0; i<= 10; i++){
      std::cout << "Benchmark " << i << ": ";

      auto begin = std::chrono::high_resolution_clock::now();
      mergeSort(vet10k, 10000);
      auto end = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
      std::cout << duration.count() << "microseconds" << std::endl;
      if(i > 0) output << duration.count() << "\n";
    }
    std::cout << "====MERGE SORT 20k====" << std::endl;
    output << "====MERGE SORT 20k\n";
    for (int i = 0; i<= 10; i++){
      std::cout << "Benchmark " << i << ": ";

      auto begin = std::chrono::high_resolution_clock::now();
      mergeSort(vet20k, 20000);
      auto end = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
      std::cout << duration.count() << "microseconds" << std::endl;
      if(i > 0) output << duration.count() << "\n";
    }
    std::cout << "====MERGE SORT 30k====" << std::endl;
    output << "====MERGE SORT 30k\n";
    for (int i = 0; i<= 10; i++){
      std::cout << "Benchmark " << i << ": ";

      auto begin = std::chrono::high_resolution_clock::now();
      mergeSort(vet30k, 30000);
      auto end = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
      std::cout << duration.count() << "microseconds" << std::endl;
      if(i > 0) output << duration.count() << "\n";
    }
    std::cout << "====MERGE SORT 40k====" << std::endl;
    output << "====MERGE SORT 40k\n";
    for (int i = 0; i<= 10; i++){
      std::cout << "Benchmark " << i << ": ";

      auto begin = std::chrono::high_resolution_clock::now();
      mergeSort(vet40k, 40000);
      auto end = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
      std::cout << duration.count() << "microseconds" << std::endl;
      if(i > 0) output << duration.count() << "\n";
    }
    initializeVector(vet1k, aurelio, 1000);
    initializeVector(vet5k, aurelio, 5000);
    initializeVector(vet10k, aurelio, 10000);
    initializeVector(vet20k, aurelio, 20000);
    initializeVector(vet30k, aurelio, 30000);
    initializeVector (vet40k, aurelio, 40000);

    //quickSort
    std::cout << "====QUICK SORT 1k====" << std::endl;
    output << "====QUICK SORT 1k\n";
    for (int i = 0; i<= 10; i++){
      std::cout << "Benchmark " << i << ": ";

      auto begin = std::chrono::high_resolution_clock::now();
      quickSort(vet1k,0, 1000-1);
      auto end = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
      std::cout << duration.count() << "microseconds" << std::endl;
      if(i > 0) output << duration.count() << "\n";
    }
    std::cout << "====QUICK SORT 5k====" << std::endl;
    output << "====QUICK SORT 5k\n";
    for (int i = 0; i<= 10; i++){
      std::cout << "Benchmark " << i << ": ";

      auto begin = std::chrono::high_resolution_clock::now();
      quickSort(vet5k,0, 5000-1);
      auto end = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
      std::cout << duration.count() << "microseconds" << std::endl;
      if(i > 0) output << duration.count() << "\n";
    }
    
    std::cout << "====QUICK SORT 10k====" << std::endl;
    output << "====QUICK SORT 10k\n";
    for (int i = 0; i<= 10; i++){
      std::cout << "Benchmark " << i << ": ";

      auto begin = std::chrono::high_resolution_clock::now();
      quickSort(vet10k,0, 10000-1);
      auto end = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
      std::cout << duration.count() << "microseconds" << std::endl;
      if(i > 0) output << duration.count() << "\n";
    }
    std::cout << "====QUICK SORT 20k====" << std::endl;
    output << "====QUICK SORT 20k\n";
    for (int i = 0; i<= 10; i++){
      std::cout << "Benchmark " << i << ": ";

      auto begin = std::chrono::high_resolution_clock::now();
      quickSort(vet20k,0, 20000-1);
      auto end = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
      std::cout << duration.count() << "microseconds" << std::endl;
      if(i > 0) output << duration.count() << "\n";
    }
    std::cout << "====QUICK SORT 30k====" << std::endl;
    output << "====QUICK SORT 30k\n";
    for (int i = 0; i<= 10; i++){
      std::cout << "Benchmark " << i << ": ";

      auto begin = std::chrono::high_resolution_clock::now();
      quickSort(vet30k,0, 30000-1);
      auto end = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
      std::cout << duration.count() << "microseconds" << std::endl;
      if(i > 0) output << duration.count() << "\n";
    }
    std::cout << "====QUICK SORT 40k====" << std::endl;
    output << "====QUICK SORT 40k\n";
    for (int i = 0; i<= 10; i++){
      std::cout << "Benchmark " << i << ": ";

      auto begin = std::chrono::high_resolution_clock::now();
      quickSort(vet40k,0, 40000-1);
      auto end = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
      std::cout << duration.count() << "microseconds" << std::endl;
      if(i > 0) output << duration.count() << "\n";
    }

    aurelio.close();
    output.close();
    return 0;
}
