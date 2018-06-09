#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "agenda.h"

//retorno: 1 = true, 0 = false;

int verificaAlunoCadastrado(Aluno *aluno);

int verificaSupervisorCadastrado(Supervisor *supervisor);

int verificaPacienteCadastrado(Paciente *paciente);

int verificaAgendamentoCadastrado(Agendamento *agendamento);

int verificaAreaPaciente(Agendamento* agendamentos[], Agendamento *agendamento, int index);
