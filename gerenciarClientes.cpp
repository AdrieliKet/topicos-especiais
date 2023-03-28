#include <iostream>
#include <list>
using namespace std;

// Definição da estrutura para cliente
struct Cliente {
    int id;
    string nome;
    int idade;
    Cliente* titular;
};

// Declaração de variáveis globais
list<Cliente*> lista_clientes;

Cliente* buscar_cliente(int id) {
    for (auto it = lista_clientes.begin(); it != lista_clientes.end(); it++) {
        if ((*it)->id == id) {
            return *it;
        }
    }
    return NULL;
}

void cadastrar_titular() {
    Cliente* novo_cliente = new Cliente;
    cout << "\nInforme o ID do cliente: ";
    cin >> novo_cliente->id;
    cout << "Informe o nome do cliente: ";
    cin >> novo_cliente->nome;
    cout << "Informe a idade do cliente: ";
    cin >> novo_cliente->idade;
    novo_cliente->titular = NULL;
    // Verifica se já existe um cliente com o mesmo ID 
    while (buscar_cliente(novo_cliente->id) != NULL) {
        cout << "\nJá existe um cliente com esse ID. Tente novamente.\n";
        delete novo_cliente;
        return;
    }
    lista_clientes.push_back(novo_cliente);
    cout << "\nCliente cadastrado com sucesso!\n";
}

// Função para cadastrar novo dependente
void cadastrar_dependente() {
    Cliente* novo_dependente = new Cliente;
    cout << "\nInforme o ID do dependente: ";
    cin >> novo_dependente->id;
    cout << "Informe o nome do dependente: ";
    cin >> novo_dependente->nome;
    cout << "Informe a idade do dependente: ";
    cin >> novo_dependente->idade;
    // Busca o titular correspondente pelo ID 
    int id_titular;
    cout << "Informe o ID do titular: ";
    cin >> id_titular;
    Cliente* titular = buscar_cliente(id_titular);
    // Verifica se o titular existe 
    while (titular == NULL) {
        cout << "\nTitular não encontrado. Tente novamente.\n";
        cout << "Informe o ID do titular: ";
        cin >> id_titular;
        titular = buscar_cliente(id_titular);
    }
       
    // Verifica se é dependente, se for não deixa passar como titular
    while (titular->titular != NULL) {
        cout << "\nNão é possível cadastrar um dependente como titular. Tente novamente.\n";
        cout << "\nInforme o ID do titular: ";
        cin >> id_titular;
        titular = buscar_cliente(id_titular);
    }
    // Verifica se o titular já possui um dependente com o mesmo ID 
    while (buscar_cliente(novo_dependente->id) != NULL) {
        cout << "\nJá existe um cliente/dependente com esse ID. Tente novamente.\n";
        cout << "\nInforme o ID do dependente: ";
        cin >> novo_dependente->id;
    }
    novo_dependente->titular = titular;
    lista_clientes.push_back(novo_dependente);
    cout << "\nDependente cadastrado com sucesso!\n";
}

void excluir_cliente() {
	int id;
	cout << "\nInforme o ID do cliente a ser excluído: ";
	cin >> id;
	Cliente* cliente = buscar_cliente(id);
	// Verifica se o cliente existe
	if (cliente == NULL) {
		cout << "\nCliente não encontrado. Tente novamente.\n";
		return;
	}
	// Verifica se o cliente é titular de algum dependente
	for (auto it = lista_clientes.begin(); it != lista_clientes.end(); it++) {
		if ((*it)->titular == cliente) {
		cout << "\nNão é possível excluir um titular com dependentes. Remova os dependentes antes.\n";
		return;
	}
	}
	lista_clientes.remove(cliente);
	delete cliente;
	cout << "\nCliente excluído com sucesso!\n";
}


void modificar_cliente() {
	int id;
	cout << "\nInforme o ID do cliente a ser modificado: ";
	cin >> id;
	Cliente* cliente = buscar_cliente(id);
	// Verifica se o cliente existe
	if (cliente == NULL) {
		cout << "\nCliente não encontrado. Tente novamente.\n";
		return;
	}
	cout << "Informe o novo nome do cliente: ";
	cin >> cliente->nome;
	cout << "Informe a nova idade do cliente: ";
	cin >> cliente->idade;
	cout << "\nCliente modificado com sucesso!\n";
}

void visualizar_clientes() {
	cout << "\nLista de clientes cadastrados:\n";
	for (auto it = lista_clientes.begin(); it != lista_clientes.end(); it++) {
		cout << "ID: " << (*it)->id << " | Nome: " << (*it)->nome << " | Idade: " << (*it)->idade;
		if ((*it)->titular != NULL) {
			cout << " | Titular: " << (*it)->titular->nome;
		}
		cout << endl;
	}
}

int main() {
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
        		cadastrar_dependente();
        		break;
    		case 3:
        		excluir_cliente();
        		break;
    		case 4:
        		modificar_cliente();
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
