#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

static const char blankString[] = QT_TRANSLATE_NOOP("SettingsDialog", "N/A");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //обновляем переменную
    stm32_port = new QSerialPort;
    terminal=new QTerminal(ui->terminal);

    terminal->setGeometry(0,0,581,111);
    terminal->CommandList.clear();
    terminal->currentCommand=0;
    terminal->currentPosition=0;

    //обновляем список портов
    on_refreshButton_clicked();

    //выводим информацию о первом порте
    showPortInfo(0);

    //связываем выбор порта из списка с выводом информации о нем
    connect(ui->portListBox,QOverload<int>::of(&QComboBox::currentIndexChanged),this,&MainWindow::showPortInfo);

    //связываем выбор графика с его отрисовкой
    connect(ui->dataListBox,QOverload<int>::of(&QComboBox::currentIndexChanged),this,&MainWindow::showGraph);

    //связываем выбор скетча с его выводом
    connect(ui->sketchesListBox,QOverload<int>::of(&QComboBox::currentIndexChanged),this,&MainWindow::showSketch);

    //заполняем лист скоростей передачи
    ui->baudRateListBox->addItem(QStringLiteral("1200"), QSerialPort::Baud1200);
    ui->baudRateListBox->addItem(QStringLiteral("2400"), QSerialPort::Baud2400);
    ui->baudRateListBox->addItem(QStringLiteral("4800"), QSerialPort::Baud4800);
    ui->baudRateListBox->addItem(QStringLiteral("9600"), QSerialPort::Baud9600);
    ui->baudRateListBox->addItem(QStringLiteral("19200"), QSerialPort::Baud19200);
    ui->baudRateListBox->addItem(QStringLiteral("38400"), QSerialPort::Baud38400);
    ui->baudRateListBox->addItem(QStringLiteral("115200"), QSerialPort::Baud115200);
    ui->baudRateListBox->addItem(QStringLiteral("256000"), 256000);

    //меню пустого графика
    ui->dataListBox->addItem("<empty>");

    //меню нового скетча
    ui->sketchesListBox->addItem("<new sketch>");

    sketches_paths.append("u"); //добавляем пустой путь

    QString temp="\0";
    QStringList temp0;
    temp0.append(temp);
    sketches.append(temp0);


    //настройка графиков
    ui->graph->addGraph();
    ui->graph->graph(0)->setPen(QPen(Qt::black));
    ui->graph->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->graph->graph(0)->setScatterStyle(QCPScatterStyle::ssDisc);
    ui->graph->xAxis->setTickLabelType(QCPAxis::ltNumber);
    ui->graph->xAxis->setNumberFormat("g");
    ui->graph->xAxis->setAutoTickStep(false);
    ui->graph->yAxis->setAutoTickStep(false);

    ui->graph->xAxis->setLabel("Sample");
    ui->graph->yAxis->setLabel("ADC Code");
    ui->graph->yAxis->setNumberFormat("g");


    ui->graph->xAxis->setRange(ui->X_min->value(),ui->X_max->value());
    ui->graph->yAxis->setRange(ui->Y_min->value(),ui->Y_max->value());

    ui->graph->xAxis->setTickStep(ui->X_step->value());
    ui->graph->yAxis->setTickStep(ui->Y_step->value());


    //связываем сигнал отправки в терминал с отправкой команды в порт
    connect(terminal,SIGNAL(messageSended()),this,SLOT(sendCommandFromTerminal()));

    //связываем наличие данных в буфере с обработчиком
    connect(stm32_port, &QSerialPort::readyRead, this, &MainWindow::receiveData);

    //связываем таймер с получением данных
    connect(&timer,SIGNAL(timeout()),SLOT(onTimer()));

    connect(ui->codeEdit,SIGNAL(textChanged()),SLOT(autosaving()));

    //связываем таймер сборки со своим слотом
    //connect(&T,SIGNAL(timeout()),SLOT(builder()));

    //по умолчанию используется папка расположения проекта
    dataPath=QDir::currentPath();
    ui->dirData->setText(dataPath);

    ui->menuWidget->setCurrentIndex(0);
    ui->graph->setVisible(false);
    ui->codeEdit->setVisible(true);
    ui->terminal->setVisible(true);
    //connect(ui->sketchesListBox,QOverload<int>::of(&QComboBox::currentIndexChanged),this,&MainWindow::showSketch);
    connect(ui->menuWidget,SIGNAL(currentChanged(int)),SLOT(drawing()));
}

