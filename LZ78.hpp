#include <map>
#include <fstream>

class noh{
    public:
    noh *pai = NULL;
    unsigned int index = 0;
    char conteudo = '0';
    std::map<char, noh*> filhos;
    noh* encontra(char d);
    void adiciona(char d, int i);
};


class LZ78{
    public:
    noh dicionario;
    std::map<int, noh*> busca;
    unsigned int tam = 0;
    void comprime(std::ifstream &entrada, std::ofstream &saida);
    void descomprime(std::ifstream &entrada, std::ofstream &saida);
    void deleta();
};