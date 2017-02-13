#include "AG.h"

AG::AG()
{
    log.open("log.txt",ios::out|ios::trunc);
    codifica();
    generaPoblacion();
    Individuo best;
    for(int j=1;j<=GENERACIONES;j++){
        evaluacion();
        log<<"Poblacion Actual"<<endl;
        for(int i=0; i<TAM_POBLACION; i++)
            log<<dec[poblacion[i].cromosoma].cromosoma<<"  "<<dec[poblacion[i].cromosoma].fenotipo<<" "<<poblacion[i].fitness-100.0<<endl;
        seleccionCandidatos();
        cruzar();
        best=elite();
        seleccion[TAM_POBLACION-1]=best;
        log<<"GENERACION: "<<j<<"  Best: "<<dec[best.cromosoma].cromosoma
    <<" fenotipo"<<dec[best.cromosoma].fenotipo<<endl;


        poblacion=seleccion;

    }

}

AG::~AG()
{
    //dtor
}
void AG::codifica()
{
    int tamdec=pow(2,TAM_CROMOSOMA);
    dec = new decoder[tamdec];
    float tamVect=LIM_SUP-LIM_INF;
    float valor=LIM_INF;
    float rang=tamVect/(pow(2,TAM_CROMOSOMA));
    for(int j=0; j<pow(2,TAM_CROMOSOMA); j++)
    {
        dec[j].fenotipo=valor;
        valor=valor+rang;
    }
    strcpy(dec[0].cromosoma,"11110");
    strcpy(dec[1].cromosoma,"11100");
    strcpy(dec[2].cromosoma,"11010");
    strcpy(dec[3].cromosoma,"10110");
    strcpy(dec[4].cromosoma,"01110");
    strcpy(dec[5].cromosoma,"00110");
    strcpy(dec[6].cromosoma,"10010");
    strcpy(dec[7].cromosoma,"11000");
    strcpy(dec[8].cromosoma,"10100");
    strcpy(dec[9].cromosoma,"01010");
    strcpy(dec[10].cromosoma,"01100");
    strcpy(dec[11].cromosoma,"00010");
    strcpy(dec[12].cromosoma,"00100");
    strcpy(dec[13].cromosoma,"01000");
    strcpy(dec[14].cromosoma,"10000");
    strcpy(dec[15].cromosoma,"00000");
    strcpy(dec[16].cromosoma,"11111");
    strcpy(dec[17].cromosoma,"11101");
    strcpy(dec[18].cromosoma,"11011");
    strcpy(dec[19].cromosoma,"10111");
    strcpy(dec[20].cromosoma,"01111");
    strcpy(dec[21].cromosoma,"00111");
    strcpy(dec[22].cromosoma,"10011");
    strcpy(dec[23].cromosoma,"11001");
    strcpy(dec[24].cromosoma,"10101");
    strcpy(dec[25].cromosoma,"01011");
    strcpy(dec[26].cromosoma,"01101");
    strcpy(dec[27].cromosoma,"00011");
    strcpy(dec[28].cromosoma,"00101");
    strcpy(dec[29].cromosoma,"01001");
    strcpy(dec[30].cromosoma,"10001");
    strcpy(dec[31].cromosoma,"00001");


}
void AG::generaPoblacion()
{
    int num;
    srand(rdtsc());
    poblacion=new Individuo[TAM_POBLACION];
    for(int j=0; j<TAM_POBLACION; j++)
    {
        num=rand()%32;
        poblacion[j].cromosoma=num;
    }


}
void AG::evaluacion()
{

    for(int j=0; j<TAM_POBLACION; j++)
    {
        poblacion[j].fitness=funcionObjetivo(dec[poblacion[j].cromosoma].fenotipo);
        //log<<poblacion[j].fitness<<endl;
    }

}
float AG::funcionObjetivo(float x)
{
    int offset=pow(LIM_INF,4)+5*pow(LIM_INF,3)+4*pow(LIM_INF,2)-4*LIM_INF+1;
    float y =-(pow(x,4)+5*pow(x,3)+4*pow(x,2)-4*x+1)+100.0;//(float)(abs(offset));
    return y;
}
void AG::seleccionCandidatos()
{
    float totalFitness=0;
    int num;
    Individuo padre;
    Individuo madre;
    float prob=0;
    seleccion=new Individuo[TAM_POBLACION];
    float probabilidades[TAM_POBLACION];
    srand(rdtsc());
    for(int j=0; j<TAM_POBLACION; j++)
    {
        totalFitness=totalFitness+poblacion[j].fitness;
    }
    for(int j=0; j<TAM_POBLACION; j++)
    {
        poblacion[j].probSeleccion=(poblacion[j].fitness*100.0)/totalFitness;
        prob=prob+poblacion[j].probSeleccion;
    }
    ordenaPoblacion();
    log<<"RULETA:"<<endl;
    for(int i=0; i<TAM_POBLACION; i=i+2)
    {
        prob=0;
        num=rand()%101;
        log<<num<<endl;
        for(int j=0; j<TAM_POBLACION; j++)
        {
            prob=prob+poblacion[j].probSeleccion;
            if(prob>num)
            {
                seleccion[i]=poblacion[j];
                log<<dec[seleccion[i].cromosoma].fenotipo<<" "<<dec[seleccion[i].cromosoma].cromosoma<<endl;
                break;
            }

        }
        prob=0;
        num=rand()%101;
        log<<num<<endl;
        for(int j=0; j<TAM_POBLACION; j++)
        {
            prob=prob+poblacion[j].probSeleccion;
            if(prob>num)
            {     seleccion[i+1]=poblacion[j];
                if(seleccion[i+1].cromosoma==seleccion[i].cromosoma){
                    prob=0;
                    num=rand()%101;
                    j=-1;
                }
                else{
                    //seleccion[i+1]=poblacion[j];
                    log<<dec[seleccion[i+1].cromosoma].fenotipo<<endl;
                    break;
                }
            }
        }
    }

}