MainWindow::~MainWindow()
{
    if(stm32_port->isOpen())
        stm32_port->close();
    delete stm32_port;
    delete ui;
}

//обновление информации о COM портах
void MainWindow::on_refreshButton_clicked()
{
    ui->portListBox->clear();
    QString description;
    QString manufacter;
    QString serialNumber;
    const auto infos=QSerialPortInfo::availablePorts();
    for(const QSerialPortInfo &info : infos)
    {
        description=info.description();
        manufacter=info.manufacturer();
        serialNumber=info.serialNumber();
        QStringList portList;
        portList << info.portName()
                 << (!description.isEmpty() ? description : blankString)
                 << (!manufacter.isEmpty() ? manufacter : blankString)
                 << (!serialNumber.isEmpty() ? serialNumber : blankString)
                 << info.systemLocation()
                 << (info.hasVendorIdentifier() ? QString::number(info.vendorIdentifier()) : blankString)
                 << (info.hasProductIdentifier() ? QString::number(info.productIdentifier()) : blankString);
        ui->portListBox->addItem(portList.first(),portList);
    }
}
//подключение и отключение микроконтроллера
void MainWindow::on_connectButton_clicked()
{
    if(stm32_port->isOpen())//отключение
    {
        stm32_port->close();      //закрываем порт
        //задаем изображение на кнопке
        QPixmap p(":/disconnect.png");
        QIcon icon(p);
        ui->connectButton->setIcon(icon);
        ui->connectButton->setIconSize(QSize(24,24));
        //выдаем статус
        QPixmap pict(":/no.png");
        ui->status->setPixmap(pict);

    }
    else
    {
        //подключаемся
        stm32_port->setPortName(ui->portListBox->currentText());
        stm32_port->open(QSerialPort::ReadWrite);
        stm32_port->setBaudRate(ui->baudRateListBox->itemData(ui->baudRateListBox->currentIndex()).toInt());
        stm32_port->setDataBits(QSerialPort::Data8);
        stm32_port->setParity(QSerialPort::NoParity);
        stm32_port->setStopBits(QSerialPort::OneStop);
        stm32_port->setFlowControl(QSerialPort::NoFlowControl);

        //обновляем изображения (аналогично)
        QPixmap p(":/connect.png");
        QIcon icon(p);
        ui->connectButton->setIcon(icon);
        ui->connectButton->setIconSize(QSize(24,24));
        QPixmap pict(":/ok.png");
        ui->status->setPixmap(pict);

    }
}
//выводим информацию о выбранном порте
void MainWindow::showPortInfo(int index)
{
    if(index==-1)
        return;
    const QStringList list = ui->portListBox->itemData(index).toStringList();
    ui->description->setText(list.count() > 1 ? "Description: "+list.at(1) : "Description: "+tr(blankString));
    ui->manufacturer->setText(list.count() > 2 ? "Manufacturer: "+list.at(2) : "Manufacturer: "+tr(blankString));
    ui->SN->setText(list.count() > 3 ? "Serial Number: "+list.at(3) :"Serial Number: "+ tr(blankString));
    ui->portName->setText("Port Name: "+ui->portListBox->currentText());
    ui->VID->setText(list.count() > 5 ? "VID: "+list.at(5) :"VID: "+ tr(blankString));
    ui->PID->setText(list.count() > 6 ? "PID: "+list.at(6) :"PID: "+ tr(blankString));
}

