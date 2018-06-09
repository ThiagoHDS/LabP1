#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "agenda.h"

//retornos: true = 1, false = 0;

//verifica se um aluno esta cadastrado(vai ser usado na parte de criar atendimento)
int verificaAlunoCadastrado(Aluno* alunos[], Aluno *aluno, int index){
	int i;
	
	for(i = 0; i < index; i++){
		if(alunoGetCpf(alunos[i]) == alunoGetCpf(aluno)){
			return 1;
		}
	}
	
	return 0;
	
}

//verifica se um paciente esta cadastrado(vai ser usado na parte de criar atendimento)
int verificaPacienteCadastrado(Paciente* pacientes[], Paciente *paciente, int index){
	int i;
	
	for(i = 0; i < index; i++){
		if(pacienteGetCpf(pacientes[i]) == pacienteGetCpf(paciente)){
			return 1;
		}
	}
	
	return 0;
	
}

//verifica se o supervisor esta cadastrado(vai ser usado na parte de criar atendimento
int verificaSupervisorCadastrado(Supervisor* supervisores[], Supervisor *supervisor, int index){
	int i;
	
	for(i = 0; i < index; i++){
		if(supervisorGetId(supervisores[i]) == supervisorGetId(supervisor)){
			return 1;
		}
	}
	
	return 0;
	
}

//verifica se um agendamento esta cadastrado(vai ser usado na parte de criar atendimento)
int verificaAgendamentoCadastrado(Agendamento* agendamentos[], Agendamento *agendamento, int index){
	int i;
	
	for(i = 0; i < index; i++){
		if(getCodigo(agendamentos[i]) == getCodigo(agendamento)){
			return 1;
		}
	}
	
	return 0;
	
}

//serve para verificar se um mesmo paciente ja possui um agendamento nesta area
//(vai ser usado para nao deixar criar um agendamento do mesmo paciente na mesma area)
int verificaAreaPaciente(Agendamento* agendamentos[], Agendamento *agendamento, int index){
	int i;
	
	for(i = 0; i < index; i++){
		if(getCodigoPacienteAgendamento(agendamento) == getCodigoPacienteAgendamento(agendamentos[i]) ){
			if( strcmp(getArea(agendamentos[i]), getArea(agendamento) ) == 0){
				return 1;
			}
		}
			
	}
		
	return 0;
}
	
	
