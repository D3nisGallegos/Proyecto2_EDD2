#include <iostream>
#include <cstdio>
#include <conio.h>
#include <stdio.h>
#include <Windows.h>

using namespace std; 


typedef struct nodo{
	int dato;
   	struct nodo *izq, *dere, *padre;
   	int fe, alturaIzq, alturaDere;
   	
	
}arbol, *parbol;


int sw=0; // Si es 1= insertar, 0=fe 

arbol *raiz, *nuevo, *recorrer; //Crea las estructuras de tipo puntero.
int buscado=0; //Variable para guardar un valor buscado
arbol *PadreAB, *sHijo, *predecesor, *abuelo, *hijoHijo;

void preorden(arbol *recorrer);
void inorden(arbol *recorrer);
void postorden(arbol *recorrer);
void insertarNuevo(arbol *recorrer, arbol *nuevo, arbol *padre);
void agregarDatos();
int exiteenArbol(arbol *recorrer, int buscado);
void graficarArbol(arbol, int, int);
void eliminarNodo(arbol *recorrer, int buscado);
void estadoFactorEquilibrio(arbol *recorrer);
void necesidadEquilibrar(arbol *recorrer);
void vaciarArbol(arbol *recorrer);

//funciones para reestructurar el árbol
void rotarII();
void rotarDD();
void rotarID();
void rotarDI();

parbol nuevoNodo();

//Variable "nuevo" almacenará una nueva hoja para el árbol.
parbol nuevoNodo(){	
	nuevo = new (arbol); //Crea la reserva de espacio en memoria.
	cout<<"Ingrese el valor del elemento: "<<endl; 
	cin>>nuevo->dato;
	nuevo->izq=NULL; //Punteros a tierra
	nuevo->dere=NULL; //Punteros a tierra
	nuevo->alturaIzq=0; //Setea en cero la altura izquierda el nodo
	nuevo->alturaDere=0; //Setea en cero la altura derecha el nodo
	nuevo->fe= nuevo->alturaDere-nuevo->alturaIzq; //Calculo del factor equilibrio, podría asignarse el valor cero desde la entrada.
	
	return nuevo;
}

void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void insertarNuevo(arbol *recorrer, arbol *nuevo, arbol *PadreAB){
	
	if (raiz==NULL){ //Si es el primer nodo entonces la raíz aún será nula porque no existe nada dentro de ella.		
		raiz=nuevo; //Asignar a la raíz el valor del nuevo nodo creado...
		raiz->padre=NULL;
	}else{
		if(nuevo->dato <= recorrer->dato){
			if(recorrer->izq!=NULL){
				PadreAB=recorrer->izq;
				//BBcout<<"Padre: "<<PadreAB->dato<<" Nuevo: "<<nuevo->dato<<endl;
				insertarNuevo(recorrer->izq, nuevo, PadreAB);
			}else{
				recorrer->izq=nuevo;
				nuevo->padre=PadreAB;
				return;
			}
		}else if (nuevo->dato > recorrer->dato){
			if (recorrer->dere!=NULL){
				PadreAB=recorrer->dere;
				//BBcout<<"Padre: "<<PadreAB->dato<<" Nuevo: "<<nuevo->dato<<endl;
				insertarNuevo(recorrer->dere, nuevo, PadreAB);	
			}else{
				recorrer->dere=nuevo;
				nuevo->padre=PadreAB;
				return;
			}
		}
	}
}

//Funcion que devuelve la altura de las ramas y su factor equilibrio, sólo devuelve valores más no calcula nada.
void estadoFactorEquilibrio(arbol *recorrer){
	if (recorrer != NULL) {
		cout<<"Dato: "<<recorrer->dato<<endl;
		cout<<"Izquierda: "<<recorrer->alturaIzq<< ", Derecha: "<<recorrer->alturaDere<<", Factor de Equilibrio: "<<recorrer->fe<<endl;
	    estadoFactorEquilibrio(recorrer->izq);
	    estadoFactorEquilibrio(recorrer->dere);
	}
}

