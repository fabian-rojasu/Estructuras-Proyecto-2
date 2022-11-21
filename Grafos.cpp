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
    string rutaMenor;
    int distanciaMenor ;
    bool existeRuta ;
    //Constructor
    Vertice (string nom){
            nombre = nom;
            sigV = NULL;
            subListaArcos = NULL;
            visitado = false;
            rutaMenor = "";
            distanciaMenor = 0; 
            existeRuta = false;
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




struct Amigos
{
    string nombre;
    string cedula;
    struct Amigos * sig;
    Amigos(string n, string c)
    {
        nombre = n;
        cedula = c;
        sig = NULL;

    };
    
};



//Esta estructura sera la que se utilice para representar a los individuos que van a recorrer los diferentes lugares
struct Personas{
    //Atributos de la estructura
    string nombre;
    string cedula;//Indentificador
    struct Vertice * inicio;//Este sera el punto de partida de la persona respectiva
    struct Amigos * listaAmigos;//Se declara la lista de personas las cuales se encuentrenen el camino
    string formaAvanzar; //Aqui se determinara la forma en la que la persona respectiva se transaladara por los diferentes lugares
    Personas * ant;
    Personas * sig;
    string estado;
    int duracion;
    //Constructor
    Personas(string nom,string ced, Vertice * ini, string FAva){
        nombre = nom;
        cedula=ced;
        inicio=ini;
        estado = inicio->nombre;
        formaAvanzar=FAva;
        listaAmigos = NULL;
        ant = NULL;
        sig = NULL;
        duracion = 0;
    }

} * nodoPersona;




//Metodos Vertice

struct Vertice *grafo1;// el apuntador inicial del grafo
struct Vertice *grafo2;// el apuntador inicial del grafo


struct Vertice * insertarVertice(string nom,Vertice *grafo){
    struct Vertice *nuevoVertice = new Vertice(nom);

    nuevoVertice->sigV = grafo;
    grafo = nuevoVertice;
    return grafo; 
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
        return NULL;
    }
    Personas*temp = nodoPersona;

    while(temp != NULL){

        if(temp->cedula == ced){
                return temp;
        }
        temp = temp->sig;
    }
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
    grafo1 = insertarVertice("Sabanilla",grafo1);
    grafo1 = insertarVertice("San Pedro",grafo1);
    grafo1 = insertarVertice("Curri",grafo1);
    grafo1 = insertarVertice("Tibas",grafo1);
    grafo1 = insertarVertice("Escalante",grafo1);

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
    grafo2 = insertarVertice("Lourdes",grafo2);
    grafo2 =insertarVertice("Campo",grafo2);
    grafo2 =insertarVertice("Gamonales",grafo2);
    grafo2 =insertarVertice("San Antonio",grafo2);
    grafo2 =insertarVertice("San Roque",grafo2);
    grafo2 =insertarVertice("San Vicente",grafo2);
    grafo2 =insertarVertice("Cedral",grafo2);

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
    insertarArco("Cedral",rand()%21,"Campo",grafo2);
    insertarArco("Cedral",rand()%21,"Lourdes",grafo2);
    insertarArco("San Vicente",rand()%21,"San Vicente",grafo2);
    insertarArco("San Vicente",rand()%21,"Lourdes",grafo2);
    insertarArco("San Vicente",rand()%21,"Campo",grafo2);
    insertarArco("San Vicente",rand()%21,"San Antonio",grafo2);
    insertarArco("San Vicente",rand()%21,"Cedral",grafo2);

    //Personas
    nodoPersona = insertarPersona("Geanca","208340764",buscarVertice("Campo",grafo2),"1",nodoPersona);
    nodoPersona = insertarPersona("a","208340760",buscarVertice("Campo",grafo2),"3",nodoPersona);
    nodoPersona = insertarPersona("b","208340761",buscarVertice("Cedral",grafo2),"2",nodoPersona);
    /*nodoPersona = insertarPersona("c","208340762",buscarVertice("Campo",grafo2),"1",nodoPersona);
    nodoPersona = insertarPersona("d","208340763",buscarVertice("Cedral",grafo2),"1",nodoPersona);
    nodoPersona = insertarPersona("f","208340765",buscarVertice("Gamonales",grafo2),"1",nodoPersona);
    nodoPersona = insertarPersona("g","208340766",buscarVertice("San Vicente",grafo2),"1",nodoPersona);
    nodoPersona = insertarPersona("h","208340767",buscarVertice("San Roque",grafo2),"1",nodoPersona);
    nodoPersona = insertarPersona("i","208340768",buscarVertice("Campo",grafo2),"1",nodoPersona);
    nodoPersona = insertarPersona("j","208340769",buscarVertice("San Vicente",grafo2),"1",nodoPersona);*/


}



