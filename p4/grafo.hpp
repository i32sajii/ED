/**
* @file grafo.hpp
* @brief PRACTICA 4
* @author IGNACIO SANCHEZ JIMENEZ
* @date 24/5/2016
* @version 1.1
*/
#ifndef GRAFO_HPP
#define GRAFO_HPP
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "vertice.hpp"
#include "lado.hpp"
///macro para infinito
#define INFINITO 999999
using std::vector;
using std::ifstream;
using std::endl;
using std::cout;
/**
* @brief Espacio de nombres ED.
*/
using namespace ed;

namespace ed
{
/**
* @brief Clase Grafo.
*/
    class Grafo
    {
    private:
        ///vector con las ciudades y sus etiquetas
        vector<Vertice> v_;
        /// matriz de adyadcencia
        double ** matriz_;
        /// va dirigido o no
        bool dirigido_;
        ///cursor para vertices
        int cursorV_;
        ///cursor para lados
        int cursorL_;
        ///numero de vertices
        int nV_;
        ///numero de lados
        int nL_;
        ///capacidad total de la matriz de adyadcencia
        int capacidad_;

    public:
/**
* @brief Constructor por defecto.
* @param capacidad: (int) capacidad de la matriz de adyadcencia inicializado a 0.
* @param dirigido: (bool) es dirigido o no, inicializado a true.
*/
        Grafo(int capacidad=0, bool dirigido=true)
        {
            if(capacidad<0)
            {
                capacidad=0;
            }

            matriz_=new double*[capacidad];
            for(int i=0; i<capacidad; ++i) // reserva de memoria para la matriz.
            {
                matriz_[i]=new double[capacidad];
            }

            for(int i=0; i<capacidad; ++i)
            {
                for(int j=0; j<capacidad; ++j)
                {
                    matriz_[i][j]=INFINITO;
                }
            }
            nV_=0;
            nL_=0;
            capacidad_=capacidad;
            dirigido_=dirigido;
        }
/**
* @brief Devuelve el número de vertices.
* @return nV_: número de vertices.
*/
        int getNV() const
        {
            return nV_;
        }
/**
* @brief Devuelve el número de Lados.
* @return nL_: número de Lados.
*/
        int getNL() const
        {
            return nL_;
        }
/**
* @brief Devuelve la matriz de adyadcencias.
* @return matriz_: matriz de adyadcencias.
*/
        double **getMatriz() const
        {
            return matriz_;
        }
/**
* @brief Devuelve la capacidad de la matriz de adyadcencias.
* @return capacidad_: capacidad de la matriz de adyadcencias.
*/
        int getCapacidad() const
        {
            return capacidad_;
        }
/**
* @brief Comprueba si el el grafo esta vacio.
* @return bool: true->vacio false->no vacio.
*/
        bool isEmpty() const
        {
            if(nV_==0 && nL_==0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
/**
* @brief Comprueba si el grafo es dirigido o no.
* @return bool: true->dirigido false->no dirigido.
*/
        bool esDirigido() const
        {
            return dirigido_;
        }

/**
* @brief Obtiene la distancia entre ciudades/vertices adyacentes.
* @param x: vertice(ciudad1)
* @param y: vertice(ciudad2)
* @return distancia en kilometros.
*/
        double adyacentes(const Vertice &x, const Vertice &y)
        {
            return matriz_[x.getEtiqueta()][y.getEtiqueta()];
        }
/**
* @brief Comprueba si el cursor de los vertices esta en una posicion valida.
* @return bool.
*/
        bool buscarCursorVertice()const
        {
            if(cursorV_<nV_)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
/**
* @brief Comprueba si el cursor de los lados esta en una posicion valida.
* @return bool.
*/
        bool buscarCursorLado()const
        {
            if(cursorL_<nL_)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

/**
* @brief Obenemos el vertice al que apunta el cursor de vertices.
* @return v: contenido del vertice apuntado.
*/
        Vertice cursorVertice()const
        {
            Vertice v;
            if(buscarCursorVertice())
            {
                v=v_[cursorV_];
            }
            return v;
        }
/**
* @brief Obenemos el lado al que apunta el cursor de lados.
* @return l: contenido del lado apuntado.
*/
        Lado cursorLado()
        {
            Lado l;
            //rellenamos el contenido de l(lado).
            l.setDistancia(matriz_[cursorV_][cursorL_]);
            l.setPrimero(v_[cursorV_]);
            l.setSegundo(v_[cursorL_]);
            return l;
        }

/**
* @brief Ponemos a true la variable privada dirigido_.
*/
        void hacerDirigido()
        {
            dirigido_=true;
        }
/**
* @brief Ponemos a false la variable privada dirigido_.
*/
        void hacerIndirecto()
        {
            dirigido_=false;
        }

/**
* @brief Añadimos una nueva ciudad al grafo.
* @param ciudad: string que contiene el nombre de la ciudad.
* @sa setCiudad()
* @sa setEtiqueta()
*/
        void addVertice(const string &ciudad)
        {
            Vertice x;
            x.setCiudad(ciudad);
            x.setEtiqueta(nV_);
            nV_++;
            nL_++;
            v_.push_back(x);//añadimos la x "rellena"
        }
/**
* @brief Añadimos lado al grafo.
* @param distancia: distancia entre los 2 vertices que conecta.
* @param x: vertice(ciudad1)
* @param y: vertice(ciudad2)
* @sa esDirigido()
* @sa getEtiqueta()
*/
        void addLado(const double &distancia, const Vertice &x, const Vertice &y)
        {
                matriz_[x.getEtiqueta()][y.getEtiqueta()]=distancia;//distancia de ciudad x a ciudad y
                if(!esDirigido())
                {
                    matriz_[y.getEtiqueta()][x.getEtiqueta()]=distancia;// si no es dirigido añadimos distancia de y a x
                }
        }

/**
* @brief colocamos el cursor en una etiqueta especifica.
* @param pos: etiqueta a colocar
* @sa getEtiqueta()
*/
        void irA(const int pos)
        {
            for( int i = 0 ; i < nV_; ++i )
            {
                if(v_[i].getEtiqueta() == pos)//buscamos esa etiqueta
                {
                    cursorV_=v_[i].getEtiqueta();// actualizamos el cursor
                    return;
                }
            }
        }

/**
* @brief Mueve el cursor hacia la posicion del lado.
* @param x: vertice(ciudad1)
* @param y: vertice(ciudad2)
* @sa getEtiqueta()
* @sa buscarVertice()
* @sa buscarCursorVertice()
* @sa getCiudad()
*/
        void buscarLado(const Vertice &x, const Vertice &y)
        {
            bool enc1, enc2;

            buscarVertice(x.getCiudad());
            if(buscarCursorVertice())
            {
                enc1 = true;
            }
            buscarVertice(y.getCiudad());
            if(buscarCursorVertice())
            {
                enc2 = true;
            }
            if(enc1 && enc2)//si encontramos los 2 vertices actualizamos
            {
                cursorV_=x.getEtiqueta();
                cursorL_=y.getEtiqueta();
            }

        }

/**
* @brief Mueve el cursor hacia la posicion del vertice.
* @param ciudad: (string) ciudad a buscar
* @sa getEtiqueta()
* @sa getCiudad()
*/
        void buscarVertice(const string &ciudad)
        {
            int i, enc=0;
            for(i=0;i< nV_ and enc==0;i++)
            {
                if(v_[i].getCiudad()==ciudad)
                {
                    enc=1;
                    cursorV_=i;
                }
            }
        }
/**
* @brief Pone el cursor de vertices apuntando al primer elemento.
*/
        void inicioVertice()
        {
            cursorV_=0;
        }
/**
* @brief Movemos el cursor al siguiente vertice.
*/
        void siguienteVertice()
        {
            cursorV_++;
        }

/**
* @brief Comprobamos que estamos en la ultima posicion.
* @return bool.
*/
        bool afterEndVertice()const
        {
            if(cursorV_==nV_)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

/**
* @brief Comprobamos que estamos en ultimo lado.
* @return bool.
*/
        bool afterEndLado()const
        {
            if(nL_==cursorL_)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
/**
* @brief Coloca en la primera posicion valida.
* @param u: Vertice
*/
        void inicioLado(Vertice u)
        {
            cursorV_=u.getEtiqueta();
            cursorL_=0;
            while(matriz_[cursorV_][cursorL_]==INFINITO && !afterEndLado())//compueba que sea valida y distinta de infinito
            {
                cursorL_++;
            }
        }
/**
* @brief Avanza el cursor de lados.
*/
        void siguienteLado()
        {
            cursorL_++;
            while(matriz_[cursorV_][cursorL_]==INFINITO && !afterEndLado())//compueba que sea valida y distinta de infinito
            {
                cursorL_++;
            }
        }

    };
}
#endif
