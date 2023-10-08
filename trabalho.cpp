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
#include <vector>
#include<ctime>
#include<iostream>
#include <fstream>
#include <chrono>
#include "sortingFunctions.h"

#define TAM 10


void initializeVector(std::vector<std::string>& vec, std::ifstream& file , int tam){
  int i = 0;
  file.clear();
  file.seekg (0, std::ios::beg);
  if(file.is_open()){
    while((i < tam) && (file.good())){
      std::string line;
      std::getline(file, line);
      vec.push_back(line);
      i++;
    }
  }
}

void imprime(std::vector<std::string> vec){
    for(int i = 0; i<vec.size();i++){
      std::cout << vec[i] << ", ";
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
    std::vector<std::string> vet1k, vet5k, vet10k, vet20k, vet30k, vet40k;
    initializeVector(vet1k, aurelio, 1000);
    initializeVector(vet5k, aurelio, 5000);
    initializeVector(vet10k, aurelio, 10000);
    initializeVector(vet20k, aurelio, 20000);
    initializeVector(vet30k, aurelio, 30000);
    initializeVector(vet40k, aurelio, 40000);
    std::cout << "Vetores inicializados com valores." << std::endl;
    std::vector<std::vector<std::string>> wordVectors= {vet1k, vet5k, vet10k, vet20k, vet30k, vet40k};
    std::cout << "Vetor de vetores inicializado." << std::endl;
 
    //0-5: bubble, seletion, insert, shell, merge, quick    
    typedef void (*SortFunction) (std::vector<std::string>&, int);
    SortFunction* sortingFunctions = getSortingFunctions(); 
    std::string* functionNames = getFunctionNames();


    //loop que itera sobre as 6 funcoes de ordenacao(i);
    //em cada um dos 6 tamanhos de vetor (j);
    //fazendo 10 rodadas e tirando as medias do benchmark (k)
    for(int i = 0; i < 6; i++){
      for (int j = 0; j < 6; j++){
        std::cout << "=====" <<  functionNames[i] << " " << wordVectors[j].size() << "====="<< std::endl;
        output <<  "=====" <<  functionNames[i] << " " << wordVectors[j].size() << "=====" << "\n";

        int avg = 0;
        for (int k = 0; k < 10; k++){
          std::vector<std::string> vec = wordVectors[j];

          std::cout << "Benchmark " << k << ": ";
          output << "Benchmark " << k << ": ";

          auto start = std::chrono::high_resolution_clock::now();
          sortingFunctions[i](vec, wordVectors[j].size());
          auto end = std::chrono::high_resolution_clock::now();

          auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
          std::cout << duration.count() << " microseconds" << std::endl;
          output << duration.count() << "\n";
          avg += duration.count();
        }
        avg /= 10;
        std::cout << "Media: " << avg << " microsegundos" << std::endl;
        output << "Media: " << avg;
      }
    }


    aurelio.close();
    output.close();
    return 0;
}
