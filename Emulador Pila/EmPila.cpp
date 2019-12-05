#include <iostream>
#include <string.h>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stack>
#include <list>
#include <ctype.h>
#include <algorithm>

using namespace std;

/*ESTADOS AFD*/
#define S_UNO 1
#define S_DOS 2
#define S_TRES 3
#define S_CUATRO 4
#define S_CINCO 5
#define S_SEIS 6
#define S_SIETE 7
#define S_OCHO 8
#define S_NUEVE 10
#define S_DIEZ 11
#define S_ONCE 12
#define S_DOCE 13
#define S_IGUAL 14
#define S_LLAVEI 15
#define S_LLAVEF 16
#define S_COMA 17
#define S_VACIO 18
#define S_ID 19
#define S_PARI 20
#define S_PARF 21

/*ESTADOS TOKEN*/
#define COMENTARIO 100
#define ESTADO_INICIAL 150
#define ESTADOS 200
#define SIMBOLOS_PILA 250
#define ALFABETO 300
#define ACEPTACION 350
#define FONDO_PILA 400
#define IGUAL 450
#define LLAVEI 500
#define LLAVEF 550
#define COMA 600
#define VACIO 650
#define ID 700
#define PARI 750
#define PARF 800
#define INICIAL 40
#define ERROR 900

int token;
string Id, IdTrans, Linea, Cadena;
char *cursor;
bool P = false;
bool Val = false;
stack<string> Pila;                 /*Pila */
list<string> Stados;                /*Lista Estados*/
list<string> StadoIni;              /*Lista EstadoInicial*/
list<string> Alfa;                  /*Lista Alfabeto*/
list<string> AlfaC;                 /*Lista Simbolos Alfabeto*/
list<string> ET;                    /*Lista Estados Terminacion*/
list<string> Fondo;                 /*Lista Fondo Pila*/
list<string> Transiciones;          /*Lista Transiciones*/
list<string>::iterator Ptr;         /*Puntero para Transiciones*/

struct nodo{
    string Estado;
    string Lectura;
    string Tope;
    string MoveU;
    string MoveP;
    string MoveStado;
    struct nodo *siguiente;
};
typedef struct nodo *NTrans;
NTrans ListaTrans = NULL;

char TomaCaracter(){
    int alto = 0;
    char caracter;
    while (!alto){
        if ((*cursor == 9)||(*cursor == 32)){
            cursor++;
        }else{
            caracter = *cursor;
            cursor++;
            return caracter;
        }
    }
}

bool Aceptacion(int Estado){
    bool Stop = false;
    switch(Estado){
        case S_DOS :    token = COMENTARIO; Stop=true; return Stop; break;
        case S_CUATRO :    token = ESTADO_INICIAL; Stop=true; return Stop;  break;
        case S_CINCO :    token = ESTADOS; Stop=true; return Stop;  break;
        case S_SIETE :    token = SIMBOLOS_PILA; Stop=true; return Stop;  break;
        case S_OCHO :    token = ALFABETO; Stop=true; return Stop;  break;
        case S_NUEVE :    token = ACEPTACION; Stop=true; return Stop;  break;
        case S_DIEZ :    token = FONDO_PILA; Stop=true; return Stop;  break;
        case S_IGUAL :    token = IGUAL; Stop=true; return Stop;  break;
        case S_LLAVEI :    token = LLAVEI; Stop=true; return Stop;  break;
        case S_LLAVEF :    token = LLAVEF; Stop=true; return Stop;  break;
        case S_COMA :    token = COMA; Stop=true; return Stop;  break;
        case S_VACIO :    token = VACIO; Stop=true; return Stop;  break;
        case S_ID :    token = ID; Stop=true; return Stop;  break;
        case S_PARI :    token = PARI; Stop=true; return Stop;  break;
        case S_PARF :    token = PARF; Stop=true; return Stop;  break;
        case ERROR  :    token = ERROR; Stop=true; return Stop; break;
        default     :    return Stop;
    }
}

