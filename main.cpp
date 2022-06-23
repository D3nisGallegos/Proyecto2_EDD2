#include <iostream>
#include <cstdio>
#include <conio.h>
#include <iostream>
#include <stdio.h>

using namespace std; 

typedef struct nodo{
	int dato;
   	struct nodo *izq, *dere, *padre;
   	int fe, alturaIzq, alturaDere;
   	
	char nombre[50];
	char apellido[50];
	char direccion[150];
	
}arbol, *parbol;


int sw=0; // Si es 1= insertar, 0=fe 

arbol *raiz, *nuevo, *recorrer; //Crea las estructuras de tipo puntero.
int buscado=0; //Variable para guardar un valor buscado
arbol *PadreAB, *sHijo, *predecesor, *abuelo, *hijoHijo;

//Recorridos pre, in, post
void preorden(arbol *recorrer);
void inorden(arbol *recorrer);
void postorden(arbol *recorrer);
void insertarNuevo(arbol *recorrer, arbol *nuevo, arbol *padre);
void agregarDatos();
int exiteenArbol(arbol *recorrer, int buscado);
void verArbol(arbol recorrer, int n);
void graficarArbol(arbol, int, int);
void dibujarCuadro(int,int,int,int);
void eliminarNodo(arbol *recorrer, int buscado);
void estadoFactorEquilibrio(arbol *recorrer);
void necesidadEquilibrar(arbol *recorrer);
void vaciarArbol(arbol *recorrer);

//funciones que reestructuran el árbol
void rotarII();
void rotarDD();
void rotarID();
void rotarDI();

parbol nuevoNodo();

//Variable "nuevo" almacenará una nueva hoja para el árbol.
parbol nuevoNodo(){	
	nuevo = new (arbol); //Crea la reserva de espacio en memoria.
	cout<<"Ingrese su NIT: "; cin>>nuevo->dato;
	cout<<"Ingrese su Nombre: "; cin>>nuevo->nombre;
	cout<<"Ingrese su Apellido: "; cin>>nuevo->apellido;
	cout<<"Ingrese su direccion: "; cin>>nuevo->direccion;
	
	
	nuevo->izq=NULL; //Punteros a tierra
	nuevo->dere=NULL; //Punteros a tierra
	nuevo->alturaIzq=0; //Setea en cero la altura izquierda el nodo
	nuevo->alturaDere=0; //Setea en cero la altura derecha el nodo
	nuevo->fe= nuevo->alturaDere-nuevo->alturaIzq; //Calculo del factor equilibrio, podría asignarse el valor cero desde la entrada.
	
	return nuevo;
}



void agregarDatos(){
	system("cls");
	int x;
	cout<<"Cuantos elementos desea insertar? ";cin>>x;
	for (int i=1; i<=x;i++){
		cout<<"\nIngrese registro "<<i<<endl;
		recorrer=raiz; //Se apunta a recorrer en al mismo nodo donde apunta la raíz
		nuevo=nuevoNodo(); //Almacena el nuevo nodo para luego insertarlo en el arbol.
		
		if (nuevo->dato!=0){
			if (exiteenArbol(recorrer, nuevo->dato)==1){ //Evalua si el nodo ya existe en el arbol.
				PadreAB=raiz;
				insertarNuevo(recorrer, nuevo, PadreAB);
					
				//BBaltura(recorrer);
				//BBnecesidadEquilibrar(recorrer);
			}else{
				cout<<"El numero ya existe en el arbol"<<endl;
				getch();
			}
		}else{
			vaciarArbol(raiz);
			system("cls");
			verArbol(raiz, 0);
			cout<<"El arbol ha sido eliminado porque ingreso el numero cero "<<endl;
			getch();
			i=x;
			return;
		}
		
		verArbol(raiz,0);
	}
}

void dibujarCuadro(int x1,int y1,int x2,int y2){
    int i;
    for (i=x1+1;i<x2;i++){
        gotoxy(i,y1); cputs("-") ;//linea horizontal superior
        gotoxy(i,y2); cprintf("-") ;//linea horizontal inferior
    }
    for (i=y1+1;i<y2;i++){
        gotoxy(x1,i); cprintf("|") ;//linea vertical izquierda
        gotoxy(x2,i); cprintf("|") ;//linea vertical derecha
    }
}

