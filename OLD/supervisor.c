#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "supervisor.h"

struct supervisor{

	char nome[100], curso[100];
	int id, codigo;

};

Supervisor *cria_supervisor(int id, char nome[100], char curso[100], int codigo){

    Supervisor* supervisor = (Supervisor*) malloc(sizeof(Supervisor));

	supervisor -> id = id;
	supervisor -> codigo = codigo;
    strcpy(supervisor -> nome, nome);
    strcpy(supervisor -> curso, curso);

    return supervisor;
}

int supervisorGetCodigo(Supervisor *supervisor){
	return supervisor -> codigo;
}

void supervisorSetCodigo(Supervisor *supervisor, int codigo){
	supervisor -> codigo = codigo;
}

int supervisorGetId(Supervisor *supervisor){
	return supervisor -> id;
}

void supervisorSetId(Supervisor *supervisor, int id){
	supervisor -> id = id;
}

char* supervisorGetNome(Supervisor *supervisor){
	return supervisor -> nome;
}

void supervisorSetNome(Supervisor *supervisor, char nome[100]){
	strcpy(supervisor -> nome, nome);
}

char* supervisorGetCurso(Supervisor *supervisor){
	return supervisor -> curso;
}

void supervisorSetCurso(Supervisor *supervisor, char curso[100]){
	strcpy(supervisor -> curso, curso);
}

void supervisorToString(Supervisor *supervisor){
	printf("Nome: %s\n",   supervisor -> nome);
    printf("Id: %d\n",     supervisor -> id);
    printf("Curso: %s\n",  supervisor -> curso);
}
