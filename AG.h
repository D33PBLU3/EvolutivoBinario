#ifndef AG_H
#define AG_H
#include <math.h>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "Individuo.h"
#include "decoder.h"
#define TAM_POBLACION 30
#define GENERACIONES 40
#define PROB_MUTACION .03
#define PROB_CRUCE .4
#define LIM_SUP -1
#define LIM_INF -4

using namespace std;

class AG
{
    public:
        AG();
        virtual ~AG();
        Individuo* poblacion;
        Individuo* seleccion;
        ofstream log;
        decoder* dec;
    protected:

    private:
    void generaPoblacion();
    void seleccionCandidatos();
    void evaluacion();
    void best();
    void codifica();
    void ordenaPoblacion();
    void cruzar();
    Individuo elite();
    float funcionObjetivo(float);
    void mutacion(int);
    void resultados();
    int rdtsc();
};

#endif // AG_H
