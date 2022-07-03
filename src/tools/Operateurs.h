/*
 *      Author: Dominique Michel
 */

#ifndef OPERATEURS_H_
#define OPERATEURS_H_

#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <functional>

#include "Erreur.h"

using namespace std;


class OperationsBasiques {
public:

    template<class T>
    static const T plus(const T &x, const T &y) { return x + y; }

    template<class T>
    static const T moins(const T &x, const T &y) { return x - y; }

    template<class T>
    static const T fois(const T &x, const T &y) { return x * y; }

    template<class T, class S>
    static const T divise(const T &x, const S &y) { return x / y; }

    template<class T>
    static const T &affectation(T &x, const T &y) { return x = y; }

    template<class T>
    static const T &plusEgal(T &x, const T &y) { return x += y; }

    template<class T, class S>
    static const T &foisEgal(T &x, const S &a) { return x *= a; }

    template<class T>
    static bool egalite(const T &x, const T &y) { return x == y; }

    template<class T>
    static bool strictInferieur(const T &x, const T &y) { return x < y; }

    template<class T>
    static bool inferieurOuEgal(const T &x, const T &y) { return x <= y; }

    template<class T>
    static const T moinsUnaire(const T &x) { return -x; }

    template<class T>
    static const T inverse(const T &x);

    template<class T>
    static const T nonLogique(const T &x) { return !x; }

    template<class T>
    static double produitScalaire(const T &u1, const T &u2) { return u1 * u2; }

    template<class T>
    static double normeCarree(const T &u) { return u * u; }

    template<class T>
    static double norme(const T &u) { return sqrt(normeCarree(u)); }

    template<class T>
    static const T milieu(const T &x, const T &y) { return 0.5 * (x + y); }

//------------------------------------------------------------------------------------------------------------

    template<class T>
    static bool /*OperationsBasiques::*/pointeurToBooleen(const T *p) { return p; }

//------------------------------------------------------------------------------------------------------------

    template<class T>
    static bool /*OperationsBasiques::*/negationPointeurToBooleen(const T *p) { return !p; }

}; //------------------------ classe OperationsBasiques ----------------------------

template<>
inline /*static*/ const double OperationsBasiques::inverse<double>(const double &x) { return 1.0 / x; }

template<>
inline /*static*/ double OperationsBasiques::norme<double>(const double &u) { return abs(u); }

template<>
inline /*static*/ double OperationsBasiques::norme<int>(const int &u) { return abs(u); }

//-------------------------------------------------------------------------


/**
 * Cette classe est maladroite. On la garde uniquement pour assurer la compatibilité avec du code ancien.
 *
 * A cette classe, il faut préférer la classe ci-dessus : c-à-d la classe OperationsBasiques
 *
 * */
template<class T, class S>
class Operateurs {
public:
    static inline const T plus(const T &x, const T &y) { return x + y; }

    static inline const T moins(const T &x, const T &y) { return x - y; }

    static inline const T fois(const T &x, const T &y) { return x * y; }

    static inline const T divise(const T &x, const S &y) { return x / y; }

    static inline const T &affectation(T &x, const T &y) { return x = y; }

    static inline const T &plusEgal(T &x, const T &y) { return x += y; }

    static inline const T &foisEgal(T &x, const S &a) { return x *= a; }

    static inline bool egalite(const T &x, const T &y) { return x == y; }

    static inline bool strictInferieur(const T &x, const T &y) { return x < y; }

    static inline bool inferieurOuEgal(const T &x, const T &y) { return x <= y; }

    static inline const T moinsUnaire(const T &x) { return -x; }

    static double produitScalaire(const T &u1, const T &u2) { return u1 * u2; }

    static double normeCarree(const T &u) { return u * u; }

    static double norme(const T &u) { return sqrt(normeCarree(u)); }

    static inline const T identite(const T &x) { return x; }
};


