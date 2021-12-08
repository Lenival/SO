#include "trem.h"
#include <QtCore>

#define E_CAMINHO(c) (int)(c<7)
#define TREM_ESTEVE_NO(p) (caminhosCriticos & (1<<p))
#define TREM_INICIOU(p) (caminhosCriticos |= (1<<p))
#define TREM_LIBEROU(p) (caminhosCriticos &= ~(1<<p))
#define TREM_APONTA(c) sem->at(c)->acquire(1)
#define TREM_APONTA_INICIA(c) sem->at(c)->acquire(2)
#define TREM_INICIA(c) TREM_APONTA(c)
//#define TREM_LIBERA(c) sem->at(c)->release(1+E_CAMINHO(c))
#define TREM_LIBERA(c) sem->at(c)->release(1)
#define CAMINHO_1 0
#define CAMINHO_2 1
#define CAMINHO_3 2
#define CAMINHO_4 3
#define CAMINHO_5 4
#define CAMINHO_6 5
#define CAMINHO_7 6
#define CRUZAMENTO_134 7
#define CRUZAMENTO_457 8
#define CRUZAMENTO_256 9

//Construtor
Trem::Trem(int ID, int x, int y){
    this->ID = ID;
    this->x = x;
    this->y = y;
    velocidade = START_SPEED;
}
Trem::Trem(int ID, int x, int y, QVector<QSemaphore*> *sem){
    this->ID = ID;
    this->x = x;
    this->y = y;
    velocidade = START_SPEED;
    this->sem = sem;
    this->caminhosCriticos = 0;
    switch (ID) {
    case 2:
        //TREM_APONTA_INICIA(CAMINHO_1);
        TREM_INICIA(CAMINHO_1);
        TREM_INICIOU(CAMINHO_1);
        break;
    case 3:
        //TREM_APONTA_INICIA(CAMINHO_2);
        TREM_INICIA(CAMINHO_2);
        TREM_INICIOU(CAMINHO_2);
        break;
    case 4:
        //TREM_APONTA(CAMINHO_3);
        TREM_APONTA(CRUZAMENTO_134);
        TREM_APONTA(CRUZAMENTO_457);
        TREM_INICIA(CAMINHO_3);
        //TREM_APONTA_INICIA(CAMINHO_3);
        TREM_INICIOU(CAMINHO_3);
        //TREM_INICIOU(CRUZAMENTO_134);
        //TREM_APONTA(CAMINHO_4);
        break;
    case 5:
        TREM_APONTA(CRUZAMENTO_457);
        TREM_APONTA(CRUZAMENTO_256);
        TREM_INICIOU(CRUZAMENTO_457);
        //TREM_APONTA(CAMINHO_5);
        //TREM_APONTA(CRUZAMENTO_256);
        //TREM_APONTA_INICIA(CAMINHO_5);
        TREM_INICIA(CAMINHO_5);
        TREM_INICIOU(CAMINHO_5);
        //TREM_APONTA(CAMINHO_6);
        break;
    default:
        break;
    }

}