void preorden(arbol *recorrer){
	if (recorrer != NULL) {
		cout<<"\nValor del elemento: "<<recorrer->dato<<endl;
	    preorden(recorrer->izq);
	    preorden(recorrer->dere);
	}
}

//Recorrido InOrden
void inorden(arbol *recorrer){
  	if (recorrer != NULL) {
    	inorden(recorrer->izq);
    	cout<<"\nElemento: "<<recorrer->dato<<endl;
    	inorden(recorrer->dere);
  	}
}

//Recorrido postOrden
void postorden(arbol *recorrer){
  	if (recorrer != NULL) {
    	postorden(recorrer->izq);
    	postorden(recorrer->dere);
    	cout<<"\nElemento: "<<recorrer->dato<<endl;
  	}
}

//Variar el arbol
void vaciarArbol(arbol *recorrer){
  	if (recorrer != NULL) {
    	postorden(recorrer->izq);
    	postorden(recorrer->dere);
    	
    	if (recorrer->dato == raiz->dato){
    		raiz=NULL;
		}else{
			delete(recorrer);//Liberamos la memoria.
		}
  	}
}

/*
En el metodo GRAFICARARBOL se puede indicar la ubicación de cada impresión del nodo.
Si entra a la derecha suma 5 espacios en X u 1 espacio en Y, inversamente si va hacia la izquierda resta los
5 espacios en X u 1 espacio en Y.
*/
void graficarArbol(arbol *recorrer, int x, int y){
	
	if(recorrer==NULL)
        return;
        
    graficarArbol(recorrer->dere, x+5, y+1);
    gotoxy(x,y); 
	cout << recorrer->dato;	
	
    graficarArbol(recorrer->izq, x-5, y+1);
    //gotoxy(x-1,y-1);
    //cout << "\\"; 
}

int existeNodo=0; //Si es 0 no existe, y si es 1 si existe.

//Función que devuelve 0 si el dato existe en un arbol y 1 si no existe.
//Esta función es utilizada por la función InsertarNuevo para validar que el nodo que se ingresa no existe en el arbol.
int exiteenArbol(arbol *recorrer, int buscado){
	if (recorrer==NULL){
		//final = 1;
		return 1;
	}else{
		if(buscado<recorrer->dato){
			exiteenArbol(recorrer->izq, buscado);
		}else if (buscado>recorrer->dato){
			exiteenArbol(recorrer->dere, buscado);
		}else{
			//final = 0;
			return 0;
		}
	}
	//return final; 
}

//Analizar si el arbol no está vacío y si el nodo a eliminar no es la raíz. 
/*
Si el árbol es vacío lo notifica y si el nodo a eliminar es la raíz también lo indica con el fin de impedir la eliminación y mantener el control.
Si el el arbol no es vacío y nodo a eliminar no es la raíz entonces se llama a eliminar para proceder con el borrado del nodo.
*/
arbol *analizarAB;
void arbolVacio(arbol *recorrer, int buscado){
	analizarAB=recorrer;
	bool existeNodo=false;
	
	if (analizarAB==NULL){
		cout<<"Arbol Vacio"<<endl;
		return;
	}else{
		if(analizarAB->dato==buscado){
			cout<<"No se puede eliminar la Raiz"<<endl;
			return;
		}
		else{
			eliminarNodo(recorrer, buscado);
		}
	}
}

