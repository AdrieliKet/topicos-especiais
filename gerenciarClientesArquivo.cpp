#include <iostream>
#include <list>
#include <stdio.h>
using namespace std;

#include <iostream>
#include <list>
#include <stdio.h>

using namespace std;

struct Cliente {
    int id;
    string nome;
    int idade;
    int titular;
};

FILE* arquivo;

Cliente* buscar_cliente(int id) {
    Cliente* cliente = new Cliente;
    fseek(arquivo, 0, SEEK_SET);
    while (fread(cliente, sizeof(Cliente), 1, arquivo) == 1) {
        if (cliente->id == id) {
            return cliente;
        }
    }
    delete cliente;
    return NULL;
}

void cadastrar_titular() {
    Cliente novo_cliente;
    Cliente cliente;
    cout << "\nInforme o ID do cliente: ";
    cin >> novo_cliente.id;
    cout << "Informe o nome do cliente: ";
    cin >> novo_cliente.nome;
    cout << "Informe a idade do cliente: ";
    cin >> novo_cliente.idade;
    novo_cliente.titular = 0;
    // Verifica se já existe um cliente com o mesmo ID 
    while (buscar_cliente(novo_cliente.id) != NULL) {
        cout << "\nJá existe um cliente com esse ID. Tente novamente.\n";
        cout << "\nInforme o ID do cliente: ";
    	cin >> novo_cliente.id;
    }
    fseek(arquivo, 0, SEEK_END);
    fwrite(&novo_cliente, sizeof(Cliente), 1, arquivo);
    cout << "\nCliente cadastrado com sucesso!\n";
}

void visualizar_clientes() {
    Cliente cliente;
    fseek(arquivo, 0, SEEK_SET);
    cout << "\nLista de clientes cadastrados:\n";

    while (fread(&cliente, sizeof(Cliente), 1, arquivo) == 1) {
        cout << "ID: " << cliente.id << " | Nome: " << cliente.nome << " | Idade: " << cliente.idade;
        if (cliente.titular != 0) {
            cout << " | Código Titular: " << cliente.titular;
        }
        cout << endl;
    }

    if (feof(arquivo)) {
        cout << "Leitura do arquivo concluida com sucesso." << endl;
    } else if (ferror(arquivo)) {
        cout << "Ocorreu um erro durante a leitura do arquivo." << endl;
    }

}

int main() {
    arquivo = fopen("clientes.txt", "ab+");
    if (!arquivo)
    {
        cout << "Erro ao abrir o arquivo!\n";
        return 1;
    }
    
	int opcao;
	while (true) {
		cout << "\nEscolha uma opção:\n";
		cout << "1 - Cadastrar cliente\n";
		cout << "2 - Cadastrar dependente\n";
		cout << "3 - Excluir cliente\n";
		cout << "4 - Modificar cliente\n";
		cout << "5 - Visualizar clientes\n";
		cout << "6 - Sair\n";
		cin >> opcao;

		switch (opcao) {
    		case 1:
        		cadastrar_titular();
        		break;
    		case 2:
        		//cadastrar_dependente();
        		break;
    		case 3:
        		//excluir_cliente();
        		break;
    		case 4:
        		//modificar_cliente();
        		break;
    		case 5:
        		visualizar_clientes();
        		break;
    		case 6:
        		return 0;
    		default:
        		cout << "\nOpção inválida. Tente novamente.\n";
        		break;
		}
	}	
}