void TomaToken(){
  int Estado = INICIAL;
  char Simbolo;
  while (Aceptacion(Estado)== false){
        Simbolo = TomaCaracter();
     switch(Estado)  {
         case INICIAL : switch(Simbolo)  {
                            case 47 : if(P==true){ Estado = S_DOCE; cursor--; }else{ Estado = S_UNO;      }  break;      /* Simbolo / */
                            case 83 : if(P==true){ Estado = S_DOCE; cursor--; }else{ Estado = S_TRES;     }  break;      /* Simbolo S */
                            case 65 : if(P==true){ Estado = S_DOCE; cursor--; }else{ Estado = S_SEIS;     }  break;      /* Simbolo A */
                            case 84 : if(P==true){ Estado = S_DOCE; cursor--; }else{ Estado = S_NUEVE;    }  break;      /* Simbolo T */
                            case 90 : if(P==true){ Estado = S_DOCE; cursor--; }else{ Estado = S_DIEZ;     }  break;      /* Simbolo Z */
                            case 61 : Estado = S_IGUAL; break;      /* Simbolo = */
                            case 123 : Estado = S_LLAVEI; Aceptacion(Estado); break;  /* Simbolo { */
                            case 125 : Estado = S_LLAVEF; Aceptacion(Estado); break;  /* Simbolo } */
                            case 44 : Estado = S_COMA;    Aceptacion(Estado); break;  /* Simbolo , */
                            case 36 : Estado = S_VACIO;   Aceptacion(Estado); break;  /* Simbolo $ */
                            default  : Estado = S_DOCE; cursor--;
                        }break;

        case S_UNO      :if (Simbolo == 43){    /* Simbolo + */
                                Estado = S_DOS;
                        }else{
                                cout <<"Error en comentario"<<endl;
                                Estado = ERROR; /*Error Comentario*/
                        }

        case S_DOS      : Aceptacion(Estado); break;
        case S_TRES     :if (Simbolo == 48){
                                Estado = S_CUATRO;  /* Simbolo 0 */
                        }else{
                                Estado = S_CINCO;
                                cursor--;
                        }
        case S_CUATRO   : Aceptacion(Estado); break;/*TOKEN ESTADO_INICIAL*/
        case S_CINCO    : Aceptacion(Estado); break;/*TOKEN ESTADOS*/
        case S_SEIS     :if (Simbolo == 67){
                                Estado = S_SIETE;  /* Simbolo C */
                        }else{
                                Estado = S_OCHO;
                                cursor--;
                        }
        break;
        case S_SIETE     : Aceptacion(Estado);break;/*TOKEN SIMPOLOS PILA*/
        case S_OCHO    : Aceptacion(Estado);break;/*TOKEN ALFABETO*/
        case S_NUEVE     : Aceptacion(Estado);break;/*TOKEN ACEPTACION*/
        case S_DIEZ    :if (Simbolo == 48){
                                Estado = S_ONCE;  /* Simbolo 0 */
                        }else {
                                cout <<"Error Fondo Pila"<<endl;
                        }
        break;
        case S_ONCE     : Aceptacion(Estado);break;/*TOKEN FONDO_PILA*/
        case S_DOCE     :if (isdigit(Simbolo)||isalpha(Simbolo)){  /* Acepta un digito/letra */
                                Id=Id+Simbolo;
                        }else if (Simbolo==44){  /* Acepta un digito/letra */
                                Estado = S_ID;
                        }else if (Simbolo==125){  /* Acepta un digito/letra */
                                Estado = S_LLAVEF;
                        }else{
                                cout <<"Aqui estaba"<<endl;
                                Estado = S_ID;
                                Aceptacion(Estado);
                        }/*TOKEN ID*/
     }
  }
}

char TomaCaracterTrans(){
    int alto = 0;
    char caracter;
    while (!alto){
            caracter = *cursor;
            cursor++;
            return caracter;
    }
}