/*

template <class T, class S>
class Operateurs
{
public:

static inline const T plus (const T & x, const T & y);
static inline const T moins (const T & x, const T & y);
static inline const T fois (const T & x, const T & y);
static inline const T divise (const T & x, const S & y);
static inline const T & affectation ( T & x, const T & y);
static inline const T & plusEgal ( T & x, const T & y);
static inline const T & foisEgal ( T & x, const S & a);
static inline bool egalite(const T & x, const T & y);
static inline bool strictInferieur(const T & x, const T & y);
static inline bool inferieurOuEgal(const T & x, const T & y);
static inline const T moinsUnaire(const T & x);
static double produitScalaire (const T & u1, const T & u2) {return u1*u2;}

static double normeCarree (const T & u) {return u*u;}
static double norme (const T & u) {return sqrt(normeCarree(u));}

static inline const T identite(const T & x){return x;}
};


template <class T, class S>
inline const T Operateurs<T,S>::plus (const T & x, const T & y)
{
return x + y;
}

template <class T, class S>
inline const T Operateurs<T,S>::moins (const T & x, const T & y)
{
return x - y;
}

template <class T, class S>
inline const T Operateurs<T,S>::fois (const T & x, const T & y)
{
return x * y;
}

template <class T, class S>
static inline const T Operateurs<T,S>::divise (const T & x, const S & y)
{
return x/y;
}

template <class T, class S>
inline const T & Operateurs<T,S>::affectation ( T & x, const T & y)
{
return x = y;
}


template <class T, class S>
inline const T & Operateurs<T,S>::plusEgal ( T & x, const T & y)
{
return x += y;
}

template <class T, class S>
inline const T & Operateurs<T,S>::foisEgal ( T & x, const S & a)
{
return x*=a;
}

template <class T, class S>
static inline bool Operateurs<T,S>::egalite(const T & x, const T & y) {return x == y;}

template <class T, class S>
static inline bool Operateurs<T,S>::strictInferieur(const T & x, const T & y) { return x < y; }

template <class T, class S>
static inline bool Operateurs<T,S>::inferieurOuEgal(const T & x, const T & y) { return x <= y; }


template <class T, class S>
static inline const T Operateurs<T,S>::moinsUnaire(const T & x) { return -x;}
*/

template<class T>
class ConditionEgalite {
public:
    T v;

    ConditionEgalite(const T &v) : v(v) {}

    bool condition(const T &a) const { return v == a; }

    bool operator()(const T &a) const { return condition(a); }
};

/**
 * indique si 2 valeurs sont à peu près égales, utiisée notamment par la méthode appartient(...) des tableaux
 *
 * */
template<class T>
class ConditionEgaliteEnviron {
public:
    T v;
    double EPS;

    ConditionEgaliteEnviron(const T &v, const double &EPS = 1.0e-4) : v(v), EPS(EPS) {}

    bool condition(const T &a) const { return norme2(a - v) < EPS; }

    bool operator()(const T &a) const { return condition(a); }
};


/**
 * Utilisée dans listes\ListeCirculaire.h echantillonneContourExterieur(...)
 * suppose qu'un appel à srand a été fait au préalable
 * */
/*
template <class T>
class Perturbation
{
double eps;
T germe;
*
 * retourne un objet x de classe T tel que | x - germe| < eps où |.| désigne la norme euclidienne
 *
const T (*random)(const T & germe, const double & rayon);
public:
Perturbation( const double & eps, const T (*random)(const T & germe, const double & rayon) = T::random):eps(eps),germe(0),random(random){}
const T f (const T & v) const { return v + random(germe,eps);}

const T operator () (const T & v) const { return f(v);}

};
*/

//--------------------------------------------------------------------------------------------

/**
 * Utilisée dans listes\ListeCirculaire.h echantillonneContourExterieur(...)
 * suppose qu'un appel à srand a été fait au préalable
 * */
template<class T>
class Perturbation {
    double eps;

/**
 * retourne un objet x de classe T tel que | x - germe| < eps où |.| désigne la norme euclidienne
 * */
    const T (*random)(const T &germe, const double &rayon);

public:
    Perturbation(const double &eps, const T (*random)(const T &germe, const double &rayon) = T::random) : eps(eps),
                                                                                                          random(random) {}