/*void avanzar2(string ced,Vertice * grafo){
    
    Personas * persona = buscarPersona(ced);
    if (persona != NULL)
    {

        Arco * temp = persona->inicio->subListaArcos;
        int cambio = 100;
        string lugar = persona->inicio->nombre;
        string destino = "";
        while (temp != NULL)
        {
            if(temp->distancia < cambio){

                cambio = temp->distancia;
                destino = temp->destino;
            }
            temp = temp->sigA;
        }
        
        Vertice * vert = buscarVertice(destino,grafo);
        persona->visitados = insertarRecorrido(lugar,cambio,persona->visitados);
        persona->inicio = vert;
        persona->duracion = persona->duracion + cambio; 
        if (destino != lugar)
        {
            avanzar2(persona->cedula,grafo);
        }
    } 
}*/
int tiempo =0;

void avanzar1(Personas * per){
    Arco * arcoContador = per->inicio->subListaArcos;
    Arco * arco = per->inicio->subListaArcos;
    int contador = 0;
    while (arcoContador != NULL)
    {
        contador++;
        arcoContador = arcoContador->sigA;
    }
    int random = rand()%contador;
    contador = 0;
    while (contador != random){
        contador++;
        arco = arco->sigA;

    }
    if (per->duracion+arco->distancia == tiempo)
    {
        if (buscarVertice(per->inicio->nombre,grafo1) != NULL)
        {
            per->inicio = buscarVertice(arco->destino, grafo1);
            per->duracion = per->duracion+arco->distancia;
            per->estado = per->inicio->nombre;
        }
        if (buscarVertice(per->inicio->nombre,grafo2) != NULL)
        {
           per->inicio = buscarVertice(arco->destino, grafo2);
           per->duracion = per->duracion+arco->distancia;
           per->estado = per->inicio->nombre;
        }
        return;
    }
    per->estado = "Caminando";
}


void avanzar2(Personas * per){
    Vertice * ver = per->inicio;
    string nombre;
    int cambio = 100 ;
    while (ver->subListaArcos->sigA != NULL){
        if (ver->subListaArcos->distancia < cambio)
        {
            if (ver->visitado == false)
            {
                cambio = ver->subListaArcos->distancia;
                nombre = ver->subListaArcos->destino;
            }
  
        }
        ver->subListaArcos = ver->subListaArcos->sigA;
    }
    if (ver->subListaArcos->sigA == NULL)
    {
        cambio = ver->subListaArcos->distancia;
        nombre = ver->subListaArcos->destino;
        ver->visitado = true;
    }
    
    
    if (per->duracion+cambio == tiempo)
    {
        if (buscarVertice(per->inicio->nombre,grafo1) != NULL)
        {
            per->inicio = buscarVertice(nombre, grafo1);
            per->duracion = per->duracion+cambio;
            per->estado = per->inicio->nombre;
        }
        if (buscarVertice(per->inicio->nombre,grafo2) != NULL)
        {
           per->inicio = buscarVertice(nombre, grafo2);
           per->duracion = per->duracion+cambio;
           per->estado = per->inicio->nombre;
        }
        return;
    }
    per->estado = "Caminando";
}