void TomaTokenTrans(){
  int Estado = INICIAL;
  char Simbolo;
  while (Aceptacion(Estado)== false){
        Simbolo = TomaCaracterTrans();
     switch(Estado)  {
         case INICIAL : switch(Simbolo)  {
                            case 9  : break;      /* Simbolo TAB */
                            case 32 : break;      /* Simbolo ESPACIO */
                            case 40 : break;      /* Simbolo ( */
                            case 41 : cout <<"Error Transición"<<endl;                     break;  /* Simbolo ) */
                            default : Estado = S_DOCE; cursor--;
                        }break;

        case S_DOCE     :if (isdigit(Simbolo)||isalpha(Simbolo)||Simbolo==36){  /* Acepta un digito/letra/Vacio */
                                IdTrans=IdTrans+Simbolo;
                        }else if (Simbolo==9){  /* Simbolo TAB */
                                Estado = S_ID;
                        }else if (Simbolo==32){ /* Simbolo ESPACIO */
                                Estado = S_ID;
                        }else if (Simbolo==44){ /* Simbolo  , */
                                Estado = S_ID;
                        }else if (Simbolo==41){ /* Simbolo ) */
                                Estado = S_PARF;
                        }else{
                                cout <<"Error Transición"<<endl;
                        }/*TOKEN ID*/
     }}}

void TomaEstados(){
    int alto = 0;
    char Simbolo;
    while(alto==0){
        TomaToken();
        switch(token){
            case IGUAL  : break;
            case LLAVEI : P = true; break;
            case ID     : Stados.push_back(Id); Id=""; break;
            case COMA   : break;
            case LLAVEF : Stados.push_back(Id); Id=""; alto =1; break;
            default     : cout <<"Error Estados"<<endl; alto =1;
        }
    }
    P = false;
}

void TomaEstadoInicial(){
    int alto = 0;
    char Simbolo;
    while(alto==0){
        TomaToken();
        switch(token){
            case IGUAL  : break;
            case LLAVEI : P = true; break;
            case ID     : StadoIni.push_back(Id); Id=""; break;
            case LLAVEF : StadoIni.push_back(Id); Id=""; alto =1; break;
            default     : cout <<"Error Estado Inicial"<<endl; alto =1;
        }
    }
    P = false;
}

void TomaAlfabeto(){
    int alto = 0;
    char Simbolo;
    while(alto==0){
        TomaToken();
        switch(token){
            case IGUAL  : break;
            case LLAVEI : P = true; break;
            case ID     : Alfa.push_back(Id); Id=""; break;
            case COMA   : break;
            case LLAVEF : Alfa.push_back(Id); Alfa.push_back("$"); Id=""; alto =1; break;
            default     : cout <<"Error Alfabeto"<<endl; alto =1;
        }
    }
    P = false;
}

void TomaSimbolosPila(){
    int alto = 0;
    char Simbolo;
    while(alto==0){
        TomaToken();
        switch(token){
            case IGUAL  : break;
            case LLAVEI : P = true; break;
            case ID     : AlfaC.push_back(Id); Id=""; break;
            case COMA   : break;
            case LLAVEF : AlfaC.push_back(Id); Id=""; alto =1; break;
            default     : cout <<"Error Simbolos Pila"<<endl; alto =1;
        }
    }
    P = false;
}

void TomaAceptacion(){
    int alto = 0;
    char Simbolo;
    while(alto==0){
        TomaToken();
        switch(token){
            case IGUAL  : break;
            case LLAVEI : P = true; break;
            case ID     : ET.push_back(Id); Id=""; break;
            case COMA   : break;
            case LLAVEF : ET.push_back(Id); Id=""; alto =1; break;
            default     : cout <<"Error Estados Terminacion"<<endl; alto =1;
        }
    }
    P = false;
}