    const T f(const T &v) const { return v + random((T) 0, eps); }

    const T operator()(const T &v) const { return f(v); }

};

//-----------------------------------------------------------------------------------------------------------


/**
 * Générateur de valeur aléatoire de type T
 * RESULTAT : une valeur aléatoire x tel que | x - germe | < eps
 *
 * fait l'hypothèse que la classe T dispose d'une fct statique de génération aléatoire de valeur à partir d'un germe et d'un rayon
 *
 * Défini pour être placé comme foncteur paramètre d'une fct template
 *
 * */
template<class T>
class GenerateurAleatoire {
    T germe;
    double rayon;
public:
    GenerateurAleatoire(const T &germe, const double &rayon) : germe(germe), rayon(rayon) {}

    const T random() const { return T::random(germe, rayon); }

    const T operator()() const { return random(); }

};


/**
 * représente un opérateur binaire. L'application la plus courante est un arbre syntaxique
 * */
template<class T>
class OpBin {
public:
    virtual const T effectue(const T &a, const T &b) const = 0;

    virtual operator string() const = 0;
};

template<class T>
ostream &operator<<(ostream &o, const OpBin<T> *op) { return o << (string) (*op); }

template<class T>
class OpBinPlus : public OpBin<T> {
public:
    virtual const T effectue(const T &a, const T &b) const { return a + b; }

    virtual operator string() const { return "+"; }
};

template<class T>
class OpBinMoins : public OpBin<T> {
public:
    virtual const T effectue(const T &a, const T &b) const { return a - b; }

    virtual operator string() const { return "-"; }
};


/**
 * Problème non résolu : produit extérieur ? produit intérieur ? produit scalaire ?
 *
 *
 * */
template<class T>
class OpBinFois : public OpBin<T> {
public:
    virtual const T effectue(const T &a, const T &b) const { return a * b; }

    virtual operator string() const { return "*"; }
};


template<class T>
class OperateurProduitScalaire {
    T v;
public:
    OperateurProduitScalaire(const T &v) : v(v) {}

    const double f(const T &a) const { return v * a; }
};

//------------------------------------------------------

/**
 * Dans la pratique, T = Vecteur<double,3> ou T = Vecteur2D
 *
 * Attention, en dimension 3, le produit vectoriel n'est pas commutatif !
 * */
template<class T>
class OperateurProduitVectorielADroite {
    T v;
public:
    OperateurProduitVectorielADroite(const T &v) : v(v) {}

    const T f(const T &a) const { return v ^ a; }

    const T operator()(const T &a) const { return f(a); }
};

//------------------------------------------------------


template<class T>
class Comparateur1 {
public:
    bool comparaison(const T &a, const T &b) const { return a <= b; }

    bool operator()(const T &a1, const T &a2) const { return comparaison(a1, a2); }

    bool f(const T &a, const T &b) const {
        return comparaison(a, b);
    }             // pour assurer la compatibilité avec ObjetToFoncteurBinaire
};


template<class T>
class Comparateur2 {
public:
    bool comparaison(const T &a, const T &b) const { return a >= b; }

    bool operator()(const T &a1, const T &a2) const { return comparaison(a1, a2); }

    bool f(const T &a, const T &b) const {
        return comparaison(a, b);
    }             // pour assurer la compatibilité avec ObjetToFoncteurBinaire
};

//---------------------------------------------------------------------------------------------

/**
 * permet de comparer une valeur quelconque v avec une valeur fixée a
 *
 * retourne true si a <= v, false si a > v
 *
 * */
template<class T>
class ComparateurUnaire1 {
public:
    T a;

    ComparateurUnaire1(const T &a) : a(a) {}

    bool comparaison(const T &v) const { return a <= v; }

    bool operator()(const T &v) const { return comparaison(v); }

    bool f(const T &v) const { return comparaison(v); }
};

//--------------------------------------------------------------------------------------------------------

/**
 * permet de comparer une valeur quelconque v avec une valeur fixée a
 *
 * retourne true si a >= v, false si a < v
 *
 * */
