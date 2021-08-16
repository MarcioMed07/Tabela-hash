#include <iostream>
#include <math.h>
#include <tuple>
#define LAMBDA -1

using namespace std;

typedef int (* vFunctionCall)(int x, int k, int tamanho);

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

        Tabela(int p_tamanho){
            this->tamanho = p_tamanho;
            this->nodes = new Node[tamanho];
        };

        int Hash(int x){
            return x % this->tamanho;
        }

        std::tuple<int, int, Node> Busca(int x, vFunctionCall tratamento){
            int encontrado = 1;
            int posicao_livre = 2;
            int fim_tabela = 3;
            int k = 0;
            int end = LAMBDA;

            while (k < this->tamanho){
                end = tratamento(Hash(x), k, this->tamanho);
                
                if(this->nodes[end].chave == x){
                    return std::make_tuple(encontrado, end, this->nodes[end]);
                }
                
                if(this->nodes[end].chave == LAMBDA){
                    return std::make_tuple(posicao_livre, end, Node());
                }

                k++;                
            }
            return std::make_tuple(fim_tabela, end, Node());
        };

        std::tuple<int, int, Node> Inserir(Node node, vFunctionCall tratamento){
            int atualizado = 1;
            int inserido = 2;
            int fim_tabela = 3;
            int k = 0;

            int code, end;
            Node found_node;
            std::tie(code, end, found_node) = this->Busca(node.chave, tratamento);
            switch (code)
            {
            case 1:
                //Atualizando valor
                this->nodes[end].valor = node.valor;
                return std::make_tuple(atualizado, end, this->nodes[end]);            
            case 2:
                this->nodes[end].valor = node.valor;
                this->nodes[end].chave = node.chave;
                return std::make_tuple(inserido, end, this->nodes[end]);
            default:
                return std::make_tuple(fim_tabela, end, Node());
            }
        };

        void PrintValores(){
            printf("[");
            for(int i = 0; i < this->tamanho; i++){
                printf("%d",this->nodes[i].valor);
                if(i+1 < this->tamanho){
                    printf(",");
                }
            }
            printf("]\n");
        }

};

int tentativa_linear(int x,int k, int tamanho){
    return (x + k) % tamanho;
}

int main(int argc, char *argv[]){
    bool verbose = false;
    if(argc < 2){
        printf("Favor inserir tamanho da tabela");
        return 1;
    } 

    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "-v") {
            verbose = true;
        }
    }

    int tamanho = std::stoi(argv[1]);

    
    vFunctionCall tratamento = (vFunctionCall) tentativa_linear;    
    
    Tabela t(tamanho);
    t.Inserir(Node(4,4), tratamento);
    t.Inserir(Node(5,5), tratamento);
    t.Inserir(Node(14,14), tratamento);
    int code, endereco;
    Node node;
    std::tie(code, endereco, node) = t.Busca(14, tratamento);
    printf("Busca 14 : codigo=%d, endereco=%d\n", code, endereco);

    if(verbose){
        t.PrintValores();
    }
    return 0;
}