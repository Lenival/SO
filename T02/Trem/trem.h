#ifndef TREM_H
#define TREM_H

#include <QThread>
//#include <QMutex>
#include <QSemaphore>

#define START_SPEED 199

/*
 * Classe Trem herda QThread
 * Classe Trem passa a ser uma thread.
 * A função START inicializa a thread. Após inicializada, a thread irá executar a função RUN.
 * Para parar a execução da função RUN da thread, basta executar a função TERMINATE.
 *
*/
class Trem: public QThread{
 Q_OBJECT
public:
    Trem(int,int,int);  //construtor
    Trem(int, int, int, QVector<QSemaphore *> *);  //construtor
    //Trem(int, int, int, QMutex *, QMutex *);  //construtor
    void run();         //função a ser executada pela thread
    void setVelocidade(int);         //função a ser executada pela thread


//Cria um sinal
signals:
    void updateGUI(int,int,int);
    void updateStats(int,int,QVector<QSemaphore *> *);

private:
   int x;           //posição X do trem na tela
   int y;           //posição Y do trem na tela
   int ID;          //ID do trem
   int velocidade;  //Velocidade. É o tempo de dormir em milisegundos entre a mudança de posição do trem
   int caminhosCriticos;
   QVector<QSemaphore*> *sem;
   //QMutex *m1;
   //QMutex *m2;
};

#endif // TREM_H