void intro(){
	clrscr();//limpia TODA LA pantalla
 
    //crea una ventana COMPLETA de fondo azul claro
    window(1,1,80,25);
    textbackground(LIGHTBLUE);//fondo de la pantalla AZUL CLARO
    clrscr();
 
    //Ventana de fondo o sombra NEGRA
    window(4,4,79,24);//crea una ventana en estar cordenadas
    textbackground(BLACK);
    clrscr();
 
    //ventana principal donde se solicitan datos
    window(2,2,77,22);//crea una ventana en estar cordenadas
    textbackground(GREEN);//fondo de la pantalla verde
    textcolor(YELLOW);//color de la letra amarillo
    clrscr();
    dibujarCuadro(1,1,75,21);//Cuadro grande
    dibujarCuadro(3,3,73,5);//Cuadro titulo
    gotoxy(16,4);
    textcolor(WHITE);//establece el color de fondo en blanco

    return;
}

int main(){
	intro();
    gotoxy(3,7);cprintf("Estructura de Datos II");
    gotoxy(3,9);cprintf("Ingeniero Miguel Zepeda");
    gotoxy(3,11);cprintf("GRUPO: Denis Gallegos, Bonieth Ramirez");
    gotoxy(3,18);cprintf("Presione cualquier tecla para continuar...");
    getch();
    clrscr();
	int opcion;
	while (opcion!=11){
		system("cls");
		cout<<"************************** MENU **************************\n\n";
		cout<<"1.  Ingresar elemento\n";
		cout<<"2.  IMPRIMIR en PreOrden\n";
		cout<<"3.  IMPRIMIR en InOrden\n";
		cout<<"4.  IMPRIMIR en PostOrden\n";
		cout<<"5.  Graficar Arbol - Rotado 90 grados\n";
		cout<<"6.  Graficar Arbol - Normal\n";
		cout<<"7.  IMPRIMIR Altura del arbol\n";
		cout<<"8.  Eliminar elemento\n";
		cout<<"9.  Buscar elemento\n";
		cout<<"10. Vaciar el arbol\n";
		cout<<"11. Salir\n";
		cout<<"Ingrese una opcion\n";
		cin>>opcion;
		
		recorrer=raiz;
		
		switch(opcion){
			case 1:
				agregarDatos();
				break;
			case 2:
				cout<<"------------PREORDEN---------"<<endl;
				preorden(recorrer);
				getch();
				break;
			case 3:
				cout<<"------------INORDEN---------"<<endl;
				inorden(recorrer);
				getch();
				break;
			case 4:
				cout<<"------------POSORDEN---------"<<endl;
				postorden(recorrer);
				getch();
				break;
			case 5:
				system("cls");
				cout<<"------------ARBOL AVL - ROTADO 90 GRADOS A LA IZQUIERDA---------"<<endl;
				verArbol(recorrer, 0);
				getch();
				break;
			case 6:
				system("cls");
				gotoxy(25,2);cprintf("------------ARBOL AVL---------");
				//cout<<"____________ARBOL AVL__________"<<endl;
				graficarArbol(recorrer, 40, 5);
				getch();
				break;
			case 7:
				cout<<"La Altura del arbol es: "<<altura(recorrer)<<endl;
				getch();
				break;
			case 8:
				cout<<"Ingrese el elemento a eliminar: ";cin>>buscado;
				arbolVacio(recorrer, buscado); //Evalua si existe, luego procede a eliminar.
				recorrer=raiz; //Volver a asinar a recorrer el puntero raiz
				//BBaltura(recorrer); //Evaluar nuevamente la altura del arbol
				//BBrecorrer=raiz; //Volver a asinar a recorrer el puntero raiz
				//BBnecesidadEquilibrar(recorrer); //Evaluar si es necesario equilibrarlo
				cout<<"\nHecho";
				getch();
				break;
			case 9:
				cout<<"Nodo a buscar: ";cin>>buscado;
				buscarDato(recorrer, buscado);
				getch();
				break;
			case 10:
				cout <<"Vaciar Arbol"<<endl;
				vaciarArbol(recorrer);
				
				getch();
				break;
			case 11:
				break;
			default:
				cout<<"No es una opcion correcta";
				break;
		}
	}
	
	intro();
	cprintf("PROGRAMA FINALIZADO");
    
	return 0;
}