template<class T>
class ComparateurUnaire2 {
public:
    T a;

    ComparateurUnaire2(const T &a) : a(a) {}

    bool comparaison(const T &v) const { return a >= v; }

    bool operator()(const T &v) const { return comparaison(v); }

    bool f(const T &v) const { return comparaison(v); }
};

//-----------------------------------------------------------------------------------------------------------------


/**
 * sert à encapsuler la fct  comparaison().
 *
 * */
template<class T>
class ObjetComparaison {
public:
    bool (*comparaison1)(const T &a, const T &b);

    ObjetComparaison(bool (*comparaison)(const T &a, const T &b)) :
            comparaison1(comparaison) {}

    bool comparaison(const T &a1, const T &a2) const { return comparaison1(a1, a2); }

    bool operator()(const T &a1, const T &a2) const { return comparaison1(a1, a2); }
};


/**
 *
 * sert à encapsuler la fct f1 dans un objet
 * respecte le contrat de la classe O paramètre template de la fct :
 * template < class T, class O>
 * inline const T *  positionMaxF(const T p[], const int m, const O * o)
 *
 * */
template<class T>
class ObjetFonction {
public:
    double (*f1)(const T &a);      // attribut de nature fonction
    ObjetFonction(double (*f1)(const T &a)) : f1(f1) {}

    double f(const T &a) const { return f1(a); }
};


/**
 * sert à encapsuler une fontion ordinaire dans un objet
 *
 * */
template<class S, class T>
class EnveloppeFonction {
    const S (*f1)(const T &s);

public:
    EnveloppeFonction(const S (*f)(const T &s)) : f1(f) {}


    const S f(const T &s) const { return f1(s); }

    const S operator()(const T &s) const { return f1(s); }

};


/**
 * sert à encapsuler une fontion ordinaire à 2 paramètres dans un objet
 *
 * */
template<class R, class S, class T>
class EnveloppeFonction2 {
    const R (*f1)(const S &s, const T &t);

public:
    EnveloppeFonction2(const R (*f)(const S &s, const T &t)) : f1(f) {}


    const R f(const S &s, const T &t) const { return f1(s, t); }

};


/**
 * sert à encapsuler une fontion ordinaire à 3 paramètres dans un objet
 *
 * */
template<class R, class S, class T, class U>
class EnveloppeFonction3 {
    const R (*f1)(const S &s, const T &t, const U &u);

public:
    EnveloppeFonction3(const R (*f)(const S &s, const T &t, const U &u)) : f1(f) {}


    const R f(const S &s, const T &t, const U &u) const { return f1(s, t, u); }

};


/**
 *
 * sert à encapsuler la fct f1 dans un objet
 * respecte le contrat de la classe O paramètre template de la fct :
 * template < class T, class O>
 * inline const T *  positionMaxF(const T p[], const int m, const O * o)
 *
 * */
template<class T>
class ObjetFonctionIdentite {
public:

    const T f(const T &a) const { return a; }

    const T operator()(const T &a) const { return a; }
};


/**
 *
 * sert à encapsuler une conversion forcée (autrement dit un cast)
 * dans un foncteur
 * */
template<class S, class T>
class ObjetConversionForcee {
public:

    const S f(const T &a) const { return (S) a; }

    const S operator()(const T &a) const { return f(a); }
};

//-----------------------------------------------------------

/**
 * Représente la fct constante v |---> a de ? ---> T
 * c-à-d que v est quelconque et de n'importe quel type
 *
 * */
template<class T>
class FoncteurConstant {
public:
    T a;

    FoncteurConstant(const T &a) : a(a) {}

    const T f() const { return a; }

    const T operator()() const { return f(); }
};

//-----------------------------------------------------------



/**
 * représente l'opération v |---> a*v de S x T --- > R
 *
 * */
template<class R, class S, class T>
class Multiplicateur {
public:
    S a;

    explicit Multiplicateur(const S &a = (S) 1) : a(a) {}

    const R f(const T &v) const { return a * v; }

    const R operator()(const T &v) const { return f(v); }
};


/**
 * représente la translation v |---> v + a de T ---> T
 *
 * */