/*
Punteros utilizadas: *recorrer, *PadreAB, *sHijo, *predecesor, *abuelo;
Evalúa cual es los tres casos principales aplica la eliminación
*/
void eliminarNodo(arbol *recorrer, int buscado){
	
	if (recorrer!=NULL){ // Se asegura que el arbol no esté vacío.
		if(buscado < recorrer->dato){ //Si el dato a encontrar es menos que busque por la rama izquierda.
			PadreAB=recorrer; //Se hace una copia de recorrer en el padre antes de la siguiente recursiva...
			eliminarNodo(recorrer->izq, buscado); //Entra recursivamente a la rama izquierda.
		}else if(buscado > recorrer->dato){ //Si el dato a encontrar es mayor que busque por la rama derecha.
			PadreAB=recorrer; //Se hace una copia de recorrer en el padre antes de la siguiente recursiva...
			eliminarNodo(recorrer->dere, buscado); //Entra recursivamente a la rama derecha.
		}else{
					
			//El elemento a eliminar es hoja, aplica al caso 1	
			if (recorrer->izq==NULL && recorrer->dere==NULL){//Condiciones para aplicar al caso 1
				if(PadreAB->izq==recorrer){ //Detectamos si el nodo a eliminar esta a la izquierda del Padre
					PadreAB->izq=NULL; //Si está a la izquierda del Padre solo tendremos que ponerl al Padre en su parte izquierda a Null
					delete(recorrer); //Liberamos la memoria.
				}else{ //Si el nodo no estaba a la izquierda, entonces estará a la derecha del Padre
					PadreAB->dere=NULL; //Ponemos a Null su parte derecha del Padre
					delete(recorrer);//Liberamos la memoria.
				} 
			}else//Sino cumple lo anterior entonces no es hoja...
			
				//Si el nodo a eliminar tiene un hijo se aplica el caso 2
				if((recorrer->izq == NULL && recorrer->dere != NULL)|| (recorrer->izq != NULL && recorrer->dere == NULL)){	//Condiciones para aplicar al caso 2
				
					if(recorrer->izq == NULL && recorrer->dere != NULL){ //Detectando el hijo del nodo a eliminar, si el hijo está a la derecha...
						sHijo=recorrer->dere; //Guardamos la dirección del nodo hijo
						//abuelo=recorrer->padre; //Guardamos la dirección del padre del padre
						if(PadreAB->izq==recorrer){//Detectamos si el nodo a eliminar está a la izquierda de padre...
							PadreAB->izq=sHijo;//Asignamos el nodo hijo del nodo eliminado al Padre en su parte izquierda.
							sHijo->padre=PadreAB; //Enlazamos al hijo al nuevo padre
							delete(recorrer); //Liberamos la memoria del nodo descartado...
						}else{ //Si el nodo a eliminar no estaba a la izquierda del Padre, entonces estará a la derecha...
							PadreAB->dere=sHijo; //Asignamos el nodo hijo del nodo eliminado al Padre en su parte derecha.
							sHijo->padre=PadreAB; //Enlazamos al hijo al nuevo padre
							delete(recorrer); //Liberamos la memoria del nodo descartado...
						}	 
					}else{//Si el hijo del nodo a eliminar no estaba a la derecha, entonces estará a la izquierda...
						sHijo=recorrer->izq;//Guardamos la dirección del nodo hijo
						if(PadreAB->izq==recorrer){ //Detectamos si el nodo a eliminar está a la derecha de padre...
							PadreAB->izq=sHijo;//Asignamos el nodo hijo del nodo eliminado al Padre en su parte izquierda.
							sHijo->padre=PadreAB; //Enlazamos al hijo al nuevo padre
							delete(recorrer);//Liberamos la memoria del nodo descartado...
						}else{ //Si el nodo a eliminar no estaba a la izquierda del Padre, entonces estará a la derecha...
							PadreAB->dere=sHijo;//Asignamos el nodo hijo del nodo eliminado al Padre en su parte derecha.
							sHijo->padre=PadreAB; //Enlazamos al hijo al nuevo padre
							delete(recorrer);//Liberamos la memoria del nodo descartado...
						}
					}
				}else{
					
					//Si no se cumple ninguno de las condiciones anteriores es porque el nodo tiene dos hijos y aplica al caso 3
					
					if(recorrer->izq != NULL && recorrer->dere != NULL){//Condiciones para aplicar al caso 3
						//Encontraremos al predecesor, es decir al nodo más a la derecha de la rama izquierda.
						
						predecesor=recorrer->izq; //asignamos al predecesor la posición izquierda del nodo a eliminar
						//Si el nodo a sustituir al padre no tiene hijos...
						if(predecesor->izq == NULL && predecesor->dere ==NULL){ //Si las partes izquierda y derecha son nulas entonces el nodo a subir no tiene hijos y además es el predecesor que sustituirá al nodo a eliminar.
							recorrer->dato=predecesor->dato; //Asignamos el dato del nuevo predecesor al nodo a eliminar
							recorrer->izq=NULL;
							delete(predecesor);	//Liberamos la memoria del nodo descartado...
						}else{
							predecesor=recorrer->dere; //asignamos al predecesor la posición derecha del nodo a eliminar
							//Si el nodo a sustituir al padre no tiene hijos...
							if(predecesor->izq == NULL && predecesor->dere ==NULL){ //Si las partes izquierda y derecha son nulas entonces el nodo a subir no tiene hijos y además es el predecesor que sustituirá al nodo a eliminar.
								recorrer->dato=predecesor->dato;//Asignamos el dato del nuevo predecesor al nodo a eliminar
								recorrer->dere=NULL;
								delete(predecesor);	//Liberamos la memoria del nodo descartado...
							}else{
								predecesor=recorrer->izq; //asignamos al predecesor la posición izquierda del nodo a eliminar
								if(predecesor->dere==NULL){ //Si el predecesor no tiene hijos a la derecha él será el seleccionado
									recorrer->dato=predecesor->dato; //Asignar el dato de predecesor al nodo a eliminar...
									recorrer->izq=predecesor->izq;//Redireccionamos su parte izquierda para los hijos de ese lado.
									sHijo=predecesor->izq;
									sHijo->padre=recorrer;
									delete(predecesor); //Liberamos la memoria del nodo descartado...
								}else{
									predecesor=recorrer->dere;//Asinamos a predecesor la posición derecha del nodo a eliminar
									if(predecesor->izq==NULL){ //Si el predecesor no tiene hijos a la izquierda, él será el seleccionado.
									recorrer->dato=predecesor->dato; //Asignar el dato de predecesor al nodo a eliminar...
									recorrer->dere=predecesor->dere;//Redireccionamos su parte izquierda para los hijos de ese lado.
									sHijo=predecesor->dere;
									sHijo->padre=recorrer;
									delete(predecesor);//Liberamos la memoria del nodo descartado...
									}else{
										predecesor=recorrer->izq; //Asignamos a predecesor la posición izquierda del nodo a eliminar...
										sHijo=predecesor; //Hacemos una copia de la posición de predecesor 
										
										while(sHijo->dere!=NULL){ //Recorreremos hasta el más a la derecha de la rama izquierda...
											predecesor=sHijo; //Guardar la posición anterior en predecesor y el Hijo estará una posición adelante.
											sHijo=sHijo->dere; //Nos movemos una posición más adelante para el siguiente ciclo.
										}
										//cout<<"\nPredecesor: "<<predecesor->dato<<" sHijo: "<<sHijo->dato<<" Recorrer: "<<recorrer->dato<<endl;
										recorrer->dato=sHijo->dato; //Asignamos al nodo a eliminar el dato de valor mas a la derecha de la rama izquierda
										predecesor->dere=sHijo->izq;//Apuntamos a la derecha al predecesor la dirección izquierda del Hijo
										hijoHijo=sHijo->izq;
										hijoHijo->padre=predecesor;
										//predecesor->izq=NULL; //Quitamos el apuntador del nodo izquierdo del predecesor porque ya no existirá en esa posición
										delete(sHijo);
										
									}
								}
							}
						
						
						}
			}
				}
			}	
	}else{
		cout<<"El nodo no se encuentra en el arbol"<<endl;
	}
}

