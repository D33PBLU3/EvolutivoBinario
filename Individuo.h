#ifndef INDIVIDUO_H
#define INDIVIDUO_H
#define TAM_CROMOSOMA 5

class Individuo
{
    public:
        Individuo();
        virtual ~Individuo();
        int cromosoma;
        float fitness;
        float probSeleccion;

    protected:

    private:
};

#endif // INDIVIDUO_H
