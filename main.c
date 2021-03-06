#include "defines.h"

/* 

	PROJETO DA DISCIPLINA DE LINGUAGEM DE PROGRAMACAO 1 DA UNIVERSIDADE ESTADUAL DA PARAIBA
	@AUTHOR THIAGO HENRIQUE DOMINGOS DE SA

	Minha ideia era criar TADs e usar ponteiros de struct(contidos na pasta OLD), mas devido a erros que para mim nao faziam sentido
	como acessar structs incompletas(que para mim nao tinha nada errado) ou erros de include acusando redefini��o de structs
	decidi simplificar e utilizar structs normais e coloca-las neste mesmo arquivo.
	
	Na parte de interface grafica utilizei a documentacao oficial da microsoft que pode ser encontrada em 
		https://msdn.microsoft.com/en/library/windows/desktop/ff818516(v=vs.85).aspx
	
	A IDE utilizada foi o DEV-C++.
	
	Ordem no arquivo:
		1. estruturas
		2. Funcoes da interface grafica
		3. funcoes das funcionalidades
		4. LRESULT CALLBACK WndProc (Aqui estao todas as funcionalidades)
		5. MAIN(LOOP da janela principal)

*/

struct data{
	
	int dia, mes, ano;
	
};

typedef struct data Data;

Data cria_data(int dia, int mes, int ano){
	
	Data data;
	
	data.dia = dia;
	data.mes = mes;
	data.ano = ano;
	
	return data;
}

struct paciente{

	char nome[100], endereco[100];
	int cpf, id;
	Data data;

};

typedef struct paciente Paciente;

Paciente cria_paciente(int id, char nome[100], Data data, long int cpf, char endereco[100]){

    Paciente paciente;

    strcpy(paciente.nome, nome);
    paciente.data = data;
    paciente.id = id;
    paciente.cpf = cpf;
    strcpy(paciente.endereco, endereco);

    return paciente;
}

struct aluno{

	char nome[100], curso[100];
	long int cpf, matricula;
	int idade;

};

typedef struct aluno Aluno;

Aluno cria_aluno(char nome[100],int idade, long int matricula, long int cpf, char curso[100]){

	Aluno aluno;

    strcpy(aluno.nome, nome);
    aluno.idade = idade;
    aluno.matricula = matricula;
    aluno.cpf = cpf;
    strcpy(aluno.curso, curso);

    return aluno;
}

struct supervisor{

	char nome[100], curso[100];
	int id, codigo;

};

typedef struct supervisor Supervisor;

Supervisor cria_supervisor(int id, char nome[100], char curso[100], int codigo){

    Supervisor supervisor;

	supervisor.id = id;
	supervisor.codigo = codigo;
    strcpy(supervisor.nome, nome);
    strcpy(supervisor.curso, curso);

    return supervisor;
}

struct agendamento{

	int codigo, codPaciente;
	char nomePaciente[100];
	Data data;
	char area[20];

};

typedef struct agendamento Agendamento;

Agendamento cria_agendamento(Paciente paciente, Data data, char area[20],int codigo){

	Agendamento agendamento;
	
	agendamento.data = data;
	agendamento.codigo = codigo;
	strcpy(agendamento.area, area);
	strcpy(agendamento.nomePaciente, paciente.nome);
	agendamento.codPaciente = paciente.id;

	return agendamento;
}

struct atendimento{
	
	int codigoAtendimento, codigoAgendamento, codAluno, codSupervisor, codPaciente;
	char nomeAluno[100], nomeSupervisor[100], nomePaciente[100], area[20];
	Data dataAtendimento;
	
};

typedef struct atendimento Atendimento;

Atendimento cria_atendimento(int codigoAtendimento, Aluno aluno, Supervisor supervisor, Agendamento agendamento){
	
	Atendimento atendimento;
	
	atendimento.codigoAtendimento = codigoAtendimento;
	strcpy(atendimento.area, agendamento.area);
	
	//pega o nome e o cpf(id) do aluno
	strcpy(atendimento.nomeAluno, aluno.nome);
	atendimento.codAluno = aluno.cpf;
	
	//pega o nome e o codigo(id) do paciente
	strcpy(atendimento.nomePaciente, agendamento.nomePaciente);
	atendimento.codPaciente = agendamento.codPaciente;
	
	//pega o nome e o codigo do supervisor
	strcpy(atendimento.nomeSupervisor, supervisor.nome);
	atendimento.codSupervisor = supervisor.codigo;
	
	//pega o codigo e a data do agendamento
	atendimento.codigoAgendamento = agendamento.codigo;
	atendimento.dataAtendimento = agendamento.data;	
	
	return atendimento;
}

const char g_szClassName[] = "CLINICA"; //nome da janela principal

//VARIAVEIS GLOBAIS PARA RECEBIMENTO DE DADOS E ESTRUTURAS
char lista[1000];
int posicoes[9];
Aluno alunos[1000];
Supervisor supervisores[1000];
Paciente pacientes[1000];
Agendamento agendamentos[1000];
Atendimento atendimentos[1000];
int posAluno, posSupervisor, posPaciente, posAgendamento, posAtendimento, pos = -1, pos2 = -1, pos3 = -1, carregou = 0;
int idPaciente = 1, idSupervisor = 1, idAgendamento = 1, idAtendimento = 1;
HWND hnome, hcurso, hcpf, hmatricula, hidade, hendereco, harea, hdia, hmes, hano, haluno, hidpaciente, hsupervisor, hidaluno, hidsupervisor, hconfirma, hcancela, hlistas, hid;

//cria uma janela cinza de dimensoes 1920x1080
void limpaTela(HWND hwnd){
	CreateWindowW(L"static", L"", WS_VISIBLE | WS_CHILDWINDOW , 0, 0, 1920, 1080, hwnd, NULL, NULL, NULL);	
}

//destroi todas as janelas editaveis
void destroiJanelas(){
	
	DestroyWindow(hnome);
	DestroyWindow(hcurso);
	DestroyWindow(hmatricula);
	DestroyWindow(hcpf);
	DestroyWindow(hidade);
	DestroyWindow(hcancela);
	DestroyWindow(hconfirma);
	DestroyWindow(hlistas);
	DestroyWindow(hendereco);
	DestroyWindow(hid);
	DestroyWindow(harea);
	DestroyWindow(hdia);
	DestroyWindow(hmes);
	DestroyWindow(hano);
	DestroyWindow(haluno);
	DestroyWindow(hsupervisor);
	DestroyWindow(hidaluno);
	DestroyWindow(hidsupervisor);
	DestroyWindow(hidpaciente);
}