//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        if(velocidade) // Se o trem está parado, não precisa executar isso aqui
            switch(ID){
            case 1:     //Trem 1
                this->sem->at(10)->acquire(1); // Tentativa de pausa mais estável
                if (y == 30 && x <330){
                    x+=10;
                    if(x==320){
                        this->
                        //sem->at(0)->acquire(2);
                        TREM_APONTA(CRUZAMENTO_134);
                        //TREM_APONTA_INICIA(CAMINHO_1);
                        TREM_INICIA(CAMINHO_1);
                        TREM_INICIOU(CAMINHO_1);
                        //TREM_APONTA(CAMINHO_3);
                        //printf("Chegou aqui com x== %d e %d recursos disponíveis!\n",x,sem->at(2)->available());
                    }
                }
                else if (x == 330 && y < 150){
                    y+=10;
                    if(y==140){
                        TREM_INICIA(CAMINHO_3);
                        TREM_INICIOU(CAMINHO_3);
                    }
                    if(y==150){
                        TREM_INICIOU(CRUZAMENTO_134);
                    }
                }
                else{ if (x > 60 && y == 150){
                        if(x==320 && TREM_ESTEVE_NO(CRUZAMENTO_134)){
                            TREM_LIBERA(CRUZAMENTO_134);
                            TREM_LIBEROU(CRUZAMENTO_134);
                        }
                        if(x==310 && TREM_ESTEVE_NO(CAMINHO_1)){
                            //sem->at(0)->release(2);
                            TREM_LIBERA(CAMINHO_1);
                            TREM_LIBEROU(CAMINHO_1);
                        }
                        x-=10;
                        if(x==180){
                            TREM_LIBERA(CAMINHO_3);
                            TREM_LIBEROU(CAMINHO_3);
                        }
                    }
                    else
                        y-=10;
                }
                if(velocidade)
                    emit updateGUI(ID, x,y);    //Emite um sinal
                emit updateStats(this->ID, this->caminhosCriticos, this->sem);
                this->sem->at(10)->release(1);// Tentativa de pausa mais estável
                break;
            case 2: //Trem 2
                this->sem->at(10)->acquire(1); // Tentativa de pausa mais estável
                if (y == 30 && x <600){
                    x+=10;
                    if(x==590){
                        //TREM_APONTA(CAMINHO_2);
                        TREM_APONTA(CRUZAMENTO_256);
                        TREM_APONTA(CRUZAMENTO_457);
                        //TREM_APONTA(CRUZAMENTO_134);
                        //TREM_APONTA_INICIA(CAMINHO_2);
                        TREM_INICIA(CAMINHO_2);
                        TREM_INICIOU(CAMINHO_2);
                        //TREM_APONTA(CAMINHO_5);
                    }
                    if(x==340 && TREM_ESTEVE_NO(CAMINHO_1)){
                        TREM_LIBERA(CAMINHO_1);
                        TREM_LIBEROU(CAMINHO_1);
                    }
                }
                else if (x == 600 && y < 150){
                    y+=10;
                    if(y==140){
                        // Avaliar os cruzamentos
                        TREM_INICIA(CAMINHO_5);
                        TREM_INICIOU(CRUZAMENTO_256);
                        TREM_INICIOU(CAMINHO_5);
                        //TREM_APONTA(CRUZAMENTO_457);
                        //TREM_APONTA(CAMINHO_4);
                    }
                }
                else {if (x > 330 && y == 150){
                        x-=10;
                        if(x==590 && TREM_ESTEVE_NO(CRUZAMENTO_256)){
                            TREM_LIBERA(CRUZAMENTO_256);
                            TREM_LIBEROU(CRUZAMENTO_256);
                        }
                        if(x==590 && TREM_ESTEVE_NO(CAMINHO_2)){
                            TREM_LIBERA(CAMINHO_2);
                            TREM_LIBEROU(CAMINHO_2);
                        }
                        if(x==470){
                            TREM_APONTA(CRUZAMENTO_134);
                            TREM_INICIA(CAMINHO_4);
                            TREM_INICIOU(CAMINHO_4);
                            TREM_INICIOU(CRUZAMENTO_457);
                        }
                        if(x==460 && TREM_ESTEVE_NO(CAMINHO_5)){
                            //TREM_APONTA(CAMINHO_1);
                            TREM_LIBERA(CAMINHO_5);
                            TREM_LIBEROU(CAMINHO_5);
                            //printf("Chegou aqui com x== %d e %d recursos disponíveis!\n",x,sem->at(0)->available());
                        }
                        if(x==450 && TREM_ESTEVE_NO(CRUZAMENTO_457)){
                            TREM_LIBERA(CRUZAMENTO_457);
                            TREM_LIBEROU(CRUZAMENTO_457);
                        }
                        if(x==340){
                            TREM_INICIOU(CRUZAMENTO_134);
                            TREM_INICIA(CAMINHO_1);
                            TREM_INICIOU(CAMINHO_1);
                        }
                        if(x==330 && TREM_ESTEVE_NO(CAMINHO_4)){
                            TREM_LIBERA(CAMINHO_4);
                            TREM_LIBEROU(CAMINHO_4);
                        }
                    }
                    else{
                        if(y==140 && TREM_ESTEVE_NO(CRUZAMENTO_134)){
                            TREM_LIBERA(CRUZAMENTO_134);
                            TREM_LIBEROU(CRUZAMENTO_134);
                        }
                        y-=10;
                    }}
                if(velocidade)
                    emit updateGUI(ID, x,y);    //Emite um sinal
                emit updateStats(this->ID, this->caminhosCriticos, this->sem);
                this->sem->at(10)->release(1);// Tentativa de pausa mais estável
                break;
            case 3: //Trem 3
                this->sem->at(10)->acquire(1); // Tentativa de pausa mais estável
                if (x <870 && y == 30){
                    x+=10;
                    if(x==610 && TREM_ESTEVE_NO(CAMINHO_2)){
                        TREM_LIBERA(CAMINHO_2);
                        TREM_LIBEROU(CAMINHO_2);
                    }
                }
                else if (x == 870 && y < 150)
                    y+=10;
                else if (x > 600 && y == 150){
                    x-=10;
                    if(x == 740){
                        //TREM_APONTA(CAMINHO_6);
                        TREM_APONTA(CRUZAMENTO_256);
                        //TREM_APONTA_INICIA(CAMINHO_6);
                        TREM_INICIA(CAMINHO_6);
                        TREM_INICIOU(CAMINHO_6);
                        //TREM_APONTA(CAMINHO_2);
                    }
                    if(x == 610){
                        TREM_INICIA(CAMINHO_2);
                        TREM_INICIOU(CAMINHO_2);
                        TREM_INICIOU(CRUZAMENTO_256);
                    }
                }
                else{
                    y-=10;
                    if(y == 140 && TREM_ESTEVE_NO(CRUZAMENTO_256)){
                        TREM_LIBERA(CRUZAMENTO_256);
                        TREM_LIBEROU(CRUZAMENTO_256);
                    }
                    if(y == 140 && TREM_ESTEVE_NO(CAMINHO_6)){
                        TREM_LIBERA(CAMINHO_6);
                        TREM_LIBEROU(CAMINHO_6);
                    }
                }
                if(velocidade)
                    emit updateGUI(ID, x,y);    //Emite um sinal
                emit updateStats(this->ID, this->caminhosCriticos, this->sem);
                this->sem->at(10)->release(1);// Tentativa de pausa mais estável
                break;
            case 4: //Trem 4
                this->sem->at(10)->acquire(1); // Tentativa de pausa mais estável
                if (x < 460 && y == 150){
                    x+=10;
                    /*if(x==190 && !(caminhosCriticos)){ //Posição inicial
                    TREM_APONTA(CAMINHO_3);
                    TREM_INICIA(CAMINHO_3);
                    TREM_INICIOU(CAMINHO_3);
                    TREM_APONTA(CAMINHO_4);
                    printf("Chegou aqui com x== %d e %d recursos disponíveis!\n",x,sem->at(2)->available());
                }*/
                    if(x==320){
                        //TREM_APONTA(CRUZAMENTO_457);
                        TREM_INICIA(CAMINHO_4);
                        TREM_INICIOU(CAMINHO_4);
                        TREM_INICIOU(CRUZAMENTO_134);
                    }
                    if(x==330 && TREM_ESTEVE_NO(CAMINHO_3)){
                        TREM_LIBERA(CAMINHO_3);
                        TREM_LIBEROU(CAMINHO_3);
                        //TREM_APONTA(CAMINHO_7);
                    }
                    if(x==330){
                        //TREM_LIBERA(CAMINHO_3);
                        //TREM_LIBEROU(CAMINHO_3);
                        //TREM_APONTA(CAMINHO_7);
                    }
                    if(x==340 && TREM_ESTEVE_NO(CRUZAMENTO_134)){
                        TREM_LIBERA(CRUZAMENTO_134);
                        TREM_LIBEROU(CRUZAMENTO_134);
                    }
                    if(x==450){
                        TREM_INICIOU(CRUZAMENTO_457);
                        TREM_INICIA(CAMINHO_7);
                        TREM_INICIOU(CAMINHO_7);
                    }
                }
                else if (x == 460 && y < 270){
                    y+=10;
                    if(y==160 && TREM_ESTEVE_NO(CRUZAMENTO_457)){
                        TREM_LIBERA(CRUZAMENTO_457);
                        TREM_LIBEROU(CRUZAMENTO_457);
                    }
                    if(y==160 && TREM_ESTEVE_NO(CAMINHO_4)){
                        TREM_LIBERA(CAMINHO_4);
                        TREM_LIBEROU(CAMINHO_4);
                    }
                }
                else if (x > 190 && y == 270){
                    x-=10;
                    if(x==440 && TREM_ESTEVE_NO(CAMINHO_7)){
                        TREM_LIBERA(CAMINHO_7);
                        TREM_LIBEROU(CAMINHO_7);
                    }

                }
                else{
                    y-=10;
                    if(y==160){
                        TREM_APONTA(CRUZAMENTO_134);
                        TREM_APONTA(CRUZAMENTO_457);
                        //TREM_APONTA_INICIA(CAMINHO_3);
                        TREM_INICIA(CAMINHO_3);
                        TREM_INICIOU(CAMINHO_3);
                        //TREM_APONTA(CAMINHO_4);
                        //printf("Chegou aqui com x== %d e %d recursos disponíveis!\n",x,sem->at(2)->available());
                    }
                }
                if(velocidade)
                    emit updateGUI(ID, x,y);    //Emite um sinal
                emit updateStats(this->ID, this->caminhosCriticos, this->sem);
                this->sem->at(10)->release(1);// Tentativa de pausa mais estável
                break;
            case 5: //Trem 5
                this->sem->at(10)->acquire(1); // Tentativa de pausa mais estável
                if (x <730 && y == 150){
                    x+=10;
                    if(x==470 && TREM_ESTEVE_NO(CRUZAMENTO_457)){
                        TREM_LIBERA(CRUZAMENTO_457);
                        TREM_LIBEROU(CRUZAMENTO_457);
                    }
                    if(x == 480 && TREM_ESTEVE_NO(CAMINHO_7)){
                        TREM_LIBERA(CAMINHO_7);
                        TREM_LIBEROU(CAMINHO_7);
                    }
                    if(x == 590){
                        TREM_INICIA(CAMINHO_6);
                        TREM_INICIOU(CAMINHO_6);
                        TREM_INICIOU(CRUZAMENTO_256);
                    }
                    if(x == 610 && TREM_ESTEVE_NO(CRUZAMENTO_256)){
                        TREM_LIBERA(CRUZAMENTO_256);
                        TREM_LIBEROU(CRUZAMENTO_256);
                    }
                    if(x == 620 && TREM_ESTEVE_NO(CAMINHO_5)){
                        TREM_LIBERA(CAMINHO_5);
                        TREM_LIBEROU(CAMINHO_5);
                    }
                }
                else if (x == 730 && y < 270){
                    y+=10;
                    if(y == 170 && TREM_ESTEVE_NO(CAMINHO_6)){
                        TREM_LIBERA(CAMINHO_6);
                        TREM_LIBEROU(CAMINHO_6);
                    }
                }
                else if (x > 460 && y == 270){
                    x-=10;
                    if(x == 470){
                        TREM_APONTA(CRUZAMENTO_457);
                        TREM_APONTA(CRUZAMENTO_256);
                        //TREM_APONTA_INICIA(CAMINHO_7);
                        TREM_INICIA(CAMINHO_7);
                        TREM_INICIOU(CAMINHO_7);
                        //TREM_APONTA(CAMINHO_5);
                    }
                }
                else{
                    y-=10;
                    //printf("Chegou aqui com x: %d, y: %d e %d recursos disponíveis!\n",x,y,sem->at(4)->available());
                    if(y == 160){
                        //TREM_APONTA(CRUZAMENTO_256);
                        TREM_INICIA(CAMINHO_5);
                        TREM_INICIOU(CAMINHO_5);
                        TREM_INICIOU(CRUZAMENTO_457);
                        //TREM_APONTA(CAMINHO_6);
                    }
                }
                if(velocidade)
                    emit updateGUI(ID, x,y);    //Emite um sinal
                emit updateStats(this->ID, this->caminhosCriticos, this->sem);
                this->sem->at(10)->release(1);// Tentativa de pausa mais estável
                break;
            default:
                break;
            }
        msleep(MAX_SPEED - velocidade);
    }
}

void Trem::setVelocidade(int value){
    this->velocidade = value;
}