template<class T>
class FoncteurTranslation {
public:
    T a;

    FoncteurTranslation(const T &a) : a(a) {}

    const T f(const T &v) const { return v + a; }

    const T operator()(const T &v) const { return f(v); }
};


/**
 * représente l'opération v |---> a*v + b de S x T --- > R
 *
 * */
template<class R, class S, class T>
class OperateurAffine {
public:
    S a;
    R b;

    OperateurAffine(const S &a, const R &b) : a(a), b(b) {}

    const R f(const T &v) const { return a * v + b; }

    const R operator()(const T &v) const { return f(v); }
};


/**
 * Convertisseur générique vers des string
 *
 * TACHE : convertit n'importe quel objet (au sens large, c'est-à-dire types simples aussi) en string
 *
 * HYPOTHESE : suppose que la classe T dispose de l'opérateur d'écriture : cout << ...
 *
 * * /
template <class T>
class ToString
{
public:
const string f(const T & a) const { ostringstream  o; o << a; return o.str();}
const string operator() (const T & a) const {return f(a);}

};
*/

/**
 * Convertisseur générique vers des string
 *
 * TACHE : convertit n'importe quel objet (au sens large, c'est-à-dire types simples aussi) en string
 *
 * HYPOTHESE : suppose que la classe T dispose de l'opérateur d'écriture : cout << ...
 *
 * */
template<class T>
class ToString {
public:
    string prefixe, suffixe;

    ToString(const string &prefixe = "", const string &suffixe = "") : prefixe(prefixe), suffixe(suffixe) {}


    const string f(const T &a) const {
        ostringstream o;
        o << prefixe << a << suffixe;
        return o.str();
    }

    const string operator()(const T &a) const { return f(a); }

};


template<>
inline const string ToString<bool>::f(const bool &a) const { return (a ? "true" : "false"); }


/**
 * Convertisseur générique de string vers le type T
 *
 * TACHE : convertit une string vers n'importe quel objet (au sens large, c'est-à-dire types simples aussi)
 *
 * HYPOTHESE : suppose que la classe T dispose de l'opérateur de lecture : cin >>  ...
 *
 * */
template<class T>
class FromString {
public:

    const T f(const string &s) const {
        istringstream is(s);
        T r;
        is >> r;
        if (is.fail()) throw Erreur("Dans FromString<T> : conversion de la string " + s + " vers le type T impossible");
        return r;
    }

    const T operator()(const string &s) const { return f(s); }

};


/**
 * Pour accéder à certains éléments du tableau t, à partir, par exemple d'un tableau d'indices
 *
 * Créé pour être combiné avec une méthode de type opUn(...) cf. OutilsTableaux.h
 *
 *
 * */
template<class T>
class AccesParIndex {
public:
    const T *t;

/**
 * t est un tableau dont on veut accéder seulement à certaines cases connues à l'aide d'un tableau d'indices
 *
 * */
    AccesParIndex(const T *t) : t(t) {}

/**
 * i est un indice valide d'une case de t
 *
 * */
    const T f(const int &i) const { return t[i]; }

    const T operator()(const int &i) const { return f(i); }

};


template<class T>
class DifferenceNormee {
public:
    const T f(const T &a, const T &b) const {
        T d = b - a;
        double n = norme(d);
        return d / n;
    }

    const T operator()(const T &a, const T &b) const { return f(a, b); }
};


template<class S, class T, class O>
class ObjetToFoncteur {
public:
    const O *o;

    ObjetToFoncteur(const O *o) : o(o) {}

    const S operator()(const T &t) const { return o->f(t); }
};

//-------------------------------------------------------------------------------

/**
 * transforme un objet disposant d'une méthode ayant la signature :
 *
 * void O::f( T & t) const;
 *
 * en un foncteur muni de l'opérateur :
 *
 * void operator() (T & t) const;
 *
 * On suppose que la méthode f() modifie le paramètre t
 *
 * */
template<class T, class O>
class ObjetToFoncteurVoid {
public:
    const O *o;