void TomaFondoPila(){
    cursor++;
    int alto = 0;
    char Simbolo;
    while(alto==0){
        TomaToken();
        switch(token){
            case IGUAL  : break;
            case LLAVEI : P = true; break;
            case ID     : Fondo.push_back(Id); Id=""; break;
            case LLAVEF : Fondo.push_back(Id); Id=""; alto =1; Val=true; break;
            default     : cout <<"Error Fondo Pila"<<endl; alto =1;
        }
    }
    P = false;
}

bool ExisteEnDefinicion(int Tipo){
    switch(Tipo){
        case 0 :Ptr = find(Stados.begin(), Stados.end(), IdTrans);
                if(Ptr!=Stados.end()){
                    return true;
                }else{
                    return false;
                }
        break;
        case 1 :
                Ptr = find(Alfa.begin(), Alfa.end(), IdTrans);
                if(Ptr!=Alfa.end()){
                    return true;
                }else{
                    return false;
                }
        break;
        case 2 :
                Ptr = find(Alfa.begin(), Alfa.end(), IdTrans);
                if(Ptr!=Alfa.end()){
                    return true;
                }else{
                    Ptr = find(AlfaC.begin(), AlfaC.end(), IdTrans);
                    if(Ptr!=AlfaC.end()){
                        return true;
                    }else{
                        return false;
                    }
                }
        break;
        default : break;
    }
}

bool ExisteEnAlfabeto(char Tecla){
    string Letra;
    Letra = Tecla;
    Ptr = find(Alfa.begin(), Alfa.end(), Letra);
    if(Ptr!=Alfa.end()){
        return true;
    }else{
        return false;
    }
}

void TomaTransiciones(){
    NTrans aux;
    aux = new(struct nodo);
    string Move;
    int alto = 0,Tipo = 0, Movimiento = 0;
    char Simbolo;
    while(alto==0){
        TomaTokenTrans();
        switch(token){
            case ID     :switch(Tipo){
                            case 0 :if(ExisteEnDefinicion(Tipo)==true){   aux->Estado = IdTrans;      IdTrans = "";   Tipo+=1;}break;
                            case 1 :if(ExisteEnDefinicion(Tipo)==true){   aux->Lectura = IdTrans;     IdTrans = "";   Tipo+=1;}break;
                            case 2 :if(ExisteEnDefinicion(Tipo)==true){   aux->Tope = IdTrans;        IdTrans = "";   Tipo+=1;}break;
                            case 3 :switch(Movimiento){
                                    case 0 :if(ExisteEnDefinicion(2)==true){   aux->MoveU = IdTrans;   IdTrans = "";   Movimiento+=1;}break;
                                    case 1 :if(ExisteEnDefinicion(2)==true){   aux->MoveP = IdTrans;   IdTrans = "";   Movimiento+=1;}break;
                                    }break;
                        } break;
            case COMA   : break;
            case PARI   : break;
            case PARF   : switch(Movimiento){
                            case 2 :if(ExisteEnDefinicion(0)==true){   aux->MoveStado = IdTrans;   IdTrans = "";   Movimiento+=1;
                            Transiciones.push_back(Move);
                            aux->siguiente = ListaTrans;
                            ListaTrans  = aux;
                            }break;
                         }alto =1; break;
            default     : cout <<"Error Transiciones"<<endl;
    }}}

bool ExisteTerminacion(string EstadoET){
    Ptr = find(ET.begin(), ET.end(), EstadoET);
    if(Ptr!=ET.end()){
        return true;
    }else{
        return false;
    }
}

