/**
* @file main.hpp
* @brief PRACTICA 4
* @author IGNACIO SANCHEZ JIMENEZ
* @date 24/5/2016
* @version 1.1
*/
#ifndef MAIN_HPP
#define MAIN_HPP

#include <algorithm>//para mayusculas
#include "grafo.hpp"
#include "macros.hpp"
///macro para infinito
#define INFINITO 999999
using namespace ed;
using std::endl;
using std::cout;
using std::cin;

/**
* @brief Carga un grafo contenido en un fichero de texto.
* @param nfich: string nombre del fichero
*/
Grafo * cargarGrafo(string nfich);

/**
* @brief Muestra el grafo contenido en el sistema.
* @param g: grafo a mostrar
* @sa inicioVertice()
*/
void mostrarGrafo(Grafo* g);

/**
* @brief Comprueba si una ciudad esta contenida en el grafo.
* @param g: grafo en el que buscar.
* @param ciudad: ciudad a buscar en el grafo.
*/
bool existe(Grafo *g,string ciudad);

/**
* @brief Obtiene el camino minimo entre dos ciudades.
* @param g: grafo en el que buscar.
* @param origen: ciudad de inicio.
* @param destino: ciudad final.
* @param **intermedios: matriz de intermedios.
*/
void camino(Grafo *g,Vertice origen,Vertice destino,int **intermedios);

/**
* @brief Algoritmo de Floyd encargado de buscar caminos minimos.
* @param g: grafo en el que buscar.
* @param **distancias: matriz de distancias.
* @param **intermedios: matriz de intermedios.
*/
void Floyd(Grafo * &g,float **&distancias,int **&intermedios);

/**
* @brief Calcula las distancias a los demas vertices de todas las ciudades adyacentes.
* @param g: grafo en el que buscar.
* @param *suma: vector.
*/
void sumarDist(Grafo *g,int *suma);

/**
* @brief Obtiene la ciudad mas centrica.
* @param g: grafo en el que buscar.
* @param **dist: matriz de distancias.
*/
void minimo(Grafo * g, float **dist);

/**
* @brief Obtiene la suma de distancias de cada ciudad cuando es usada como origen.
* @param g: grafo en el que buscar.
* @param posicion: poscion de la ciudad a estudiar.
* @param **distancias: matriz de distancias.
*/
void distanciasCiudades(Grafo* g,int posicion,float** distancias);

/**
* @brief Transforma a mayúsculas una cadena.
* @param strToConvert Cadena a convertir.
*/
std::string toUpper(std::string strToConvert);

/**
* @brief Carga un grafo contenido en un fichero de texto.
* @param nfich: string nombre del fichero
* @sa addVertice()
* @sa buscarVertice()
* @sa cursorVertice()
* @sa addLado()
* @return g: (Grafo) grafo cargado o un grafo vacio en el caso de error en el fichero.
*/
Grafo * cargarGrafo(string nfich)
{

		Grafo *g;
		int n,d,distancia;
		bool dir;
		string c,c2;
		Vertice inicio,fin;

		ifstream fich(nfich.c_str());
		if(fich.is_open())//control de errores
		{
			fich>>n; //Obtengo el numero de nodos
			fich>>d; //Obtengo si el grafo es dirigido o no
			if(d==0)
				dir=false;

			else
				dir=true;

			g=new Grafo(n,dir); //Reservo memoria

			for(int i=0;i<n;i++)
			{
				fich>>c;
				g->addVertice(c);
			}

			while(fich>>c >>c2 >>distancia)
			{

				g->buscarVertice(c);
				inicio=g->cursorVertice();

				g->buscarVertice(c2);
				fin=g->cursorVertice();

				g->addLado(distancia,inicio,fin);

			}

			fich.close();
		}
		else
		{
			g=new Grafo();//devolvemos un grafo vacio para que salte el error en el main()
		}
			return g;
}

