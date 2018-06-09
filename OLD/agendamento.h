#include "paciente.h"
#include "data.h"

typedef struct agendamento Agendamento;

Agendamento *cria_agendamento(Paciente *paciente, Data *data, char area[20], int codigo);

char* getNomeAgendamento(Agendamento *agendamento);

void setNomeAgendamento(Agendamento *agendamento, char nome[100]);

int getCodigoPaciente(Agendamento *agendamento);

void setCodigoPaciente(Agendamento *agendamento, int codigo);

Data* getData(Agendamento *agendamento);

void setData(Agendamento *agendamento, Data *data);

char* getArea(Agendamento *agendamento);

void setArea(Agendamento *agendamento, char area[20]);

int getCodigo(Agendamento *agendamento);

void setCodigo(Agendamento *agendamento, int codigo);

void agendamentoToString(Agendamento *agendamento);

int getDiaAgendamento(Agendamento *agendamento);

int getMesAgendamento(Agendamento *agendamento);

int getAnoAgendamento(Agendamento *agendamento);

void setDiaAgendamento(Agendamento *agendamento, int dia);

void setMesAgendamento(Agendamento *agendamento, int mes);

void setAnoAgendamento(Agendamento *agendamento, int ano);