void MainWindow::sendCommandFromTerminal()
{
    int error=0; //код ошибки
    //загружаем последнюю отправленную команду
    QStringList data=terminal->CommandList;
    QString command=data.at(data.length()-1);

    QStringList commandContain=command.split(" ");//отделяем составляющие команды
    //разбираем команду на составляющие
    QString com=commandContain.first();
    QString arg=commandContain.last();


    if(com=="meas")//найдено ключевое слово meas, команда вида meas 10000
    {
        if(commandContain.length()==2)
        {
startlabel:
            if(!arg.isEmpty())//аргумент не пустой, пробел стоит, и число есть
            {
                int N=arg.toInt(); //проверяем число
                if(N>0)//неотрицательное число
                {
                    QString message="start "+arg+"\r\n"; //собираем команду
                    if(stm32_port->isWritable())//пишем в порт
                    {
                        isMeas=true;
                        isBuilding=false;
                        stm32_port->write(message.toStdString().c_str());
                        timer.start(2000); //ожидаем данные 2 секунды
                    }
                    else
                        error=998;
                }
                else
                    error=5;
            }
            else
                error=4;
        }
        else
            error=6;
        //все отправлено, выходим из подфункции, отдаем на обработку код ошибки
        errorHandler(error);
        return;
    }


//    if((com=="set")||(com=="reset"))
//    {
//        // тут проверка грин-блю
//        if(commandContain.length()==2)
//        {
//            if  (    (arg=="blue") || (arg=="green")     )
//            {
//                command+="\r\n";
//                if(stm32_port->isWritable())
//                {
//                    stm32_port->write(command.toStdString().c_str());
//                }
//                else
//                    error=998;
//            }
//            else
//                error=5;
//        }
//        else
//            error=6;
//        errorHandler(error);
//        return;
//    }

    if(com=="sudo")
    {
        if(commandContain[1]=="start")
        {
            goto startlabel;
        }
        else
        {
            QString message=command.mid(5)+"\r\n"; //собираем команду
            if(stm32_port->isWritable())//пишем в порт
                stm32_port->write(message.toStdString().c_str());
        }
        errorHandler(error);
        return;
    }

    if((com=="clear"))//найдено ключевое слово clear
    {
            terminal->clear();
            terminal->output("Screen was cleared, command history list is not empty!");
            return;
    }
    if((com=="help"))//найдено ключевое слово help
    {
            //выводим список команд
            terminal->output("help: get command list");
            terminal->output("meas N: start measuring, N - number of points");
            terminal->output("setup ch1,ch2,m: choose channels and mode, ch1 - channel 1, ch2 - channel 2, m - mode");
            terminal->output("clear - clear screen");
            return;

    }
    if(com=="setup")//найдено ключевое слово setup, команда вида setup 1,1,0
    {
        if(commandContain.length()==2)
        {
            QStringList arguments=arg.split(",");
            //проверяем аргументы
            if(arguments.length()==3)
            {
                bool isOK=true;//индикатор неверного аргумента

                //аргументы
                int ch1=arguments[0].toInt();
                int ch2=arguments[1].toInt();
                int mode=arguments[2].toInt();

                //правильность аргументов
                bool cond1=(ch1==1)||(ch1==2)||(ch1==3)||(ch1==4)||(ch1==5)||(ch1==6)||(ch1==7)||(ch1==8);
                bool cond2=(ch2==1)||(ch2==2)||(ch2==3)||(ch2==4)||(ch2==5)||(ch2==6)||(ch2==7)||(ch1==8);
                bool cond3=(mode==0)||(mode==1);
                if(!cond1)
                {
                    error=1;
                    isOK=false;
                }
                if(!cond2)
                {
                    error=2;
                    isOK=false;
                }
                if(!cond3)
                {
                    error=3;
                    isOK=false;
                }

                //отправка, если все ок
                if(isOK)
                {
                    QString message="setup "+QString::number(ch1)+QString::number(ch2)+QString::number(mode)+"\r\n";
                    if(stm32_port->isWritable())
                    {
                        stm32_port->write(message.toStdString().c_str());
                    }
                    else
                        error=998;
                }

            }
            else
                error=5;
        }
        else
            error=5;
        errorHandler(error);
        return;
    }

    //ни одна команда не была распознана
    error=999;
    errorHandler(error);

}

void MainWindow::receiveData()
{
    buff.append(stm32_port->readAll());
}

