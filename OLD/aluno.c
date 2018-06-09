#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno.h"

struct aluno{

	char nome[100], curso[100];
	long int cpf, matricula;
	int idade;

};

Aluno *cria_aluno(char nome[100],int idade, long int matricula, long int cpf, char curso[100]){

    Aluno* aluno = (Aluno*) malloc(sizeof(Aluno));

    strcpy(aluno -> nome, nome);
    aluno -> idade = idade;
    aluno -> matricula = matricula;
    aluno -> cpf = cpf;
    strcpy(aluno -> curso, curso);

    return aluno;
}

int alunoGetIdade(Aluno *aluno){
	return aluno -> idade;
}

void alunoSetIdade(Aluno *aluno, int idade){
	aluno -> idade = idade;
}

long int alunoGetMatricula(Aluno *aluno){
	return aluno -> matricula;
}

void alunoSetMatricula(Aluno *aluno, long int mat){
	aluno -> matricula = mat;
}

long int alunoGetCpf(Aluno *aluno){
	return aluno -> cpf;
}

void alunoSetCpf(Aluno *aluno, long int cpf){
	aluno -> cpf = cpf;
}

char* alunoGetNome(Aluno *aluno){
	return aluno -> nome;
}

void alunoSetNome(Aluno *aluno, char nome[100]){
	strcpy(aluno -> nome, nome);
}


char* alunoGetCurso(Aluno *aluno){
	return aluno -> curso;
}

void alunoSetCurso(Aluno *aluno, char curso[100]){
	strcpy(aluno -> curso, curso);
}

void alunoToString(Aluno *aluno){
	printf("Nome: %s\n",      aluno -> nome);
    printf("Idade: %d\n",     aluno -> idade);
    printf("Matricula: %d\n", aluno -> matricula);
    printf("CPF: %d\n",       aluno -> cpf);
    printf("Curso: %s\n",     aluno -> curso);
}
