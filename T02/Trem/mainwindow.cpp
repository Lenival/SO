#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Cria vetor de caminhos
    //QVector<int> caminhosCriticos = QVector<int>(7);

    //Cria o vetor de QSemaphore
    QSemaphore *s1 = new QSemaphore(1);     // Semáforo de percurso
    QSemaphore *s2 = new QSemaphore(1);     // Semáforo de percurso
    QSemaphore *s3 = new QSemaphore(1);     // Semáforo de percurso
    QSemaphore *s4 = new QSemaphore(1);     // Semáforo de percurso
    QSemaphore *s5 = new QSemaphore(1);     // Semáforo de percurso
    QSemaphore *s6 = new QSemaphore(1);     // Semáforo de percurso
    QSemaphore *s7 = new QSemaphore(1);     // Semáforo de percurso
    QSemaphore *s134 = new QSemaphore(2);   // Semáforo de cruzamento
    QSemaphore *s457 = new QSemaphore(2);   // Semáforo de cruzamento
    QSemaphore *s256 = new QSemaphore(2);   // Semáforo de cruzamento
    QSemaphore *r1 = new QSemaphore(3);     // Semáforo de região
    QSemaphore *r2 = new QSemaphore(3);     // Semáforo de região
    QSemaphore *r3 = new QSemaphore(4);     // Semáforo de região
    //Justando semáforos às posições iniciais dos trens


    QVector<QSemaphore*> *sem = new QVector<QSemaphore*>();

    sem->insert(0,s1);
    sem->insert(1,s2);
    sem->insert(2,s3);
    sem->insert(3,s4);
    sem->insert(4,s5);
    sem->insert(5,s6);
    sem->insert(6,s7);
    sem->insert(7,s134);
    sem->insert(8,s457);
    sem->insert(9,s256);
    sem->insert(10,r1);
    sem->insert(11,r2);
    sem->insert(12,r3);


    //Cria o trem com seu (ID, posição X, posição Y)
    //trem1 = new Trem(1,60,30, m12, m41);
    //trem2 = new Trem(2,330,30, m12, m23);
    trem1 = new Trem(1,60,30, sem);
    trem2 = new Trem(2,330,30, sem);
    trem3 = new Trem(3,600,30, sem);
    trem4 = new Trem(4,190,150, sem);
    trem5 = new Trem(5,460,150, sem);

    /*
     * Conecta o sinal UPDATEGUI à função UPDATEINTERFACE.
     * Ou seja, sempre que o sinal UPDATEGUI foi chamado, será executada a função UPDATEINTERFACE.
     * Os 3 parâmetros INT do sinal serão utilizados na função.
     * Trem1 e Trem2 são os objetos que podem chamar o sinal. Se um outro objeto chamar o
     * sinal UPDATEGUI, não haverá execução da função UPDATEINTERFACE
     */
    connect(trem1,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem2,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem3,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem4,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem5,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));

    connect(trem1,SIGNAL(updateStats(int,int,QVector<QSemaphore*>*)),SLOT(updateSemStats(int,int,QVector<QSemaphore*>*)));
    connect(trem2,SIGNAL(updateStats(int,int,QVector<QSemaphore*>*)),SLOT(updateSemStats(int,int,QVector<QSemaphore*>*)));
    connect(trem3,SIGNAL(updateStats(int,int,QVector<QSemaphore*>*)),SLOT(updateSemStats(int,int,QVector<QSemaphore*>*)));
    connect(trem4,SIGNAL(updateStats(int,int,QVector<QSemaphore*>*)),SLOT(updateSemStats(int,int,QVector<QSemaphore*>*)));
    connect(trem5,SIGNAL(updateStats(int,int,QVector<QSemaphore*>*)),SLOT(updateSemStats(int,int,QVector<QSemaphore*>*)));



}