//обработчик ошибок
void MainWindow::errorHandler(int code)
{
    switch (code) {

        case 0:
            terminal->output("Command was sended");
            break;
        case 1:
            terminal->output("Channel 1 was given uncorrectly!");
            break;
        case 2:
            terminal->output("Channel 2 was given uncorrectly!");
            break;
        case 3:
            terminal->output("Mode was given uncorrectly!");
            break;
        case 4:
            terminal->output("Number of points has uncorrect format!");
            break;
        case 5:
            terminal->output("Invalid argument!");
            break;
        case 6:
            terminal->output("Invalid command format! Please check, it's can be SPACE in end of string");
            break;
        case 999:
            terminal->output("Unknown command!");
            break;
        case 998:
            terminal->output("Port is closed!");
            break;
        case 997:
            terminal->output("Sketch is empty!");
            break;
    }
}

//изменение масштаба графика
void MainWindow::on_X_min_valueChanged(int arg1)
{
    ui->graph->xAxis->setRange(arg1,ui->X_max->value());
    ui->graph->yAxis->setRange(ui->Y_min->value(),ui->Y_max->value());
    ui->graph->replot();
}

void MainWindow::on_X_max_valueChanged(int arg1)
{
    ui->graph->xAxis->setRange(ui->X_min->value(),arg1);
    ui->graph->yAxis->setRange(ui->Y_min->value(),ui->Y_max->value());
    ui->graph->replot();
}

void MainWindow::on_Y_min_valueChanged(int arg1)
{
    ui->graph->xAxis->setRange(ui->X_min->value(),ui->X_max->value());
    ui->graph->yAxis->setRange(arg1,ui->Y_max->value());
    ui->graph->replot();
}

void MainWindow::on_Y_max_valueChanged(int arg1)
{
    ui->graph->xAxis->setRange(ui->X_min->value(),ui->X_max->value());
    ui->graph->yAxis->setRange(ui->Y_min->value(),arg1);
    ui->graph->replot();
}

void MainWindow::on_X_step_valueChanged(int arg1)
{
    ui->graph->xAxis->setTickStep(arg1);
    ui->graph->replot();
}

void MainWindow::on_Y_step_valueChanged(int arg1)
{
    ui->graph->yAxis->setTickStep(arg1);
    ui->graph->replot();
}

void MainWindow::onTimer()
{
    qDebug()<<"Timer is starting!";
    timer.stop(); //останавливаем таймер
    QString dat = QString::fromLocal8Bit(buff); //переводим данные в строку
    points = dat.split("\r\n");//разбиваем построчно
    points.removeLast();//удаляем end в конце
    //добавляем данные в общий массив
    qDebug()<<points.length();

    if(!points.isEmpty()&&(isMeas))
    {
        data.append(points);
        saveGraph(points);
        drawGraph(points);
        ui->dataListBox->setCurrentIndex(paths.length());
    }
    buff.clear();
    if(isBuilding)
        builder();
}


void MainWindow::on_chooseDataDir_clicked()
{
    QString dataPath_back;
    dataPath_back=QFileDialog::getExistingDirectory(this,"Select folder",dataPath);
    if(!dataPath_back.isEmpty())
    {
        dataPath=dataPath_back;
        ui->dirData->setText(dataPath);
    }
}

//сохранение графика, выбранного
void MainWindow::saveGraph(QStringList d)
{
    //имя файла состоит из даты-времени, собираем
    QString date=QDateTime::currentDateTime().toString("dd.MM.yyyy");
    QString hour=QDateTime::currentDateTime().toString("hh");
    QString minute=QDateTime::currentDateTime().toString("mm");
    QString sec=QDateTime::currentDateTime().toString("ss");

    QString name=date+"_"+hour+minute+sec+".ini";


    //полный путь
    dataPath=ui->dirData->text();
    if(dataPath.isEmpty())
        dataPath=QDir::currentPath();
    ui->dirData->setText(dataPath);



    QString path=dataPath+"/"+name;
    //далее сохраняем
    char* p=path.toLatin1().data();
    FILE* f=fopen(p,"w");
    for(int i=0;i<d.length();i++)
    {
        QString dat=d[i];
        dat+="\r\n";
        char str[256];
        std::string s=dat.toStdString();
        for(int j=0;j<dat.length();j++)
                str[j]=s[j];
        fwrite(str,sizeof(char),dat.length(),f);
    }
    fclose(f);
    //добавляем в массив путей до данных
    paths.append(path);
    //добавляем в список графиков
    ui->dataListBox->addItem(path);
}

