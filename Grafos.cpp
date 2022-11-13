#include <iostream>
using namespace std;


struct Vertice{
    string nombre;

    struct Vertice * sigV;//para enlazar todos los vertices en una lista
    struct Arco *subListaArcos;//representa los arcos que salen de ese vertice

    bool visitado;
    Vertice (string nom){
            nombre = nom;
            sigV = NULL;
            subListaArcos = NULL;
            visitado = false;
    }
};

struct Arco{
    int distancia;
    string destino;
    struct Arco *sigA;//siguiente arco.
    Arco(int dis, string des){
            distancia = dis;
            destino = des;
            sigA = NULL;
    }
};

struct Personas{
    string nombre;
    string cedula;
    Personas * ant;
    Personas * sig;
    Personas(string nom,string ced){
        nombre = nom;
        cedula=ced;
        ant = NULL;
        sig = NULL;
    }

} * nodoPersona;

//Vertice

struct Vertice *grafo;// el apuntador inicial del grafo


void insertarVertice(string nom){
            struct Vertice *nuevoVertice = new Vertice(nom);

            nuevoVertice->sigV = grafo;
            grafo = nuevoVertice;
}


struct Vertice *   buscarVertice(string origen){
        struct Vertice *tempV = grafo;
        while(tempV != NULL){
            if(tempV->nombre == origen)
                return tempV;

            tempV = tempV->sigV;
        }
    return NULL;//no lo encontro
}


//Arco

void insertarArco(string origen, int dis, string des){

        struct Vertice *vOrigen = buscarVertice(origen);
        struct Vertice *vDestino = buscarVertice(des);

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

//Persona

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
Personas * insertarPersona(string nom , string ced ,Personas *lista){

    if(buscarPersona(c)==NULL){
        Personas*nuevo = new Personas(nom,ced);

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


}

int main(){
    cargarDatos();

}


