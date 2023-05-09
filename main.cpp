#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <map>
#include "LZ78.hpp"

int main(int argc, char **argv){
    int entrada, saida = 0; 
    bool compressao;
    if((!strcmp(argv[1],"-c")) || (!strcmp(argv[1],"-C"))){
        compressao = true;
    }
    else if((!strcmp(argv[1],"-x")) || (!strcmp(argv[1],"-X"))){
        compressao = false;
    }
    entrada = 2;
    if((argc>3)){
        if((!strcmp(argv[3],"-o")) || (!strcmp(argv[3],"-O"))){
            saida = 4;
        }
    }
    std::ifstream arquivo_entrada;
    std::ofstream arquivo_saida;
    arquivo_entrada.open(argv[entrada], std::ios::binary | std::ios::in);
    if(saida>0) arquivo_saida.open(argv[saida], std::ios::binary | std::ios::out);
    else{
        int i;
        for(i = 0; ; i++){
            if(argv[entrada][i]=='.') break;
        }
        std::string nome = "";
        for(int j = 0; j<=i ; j++){
            nome += argv[entrada][j];
        }
        if(compressao) nome += "z78";
        else nome += "txt";
        arquivo_saida.open(nome, std::ios::binary | std::ios::out);
    }
    LZ78 compressor;
    if(compressao) compressor.comprime(arquivo_entrada,arquivo_saida);
    else compressor.descomprime(arquivo_entrada,arquivo_saida);
    compressor.deleta();
    return 0;
}