//отрисовка графика
void MainWindow::drawGraph(QStringList d)
{
    ui->graph->graph(0)->clearData();

    //int max=0;//поиск максимального отсчета
    for(int i=0;i<d.length();i++)
    {
        int sample=d[i].toInt();
//        if(sample>max)
//            max=sample;
        ui->graph->graph(0)->addData(i,sample);
    }

    ui->X_min->setValue(0);
    ui->Y_min->setValue(0);
    ui->X_max->setValue(d.length());
    ui->Y_max->setValue(4500);

    ui->graph->xAxis->setRange(0,d.length());
    ui->graph->yAxis->setRange(0,4500);
    ui->graph->xAxis->setAutoTickStep(true);
    ui->graph->replot();


}

//отображение выбранного в listbox графика
void MainWindow::showGraph()
{
    if(data.isEmpty())
    {
        return;
    }
    int index=ui->dataListBox->currentIndex();
    if(index==0)
    {
        ui->graph->graph(0)->clearData();
        ui->graph->replot();
        return;
    }
    QStringList dat=data[index-1];
    drawGraph(dat);
}

void MainWindow::showSketch()
{
    qDebug()<<"YE";
    if(sketches.isEmpty())
        return;
    qDebug()<<"NO";
    QString code=ui->codeEdit->toPlainText();
    QStringList s=code.split("\n");
    sketches[lastIndex]=s;

    qDebug()<<"last="<<lastIndex;
    qDebug()<<"s="<<sketches[lastIndex];

    int index=ui->sketchesListBox->currentIndex();
    qDebug()<<"index="<<index;
    if(index==-1)
        return;
    if(sketches.isEmpty())
        return;
    QStringList sk=sketches[index];
    ui->codeEdit->clear();

    for(int i=0;i<sk.length();i++)
        ui->codeEdit->append(sk[i]);
    lastIndex=ui->sketchesListBox->currentIndex();
}

void MainWindow::drawing()
{
    int index=ui->menuWidget->currentIndex();
    if(index==2)
    {
        ui->graph->setVisible(true);
        ui->codeEdit->setVisible(false);
    }
    else
    {
        ui->graph->setVisible(false);
        ui->codeEdit->setVisible(true);
    }
}

//открываем график из файла
void MainWindow::on_openGraph_clicked()
{
    QString path=QFileDialog::getOpenFileName(
                this,
                "Open file",dataPath,
                "Ini files (*.ini);");
    if(path.isEmpty())
        return;

    char* p=path.toLatin1().data();

    FILE* f=fopen(p,"r");

    QString dat;
    while(!feof(f))
    {
        char str[256];
        fgets(str, 256, f);
        QString temp=QString::fromLatin1(str);
        if(!temp.isEmpty())
            if(!temp.contains("end"))
                dat+=QString::fromLatin1(str);
    }


    if(dat.isEmpty())
    {
        return;
    }
    if(!dat.isEmpty())
    {
        QStringList d=dat.split("\r\n");
        data.append(d);
        paths.append(path);
        ui->dataListBox->addItem(path);
        ui->dataListBox->setCurrentIndex(data.length());
    }
    fclose(f);

    ui->dataListBox->setCurrentIndex(data.length());
}

void MainWindow::on_closeGraph_clicked()
{
    if(data.isEmpty())
        return;
    int index=ui->dataListBox->currentIndex();
    if(index==0)
        return;
    data.remove(index-1);
    paths.remove(index-1);
    ui->dataListBox->setCurrentIndex(0);
    ui->dataListBox->removeItem(index);
    ui->dataListBox->setCurrentIndex(paths.length());

    ui->graph->graph(0)->clearData();
    ui->graph->replot();
}

