typedef struct supervisor Supervisor;

Supervisor *cria_supervisor(int id, char nome[100], char curso[100], int codigo);

int supervisorGetId(Supervisor *supervisor);

char* supervisorGetNome(Supervisor *supervisor);

char* supervisorGetCurso(Supervisor *supervisor);

int supervisorGetCodigo(Supervisor *supervisor);

void supervisorSetCodigo(Supervisor *supervisor, int codigo);

void supervisorSetId(Supervisor *supervisor, int id);

void supervisorSetNome(Supervisor *supervisor, char nome[100]);

void supervisorSetCurso(Supervisor *supervisor, char curso[100]);

void supervisorToString(Supervisor *supervisor);