    ObjetToFoncteurVoid(const O *o) : o(o) {}

    void operator()(T &t) const { o->f(t); }
};

//-------------------------------------------------------------------------------


/*template <class S, class T, class O>
class OpposeObjetToFoncteur
{
public:
const O * o;
OpposeObjetToFoncteur( const O * o) : o(o) {}

const S operator () (const T & t) const {return -(o->f(t));}
};*/


//----------------------------------------------------------------

template<class S, class T, class FONCTEUR>
class FoncteurOppose {
public:
    FONCTEUR f;

    FoncteurOppose(const FONCTEUR &f) : f(f) {}

    const S operator()(const T &t) const { return -f(t); }
};

//----------------------------------------------------------------



template<class T, class O>
class ObjetConditionToFoncteur {
public:
    const O *o;

    ObjetConditionToFoncteur(const O *o) : o(o) {}

    bool operator()(const T &t) const { return o->condition(t); }
};


template<class T, class O>
class ObjetComparaisonToFoncteur {
public:
    const O *o;

    ObjetComparaisonToFoncteur(const O *o) : o(o) {}

    bool operator()(const T &a, const T &b) const { return o->comparaison(a, b); }
};


template<class R, class S, class T, class O>
class ObjetToFoncteurBinaire {
public:
    const O *o;

    ObjetToFoncteurBinaire(const O *o) : o(o) {}

    const R operator()(const S &s, const T &t) const { return o->f(s, t); }
};


template<class R, class S, class T, class U, class O>
class ObjetToFoncteurTernaire {
public:
    const O *o;

    ObjetToFoncteurTernaire(const O *o) : o(o) {}

    const R operator()(const S &s, const T &t, const U &u) const { return o->f(s, t, u); }
};


template<class S, class T>
class FoncteurCombinaisonLineaire {
public:

    const T f(const S &a, const T &u, const S &b, const T &v) const { return a * u + b * v; }

    const T operator()(const S &a, const T &u, const S &b, const T &v) const { return f(a, u, b, v); }

};

template<class S, class T>
class FoncteurCombinaisonLineaire2 {
public:
    S a, b;

    FoncteurCombinaisonLineaire2(const S &a, const S &b) : a(a), b(b) {}

    const T f(const T &u, const T &v) const { return a * u + b * v; }

    const T operator()(const T &u, const T &v) const { return f(u, v); }
};

//-----------------------------------------------------------

/**
 * sert à encapsuler la fct normeSup. Utilisée par les fcts qui calculent les normeSup
 * */

template<class T>
class ObjetNormeSup {
public:
    inline double f(const T &a) const { return T::normeSup(a); }

    double operator()(const T &a) const { return f(a); }
};

template<>
inline double ObjetNormeSup<double>::f(const double &a) const { return abs(a); }


template<>
inline double ObjetNormeSup<int>::f(const int &a) const { return abs(a); }


//-----------------------------------------------------------------------------------------

template<class T>
class FoncteurPivot {
public:

    double f(const T &x) const { return T::abs(x); }

    double operator()(const T &x) const { return f(x); }
};

template<>
inline double FoncteurPivot<double>::f(const double &x) const { return abs(x); }


//-------------------------------------------------------------------------------

/**
 * calcule la distance de x à v pour tout x.
 * v est fixé
 *
 * */
template<class T, class FONCTEUR_CALCUL_NORME = ObjetNormeSup<T>>
class FoncteurDistance {
public:
    T v;
    FONCTEUR_CALCUL_NORME c;

    FoncteurDistance(const T &v) : v(v) {}

    FoncteurDistance(const T &v, const FONCTEUR_CALCUL_NORME &c) : v(v), c(c) {}

    double operator()(const T &x) const { return c(x - v); }

};

//-------------------------------------------------------------------------------


template<class S, class T>
class FunctionToFoncteur {
public:
    function<const S(const T &)> f;

    FunctionToFoncteur(const function<const S(const T &)> &f) : f(f) {}

    const S operator()(const T &a) const { return f(a); }
};

//--------------------------------------------------------------------------------------

