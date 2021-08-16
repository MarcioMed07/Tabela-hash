#include <iostream>
#include <math.h>
#include <tuple>
#define LAMBDA -1

using namespace std;

typedef int (* fTratamento)(int x, int k, int tamanho, int hashed);

class Node{
    public:
        int chave;
        int valor;
        Node(){
            this->chave = LAMBDA;
            this->valor = 0;
        };
        Node(int p_chave, int p_valor){
            this->chave = p_chave;
            this->valor = p_valor;
        }
};

class Tabela{
    public:
        Node *nodes;
        int tamanho;
        double fator_carga;
        fTratamento tratamento; 

        Tabela(int p_tamanho, fTratamento p_tratamento){
            this->tamanho = p_tamanho;
            this->nodes = new Node[tamanho];
            this->tratamento = p_tratamento;
            this->fator_carga = 0.0;
        };

        int Hash(int x){
            return x % tamanho;
        }

        std::tuple<int, int, Node> Busca(int x, bool contar_colisao){
            int colisao = 0;
            int encontrado = 1;
            int posicao_livre = 2;
            int fim_tabela = 3;
            int k = 0;
            int end = LAMBDA;

            while (k < tamanho){
                end = tratamento(x, k, tamanho, Hash(x));
                
                if(nodes[end].chave == x){
                    if(contar_colisao){
                        printf("numero de colisoes=%d\n",colisao);
                    }
                    return std::make_tuple(encontrado, end, nodes[end]);
                }
                
                if(nodes[end].chave == LAMBDA){
                    return std::make_tuple(posicao_livre, end, Node());
                }

                k++;
                colisao++;                
            }
            return std::make_tuple(fim_tabela, end, Node());
        };

        std::tuple<int, int, Node> Inserir(Node node){
            int atualizado = 1;
            int inserido = 2;
            int fim_tabela = 3;
            int k = 0;

            int code, end;
            Node found_node;
            std::tie(code, end, found_node) = Busca(node.chave, false);
            switch (code)
            {
            case 1:
                //Atualizando valor
                nodes[end].valor = node.valor;
                return std::make_tuple(atualizado, end, nodes[end]);            
            case 2:
                nodes[end].valor = node.valor;
                nodes[end].chave = node.chave;
                fator_carga = fator_carga + (1.0/tamanho);
                return std::make_tuple(inserido, end, nodes[end]);
            default:
                return std::make_tuple(fim_tabela, end, Node());
            }
        };

        //TODO:  mover chaves futuras para os endereços passdos
        std::tuple<int, int, Node> Remover(int chave){
            int removido = 1;
            int nao_encontrado = 2;
            int fim_tabela = 3;
            int k = 0;

            int code, end;
            Node found_node;
            std::tie(code, end, found_node) = Busca(chave, false);
            switch (code)
            {
            case 1:
                nodes[end].valor = 0;
                nodes[end].chave = LAMBDA;
                fator_carga = fator_carga - (1.0/tamanho);
                return std::make_tuple(removido, end, nodes[end]);            
            case 2:
                return std::make_tuple(nao_encontrado, end, Node());
            default:
                return std::make_tuple(fim_tabela, end, Node());
            }
        };

        void PrintValores(){
            printf("----------\nFator de Carga: %lf\n", fator_carga);
            printf("[");
            for(int i = 0; i < tamanho; i++){
                if(nodes[i].chave == LAMBDA){
                    printf("_");
                }else{
                    printf("%d",nodes[i].valor);
                }
                if(i+1 < tamanho){
                    printf(",");
                }
            }
            printf("]\n");
        }

};

int tentativa_linear(int x,int k, int tamanho, int h){
    return (h + k) % tamanho;
}

int tentativa_quadratica(int x, int k, int tamanho, int h){
    if(k == 0){
        return h;
    }
    return (tentativa_quadratica(x,k-1,tamanho, h) + k) % tamanho;
}


//TODO: A função hash2 precisa ser melhorada
int dispersao_dupla(int x, int k, int tamanho, int h){
    int hash2 = x % (tamanho/2);
    return (h + (k*hash2)) % tamanho;
}

int main(int argc, char *argv[]){
    bool verbose = false;
    bool contar_colisao = false;
    double fator_desejado = 0;
    double fator_threshold = 0.01;
    int busca = LAMBDA;
    fTratamento tratamento = (fTratamento) tentativa_linear;

    if(argc < 2){
        printf("Favor inserir tamanho da tabela");
        return 1;
    } 

    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "-q") {
            tratamento = (fTratamento) tentativa_quadratica;
        }
        if (std::string(argv[i]) == "-d") {
            tratamento = (fTratamento) dispersao_dupla;
        }
        if (std::string(argv[i]) == "-v") {
            verbose = true;
        }
        if (std::string(argv[i]) == "-c") {
            contar_colisao = true;
        }
        if (std::string(argv[i]) == "-f") {
            fator_desejado = std::stod(std::string(argv[i + 1]));
        }
        if (std::string(argv[i]) == "-b") {
            busca = std::stoi(std::string(argv[i + 1]));
        }
    }

    int tamanho = std::stoi(argv[1]);
    
    Tabela t(tamanho, tratamento);
    while (t.fator_carga < fator_desejado)
    {
        int random = rand() % (tamanho *2);
        t.Inserir(Node(random, random));
    }
    
    if(busca != LAMBDA){
        int code, endereco;
        Node node;
        std::tie(code, endereco, node) = t.Busca(busca, contar_colisao);
        if(code == 1){
            printf("Busca %d : codigo=%d, endereco=%d\n",busca, code, endereco);
        }else{
            printf("Busca %d : codigo=%d\n",busca, code);
        }
    }

    if(verbose){
        t.PrintValores();
    }
    return 0;
}