#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "atendimento.h"

struct Atendimento{
	
	int codigoAtendimento, codigoAgendamento, codAluno, codSupervisor, codPaciente;
	char nomeAluno[100], nomeSupervisor[100], nomePaciente[100], area[20];
	Data *dataAtendimento;
	
};

Atendimento *cria_atendimento(int codigoAtendimento, Aluno *aluno, Paciente *paciente, Supervisor *supervisor, Agendamento *agendamento){
	
	struct Atendimento *atendimento = (Atendimento*) malloc(sizeof(atendimento));
	
	struct Agendamento *agendamentoaux = (Agendamento*) malloc(sizeof(agendamentoaux));
	agendamentoaux = agendamento;
	
	atendimento -> codigoAtendimento = codigoAtendimento;
	strcpy(atendimento -> area, getArea(agendamentoaux));
	
	//pega o nome e o cpf(id) do aluno
	strcpy(atendimento -> nomeAluno, alunoGetNome(aluno));
	atendimento -> codAluno = alunoGetCpf(aluno);
	
	//pega o nome e o codigo(id) do paciente
	strcpy(atendimento -> nomePaciente, pacienteGetNome(paciente));
	atendimento -> codPaciente = pacienteGetId(paciente);
	
	//pega o nome e o codigo do supervisor
	strcpy(atendimento -> nomeSupervisor, supervisorGetNome(supervisor));
	atendimento -> codSupervisor = supervisorGetCodigo(supervisor);
	
	
	//pega o codigo e a data do agendamento
	atendimento -> codigoAgendamento = getCodigo(agendamentoaux);
	atendimento -> dataAtendimento = getData(agendamentoaux);	
	
	return atendimento;
}

int getCodigoAtendimento(Atendimento *atendimento){
	struct Atendimento *atendimentoaux = (Atendimento*) malloc(sizeof(atendimentoaux));
	atendimentoaux = atendimento;
	
	return atendimentoaux -> codigoAtendimento;
}

void setCodigoAtendimento(Atendimento *atendimento, int codigo){
	struct Atendimento *atendimentoaux = (Atendimento*) malloc(sizeof(atendimentoaux));
	atendimentoaux = atendimento;
	
	atendimentoaux -> codigoAtendimento = codigo;
	
	atendimento = atendimentoaux;
}

int getCodigoAgendamento(Atendimento *atendimento){
	struct Atendimento *atendimentoaux = (Atendimento*) malloc(sizeof(atendimentoaux));
	atendimentoaux = atendimento;
	
	return atendimentoaux -> codigoAgendamento;
}

void setCodigoAgendamento(Atendimento *atendimento, int codigo){
	struct Atendimento *atendimentoaux = (Atendimento*) malloc(sizeof(atendimentoaux));
	atendimentoaux = atendimento;
	
	atendimentoaux -> codigoAgendamento = codigo;
	
	atendimento = atendimentoaux;
}

int getCodigoAlunoAtendimento(Atendimento *atendimento){
	struct Atendimento *atendimentoaux = (Atendimento*) malloc(sizeof(atendimentoaux));
	atendimentoaux = atendimento;
	
	return atendimentoaux -> codAluno;
}

void setCodigoAlunoAtendimento(Atendimento *atendimento, int codigo){
	struct Atendimento *atendimentoaux = (Atendimento*) malloc(sizeof(atendimentoaux));
	atendimentoaux = atendimento;
	
	atendimentoaux -> codAluno = codigo;
	
	atendimento = atendimentoaux;
}

int getCodigoPacienteAtendimento(Atendimento *atendimento){
	struct Atendimento *atendimentoaux = (Atendimento*) malloc(sizeof(atendimentoaux));
	atendimentoaux = atendimento;
	
	return atendimentoaux -> codPaciente;
}

void setCodigoPacienteAtendimento(Atendimento *atendimento, int codigo){
	struct Atendimento *atendimentoaux = (Atendimento*) malloc(sizeof(atendimentoaux));
	atendimentoaux = atendimento;
	
	atendimentoaux -> codPaciente = codigo;
	
	atendimento = atendimentoaux;
}

int getCodigoSupervisorAtendimento(Atendimento *atendimento){
	struct Atendimento *atendimentoaux = (Atendimento*) malloc(sizeof(atendimentoaux));
	atendimentoaux = atendimento;
	
	return atendimentoaux -> codSupervisor;
}

void setCodigoSupervisorAtendimento(Atendimento *atendimento, int codigo){
	struct Atendimento *atendimentoaux = (Atendimento*) malloc(sizeof(atendimentoaux));
	atendimentoaux = atendimento;
	
	atendimentoaux -> codigoAtendimento = codigo;
	
	atendimento = atendimentoaux;
}

char* getNomeAlunoAtendimento(Atendimento *atendimento){
	struct Atendimento *atendimentoaux = (Atendimento*) malloc(sizeof(atendimentoaux));
	atendimentoaux = atendimento;
	
	return atendimentoaux -> nomeAluno;
}

void setNomeAlunoAtendimento(Atendimento *atendimento, char nome[100]){
	struct Atendimento *atendimentoaux = (Atendimento*) malloc(sizeof(atendimentoaux));
	atendimentoaux = atendimento;
	
	strcpy(atendimentoaux -> nomeAluno, nome);
	
	atendimento = atendimentoaux;
}