/*
Se calcula la altura de cada rama y su factor de equilibrio.
La función se va hasta la izquierda del arbol para luego empezar a mandar los datos de altura a los niveles superiores del arbol.
Si la altura de la rama izquierda es mayor que la derecha entonces sube el valor de la rama izquierda para luego calcular el
factor de equilibrio del nodo padre, así hasta llegar al nodo raíz.
*/
int altura(arbol *recorrer){
	if (recorrer == NULL)//Si el nodo está vació entonces que salga.
		return 0 ; //Devuelve el valor cero.
	else{
		recorrer->alturaIzq=altura (recorrer->izq);
		recorrer->alturaDere=altura (recorrer->dere);
		recorrer->fe=recorrer->alturaDere-recorrer->alturaIzq;
		
		if (recorrer->alturaIzq > recorrer->alturaDere)
			return recorrer->alturaIzq + 1;
		else
			return recorrer->alturaDere + 1;
	}
}

/*
Esta función analiza durante una busqueda si existe un factor de equilibrio que sea 2 o -2, si fuera el caso apunta al padre a ese nodo y
luego apunta al hijo para evaluar si el signo de este es positivo o negativo y así determinar el tipo de rotación que se necesita para
balancear el árbol.
El funcionamiento es:
Buscar el valor (-2) o (2) en el factor equilibrio de cualquier nodo del arbol.
Si es (-2) significa que existe desbalance a la izquierda y si el hijo es también (-) negativo significa que es el caso Rotación Izquierda Izquierda, y si fuera positivo es una Rotación Izquierda Derecha.
Si es (2) significa que existe desbalance a la derecha y si el hijo es también (+) positivo significa que es el caso Rotación Derecha Derecha, y si fuera negativo es una Rotación Derecha Izquierda.
*/
//arbol *PadreAB, *sHijo, *predecesor;
void necesidadEquilibrar(arbol *recorrer){ //Con esta función analizo si es necesario equilibrar el árbol, esta función busca el valor -2 o 2.
	if (recorrer != NULL) {
		
		necesidadEquilibrar(recorrer->izq);
	    necesidadEquilibrar(recorrer->dere);

		if ((recorrer->fe==2)||(recorrer->fe==-2)){
			system("cls");
			cout<<"Es necesario equilibrar el arbol"<<endl;
			
			PadreAB=recorrer;
			sHijo=PadreAB->dere;
			
			//Identificar Si es el caso  RDD, Rotación Derecha, Derecha.
			if ((PadreAB->fe>1)&&(sHijo->fe>0)){
				cout<<"Rotacion derecha derecha."<<endl;
				cout<<" Padre: "<<PadreAB->dato<<" Hijo: "<<sHijo->dato<<endl;
				getch();
				rotarDD();
				altura(raiz);
				return;
			//Identificar Si es el caso  RDI, Rotación Derecha, Izquierda.
			}else if((PadreAB->fe>1)&&(sHijo->fe<0)){
				cout<<"Rotacion derecha izquierda."<<endl;
				cout<<" Padre: "<<PadreAB->dato<<" Hijo: "<<sHijo->dato<<endl;
				getch();
				rotarDI();
				altura(raiz);
				return;
			}else{
				
				PadreAB=recorrer;
				sHijo=PadreAB->izq;
				
				//Identificar Si es el caso  RII, Rotación Izquierda, Izquierda.
				if((PadreAB->fe<-1)&&(sHijo->fe<0)){
					cout<<"Rotacion izquierda izquierda."<<endl;
					cout<<" Padre: "<<PadreAB->dato<<" Hijo: "<<sHijo->dato<<endl;
					getch();
					rotarII();
					altura(raiz);
					return;
				//Identificar Si es el caso  RID, Rotación Izquierda, Derecha.	
				}else if((PadreAB->fe<-1)&&(sHijo->fe>0)){
					cout<<"Rotacion izquierda Derecha."<<endl;
					cout<<" Padre: "<<PadreAB->dato<<" Hijo: "<<sHijo->dato<<endl;
					getch();
					rotarID();
					altura(raiz);
					return;
				}
			}
			return;
		}	
	}
}

