#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <qterminal.h>
#include <qcustomplot.h>
#include <QTimer>
#include <QVector>
#include <QDir>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //обновление списка портов
    void on_refreshButton_clicked();


    //подключение/отключение
    void on_connectButton_clicked();


    //вывод информации о выбранном порте
    void showPortInfo(int index);

    //отправка команды из терминала
    void sendCommandFromTerminal();

    //прием данных
    void receiveData();

    //обработчик ошибок
    void errorHandler(int code);


    //масштабирование графика
    void on_X_min_valueChanged(int arg1);

    void on_X_max_valueChanged(int arg1);

    void on_Y_min_valueChanged(int arg1);

    void on_Y_max_valueChanged(int arg1);

    void on_X_step_valueChanged(int arg1);

    void on_Y_step_valueChanged(int arg1);

    //обработка полученных данных после отправки команды meas
    void onTimer();

    //изменение папки для сохранения данных
    void on_chooseDataDir_clicked();

    //сохранение выбранного графика
    void saveGraph(QStringList d);

    //отрисовка выбранного графика
    void drawGraph(QStringList d);

    //вывод графика (вызов из ListBox)
    void showGraph();

    //вывод скетча
    void showSketch();

    void drawing();


    //работа с файлами
    void on_openGraph_clicked();

    void on_closeGraph_clicked();


    void on_startSketch_clicked();
    //анализатор сборщика
    bool sketchAnalyzer();

    //сборка скетча
    void builder();

    //работа с файлами скетчей
//    void saveSketch(QStringList s, int index);
//    void loadSketch();


    void on_openSketch_clicked();

    void on_closeSketch_clicked();

    void on_saveSketch_clicked();

    void autosaving();

    void on_saveSketchAs_clicked();

    void on_saveSketches_clicked();

    void on_addSketch_clicked();

    void localSave();

//    void on_sketchesListBox_activated(int index);

private:
    Ui::MainWindow *ui;
    //данные о микроконтроллере
    static const quint16 stm32_VID=9825;
    static const quint16 stm32_PID=67;
    QSerialPort *stm32_port; //порт, в котором находится микроконтроллер
    //состояние подключения
    bool isConnected=false;
    //консоль
    QTerminal *terminal;

    //буфер с портом
    QByteArray buff;

    //таймер ожидания данных
    QTimer timer;
    //принятые точки
    QStringList points;
    //код на выолнение
    QStringList sketch;

    //массив с данными графиков
    QVector<QStringList> data;
    //массив с путями до сохранённых данных
    QVector<QString> paths;
    //массив со сценариями
    QVector<QStringList> sketches;
    //массив с путями до сценариев
    QVector<QString> sketches_paths;

    //индексы данных и скетча
    int indexData=0;
    int indexSketch=0;

    //папка для сохранения данных
    QString dataPath;

    //таймер сборщика
    //QTimer T;

    //построчный индекс сборщика
    int k=0;
    int K=0;

    bool isBuilding=false;
    bool isMeas=false;

    //код ошибки сборки
    int err;
    int line;

    int lastIndex=0;

};

#endif // MAINWINDOW_H
