typedef struct aluno Aluno;

Aluno *cria_aluno(char nome[100],int idade, long int matricula, long int cpf, char curso[100]);

long int alunoGetMatricula(Aluno *aluno);

long int alunoGetCpf(Aluno *aluno);

int alunoGetIdade(Aluno *aluno);

char* alunoGetNome(Aluno *aluno);

char* alunoGetCurso(Aluno *aluno);

void alunoSetMatricula(Aluno *aluno, long int mat);

void alunoSetCpf(Aluno *aluno, long int cpf);

void alunoSetIdade(Aluno *aluno, int idade);

void alunoSetNome(Aluno *aluno, char nome[100]);

void alunoSetCurso(Aluno *aluno, char curso[100]);

void alunoToString(Aluno *aluno);