//Rotación Derecha Izquierda
void rotarDI(){
	if (PadreAB==raiz){
		
		hijoHijo=sHijo->izq; //Ubico al hijo del hijo...
		
		raiz=hijoHijo; //Cambiar el apuntador de la raíz.
		
		hijoHijo->padre=NULL; //Aseguro que el padre de la raíz se quede en NULL
		
		hijoHijo->dere=sHijo; // el nuevo padre debe apuntar al hijo izquierdo.		
		sHijo->padre=hijoHijo; //El hijo debe apuntar a su nuevo padre.
		if(sHijo->izq!=NULL){
			sHijo->izq=hijoHijo->izq;
		}else{
			sHijo->izq=NULL; //Apuntar a Null la parte izquierda del hijo, ya que ahora no tendrá hijos...			
		}
		
		//sHijo->dere=NULL; // Apuntar a Null la parte derecha del hijo, ya que ahora no tendrá Hijos...
		
		hijoHijo->izq=PadreAB; //El nuevo padre debe apuntar al hijo derecho.
		
		if(PadreAB->izq==NULL){
			PadreAB->izq=NULL; //El antiguo padre debe apuntar ahora a nu
		}

		PadreAB->dere=NULL; //el antiguo padre debe apuntar ahora a null
		PadreAB->padre=hijoHijo; //Apuntar al nuevo padre ...
	}else{
		
		abuelo=PadreAB->padre;
		
		hijoHijo=sHijo->izq; //Ubico al hijo del hijo...
		
		hijoHijo->padre=abuelo; //Aseguro que el padre de la raíz se quede apuntando al abuelo
		
		hijoHijo->dere=sHijo; // el nuevo padre debe apuntar al hijo izquierdo.		
		sHijo->padre=hijoHijo; //El hijo debe apuntar a su nuevo padre.
		
		if(sHijo->izq!=NULL){
			sHijo->izq=hijoHijo->izq;
		}else{
			sHijo->izq=NULL; //Apuntar a Null la parte izquierda del hijo, ya que ahora no tendrá hijos...			
		}
		
		//sHijo->dere=NULL; // Apuntar a Null la parte derecha del hijo, ya que ahora no tendrá Hijos...
		
		hijoHijo->izq=PadreAB; //El nuevo padre debe apuntar al hijo derecho.
		
		if(PadreAB->izq==NULL){
			PadreAB->izq=NULL; //El antiguo padre debe apuntar ahora a nu
		}
		
		PadreAB->dere=NULL; //el antiguo padre debe apuntar ahora a null
		PadreAB->padre=hijoHijo; //Apuntar al nuevo padre ...
		
		abuelo->dere=hijoHijo;
	}
}

