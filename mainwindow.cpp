#include "mainwindow.h"
#include <vector>
#include <algorithm>

const int SUMBUT=4;//количество кнопок.
const QString TRUE_ANSWER_COLOR="background-color: rgb(251, 249, 236);";
const QString FALSE_ANSWER_COLOR="background-color: rgb(204, 192, 133);";
const QString DEFAULT_COLOR="background-color: rgb(245, 242, 221);";


void pushInMyListID(std::vector<int> &MyVec,int const &MaxInt){
    for(;;){
        if(MyVec.size()==SUMBUT){break;}
        int nextId=qrand() % MaxInt;
        if(!std::count(MyVec.begin(), MyVec.end(), nextId)){
            MyVec.push_back(nextId);
        }

    };
}

Buttom::Buttom(QPushButton *parent): QPushButton(parent){
    //font and start text
    {
    QFont font;
    font.setFamily(QStringLiteral("Courier New"));
    font.setPointSize(10);
    this->setFont(font);
    this->setText("MyClassButtom");
    }
    //color buttom
    {
    QPalette p=palette();
    QColor q1;
    q1.setRgb(65, 48, 3);
    p.setBrush(QPalette::ButtonText,q1);
    this->setPalette(p);
    }
    this->setStyleSheet(DEFAULT_COLOR);
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setSizePolicy(sizePolicy);
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QWidget *window = new QWidget;
    //Testing QMenuBar
    {
    highTopMenu=new QMenuBar;
    highTopMenu->setStyleSheet("background-color:rgb(204,192,133);");
    QMenu*   firstMenuInHighTopMenu   = new QMenu("&Файл");

    firstMenuInHighTopMenu->addAction("True Answer",
                        this,
                        SLOT(ColorTrueAncwer()),
                        Qt::CTRL + Qt::Key_Q
                       );
    firstMenuInHighTopMenu->addSeparator(); //set Sepatator


    QAction* pCheckableAction = firstMenuInHighTopMenu->addAction("AudioPlay",this,
                                                                  SLOT(AudioPlay()));
    pCheckableAction->setCheckable(true);
    pCheckableAction->setChecked(false);

    QMenu* pmnuSubMenu = new QMenu("&SubMenu", firstMenuInHighTopMenu);
    firstMenuInHighTopMenu->addMenu(pmnuSubMenu);
    pmnuSubMenu->addAction("&Test");

    highTopMenu->addMenu(firstMenuInHighTopMenu);
    this->setMenuBar(highTopMenu);

    }
    this->setCentralWidget(window);
    buttomLauout =new QHBoxLayout;
    mainLayout =new QVBoxLayout(this);
    //create buttom
    {
    buttom_1 =new Buttom;
    buttom_1->setObjectName("buttom_1");
    buttom_2 =new Buttom;
    buttom_2->setObjectName("buttom_2");
    buttom_3 =new Buttom;
    buttom_3->setObjectName("buttom_3");
    buttom_4 =new Buttom;
    buttom_4->setObjectName("buttom_4");
    buttomList=new Buttom*[4];
    buttomList[0]=buttom_1;
    buttomList[1]=buttom_2;
    buttomList[2]=buttom_3;
    buttomList[3]=buttom_4;
    }
    //label setting
    {
    label=new QLabel("start");
    label->setAlignment(Qt::AlignCenter);
    label->setCursor(QCursor(Qt::CrossCursor));
    //label font
    {
    QFont font;
    font.setFamily(QStringLiteral("Courier New"));
    font.setPointSize(10);
    label->setFont(font);
    }
    //label color
    {
    QPalette p=palette();
    QColor q1;
    q1.setRgb(65, 48, 3);
    p.setBrush(QPalette::ButtonText,q1);
    label->setPalette(p);
    }
    }
    mainLayout->addWidget(label);
    mainLayout->addLayout(buttomLauout);
    buttomLauout->addWidget(buttom_1);
    buttomLauout->addWidget(buttom_2);
    buttomLauout->addWidget(buttom_3);
    buttomLauout->addWidget(buttom_4);
    window->setLayout(mainLayout);

    this->setStyleSheet("background-color: rgb(252, 250, 235);");
    this->setWindowTitle(QApplication::translate("Widget", "1\320\241:\320\237\321\200\320\265\320\264\320\277\321\200\320\270\321\217\321\202\320\270\320\265 8.3 (8.3.8.1933)", Q_NULLPTR));

    connect(buttom_1, SIGNAL(clicked()), this, SLOT(slotButton()));
    connect(buttom_2, SIGNAL(clicked()), this, SLOT(slotButton()));
    connect(buttom_3, SIGNAL(clicked()), this, SLOT(slotButton()));
    connect(buttom_4, SIGNAL(clicked()), this, SLOT(slotButton()));


    go_next=false;
    runAudio=false;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("lingualeo.db");
    if (!db.open()){
        label->setText("Not !db.open()"+db.lastError().text());
    }
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    //инициализация каким-то числом генератора. Вообще не знаю, как эта страка работает, но она инициализирует seed уникальным числом.

}