void avanzar3(Personas * per){
    Vertice * ver = per->inicio;
    string nombre;
    int cambio = 100 ;
    while (ver->subListaArcos->sigA != NULL){
        if (ver->subListaArcos->distancia < cambio)
        {
            if (ver->visitado == false)
            {
                cambio = ver->subListaArcos->distancia;
                nombre = ver->subListaArcos->destino;
            }
  
        }
        ver->subListaArcos = ver->subListaArcos->sigA;
    }
    if (ver->subListaArcos->sigA == NULL)
    {   
        if (ver->visitado == false){
            cambio = ver->subListaArcos->distancia;
            nombre = ver->subListaArcos->destino;
            ver->visitado = true;
        }        
    }
    
    
    if (per->duracion+cambio == tiempo)
    {
        if (buscarVertice(per->inicio->nombre,grafo1) != NULL)
        {
            per->inicio = buscarVertice(nombre, grafo1);
            per->duracion = per->duracion+cambio;
            per->estado = per->inicio->nombre;
        }
        if (buscarVertice(per->inicio->nombre,grafo2) != NULL)
        {
           per->inicio = buscarVertice(nombre, grafo2);
           per->duracion = per->duracion+cambio;
           per->estado = per->inicio->nombre;
        }
        return;
    }
    per->estado = "Caminando";
}

void avanzar4(Personas * per, string destino){
    if (per->inicio->nombre == destino) {
        per->duracion= 0;
        per->estado = "Saliendo";
    }
    
}



void moverPersona(Personas* per){
    Personas * temp = per;
    string a;

    if(temp->formaAvanzar=="1"){
        avanzar1(temp);
        if(temp->sig!=NULL)
            moverPersona(temp->sig);
    }
    if(temp->formaAvanzar=="2"){        
        avanzar2(temp);
        if(temp->sig!=NULL)
            moverPersona(temp->sig);
    }
    tiempo++;
    moverPersona(nodoPersona); 
}

////////////////////////// Metodos Amigos//////////////////////////////
void agregarAmigos(Personas* persona1,Personas* persona2){
    Amigos* listAmigos1 = persona1->listaAmigos;
    Amigos* listAmigos2 = persona2->listaAmigos;
    Amigos* nuevoAmigoInicial = NULL;
    if(listAmigos1 == NULL){
        persona1->listaAmigos = new Amigos(persona2->nombre,persona2->cedula);
    }else{
        while (listAmigos1 != NULL){
            if(listAmigos1->cedula == persona2->cedula){
                return;
            }
            
            listAmigos1 = listAmigos1->sig;
            
        }
        nuevoAmigoInicial = new Amigos(persona2->nombre,persona2->cedula);
        nuevoAmigoInicial->sig = persona1->listaAmigos;
        persona1->listaAmigos = nuevoAmigoInicial;
    }
    if (listAmigos2 == NULL){
        persona2->listaAmigos = new Amigos(persona1->nombre,persona1->cedula);
    }else{
        while (listAmigos2 != NULL){
            if(listAmigos2->cedula == persona1->cedula){
                return;
            }
            
            listAmigos2 = listAmigos2->sig;
            
        }
        nuevoAmigoInicial = new Amigos(persona1->nombre,persona1->cedula);
        nuevoAmigoInicial->sig = persona2->listaAmigos;
        persona2->listaAmigos = nuevoAmigoInicial;
    }

}

//Consulta 2//
void personaPopu(){
    if(nodoPersona == NULL){
        cout<<"\n Lista de personas vacia....\n";
        return;
    }
    else{
        Personas*temp = nodoPersona;
        int amigos = 0;
        int size=0;
        string nombre;
        while (temp != NULL)
        {
            Amigos* listAmigos = temp->listaAmigos;
            
            while (listAmigos != NULL)
            {   
                size++;
                listAmigos = listAmigos->sig;
            }
            if(size>amigos){
                amigos=size;
                nombre = temp->nombre;
            }
            temp = temp->sig;
        }
        cout<<"\n La persona con mas amigos es "<< nombre <<" con un total de " << amigos << " amigos.";
        
    }
}
/// @brief reporte# 9
/// @param ced cedula de la persona a buscar
void buscarAmigos(string ced){
    Personas* buscado = buscarPersona(ced);
        if(buscado == NULL){
            cout<<"\n Persona no encontrada....\n";
            return;
        }else{
            int size=0;
            Amigos* listAmigos = buscado->listaAmigos;
            while (listAmigos != NULL)
            {   
                size++;
                cout<<"\n Amigos de "<<buscado->nombre<<":\n"<< listAmigos->nombre;
                listAmigos = listAmigos->sig;
            }
            cout<<"\n"<<buscado->nombre<<" tiene "<<size<<" amigos.";
        }
}