void MainWindow::builder()
{
    qDebug()<<"zzz";
    if(K==0) //?? не срабатывает, QTextEdit всегда непустой
    {
        terminal->output("Sketch is empty!");
        return;
    }

    if(k==K)
    {
        //T.stop();
        terminal->output("Sketch complete!");
        isBuilding=false;
        return;
    }

    QString command=sketch[k];
    QString com=command.split(" ").first();

    if(stm32_port->isWritable())//проверка подключения (скетч правильный, но нет подключения)
    {
        if(!command.isEmpty())
        {
            if(com=="start")
                isMeas=true;
            else
                isMeas=false;

            command+="\r\n";
            stm32_port->write(command.toStdString().c_str());
            k++;
            timer.start(2000);
        }
    }
    else
    {
        err=998;
        errorHandler(err);
        return;
    }
}

void MainWindow::on_startSketch_clicked()//запуск сборки
{
    QString code=ui->codeEdit->toPlainText();
    sketch=code.split("\n");

    if(sketchAnalyzer())//код правильный, подключение в норме
    {
        terminal->output("Analysis complete, building the project...");
        k=0;
        K=sketch.length();


        //T.start(1000);


        isBuilding=true;
        builder();
    }
    else
    {
        terminal->output("line "+QString::number(line+1));
        errorHandler(err);
    }

}

bool MainWindow::sketchAnalyzer() //анализатор кода
{
    line=0;
    err=0;
    if(sketch.isEmpty())
    {
        err=997;
        return false;
    }
    for(int i=0;i<sketch.length();i++)
    {
        //считали команду
        QString command=sketch[i];
        if(command.isEmpty())//пустая строчка
            continue;
        QStringList commandContain=command.split(" ");//выделяем составляющие

        //спаренные пробелы???
//        for(int j=0;j<commandContain.length();j++) //удаляем спаренные пробелы
//        {
//            if(commandContain[j].isEmpty())
//                commandContain.removeAt(j);
//        }
        if(commandContain.length()==2)//должно остаться только 2 аргумента
        {
            //собираем команду
            QString com=commandContain.first();
            QString arg=commandContain.last();

            if(com=="meas")//команда meas
            {
                int N=arg.toInt();//проверяем аргумент
                if(N>0)
                {
                    //переводим в команды микроконтроллера
                    QString message="start "+arg;
                    sketch[i]=message;
                    continue;
                }
                else
                    err=4;
            }

            if(com=="setup")
            {
                //берем аргументы
                QStringList arguments=arg.split(",");



                if(arguments.length()==3)
                {
                    //аргументы
                    int ch1=arguments[0].toInt();
                    int ch2=arguments[1].toInt();
                    int mode=arguments[2].toInt();

                    //правильность аргументов
                    bool cond1=(ch1==1)||(ch1==2)||(ch1==3)||(ch1==4)||(ch1==5)||(ch1==6)||(ch1==7)||(ch1==8);
                    bool cond2=(ch2==1)||(ch2==2)||(ch2==3)||(ch2==4)||(ch2==5)||(ch2==6)||(ch2==7)||(ch2==8);
                    bool cond3=(mode==0)||(mode==1);
                    if(!cond1)
                        err=1;
                    if(!cond2)
                        err=2;
                    if(!cond3)
                        err=3;

                    if(err==0)
                    {
                        QString message="setup "+QString::number(ch1)+QString::number(ch2)+QString::number(mode);
                        sketch[i]=message;
                        continue;
                    }
                }
                else
                    err=5;
            }

            if((com=="set") ||(com=="reset"))
            {
                if((arg=="blue")||(arg=="green"))
                    continue;
                else
                    err=5;
            }
        }
        else
            err=5;

        line=i;
        if(err==0) //анализатор прошел до конца, команда не из списка
        {
            err=999;
            return false;
        }

        //была найдена ошибка
        if(err>0)
        {
            return false;
        }
    }
    return true;
}

