#include "agendamento.h"
#include "atendimento.h"

typedef struct agenda Agenda;

Agenda *cria_agenda(void);

void cadastraAgendamento(Agenda *agenda, Agendamento *agendamento);

void removeAgendamento(Agenda *agenda, Agendamento *agendamento);

void listaAgendamentos(Agenda *agenda);

void aumentaPosAgendamento(Agenda *agenda);

void reduzPosAgendamento(Agenda *agenda);

void shiftAgendamentos(Agenda *agenda, int indice);

void cadastraAtendimento(Agenda *agenda, Atendimento *atendimento);

void removeAtendimento(Agenda *agenda, Atendimento *atendimento);

void listaAtendimentos(Agenda *agenda);

void listaAtendimentoPorNomeAluno(Agenda *agenda, char *nome);

void listaAtendimentoPorPaciente(Agenda *agenda, char *paciente);

void listaAtendimentoPorArea(Agenda *agenda, char *area);

void aumentaPosAtendimento(Agenda *agenda);

void reduzPosAtendimento(Agenda *agenda);

void shiftAtendimento(Agenda *agenda, int indice);
