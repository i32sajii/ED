/**
* @file lado.hpp
* @brief PRACTICA 4
* @author IGNACIO SANCHEZ JIMENEZ
* @date 24/5/2016
* @version 1.1
*/
#ifndef LADO_HPP
#define LADO_HPP

#include "vertice.hpp"
/**
* @brief Espacio de nombres ED.
*/
using namespace ed;

namespace ed
{
  ///clase Lado
    class Lado
    {
    private:
        ///distancia
        double distancia_;
        /// primer vertice
        Vertice primero_;
        /// segundo vertice
        Vertice segundo_;

    public:

/**
* @brief Comparador de igualdad de lados.
* @param x: tipo Lado que contiene el valor a comparar.
* @sa getPrimero()
* @sa getSegundo()
* @return bool
*/
        bool operator == (const Lado &x)
        {
            if(this->getPrimero()==x.getPrimero() && this->getSegundo()==x.getSegundo())
            {
                return true;
            }
            return false;
        }
/**
* @brief Obtiene el contenido del campo privado distancia_.
* @return distancia_: contenido del campo privado distancia_.
*/
        double getDistancia() const
        {
            return distancia_;
        }
/**
* @brief Obtiene el contenido del campo privado primero_.
* @return primero_: contenido del campo privado primero_.
*/
        Vertice getPrimero() const
        {
            return primero_;
        }
/**
* @brief Obtiene el contenido del campo privado segundo_.
* @return segundo_: contenido del campo privado segundo_.
*/
        Vertice getSegundo() const
        {
            return segundo_;
        }
/**
* @brief Modifica el contenido del campo privado distancia_.
* @param distancia: tipo double que contiene el valor a actualizar.
*/
        void setDistancia(double &distancia)
        {
            distancia_=distancia;
        }
/**
* @brief Modifica el contenido del campo privado primero_.
* @param primero: tipo double que contiene el valor a actualizar.
*/
        void setPrimero(Vertice &primero)
        {
            primero_=primero;
        }
/**
* @brief Modifica el contenido del campo privado segundo_.
* @param segundo: tipo double que contiene el valor a actualizar.
*/
        void setSegundo(Vertice &segundo)
        {
            segundo_=segundo;
        }
    };
}
#endif