//открытие скетча из файла
void MainWindow::on_openSketch_clicked()
{
    bool isOne=false;
    int l=sketches.length(); //вычислим длину
    if(l==1)
    {
        QString code=ui->codeEdit->toPlainText();
        if((code=="")&&(sketches_paths[0]=="u"))
            isOne=true;
    }

    QString path=QFileDialog::getOpenFileName(
                this,
                "Open file",dataPath,
                "Skc files (*.skc);");
    if(path.isEmpty())
        return;

    char* p=path.toLatin1().data();
    FILE* f=fopen(p,"r");
    QString dat;
    while(!feof(f))
    {
        char str[256];
        fgets(str,256,f);
        QString temp=QString::fromLatin1(str);
        if(!temp.isEmpty())
            dat+=QString::fromLatin1(str);
    }
    fclose(f);

    if(dat.isEmpty())
        return;

    QStringList sk=dat.split("\r\n");
    sk.removeAt(sk.length()-2);

    if(isOne)
    {
        sketches[0]=sk;
        sketches_paths[0]=path;
        ui->codeEdit->clear();
        for(int i=0;i<sk.length();i++)
            ui->codeEdit->append(sk[i]);
        QString name=path.split("/").last();
        ui->sketchesListBox->setItemText(0,name);
    }
    else
    {
        sketches.append(sk);
        sketches_paths.append(path);
        ui->codeEdit->clear();
        for(int i=0;i<sk.length();i++)
            ui->codeEdit->append(sk[i]);
        QString name=path.split("/").last();
        ui->sketchesListBox->addItem(name);
        ui->sketchesListBox->setCurrentIndex(sketches_paths.length()-1);
        lastIndex=ui->sketchesListBox->currentIndex();
    }
}

void MainWindow::on_closeSketch_clicked()
{
    int l=sketches.length();
    if(l==1)
    {
        //полная чистка
        ui->codeEdit->clear();
        ui->sketchesListBox->clear();
        sketches.clear();
        sketches_paths.clear();
        //создаем пустые поля
        sketches_paths.append("u"); //добавляем пустой путь

        QString temp="\0";
        QStringList temp0;
        temp0.append(temp);
        sketches.append(temp0);
        //меню нового скетча
        ui->sketchesListBox->addItem("<new sketch>");

    }
    else
    {
        //берем выбранный индекс и общую длину изменяемого вектора
        int index=ui->sketchesListBox->currentIndex();
        //удаляем все, что надо
        sketches.removeAt(index);
        sketches_paths.removeAt(index);
        ui->codeEdit->clear();
        ui->sketchesListBox->removeItem(index);
        //далее перезагружаем
        index=0;

        QStringList sk=sketches[index];
        for(int i=0;i<sk.length();i++)
            ui->codeEdit->append(sk[i]);
        QString path=sketches_paths[index];
        QString name;
        if(path=="u")
            name="<new sketch>";
        else
            name=path.split("/").last();
        ui->sketchesListBox->setCurrentIndex(index);
        ui->sketchesListBox->setItemText(index,name);

    }
}

void MainWindow::on_saveSketch_clicked()
{
    int index=ui->sketchesListBox->currentIndex();
    QString code=ui->codeEdit->toPlainText();
    QStringList s=code.split("\n");
    if(sketches_paths[index]=="u")
    {
        QString path=QFileDialog::getSaveFileName(
                    this,
                    "Save file",dataPath,
                    "Skc files (*.skc);");
        //далее сохраняем
        if(path.isEmpty())
            return;
        char* p=path.toLatin1().data();
        FILE* f=fopen(p,"w");
        for(int i=0;i<s.length();i++)
        {
            QString dat=s[i];
            dat+="\r\n";
            char str[256];
            std::string s1=dat.toStdString();
            for(int j=0;j<dat.length();j++)
                str[j]=s1[j];
            fwrite(str,sizeof(char),dat.length(),f);
        }
        fclose(f);
        //теперь обновляем все
        sketches[index]=s;
        sketches_paths[index]=path;
        QString name=path.split("/").last();
        ui->sketchesListBox->setItemText(index,name);
    }
    else
    {
        QString path=sketches_paths[index];
        if(path.contains("*"))
            path.remove(path.length()-1);
        //далее сохраняем
        char* p=path.toLatin1().data();
        FILE* f=fopen(p,"w");
        for(int i=0;i<s.length();i++)
        {
            QString dat=s[i];
            dat+="\r\n";
            char str[256];
            std::string s1=dat.toStdString();
            for(int j=0;j<dat.length();j++)
                str[j]=s1[j];
            fwrite(str,sizeof(char),dat.length(),f);
        }
        fclose(f);
        //теперь обновляем все
        sketches[index]=s;
        QString name=path.split("/").last();
        ui->sketchesListBox->setItemText(index,name);
    }
}

