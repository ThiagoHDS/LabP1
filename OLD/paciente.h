typedef struct paciente Paciente;

Paciente *cria_paciente(int id, char nome[100], char idade[10], long int cpf, char endereco[100]);

int pacienteGetId(Paciente *paciente);

long int pacienteGetCpf(Paciente *paciente);

char* pacienteGetIdade(Paciente *paciente);

char* pacienteGetNome(Paciente *paciente);

char* pacienteGetEndereco(Paciente *paciente);

void pacienteSetId(Paciente *paciente, int id);

void pacienteSetCpf(Paciente *paciente, long int cpf);

void pacienteSetIdade(Paciente *paciente, char idade[10]);

void pacienteSetNome(Paciente *paciente, char nome[100]);

void pacienteSetEndereco(Paciente *paciente, char endereco[100]);

void pacienteToString(Paciente *paciente);