/// @brief REPORTE#10
void personaAsocial(){
if(nodoPersona == NULL){
        cout<<"\n Lista de personas vacia....\n";
        return;
    }
    else{
        Personas*temp = nodoPersona;
        while (temp != NULL)//recorre lista personas
        {
            if (temp->listaAmigos==NULL){
                cout<<"\n Personas sin amigos: \n" << temp->nombre << temp->cedula;
            }
        }
        
        
    }
}

//Metodo Imprimir: muestra todos los datos de dicho nodo
void imprimir(){
    if(nodoPersona == NULL){
        cout<<"\n Lista vacia........\n";
    }else{
        Personas*temp = nodoPersona;
        while(temp!= NULL){
            cout<<"\n Nombre: "<<temp->nombre<<",   "<<"\nCedula: "<<temp->cedula<<",   "<<"\n Inicio: "<<temp->inicio->nombre<<",   "<<"\n Forma avanzar: "<<temp->formaAvanzar<<",   ";
            temp = temp->sig;
        }
    }
    
    
}

void amplitud(Vertice*graf){
    struct Vertice *tempV = graf;

    while(tempV != NULL){//RECORRE LA LISTA DE VERTICES
        cout<<"\nVertice:  "<<tempV->nombre<<"\t";
        struct Arco *tempA = tempV->subListaArcos;

        while(tempA != NULL){//RECORRE LOS ARCOS DE LA LISTA DE ARCOS DEL VERTICE
                cout<<tempV->nombre<<tempA->destino<<tempA->distancia<<",  ";
            tempA = tempA->sigA;
        }
        tempV = tempV->sigV;
    }
}

void profundidad (struct Vertice *inicio, Vertice * graf){
    if((inicio == NULL) or (inicio->visitado== true)){
            cout<<endl;
        return;
    }

    inicio->visitado = true;

    struct Arco *tempA = inicio->subListaArcos;
    while(tempA != NULL){
        cout<<inicio->nombre<<tempA->destino<<tempA->distancia<<",  ";

        profundidad(buscarVertice(tempA->destino,graf),graf);

        tempA = tempA->sigA;
    }

}



void menuReportes(){
    cout<<"*****Sistema de Reportes*****";
    cout << "1) Amplitud del grafo " << endl;
    cout << "2) Profundidad del grafo " << endl;
    cout << "3) Lista de Personas " << endl;
    cout << "4) Rutas cortas " << endl;
    cout << "5) Buscar amigos " << endl;
    cout << "6) Persona sin amigos " << endl;
    cout << "7) Persona sin ruta " << endl;
    cout << "8) Salir " << endl;
    cout << "Digite el numero de opcion:" << endl;
    int opt;
    string nom;
    string ced;
    cin>> opt;
    switch (opt)
    {
    case 1:
        cout << "Digite el numero de grafo a revisar (1/2):" << endl;
        cin>> opt;
        if (opt == 1){
            amplitud(grafo1);
            menuReportes();

        }
        if (opt == 2){
            amplitud(grafo2);
            menuReportes();
        }

        break;
    case 2:
        cout << "Digite el numero de grafo a revisar (1/2):" << endl;

        cin>> opt;
        cout << "Digite el nombre del lugar inicial:" << endl;
        
        cin>> nom;
        if (opt == 1){
            profundidad(buscarVertice(nom,grafo1),grafo1);
            menuReportes();
        }
        if (opt == 2){
           profundidad(buscarVertice(nom,grafo2),grafo2);
           menuReportes();
        }
        
        break;
    case 3:
        imprimir();
        menuReportes();
        break;
    case 4:
        //////////falta reporte 8/////////
        break;
    case 5:
        cout << "Digite la cedula de la persona:" << endl;
        
        cin>> ced;
        buscarAmigos(ced);
        menuReportes();
        break;
    case 6:
        personaAsocial();
        menuReportes();
        break;
    case 7:
        ////////////reporte 11/////////
        menuReportes();
        break;
    case 8:
        return;
    default:
        cout << "La opcion escogida no es válida.\n";
        break;
    }
}

