typedef struct data Data;

Data *cria_data(int dia, int mes, int ano);

int getDia(Data *data);

int getMes(Data *data);

int getAno(Data *data);

void setDia(Data *data, int dia);

void setMes(Data *data, int mes);

void setAno(Data *data, int ano);

void dataToString(Data *data);
