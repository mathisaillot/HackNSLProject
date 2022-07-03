#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

template<class T>
class Vecteur2D {
public:
    T _x, _y;
    /*****************************************
     *              constr/destr             *
     *****************************************/
    Vecteur2D() : _x(0), _y(0) {}
    Vecteur2D(const T & x, const T & y) {
        *this = load(x, y);
    }
    Vecteur2D(const Vecteur2D<T> & o) {
        *this = load(o._x, o._y);
    }
    /*****************************************
     *                operator               *
     *****************************************/

    Vecteur2D<T> & operator = (const Vecteur2D<T> & opd) {
        if(this != &opd) {
            // rien a supprimer
            // on initialise notre vecteur a partir de opd
            *this = load(opd._x, opd._y);
        }
        return *this;
    }

    Vecteur2D<T> operator + (const Vecteur2D<T> & opd) const {
        return somme(*this, opd);
    }

    Vecteur2D<T> operator + (const T & opd) const {
        return somme(*this, Vecteur2D<T>(opd,opd));
    }

    Vecteur2D<T> operator - () const{
        return Vecteur2D<T>(-_x, -_y);
    }

    Vecteur2D<T> operator - (const Vecteur2D<T> & opd) const {
        return soustraction(*this, opd);
    }

    Vecteur2D<T> operator - (const T & opd) const {
        return soustraction(*this, Vecteur2D<T>(opd,opd));
    }

    Vecteur2D<T> operator*(const Vecteur2D<T> &v) const {
        return Vecteur2D<T>(_x * v.getX(), _y * v.getY());
    }

    Vecteur2D<T> operator/(const Vecteur2D<T> &v){
        return Vecteur2D<T>(_x / v.getX(), _y / v.getY());
    }

    Vecteur2D<T> operator*(T t) const{
        return Vecteur2D<T>(_x * t, _y * t);
    }

    Vecteur2D<T> operator/(T t){
        return Vecteur2D<T>(_x / t, _y / t);
    }

    const Vecteur2D<T> & operator += (const Vecteur2D<T> & opd) {
        return *this = (*this + opd);
    }

    bool operator == (const Vecteur2D<T>& opd){
        return (_x == opd.getX()) && (_y == opd.getY());
    }

    const Vecteur2D<T> & operator += (const T & opd) {
        return *this = (*this + opd);
    }

    const Vecteur2D<T> & operator -= (const Vecteur2D<T> & opd) {
        return *this = (*this - opd);
    }

    const Vecteur2D<T> & operator -= (const T & opd) {
        return *this = (*this - opd);
    }

    const Vecteur2D<T> & operator *= (const Vecteur2D<T> &v){
        _x *= v.getX();
        _y *= v.getY();
        return *this;
    }

    explicit operator std::string () const {
        std::ostringstream oss;
        oss << "(" << _x << "," << _y << ")";
        return oss.str();
    }

    friend std::ostream & operator << (std::ostream & os, const Vecteur2D<T> & vecteur2d) {
        return os << (std::string) vecteur2d;
    }
    /*****************************************
     *             getter/setter             *
     *****************************************/
    //// getter
    const T & getX() const { return _x; }
    const T & getY() const { return _y; }

    double get_norme() const {
        return sqrt(_x * _x + _y * _y);
    }

    const T & squared_length() const {
        return _x*_x + _y*_y;
    }
    
    Vecteur2D<T> get_vecteur_norme() const {
        double norme(get_norme());
        return Vecteur2D<T>(
            _x / norme, _y / norme
        );
    }
    //// setter
    Vecteur2D<T> & setX(const T & x) { 
        _x = x;
        return *this;
    }

    Vecteur2D<T> & setY(const T & y) { 
        _y = y;
        return *this;
    }
    /*****************************************
     *                  load                 *
     *****************************************/
    private:
    Vecteur2D<T> & load(const T & x, const T & y) {
        return setX(x).setY(y);
    }
    public:
    /*****************************************
     *                 delete                *
     *****************************************/
    /*****************************************
     *               primitives              *
     *****************************************/
    private:
    Vecteur2D<T> somme(const Vecteur2D<T> & opg, const Vecteur2D<T> & opd) const {
        return Vecteur2D<T>(opg._x + opd._x, opg._y + opd._y);
    }

    Vecteur2D<T> soustraction(const Vecteur2D<T> & opg, const Vecteur2D<T> & opd) const {
        return Vecteur2D<T>(opg._x - opd._x, opg._y - opd._y);
    }
    public:

    double distance(const Vecteur2D<T> &v, const Vecteur2D<T> &v2){
        return (sqrt((v.getX()-v2.getX()*(v.getX()-v2.getX())+(v.getY()-v2.getY())*(v.getY()-v2.getY()))));
    }
};