char* getNomeSupervisorAtendimento(Atendimento *atendimento){
	struct Atendimento *atendimentoaux = (Atendimento*) malloc(sizeof(atendimentoaux));
	atendimentoaux = atendimento;
	
	return atendimentoaux -> nomeSupervisor;
}

void setNomeSupervisorAtendimento(Atendimento *atendimento, char nome[100]){
	struct Atendimento *atendimentoaux = (Atendimento*) malloc(sizeof(atendimentoaux));
	atendimentoaux = atendimento;
	
	strcpy(atendimentoaux -> nomeSupervisor, nome);
	
	atendimento = atendimentoaux;
}

char* getNomePacienteAtendimento(Atendimento *atendimento){
	struct Atendimento *atendimentoaux = (Atendimento*) malloc(sizeof(atendimentoaux));
	atendimentoaux = atendimento;
	
	return atendimentoaux -> nomePaciente;
}

void setNomePacienteAtendimento(Atendimento *atendimento, char nome[100]){
	struct Atendimento *atendimentoaux = (Atendimento*) malloc(sizeof(atendimentoaux));
	atendimentoaux = atendimento;
	
	strcpy(atendimentoaux -> nomePaciente, nome);
	
	atendimento = atendimentoaux;
}

char* getAreaAtendimento(Atendimento *atendimento){
	struct Atendimento *atendimentoaux = (Atendimento*) malloc(sizeof(atendimentoaux));
	atendimentoaux = atendimento;
	
	return atendimentoaux -> area;
}

void setAreaAtendimento(Atendimento *atendimento, char area[20]){
	struct Atendimento *atendimentoaux = (Atendimento*) malloc(sizeof(atendimentoaux));
	atendimentoaux = atendimento;
	
	strcpy(atendimentoaux -> area, area);
	
	atendimento = atendimentoaux;
}

Data* getDataAtendimento(Atendimento *atendimento){
	struct Atendimento *atendimentoaux = (Atendimento*) malloc(sizeof(atendimentoaux));
	atendimentoaux = atendimento;
	
	return atendimentoaux -> dataAtendimento;
}

void setDataAtendimento(Atendimento *atendimento, Data *data){
	struct Atendimento *atendimentoaux = (Atendimento*) malloc(sizeof(atendimentoaux));
	atendimentoaux = atendimento;
	
	atendimentoaux -> dataAtendimento = data;
	
	atendimento = atendimentoaux;
}

int getDiaAtendimento(Atendimento *atendimento){   

	struct Atendimento *atendimentoaux = (Atendimento*) malloc(sizeof(atendimentoaux));
	atendimentoaux = atendimento;
    
	return getDia(atendimentoaux -> dataAtendimento);
}

int getMesAtendimento(Atendimento *atendimento){
	
	struct Atendimento *atendimentoaux = (Atendimento*) malloc(sizeof(atendimentoaux));
	atendimentoaux = atendimento;
	
	return getMes(atendimentoaux -> dataAtendimento);
}

int getAnoAtendimento(Atendimento *atendimento){
	
	struct Atendimento *atendimentoaux = (Atendimento*) malloc(sizeof(atendimentoaux));
	atendimentoaux = atendimento;
	
	return getAno(atendimentoaux -> dataAtendimento);
}

void setDiaAtendimento(Atendimento *atendimento, int dia){   

	struct Atendimento *atendimentoaux = (Atendimento*) malloc(sizeof(atendimentoaux));
	atendimentoaux = atendimento;
    
	setDia(atendimentoaux -> dataAtendimento, dia);
}

void setMesAtendimento(Atendimento *atendimento, int mes){   

	struct Atendimento *atendimentoaux = (Atendimento*) malloc(sizeof(atendimentoaux));
	atendimentoaux = atendimento;
    
	setMes(atendimentoaux -> dataAtendimento, mes);
}

void setAnoAtendimento(Atendimento *atendimento, int ano){   

	struct Atendimento *atendimentoaux = (Atendimento*) malloc(sizeof(atendimentoaux));
	atendimentoaux = atendimento;
    
	setAno(atendimentoaux -> dataAtendimento, ano);
}

void atendimentoToString(Atendimento *atendimento){
	struct Atendimento *atendimentoaux = (Atendimento*) malloc(sizeof(atendimentoaux));
	atendimentoaux = atendimento;
	
	printf("Supervisor: ");
	puts(atendimentoaux -> nomeSupervisor);
	printf("Codigo Supervisor: %d\n", atendimentoaux -> codSupervisor);
	
	printf("Paciente: ");
	puts(atendimentoaux -> nomePaciente);
	printf("Codigo Paciente: %d\n", atendimentoaux -> codPaciente);
	
	printf("Aluno: ");
	puts(atendimentoaux -> nomeAluno);
	printf("Codigo Aluno: %d\n", atendimentoaux -> codAluno);
	
	printf("Codigo do Atendimento: %d\n", atendimentoaux -> codigoAtendimento);
	printf("Codigo do Agendamento: %d\n", atendimentoaux -> codigoAgendamento);
	
	printf("Area do Atendimento: ");
	puts(atendimentoaux -> area);
	
	printf("Data do Atendimento: ");
	dataToString(atendimentoaux -> dataAtendimento);
	
}