/**
* @brief Muestra el grafo contenido en el sistema.
* @param g: grafo a mostrar
* @sa inicioVertice()
* @sa getCiudad()
* @sa getEtiqueta()
* @sa siguienteVertice()
* @sa afterEndVertice()
* @sa inicioLado()
* @sa afterEndLado()
* @sa getPrimero()
* @sa getSegundo()
* @sa getDistancia()
* @return g: (Grafo) grafo cargado o un grafo vacio en el caso de error en el fichero.
*/
		void mostrarGrafo(Grafo* g)
		{

			Vertice v;
			Lado aux;
			std::cout <<endl<<endl<<BLUE<< "======================"<<endl<<RESET;
			cout<<GREEN<<"Vector de vertices"<<endl;
			std::cout <<BLUE<< "======================" <<RESET<<endl<<endl;

			g->inicioVertice();//nos ponemos al principio del grafo

			do{
				v=g->cursorVertice();
				cout<<v.getCiudad()<<"-->"<<GREEN<<v.getEtiqueta()<<endl<<RESET;
				g->siguienteVertice();


			}while(not g->afterEndVertice());
			std::cout <<endl<<endl<<BLUE<< "======================"<<endl<<RESET;
			cout<<GREEN<<"Matriz de adyacencia"<<endl;
			std::cout <<BLUE<< "======================" <<RESET<<endl<<endl;

			g->inicioVertice();

			do{
				v=g->cursorVertice();
				g->inicioLado(v);//nos colocamos en el primer lado del vertice estudiado en cada iteracion
				while(not g->afterEndLado())
				{
					aux=g->cursorLado();
					cout<<aux.getPrimero().getCiudad()<<"-->"<<aux.getSegundo().getCiudad()<<"-->"<<GREEN<<aux.getDistancia()<<RESET<<endl;

					g->siguienteLado();
				}
			g->siguienteVertice();
	  }while(not g->afterEndVertice());
	}

/**
* @brief Comprueba si una ciudad esta contenida en el grafo.
* @param g: grafo en el que buscar.
* @param ciudad: ciudad a buscar en el grafo.
* @sa irA()
* @sa cursorVertice()
* @sa getNV()
* @sa getCiudad()
* @return bool.
*/
bool existe(Grafo *g,string ciudad)
{
		Vertice u;

		for(int i=0;i<g->getNV();i++)//recorremos el grafo comparando las ciudades
		{
			g->irA(i);
			u=g->cursorVertice();

			if(ciudad==u.getCiudad())
			{
				return true;
			}
		}
		return false;

}

/**
* @brief Obtiene el camino minimo entre dos ciudades.
* @param g: grafo en el que buscar.
* @param origen: ciudad de inicio.
* @param destino: ciudad final.
* @param **intermedios: matriz de intermedios.
* @sa irA()
* @sa getEtiqueta()
* @sa cursorVertice()
* @sa getCiudad()
*/
void camino(Grafo *g,Vertice origen,Vertice destino,int **intermedios)
{
		if(intermedios[origen.getEtiqueta()][destino.getEtiqueta()] != -1)//-1 inicializado en floyd
		{
			g->irA(intermedios[origen.getEtiqueta()][destino.getEtiqueta()]);
			Vertice intermedio=g->cursorVertice();
			camino(g,origen,intermedio,intermedios);
			cout<<intermedio.getCiudad()<<" ";
			camino(g,intermedio,destino,intermedios);
		}
}