//Rotación  Izquierda Derecha
void rotarID(){
	if (PadreAB==raiz){
		
		hijoHijo=sHijo->dere; //Ubico al hijo del hijo...
		
		raiz=hijoHijo; //Cambiar el apuntador de la raíz.
		
		hijoHijo->padre=NULL; //Aseguro que el padre de la raíz se quede en NULL
		
		hijoHijo->izq=sHijo; // el nuevo padre debe apuntar al hijo izquierdo.		
		sHijo->padre=hijoHijo; //El hijo debe apuntar a su nuevo padre.
		
		sHijo->dere=NULL; //Apuntar a Null la parte izquierda del hijo, ya que ahora no tendrá hijos...			

		PadreAB->izq=NULL; //El antiguo padre debe apuntar ahora a null 
		
		hijoHijo->dere=PadreAB; //El nuevo padre debe apuntar al hijo derecho.
		
		
		if(PadreAB->dere==NULL){
			PadreAB->dere=NULL; //El antiguo padre debe apuntar ahora a nu
		}
		PadreAB->padre=hijoHijo; //Apuntar al nuevo padre ...
	}else{
		
		abuelo=PadreAB->padre;
		
		hijoHijo=sHijo->dere; //Ubico al hijo del hijo...
		
		hijoHijo->padre=abuelo; //Aseguro que el padre de la raíz se quede apuntando al abuelo
		abuelo->izq=hijoHijo;
		
		hijoHijo->izq=sHijo; // el nuevo padre debe apuntar al hijo izquierdo.		
		sHijo->padre=hijoHijo; //El hijo debe apuntar a su nuevo padre.
				
		sHijo->dere=NULL; //Apuntar a Null la parte izquierda del hijo, ya que ahora no tendrá hijos...			
		
		
		hijoHijo->dere=PadreAB; //El nuevo padre debe apuntar al hijo derecho.
		
		PadreAB->izq=NULL; //El antiguo padre debe apuntar ahora a null 
		
		if(PadreAB->dere==NULL){
			PadreAB->dere=NULL; //El antiguo padre debe apuntar ahora a nu
		}
		PadreAB->padre=hijoHijo; //Apuntar al nuevo padre ...
	}
}