void MainWindow::autosaving()//не сейв, показывает, что были изменения (тип не сохранено)
{
    int index=ui->sketchesListBox->currentIndex();
    if(index==-1)
        return;
    QString p=ui->sketchesListBox->currentText();
    if((!p.contains("*"))&& (!(p=="<new sketch>")))
        p+="*";
    ui->sketchesListBox->setItemText(index,p);
}

void MainWindow::on_saveSketchAs_clicked()
{
    int index=ui->sketchesListBox->currentIndex();
    QString code=ui->codeEdit->toPlainText();
    QStringList s=code.split("\n");
    QString path=QFileDialog::getSaveFileName(
                this,
                "Save file",dataPath,
                "Skc files (*.skc);");
    //далее сохраняем
    if(path.isEmpty())
        return;
    char* p=path.toLatin1().data();
    FILE* f=fopen(p,"w");
    for(int i=0;i<s.length();i++)
    {
        QString dat=s[i];
        dat+="\r\n";
        char str[256];
        std::string s1=dat.toStdString();
        for(int j=0;j<dat.length();j++)
            str[j]=s1[j];
        fwrite(str,sizeof(char),dat.length(),f);
    }
    fclose(f);
    //теперь обновляем все
    sketches[index]=s;
    sketches_paths[index]=path;
    QString name=path.split("/").last();
    ui->sketchesListBox->setItemText(index,name);
}

void MainWindow::on_saveSketches_clicked()
{
    for(int i=0;i<sketches.length();i++)
    {
        QStringList s=sketches[i];
        QString path=sketches_paths[i];
        if(path=="u")
        {
            path=QFileDialog::getSaveFileName(
                        this,
                        "Save file",dataPath,
                        "Skc files (*.skc);");
            //далее сохраняем
            if(path.isEmpty())
            {
                path="u";
                return;
            }
            char* p=path.toLatin1().data();
            FILE* f=fopen(p,"w");
            for(int i=0;i<s.length();i++)
            {
                QString dat=s[i];
                dat+="\r\n";
                char str[256];
                std::string s1=dat.toStdString();
                for(int j=0;j<dat.length();j++)
                    str[j]=s1[j];
                fwrite(str,sizeof(char),dat.length(),f);
            }
            fclose(f);
            //теперь обновляем все
            sketches[i]=s;
            sketches_paths[i]=path;
            QString name=path.split("/").last();
            ui->sketchesListBox->setItemText(i,name);
        }
        else
        {
            if(path.contains("*"))
                path.remove(path.length()-1);
            //далее сохраняем
            char* p=path.toLatin1().data();
            FILE* f=fopen(p,"w");
            for(int i=0;i<s.length();i++)
            {
                QString dat=s[i];
                dat+="\r\n";
                char str[256];
                std::string s1=dat.toStdString();
                for(int j=0;j<dat.length();j++)
                    str[j]=s1[j];
                fwrite(str,sizeof(char),dat.length(),f);
            }
            fclose(f);
            //теперь обновляем все
            sketches[i]=s;
            QString name=path.split("/").last();
            ui->sketchesListBox->setItemText(i,name);
        }
    }
}

void MainWindow::on_addSketch_clicked()
{
//    localSave();
    QString code=ui->codeEdit->toPlainText();
    QStringList s=code.split("\n");
    sketches[lastIndex]=s;
    qDebug()<<"last="<<lastIndex;
    qDebug()<<"s="<<sketches[lastIndex];



    ui->codeEdit->clear();
    sketches_paths.append("u"); //добавляем пустой путь

    QString temp="\0";
    QStringList temp0;
    temp0.append(temp);
    sketches.append(temp0);

    lastIndex=sketches.length()-1;

    //меню нового скетча
    ui->sketchesListBox->addItem("<new sketch>");
    ui->sketchesListBox->setCurrentIndex(sketches.length()-1);

}

void MainWindow::localSave()
{
    int index=ui->sketchesListBox->currentIndex();
    QString code=ui->codeEdit->toPlainText();
    QStringList s=code.split("\n");
    sketches[index]=s;
}

//void MainWindow::on_sketchesListBox_activated(int index)
//{
//    if(index==-1)
//        return;
//    localSave();
//}
