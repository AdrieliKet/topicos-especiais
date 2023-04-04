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

Cliente buscar_cliente(int id) {
    Cliente cliente = new Cliente;
    fseek(arquivo, 0, SEEK_SET);
    while (fread(cliente, sizeof(Cliente), 1, arquivo) == 1) {
        if (cliente.id == id) {
            return cliente;
        }
    }
    delete cliente;
    return NULL;
}

void cadastrar_titular() {
    Cliente novo_cliente = new Cliente;
    Cliente cliente;
    cout << "\nInforme o ID do cliente: ";
    cin >> novo_cliente.id;
    cout << "Informe o nome do cliente: ";
    cin >> novo_cliente.nome;
    cout << "Informe a idade do cliente: ";
    cin >> novo_cliente.idade;
    novo_cliente.titular = NULL;
    // Verifica se já existe um cliente com o mesmo ID 
    while (buscar_cliente(novo_cliente.id, arquivo) != NULL) {
        cout << "\nJá existe um cliente com esse ID. Tente novamente.\n";
        cout << "\nInforme o ID do cliente: ";
    	cin >> novo_cliente.id;
    }
    fseek(arquivo, 0, SEEK_END);
    fwrite(novo_cliente, sizeof(Cliente), sizeof(novo_cliente), arquivo);
    cout << "\nCliente cadastrado com sucesso!\n";
}

// void cadastrar_dependente() {
//     Cliente* novo_dependente = new Cliente;
//     cout << "\nInforme o ID do dependente: ";
//     cin >> novo_dependente->id;
//     cout << "Informe o nome do dependente: ";
//     cin >> novo_dependente->nome;
//     cout << "Informe a idade do dependente: ";
//     cin >> novo_dependente->idade;
//     // Busca o titular correspondente pelo ID 
//     int id_titular;
//     cout << "Informe o ID do titular: ";
//     cin >> id_titular;
//     Cliente* titular = buscar_cliente(id_titular, arquivo);
//     // Verifica se o titular existe 
//     while (titular == NULL) {
//         cout << "\nTitular não encontrado. Tente novamente.\n";
//         cout << "Informe o ID do titular: ";
//         cin >> id_titular;
//         titular = buscar_cliente(id_titular, arquivo);
//     }
       
//     // Verifica se é dependente, se for não deixa passar como titular
//     while (titular->titular != NULL) {
//         cout << "\nNão é possível cadastrar um dependente como titular. Tente novamente.\n";
//         cout << "\nInforme o ID do titular: ";
//         cin >> id_titular;
//         titular = buscar_cliente(id_titular, arquivo);
//     }
//     // Verifica se o titular já possui um dependente com o mesmo ID 
//     while (buscar_cliente(novo_dependente->id, arquivo) != NULL) {
//         cout << "\nJá existe um cliente/dependente com esse ID. Tente novamente.\n";
//         cout << "\nInforme o ID do dependente: ";
//         cin >> novo_dependente->id;
//     }
//     novo_dependente->titular = titular;
//     fseek(arquivo, 0, SEEK_END);
//     fwrite(&novo_dependente, sizeof(Cliente), 1, arquivo);
//     cout << "\nDependente cadastrado com sucesso!\n";
// }

// void excluir_cliente() {
// 	int id;
// 	cout << "\nInforme o ID do cliente a ser excluído: ";
// 	cin >> id;
// 	Cliente* cliente = buscar_cliente(id, arquivo);
// 	// Verifica se o cliente existe
// 	if (cliente == NULL) {
// 		cout << "\nCliente não encontrado. Tente novamente.\n";
// 		return;
// 	}
// 	// Verifica se o cliente é titular de algum dependente
// 	for (auto it = lista_clientes.begin(); it != lista_clientes.end(); it++) {
// 		if ((*it)->titular == cliente) {
// 		cout << "\nNão é possível excluir um titular com dependentes. Remova os dependentes antes.\n";
// 		return;
// 	}
// 	}
// 	lista_clientes.remove(cliente);
// 	delete cliente;
// 	cout << "\nCliente excluído com sucesso!\n";
// }


// void modificar_cliente() {
// 	int id;
// 	cout << "\nInforme o ID do cliente a ser modificado: ";
// 	cin >> id;
// 	Cliente* cliente = buscar_cliente(id, arquivo);
// 	// Verifica se o cliente existe
// 	if (cliente == NULL) {
// 		cout << "\nCliente não encontrado. Tente novamente.\n";
// 		return;
// 	}
// 	cout << "Informe o novo nome do cliente: ";
// 	cin >> cliente->nome;
// 	cout << "Informe a nova idade do cliente: ";
// 	cin >> cliente->idade;
// 	cout << "\nCliente modificado com sucesso!\n";
// }

void visualizar_clientes() {
    Cliente cliente;
    fseek(arquivo, 0, SEEK_SET);
    cout << "\nLista de clientes cadastrados:\n";

    while (fread(&cliente, sizeof(Cliente), 1, arquivo) == 1) {
        cout << "ID: " << cliente.id << " | Nome: " << cliente.nome << " | Idade: " << cliente.idade;
        //if (cliente.titular != NULL) {
            //cout << " | Titular: " << cliente.titular->nome;
        //}
        cout << endl;
    }

    if (feof(arquivo)) {
        cout << "Leitura do arquivo concluida com sucesso." << endl;
    } else if (ferror(arquivo)) {
        cout << "Ocorreu um erro durante a leitura do arquivo." << endl;
    }

    fclose(arquivo);
}

int main() {
    arquivo = fopen("clientes.dat", "ab+");
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