//Rotación  Derecha Derecha
void rotarDD(){
	if (PadreAB==raiz){
		raiz=sHijo;
		
		//sHijo->dere=hijoHijo;
		//hijoHijo->padre=sHijo;
		//hijoHijo->dere=NULL;
		
		sHijo->izq=PadreAB;
		PadreAB->padre=sHijo;
		PadreAB->dere=NULL;
		
		sHijo->padre=NULL;
		
	}else{
		abuelo=PadreAB->padre;
		abuelo->dere=PadreAB->dere;
		sHijo->padre=abuelo;
		sHijo->izq=PadreAB;
		PadreAB->padre=sHijo;
		PadreAB->dere=NULL;
	}
}

//Rotación  Izquierda Izquierda
void rotarII(){
	if(PadreAB==raiz){
		raiz=sHijo;
		
		hijoHijo=sHijo->izq;
		
		sHijo->dere=PadreAB;
		PadreAB->izq=NULL;
		PadreAB->padre=sHijo;
		
		sHijo->padre=NULL;
		
		//PadreAB->dere=hijoHijo;
		//hijoHijo->padre=PadreAB;
		
		//sHijo->dere=PadreAB;
		
		
	}else{
		abuelo=PadreAB->padre;
		abuelo->izq=PadreAB->izq;
		sHijo->padre=abuelo;
		sHijo->dere=PadreAB;
		PadreAB->padre=sHijo;
		PadreAB->izq=NULL;
	}	
}

void agregarDatos(){
	system("cls");
	int x;
	cout<<"Cuantos elementos desea insertar? ";
	cin>>x;
	for (int i=1; i<=x;i++){
		cout<<"\nIngrese informacion para el elemento: "<<i<<endl;
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
			//verArbol(raiz, 0);
			//graficarArbol(recorrer, 40, 5); 
			cout<<"El arbol ha sido eliminado porque ingreso el numero cero "<<endl;
			getch();
			i=x;
			return;
		}
		
	//graficarArbol(recorrer, 40, 5);
	}
}


int main(){
    gotoxy(3,7);cout <<"Estructura de Datos II";
    gotoxy(3,9);cout <<"Ingeniero Juan Zepeda";
    gotoxy(3,11);cout <<"GRUPO: Denis Gallegos 11951011, Bonieth Ramirez 11921012";
    gotoxy(3,18);cout << "Presione cualquier tecla para continuar...";
    getch();
	int opcion;
	while (opcion!=9){
		system("cls");
		cout<<"************************** MENU **************************\n\n";
		cout<<"1.  Ingresar elemento\n";
		cout<<"2.  IMPRIMIR en PreOrden\n";
		cout<<"3.  IMPRIMIR en InOrden\n";
		cout<<"4.  IMPRIMIR en PostOrden\n";
		cout<<"5.  Graficar Arbol\n";
		cout<<"6.  IMPRIMIR Altura del arbol\n";
		cout<<"7.  Eliminar elemento\n";
		cout<<"8.  Vaciar el arbol\n";
		cout<<"9.  Salir\n";
		cout<<"Ingrese una opcion" <<endl;
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
				gotoxy(25,2);
				cout<<"------------ARBOL AVL---------";
				//cout<<"____________ARBOL AVL__________"<<endl;
				graficarArbol(recorrer, 40, 5);
				getch();
				break;
			case 6:
				cout<<"La Altura del arbol es: "<<altura(recorrer)<<endl;
				getch();
				break;
			case 7:
				cout<<"Ingrese el elemento a eliminar: ";
				cin>>buscado;
				arbolVacio(recorrer, buscado); //Evalua si existe, luego procede a eliminar.
				recorrer=raiz; //Volver a asinar a recorrer el puntero raiz
				cout<< "Hecho" <<endl;
				getch();
				break;
			case 8:
				cout <<"Vaciar Arbol"<<endl;
				vaciarArbol(recorrer);
				getch();
				break;
			case 9:
				break;
			default:
				cout<<"Opcion invalida, ingrese una opcion nuevamente. ";
				break;
		}
	}
	
	cout<<"PROGRAMA FINALIZADO"<<endl;
    
	return 0;
}





