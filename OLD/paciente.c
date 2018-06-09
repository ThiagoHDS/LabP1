#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paciente.h"

struct paciente{

	char nome[100], endereco[100], idade[10];
	int cpf, id;

};

Paciente *cria_paciente(int id, char nome[100],char idade[10], long int cpf, char endereco[100]){

    Paciente* paciente = (Paciente*) malloc(sizeof(Paciente));

    strcpy(paciente -> nome, nome);
    strcpy(paciente -> idade, idade);
    paciente -> id = id;
    paciente -> cpf = cpf;
    strcpy(paciente -> endereco, endereco);

    return paciente;
}

char* pacienteGetIdade(Paciente *paciente){
	return paciente -> idade;
}

void pacienteSetIdade(Paciente *paciente, char idade[10]){
	strcpy(paciente -> idade, idade);
}

int pacienteGetId(Paciente *paciente){
	return paciente -> id;
}

void pacienteSetId(Paciente *paciente, int id){
	paciente -> id = id;
}

long int pacienteGetCpf(Paciente *paciente){
	return paciente -> cpf;
}

void pacienteSetCpf(Paciente *paciente, long int cpf){
	paciente -> cpf = cpf;
}

char* pacienteGetNome(Paciente *paciente){
	return paciente -> nome;
}

void pacienteSetNome(Paciente *paciente, char nome[100]){
	strcpy(paciente -> nome, nome);
}

char* pacienteGetEndereco(Paciente *paciente){
	return paciente -> endereco;
}

void pacienteSetEndereco(Paciente *paciente, char endereco[100]){
	strcpy(paciente -> endereco, endereco);
}

void pacienteToString(Paciente *paciente){
	printf("Nome: %s\n",      paciente -> nome);
    printf("Idade: %s\n",     paciente -> idade);
    printf("Id: %d\n",        paciente -> id);
    printf("CPF: %d\n",       paciente -> cpf);
    printf("Endereco: %s\n",  paciente -> endereco);
}
