#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

struct Data{
	
	int dia, mes, ano;
	
};

Data *cria_data(int dia, int mes, int ano){
	
	struct Data *data = (Data*) malloc(sizeof(data));
	
	data -> dia = dia;
	data -> mes = mes;
	data -> ano = ano;
	
	return data;
}

int getDia(Data *data){
	struct Data *dataux = (Data*) malloc(sizeof(dataux));
	dataux = data;
	
	return dataux -> dia;
}

int getMes(Data *data){
	struct Data *dataux = (Data*) malloc(sizeof(dataux));
	dataux = data;
	
	return dataux -> mes;
}

int getAno(Data *data){
	struct Data *dataux = (Data*) malloc(sizeof(dataux));
	dataux = data;
	
	return dataux -> ano;
}

void setDia(Data *data, int dia){
	struct Data *dataux = (Data*) malloc(sizeof(dataux));
	dataux = data;
	
	dataux -> dia = dia;
	data = dataux;
}

void setMes(Data *data, int mes){
	struct Data *dataux = (Data*) malloc(sizeof(dataux));
	dataux = data;
	
	dataux -> dia = mes;
	data = dataux;
}

void setAno(Data *data, int ano){
	struct Data *dataux = (Data*) malloc(sizeof(dataux));
	dataux = data;
	
	dataux -> dia = ano;
	data = dataux;
}

void dataToString(Data *data){
	struct Data *dataux = (Data*) malloc(sizeof(dataux));
	dataux = data;
	
	printf("%d/%d/%d\n", dataux -> dia, dataux -> mes, dataux -> ano);
	
}