// FUNCOES PARA AS JANELAS DA INTERFACE GRAFICA
void janelaCriaAluno(HWND hwnd){
	
	// POSICAO HORIZONTAL - POSICAO VERTICAL - LARGURA - ALTURA
	CreateWindowW(L"static", L">>>> CADASTRO DE ALUNO", WS_VISIBLE | WS_CHILDWINDOW, 10, 20, 200, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	CreateWindowW(L"static", L"Nome:", WS_VISIBLE | WS_CHILDWINDOW, 10, 50, 130, 24, (HWND) hwnd, NULL, NULL, NULL);
	hnome = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 90, 50, 300, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	CreateWindowW(L"static", L"Curso:", WS_VISIBLE | WS_CHILDWINDOW, 10, 80, 130, 24, (HWND) hwnd, NULL, NULL, NULL);
	hcurso = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 90, 80, 300, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	CreateWindowW(L"static", L"CPF:", WS_VISIBLE | WS_CHILDWINDOW, 10, 110, 130, 24, (HWND) hwnd, NULL, NULL, NULL);
	hcpf = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER , 90, 110, 300, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	CreateWindowW(L"static", L"Matricula:", WS_VISIBLE | WS_CHILDWINDOW, 10, 140, 130, 24, (HWND) hwnd, NULL, NULL, NULL);
	hmatricula = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 90, 140, 300, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	CreateWindowW(L"static", L"Idade:", WS_VISIBLE | WS_CHILDWINDOW, 10, 170, 130, 24, (HWND) hwnd, NULL, NULL, NULL);
	hidade = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 90, 170, 35, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	hconfirma = CreateWindowW(L"button", L"Confirmar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 90, 200, 100, 24, (HWND) hwnd, (HMENU) ALUNO_CRIAR_OK, NULL, NULL);
	hcancela = CreateWindowW(L"button", L"Cancelar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 210, 200, 100, 24, (HWND) hwnd, (HMENU) BOTAO_CANCEL, NULL, NULL);
	
}

void janelaEditaAluno(HWND hwnd, Aluno aluno){
	
	// POSICAO HORIZONTAL - POSICAO VERTICAL - LARGURA - ALTURA
	CreateWindowW(L"static", L">>>> EDITAR ALUNO", WS_VISIBLE | WS_CHILDWINDOW, 10, 20, 200, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	CreateWindowW(L"static", L"Nome:", WS_VISIBLE | WS_CHILDWINDOW, 10, 50, 130, 24, (HWND) hwnd, NULL, NULL, NULL);
	hnome = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 90, 50, 300, 24, (HWND) hwnd, NULL, NULL, NULL);
	SetWindowText(hnome, aluno.nome);
	
	CreateWindowW(L"static", L"Curso:", WS_VISIBLE | WS_CHILDWINDOW, 10, 80, 130, 24, (HWND) hwnd, NULL, NULL, NULL);
	hcurso = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 90, 80, 300, 24, (HWND) hwnd, NULL, NULL, NULL);
	SetWindowText(hcurso, aluno.curso);
	
	CreateWindowW(L"static", L"CPF:", WS_VISIBLE | WS_CHILDWINDOW, 10, 110, 130, 24, (HWND) hwnd, NULL, NULL, NULL);
	hcpf = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER , 90, 110, 300, 24, (HWND) hwnd, NULL, NULL, NULL);
	char cpf[11];
	sprintf(cpf, "%ld", aluno.cpf);
	SetWindowText(hcpf, cpf);
	
	CreateWindowW(L"static", L"Matricula:", WS_VISIBLE | WS_CHILDWINDOW, 10, 140, 130, 24, (HWND) hwnd, NULL, NULL, NULL);
	hmatricula = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 90, 140, 300, 24, (HWND) hwnd, NULL, NULL, NULL);
	char mat[11];
	sprintf(mat, "%ld", aluno.matricula);
	SetWindowText(hmatricula, mat);
	
	CreateWindowW(L"static", L"Idade:", WS_VISIBLE | WS_CHILDWINDOW, 10, 170, 130, 24, (HWND) hwnd, NULL, NULL, NULL);
	hidade = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 90, 170, 35, 24, (HWND) hwnd, NULL, NULL, NULL);
	char idade[3];
	sprintf(idade, "%d", aluno.idade);
	SetWindowText(hidade, idade);
	
	hconfirma = CreateWindowW(L"button", L"Confirmar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 90, 200, 100, 24, (HWND) hwnd, (HMENU) ALUNO_EDITAR, NULL, NULL);
	hcancela = CreateWindowW(L"button", L"Cancelar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 210, 200, 100, 24, (HWND) hwnd, (HMENU) BOTAO_CANCEL, NULL, NULL);

}

void janelaProcuraAluno(HWND hwnd){
	
	// POSICAO HORIZONTAL - POSICAO VERTICAL - LARGURA - ALTURA
	CreateWindowW(L"static", L">>>> EDITAR ALUNO - PROCURA POR CPF", WS_VISIBLE | WS_CHILDWINDOW, 10, 20, 400, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	CreateWindowW(L"static", L"Digite o CPF do aluno:", WS_VISIBLE | WS_CHILDWINDOW, 10, 50, 200, 24, (HWND) hwnd, NULL, NULL, NULL);
	hcpf = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 170, 50, 300, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	hconfirma = CreateWindowW(L"button", L"Procurar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 170, 90, 100, 24, (HWND) hwnd, (HMENU) ALUNO_PROCURAR_OK, NULL, NULL);
	hcancela = CreateWindowW(L"button", L"Cancelar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 290, 90, 100, 24, (HWND) hwnd, (HMENU) BOTAO_CANCEL, NULL, NULL);
	
}

void janelaDeletaAluno(HWND hwnd){
	
	// POSICAO HORIZONTAL - POSICAO VERTICAL - LARGURA - ALTURA
	CreateWindowW(L"static", L">>>> REMOVER ALUNO - PROCURA POR CPF", WS_VISIBLE | WS_CHILDWINDOW, 10, 20, 400, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	CreateWindowW(L"static", L"Digite o CPF do aluno:", WS_VISIBLE | WS_CHILDWINDOW, 10, 50, 200, 24, (HWND) hwnd, NULL, NULL, NULL);
	hcpf = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 170, 50, 300, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	hconfirma = CreateWindowW(L"button", L"Procurar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 170, 90, 100, 24, (HWND) hwnd, (HMENU) ALUNO_REMOVE_OK, NULL, NULL);
	hcancela = CreateWindowW(L"button", L"Cancelar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 290, 90, 100, 24, (HWND) hwnd, (HMENU) BOTAO_CANCEL, NULL, NULL);
	
}

void janelaCriaPaciente(HWND hwnd){
	
	// POSICAO HORIZONTAL - POSICAO VERTICAL - LARGURA - ALTURA
	CreateWindowW(L"static", L">>>> CADASTRO DE PACIENTE", WS_VISIBLE | WS_CHILDWINDOW, 10, 20, 250, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	CreateWindowW(L"static", L"Nome:", WS_VISIBLE | WS_CHILDWINDOW, 10, 50, 130, 24, (HWND) hwnd, NULL, NULL, NULL);
	hnome = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 90, 50, 300, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	CreateWindowW(L"static", L"Endereco:", WS_VISIBLE | WS_CHILDWINDOW, 10, 80, 130, 24, (HWND) hwnd, NULL, NULL, NULL);
	hendereco = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 90, 80, 300, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	CreateWindowW(L"static", L"CPF:", WS_VISIBLE | WS_CHILDWINDOW, 10, 110, 130, 24, (HWND) hwnd, NULL, NULL, NULL);
	hcpf = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER , 90, 110, 300, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	CreateWindowW(L"static", L"Data Nasc:", WS_VISIBLE | WS_CHILDWINDOW, 10, 140, 130, 24, (HWND) hwnd, NULL, NULL, NULL);
	hdia = CreateWindowW(L"edit", L"DIA", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 90, 140, 35, 24, (HWND) hwnd, NULL, NULL, NULL);
	hmes = CreateWindowW(L"edit", L"MES", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 140, 140, 35, 24, (HWND) hwnd, NULL, NULL, NULL);
	hano = CreateWindowW(L"edit", L"ANO", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 190, 140, 45, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	/*CreateWindowW(L"static", L"Data Nasc:", WS_VISIBLE | WS_CHILDWINDOW, 10, 140, 130, 24, (HWND) hwnd, NULL, NULL, NULL);
	hidade = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 90, 140, 300, 24, (HWND) hwnd, NULL, NULL, NULL);*/
	
	hconfirma = CreateWindowW(L"button", L"Confirmar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 90, 170, 100, 24, (HWND) hwnd, (HMENU) PACIENTE_CRIAR_OK, NULL, NULL);
	hcancela = CreateWindowW(L"button", L"Cancelar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 210, 170, 100, 24, (HWND) hwnd, (HMENU) BOTAO_CANCEL, NULL, NULL);
}

void janelaProcuraPaciente(HWND hwnd){
	
	// POSICAO HORIZONTAL - POSICAO VERTICAL - LARGURA - ALTURA
	CreateWindowW(L"static", L">>>> EDITAR PACIENTE - PROCURA POR CPF", WS_VISIBLE | WS_CHILDWINDOW, 10, 20, 400, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	CreateWindowW(L"static", L"Digite o CPF do paciente:", WS_VISIBLE | WS_CHILDWINDOW, 10, 50, 200, 24, (HWND) hwnd, NULL, NULL, NULL);
	hcpf = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 180, 50, 300, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	hconfirma = CreateWindowW(L"button", L"Procurar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 180, 90, 100, 24, (HWND) hwnd, (HMENU) PACIENTE_PROCURAR_OK, NULL, NULL);
	hcancela = CreateWindowW(L"button", L"Cancelar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 300, 90, 100, 24, (HWND) hwnd, (HMENU) BOTAO_CANCEL, NULL, NULL);
}

void janelaRemovePaciente(HWND hwnd){
	
	// POSICAO HORIZONTAL - POSICAO VERTICAL - LARGURA - ALTURA
	CreateWindowW(L"static", L">>>> REMOVER PACIENTE - PROCURA POR CPF", WS_VISIBLE | WS_CHILDWINDOW, 10, 20, 400, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	CreateWindowW(L"static", L"Digite o CPF do paciente:", WS_VISIBLE | WS_CHILDWINDOW, 10, 50, 200, 24, (HWND) hwnd, NULL, NULL, NULL);
	hcpf = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 180, 50, 300, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	hconfirma = CreateWindowW(L"button", L"Procurar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 180, 90, 100, 24, (HWND) hwnd, (HMENU) PACIENTE_REMOVE_OK, NULL, NULL);
	hcancela = CreateWindowW(L"button", L"Cancelar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 300, 90, 100, 24, (HWND) hwnd, (HMENU) BOTAO_CANCEL, NULL, NULL);
}

void janelaEditaPaciente(HWND hwnd, Paciente paciente){
	
	// POSICAO HORIZONTAL - POSICAO VERTICAL - LARGURA - ALTURA
	CreateWindowW(L"static", L">>>> EDITAR PACIENTE", WS_VISIBLE | WS_CHILDWINDOW, 10, 20, 200, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	CreateWindowW(L"static", L"Nome:", WS_VISIBLE | WS_CHILDWINDOW, 10, 50, 130, 24, (HWND) hwnd, NULL, NULL, NULL);
	hnome = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 90, 50, 300, 24, (HWND) hwnd, NULL, NULL, NULL);
	SetWindowText(hnome, paciente.nome);
	
	CreateWindowW(L"static", L"Endereco:", WS_VISIBLE | WS_CHILDWINDOW, 10, 80, 130, 24, (HWND) hwnd, NULL, NULL, NULL);
	hendereco = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 90, 80, 300, 24, (HWND) hwnd, NULL, NULL, NULL);
	SetWindowText(hendereco, paciente.endereco);
	
	CreateWindowW(L"static", L"CPF:", WS_VISIBLE | WS_CHILDWINDOW, 10, 110, 130, 24, (HWND) hwnd, NULL, NULL, NULL);
	hcpf = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER , 90, 110, 300, 24, (HWND) hwnd, NULL, NULL, NULL);
	char cpf[11];
	sprintf(cpf, "%ld", paciente.cpf);
	SetWindowText(hcpf, cpf);
	
	CreateWindowW(L"static", L"Data:", WS_VISIBLE | WS_CHILDWINDOW, 10, 140, 130, 24, (HWND) hwnd, NULL, NULL, NULL);
	hdia = CreateWindowW(L"edit", L"DIA", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 90, 140, 35, 24, (HWND) hwnd, NULL, NULL, NULL);
	char dia[4];
	sprintf(dia, "%d", paciente.data.dia);
	SetWindowText(hdia, dia);
	
	hmes = CreateWindowW(L"edit", L"MES", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 140, 140, 35, 24, (HWND) hwnd, NULL, NULL, NULL);
	char mes[4];
	sprintf(mes, "%d", paciente.data.mes);
	SetWindowText(hmes, mes);
	
	hano = CreateWindowW(L"edit", L"ANO", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 190, 140, 45, 24, (HWND) hwnd, NULL, NULL, NULL);
	char ano[5];
	sprintf(ano, "%d", paciente.data.ano);
	SetWindowText(hano, ano);
	
	/*CreateWindowW(L"static", L"Data Nasc:", WS_VISIBLE | WS_CHILDWINDOW, 10, 140, 130, 24, (HWND) hwnd, NULL, NULL, NULL);
	hidade = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 90, 140, 300, 24, (HWND) hwnd, NULL, NULL, NULL);
	SetWindowText(hidade, paciente.idade);*/
	
	hconfirma = CreateWindowW(L"button", L"Confirmar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 90, 170, 100, 24, (HWND) hwnd, (HMENU) PACIENTE_EDITAR_OK, NULL, NULL);
	hcancela = CreateWindowW(L"button", L"Cancelar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 210, 170, 100, 24, (HWND) hwnd, (HMENU) BOTAO_CANCEL, NULL, NULL);
	
}

void janelaCriaSupervisor(HWND hwnd){
	
	// POSICAO HORIZONTAL - POSICAO VERTICAL - LARGURA - ALTURA
	CreateWindowW(L"static", L">>>> CADASTRO DE SUPERVISOR", WS_VISIBLE | WS_CHILDWINDOW, 10, 20, 400, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	CreateWindowW(L"static", L"Nome:", WS_VISIBLE | WS_CHILDWINDOW, 10, 50, 130, 24, (HWND) hwnd, NULL, NULL, NULL);
	hnome = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 90, 50, 300, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	CreateWindowW(L"static", L"Curso:", WS_VISIBLE | WS_CHILDWINDOW, 10, 80, 130, 24, (HWND) hwnd, NULL, NULL, NULL);
	hcurso = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 90, 80, 300, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	CreateWindowW(L"static", L"Cod. Sup.:", WS_VISIBLE | WS_CHILDWINDOW, 10, 110, 130, 24, (HWND) hwnd, NULL, NULL, NULL);
	hid = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 90, 110, 300, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	hconfirma = CreateWindowW(L"button", L"Confirmar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 90, 140, 100, 24, (HWND) hwnd, (HMENU) SUPERVISOR_CRIAR_OK, NULL, NULL);
	hcancela = CreateWindowW(L"button", L"Cancelar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 210, 140, 100, 24, (HWND) hwnd, (HMENU) BOTAO_CANCEL, NULL, NULL);
	
}

void janelaProcuraSupervisor(hwnd){
	
	// POSICAO HORIZONTAL - POSICAO VERTICAL - LARGURA - ALTURA
	CreateWindowW(L"static", L">>>> EDITAR SUPERVISOR - PROCURA POR ID", WS_VISIBLE | WS_CHILDWINDOW, 10, 20, 400, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	CreateWindowW(L"static", L"Digite o ID do supervisor:", WS_VISIBLE | WS_CHILDWINDOW, 10, 50, 200, 24, (HWND) hwnd, NULL, NULL, NULL);
	hid = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 200, 50, 300, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	hconfirma = CreateWindowW(L"button", L"Procurar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 200, 90, 100, 24, (HWND) hwnd, (HMENU) SUPERVISOR_PROCURAR_OK, NULL, NULL);
	hcancela = CreateWindowW(L"button", L"Cancelar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 320, 90, 100, 24, (HWND) hwnd, (HMENU) BOTAO_CANCEL, NULL, NULL);
}

void janelaEditaSupervisor(HWND hwnd, Supervisor supervisor){
	
	// POSICAO HORIZONTAL - POSICAO VERTICAL - LARGURA - ALTURA
	CreateWindowW(L"static", L">>>> EDITAR SUPERVISOR", WS_VISIBLE | WS_CHILDWINDOW, 10, 20, 200, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	CreateWindowW(L"static", L"Nome:", WS_VISIBLE | WS_CHILDWINDOW, 10, 50, 130, 24, (HWND) hwnd, NULL, NULL, NULL);
	hnome = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 90, 50, 300, 24, (HWND) hwnd, NULL, NULL, NULL);
	SetWindowText(hnome, supervisor.nome);
	
	CreateWindowW(L"static", L"Curso:", WS_VISIBLE | WS_CHILDWINDOW, 10, 80, 130, 24, (HWND) hwnd, NULL, NULL, NULL);
	hcurso = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 90, 80, 300, 24, (HWND) hwnd, NULL, NULL, NULL);
	SetWindowText(hcurso, supervisor.curso);
	
	CreateWindowW(L"static", L"Cod. Sup.:", WS_VISIBLE | WS_CHILDWINDOW, 10, 110, 130, 24, (HWND) hwnd, NULL, NULL, NULL);
	hid = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 90, 110, 300, 24, (HWND) hwnd, NULL, NULL, NULL);
	char id[11];
	sprintf(id, "%d", supervisor.codigo);
	SetWindowText(hid, id);
	
	hconfirma = CreateWindowW(L"button", L"Confirmar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 90, 140, 100, 24, (HWND) hwnd, (HMENU) SUPERVISOR_EDITAR_OK, NULL, NULL);
	hcancela = CreateWindowW(L"button", L"Cancelar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 210, 140, 100, 24, (HWND) hwnd, (HMENU) BOTAO_CANCEL, NULL, NULL);
	
}

void janelaRemoveSupervisor(HWND hwnd){
	
	// POSICAO HORIZONTAL - POSICAO VERTICAL - LARGURA - ALTURA
	CreateWindowW(L"static", L">>>> REMOVER SUPERVISOR - PROCURA POR ID", WS_VISIBLE | WS_CHILDWINDOW, 10, 20, 400, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	CreateWindowW(L"static", L"Digite o ID do supervisor:", WS_VISIBLE | WS_CHILDWINDOW, 10, 50, 200, 24, (HWND) hwnd, NULL, NULL, NULL);
	hid = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 200, 50, 300, 24, hwnd, NULL, NULL, NULL);
	
	hconfirma = CreateWindowW(L"button", L"Procurar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 200, 90, 100, 24, (HWND) hwnd, (HMENU) SUPERVISOR_REMOVE_OK, NULL, NULL);
	hcancela = CreateWindowW(L"button", L"Cancelar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 320, 90, 100, 24, (HWND) hwnd, (HMENU) BOTAO_CANCEL, NULL, NULL);
	
}

void janelaAgendamentoProcuraPaciente(HWND hwnd){
	
	// POSICAO HORIZONTAL - POSICAO VERTICAL - LARGURA - ALTURA
	CreateWindowW(L"static", L">>>> 1. CRIAR AGENDAMENTO - PROCURAR PACIENTE POR ID", WS_VISIBLE | WS_CHILDWINDOW, 10, 20, 600, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	CreateWindowW(L"static", L"Digite o ID do paciente:", WS_VISIBLE | WS_CHILDWINDOW, 10, 50, 200, 24, (HWND) hwnd, NULL, NULL, NULL);
	hid = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 200, 50, 300, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	hconfirma = CreateWindowW(L"button", L"Procurar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 200, 90, 100, 24, (HWND) hwnd, (HMENU) AGE_PROCURA_PAC_OK, NULL, NULL);
	hcancela = CreateWindowW(L"button", L"Cancelar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 320, 90, 100, 24, (HWND) hwnd, (HMENU) BOTAO_CANCEL, NULL, NULL);
	
}

void janelaCriaAgendamento(HWND hwnd, Paciente paciente){
	
	// POSICAO HORIZONTAL - POSICAO VERTICAL - LARGURA - ALTURA
	CreateWindowW(L"static", L">>>> 2. CRIAR AGENDAMENTO", WS_VISIBLE | WS_CHILDWINDOW, 10, 20, 400, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	CreateWindowW(L"static", L"Paciente:", WS_VISIBLE | WS_CHILDWINDOW, 10, 50, 130, 24, (HWND) hwnd, NULL, NULL, NULL);
	hnome = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER | WS_DISABLED, 90, 50, 300, 24, (HWND) hwnd, NULL, NULL, NULL);
	SetWindowText(hnome, paciente.nome);
	
	CreateWindowW(L"static", L"ID Pac.:", WS_VISIBLE | WS_CHILDWINDOW, 10, 80, 130, 24, (HWND) hwnd, NULL, NULL, NULL);
	hid = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER | WS_DISABLED, 90, 80, 35, 24, (HWND) hwnd, NULL, NULL, NULL);
	char id[4];
	sprintf(id, "%d", paciente.id);
	SetWindowText(hid, id);
	
	CreateWindowW(L"static", L"Area:", WS_VISIBLE | WS_CHILDWINDOW, 10, 110, 130, 24, (HWND) hwnd, NULL, NULL, NULL);
	harea = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 90, 110, 300, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	CreateWindowW(L"static", L"Data:", WS_VISIBLE | WS_CHILDWINDOW, 10, 140, 130, 24, (HWND) hwnd, NULL, NULL, NULL);
	hdia = CreateWindowW(L"edit", L"DIA", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 90, 140, 35, 24, (HWND) hwnd, NULL, NULL, NULL);
	hmes = CreateWindowW(L"edit", L"MES", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 140, 140, 35, 24, (HWND) hwnd, NULL, NULL, NULL);
	hano = CreateWindowW(L"edit", L"ANO", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 190, 140, 45, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	hconfirma = CreateWindowW(L"button", L"Confirmar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 90, 180, 100, 24, (HWND) hwnd, (HMENU) AGE_CRIAR_OK, NULL, NULL);
	hcancela = CreateWindowW(L"button", L"Cancelar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 210, 180, 100, 24, (HWND) hwnd, (HMENU) BOTAO_CANCEL, NULL, NULL);
	
}

void janelaCancelaAgendamento(HWND hwnd){
	
	// POSICAO HORIZONTAL - POSICAO VERTICAL - LARGURA - ALTURA
	CreateWindowW(L"static", L">>>> CANCELAR AGENDAMENTO - PROCURAR AGENDAMENTO POR ID", WS_VISIBLE | WS_CHILDWINDOW, 10, 20, 600, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	CreateWindowW(L"static", L"Digite o ID do agendamento:", WS_VISIBLE | WS_CHILDWINDOW, 10, 50, 200, 24, (HWND) hwnd, NULL, NULL, NULL);
	hid = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 200, 50, 300, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	hconfirma = CreateWindowW(L"button", L"Procurar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 200, 90, 100, 24, (HWND) hwnd, (HMENU) AGE_CANCELA_OK, NULL, NULL);
	hcancela = CreateWindowW(L"button", L"Cancelar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 320, 90, 100, 24, (HWND) hwnd, (HMENU) BOTAO_CANCEL, NULL, NULL);
}

void janelaListaAtendimentoAluno(HWND hwnd){
	
	// POSICAO HORIZONTAL - POSICAO VERTICAL - LARGURA - ALTURA
	CreateWindowW(L"static", L">>>> LISTAR ATENDIMENTOS - POR NOME ALUNO", WS_VISIBLE | WS_CHILDWINDOW, 10, 20, 600, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	CreateWindowW(L"static", L"Digite o nome:", WS_VISIBLE | WS_CHILDWINDOW, 10, 50, 200, 24, (HWND) hwnd, NULL, NULL, NULL);
	hnome = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 120, 50, 300, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	hconfirma = CreateWindowW(L"button", L"Procurar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 120, 90, 100, 24, (HWND) hwnd, (HMENU) ATEN_LISTAR_ALUNO_OK, NULL, NULL);
	hcancela = CreateWindowW(L"button", L"Cancelar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 240, 90, 100, 24, (HWND) hwnd, (HMENU) BOTAO_CANCEL, NULL, NULL);
	
}

void janelaListaAtendimentoArea(hwnd){
	
	// POSICAO HORIZONTAL - POSICAO VERTICAL - LARGURA - ALTURA
	CreateWindowW(L"static", L">>>> LISTAR ATENDIMENTOS - POR AREA", WS_VISIBLE | WS_CHILDWINDOW, 10, 20, 600, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	CreateWindowW(L"static", L"Digite a area:", WS_VISIBLE | WS_CHILDWINDOW, 10, 50, 200, 24, (HWND) hwnd, NULL, NULL, NULL);
	harea = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 120, 50, 300, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	hconfirma = CreateWindowW(L"button", L"Procurar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 120, 90, 100, 24, (HWND) hwnd, (HMENU) ATEN_LISTAR_AREA_OK, NULL, NULL);
	hcancela = CreateWindowW(L"button", L"Cancelar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 240, 90, 100, 24, (HWND) hwnd, (HMENU) BOTAO_CANCEL, NULL, NULL);
	
}

void janelaListaAtendimentoPaciente(hwnd){
	
	// POSICAO HORIZONTAL - POSICAO VERTICAL - LARGURA - ALTURA
	CreateWindowW(L"static", L">>>> LISTAR ATENDIMENTOS - POR NOME PACIENTE", WS_VISIBLE | WS_CHILDWINDOW, 10, 20, 600, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	CreateWindowW(L"static", L"Digite nome:", WS_VISIBLE | WS_CHILDWINDOW, 10, 50, 200, 24, (HWND) hwnd, NULL, NULL, NULL);
	hnome = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 120, 50, 300, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	hconfirma = CreateWindowW(L"button", L"Procurar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 120, 90, 100, 24, (HWND) hwnd, (HMENU) ATEN_LISTAR_PACIENTE_OK, NULL, NULL);
	hcancela = CreateWindowW(L"button", L"Cancelar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 240, 90, 100, 24, (HWND) hwnd, (HMENU) BOTAO_CANCEL, NULL, NULL);
	
}

void janelaCriaAtendimento(HWND hwnd){
	
	// POSICAO HORIZONTAL - POSICAO VERTICAL - LARGURA - ALTURA
	CreateWindowW(L"static", L">>>> 1. CRIAR ATENDIMENTO - PROCURAR ALUNO, SUPERVISOR E AGENDAMENTO", WS_VISIBLE | WS_CHILDWINDOW, 10, 20, 600, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	CreateWindowW(L"static", L"Digite o ID do agendamento:", WS_VISIBLE | WS_CHILDWINDOW, 10, 50, 200, 24, (HWND) hwnd, NULL, NULL, NULL);
	hid = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 200, 50, 300, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	CreateWindowW(L"static", L"Digite o CPF aluno:", WS_VISIBLE | WS_CHILDWINDOW, 10, 90, 200, 24, (HWND) hwnd, NULL, NULL, NULL);
	haluno = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 200, 90, 300, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	CreateWindowW(L"static", L"Digite o ID do supervisor:", WS_VISIBLE | WS_CHILDWINDOW, 10, 130, 200, 24, (HWND) hwnd, NULL, NULL, NULL);
	hsupervisor = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 200, 130, 300, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	hconfirma = CreateWindowW(L"button", L"Procurar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 200, 170, 100, 24, (HWND) hwnd, (HMENU) ATENDIMENTO_CRIAR_OK, NULL, NULL);
	hcancela = CreateWindowW(L"button", L"Cancelar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 320, 170, 100, 24, (HWND) hwnd, (HMENU) BOTAO_CANCEL, NULL, NULL);
}

void janelaCriaAtendimento2(HWND hwnd, Agendamento agendamento, Aluno aluno, Supervisor supervisor){
	
	// POSICAO HORIZONTAL - POSICAO VERTICAL - LARGURA - ALTURA
	CreateWindowW(L"static", L">>>> 2. CRIAR ATENDIMENTO", WS_VISIBLE | WS_CHILDWINDOW, 10, 20, 400, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	CreateWindowW(L"static", L"Paciente:", WS_VISIBLE | WS_CHILDWINDOW, 10, 50, 130, 24, (HWND) hwnd, NULL, NULL, NULL);
	hnome = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER | WS_DISABLED, 90, 50, 300, 24, (HWND) hwnd, NULL, NULL, NULL);
	SetWindowText(hnome, agendamento.nomePaciente);
	
	CreateWindowW(L"static", L"ID Pac.:", WS_VISIBLE | WS_CHILDWINDOW, 10, 80, 130, 24, hwnd, NULL, NULL, NULL);
	hidpaciente = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER | WS_DISABLED, 90, 80, 35, 24, (HWND) hwnd, NULL, NULL, NULL);
	char id[4];
	sprintf(id, "%d", agendamento.codPaciente);
	SetWindowText(hidpaciente, id);
	
	CreateWindowW(L"static", L"Area:", WS_VISIBLE | WS_CHILDWINDOW, 10, 110, 130, 24, (HWND) hwnd, NULL, NULL, NULL);
	harea = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER | WS_DISABLED, 90, 110, 300, 24, (HWND) hwnd, NULL, NULL, NULL);
	SetWindowText(harea, agendamento.area);
	
	CreateWindowW(L"static", L"Data:", WS_VISIBLE | WS_CHILDWINDOW, 10, 140, 130, 24, (HWND) hwnd, NULL, NULL, NULL);
	hdia = CreateWindowW(L"edit", L"DIA", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER | WS_DISABLED, 90, 140, 35, 24, (HWND) hwnd, NULL, NULL, NULL);
	char dia[4];
	sprintf(dia, "%d", agendamento.data.dia);
	SetWindowText(hdia, dia);
	
	hmes = CreateWindowW(L"edit", L"MES", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER | WS_DISABLED, 140, 140, 35, 24, (HWND) hwnd, NULL, NULL, NULL);
	char mes[4];
	sprintf(mes, "%d", agendamento.data.mes);
	SetWindowText(hmes, mes);
	
	hano = CreateWindowW(L"edit", L"ANO", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER | WS_DISABLED, 190, 140, 35, 24, (HWND) hwnd, NULL, NULL, NULL);
	char ano[4];
	sprintf(ano, "%d", agendamento.data.ano);
	SetWindowText(hano, ano);
	
	CreateWindowW(L"static", L"Aluno:", WS_VISIBLE | WS_CHILDWINDOW, 10, 170, 130, 24, (HWND) hwnd, NULL, NULL, NULL);
	haluno = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER | WS_DISABLED, 90, 170, 300, 24, (HWND) hwnd, NULL, NULL, NULL);
	SetWindowText(haluno, aluno.nome);
	
	CreateWindowW(L"static", L"ID aluno:", WS_VISIBLE | WS_CHILDWINDOW, 10, 200, 130, 24, (HWND) hwnd, NULL, NULL, NULL);
	hidaluno = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER | WS_DISABLED, 90, 200, 110, 24, (HWND) hwnd, NULL, NULL, NULL);
	char id2[12];
	sprintf(id2, "%ld", aluno.cpf);
	SetWindowText(hidaluno, id2);
	
	CreateWindowW(L"static", L"Supervisor:", WS_VISIBLE | WS_CHILDWINDOW, 10, 230, 130, 24, (HWND) hwnd, NULL, NULL, NULL);
	hsupervisor = CreateWindowW(L"edit", L"DIA", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER | WS_DISABLED, 90, 230, 300, 24, (HWND) hwnd, NULL, NULL, NULL);
	SetWindowText(hsupervisor, supervisor.nome);
	
	CreateWindowW(L"static", L"ID Sup.:", WS_VISIBLE | WS_CHILDWINDOW, 10, 260, 130, 24, hwnd, NULL, NULL, NULL);
	hidsupervisor = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER | WS_DISABLED, 90, 260, 35, 24, (HWND) hwnd, NULL, NULL, NULL);
	char id3[4];
	sprintf(id3, "%d", supervisor.id);
	SetWindowText(hidsupervisor, id3);
	
	hconfirma = CreateWindowW(L"button", L"Confirmar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 90, 290, 100, 24, (HWND) hwnd, (HMENU) ATENDIMENTO_CRIAR_2_OK, NULL, NULL);
	hcancela = CreateWindowW(L"button", L"Cancelar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 210, 290, 100, 24, (HWND) hwnd, (HMENU) BOTAO_CANCEL, NULL, NULL);
	
}

void janelaAtendimentoCancelar(HWND hwnd){
	
	// POSICAO HORIZONTAL - POSICAO VERTICAL - LARGURA - ALTURA
	CreateWindowW(L"static", L">>>> CANCELAR ATENDIMENTO - PESQUISA POR ID", WS_VISIBLE | WS_CHILDWINDOW, 10, 20, 600, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	CreateWindowW(L"static", L"Digite o ID:", WS_VISIBLE | WS_CHILDWINDOW, 10, 50, 200, 24, (HWND) hwnd, NULL, NULL, NULL);
	hid = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 120, 50, 300, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	hconfirma = CreateWindowW(L"button", L"Procurar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 120, 90, 100, 24, (HWND) hwnd, (HMENU) ATEN_CANCELAR_OK, NULL, NULL);
	hcancela = CreateWindowW(L"button", L"Cancelar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 240, 90, 100, 24, (HWND) hwnd, (HMENU) BOTAO_CANCEL, NULL, NULL);
	
}

void janelaLogin(HWND hwnd){
	
	// POSICAO HORIZONTAL - POSICAO VERTICAL - LARGURA - ALTURA
	//CreateWindowW(L"static", L"AREA DE LOGIN", WS_VISIBLE | WS_CHILDWINDOW, 220, 80, 600, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	CreateWindowW(L"static", L"Username:", WS_VISIBLE | WS_CHILDWINDOW, 140, 122, 200, 24, (HWND) hwnd, NULL, NULL, NULL);
	hnome = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 230, 120, 150, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	CreateWindowW(L"static", L"Password:", WS_VISIBLE | WS_CHILDWINDOW, 140, 152, 200, 24, (HWND) hwnd, NULL, NULL, NULL);
	hid = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 230, 150, 150, 24, (HWND) hwnd, NULL, NULL, NULL);
	
	hconfirma = CreateWindowW(L"button", L"Login", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 230, 180, 100, 24, (HWND) hwnd, (HMENU) LOGIN_OK, NULL, NULL);
	
}

void criaMenus(HWND hwnd){
	
	//-------------- DEFINICAO DOS MENUS E SUBMENUS --------------//
	HMENU hMenu = CreateMenu(); // Barra de menus
	HMENU menuArquivo = CreateMenu(); // cria o menu arquivo
	HMENU menuAtendimento = CreateMenu(); // cria o menu atendimento
	HMENU menuAgendamento = CreateMenu(); // cria o menu agendamento
	HMENU menuAluno= CreateMenu(); // cria o menu aluno
	HMENU menuSupervisor = CreateMenu(); // cria o menu supervisor
	HMENU menuPaciente= CreateMenu(); // cria o menu paciente
	HMENU subMenuAtendimento = CreateMenu(); // cria o menu atendimento
	
	//-------------- MENU DE ARQUIVO --------------//
	AppendMenu(menuArquivo, MF_STRING, ARQUIVO_SALVAR,     "Salvar");
	AppendMenu(menuArquivo, MF_STRING, ARQUIVO_CARREGAR,   "Carregar Arquivos");
	AppendMenu(menuArquivo, MF_STRING, ARQUIVO_SAIR,       "Sair");
	
	//-------------- MENU DE ATENDIMENTO --------------//
	// submenu listas
	AppendMenu(subMenuAtendimento, MF_STRING, ATENDIMENTO_LISTAR_TUDO,     "Listar todos os atendimentos");
	AppendMenu(subMenuAtendimento, MF_STRING, ATENDIMENTO_LISTAR_ALUNO,    "Listar por aluno");
	AppendMenu(subMenuAtendimento, MF_STRING, ATENDIMENTO_LISTAR_AREA,     "Listar por area");
	AppendMenu(subMenuAtendimento, MF_STRING, ATENDIMENTO_LISTAR_PACIENTE, "Listar por paciente");
	//termina sub menu lista
	
	AppendMenu(menuAtendimento, MF_STRING, ATENDIMENTO_CRIAR,            "Adicionar Atendimento");
	//AppendMenu(menuAtendimento, MF_STRING, ATENDIMENTO_EDITAR,          "Editar Atendimento");
	AppendMenu(menuAtendimento, MF_STRING, ATENDIMENTO_CANCELAR,         "Cancelar Atendimento");
	AppendMenu(menuAtendimento, MF_POPUP, (UINT_PTR) subMenuAtendimento, "Listar Atendimentos");
	
	
	//-------------- MENU DE AGENDAMENTO --------------//
	AppendMenu(menuAgendamento, MF_STRING, AGENDAMENTO_CRIAR,    "Adicionar Agendamento");
	//AppendMenu(menuAgendamento, MF_STRING, AGENDAMENTO_EDITAR,   "Editar Agendamento");
	AppendMenu(menuAgendamento, MF_STRING, AGENDAMENTO_CANCELAR, "Cancelar Agendamento");
	AppendMenu(menuAgendamento, MF_STRING, AGENDAMENTO_LISTAR,   "Listar Agendamentos");
	
	//-------------- MENU DE ALUNO --------------//
	AppendMenu(menuAluno, MF_STRING, ALUNO_CRIAR,     "Adicionar Aluno");
	AppendMenu(menuAluno, MF_STRING, ALUNO_PROCURAR,  "Editar Aluno");
	AppendMenu(menuAluno, MF_STRING, ALUNO_REMOVER,   "Remover Aluno");
	AppendMenu(menuAluno, MF_STRING, ALUNO_LISTAR,    "Listar Alunos");
	
	//-------------- MENU DE PACIENTE --------------//
	AppendMenu(menuPaciente, MF_STRING, PACIENTE_CRIAR,   "Adicionar Paciente");
	AppendMenu(menuPaciente, MF_STRING, PACIENTE_EDITAR,  "Editar Paciente");
	AppendMenu(menuPaciente, MF_STRING, PACIENTE_REMOVER, "Remover Paciente");
	AppendMenu(menuPaciente, MF_STRING, PACIENTE_LISTAR,  "Listar Pacientes");
	
	//-------------- MENU DE SUPERVISOR --------------//
	AppendMenu(menuSupervisor, MF_STRING, SUPERVISOR_CRIAR,   "Adicionar Supervisor");
	AppendMenu(menuSupervisor, MF_STRING, SUPERVISOR_EDITAR,  "Editar Supervisor");
	AppendMenu(menuSupervisor, MF_STRING, SUPERVISOR_REMOVER, "Remover Supervisor");
	AppendMenu(menuSupervisor, MF_STRING, SUPERVISOR_LISTAR,  "Listar Supervisores");
	
	//-------------- MENUS PRINCIPAIS --------------//
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR) menuArquivo,     "Arquivo");
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR) menuAtendimento, "Atendimento");
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR) menuAgendamento, "Agendamento");
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR) menuAluno,       "Aluno");
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR) menuPaciente,    "Paciente");
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR) menuSupervisor,  "Supervisor");
	
	SetMenu(hwnd, hMenu);
	
}

 // ---------------------- FUNCOES DAS FUNCIONALIDADES ---------------------- //
 
//altera a string para lowercase(apenas para buscas e verificacoes)
char* lowerCase(char str[], int tam){
	char min[tam];
	
	int i;
	for(i = 0; i < tam; i++){
		min[i] = tolower(str[i]);
	}
	
	return min;
}

// retorna 1 se for invalida e 0 se for valida
int verificaData(int dia, int mes, int ano){
	
	if(dia > 31 || mes > 12 || ano < 2018 || dia == 0 || mes == 0 || ano == 0){
		return 1;
	}
	
	return 0;
}

void cancela(HWND hwnd){
	int op = MessageBoxW(hwnd, L"Deseja realmente cancelar?", L"Aviso!", MB_YESNO | MB_ICONWARNING);
						
	if(op == IDYES){
		limpaTela(hwnd);
		destroiJanelas();
	}
}

void login(HWND hwnd){
	int senha = 123, aux;
					
	char username[10], senha2[10];
					
	GetWindowText(hnome, username, 10);
	GetWindowText(hid, senha2, 10);
					
	aux = atoi(senha2);
					
	if(strcmp(username, "") == 0|| strcmp(senha2, "") == 0){
		MessageBoxW(hwnd, L"Preencha os campos em branco!", L"Aviso!", MB_OK | MB_ICONWARNING);
							
	}else if(aux != senha || strcmp(username, "admin") != 0){
		MessageBoxW(hwnd, L"Dado(s) incorretos. Tente novamente!", L"Aviso!", MB_OK | MB_ICONWARNING);
						
	}else{
		MessageBoxW(hwnd, L"Login efetuado com sucesso!", L"Sucesso!", MB_OK | MB_ICONINFORMATION);
		limpaTela(hwnd);
		destroiJanelas();
		criaMenus(hwnd);
	}
	
}

void salvar(HWND hwnd){
	int op;
					
	FILE* arquivo_pos;
	FILE* arquivo_aluno;
	FILE* arquivo_paciente;
	FILE* arquivo_supervisor;
	FILE* arquivo_agendamento;
	FILE* arquivo_atendimento;
					
	if(carregou == 0){
		op = MessageBox(hwnd, "Nenhum arquivo foi carregado durante esta execucao. Deseja realmente salvar?", "Aviso!", MB_YESNO);
	}
	
	if(IDYES == op){
						
	posicoes[0] = posAluno;
	posicoes[1] = posSupervisor;
	posicoes[2] = posPaciente;
	posicoes[3] = posAgendamento;
	posicoes[4] = posAtendimento;
	posicoes[5] = idPaciente;
	posicoes[6] = idSupervisor;
	posicoes[7] = idAgendamento;
	posicoes[8] = idAtendimento;
	
	arquivo_pos = fopen("pos.bin", "w+b");
	fwrite(posicoes, sizeof(int), 9, arquivo_pos);
	fclose(arquivo_pos);
			
	arquivo_aluno = fopen("alunos.bin", "w+b"); 
	fwrite(alunos, sizeof(alunos[0]), 1000, arquivo_aluno);
	fclose(arquivo_aluno); 
						
	arquivo_paciente = fopen("pacientes.bin", "w+b");
	fwrite(pacientes, sizeof(pacientes[0]), 1000, arquivo_paciente);
	fclose(arquivo_paciente);
						
	arquivo_supervisor = fopen("supervisores.bin", "w+b");
	fwrite(supervisores, sizeof(supervisores[0]), 1000, arquivo_supervisor);
	fclose(arquivo_supervisor);
						
	arquivo_agendamento = fopen("agendamentos.bin", "w+b");
	fwrite(agendamentos, sizeof(agendamentos[0]), 1000, arquivo_agendamento);
	fclose(arquivo_agendamento);
	
	arquivo_atendimento = fopen("atendimentos.bin", "w+b");
	fwrite(atendimentos, sizeof(atendimentos[0]), 1000, arquivo_atendimento);
	fclose(arquivo_atendimento);
						
	MessageBox(hwnd, "Arquivos salvos com sucesso!", "Sucesso!", MB_ICONINFORMATION);
						
	}
}

void carregar(HWND hwnd){
	
	FILE* arquivo_pos;
	FILE* arquivo_aluno;
	FILE* arquivo_paciente;
	FILE* arquivo_supervisor;
	FILE* arquivo_agendamento;
	FILE* arquivo_atendimento;
			
	arquivo_pos = fopen("pos.bin", "r+b");
	fread(posicoes, sizeof(int), 9, arquivo_pos);
	fclose(arquivo_pos);
					
	posAluno 		= posicoes[0];
	posSupervisor 	= posicoes[1];
	posPaciente		= posicoes[2];
	posAgendamento 	= posicoes[3];					
	posAtendimento	= posicoes[4];
	idPaciente		= posicoes[5];
	idSupervisor	= posicoes[6];
	idAgendamento	= posicoes[7];
	idAtendimento	= posicoes[8];
					
	arquivo_aluno = fopen("alunos.bin", "r+b"); 
	fread(alunos, sizeof(alunos[0]), posAluno, arquivo_aluno);
	fclose(arquivo_aluno); 
					
	arquivo_paciente = fopen("pacientes.bin", "r+b");
	fread(pacientes, sizeof(pacientes[0]), posPaciente, arquivo_paciente);
	fclose(arquivo_paciente);
						
	arquivo_supervisor = fopen("supervisores.bin", "r+b");
	fread(supervisores, sizeof(supervisores[0]), posSupervisor, arquivo_supervisor);
	fclose(arquivo_supervisor);
						
	arquivo_agendamento = fopen("agendamentos.bin", "r+b");
	fread(agendamentos, sizeof(agendamentos[0]), posAgendamento, arquivo_agendamento);
	fclose(arquivo_agendamento);

	arquivo_atendimento = fopen("atendimentos.bin", "r+b");
	fread(atendimentos, sizeof(atendimentos[0]), posAgendamento, arquivo_atendimento);
	fclose(arquivo_atendimento);
	
	MessageBoxW(NULL, L"Arquivos carregados!", L"Carregamento", MB_ICONINFORMATION);
					
	carregou = 1;
	
}

void fechaPrograma(HWND hwnd){
	int op;
	
	op = MessageBoxW(NULL, L"Deseja realmente sair do programa?", L"SAIR", MB_YESNO | MB_ICONWARNING);
					
	if(op == IDYES)
		DestroyWindow(hwnd);
}

void criaAtendimento(HWND hwnd) {
    int id2, cpf2, idsup2, i;
    char id[4], cpf[11], idsup[4];

    GetWindowText(hid, id, 4);
    GetWindowText(haluno, cpf, 11);
    GetWindowText(hsupervisor, idsup, 4);

    id2 = atoi(id);
    cpf2 = atol(cpf);
    idsup2 = atoi(idsup);

    if (strcmp(id, "") == 0 || strcmp(cpf, "") == 0 || strcmp(idsup, "") == 0) {
        MessageBoxW(hwnd, L"Preencha os campos em branco!", L"Aviso!", MB_OK | MB_ICONWARNING);

    } else if (id2 == 0 || cpf2 == 0 || idsup2 == 0) {
        MessageBoxW(hwnd, L"Digite apenas numeros!", L"Aviso!", MB_OK | MB_ICONWARNING);

    } else {

        for (i = 0; i < posAgendamento; i++) {
            if (agendamentos[i].codigo == id2) {
                pos = i;
                break;
            }

            pos = -1;
        }

        for (i = 0; i < posAluno; i++) {
            if (alunos[i].cpf == cpf2) {
                pos2 = i;
                break;
            }

            pos2 = -1;
        }

        for (i = 0; i < posSupervisor; i++) {
            if (supervisores[i].id == idsup2) {
                pos3 = i;
                break;
            }

            pos3 = -1;
        }

        if (pos < 0) {
            MessageBoxW(hwnd, L"Agendamento nao encontrado! Acesse o menu cadastro e faca o cadastro!", L"Aviso!", MB_OK | MB_ICONWARNING);

        } else if (pos2 < 0) {
            MessageBoxW(hwnd, L"Aluno nao encontrado! Acesse o menu cadastro e faca o cadastro!", L"Aviso!", MB_OK | MB_ICONWARNING);

        } else if (pos3 < 0) {
            MessageBoxW(hwnd, L"Supervisor nao encontrado! Acesse o menu cadastro e faca o cadastro!", L"Aviso!", MB_OK | MB_ICONWARNING);

        } else {
            MessageBoxW(hwnd, L"Aluno, agendamento e supervisor encontrados!", L"Sucesso!", MB_OK | MB_ICONINFORMATION);
            limpaTela(hwnd);
            destroiJanelas();
            janelaCriaAtendimento2(hwnd, agendamentos[pos], alunos[pos2], supervisores[pos3]);

        }

    }
}

void criaAtendimento2(HWND hwnd) {
    atendimentos[posAtendimento] = cria_atendimento(idAtendimento, alunos[pos], supervisores[pos], agendamentos[pos]);

    int i, j;
    for (i = 0; i < posAgendamento; i++) {
        if (agendamentos[pos].codigo == agendamentos[i].codigo) {
            for (j = i; j < posAgendamento - 1; j++) {
                agendamentos[j] = agendamentos[j + 1];
            }
        }
    }

    posAtendimento++;
    idAtendimento++;
    posAgendamento--;

    MessageBoxW(hwnd, L"Atendimento criado com sucesso!", L"Sucesso!", MB_OK | MB_ICONINFORMATION);
    limpaTela(hwnd);
    destroiJanelas();

}

void cancelaAtendimento(HWND hwnd) {
    int op;
    char id[4];
    GetWindowText(hid, id, 4);
    int id2;
    id2 = atoi(id);

    if (strcmp(id, "") == 0) {
        MessageBoxW(hwnd, L"Preencha os campos em branco!", L"Aviso!", MB_OK | MB_ICONWARNING);

    } else if (id2 == 0) {
        MessageBoxW(hwnd, L"Digite apenas numeros!", L"Aviso!", MB_OK | MB_ICONWARNING);

    } else {

        int i, j, achou = 0;

        for (i = 0; i < posAtendimento; i++) {
            if (id2 == atendimentos[i].codigoAtendimento) {
                achou = 1;
                op = MessageBoxW(hwnd, L"Atendimento encontrado! Tem certeza que deseja excluir?",
                    L"Confirmacao!", MB_YESNO | MB_ICONINFORMATION);

                if (op == IDYES) {
                    for (j = i; j < posAtendimento - 1; j++) {
                        atendimentos[j] = atendimentos[j + 1];

                    }

                    posAtendimento--;
                    MessageBoxW(hwnd, L"Atendimento removido com sucesso!", L"Sucesso!", MB_OK | MB_ICONINFORMATION);
                    limpaTela(hwnd);
                    destroiJanelas();
                }

                break;
            }

        }

        if (achou == 0)
            MessageBoxW(hwnd, L"Agendamento nao encontrado! Acesse o menu de cadastro e cadastre o agendamento!", L"Aviso!",
                MB_OK | MB_ICONWARNING);

    }
}

void concatenaAtendimento(int i) {

    char idAluno[10], idSupervisor[10], idPaciente[10], dia[10], mes[10], ano[10], codigoAgendamento[10], codigoAtendimento[10];

    Data data = atendimentos[i].dataAtendimento;
    sprintf(dia, "%d", data.dia);
    sprintf(mes, "%d", data.mes);
    sprintf(ano, "%d", data.ano);
    sprintf(codigoAgendamento, "%d", atendimentos[i].codigoAgendamento);
    sprintf(codigoAtendimento, "%d", atendimentos[i].codigoAtendimento);
    sprintf(idAluno, "%d", atendimentos[i].codAluno);
    sprintf(idPaciente, "%d", atendimentos[i].codPaciente);
    sprintf(idSupervisor, "%d", atendimentos[i].codSupervisor);

    strcat(lista, "ID Atendimento: ");
    strcat(lista, codigoAtendimento);
    strcat(lista, "\r\n");
    strcat(lista, "ID Agendamento: ");
    strcat(lista, codigoAgendamento);
    strcat(lista, "\r\n");
    strcat(lista, "Nome do Paciente: ");
    strcat(lista, atendimentos[i].nomePaciente);
    strcat(lista, "\r\n");
    strcat(lista, "ID do Paciente: ");
    strcat(lista, idPaciente);
    strcat(lista, "\r\n");
    strcat(lista, "Nome do Aluno: ");
    strcat(lista, atendimentos[i].nomeAluno);
    strcat(lista, "\r\n");
    strcat(lista, "ID do Aluno: ");
    strcat(lista, idAluno);
    strcat(lista, "\r\n");
    strcat(lista, "Nome do supervisor: ");
    strcat(lista, atendimentos[i].nomeSupervisor);
    strcat(lista, "\r\n");
    strcat(lista, "ID do supervisor: ");
    strcat(lista, idSupervisor);
    strcat(lista, "\r\n");
    strcat(lista, "Area: ");
    strcat(lista, atendimentos[i].area);
    strcat(lista, "\r\n");
    strcat(lista, "Data do atendimento: ");
    strcat(lista, dia);
    strcat(lista, "/");
    strcat(lista, mes);
    strcat(lista, "/");
    strcat(lista, ano);
    strcat(lista, "\r\n");
    strcat(lista, "\r\n");

}

void listarTudoAtendimento(HWND hwnd) {
    int i;

    CreateWindowW(L"static", L">>>> LISTA DE ATENDIMENTOS CADASTRADOS", WS_VISIBLE | WS_CHILDWINDOW, 10, 20, 400, 24, hwnd, NULL, NULL, NULL);

    if (posAtendimento == 0) {
        CreateWindowW(L"static", L"NENHUM ATENDIMENTO CADASTRADO!", WS_VISIBLE | WS_CHILDWINDOW, 10, 60, 400, 50, hwnd, NULL, NULL, NULL);

    } else {

        strcpy(lista, "");
        for (i = 0; i < posAtendimento; i++) {
            concatenaAtendimento(i);
        }

        hlistas = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER | ES_MULTILINE | WS_VSCROLL, 10, 60, 400, 230, hwnd, NULL, NULL, NULL);
        SetWindowText(hlistas, lista);

        hcancela = CreateWindowW(L"button", L"Voltar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 420, 265, 100, 24, (HWND) hwnd, (HMENU) BOTAO_VOLTAR, NULL, NULL);
    }
}

void listarAlunoAtendimento(HWND hwnd) {
    int i, j, achou = 0;
    char idAluno[10], idSupervisor[10], idPaciente[10], dia[10], mes[10], ano[10], codigoAgendamento[10], codigoAtendimento[10];
    char nome[100], nomeLower[100];

    GetWindowText(hnome, nome, 100); //nome passado para pesquisa

    strcpy(nomeLower, lowerCase(nome, 100));

    for (i = 0; i < posAtendimento; i++) {
        if (strcmp(nomeLower, lowerCase(atendimentos[i].nomeAluno, 100)) == 0) {
            achou = 1;
            break;
        }
    }

    if (strcmp(nome, "") == 0) {
        MessageBox(hwnd, "Preencha os campos em branco!", "Aviso!", MB_ICONWARNING);
    } else if (achou == 0) {
        MessageBox(hwnd, "Nenhum atendimento cadastrado com o nome deste aluno!", "Aviso!", MB_ICONWARNING);

    } else {

        limpaTela(hwnd);
        destroiJanelas();

        strcpy(lista, "");
        for (i = 0; i < posAtendimento; i++) {
            if (strcmp(nomeLower, lowerCase(atendimentos[i].nomeAluno, 100)) == 0) {
                concatenaAtendimento(i);
            }
        }

        CreateWindowW(L"static", L">>>> LISTA DE ATENDIMENTOS POR NOME ALUNO", WS_VISIBLE | WS_CHILDWINDOW, 10, 20, 400, 24, hwnd, NULL, NULL, NULL);

        hlistas = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER | ES_MULTILINE | WS_VSCROLL, 10, 60, 400, 230, hwnd, NULL, NULL, NULL);
        SetWindowText(hlistas, lista);

        hcancela = CreateWindowW(L"button", L"Voltar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 420, 265, 100, 24, (HWND) hwnd, (HMENU) BOTAO_VOLTAR, NULL, NULL);
    }

}

void listarAreaAtendimento(HWND hwnd) {
    int i, j, achou = 0;
    char idAluno[10], idSupervisor[10], idPaciente[10], dia[10], mes[10], ano[10], codigoAgendamento[10], codigoAtendimento[10];
    char area[20], areaLower[20];

    GetWindowText(harea, area, 100); //nome passado para pesquisa

    strcpy(areaLower, lowerCase(area, 20));

    for (i = 0; i < posAtendimento; i++) {
        if (strcmp(areaLower, lowerCase(atendimentos[i].area, 20)) == 0) {
            achou = 1;
            break;
        }
    }

    if (strcmp(area, "") == 0) {
        MessageBox(hwnd, "Preencha os campos em branco!", "Aviso!", MB_ICONWARNING);
    } else if (achou == 0) {
        MessageBox(hwnd, "Nenhum atendimento cadastrado nesta area!", "Aviso!", MB_ICONWARNING);

    } else {

        limpaTela(hwnd);
        destroiJanelas();

        strcpy(lista, "");
        for (i = 0; i < posAtendimento; i++) {
            if (strcmp(areaLower, lowerCase(atendimentos[i].area, 20)) == 0) {
                concatenaAtendimento(i);
            }
        }

        CreateWindowW(L"static", L">>>> LISTA DE ATENDIMENTOS POR AREA", WS_VISIBLE | WS_CHILDWINDOW, 10, 20, 400, 24, hwnd, NULL, NULL, NULL);

        hlistas = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER | ES_MULTILINE | WS_VSCROLL, 10, 60, 400, 230, hwnd, NULL, NULL, NULL);
        SetWindowText(hlistas, lista);

        hcancela = CreateWindowW(L"button", L"Voltar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 420, 265, 100, 24, (HWND) hwnd, (HMENU) BOTAO_VOLTAR, NULL, NULL);
    }
}

void listarPacienteAtendimento(HWND hwnd) {
    int i, j, achou = 0;
    char idAluno[10], idSupervisor[10], idPaciente[10], dia[10], mes[10], ano[10], codigoAgendamento[10], codigoAtendimento[10];
    char nome[100], nomeLower[100];

    GetWindowText(hnome, nome, 100); //nome passado para pesquisa

    strcpy(nomeLower, lowerCase(nome, 100));

    for (i = 0; i < posAtendimento; i++) {
        if (strcmp(nomeLower, lowerCase(atendimentos[i].nomePaciente, 100)) == 0) {
            achou = 1;
            break;
        }
    }

    if (strcmp(nome, "") == 0) {
        MessageBox(hwnd, "Preencha os campos em branco!", "Aviso!", MB_ICONWARNING);
    } else if (achou == 0) {
        MessageBox(hwnd, "Nenhum atendimento cadastrado com o nome deste paciente!", "Aviso!", MB_ICONWARNING);

    } else {

        limpaTela(hwnd);
        destroiJanelas();

        strcpy(lista, "");
        for (i = 0; i < posAtendimento; i++) {
            if (strcmp(nomeLower, lowerCase(atendimentos[i].nomePaciente, 100)) == 0) {
                concatenaAtendimento(i);
            }
        }

        CreateWindowW(L"static", L">>>> LISTA DE ATENDIMENTOS POR NOME PACIENTE", WS_VISIBLE | WS_CHILDWINDOW, 10, 20, 400, 24, hwnd, NULL, NULL, NULL);

        hlistas = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER | ES_MULTILINE | WS_VSCROLL, 10, 60, 400, 230, hwnd, NULL, NULL, NULL);
        SetWindowText(hlistas, lista);

        hcancela = CreateWindowW(L"button", L"Voltar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 420, 265, 100, 24, (HWND) hwnd, (HMENU) BOTAO_VOLTAR, NULL, NULL);
    }
}

void criaAgendamento(HWND hwnd) {
    int id2, i;
    char id[3];

    GetWindowText(hid, id, 3);
    id2 = atoi(id);

    if (strcmp(id, "") == 0) {
        MessageBoxW(hwnd, L"Preencha os campos em branco!", L"Aviso!", MB_OK | MB_ICONWARNING);

    } else if (id2 == 0) {
        MessageBoxW(hwnd, L"Digite apenas numeros!", L"Aviso!", MB_OK | MB_ICONWARNING);

    } else {

        for (i = 0; i < posPaciente; i++) {
            if (pacientes[i].id == id2) {
                pos = i;
                break;
            }

            pos = -1;
        }

        if (pos < 0) {
            MessageBoxW(hwnd, L"Paciente nao encontrado! Acesse o menu cadastro e cadastre o paciente!", L"Aviso!", MB_OK | MB_ICONWARNING);

        } else {
            MessageBoxW(hwnd, L"Paciente encontrado!", L"Sucesso!", MB_OK | MB_ICONINFORMATION);
            limpaTela(hwnd);
            destroiJanelas();
            janelaCriaAgendamento(hwnd, pacientes[pos]);

        }

    }
}

void criaAgendamento2(HWND hwnd) {
    char nomePaciente[100], area[20], id[4], dia[4], mes[4], ano[5];
    int id2, dia2, mes2, ano2;

    GetWindowText(hnome, nomePaciente, 100);
    GetWindowText(harea, area, 20);
    GetWindowText(hid, id, 4);
    GetWindowText(hdia, dia, 4);
    GetWindowText(hmes, mes, 4);
    GetWindowText(hano, ano, 5);

    dia2 = atoi(dia);
    mes2 = atoi(mes);
    ano2 = atoi(ano);

    char nomeLower[100], nomeAgeLower[100], areaAgeLower[20], areaLower[20];

    strcpy(nomeLower, lowerCase(nomePaciente, 100));
    strcpy(areaLower, lowerCase(area, 20));

    int i, sent = 0;
    for (i = 0; i < posAgendamento; i++) {
        strcpy(nomeAgeLower, lowerCase(agendamentos[i].nomePaciente, 100));

        if (strcmp(nomeLower, nomeAgeLower) == 0) {
            strcpy(areaAgeLower, lowerCase(agendamentos[i].area, 20));

            if (strcmp(areaAgeLower, areaLower) == 0) {
                sent = 1;
                break;
            }
        }
    }

    if (strcmp(nomePaciente, "") == 0 || strcmp(area, "") == 0 || strcmp(id, "") == 0 || strcmp(dia, "") == 0 || strcmp(mes, "") == 0 || strcmp(ano, "") == 0) {
        MessageBoxW(hwnd, L"Preencha os campos em branco!", L"Aviso!", MB_OK | MB_ICONWARNING);

    } else if (strcmp(areaLower, "fisioterapia") != 0 && strcmp(areaLower, "odontologia") != 0 && strcmp(areaLower, "psicologia") != 0) {
        MessageBoxW(hwnd, L"Area invalida! Entre com fisioterapia, odontologia ou psicologia!", L"Aviso!", MB_OK | MB_ICONWARNING);

    } else if (dia2 == 0 || mes2 == 0 || ano2 == 0) {
        MessageBoxW(hwnd, L"Digite apenas numeros nos campos da data!", L"Aviso!", MB_OK | MB_ICONWARNING);

    } else if (verificaData(dia2, mes2, ano2) == 1) {
        MessageBoxW(hwnd, L"Data invalida. Insira uma data valida!", L"Aviso!", MB_OK | MB_ICONWARNING);

    } else if (sent == 1) {
        MessageBoxW(hwnd, L"O paciente ja tem um agendamento marcado nesta area!", L"Aviso!", MB_OK | MB_ICONWARNING);

    } else {

        Data data = cria_data(dia2, mes2, ano2);

        agendamentos[posAgendamento] = cria_agendamento(pacientes[pos], data, area, idAgendamento);

        idAgendamento++;
        posAgendamento++;

        MessageBoxW(hwnd, L"Agendamento criado com sucesso!", L"Sucesso!", MB_OK | MB_ICONINFORMATION);
        limpaTela(hwnd);
        destroiJanelas();

    }

}

void cancelaAgendamento(HWND hwnd) {
    int op;
    char id[4];
    GetWindowText(hid, id, 4);
    int id2;
    id2 = atol(id);

    if (strcmp(id, "") == 0) {
        MessageBoxW(hwnd, L"Preencha os campos em branco!", L"Aviso!", MB_OK | MB_ICONWARNING);

    } else if (id2 == 0) {
        MessageBoxW(hwnd, L"Digite apenas numeros!", L"Aviso!", MB_OK | MB_ICONWARNING);

    } else {

        int i, j, achou = 0;

        for (i = 0; i < posAgendamento; i++) {
            if (id2 == agendamentos[i].codigo) {
                achou = 1;
                op = MessageBoxW(hwnd, L"Agendamento encontrado! Tem certeza que deseja excluir?",
                    L"Confirmacao!", MB_YESNO | MB_ICONINFORMATION);

                if (op == IDYES) {
                    for (j = i; j < posAgendamento - 1; j++) {
                        agendamentos[j] = agendamentos[j + 1];

                    }
                }

                posAgendamento--;
                MessageBoxW(hwnd, L"Agendamento removido com sucesso!", L"Sucesso!", MB_OK | MB_ICONINFORMATION);
                limpaTela(hwnd);
                destroiJanelas();
                break;
            }

        }

        if (achou == 0)
            MessageBoxW(hwnd, L"Agendamento nao encontrado! Acesse o menu de cadastro e cadastre o agendamento!", L"Aviso!",
                MB_OK | MB_ICONWARNING);

    }
}

void listaAgendamento(HWND hwnd) {
    CreateWindowW(L"static", L">>>> LISTA DE AGENDAMENTOS CADASTRADOS", WS_VISIBLE | WS_CHILDWINDOW, 10, 20, 400, 24, hwnd, NULL, NULL, NULL);

    if (posAgendamento == 0) {
        CreateWindowW(L"static", L"NENHUM AGENDAMENTO CADASTRADO!", WS_VISIBLE | WS_CHILDWINDOW, 10, 60, 400, 50, hwnd, NULL, NULL, NULL);

    } else {
        int i, j;
        char nomePaciente[100], area[20], dia[3], mes[3], ano[5], codigo[3], id[5];

        strcpy(lista, "");
        for (i = 0; i < posAgendamento; i++) {
            Data data = agendamentos[i].data;
            sprintf(dia, "%d", data.dia);
            sprintf(mes, "%d", data.mes);
            sprintf(ano, "%d", data.ano);
            sprintf(codigo, "%d", agendamentos[i].codigo);
            sprintf(id, "%d", agendamentos[i].codPaciente);

            strcat(lista, "Nome do Paciente: ");
            strcat(lista, agendamentos[i].nomePaciente);
            strcat(lista, "\r\n");
            strcat(lista, "ID do Paciente: ");
            strcat(lista, id);
            strcat(lista, "\r\n");
            strcat(lista, "ID Agendamento: ");
            strcat(lista, codigo);
            strcat(lista, "\r\n");
            strcat(lista, "Data do agendamento: ");
            strcat(lista, dia);
            strcat(lista, "/");
            strcat(lista, mes);
            strcat(lista, "/");
            strcat(lista, ano);
            strcat(lista, "\r\n");
            strcat(lista, "Area: ");
            strcat(lista, agendamentos[i].area);
            strcat(lista, "\r\n");
            strcat(lista, "\r\n");

        }

        hlistas = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER | ES_MULTILINE | WS_VSCROLL, 10, 60, 400, 230, hwnd, NULL, NULL, NULL);
        SetWindowText(hlistas, lista);

        hcancela = CreateWindowW(L"button", L"Voltar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 420, 265, 100, 24, (HWND) hwnd, (HMENU) BOTAO_VOLTAR, NULL, NULL);
    }
}

void criaAluno(HWND hwnd) {
    char nome[100], curso[100], cpf[12], idade[3], matricula[10];
    long int cpf2, matricula2;
    int idade2;

    GetWindowText(hnome, nome, 100);
    GetWindowText(hcurso, curso, 100);
    GetWindowText(hcpf, cpf, 12);
    GetWindowText(hidade, idade, 3);
    GetWindowText(hmatricula, matricula, 10);

    idade2 = atoi(idade);
    cpf2 = atol(cpf);
    matricula2 = atol(matricula);

    int i, contem = 0;
    for (i = 0; i < posAluno; i++) {
        cpf2 = atol(cpf);

        if (alunos[i].cpf == cpf2) {
            contem = 1;
            break;
        }
    }

    if (strcmp(nome, "") == 0 || strcmp(curso, "") == 0 || strcmp(cpf, "") == 0 || strcmp(idade, "") == 0 || strcmp(matricula, "") == 0) {
        MessageBoxW(hwnd, L"Preencha os campos em branco!", L"Aviso!", MB_OK | MB_ICONWARNING);

    } else if (idade2 == 0 || matricula2 == 0 || cpf2 == 0) {
        MessageBoxW(hwnd, L"Digite apenas numeros nos campos idade, cpf e matricula!", L"Aviso!", MB_OK | MB_ICONWARNING);

    } else if (contem == 1) {
        MessageBoxW(hwnd, L"Aluno ja cadastrado", L"Aviso!", MB_OK | MB_ICONWARNING);

    } else {
        alunos[posAluno] = cria_aluno(nome, idade2, matricula2, cpf2, curso);
        posAluno++;

        MessageBoxW(hwnd, L"Aluno criado com sucesso!", L"Sucesso!", MB_OK | MB_ICONINFORMATION);
        limpaTela(hwnd);
        destroiJanelas();

    }
}

void procuraAluno(HWND hwnd) {
    int i;
    char cpf[11];
    long int cpf2;

    GetWindowText(hcpf, cpf, 11);

    cpf2 = atol(cpf);

    if (strcmp(cpf, "") == 0) {
        MessageBoxW(hwnd, L"Preencha os campos em branco!", L"Aviso!", MB_OK | MB_ICONWARNING);

    } else if (cpf2 == 0) {
        MessageBoxW(hwnd, L"Digite apenas numeros!", L"Aviso!", MB_OK | MB_ICONWARNING);

    } else {

        for (i = 0; i < posAluno; i++) {
            if (alunos[i].cpf == cpf2) {
                pos = i;
                break;
            }

            pos = -1;
        }

        if (pos < 0) {
            MessageBoxW(hwnd, L"Aluno nao encontrado! Acesse o menu cadastro e cadastre o aluno!", L"Aviso!", MB_OK | MB_ICONWARNING);

        } else {
            MessageBoxW(hwnd, L"Aluno encontrado!", L"Sucesso!", MB_OK | MB_ICONINFORMATION);
            limpaTela(hwnd);
            destroiJanelas();
            janelaEditaAluno(hwnd, alunos[pos]);

        }

    }
}

void editaAluno(HWND hwnd) {
    char nome[100], curso[100], cpf[11], idade[3], matricula[10];
    long int cpf2, matricula2;
    int idade2;

    GetWindowText(hnome, nome, 100);
    GetWindowText(hcurso, curso, 100);
    GetWindowText(hcpf, cpf, 11);
    GetWindowText(hidade, idade, 3);
    GetWindowText(hmatricula, matricula, 10);

    cpf2 = atol(cpf);
    idade2 = atoi(idade);
    matricula2 = atol(matricula);

    int i, contem = 0;
    for (i = 0; i < posAluno; i++) {
        if (alunos[i].cpf == cpf2 && i != pos) {
            contem = 1;
            break;
        }
    }

    if (strcmp(nome, "") == 0 || strcmp(curso, "") == 0 || strcmp(cpf, "") == 0 || strcmp(idade, "") == 0 || strcmp(matricula, "") == 0) {
        MessageBoxW(hwnd, L"Preencha os campos em branco!", L"Aviso!", MB_OK | MB_ICONWARNING);

    } else if (cpf2 == 0 || matricula2 == 0 || idade2 == 0) {
        MessageBoxW(hwnd, L"Digite apenas numeros nos campos idade, cpf e matricula!", L"Aviso!", MB_OK | MB_ICONWARNING);

    } else if (contem == 1) {
        MessageBoxW(hwnd, L"Este CPF ja esta cadastrado!", L"Aviso!", MB_OK | MB_ICONWARNING);

    } else {

        alunos[pos].cpf = cpf2;
        strcpy(alunos[pos].nome, nome);
        strcpy(alunos[pos].curso, curso);
        alunos[pos].idade = idade2;
        alunos[pos].matricula = matricula2;

        MessageBoxW(hwnd, L"Alteracoes feitas com sucesso!", L"Sucesso!", MB_OK | MB_ICONINFORMATION);
        limpaTela(hwnd);
        destroiJanelas();
    }

}

void removeAluno(HWND hwnd) {
    int op;
    char cpf[11];
    long int cpf2;

    GetWindowText(hcpf, cpf, 11);
    cpf2 = atol(cpf);

    if (strcmp(cpf, "") == 0) {
        MessageBoxW(hwnd, L"Preencha os campos em branco!", L"Aviso!", MB_OK | MB_ICONWARNING);

    } else if (cpf2 == 0) {
        MessageBoxW(hwnd, L"Digite apenas numeros!", L"Aviso!", MB_OK | MB_ICONWARNING);

    } else {
        int i, j, achou = 0;

        for (i = 0; i < posAluno; i++) {
            if (cpf2 == alunos[i].cpf) {
                achou = 1;
                op = MessageBoxW(hwnd, L"Aluno encontrado! Tem certeza que deseja excluir?",
                    L"Confirmacao!", MB_YESNO | MB_ICONINFORMATION);

                if (op == IDYES) {
                    for (j = i; j < posAluno - 1; j++) {
                        alunos[j] = alunos[j + 1];
                    }

                    posAluno--;
                    MessageBoxW(hwnd, L"Aluno removido com sucesso!", L"Sucesso!", MB_OK | MB_ICONINFORMATION);
                    limpaTela(hwnd);
                    destroiJanelas();

                }

                break;
            }

        }

        if (achou == 0)
            MessageBoxW(hwnd, L"Aluno nao encontrado! Acesse o menu cadastro e cadastre o aluno!", L"Aviso!", MB_OK | MB_ICONWARNING);

    }

}

void listaAluno(HWND hwnd) {
    CreateWindowW(L"static", L">>>> LISTA DE ALUNOS CADASTRADOS", WS_VISIBLE | WS_CHILDWINDOW, 10, 20, 400, 24, hwnd, NULL, NULL, NULL);

    if (posAluno == 0) {
        CreateWindowW(L"static", L"NENHUM ALUNO CADASTRADO!", WS_VISIBLE | WS_CHILDWINDOW, 10, 60, 400, 50, hwnd, NULL, NULL, NULL);

    } else {
        int i;
        char cpf[11], idade[3], matricula[11], num[3];

        strcpy(lista, "");
        for (i = 0; i < posAluno; i++) {
            sprintf(cpf, "%ld", alunos[i].cpf);
            sprintf(matricula, "%ld", alunos[i].matricula);
            sprintf(idade, "%d", alunos[i].idade);

            strcat(lista, "Aluno: ");
            strcat(lista, alunos[i].nome);
            strcat(lista, "\r\n");
            strcat(lista, "Idade: ");
            strcat(lista, idade);
            strcat(lista, "\r\n");
            strcat(lista, "Curso: ");
            strcat(lista, alunos[i].curso);
            strcat(lista, "\r\n");
            strcat(lista, "Matricula: ");
            strcat(lista, matricula);
            strcat(lista, "\r\n");
            strcat(lista, "CPF: ");
            strcat(lista, cpf);
            strcat(lista, "\r\n");
            strcat(lista, "\r\n");

        }

        /*strcat(lista, "Idade: ");
        strcat(lista, alunoGetIdade(alunos[0]));*/
        hlistas = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER | ES_MULTILINE | WS_VSCROLL, 10, 60, 400, 230, hwnd, NULL, NULL, NULL);
        SetWindowText(hlistas, lista);

        hcancela = CreateWindowW(L"button", L"Voltar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 420, 265, 100, 24, (HWND) hwnd, (HMENU) BOTAO_VOLTAR, NULL, NULL);
    }

}

void criaPaciente(HWND hwnd) {
    char nome[100], endereco[100], cpf[11], dia[4], mes[4], ano[5];
    int id2, dia2, mes2, ano2;
    long int cpf2;

    GetWindowText(hnome, nome, 100);
    GetWindowText(hendereco, endereco, 100);
    GetWindowText(hcpf, cpf, 11);
    GetWindowText(hdia, dia, 4);
    GetWindowText(hmes, mes, 4);
    GetWindowText(hano, ano, 5);

    dia2 = atoi(dia);
    mes2 = atoi(mes);
    ano2 = atoi(ano);
    cpf2 = atol(cpf);

    printf("soma %d\n", dia2 + mes2 + ano2);

    cpf2 = atol(cpf);
    int i, contem = 0;
    for (i = 0; i < posPaciente; i++) {
        if (pacientes[i].cpf == cpf2) {
            contem = 1;
            break;
        }
    }

    if (strcmp(nome, "") == 0 || strcmp(endereco, "") == 0 || strcmp(cpf, "") == 0) {
        MessageBoxW(hwnd, L"Preencha os campos em branco!", L"Aviso!", MB_OK | MB_ICONWARNING);

    } else if (dia2 == 0 || mes2 == 0 || ano2 == 0 || cpf2 == 0) {
        MessageBoxW(hwnd, L"Digite apenas numeros nos campos da data e do cpf!", L"Aviso!", MB_OK | MB_ICONWARNING);

    } else if (contem == 1) {
        MessageBoxW(hwnd, L"Paciente ja cadastrado!", L"Aviso!", MB_OK | MB_ICONWARNING);

    } else if (dia2 > 31 || mes2 > 12) {
        MessageBoxW(hwnd, L"Data invalida. Insira uma data valida!", L"Aviso!", MB_OK | MB_ICONWARNING);

    } else {
        Data data = cria_data(dia2, mes2, ano2);

        pacientes[posPaciente] = cria_paciente(idPaciente, nome, data, cpf2, endereco);
        posPaciente++;
        idPaciente++;

        MessageBoxW(hwnd, L"Paciente criado com sucesso!", L"Sucesso!", MB_OK | MB_ICONINFORMATION);
        limpaTela(hwnd);
        destroiJanelas();

    }
}

void procuraPaciente(HWND hwnd) {
    int i;
    char cpf[11];
    long int cpf2;

    GetWindowText(hcpf, cpf, 11);
    cpf2 = atol(cpf);

    if (strcmp(cpf, "") == 0) {
        MessageBoxW(hwnd, L"Preencha os campos em branco!", L"Aviso!", MB_OK | MB_ICONWARNING);

    } else if (cpf2 == 0) {
        MessageBoxW(hwnd, L"Digite apenas numeros!", L"Aviso!", MB_OK | MB_ICONWARNING);

    } else {

        for (i = 0; i < posPaciente; i++) {
            if (pacientes[i].cpf == cpf2) {
                pos = i;
                break;
            }

            pos = -1;
        }

        if (pos < 0) {
            MessageBoxW(hwnd, L"Paciente nao encontrado! Acesse o menu cadastro e cadastre o paciente!", L"Aviso!", MB_OK | MB_ICONWARNING);

        } else {
            MessageBoxW(hwnd, L"Paciente encontrado!", L"Sucesso!", MB_OK | MB_ICONINFORMATION);
            limpaTela(hwnd);
            destroiJanelas();
            janelaEditaPaciente(hwnd, pacientes[i]);

        }

    }
}

void editaPaciente(HWND hwnd) {
    char nome[100], endereco[100], cpf[11], idade[10], dia[4], mes[4], ano[5];
    long int cpf2;
    int dia2, mes2, ano2;

    GetWindowText(hnome, nome, 100);
    GetWindowText(hendereco, endereco, 100);
    GetWindowText(hcpf, cpf, 11);
    GetWindowText(hdia, dia, 4);
    GetWindowText(hmes, mes, 4);
    GetWindowText(hano, ano, 5);

    cpf2 = atol(cpf);
    dia2 = atoi(dia);
    mes2 = atoi(mes);
    ano2 = atoi(ano);

    int i, contem = 0;
    for (i = 0; i < posPaciente; i++) {
        if (pacientes[i].cpf == cpf2 && i != pos) {
            contem = 1;
            break;
        }
    }

    if (strcmp(nome, "") == 0 || strcmp(endereco, "") == 0 || strcmp(cpf, "") == 0) {
        MessageBoxW(hwnd, L"Preencha os campos em branco!", L"Aviso!", MB_OK | MB_ICONWARNING);

    } else if (dia2 == 0 || mes2 == 0 || ano2 == 0 || cpf2 == 0) {
        MessageBoxW(hwnd, L"Digite apenas numeros nos campos da data e do cpf!", L"Aviso!", MB_OK | MB_ICONWARNING);

    } else if (dia2 > 31 || mes2 > 12) {
        MessageBoxW(hwnd, L"Data invalida. Insira uma data valida!", L"Aviso!", MB_OK | MB_ICONWARNING);

    } else if (contem == 1) {
        MessageBoxW(hwnd, L"Este CPF ja esta cadastrado!", L"Aviso!", MB_OK | MB_ICONWARNING);

    } else {

        Data data = cria_data(dia2, mes2, ano2);

        pacientes[pos].cpf = cpf2;
        strcpy(pacientes[pos].nome, nome);
        strcpy(pacientes[pos].endereco, endereco);
        pacientes[pos].data = data;

        MessageBoxW(hwnd, L"Alteracoes feitas com sucesso!", L"Sucesso!", MB_OK | MB_ICONINFORMATION);
        limpaTela(hwnd);
        destroiJanelas();
    }
}

void removePaciente(HWND hwnd) {
    int op;
    char cpf[11];
    long int cpf2;

    GetWindowText(hcpf, cpf, 11);
    cpf2 = atol(cpf);

    if (strcmp(cpf, "") == 0) {
        MessageBoxW(hwnd, L"Preencha os campos em branco!", L"Aviso!", MB_OK | MB_ICONWARNING);

    } else if (cpf2 == 0) {
        MessageBoxW(hwnd, L"Digite apenas numeros!", L"Aviso!", MB_OK | MB_ICONWARNING);

    } else {
        int i, j, achou = 0;

        for (i = 0; i < posPaciente; i++) {
            if (cpf2 == pacientes[i].cpf) {
                achou = 1;
                op = MessageBoxW(hwnd, L"Paciente encontrado! Tem certeza que deseja excluir?",
                    L"Confirmacao!", MB_YESNO | MB_ICONINFORMATION);

                if (op == IDYES) {
                    for (j = i; j < posPaciente - 1; j++) {
                        pacientes[j] = pacientes[j + 1];

                    }

                    posPaciente--;
                    MessageBoxW(hwnd, L"Paciente removido com sucesso!", L"Sucesso!", MB_OK | MB_ICONINFORMATION);
                    limpaTela(hwnd);
                    destroiJanelas();
                }

                break;
            }

        }

        if (achou == 0)
            MessageBoxW(hwnd, L"Paciente nao encontrado! Acesse o menu cadastro e cadastre o paciente!", L"Aviso!", MB_OK | MB_ICONWARNING);

    }

}

void listaPaciente(HWND hwnd) {
    CreateWindowW(L"static", L">>>> LISTA DE PACIENTES CADASTRADOS", WS_VISIBLE | WS_CHILDWINDOW, 10, 20, 400, 24, hwnd, NULL, NULL, NULL);

    if (posPaciente == 0) {
        CreateWindowW(L"static", L"NENHUM PACIENTE CADASTRADO!", WS_VISIBLE | WS_CHILDWINDOW, 10, 60, 400, 50, hwnd, NULL, NULL, NULL);

    } else {
        int i;
        char lista[1000], cpf[11], num[3], id[3], dia[10], mes[10], ano[10];

        strcpy(lista, "");
        for (i = 0; i < posPaciente; i++) {
            sprintf(cpf, "%ld", pacientes[i].cpf);
            sprintf(id, "%d", pacientes[i].id);
            sprintf(dia, "%d", pacientes[i].data.dia);
            sprintf(mes, "%d", pacientes[i].data.mes);
            sprintf(ano, "%d", pacientes[i].data.ano);

            strcat(lista, "ID: ");
            strcat(lista, id);
            strcat(lista, "\r\n");
            strcat(lista, "Paciente: ");
            strcat(lista, pacientes[i].nome);
            strcat(lista, "\r\n");
            strcat(lista, "Data de nascimento: ");
            strcat(lista, dia);
            strcat(lista, "/");
            strcat(lista, mes);
            strcat(lista, "/");
            strcat(lista, ano);
            strcat(lista, "\r\n");
            strcat(lista, "Endereco: ");
            strcat(lista, pacientes[i].endereco);
            strcat(lista, "\r\n");
            strcat(lista, "CPF: ");
            strcat(lista, cpf);
            strcat(lista, "\r\n");
            strcat(lista, "\r\n");

        }

        hlistas = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER | ES_MULTILINE | WS_VSCROLL, 10, 60, 400, 230, hwnd, NULL, NULL, NULL);
        SetWindowText(hlistas, lista);

        hcancela = CreateWindowW(L"button", L"Voltar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 420, 265, 100, 24, (HWND) hwnd, (HMENU) BOTAO_VOLTAR, NULL, NULL);

    }

}

void criaSupervisor(HWND hwnd) {
    char nome[100], curso[100], id[11];

    GetWindowText(hnome, nome, 100);
    GetWindowText(hcurso, curso, 100);
    GetWindowText(hid, id, 11);

    int id2 = atoi(id);
    int i, contem = 0;
    for (i = 0; i < posSupervisor; i++) {
        if (supervisores[i].codigo == id2) {
            contem = 1;
            break;
        }
    }

    if (strcmp(nome, "") == 0 || strcmp(curso, "") == 0 || strcmp(id, "") == 0) {
        MessageBoxW(hwnd, L"Preencha os campos em branco!", L"Aviso!", MB_OK | MB_ICONWARNING);

    } else if (id2 == 0) {
        MessageBoxW(hwnd, L"Digite apenas numeros no campo ID!", L"Aviso!", MB_OK | MB_ICONWARNING);

    } else if (contem == 1) {
        MessageBoxW(hwnd, L"Supervisor ja cadastrado!", L"Aviso!", MB_OK | MB_ICONWARNING);

    } else {

        supervisores[posSupervisor] = cria_supervisor(idSupervisor, nome, curso, id2);
        posSupervisor++;
        idSupervisor++;

        MessageBoxW(hwnd, L"Supervisor criado com sucesso!", L"Sucesso!", MB_OK | MB_ICONINFORMATION);
        limpaTela(hwnd);
        destroiJanelas();

    }

}

void procuraSupervisor(HWND hwnd) {
    int i;
    char id[4];
    int id2;

    GetWindowText(hid, id, 4);
    id2 = atoi(id);

    if (strcmp(id, "") == 0) {
        MessageBoxW(hwnd, L"Preencha os campos em branco!", L"Aviso!", MB_OK | MB_ICONWARNING);

    } else if (id2 == 0) {
        MessageBoxW(hwnd, L"Digite apenas numeros!", L"Aviso!", MB_OK | MB_ICONWARNING);

    } else {

        for (i = 0; i < posSupervisor; i++) {
            if (supervisores[i].id == id2) {
                pos = i;
                break;
            }

            pos = -1;
        }

        if (pos < 0) {
            MessageBoxW(hwnd, L"Supervisor nao encontrado! Acesse o menu cadastro e cadastre o supervisor!", L"Aviso!", MB_OK | MB_ICONWARNING);

        } else {
            MessageBoxW(hwnd, L"Supervisor encontrado!", L"Sucesso!", MB_OK | MB_ICONINFORMATION);
            limpaTela(hwnd);
            destroiJanelas();
            janelaEditaSupervisor(hwnd, supervisores[i]);

        }

    }

}

void editaSupervisor(HWND hwnd) {
    char nome[100], curso[100], id[11];

    GetWindowText(hnome, nome, 100);
    GetWindowText(hcurso, curso, 100);
    GetWindowText(hid, id, 11);

    int id2 = atoi(id);
    int i, contem = 0;
    for (i = 0; i < posSupervisor; i++) {
        if (supervisores[i].codigo == id2 && i != pos) {
            contem++;
            break;
        }
    }

    if (strcmp(nome, "") == 0 || strcmp(curso, "") == 0 || strcmp(id, "") == 0) {
        MessageBoxW(hwnd, L"Preencha os campos em branco!", L"Aviso!", MB_OK | MB_ICONWARNING);

    } else if (id2 == 0) {
        MessageBoxW(hwnd, L"Digite apenas numeros no campo ID!", L"Aviso!", MB_OK | MB_ICONWARNING);

    } else if (contem == 1) {
        MessageBoxW(hwnd, L"Este CPF ja esta cadastrado!", L"Aviso!", MB_OK | MB_ICONWARNING);

    } else {
        strcpy(supervisores[pos].nome, nome);
        strcpy(supervisores[pos].curso, curso);
        supervisores[pos].codigo = id2;

        MessageBoxW(hwnd, L"Alteracoes feitas com sucesso!", L"Sucesso!", MB_OK | MB_ICONINFORMATION);
        limpaTela(hwnd);
        destroiJanelas();
    }

}

void removeSupervisor(HWND hwnd) {
    int op;
    char id[3];
    GetWindowText(hid, id, 3);

    if (strcmp(id, "") == 0) {
        MessageBoxW(hwnd, L"Preencha os campos em branco!", L"Aviso!", MB_OK | MB_ICONWARNING);

    } else {
        int i, j, achou = 0;
        int id2;
        id2 = atoi(id);

        for (i = 0; i < posSupervisor; i++) {
            if (id2 == supervisores[i].id) {
                achou = 1;
                op = MessageBoxW(hwnd, L"Supervisor encontrado! Tem certeza que deseja excluir?",
                    L"Confirmacao!", MB_YESNO | MB_ICONINFORMATION);

                if (op == IDYES) {
                    for (j = i; j < posSupervisor - 1; j++) {
                        supervisores[j] = supervisores[j + 1];

                    }

                    posSupervisor--;
                    MessageBoxW(hwnd, L"Supervisor removido com sucesso!", L"Sucesso!", MB_OK | MB_ICONINFORMATION);
                    limpaTela(hwnd);
                    destroiJanelas();
                }

                break;
            }

        }

        if (achou == 0)
            MessageBoxW(hwnd, L"Paciente nao encontrado! Acesse o menu cadastro e cadastre o paciente!", L"Aviso!", MB_OK | MB_ICONWARNING);

    }

}

void listaSupervisor(HWND hwnd) {

    CreateWindowW(L"static", L">>>> LISTA DE SUPERVISORES CADASTRADOS", WS_VISIBLE | WS_CHILDWINDOW, 10, 20, 400, 24, hwnd, NULL, NULL, NULL);

    if (posSupervisor == 0) {
        CreateWindowW(L"static", L"NENHUM SUPERVISOR CADASTRADO!", WS_VISIBLE | WS_CHILDWINDOW, 10, 60, 400, 50, hwnd, NULL, NULL, NULL);

    } else {
        int i;
        char lista[1000], id[3], codigo[11];

        strcpy(lista, "");
        for (i = 0; i < posSupervisor; i++) {
            sprintf(id, "%d", supervisores[i].id);
            sprintf(codigo, "%d", supervisores[i].codigo);

            strcat(lista, "ID: ");
            strcat(lista, id);
            strcat(lista, "\r\n");
            strcat(lista, "Supervisor: ");
            strcat(lista, supervisores[i].nome);
            strcat(lista, "\r\n");
            strcat(lista, "Curso: ");
            strcat(lista, supervisores[i].curso);
            strcat(lista, "\r\n");
            strcat(lista, "Codigo: ");
            strcat(lista, codigo);
            strcat(lista, "\r\n");
            strcat(lista, "\r\n");

        }

        hlistas = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER | ES_MULTILINE | WS_VSCROLL, 10, 60, 400, 230, hwnd, NULL, NULL, NULL);
        SetWindowText(hlistas, lista);

        hcancela = CreateWindowW(L"button", L"Voltar", WS_VISIBLE | WS_CHILDWINDOW | WS_BORDER, 420, 265, 100, 24, (HWND) hwnd, (HMENU) BOTAO_VOLTAR, NULL, NULL);
    }

}

//TODAS AS FUNCIONALIDADES DO PROGRAMA ESTAO AQUI
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    switch (msg) {

    case WM_COMMAND:
        {

        	//SELECAO DOS MENUS
        	switch (wParam) {

            case BOTAO_CANCEL:
                {
                    cancela(hwnd);
                    break;
                }
                
            case BOTAO_VOLTAR:
            	{
            		destroiJanelas();
            		limpaTela(hwnd);
            		break;
				}

            case LOGIN_OK:
                {
                    login(hwnd);
                    break;
                }

                //------------------ INICIO MENUS ------------------//

                //------------------ INICIO MENU ARQUIVO ------------------//

            case ARQUIVO_SALVAR:
                {
                    salvar(hwnd);
                    break;
                }

            case ARQUIVO_CARREGAR:
                {
                    carregar(hwnd);
                    break;
                }

            case ARQUIVO_SAIR:
				{
					fechaPrograma(hwnd);
                	break;
				}

                //------------------ FIM MENU ARQUIVO ------------------//

                //------------------ INICIO MENU ATENDIMENTO ------------------//

            case ATENDIMENTO_CRIAR:
                {
                    limpaTela(hwnd);
                    destroiJanelas();
                    janelaCriaAtendimento(hwnd);
                    break;
                }

            case ATENDIMENTO_CRIAR_OK:
                {
                    criaAtendimento(hwnd);
                    break;
                }

            case ATENDIMENTO_CRIAR_2_OK:
                {
                    criaAtendimento2(hwnd);
                    break;
                }

            case ATENDIMENTO_EDITAR:
                break;

            case ATENDIMENTO_CANCELAR:
                {
                    limpaTela(hwnd);
                    destroiJanelas();
                    janelaAtendimentoCancelar(hwnd);
                    break;
                }

            case ATEN_CANCELAR_OK:
                {
                    cancelaAtendimento(hwnd);
                    break;
                }

            case ATENDIMENTO_LISTAR_TUDO:
                {
                    limpaTela(hwnd);
                    destroiJanelas();
                    listarTudoAtendimento(hwnd);
                    break;
                }

            case ATENDIMENTO_LISTAR_ALUNO:
                {
                    limpaTela(hwnd);
                    destroiJanelas();
                    janelaListaAtendimentoAluno(hwnd);
                    break;
                }

            case ATEN_LISTAR_ALUNO_OK:
                {
                    listarAlunoAtendimento(hwnd);
                    break;
                }

            case ATENDIMENTO_LISTAR_AREA:
                {
                    limpaTela(hwnd);
                    destroiJanelas();
                    janelaListaAtendimentoArea(hwnd);
                    break;
                }

            case ATEN_LISTAR_AREA_OK:
                {
                    listarAreaAtendimento(hwnd);
                    break;
                }

            case ATENDIMENTO_LISTAR_PACIENTE:
                {
                    limpaTela(hwnd);
                    destroiJanelas();
                    janelaListaAtendimentoPaciente(hwnd);
                    break;
                }

            case ATEN_LISTAR_PACIENTE_OK:
                {
                    listarPacienteAtendimento(hwnd);
                    break;
                }

                //------------------ FIM MENU ATENDIMENTO ------------------//

                //------------------ INICIO MENU AGENDAMENTO ------------------//

            case AGENDAMENTO_CRIAR:
                {
                    limpaTela(hwnd);
                    destroiJanelas();
                    janelaAgendamentoProcuraPaciente(hwnd);
                    break;
                }

            case AGE_PROCURA_PAC_OK:
                {
                    criaAgendamento(hwnd);
                    break;
                }

            case AGE_CRIAR_OK:
                {
                    criaAgendamento2(hwnd);
                    break;
                }

            case AGENDAMENTO_EDITAR:
                MessageBeep(MB_OK);
                break;

            case AGENDAMENTO_CANCELAR:
                {
                    limpaTela(hwnd);
                    destroiJanelas();
                    janelaCancelaAgendamento(hwnd);
                    break;
                }

            case AGE_CANCELA_OK:
                {
                    cancelaAgendamento(hwnd);
                    break;
                }

            case AGENDAMENTO_LISTAR:
                {
                    limpaTela(hwnd);
                    destroiJanelas();
                    listaAgendamento(hwnd);
                    break;
                }

                //------------------ FIM MENU AGENDAMENTO ------------------//

                //------------------ INICIO MENU ALUNO ------------------//

            case ALUNO_CRIAR:
                {
                    limpaTela(hwnd);
                    destroiJanelas();
                    janelaCriaAluno(hwnd);
                    break;
                }

            case ALUNO_CRIAR_OK:
                {
                    criaAluno(hwnd);
                    break;
                }

            case ALUNO_PROCURAR:
                {
                    limpaTela(hwnd);
                    destroiJanelas();
                    janelaProcuraAluno(hwnd);
                    break;
                }

            case ALUNO_PROCURAR_OK:
                {
                    procuraAluno(hwnd);
                    break;
                }

            case ALUNO_EDITAR:
                {
                    editaAluno(hwnd);
                    break;
                }

            case ALUNO_REMOVER:
                {
                    limpaTela(hwnd);
                    destroiJanelas();
                    janelaDeletaAluno(hwnd);
                    break;
                }

            case ALUNO_REMOVE_OK:
                {
                    removeAluno(hwnd);
                    break;
                }

            case ALUNO_LISTAR:
                {
                    limpaTela(hwnd);
                    destroiJanelas();
                    listaAluno(hwnd);
                    break;
                }

                //------------------ FIM MENU ALUNO ------------------//

                //------------------ INICIO MENU PACIENTE ------------------//

            case PACIENTE_CRIAR:
                {
                    limpaTela(hwnd);
                    destroiJanelas();
                    janelaCriaPaciente(hwnd);
                    break;
                }

            case PACIENTE_CRIAR_OK:
                {
                    criaPaciente(hwnd);
                    break;
                }

            case PACIENTE_EDITAR:
                {
                    limpaTela(hwnd);
                    destroiJanelas();
                    janelaProcuraPaciente(hwnd);
                    break;
                }

            case PACIENTE_PROCURAR_OK:
                {
                    procuraPaciente(hwnd);
                    break;
                }

            case PACIENTE_EDITAR_OK:
                {
                    editaPaciente(hwnd);
                    break;
                }

            case PACIENTE_REMOVER:
                {
                    limpaTela(hwnd);
                    destroiJanelas();
                    janelaRemovePaciente(hwnd);
                    break;
                }

            case PACIENTE_REMOVE_OK:
                {
                    removePaciente(hwnd);
                    break;
                }

            case PACIENTE_LISTAR:
                {
                    limpaTela(hwnd);
                    destroiJanelas();
                    listaPaciente(hwnd);
                    break;
                }

                //------------------ FIM MENU PACIENTE ------------------//

                //------------------ INICIO MENU SUPERVISOR ------------------//

            case SUPERVISOR_CRIAR:
                {
                    limpaTela(hwnd);
                    destroiJanelas();
                    janelaCriaSupervisor(hwnd);
                    break;
                }

            case SUPERVISOR_CRIAR_OK:
                {
                    criaSupervisor(hwnd);
                    break;
                }

            case SUPERVISOR_EDITAR:
                {
                    limpaTela(hwnd);
                    destroiJanelas();
                    janelaProcuraSupervisor(hwnd);
                    break;
                }

            case SUPERVISOR_PROCURAR_OK:
                {
                    procuraSupervisor(hwnd);
                    break;
                }

            case SUPERVISOR_EDITAR_OK:
                {
                    editaSupervisor(hwnd);
                    break;
                }

            case SUPERVISOR_REMOVER:
                {
                    limpaTela(hwnd);
                    destroiJanelas();
                    janelaRemoveSupervisor(hwnd);
                    break;
                }

            case SUPERVISOR_REMOVE_OK:
                {
                    removeSupervisor(hwnd);
                    break;
                }

            case SUPERVISOR_LISTAR:
                {
                    limpaTela(hwnd);
                    destroiJanelas();
                    listaSupervisor(hwnd);
                    break;
                }

                //------------------ FIM MENU SUPERVISOR ------------------//

                //------------------ FIM MENUS ------------------//
            }

            break;
        }

    //CRIA OS MENUS DAS JANELAS E CONTROLES
    case WM_CREATE:
        {
            limpaTela(hwnd);
            janelaLogin(hwnd);
            break;
        }

    case WM_CLOSE:
        {
            int op;

            op = MessageBoxW(NULL, L"Deseja realmente fechar o programa?", L"SAIR", MB_YESNO | MB_ICONWARNING);
            if (op == IDYES)
                DestroyWindow(hwnd);

            break;
        }

    case WM_DESTROY:
        {
            DestroyWindow(hwnd);
            PostQuitMessage(0);
            break;
        }

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    return 0;
}

//MAIN DA JANELA PRINCIPAL
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow) {

  WNDCLASSEX wc; //CLASSE PRINCIPAL
  HWND hwnd; // HANDLER DA CLASSE PRINCIPAL
  MSG Msg; // VARIAVEL PARA CONTROLAR O QUE ACONTECE NA JANELA

  wc.cbSize = sizeof(WNDCLASSEX); // tamanho da struct WNDCLASSX
  wc.style = 0; // estilo da janela
  wc.lpfnWndProc = WndProc; // Callback da janela
  wc.cbClsExtra = 0; // memoria extra para esta janela (0 = nenhuma)
  wc.cbWndExtra = 0; //  memoria extra para outras janelas criadas a partir desta (0 = nenhuma)
  wc.hInstance = hInstance; // identificador recebido no winmain
  wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); // icone a ser mostrado no alt + tab
  wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // cor do plano de fundo (tem que dar cast para o tipo HBRUSH)
  wc.lpszMenuName = NULL; // se for menu
  wc.lpszClassName = g_szClassName; // nome da classe
  wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION); // icone a ser mostrado na barra de tarefas
  wc.hCursor = LoadCursor(NULL, IDC_ARROW); // serve para mostrar o cursor dentro da aplicacao(IDC_ARROW = tipo do cursor)

  // tenta registrar a struct wc, se nao conseguir retorna um erro
  if (!RegisterClassEx( & wc)) {
    MessageBox(NULL, "Falha no registro da janela!", "Error", MB_ICONEXCLAMATION | MB_OK);
    return 0;
  }

  //seta a borda da janela, nome da janela principal, titulo da janela, estilo da janela, coordenada x, coordenada y,
  //largura, altura, NULL porque esta janela � a main, nao tem parentes, NULL porque nao tem menu ate o momento, parametro passado no main,
  //NULL porque n cria dados
  hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, g_szClassName, "CLINICA", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 600, 400, NULL, NULL, hInstance, NULL);

  // se null(0), significa que a criacao da janela falhou
  if (hwnd == NULL) {
    MessageBox(NULL, "Falha na criacao da janela!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    return 0;
  }

  ShowWindow(hwnd, nCmdShow); // mostra a janela usando o ultimo comando recebido no main como parametro;
  UpdateWindow(hwnd); //atualiza a janela para verificar se vai ser mostrada corretamente

  //loop principal da janela
  while (GetMessage( & Msg, NULL, 0, 0) > 0) {
    TranslateMessage( & Msg);
    DispatchMessage( & Msg);
  }

  return Msg.wParam;

}
