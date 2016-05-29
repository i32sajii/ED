/**
* @file vertice.hpp
* @brief PRACTICA 4
* @author IGNACIO SANCHEZ JIMENEZ
* @date 24/5/2016
* @version 1.1
*/
#ifndef VERTICE_HPP
#define VERTICE_HPP
#include <iostream>
#include <string>
using std::string;
/**
* @brief Espacio de nombres ED.
*/

namespace ed
{
  ///clase Vertice
    class Vertice
    {
    private:
        ///nombre de la ciudad
        string ciudad_;
        ///etiqueta unica que referencia a cada ciudad
        int etiqueta_;
    public:

/**
* @brief Obtiene el contenido del campo privado ciudad_.
* @return ciudad_: contenido del campo privado ciudad_.
*/
        string getCiudad()const
        {
            return ciudad_;
        }
/**
* @brief Obtiene el contenido del campo privado etiqueta_.
* @return ciudad_: contenido del campo privado etiqueta.
*/
        int getEtiqueta() const
        {
            return etiqueta_;
        }
/**
* @brief Modifica el contenido del campo privado ciudad_.
* @param ciudad: tipo string que contiene el valor a actualizar.
*/
        void setCiudad(const string &ciudad)
        {
            ciudad_=ciudad;
        }
/**
* @brief Modifica el contenido del campo privado etiqueta.
* @param etiqueta: tipo string que contiene el valor a actualizar.
*/
        void setEtiqueta(const int &etiqueta)
        {
            etiqueta_=etiqueta;
        }
/**
* @brief Comparador de igualdad de vertices.
* @param x: tipo Vertice que contiene el valor a comparar.
* @sa getCiudad()
* @return bool.
*/
        bool operator == (const Vertice &x)
        {
            if(this->getCiudad()==x.getCiudad())
            {
                return true;
            }
            return false;
        }
/**
* @brief Comparador de igualdad de vertices.
* @param v: tipo Vertice que contiene el valor a comparar.
* @sa getCiudad()
* @return bool.
*/
        bool operator!=(const Vertice &v)
        {
            return (this->getCiudad()!=v.getCiudad());
        }

    };
}
#endif
