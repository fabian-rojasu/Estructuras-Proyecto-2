#include <iostream>
#include <cstdlib>
using namespace std;

//Esta estructura sera la que se utilice para representar los lugares que seran visitados 
struct Vertice{
    //Atributos de la estructura
    string nombre;
    struct Vertice * sigV;//para enlazar todos los vertices en una lista
    struct Arco *subListaArcos;//representa los arcos que salen de ese vertice
    bool visitado;
    //Constructor
    Vertice (string nom){
            nombre = nom;
            sigV = NULL;
            subListaArcos = NULL;
            visitado = false;
    }
};

//Esta estructura sera la que se utilice para representar la conexion que que habra entre los diferentes lugares
struct Arco{
    //Atributos de la estructura
    int distancia;//Medida que tendran que recorrer de un vertice a otro
    string destino;
    struct Arco *sigA;//siguiente arco.
    //Constructor
    Arco(int dis, string des){
            distancia = dis;
            destino = des;
            sigA = NULL;
    }
};

//Esta estructura sera la que se utilice para representar a los individuos que van a recorrer los diferentes lugares
struct Personas{
    //Atributos de la estructura
    string nombre;
    string cedula;//Indentificador
    struct Vertice * inicio;//Este sera el punto de partida de la persona respectiva 
    string formaAvanzar; //Aqui se determinara la forma en la que la persona respectiva se transaladara por los diferentes lugares
    struct Amigos* amigos;
    Personas * ant;
    Personas * sig;
    //Constructor
    Personas(string nom,string ced, Vertice * ini, string FAva){
        nombre = nom;
        cedula=ced;
        inicio=ini;
        formaAvanzar=FAva;
        ant = NULL;
        sig = NULL;
        amigos=NULL;  
    }

} * nodoPersona;

struct Amigos{
    string amigo;
    Amigos * sig;
    Amigos(string ami){
        amigo=ami;
        sig=NULL;
    }
};


//Metodos Vertice

struct Vertice *grafo1;// el apuntador inicial del grafo
struct Vertice *grafo2;// el apuntador inicial del grafo


void insertarVertice(string nom,Vertice*graf){
    struct Vertice *nuevoVertice = new Vertice(nom);

    nuevoVertice->sigV = graf;
    graf = nuevoVertice;
}


struct Vertice *   buscarVertice(string origen,Vertice*graf){
    struct Vertice *tempV = graf;
    while(tempV != NULL){
        if(tempV->nombre == origen)
            return tempV;

        tempV = tempV->sigV;
    }
return NULL;//no lo encontro
}

void modificarVertice(Vertice*graf){
    string nom;
    printf("Nombre del vertice:  ");
    cin>> nom;
    struct Vertice *tempV = buscarVertice(nom,graf);
    if (tempV == NULL){
        printf("Persona no encontrado");
    }else{
        printf("\n\nNombre nuevo:  ");
        cin>> nom; 
        tempV->nombre = nom;
    }
}

//Metodo Borrar: selecciona al nodo que se desea eliminar por medio de su respectivo buscar
void borrarVertice(string nom,Vertice*graf){
    Vertice* buscado = buscarVertice(nom,graf);
    if(buscado == NULL){
        cout<<"\n vertice no encontrada....\n";
        return;
    }
    else{
        if(buscado == graf){//si el buscado es el primero
                graf = graf->sigV;
        }
        else{//borra en medio o al final
            Vertice * temp =graf->sigV; /*1    2   3*/
            Vertice * ant =graf;
            while ((temp!= NULL) && (temp!=buscado))
            {
                ant = temp;
                temp = temp->sigV;
            }
            if(temp==buscado){
                if (temp->sigV==NULL)
                {
                    ant->sigV=NULL;
                }else{
                    ant->sigV=temp->sigV;  

                }
            }
            
        }
    }
}


//Metodos Arco

void insertarArco(string origen, int dis, string des,Vertice*graf){

        struct Vertice *vOrigen = buscarVertice(origen,graf);
        struct Vertice *vDestino = buscarVertice(des,graf);

        if(vOrigen == NULL){
            cout<<"\nNo se encuentra el origen.";
            return;
        }
        if(vDestino == NULL){
            cout<<"\nNo se encuentra el destino.";
            return;
        }
        struct Arco *nuevoArco = new Arco(dis,des);

        //se inserto al inicio de la sublista de Arcos
        nuevoArco->sigA = vOrigen->subListaArcos;
        vOrigen->subListaArcos = nuevoArco;

}

//Metodos Persona

//Metodo Buscar: inicia la busqueda a partir del indentificador unico de la persona que seria la cedula y retorna dicha persona 
Personas* buscarPersona(string ced){

    if(nodoPersona == NULL){
        cout<<"\nLista vacia.....\n";
        return NULL;
    }
    Personas*temp = nodoPersona;

    while(temp != NULL){

        if(temp->cedula == ced){
                cout<<"\n Persona encontrada...\n";
                return temp;
        }
        temp = temp->sig;
    }
    cout<<"\nNo encontrado en la lista";
    return NULL;
}

