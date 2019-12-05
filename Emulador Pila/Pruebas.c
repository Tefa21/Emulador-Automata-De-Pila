#include <iostream>
#include <string.h>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define FIRST 0

//ESTADOS AFD
#define COMENTARIO 1
#define ESTADO_INICIAL 2
#define ESTADOS 3
#define SIMBOLOS_PILA 4
#define ALFABETO 5
#define ESTADO_ACEPTACION 6
#define FONDO_PILA 7
#define IGUAL 8
#define LLAVE_I 9
#define LLAVE_F 10
#define COMA 11
#define VACIO 12
#define ID 13
#define ENTER 14
#define ESPACIO 15





#define Error 100



void ObtieneToken(string Linea, char *Cadena);
char EstadoInicial(string Linea);

int main() {
	fstream Archivo;
	string NombreArchivo;
	string Linea;

	cout << "Ingrese La Direccion Del Archivo De Texto: ";
	getline(cin, NombreArchivo);
	Archivo.open(NombreArchivo.c_str(),ios::in);


	if (Archivo.is_open()) {
		while (!Archivo.eof()) {
			getline(Archivo, Linea);
			char *Cadena=strdup(Linea.c_str());
			ObtieneToken(Linea, Cadena);
		}

		Archivo.close();
	}else cout << "No Se Encontro El Archivo" << endl;
	return 0;
}

void ObtieneToken(string Linea, char *Cadena) {
    string Lexema;
    char *ptr;
	ptr = strtok(Cadena, " ");
	bool STOP = false;
	int Estado = FIRST;
	bool Digi= false;

	for(int i=0;i<strlen(Cadena);i++){
        Lexema = Lexema+Cadena[i];
	}

	while (STOP==false){
            switch(Estado){
                case FIRST:
                    if(Lexema=="/+"){
                        Estado = COMENTARIO;
                    }else if(Lexema=="S"){
                        Estado = ESTADOS;
                    }else if(Lexema=="S0"){
                        Estado = ESTADO_INICIAL;
                    }else if(Lexema=="A"){
                        Estado = ALFABETO;
                    }else if(Lexema=="AC"){
                        Estado = SIMBOLOS_PILA;
                    }else if(Lexema=="T"){
                        Estado = ESTADO_ACEPTACION;
                    }else if(Lexema=="Z0"){
                        Estado = FONDO_PILA;
                    }else if(Lexema==""){
                        cout << Linea << endl;
                        STOP = true;
                    }else{
                        cout << "\nERROR DE SINTAXIS" << endl;
                        exit(1);
                    }
                break;

                case COMENTARIO:
                    cout << Linea << endl;
                    STOP = true;
                break;


                case ESTADO_INICIAL:
                    EstadoInicial(Linea);
                    STOP = true;
                break;

                case ESTADOS:
                    cout << "Estados" << endl;
                    STOP = true;
                break;

                case SIMBOLOS_PILA:
                    cout << "Simbolos" << endl;
                    STOP = true;
                break;

                case ALFABETO:
                    cout << "Alfabeto" << endl;
                    STOP = true;
                break;

                case ESTADO_ACEPTACION:
                    cout << "Estado Aceptacion" << endl;
                    STOP = true;
                break;

                case FONDO_PILA:
                    cout << "Fondo Pila" << endl;
                    STOP = true;
                break;

                case ENTER:
                    cout << "\n" << endl;
                    STOP = true;
                break;

                case ID:
                    cout << "ID" << endl;
                    STOP = true;
                break;

            }
    }
}

char EstadoInicial(string Linea){
    char *Cadena=strdup(Linea.c_str());
    char *ptr = strtok(Cadena, " ");
	bool STOP = false;
	int Estado = FIRST;
	bool ET= false;
	if(ptr != NULL){
        while(ptr != NULL){
            if(ptr=="S0"){
                ptr = strtok(NULL, " ");
            }else if(ptr=="="){
                ptr = strtok(NULL, " ");
            }else{
                ptr = strtok(NULL, " ");
                ptr = strtok(NULL, " ");
                char *Lex = strtok(ptr, " ");

            }
        }
    }

}