MainWindow::~MainWindow()
{
    //if window dest =app close then label,buttom clear memory.
}

void MainWindow::slotButton(){
    QObject* obj = sender();
    Buttom *buttom=findChild<Buttom*>(obj->objectName());
    if(buttom->text()==ChooseWord[0]){
        if(runAudio){
            static QMediaPlayer *player = new QMediaPlayer;
            player->setMedia(QUrl::fromLocalFile(QDir::toNativeSeparators("content\\"+ChooseWord[0]+".mp3")));
            player->play();

        }


        if (!go_next){
                    buttom->setStyleSheet(TRUE_ANSWER_COLOR);
                    go_next=true;
        }
        else{
                    go_next=false;
                    nextRound();
            }
    }
    else{
        buttom->setStyleSheet(FALSE_ANSWER_COLOR);
    }
}

bool MainWindow::nextRound(){
    buttom_1->setStyleSheet(DEFAULT_COLOR);
    buttom_2->setStyleSheet(DEFAULT_COLOR);
    buttom_3->setStyleSheet(DEFAULT_COLOR);
    buttom_4->setStyleSheet(DEFAULT_COLOR);

    int MAXROWDB=0;
    try{
        query=db.exec( QString( "SELECT MAX(id) from MainTable" ) );
        query.first();

    }
    catch(...){
       label->setText("Наверное не тот бд");
       return false;
    }
    MAXROWDB=query.value(0).toInt();
    if (MAXROWDB==0){
    label->setText("В бд нет строк, похоже она пустая.");
    return false;
    }
    std::vector<int> ListIntId;
    pushInMyListID(ListIntId,MAXROWDB);
    QString World[4][4]; //ru,eng,audio, image;
    int tryWorld=qrand() % SUMBUT;
    for(int i=0;i!=SUMBUT;i++){
        query=db.exec( QString( "SELECT eng, ru,audio,image FROM MainTable where id=?;" ) );
        query.addBindValue(ListIntId[i]);
        query.exec();
        query.first();
        World[i][0]=query.value(0).toString();
        World[i][1]=query.value(1).toString();
        World[i][2]=query.value(2).toString();
        World[i][3]=query.value(3).toString();
        if(i==tryWorld){
            ChooseWord[0]=query.value(0).toString();
            ChooseWord[1]=query.value(1).toString();
           }
       }
    label->setText(ChooseWord[1]);
    buttom_1->setText(World[0][0]);
    buttom_2->setText(World[1][0]);
    buttom_3->setText(World[2][0]);
    buttom_4->setText(World[3][0]);

}

void MainWindow::ColorTrueAncwer(){
   for(int i=0;i!=SUMBUT;i++){
       if(buttomList[i]->text()==ChooseWord[0]){
           buttomList[i]->setStyleSheet(TRUE_ANSWER_COLOR+"color:red;");
       }
       else{
           buttomList[i]->setStyleSheet(FALSE_ANSWER_COLOR);
       }
   };
}

void MainWindow::AudioPlay(){
    runAudio=!runAudio;
}