void menuMantenimientos(){
    cout<<"\t*****Sistema de mantenimiento*****";
    cout<<"*****Vertices*****";
    cout << "1) Crear vertice " << endl;
    cout << "2) Modificar vertice " << endl;
    cout << "3) Borrar vertice " << endl;
    cout<<"*****Arcos*****";
    cout << "4) Crear arco " << endl;
    cout<<"*****Personas*****";
    cout << "5) Crear persona " << endl;
    cout << "6) Modificar persona " << endl;
    cout << "7) Borrar persona " << endl;
    cout << "8) Salir " << endl;
    cout << "Digite el numero de opcion:" << endl;
    int opt;
    cin>> opt;
    string nom;
    int dis;
    string ced;
    string des;
    string form;
    switch (opt)
    {
    case 1:
        cout << "Digite el numero de grafo (1/2):" << endl;
        cin>> opt;
        cout << "Nombre del lugar: " << endl;
        cin>> nom;
        if (opt == 1){
            insertarVertice(nom,grafo1);
            menuMantenimientos();
        }
        if (opt == 2){
            insertarVertice(nom,grafo2);
            menuMantenimientos();
        }
        break;
    case 2:
        cout << "Digite el numero de grafo (1/2):" << endl;
        cin>> opt;
         if (opt == 1){
            modificarVertice(grafo1);
            menuMantenimientos();
        }
        if (opt == 2){
            modificarVertice(grafo2);
            menuMantenimientos();
        }
        break;
    case 3:
        cout << "Digite el numero de grafo (1/2):" << endl;

        cin>> opt;
        cout << "Nombre del lugar a borrar: " << endl;

        cin>> nom;
        if (opt == 1){
            borrarVertice(nom,grafo1);
            menuMantenimientos();
        }
        if (opt == 2){
            borrarVertice(nom,grafo2);
            menuMantenimientos();
        }
        break;
    case 4:
        cout << "Digite el numero de grafo (1/2):" << endl;

        cin>> opt;
        cout << "Nombre del lugar inicial: " << endl;

        cin>> nom;
        cout << "Nombre del lugar de destino: " << endl;
        
        cin>> des;
        cout << "Digite la distancia:" << endl;

        cin>> dis;
        if (opt == 1){
            insertarArco(nom,dis,des,grafo1);
            menuMantenimientos();
        }
        if (opt == 2){
            insertarArco(nom,dis,des,grafo2);
            menuMantenimientos();
        }
        break;
    case 5:
        cout << "Digite el numero de forma de avanzar (1/2/3/4):" << endl;
        
        cin>> form;
        cout << "Nombre de la persona: " << endl;

        cin>> nom;
        cout << "Cedula: " << endl;
        
        cin>> ced;
        cout << "Digite el numero de grafo (1/2):" << endl;

        cin>> opt;
        cout << "Digite el lugar de inicio:" << endl;
        
        cin>> des;
        if (opt == 1){
            insertarPersona(nom,ced,buscarVertice(des,grafo1),form,nodoPersona);
            menuMantenimientos();
        }
        if (opt == 2){
            insertarPersona(nom,ced,buscarVertice(des,grafo2),form,nodoPersona);
            menuMantenimientos();
        }
        break;
    case 6:
        modificarPersona();
        menuMantenimientos();
        break;
    case 7:
        cout << "Cedula de la persona a borrar: " << endl;

        cin>> ced;
        borrarPersona(ced);
        menuMantenimientos();
        break;
    case 8:
        return;
    default:
        cout << "La opcion escogida no es válida.\n";
        break;
    }
}   

void menu(){
    cout << endl <<"*****Sistema de caminatas*****"<< endl;
    cout <<"1) Iniciar Caminata " << endl;
    cout << "2) Reportes " << endl;
    cout << "3) Mantenimientos " << endl;
    cout << "4) Salir " << endl;
    cout << "Digite el numero de opcion:" << endl;
    int opt;
    cin>> opt;
    switch (opt)
    {
    case 1:
        
        break;
    case 2:
        menuReportes();
        break;
    case 3:
        menuMantenimientos();
        break;
    case 4:
        break;
    default:
        cout << "La opcion escogida no es válida.\n";
        break;
    }
}
//Metodo principal donde se ejecutara todo
int main(){
    cargarDatos();
    menu();

}


