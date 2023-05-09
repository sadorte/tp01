#include "LZ78.hpp"

noh* noh::encontra(char d){
    std::map<char, noh*>::iterator it;
    it = filhos.find(d);
    if(it!=filhos.end()) return it->second;
    return NULL;
}

void noh::adiciona(char d, int i){
    noh *it = new noh;
    filhos[d] = it;
    it->index = i;
    it->conteudo = d;
    it->pai = this;
}

void LZ78::comprime(std::ifstream &entrada, std::ofstream &saida){
    int i = 1;
    busca[0] = &dicionario;
    noh *atual = &dicionario;
    std::string cadeia = "";
    char c;
    entrada >> std::noskipws >> c;
    while(!entrada.eof()){
        while(atual->encontra(c)!=NULL){
            atual = atual->encontra(c);
            entrada >> std::noskipws >> c;
        }
        atual->adiciona(c,i);
        busca[i] = atual->encontra(c);
        tam = i;
        i++;
        unsigned int z = atual->index;
        unsigned int x = 3;
        while(x){
            int y = 7*(x-1);
            char c = char((z>>y));
            saida.write(&c, 1);
            z-=(z>>y)<<y;
            x--;
        }
        saida.write(&c, sizeof(char));
        atual = &dicionario;
        entrada >> std::noskipws >> c;
    }
}

void LZ78::descomprime(std::ifstream &entrada, std::ofstream &saida){
    busca[0] = &dicionario;
    unsigned int j = 0;
    int i = 1;
    std::string cadeia = "";
    char c;
    while(!entrada.eof()){
        int x = 3;
        while(x){
            int y = 7*(x-1);
            char d;
            entrada.read(&d, 1);
            j+= (unsigned int)((d<<y));
            x--;
        }
        entrada.read(&c, 1);
        busca[j]->adiciona(c,i);
        tam = i;
        busca[i] = busca[j]->encontra(c);
        if(busca[i]==NULL) return;
        for(int k = i; k!=0; k=busca[k]->pai->index){
            cadeia += busca[k]->conteudo;
        }
        for(int k = cadeia.length() - 1; k >= 0; k--){
            saida.write(&cadeia[k], sizeof(char));
        }
        cadeia = "";
        i++;
        j = 0;
    }
}

void LZ78::deleta(){
    if(tam==0) return;
    for(int i = tam; i>0; i--) delete busca[i];
}