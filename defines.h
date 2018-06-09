#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <unistd.h>

#define LOGIN_OK 1000

// DEFINES PARA OS MENUS

#define ARQUIVO_SALVAR 1
#define ARQUIVO_CARREGAR 2
#define ARQUIVO_SAIR 3

#define ATENDIMENTO_CRIAR 4
#define ATENDIMENTO_EDITAR 5
#define ATENDIMENTO_CANCELAR 6
#define ATENDIMENTO_LISTAR_TUDO 7
#define ATENDIMENTO_LISTAR_ALUNO 8
#define ATENDIMENTO_LISTAR_AREA 9
#define ATENDIMENTO_LISTAR_PACIENTE 10

#define AGENDAMENTO_CRIAR 11
#define AGENDAMENTO_EDITAR 12
#define AGENDAMENTO_CANCELAR 13
#define AGENDAMENTO_LISTAR 14

#define ALUNO_CRIAR 15
#define ALUNO_PROCURAR 16
#define ALUNO_EDITAR 30
#define ALUNO_REMOVER 17
#define ALUNO_LISTAR 18

#define PACIENTE_CRIAR 19
#define PACIENTE_EDITAR 20
#define PACIENTE_REMOVER 21
#define PACIENTE_LISTAR 22

#define SUPERVISOR_CRIAR 23
#define SUPERVISOR_EDITAR 24
#define SUPERVISOR_REMOVER 25
#define SUPERVISOR_LISTAR 26

// DEFINE BOTOES

#define BOTAO_CANCEL 200

#define ALUNO_CRIAR_OK 100
#define ALUNO_PROCURAR_OK 101
#define ALUNO_REMOVE_OK 102

#define PACIENTE_CRIAR_OK 103
#define PACIENTE_PROCURAR_OK 104
#define PACIENTE_EDITAR_OK 105
#define PACIENTE_REMOVE_OK 106

#define SUPERVISOR_CRIAR_OK 107
#define SUPERVISOR_PROCURAR_OK 108
#define SUPERVISOR_EDITAR_OK 109
#define SUPERVISOR_REMOVE_OK 110

#define AGE_PROCURA_PAC_OK 111
#define AGE_CRIAR_OK 112
#define AGE_CANCELA_OK 113

#define ATEN_LISTAR_ALUNO_OK 114
#define ATEN_LISTAR_AREA_OK 115
#define ATEN_LISTAR_PACIENTE_OK 116
#define ATEN_CANCELAR_OK 117
#define ATENDIMENTO_CRIAR_OK 118
#define ATENDIMENTO_CRIAR_2_OK 119

#define IDD_CONTROLSDLG 150
#define IDD_SIZE_CBO    151

