#include "aluno.h"
#include "paciente.h"
#include "supervisor.h"
#include "data.h"
#include "agendamento.h"

typedef struct atendimento Atendimento;

Atendimento *cria_atendimento(int codigoAtendimento, Aluno *aluno, Paciente *paciente, Supervisor *supervisor, Agendamento *agendamento);

int getCodigoAtendimento(Atendimento *atendimento);

void setCodigoAtendimento(Atendimento *atendimento, int codigo);

int getCodigoAgendamento(Atendimento *atendimento);

void setCodigoAgendamento(Atendimento *atendimento, int codigo);

char* getAreaAtendimento(Atendimento *atendimento);

void setAreaAtendimento(Atendimento *atendimento, char area[20]);

char* getNomeAlunoAtendimento(Atendimento *atendimento);

void setNomeAlunoAtendimento(Atendimento *atendimento, char nome[100]);

int getCodigoAlunoAtendimento(Atendimento *atendimento);

void setCodigoAlunoAtendimento(Atendimento *atendimento, int codigo);

char* getNomePacienteAtendimento(Atendimento *atendimento);

void setNomePacienteAtendimento(Atendimento *atendimento, char nome[100]);

int getCodigoPacienteAtendimento(Atendimento *atendimento);

void setCodigoPacienteAtendimento(Atendimento *atendimento, int codigo);

char* getNomeSupervisorAtendimento(Atendimento *atendimento);

void setNomeSupervisorAtendimento(Atendimento *atendimento, char nome[100]);

int getCodigoSupervisorAtendimento(Atendimento *atendimento);

void setCodigoSupervisorAtendimento(Atendimento *atendimento, int codigo);

Data* getDataAtendimento(Atendimento *atendimento);

void setDataAtendimento(Atendimento *atendimento, Data *data);

Data* getDataAgendamentoAtendimento(Atendimento *atendimento);

void setDataAgendamentoAtendimento(Atendimento *atendimento, Data *data);

void atendimentoToString(Atendimento *atendimento);
