#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agenda.h"

struct Agenda{
	
	int posAgendamento, posAtendimento;
	Agendamento *agendamentos[100];
	Atendimento *atendimentos[100];
	
};

Agenda *cria_agenda(void){
	
	struct Agenda *agenda = (Agenda*) malloc(sizeof(agenda));
	
	agenda -> posAtendimento = 0;
	agenda -> posAgendamento = 0;
	
	return agenda;
}

void cadastraAgendamento(Agenda *agenda, Agendamento *agendamento){
	struct Agenda *agendaux = (Agenda*) malloc(sizeof(agendaux));
	agendaux = agenda;
	
	agendaux -> agendamentos[agendaux -> posAgendamento] = agendamento;
	aumentaPosAgendamento(agendaux);
	
	agenda = agendaux;
}

void removeAgendamento(Agenda *agenda, Agendamento *agendamento){
	struct Agenda *agendaux = (Agenda*) malloc(sizeof(agendaux));
	agendaux = agenda;
	
	struct Agendamento *agendamentoaux = (Agendamento*) malloc(sizeof(agendamentoaux));
	agendamentoaux = agendamento;
	
	int i, indice;
	
	for(i = 0; i < agendaux -> posAgendamento; i++){
		if(getCodigo(agendamentoaux) == getCodigo(agendaux -> agendamentos[i])){
			indice = i;
			break;
		}
	}
	
	shiftAgendamentos(agendaux, indice);
	agenda = agendaux;
	agendamento = agendamentoaux;
}

void listaAgendamentos(Agenda *agenda){
	struct Agenda *agendaux = (Agenda*) malloc(sizeof(agendaux));
	agendaux = agenda;
	
	int i;
	
	for(i = 0; i < agendaux -> posAgendamento; i++){
		agendamentoToString(agendaux -> agendamentos[i]);
	}
	
	
}

void aumentaPosAgendamento(Agenda *agenda){
	struct Agenda *agendaux = (Agenda*) malloc(sizeof(agendaux));
	agendaux = agenda;
	
	agendaux -> posAgendamento += 1;
	agenda = agendaux;
}

void reduzPosAgendamento(Agenda *agenda){
	struct Agenda *agendaux = (Agenda*) malloc(sizeof(agendaux));
	agendaux = agenda;
	
	agendaux -> posAgendamento -= 1;
	agenda = agendaux;
}

void shiftAgendamentos(Agenda *agenda, int indice){
	struct Agenda *agendaux = (Agenda*) malloc(sizeof(agendaux));
	agendaux = agenda;
	
	int i, pos;
	
	pos = agendaux -> posAgendamento;	
	for(i = indice; i < pos - 1; i++){
		agendaux -> agendamentos[i] = agendaux -> agendamentos[i + 1];
	}
	
	reduzPosAgendamento(agendaux);
	agenda = agendaux;
}

void cadastraAtendimento(Agenda *agenda, Atendimento *atendimento){
	struct Agenda *agendaux = (Agenda*) malloc(sizeof(agendaux));
	agendaux = agenda;
	
	struct Atendimento *atendimentoaux = (Atendimento*) malloc(sizeof(atendimentoaux));
	atendimentoaux = atendimento;
	
	agendaux -> atendimentos[agendaux -> posAtendimento] = atendimentoaux;
	aumentaPosAtendimento(agendaux);
	
	agenda = agendaux;
	
}

void removeAtendimento(Agenda *agenda, Atendimento *atendimento){
	struct Agenda *agendaux = (Agenda*) malloc(sizeof(agendaux));
	agendaux = agenda;
	
	struct Atendimento *atendimentoaux = (Atendimento*) malloc(sizeof(atendimentoaux));
	atendimentoaux = atendimento;
	
	int i, indice;
	
	for(i = 0; i < agendaux -> posAtendimento; i++){
		if(getCodigoAtendimento(atendimentoaux) == getCodigoAtendimento(agendaux -> atendimentos[i])){
			indice = i;
			break;
		}
	}
	
	shiftAtendimentos(agendaux, indice);
	agenda = agendaux;
	atendimento = atendimentoaux;
	
	
}

void listaAtendimentos(Agenda *agenda){
	struct Agenda *agendaux = (Agenda*) malloc(sizeof(agendaux));
	agendaux = agenda;
	
	int i;
	
	for(i = 0; i < agendaux -> posAtendimento; i++){
		atendimentoToString(agendaux -> atendimentos[i]);
	}
}

void listaAtendimentoPorNomeAluno(Agenda *agenda, char *nome){
	struct Agenda *agendaux = (Agenda*) malloc(sizeof(agendaux));
	agendaux = agenda;
	
	int i;
	
	for(i = 0; i < agendaux -> posAtendimento; i++){
		if(strcmp(nome, getNomeAlunoAtendimento(agendaux -> atendimentos[i])) == 0){
			atendimentoToString(agendaux -> atendimentos[i]);
		}	
	}
}

void listaAtendimentoPorArea(Agenda *agenda, char *area){
	struct Agenda *agendaux = (Agenda*) malloc(sizeof(agendaux));
	agendaux = agenda;
	
	int i;
	
	for(i = 0; i < agendaux -> posAtendimento; i++){
		if(strcmp(area, getAreaAtendimento(agendaux -> atendimentos[i])) == 0){
			atendimentoToString(agendaux -> atendimentos[i]);
		}	
	}
}

void listaAtendimentoPorPaciente(Agenda *agenda, char *paciente){
	struct Agenda *agendaux = (Agenda*) malloc(sizeof(agendaux));
	agendaux = agenda;
	
	int i;
	
	for(i = 0; i < agendaux -> posAtendimento; i++){
		if(strcmp(paciente, getNomePacienteAtendimento(agendaux -> atendimentos[i])) == 0){
			atendimentoToString(agendaux -> atendimentos[i]);
		}	
	}
}

void aumentaPosAtendimento(Agenda *agenda){
	struct Agenda *agendaux = (Agenda*) malloc(sizeof(agendaux));
	agendaux = agenda;
	
	agendaux -> posAtendimento += 1;
	agenda = agendaux;
}

void reduzPosAtendimento(Agenda *agenda){
	struct Agenda *agendaux = (Agenda*) malloc(sizeof(agendaux));
	agendaux = agenda;
	
	agendaux -> posAtendimento -= 1;
	agenda = agendaux;
}

void shiftAtendimentos(Agenda *agenda, int indice){
	struct Agenda *agendaux = (Agenda*) malloc(sizeof(agendaux));
	agendaux = agenda;
	
	int i, pos;
	
	pos = agendaux -> posAtendimento;	
	for(i = indice; i < pos - 1; i++){
		agendaux -> atendimentos[i] = agendaux -> atendimentos[i + 1];
	}
	
	reduzPosAtendimento(agendaux);
	agenda = agendaux;
}
