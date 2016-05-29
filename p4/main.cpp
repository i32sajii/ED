/**
* @mainpage
* @brief PRACTICA 4
* @author IGNACIO SANCHEZ JIMENEZ
* @date 24/5/2016
* @version 1.1
*/
#include <iostream>
#include <cstdlib>//para system("clear")
#include "grafo.hpp"
#include "main.hpp"
#include "macros.hpp"

using std::endl;
using std::cout;
using std::cin;

///espacio de nombres ed
using namespace ed;
///Main para probar el funcionamiento de la clase Grafo

int main()
{
	Grafo* g=new Grafo();
	int op, op2;
	bool encontrado;
	string nfich,origen,destino;
	float **distancias=NULL;
	int **intermedios=NULL;
	int*sumaM;
	Vertice v,u;
	system("clear");
std::cout <<endl<<endl<<endl;
cout<<" ██████╗ ██╗███████╗███╗   ██╗██╗   ██╗███████╗███╗   ██╗██╗██████╗  ██████╗"<<endl;
cout<<" ██╔══██╗██║██╔════╝████╗  ██║██║   ██║██╔════╝████╗  ██║██║██╔══██╗██╔═══██╗"<<endl;
cout<<" ██████╔╝██║█████╗  ██╔██╗ ██║██║   ██║█████╗  ██╔██╗ ██║██║██║  ██║██║   ██║"<<endl;
cout<<" ██╔══██╗██║██╔══╝  ██║╚██╗██║╚██╗ ██╔╝██╔══╝  ██║╚██╗██║██║██║  ██║██║   ██║"<<endl;
cout<<" ██████╔╝██║███████╗██║ ╚████║ ╚████╔╝ ███████╗██║ ╚████║██║██████╔╝╚██████╔╝"<<endl;
cout<<" ╚═════╝ ╚═╝╚══════╝╚═╝  ╚═══╝  ╚═══╝  ╚══════╝╚═╝  ╚═══╝╚═╝╚═════╝  ╚═════╝ "<<endl;

LUGAR(23, 25);
std::cout << GREEN;
std::cout << "Pulse ";
INVERSO;
std::cout << "ENTER";
std::cout << RESET;
std::cout << GREEN;
std::cout << " para ";
std::cout << "iniciar el programa";
std::cout << RESET;

	do{
		cin.ignore();
		system("clear");
		cout<<endl<< "**** Menu ****"<<endl;
		cout<< "0. Terminar."<<endl;
		cout<< "1. Cargar grafo desde el fichero."<<endl;
		cout<< "2. Mostrar el grafo por pantalla."<<endl;
		cout<< "3. Aplicar el algoritmo de Floyd." <<endl;

		std::cout<< RESET;
		SUBRAYADO;
		cout<<endl<<"\t"<<"introducir opcion del menu:";
		std::cout<< RESET<<" ";
		std::cout<<INTENSIDAD<<MAGENTA;
		cin>>op;// OjO si metemos un valor no entero, lo mas normal es que si inicialize a null por lo que entrara al case 0 y acabara el programa.
		std::cout << RESET;

		switch(op)
		{
			case 0:

			system("clear");
			exit(EXIT_SUCCESS);
			APAGA;
			break;

			case 1:

			cout<<"Introduzca el nombre del fichero: "<<INTENSIDAD<<MAGENTA;
			cin>>nfich;
			cout<<RESET;
			g=cargarGrafo(nfich);
			if(g->isEmpty())//control de error de fichero
			{
				std::cout <<RED<<"ERROR, introduzca un fichero valido" << std::endl;
			}
			else
			{
				std::cout <<GREEN<<"Fichero cargado correctamente"<<RESET<< std::endl;
			}

			std::cout << std::endl<<endl;

			LUGAR(23, 25);
			std::cout << GREEN;
			std::cout << "Pulse ";
			INVERSO;
			std::cout << "ENTER";
			std::cout << RESET;
			std::cout << GREEN;
			std::cout << " para ";
			std::cout << "volver al menu";
			std::cout << RESET;

		cin.ignore();
			break;

			case 2:

			if(g->isEmpty())//control de error
			{
				std::cout << RED;
				cout<<"Debe cargar primero un grafo"<<endl;
				std::cout << RESET;
			}
			else
			{
				mostrarGrafo(g);
			}
			std::cout << std::endl<<endl;

			LUGAR(23, 25);
			std::cout << GREEN;
			std::cout << "Pulse ";
			INVERSO;
			std::cout << "ENTER";
			std::cout << RESET;
			std::cout << GREEN;
			std::cout << " para ";
			std::cout << "volver al menu";
			std::cout << RESET;

		cin.ignore();
			break;

			case 3:

			if(g->isEmpty())//control de error
			{
				std::cout << RED;
				cout<<"Debe cargar primero un grafo"<<endl;
				std::cout << RESET;
			}
			else
			{
				Floyd(g,distancias,intermedios);

				system("clear");
				cout<<endl<< "**** MenuFloyd ****"<<endl;
				cout<< "1. Mostrar la ciudad más céntrica."<<endl;
				cout<< "2. Mostrar información de distancias de todas las ciudades."<<endl;
				cout<< "3. Mostrar el El camino mínimo entre 2 ciudades."<<endl;
				cout<< "X. cualquier otro número para salir del menú Floyd"<<endl;
				SUBRAYADO;
				cout<<endl<<"\t"<<"introducir opcion del subMenu:";
				std::cout<< RESET<<" ";
				std::cout<<INTENSIDAD<<MAGENTA;
				cin>>op2;
				std::cout <<endl<< RESET;
				switch (op2)
				{
					case 1:
							minimo(g,distancias);//el vértice que tiene la menor suma de distancias a los demás vértices
						break;
					case 2:
							sumaM=new int[g->getNV()];
							sumarDist(g,sumaM);//sumaM almacenara las distancias a los demas vertices de todas las ciudades adyacentes

							std::cout <<endl<< "Suma de distancias a los demás vértices de todas las ciudades:" <<endl<<endl;
							for(int i=0;i<g->getNV();i++)
							{
								g->irA(i);
								u=g->cursorVertice();
								cout<<YELLOW<<"\t"<<u.getCiudad()<<RESET<<"-->"<<GREEN<<sumaM[u.getEtiqueta()]<<RESET<<endl;
							}
							std::cout <<endl<< "Suma de distancias cuando cada ciudad es usada como origen" <<endl<<endl;
							for(int i=0;i<g->getNV();i++)
							{
								std::cout <<"\t";
								distanciasCiudades(g,i,distancias);
							}
						break;
					case 3:
							do{

								cout<<endl<<"\t"<<BLUE<<"Introduce el nodo de inicio: "<<INTENSIDAD<<MAGENTA;
								cin>>origen;
								origen=toUpper(origen);
								cout<<RESET;
								encontrado=existe(g,origen);
								if(not encontrado)
								cout<<RED<<"La ciudad especificada no se encuntra en el grafo..."<<endl<<RESET;
							}while(not encontrado);


							do{
								cout<<endl<<"\t"<<BLUE<<"Introduce el destino: "<<INTENSIDAD<<MAGENTA;
								cin>>destino;
								destino=toUpper(destino);
								cout<<RESET;

								encontrado=existe(g,destino);
								if(not encontrado)
								cout<<RED<<"La ciudad especificada no se encuntra en el grafo..."<<endl<<RESET;
							}while(not encontrado);

							g->buscarVertice(origen);
							u=g->cursorVertice();

							g->buscarVertice(destino);
							v=g->cursorVertice();

							if( distancias[u.getEtiqueta()][v.getEtiqueta()] == 0 )
							cout<<"No existe distancia mínima"<<endl;
							else
							cout<<endl<<"La distancia mínima entre "<<u.getCiudad()<<" y "<<v.getCiudad()<<" es: "<<GREEN<<distancias[u.getEtiqueta()][v.getEtiqueta()]<<RESET<<endl;

							cout<<"El camino mínimo es: ";
							cout<<GREEN<<origen<<" ";
							camino(g,u,v,intermedios);
							cout<<destino<<endl<<RESET;
						break;
					default:
						break;
				}

					}
			std::cout << std::endl<<endl;

			LUGAR(23, 25);
			std::cout << GREEN;
			std::cout << "Pulse ";
			INVERSO;
			std::cout << "ENTER";
			std::cout << RESET;
			std::cout << GREEN;
			std::cout << " para ";
			std::cout << "volver al menu";
			std::cout << RESET;

		cin.ignore();
			break;

			default:
			std::cout << ONRED;
			cout<<"opcion no valida"<<endl;
			std::cout << RESET;

			std::cout << std::endl<<endl;

			LUGAR(23, 25);
			std::cout << GREEN;
			std::cout << "Pulse ";
			INVERSO;
			std::cout << "ENTER";
			std::cout << RESET;
			std::cout << GREEN;
			std::cout << " para ";
			std::cout << "volver al menu";
			std::cout << RESET;

			cin.ignore();
			break;

		}

	}while(op!=0);
	cout<<RESET;
	return 0;
}
