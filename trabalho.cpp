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
#include "sortingFunctions.h"

#define TAM 10


void initializeVector(std::string *vec, std::ifstream& file ,int tam){
  int i = 0;
  if(file.is_open()){
    while((i < tam) && (file.good())){
      std::getline(file, vec[i]);
      //file >> vec[i];
      i++;
    }
  }
}

void imprime(std::string *vet, int tam){
    for(int i = 0; i<tam;i++){
      std::cout << vet[i] << ", ";
    }
}


int main(void){
    //abrindo o arquivo
    std::ifstream aurelio;
    aurelio.open("arquivos/aurelio40000.txt");

    std::ofstream output;
    output.open("arquivos/output.txt", std::ofstream::out | std::ofstream::trunc );
    if (output.is_open()){
      std::cout << "Output funcionando." << std::endl;
    }


    //inicialização dos vetores
    std::string vet1k[1000], vet5k[5000], vet10k[10000]
      ,vet20k[20000], vet30k[30000], vet40k[40000];

    //sorts com bubbleSort
    std::cout << "====BUBBLE SORT 1k====" << std::endl;
    output << "====BUBLE SORT 1k====\n";
    for (int i = 0; i <= 10; i++){
      initializeVector(vet1k, aurelio, 1000);
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
    for (int i = 0; i < 6; i++)


    aurelio.close();
    output.close();
    return 0;
}
