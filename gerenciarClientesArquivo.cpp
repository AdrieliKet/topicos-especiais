#include <iostream>
#include <stdio.h>
using namespace std;


struct Cliente {
    int id = 0;
    char nome[50];
    int idade;
    int titular = 0;
    bool excluido = false;
};

FILE* arquivo;

Cliente buscar_cliente(int id) {
    Cliente cliente;
    fseek(arquivo, 0, SEEK_SET);
    while (fread(&cliente, sizeof(Cliente), 1, arquivo) == 1) {
        if (cliente.id == id && !cliente.excluido) {
            return cliente;
        }
    }
    return Cliente();
}

void cadastrar_titular() {
    Cliente novo_cliente;
    cout << "\nInforme o ID do cliente: ";
    cin >> novo_cliente.id;
    while (novo_cliente.id <= 0) {
        cout << "\nInsira um valor maior que 0.\n";
        cout << "\nInforme o ID do cliente: ";
    	cin >> novo_cliente.id;
    }
    cout << "Informe o nome do cliente: ";
    cin >> novo_cliente.nome;
    cout << "Informe a idade do cliente: ";
    cin >> novo_cliente.idade;
    novo_cliente.titular = 0;
 
    while (buscar_cliente(novo_cliente.id).id != 0) {
        cout << "\nJá existe um cliente com esse ID. Tente novamente.\n";
        cout << "\nInforme o ID do cliente: ";
    	cin >> novo_cliente.id;
    }
    fseek(arquivo, 0, SEEK_END);
    fwrite(&novo_cliente, sizeof(Cliente), 1, arquivo);
    cout << "\nCliente cadastrado com sucesso!\n";
}

void cadastrar_dependente() {
    Cliente novo_dependente;
    cout << "\nInforme o ID do dependente: ";
    cin >> novo_dependente.id;
    while (novo_dependente.id <= 0) {
        cout << "\nInsira um valor maior que 0.\n";
        cout << "\nInforme o ID do cliente: ";
    	cin >> novo_dependente.id;
    }
    cout << "Informe o nome do dependente: ";
    cin >> novo_dependente.nome;
    cout << "Informe a idade do dependente: ";
    cin >> novo_dependente.idade;

    int id_titular;
    cout << "Informe o ID do titular: ";
    cin >> id_titular;
    Cliente titular = buscar_cliente(id_titular);
    
    while (titular.id == 0) {
        cout << "\nTitular não encontrado. Tente novamente.\n";
        cout << "Informe o ID do titular: ";
        cin >> id_titular;
        titular = buscar_cliente(id_titular);
    }
       
    while (titular.titular != 0) {
        cout << "\nNão é possível cadastrar um dependente como titular. Tente novamente.\n";
        cout << "\nInforme o ID do titular: ";
        cin >> id_titular;
        titular = buscar_cliente(id_titular);
    }

    while (buscar_cliente(novo_dependente.id).id != 0) {
        cout << "\nJá existe um cliente/dependente com esse ID. Tente novamente.\n";
        cout << "\nInforme o ID do dependente: ";
        cin >> novo_dependente.id;
    }
    novo_dependente.titular = titular.id;
    fseek(arquivo, 0, SEEK_END);
    fwrite(&novo_dependente, sizeof(Cliente), 1, arquivo);
    cout << "\nDependente cadastrado com sucesso!\n";
}

void excluir_cliente() {
    int id_cliente;
    cout << "\nInforme o ID do cliente que deseja excluir: ";
    cin >> id_cliente;

    Cliente cliente = buscar_cliente(id_cliente);

    if (cliente.id == 0) {
        cout << "\nCliente não encontrado. Tente novamente.\n";
        return;
    }
    
    fseek(arquivo, 0, SEEK_SET);
    while (fread(&cliente, sizeof(Cliente), 1, arquivo) == 1) {
		if (cliente.titular == id_cliente && cliente.excluido == false) {
			cout << "\nNão é possível excluir um titular com dependentes. Remova os dependentes antes.\n";
			return;
		}
	}

 
    cliente.excluido = true;

    fseek(arquivo, -sizeof(Cliente), SEEK_CUR);
    fwrite(&cliente, sizeof(Cliente), 1, arquivo);

    cout << "\nCliente excluído com sucesso!\n";
}

void modificar_cliente() {
    int id_cliente;
    cout << "\nInforme o ID do cliente que deseja modificar: ";
    cin >> id_cliente;
    Cliente cliente = buscar_cliente(id_cliente);
    if (cliente.id == 0) {
        cout << "\nCliente não encontrado.\n";
        return;
    }
    cout << "\nInforme o novo nome do cliente: ";
    cin >> cliente.nome;
    cout << "Informe a nova idade do cliente: ";
    cin >> cliente.idade;

    fseek(arquivo, -sizeof(Cliente), SEEK_CUR);
    fwrite(&cliente, sizeof(Cliente), 1, arquivo);
    cout << "\nCliente modificado com sucesso!\n";
}

void visualizar_clientes() {
    Cliente cliente;
    fseek(arquivo, 0, SEEK_SET);
    cout << "\nLista de clientes cadastrados:\n";

    while (fread(&cliente, sizeof(Cliente), 1, arquivo) == 1) {
    	if(cliente.excluido != true) {
        	cout << "ID: " << cliente.id << " | Nome: " << cliente.nome << " | Idade: " << cliente.idade;
        	if (cliente.titular != 0) {
            	cout << " | Código Titular: " << cliente.titular;
        	}
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
    arquivo = fopen("clientes.txt", "rb+");
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
