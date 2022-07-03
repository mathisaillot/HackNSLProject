/*
 *      Author: Dominique Michel
 */
#ifndef ERREUR
#define ERREUR



#include <string>
#include <iostream>
#include <exception>

using namespace std;

class Erreur : public exception
{
public:
string message;
inline Erreur();
inline Erreur(const char * messageErreur);
inline Erreur(const string & messageErreur);

/*inline static void testeEgalite(int m, int n, const char * message);

inline static void testeNonEgalite(int m, int n, const char * message);*/

template <class T>
inline static void testeEgalite(const T &  m, const T &  n, const char * message);

template <class T>
inline static void testeNonEgalite(const T &  m, const T &  n, const char * message);


//----------------------------------------------------------------------------------------

/**
 * vérifie que a <= b
 * lance une exception si a > b
 *
 * */
template <class T>
static void testePlusPetitOuEgal(const T & a, const T & b, const string & message)
{                                                                                                       //cout << "appel à Erreur::testePlusPetitOuEgal, début"<<endl;
#ifdef DEBUG
if ( a > b ){ /*cout << "appel à Erreur::testePlusPetitOuEgal, avant throw"<<endl; */throw Erreur(message); /*Erreur(message);*//*cout << "appel à Erreur::testePlusPetitOuEgal, après throw"<<endl;*/}
#endif
}

//----------------------------------------------------------------------------------------

/**
 * lance une exception si x n'est pas dans [a,b]
 * */
template <class T>
static void testeAppartient(const T & a, const T & x, const T & b, const string & message)
{
Erreur::testePlusPetitOuEgal<T>(a,x,message);
Erreur::testePlusPetitOuEgal<T>(x,b,message);
}

//----------------------------------------------------------------------------------------

/*
*
 * vérifie que a <= b
 * lance une exception si a > b
 *
 *
inline static void testePlusPetitOuEgal(const int a, const int b, const char * message);

*
 * lance une exception si x n'est pas dans [a,b]
 *
inline static void testeAppartient(int a, int x, int b, const char * message);
*/

/**
 * vérifie que a <= b
 * lance une exception si a > b
 *
 * */
template <class T>
inline static void testePlusPetitOuEgal(const T & a, const T & b, const char * message) { testePlusPetitOuEgal( a, b, (string)message); }

/**
 * lance une exception si x n'est pas dans [a,b]
 * */
template <class T>
inline static void testeAppartient(const T & a, const T & x, const T & b, const char * message) { testeAppartient( a, x, b, (string) message); }


/**
 * lance une exception si d est vide
 * */

inline static void testeNonVide(const void *d, const char * message);

inline operator string() const;


//------------------------------------------------------------------------------------

virtual const char* what() const noexcept
{
static constexpr int LONGUEUR_MESSAGE = 500;

static char messageOldSchool[LONGUEUR_MESSAGE];

strncpy(messageOldSchool,((string)(*this)).c_str(),LONGUEUR_MESSAGE-1);      // monStrncpy(,,) est défini dans ChainesCar.h
return messageOldSchool;
}

};

inline ostream & operator << (ostream & os, const Erreur & erreur)
{
os << (string) erreur;
return os;
}


inline Erreur::Erreur() : message("Erreur !"){}

inline Erreur::Erreur(const char * messageErreur) : Erreur((string)messageErreur){}
/*
{
strcpy(this->message,"Erreur : ");
int l = strlen(messageErreur);
static int n = LONGUEURMESSAGE-9;
if (l <= n) strcat(this->message,messageErreur);
else
        {
        strncat(this->message,messageErreur,n);
        this->message[LONGUEURMESSAGE] = '\0';
        }
}
*/

Erreur::Erreur(const string & messageErreur) : Erreur()
{
this->message +=" "+messageErreur;
}

Erreur::operator string() const
{
return this->message;
}









template <class T>
inline void Erreur::testeEgalite(const T & m, const T & n, const char * message)
{
#ifdef DEBUG
if ( m != n ) {/*cout<<"avant throw dans testeEgalite(...)" << endl;*/ throw Erreur(message);}
#endif
}

template <class T>
inline void Erreur::testeNonEgalite(const T & m, const T & n, const char * message)
{
#ifdef DEBUG
if ( m == n ) throw Erreur(message);
#endif
}
/*

*
 * vérifie que a <= b
 * lance une exception si a > b
 *
 *
inline static void Erreur::testePlusPetitOuEgal(const int a, const int b, const char * message)
{                                                                                                       //cout << "appel à Erreur::testePlusPetitOuEgal, début"<<endl;
#ifdef DEBUG
if ( a > b ){ cout << "appel à Erreur::testePlusPetitOuEgal, avant throw"<<endl; throw Erreur(message); Erreur(message);cout << "appel à Erreur::testePlusPetitOuEgal, après throw"<<endl;}
#endif
}



*
 * lance une exception si x n'est pas dans [a,b]
 *
inline static void Erreur::testeAppartient(int a, int x, int b, const char * message)
{
Erreur::testePlusPetitOuEgal(a,x,message);
Erreur::testePlusPetitOuEgal(x,b,message);
}

*/
/**
 * vérifie que a <= b
 * lance une exception si a > b
 *
 * */
/*template <class T>
inline static void Erreur::testePlusPetitOuEgal(const T & a, const T & b, const char * message)
{                                                                                                       //cout << "appel à Erreur::testePlusPetitOuEgal, début"<<endl;
#ifdef DEBUG
if ( a > b ){ cout << "appel à Erreur::testePlusPetitOuEgal, avant throw"<<endl; throw Erreur(message); Erreur(message);cout << "appel à Erreur::testePlusPetitOuEgal, après throw"<<endl;}
#endif
}



*
 * lance une exception si x n'est pas dans [a,b]
 *
template <class T>
inline static void Erreur::testeAppartient(const T & a, const T & x, const T & b, const char * message)
{
Erreur::testePlusPetitOuEgal<T>(a,x,message);
Erreur::testePlusPetitOuEgal<T>(x,b,message);
}*/


/*{
#ifdef DEBUG
if ( !(  a <= x && x <= b ) ) throw Erreur(message);
#endif
}*/

/**
 * lance une exception si d est vide
 * */

inline /*static*/ void Erreur::testeNonVide(const void *d, const char * message)
{
#ifdef DEBUG
if ( !d ) throw Erreur(message);
#endif
}



#endif
