#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agendamento.h"
#include "data.h"

struct Agendamento{

	int codigo, codPaciente;
	char nomePaciente[100];
	Data *data;
	char area[20], nomePacienteAgendamento[100];

};

Agendamento *cria_agendamento(Paciente *paciente, Data *data, char area[20],int codigo){

	struct Agendamento *agendamento = (Agendamento*) malloc(sizeof(agendamento));
	
	agendamento -> data = data;
	agendamento -> codigo = codigo;
	strcpy(agendamento -> area, area);
	strcpy(agendamento -> nomePacienteAgendamento, pacienteGetNome(paciente));
	agendamento -> codPaciente = pacienteGetId(paciente);

	return agendamento;
}

int getCodigoPaciente(Agendamento *agendamento){
	
	struct Agendamento *agendamentoaux = (Agendamento*) malloc(sizeof(agendamentoaux));
    agendamentoaux = agendamento;

	return agendamentoaux -> codPaciente;
}

void setCodigoPaciente(Agendamento *agendamento, int codigo){
	
	struct Agendamento *agendamentoaux = (Agendamento*) malloc(sizeof(agendamentoaux));
    agendamentoaux = agendamento;

	agendamentoaux -> codPaciente = codigo;
	
	agendamento = agendamentoaux;
}


char* getNomeAgendamento(Agendamento *agendamento){

    struct Agendamento *agendamentoaux = (Agendamento*) malloc(sizeof(agendamentoaux));
    agendamentoaux = agendamento;

	return agendamentoaux -> nomePacienteAgendamento;
}

void setNomeAgendamento(Agendamento *agendamento, char nome[100]){
	
	struct Agendamento *agendamentoaux = (Agendamento*) malloc(sizeof(agendamentoaux));
    agendamentoaux = agendamento;
    
    strcpy(agendamentoaux -> nomePacienteAgendamento, nome);
    
    agendamento = agendamentoaux;
}

int getCodigo(Agendamento *agendamento){

    struct Agendamento *agendamentoaux = (Agendamento*) malloc(sizeof(agendamentoaux));
    agendamentoaux = agendamento;

	return agendamentoaux -> codigo;
}

void setCodigo(Agendamento *agendamento, int codigo){
	
	struct Agendamento *agendamentoaux = (Agendamento*) malloc(sizeof(agendamentoaux));
    agendamentoaux = agendamento;
    
    agendamentoaux -> codigo = codigo;
    
    agendamento = agendamentoaux;
}

Data* getData(Agendamento *agendamento){

    struct Agendamento *agendamentoaux = (Agendamento*) malloc(sizeof(agendamentoaux));
    agendamentoaux = agendamento;

	return agendamentoaux -> data;
}

void setData(Agendamento *agendamento, Data *data){
	
	struct Agendamento *agendamentoaux = (Agendamento*) malloc(sizeof(agendamentoaux));
    agendamentoaux = agendamento;
    
    agendamentoaux -> data = data;
    
    agendamento = agendamentoaux;
}

char* getArea(Agendamento *agendamento){

    struct Agendamento *agendamentoaux = (Agendamento*) malloc(sizeof(agendamentoaux));
    agendamentoaux = agendamento;

	return agendamentoaux -> area;
}

void setArea(Agendamento *agendamento, char area[20]){
	
	struct Agendamento *agendamentoaux = (Agendamento*) malloc(sizeof(agendamentoaux));
    agendamentoaux = agendamento;
    
    strcpy(agendamentoaux -> area, area);
    
    agendamento = agendamentoaux;
}

void agendamentoToString(Agendamento *agendamento){

    struct Agendamento *agendamentoaux = (Agendamento*) malloc(sizeof(agendamentoaux));
    agendamentoaux = agendamento;
    
	printf("Codigo do agendamento: %d\n",  agendamentoaux -> codigo);
	
	printf("Nome do paciente: ");
	puts(agendamentoaux -> nomePaciente);
	
	printf("Data do agendamento: %d/%d/%d\n", getDiaAgendamento(agendamentoaux), getMesAgendamento(agendamentoaux), getAnoAgendamento(agendamentoaux));
	//puts(agendamentoaux -> data);
	
	printf("Area do Agendamento: ");
	puts(agendamentoaux -> area);
}

int getDiaAgendamento(Agendamento *agendamento){   

	struct Agendamento *agendamentoaux = (Agendamento*) malloc(sizeof(agendamentoaux));
    agendamentoaux = agendamento;
    
	return getDia(agendamentoaux -> data);
}

int getMesAgendamento(Agendamento *agendamento){
	
	struct Agendamento *agendamentoaux = (Agendamento*) malloc(sizeof(agendamentoaux));
    agendamentoaux = agendamento;
	
	return getMes(agendamentoaux -> data);
}

int getAnoAgendamento(Agendamento *agendamento){
	
	struct Agendamento *agendamentoaux = (Agendamento*) malloc(sizeof(agendamentoaux));
    agendamentoaux = agendamento;
	
	return getAno(agendamentoaux -> data);
}

void setDiaAgendamento(Agendamento *agendamento, int dia){   

	struct Agendamento *agendamentoaux = (Agendamento*) malloc(sizeof(agendamentoaux));
    agendamentoaux = agendamento;
    
	setDia(agendamentoaux -> data, dia);
}

void setMesAgendamento(Agendamento *agendamento, int mes){   

	struct Agendamento *agendamentoaux = (Agendamento*) malloc(sizeof(agendamentoaux));
    agendamentoaux = agendamento;
    
	setMes(agendamentoaux -> data, mes);
}

void setAnoAgendamento(Agendamento *agendamento, int ano){   

	struct Agendamento *agendamentoaux = (Agendamento*) malloc(sizeof(agendamentoaux));
    agendamentoaux = agendamento;
    
	setAno(agendamentoaux -> data, ano);
}