void AG::ordenaPoblacion()
{
    Individuo tmp;
    for(int i=0; i<TAM_POBLACION; i++)
    {
        for(int j=0; j<TAM_POBLACION-1; j++)
        {
            if(poblacion[j].probSeleccion>poblacion[j+1].probSeleccion)
            {
                tmp=poblacion[j];
                poblacion[j]=poblacion[j+1];
                poblacion[j+1]=tmp;
            }
        }

    }
    for(int i=0;i<TAM_POBLACION;i++)
        log<<poblacion[i].probSeleccion<<endl;
}

void AG::cruzar()
{
    int num;
    char tmp;
    char padreA[TAM_CROMOSOMA+1];
    char padreB[TAM_CROMOSOMA+1];
    log<<"CRUCE:"<<endl;
    srand(rdtsc());
    for(int j=0;j<TAM_POBLACION;j=j+2){

        if((double) rand()/(RAND_MAX+1.0) < PROB_CRUCE)
        {
            num=1+rand()%((TAM_CROMOSOMA+1)-1);

            log<<num<<endl;
            strcpy(padreA,dec[seleccion[j].cromosoma].cromosoma);
            strcpy(padreB,dec[seleccion[j+1].cromosoma].cromosoma);
            log<<"Padres: "<<padreA<<"  "<<padreB<<endl;
            for(int i=0;i<num;i++){
                tmp=padreA[i];
                padreA[i]=padreB[i];
                padreB[i]=tmp;
            }
            log<<"hijos: "<<padreA<<"  "<<padreB<<endl;

            for(int i=0;i<pow(2,TAM_CROMOSOMA);i++){
                if(strcmp(padreA,dec[i].cromosoma)==0)
                    seleccion[j].cromosoma=i;
                if(strcmp(padreB,dec[i].cromosoma)==0)
                    seleccion[j+1].cromosoma=i;
                }
            mutacion(j);
            }
        //mutacion(j);
        }

    for(int j=0; j<TAM_POBLACION-1; j++)
    {
       // cout<<dec[seleccion[j].cromosoma].fenotipo<<endl;
    }

}
Individuo AG::elite(){
    Individuo elite=poblacion[0];

    for(int j=1;j<TAM_POBLACION;j++){
        if(poblacion[j].fitness>elite.fitness)
            elite=poblacion[j];
    }
    return elite;
}

void AG::mutacion(int i){
    char pA[TAM_CROMOSOMA+1];
    char pB[TAM_CROMOSOMA+1];
    strcpy(pA,dec[seleccion[i].cromosoma].cromosoma);
    strcpy(pB,dec[seleccion[i+1].cromosoma].cromosoma);

    for(int j=0; j<TAM_CROMOSOMA; j++){
        if ((double) rand()/(RAND_MAX+1.0) < PROB_MUTACION)
        {   log<<"MUTACION! "<<j<<endl;
            if(pA[j]=='1')
                pA[j] ='0';
            else pA[j] = '1';
        }
    }
    for(int j=0; j<TAM_CROMOSOMA; j++){
        if ((double) rand()/(RAND_MAX+1.0) < PROB_MUTACION)
        {   log<<"MUTACION! "<<j<<endl;
            if(pB[j]=='1')
                pB[j] ='0';
            else pB[j] = '1';
        }
    }
    log<<"mutados "<<pA<<" "<<pB<<endl;
    for(int j=0;j<pow(2,TAM_CROMOSOMA);j++){
            if(strcmp(pA,dec[j].cromosoma)==0)
                seleccion[i].cromosoma=j;
            if(strcmp(pB,dec[j].cromosoma)==0)
                seleccion[i+1].cromosoma=j;
        }

}
int AG::rdtsc()
{
    __asm__ __volatile__("rdtsc");
}