//Metodo Insertar: a partir del nodo de personas agrega a las personas con le metodo de una lista doble con insercion ordenado por nombre
Personas * insertarPersona(string nom , string ced , Vertice* inicio,string forma, Personas *lista){

    if(buscarPersona(ced)==NULL){
        Personas*nuevo = new Personas(nom,ced,inicio,forma);

        if(nodoPersona== NULL)
            lista = nuevo;
        else if (nom < lista->nombre){
            nuevo->sig = lista;
            lista->ant = nuevo;
            lista = nuevo;
        }
        else{//es en medio o al final de la lista
        Personas* temp = lista;
            while(temp!= NULL){
                if(nom>temp->nombre)
                    if (temp->sig != NULL){
                        if (nom<temp->sig->nombre)
                        {
                            nuevo->ant = temp;
                            nuevo->sig = temp->sig;
                            temp->sig->ant = nuevo;
                            temp->sig =nuevo;
                            return lista;


                        }
                        temp = temp->sig;
                        
                    }else{
                        nuevo->ant = temp;
                        temp->sig =nuevo;
                        return lista;
                    }
            }
        }
    }else{
        cout<<"Persona ya registrada";
    }
    return lista;
}

//Metodo Modificar: selecciona al nodo que se desea modificar por medio de su respectivo buscar
void modificarPersona(){
    string ced;
    string n;
    printf("Cedula de la persona:  ");
    cin>> ced;
    Personas*buscado = buscarPersona(ced);
    if (buscado == NULL){
        printf("Persona no encontrado");
    }else{
        printf("\n\nCedula de la persona:  ");
        cin>> ced;
        printf("\n\nNombre de la persona:  ");
        cin>> n;  
        buscado->nombre = n;
        buscado->cedula = ced;
    }
}

//Metodo Borrar: selecciona al nodo que se desea eliminar por medio de su respectivo buscar
void borrarPersona(string ced){
        Personas* buscado = buscarPersona(ced);
        if(buscado == NULL){
            cout<<"\n Persona no encontrada....\n";
            return;
        }
        else{
            if(buscado == nodoPersona){//si el buscado es el primero
                    nodoPersona = nodoPersona->sig;
                    if(nodoPersona != NULL)
                            nodoPersona->ant = NULL;
            }
            else{//borra en medio o al final
                buscado->ant->sig = buscado->sig;
                if(buscado->sig != NULL)
                    buscado->sig->ant = buscado->ant;
            }
        }
}

void cargarDatos(){
    //GRAFO1
    insertarVertice("Sabanilla",grafo1);
    insertarVertice("San Pedro",grafo1);
    insertarVertice("Curri",grafo1);
    insertarVertice("Tibas",grafo1);
    insertarVertice("Escalante",grafo1);

    insertarArco("Sabanilla",rand()%21,"San Pedro",grafo1);
    insertarArco("Sabanilla",rand()%21,"Curri",grafo1);
    insertarArco("Sabanilla",rand()%21,"Tibas",grafo1);
    insertarArco("San Pedro",rand()%21,"Curri",grafo1);
    insertarArco("San Pedro",rand()%21,"Escalante",grafo1);
    insertarArco("Curri",rand()%21,"Curri",grafo1);
    insertarArco("Tibas",rand()%21,"Escalante",grafo1);
    insertarArco("Tibas",rand()%21,"San Pedro",grafo1);
    insertarArco("Escalante",rand()%21,"Sabanilla",grafo1);
    insertarArco("Escalante",rand()%21,"San Pedro",grafo1);
    

    

    //GRAFO2
    insertarVertice("Lourdes",grafo2);
    insertarVertice("Campo",grafo2);
    insertarVertice("Gamonales",grafo2);
    insertarVertice("San Antonio",grafo2);
    insertarVertice("San Roque",grafo2);
    insertarVertice("San Vicente",grafo2);
    insertarVertice("Cedral",grafo2);

    insertarArco("Lourdes",rand()%21,"Gamonales",grafo2);
    insertarArco("Lourdes",rand()%21,"San Antonio",grafo2);
    insertarArco("Lourdes",rand()%21,"San Vicente",grafo2);
    insertarArco("Campo",rand()%21,"Lourdes",grafo2);
    insertarArco("Campo",rand()%21,"Campo",grafo2);
    insertarArco("Campo",rand()%21,"Gamonales",grafo2);
    insertarArco("Gamonales",rand()%21,"San Antonio",grafo2);
    insertarArco("Gamonales",rand()%21,"Cedral",grafo2);
    insertarArco("Gamonales",rand()%21,"San Roque",grafo2);
    insertarArco("San Roque",rand()%21,"San Roque",grafo2);
    insertarArco("San Roque",rand()%21,"Campo",grafo2);
    insertarArco("San Roque",rand()%21,"San Antonio",grafo2);
    insertarArco("San Roque",rand()%21,"Cedral",grafo2);
    insertarArco("San Roque",rand()%21,"Cedral",grafo2);
    insertarArco("San Antonio",rand()%21,"Campo",grafo2);
    insertarArco("San Antonio",rand()%21,"San Roque",grafo2);
    insertarArco("San Antonio",rand()%21,"Cedral",grafo2);
    insertarArco("Cedral",rand()%21,"Cedral",grafo2);
    insertarArco("Cedral",rand()%21,"Lourdes",grafo2);
    insertarArco("Cedral",rand()%21,"San Vicente",grafo2);
    insertarArco("San Vicente",rand()%21,"San Vicente",grafo2);
    insertarArco("San Vicente",rand()%21,"Lourdes",grafo2);
    insertarArco("San Vicente",rand()%21,"Campo",grafo2);
    insertarArco("San Vicente",rand()%21,"San Antonio",grafo2);
    insertarArco("San Vicente",rand()%21,"Cedral",grafo2);

    //Personas
    

}

//Metodo principal donde se ejecutara todo
int main(){
    cout<<"*****Sistema de caminatas*****";
    cargarDatos();

}