template<class S, class T, class U>
class FunctionBinaireToFoncteur {
public:
    function<const S(const T &, const U &)> f;

    FunctionBinaireToFoncteur(const function<const S(const T &, const U &)> &f) : f(f) {}

    const S operator()(const T &a, const U &b) const { return f(a, b); }
};

//--------------------------------------------------------------------------------------



/*
 * utilisé comme critère de détection d'anomalies
 *
 * Calcule d = |a|*|b| - a*b
 *
 * où |.| désigne la norme euclidienne
 *
 * Cette quantité d est telle que d >= 0
 * */
template<class T>
class PresqueOpposeCosinus {
public:
    double f(const T &a, const T &b) const {
        double a2b2 = OperationsBasiques::normeCarree<T>(a) * OperationsBasiques::normeCarree<T>(b);
        return sqrt(a2b2) - a * b;
    }

    double operator()(const T &a, const T &b) const { return f(a, b); }
};


//-------------------------------------------------------------------------------

/**
 * compose les foncteurs.
 *
 * On obtient la fct :
 *
 * g o f : T  ---> R
 *         t |---> g(f(t))
 * */
template<class R, class S, class T>
class FoncteurComposeUnaire {
public:
    function<const R(const S &)> g;
    function<const S(const T &)> f;

    FoncteurComposeUnaire(const function<const R(const S &)> &g,
                          const function<const S(const T &)> &f) : g(g), f(f) {}

    const R operator()(const T &t) const { return g(f(t)); }
};

//-------------------------------------------------------------------------------

/**
 * compose les foncteurs.
 *
 * On obtient la fct :
 *
 * g o f : T x U  ---> R
 *         (t,u) |---> g(f(t,u))
 * */
template<class R, class S, class T, class U>
class FoncteurComposeBinaire {
public:
    function<const R(const S &)> g;
    function<const S(const T &, const U &)> f;

    FoncteurComposeBinaire(const function<const R(const S &)> &g,
                           const function<const S(const T &, const U &)> &f) : g(g), f(f) {}

    const R operator()(const T &t, const U &u) const { return g(f(t, u)); }
};

//-------------------------------------------------------------------------------

/**
 * compose les foncteurs.
 *
 * On obtient la fct :
 *
 * g o f : T x U x V x W ---> R
 *         (t,u,v,w) |---> g(f(t,u,v,w))
 * */
template<class R, class S, class T, class U, class V, class W>
class FoncteurComposeQuaternaire {
public:
    function<const R(const S &)> g;
    function<const S(const T &, const U &, const V &, const W &)> f;

    FoncteurComposeQuaternaire(const function<const R(const S &)> &g,
                               const function<const S(const T &, const U &, const V &, const W &)> &f) : g(g), f(f) {}

    const R operator()(const T &t, const U &u, const V &v, const W &w) const { return g(f(t, u, v, w)); }
};

//-------------------------------------------------------------------------------

template<class T>
class FunctionToFoncteurVoid {
public:
    const function<const T(const T &)> &f;

    FunctionToFoncteurVoid(const function<const T(const T &)> &f) : f(f) {}

    void operator()(T &x) const { x = f(x); }
};

//------------------------------------------------------

/**
 * Utilisé pour calculer une différence divisée de la forme
 *
 *       Delta P      Pfinal - Pdébut
 *      --------- = -------------------
 *       Delta t      tfinal - tdébut
 *
 * Cette expression intervient lors du calcul de dérivée et en particulier de vitesse
 *
 *
 * */
template<class T>
class FoncteurTauxAccroissement {
public:
    const T f(const T &pDebut, const T &pFinal,
              const double &tDebut, const double &tFinal) const {
        T dp = pFinal - pDebut;
        double dt = tFinal - tDebut;

        return dp / dt;
    }

    const T operator()(const T &pDebut, const T &pFinal,
                       const double &tDebut, const double &tFinal) const {
        return f(pDebut, pFinal, tDebut, tFinal);
    }

};      // FoncteurTauxAccroissement

//------------------------------------------------------------------------------------------------------





#endif /* OPERATEURS_H_ */