//Função que será executada quando o sinal UPDATEGUI for emitido
void MainWindow::updateInterface(int id, int x, int y){
    switch(id){
    case 1: //Atualiza a posição do objeto da tela (quadrado) que representa o trem1
        ui->label_trem1->setGeometry(x,y,21,17);
        break;
    case 2: //Atualiza a posição do objeto da tela (quadrado) que representa o trem2
        ui->label_trem2->setGeometry(x,y,21,17);
        break;
    case 3: //Atualiza a posição do objeto da tela (quadrado) que representa o trem3
        ui->label_trem3->setGeometry(x,y,21,17);
        break;
    case 4: //Atualiza a posição do objeto da tela (quadrado) que representa o trem4
        ui->label_trem4->setGeometry(x,y,21,17);
        break;
    case 5: //Atualiza a posição do objeto da tela (quadrado) que representa o trem5
        ui->label_trem5->setGeometry(x,y,21,17);
        break;
    default:
        break;
    }
    //ui->label_rec_1->setText("teste");
    //ui->label_rec_2->setText(QString::number(s2->available()));
}

void MainWindow::updateSemStats(int id, int caminhosCriticos, QVector<QSemaphore *> *semVector){
    switch (id) {
    case 1:
        ui->label_rec_1_1->setText(QString::number(semVector->at(0)->available()));
        ui->label_rec_1_2->setText(QString::number(semVector->at(1)->available()));
        ui->label_rec_1_3->setText(QString::number(semVector->at(2)->available()));
        ui->label_rec_1_4->setText(QString::number(semVector->at(3)->available()));
        ui->label_rec_1_5->setText(QString::number(semVector->at(4)->available()));
        ui->label_rec_1_6->setText(QString::number(semVector->at(5)->available()));
        ui->label_rec_1_7->setText(QString::number(semVector->at(6)->available()));
        ui->label_rec_1_8->setText(QString::number(semVector->at(7)->available()));
        ui->label_rec_1_9->setText(QString::number(semVector->at(8)->available()));
        ui->label_rec_1_10->setText(QString::number(semVector->at(9)->available()));
        ui->label_rec_1_12->setText(QString::number(semVector->at(10)->available()));
        ui->label_rec_1_13->setText(QString::number(semVector->at(11)->available()));
        ui->label_rec_1_14->setText(QString::number(semVector->at(12)->available()));
        ui->label_rec_1_11->setText(QString::number(caminhosCriticos,2));
        break;
    case 2:
        ui->label_rec_2_1->setText(QString::number(semVector->at(0)->available()));
        ui->label_rec_2_2->setText(QString::number(semVector->at(1)->available()));
        ui->label_rec_2_3->setText(QString::number(semVector->at(2)->available()));
        ui->label_rec_2_4->setText(QString::number(semVector->at(3)->available()));
        ui->label_rec_2_5->setText(QString::number(semVector->at(4)->available()));
        ui->label_rec_2_6->setText(QString::number(semVector->at(5)->available()));
        ui->label_rec_2_7->setText(QString::number(semVector->at(6)->available()));
        ui->label_rec_2_8->setText(QString::number(semVector->at(7)->available()));
        ui->label_rec_2_9->setText(QString::number(semVector->at(8)->available()));
        ui->label_rec_2_10->setText(QString::number(semVector->at(9)->available()));
        ui->label_rec_2_12->setText(QString::number(semVector->at(10)->available()));
        ui->label_rec_2_13->setText(QString::number(semVector->at(11)->available()));
        ui->label_rec_2_14->setText(QString::number(semVector->at(12)->available()));
        ui->label_rec_2_11->setText(QString::number(caminhosCriticos,2));
        break;
    case 3:
        ui->label_rec_3_1->setText(QString::number(semVector->at(0)->available()));
        ui->label_rec_3_2->setText(QString::number(semVector->at(1)->available()));
        ui->label_rec_3_3->setText(QString::number(semVector->at(2)->available()));
        ui->label_rec_3_4->setText(QString::number(semVector->at(3)->available()));
        ui->label_rec_3_5->setText(QString::number(semVector->at(4)->available()));
        ui->label_rec_3_6->setText(QString::number(semVector->at(5)->available()));
        ui->label_rec_3_7->setText(QString::number(semVector->at(6)->available()));
        ui->label_rec_3_8->setText(QString::number(semVector->at(7)->available()));
        ui->label_rec_3_9->setText(QString::number(semVector->at(8)->available()));
        ui->label_rec_3_10->setText(QString::number(semVector->at(9)->available()));
        ui->label_rec_3_12->setText(QString::number(semVector->at(10)->available()));
        ui->label_rec_3_13->setText(QString::number(semVector->at(11)->available()));
        ui->label_rec_3_14->setText(QString::number(semVector->at(12)->available()));
        ui->label_rec_3_11->setText(QString::number(caminhosCriticos,2));
        break;
    case 4:
        ui->label_rec_4_1->setText(QString::number(semVector->at(0)->available()));
        ui->label_rec_4_2->setText(QString::number(semVector->at(1)->available()));
        ui->label_rec_4_3->setText(QString::number(semVector->at(2)->available()));
        ui->label_rec_4_4->setText(QString::number(semVector->at(3)->available()));
        ui->label_rec_4_5->setText(QString::number(semVector->at(4)->available()));
        ui->label_rec_4_6->setText(QString::number(semVector->at(5)->available()));
        ui->label_rec_4_7->setText(QString::number(semVector->at(6)->available()));
        ui->label_rec_4_8->setText(QString::number(semVector->at(7)->available()));
        ui->label_rec_4_9->setText(QString::number(semVector->at(8)->available()));
        ui->label_rec_4_10->setText(QString::number(semVector->at(9)->available()));
        ui->label_rec_4_12->setText(QString::number(semVector->at(10)->available()));
        ui->label_rec_4_13->setText(QString::number(semVector->at(11)->available()));
        ui->label_rec_4_14->setText(QString::number(semVector->at(12)->available()));
        ui->label_rec_4_11->setText(QString::number(caminhosCriticos,2));
        break;
    case 5:
        ui->label_rec_5_1->setText(QString::number(semVector->at(0)->available()));
        ui->label_rec_5_2->setText(QString::number(semVector->at(1)->available()));
        ui->label_rec_5_3->setText(QString::number(semVector->at(2)->available()));
        ui->label_rec_5_4->setText(QString::number(semVector->at(3)->available()));
        ui->label_rec_5_5->setText(QString::number(semVector->at(4)->available()));
        ui->label_rec_5_6->setText(QString::number(semVector->at(5)->available()));
        ui->label_rec_5_7->setText(QString::number(semVector->at(6)->available()));
        ui->label_rec_5_8->setText(QString::number(semVector->at(7)->available()));
        ui->label_rec_5_9->setText(QString::number(semVector->at(8)->available()));
        ui->label_rec_5_10->setText(QString::number(semVector->at(9)->available()));
        ui->label_rec_5_12->setText(QString::number(semVector->at(10)->available()));
        ui->label_rec_5_13->setText(QString::number(semVector->at(11)->available()));
        ui->label_rec_5_14->setText(QString::number(semVector->at(12)->available()));
        ui->label_rec_5_11->setText(QString::number(caminhosCriticos,2));
        break;
    default:
        break;
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * Ao clicar, trens começam execução
 */
void MainWindow::on_pushButton_clicked()
{
    trem1->start();
    trem2->start();
    trem3->start();
    trem4->start();
    trem5->start();
    ui->pushButton->setDisabled(true);
    ui->pushButton_2->setEnabled(true);
}

/*
 * Ao clicar, trens param execução
 */
void MainWindow::on_pushButton_2_clicked()
{
    trem1->terminate();
    trem2->terminate();
    trem3->terminate();
    trem4->terminate();
    trem5->terminate();
    ui->pushButton_2->setDisabled(true);
    ui->pushButton->setEnabled(true);
    //while (trem1->wait()) {}
}

void MainWindow::on_verticalSlider1_valueChanged(int value)
{
    trem1->setVelocidade(value);
    ui->speed_1->setText(QString::number(value));
}

void MainWindow::on_verticalSlider2_valueChanged(int value)
{
    trem2->setVelocidade(value);
    ui->speed_2->setText(QString::number(value));
}

void MainWindow::on_verticalSlider3_valueChanged(int value)
{
    trem3->setVelocidade(value);
    ui->speed_3->setText(QString::number(value));
}

void MainWindow::on_verticalSlider4_valueChanged(int value)
{
    trem4->setVelocidade(value);
    ui->speed_4->setText(QString::number(value));
}

void MainWindow::on_verticalSlider5_valueChanged(int value)
{
    trem5->setVelocidade(value);
    ui->speed_5->setText(QString::number(value));
}