/**
* @brief Algoritmo de Floyd encargado de buscar caminos minimos.
* @param g: grafo en el que buscar.
* @param **distancias: matriz de distancias.
* @param **intermedios: matriz de intermedios.
* @sa irA()
* @sa getCapacidad()
* @sa cursorVertice()
* @sa getNV()
* @sa adyacentes()
*/
void Floyd(Grafo * &g,float **&distancias,int **&intermedios)
{
	int i,j,k;
	Vertice u,v;
	distancias=NULL;

	//Reservamos memoria para las dos matrices
	distancias=new float*[g->getCapacidad()];
	for(int i=0;i<g->getCapacidad();i++)
	distancias[i]=new float[g->getCapacidad()];

	intermedios=new int*[g->getCapacidad()];
	for(int i=0;i<g->getCapacidad();i++)
	intermedios[i]=new int[g->getCapacidad()];
	//fin reserva

//inicializamos las matrices
	for(i=0;i<g->getNV();i++)
	{
		for(j=0;j<g->getNV();j++)
		{
			intermedios[i][j]=-1;
			if(i==j)
			{
				distancias[i][j]=0;
			}
			else
			{
				g->irA(i);
				u=g->cursorVertice();
				g->irA(j);
				v=g->cursorVertice();
				distancias[i][j]=g->adyacentes(u,v);
			}
		}
	}
//Floyd busqueda de caminos minimos
for(k=0;k<g->getNV();k++)
{
	for(i=0;i<g->getNV();i++)
	{
		for(j=0;j<g->getNV();j++)
		{
			if( distancias[i][j] > ( (distancias[i][k]) + (distancias[k][j]) ) )
			{
			distancias[i][j]=( distancias[i][k]+distancias[k][j] );
			intermedios[i][j]=k;
			}
		}
	}
}

}
/**
* @brief Calcula las distancias a los demas vertices de todas las ciudades adyacentes.
* @param g: grafo en el que buscar.
* @param *suma: vector .
* @sa irA()
* @sa cursorVertice()
* @sa getNV()
* @sa adyacentes()
*/
void sumarDist(Grafo *g,int *suma)
{
	Vertice u,v;
	int x,total;

	for(int i=0;i<g->getNV();i++)
	{
		total=0;
		g->irA(i);
		u=g->cursorVertice();

		for(int j=0;j<g->getNV();j++)
		{
			g->irA(j);
			v=g->cursorVertice();
			x=g->adyacentes(u,v);//guardamos en x las distancias de los adyacentes

			if(x!=INFINITO)
			{
				total=total+x;//si no x es infinito, vamos acumulando las distancias
			}
		}
		suma[i]=total;
	}
}
/**
* @brief Obtiene la ciudad mas centrica.
* @param g: grafo en el que buscar.
* @param **dist: matriz de distancias.
* @sa irA()
* @sa cursorVertice()
* @sa getNV()
* @sa getCiudad()
*/
void minimo(Grafo * g, float **dist)
{
	Vertice v;
	float total,min=INFINITO;
	int posicion;

//recorremos la Matriz
	for(int i=0;i<g->getNV();i++)
	{
		total=0;

		for(int j=0;j<g->getNV();j++)
		{
			total=total+dist[i][j];
		}

		if(min>total)
		{
			min=total;
			posicion=i;//guardamos la etiqueta de la ciudad con menor distancia a las demas
		}
	}
	g->irA(posicion);
	v=g->cursorVertice();
	cout<<endl<<"La ciudad más centrica es: "<<GREEN<<v.getCiudad()<<RESET<<endl<<endl;
}

/**
* @brief Obtiene la suma de distancias de cada ciudad cuando es usada como origen.
* @param g: grafo en el que buscar.
* @param posicion: poscion de la ciudad a estudiar.
* @param **distancias: matriz de distancias.
* @sa irA()
* @sa cursorVertice()
* @sa getNV()
* @sa getCiudad()
*/
void distanciasCiudades(Grafo* g,int posicion,float** distancias)
{
	Vertice v;
	int total;
	total=0;
	g->irA(posicion);
	for(int j=0;j<g->getNV();j++)
	{
		total=total+distancias[posicion][j];
	}
	v=g->cursorVertice();
	cout<<YELLOW<<v.getCiudad()<<RESET<<"-->"<<GREEN<<total<<RESET<<endl;
}
/**
* @brief Transforma a mayúsculas una cadena.
* @param strToConvert Cadena a convertir.
* @return strToConvert en mayúsuclas.
*/
std::string toUpper(std::string strToConvert)
{
    std::transform(strToConvert.begin(), strToConvert.end(), strToConvert.begin(), ::toupper);

    return strToConvert;
}

#endif
