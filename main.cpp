#include <iostream>
#include <cstdio>


using namespace std; 

int menu(); 

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


int menu(){
	int opcion = 0; 
	while (opcion != 4){
		cout << "--------MENU--------" <<endl;
		cout << " 1) Insertar al arbol AVL "<<endl;
		cout << " 2) Eliminar del arbol AVL " <<endl; 
		cout << " 3) Imprimir arbol AVL " <<endl; 
		cout << " 4) Salir. " <<endl; 
		cout << "---------------------" <<endl; 
		cout << " Ingrese la opcion: " <<endl; 
		cin>> opcion; 
		if (opcion == 4){
			cout << "Ha elegido salir del sistema. " <<endl; 
		}else if (opcion > 0 && opcion < 4){
			break; 
		}
	}
	return opcion; 
}