bool MostrandoPila(){
    int i=1;
    string Letra;
    Cadena += "$";
    cursor = strdup(Cadena.c_str());
    Ptr = StadoIni.begin();
    string EstadoActual(*Ptr);
    Ptr = Fondo.begin();
    string Fondo(*Ptr);
    Pila.push(Fondo);
    while(*cursor!=NULL){
        Letra=*cursor;
        cout << "\nESTADO" << "\t" << "LECTURA" << "\t" <<  "TOPE PILA" << "\t" << "MOVIMIENTO" << endl;
        cout << EstadoActual << "\t" << Letra << "\t" <<  Pila.top() << "\t\t";
        NTrans aux = ListaTrans;
        while(aux!=NULL ){
                if(aux->Estado==EstadoActual && aux->Lectura==Letra && aux->Tope==Pila.top()){
                        Fondo = Pila.top();
                        Pila.pop();
                    if(aux->MoveP=="$" && aux->MoveU=="$"){
                        cout << "(" << aux->MoveP << "," << aux->MoveP << "," << aux->MoveStado << ")" << endl;
                        EstadoActual = aux->MoveStado;
                        aux=NULL;
                    }else if(aux->MoveU=="$"){
                        cout << "(" << aux->MoveP << "," << aux->MoveP << "," << aux->MoveStado << ")" << endl;
                        Pila.push(aux->MoveP);
                        EstadoActual = aux->MoveStado;
                        aux=NULL;
                    }else if(aux->MoveP=="$"){
                        cout << "(" << aux->MoveP << "," << aux->MoveP << "," << aux->MoveStado << ")" << endl;
                        Pila.push(aux->MoveU);
                        EstadoActual = aux->MoveStado;
                        aux=NULL;
                    }else{
                        cout << "(" << aux->MoveP << "," << aux->MoveP << "," << aux->MoveStado << ")" << endl;
                        Pila.push(aux->MoveP);
                        Pila.push(aux->MoveU);
                        EstadoActual = aux->MoveStado;
                        aux=NULL;
                    }
                }else{
                    aux = aux->siguiente;
                }

        }
        cursor++;
        i++;
        getch();

    }
    if(ExisteTerminacion(EstadoActual)==true){
        return true;
    }else{
        return false;
    }

}

void ProcesarEntrada(){
    char tecla;
    cursor = strdup(Cadena.c_str());
    while (*cursor!=NULL){
        tecla = *cursor;
        if (ExisteEnAlfabeto(tecla)){
            cursor++;
        }else{
            cout <<"Cadena No Valida"<< endl;
            exit(1);
        }
    }
    if(MostrandoPila()==true){
        cout <<"\n\n\t\tCADENA VALIDA"<< endl;
    }else{
        cout <<"\n\n\t\tCADENA NO VALIDA"<< endl;
    }

}

int main() {
    setlocale(LC_ALL, "");
	fstream Archivo;
	string NombreArchivo;

	cout << "Ingrese La Direccion Del Archivo De Texto: ";
	getline(cin, NombreArchivo);
	Archivo.open(NombreArchivo.c_str(),ios::in);

	if (Archivo.is_open()) {
		while (!Archivo.eof()) {  /*AQUÍ SE PROCESA EL ARCHIVO*/
			getline(Archivo, Linea);
			if(Linea!=""){
                cursor = strdup(Linea.c_str());
                if(Val==false){
                    TomaToken();
                    switch(token) {
                        case COMENTARIO         : cout <<Linea<<endl;       break; //Muestra Los Comentarios;
                        case ESTADOS            : TomaEstados();            break;
                        case ESTADO_INICIAL     : TomaEstadoInicial();      break;
                        case ALFABETO           : TomaAlfabeto();           break;
                        case SIMBOLOS_PILA      : TomaSimbolosPila();       break;
                        case ACEPTACION         : TomaAceptacion();         break;
                        case FONDO_PILA         : TomaFondoPila();          break;
                        default                 : cout <<"ERROR"<<endl;
                    }
                }else{
                    TomaTransiciones();
                }
			}
        }
        cout <<"\nIngrese Una Cadena\t";
        cin>>Cadena;
        ProcesarEntrada();
		Archivo.close();
	}else{ cout << "No Se Encontro El Archivo" << endl;}
	return 0;
}
