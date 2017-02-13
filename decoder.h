#ifndef DECODER_H
#define DECODER_H
#include "Individuo.h"

class decoder
{
    public:
        decoder();
        virtual ~decoder();
        char cromosoma[TAM_CROMOSOMA+1];
        float fenotipo;
    protected:

    private:
};

#endif // DECODER_H
