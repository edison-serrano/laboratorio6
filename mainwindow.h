// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include "planeta.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void agregarCuerpo();
    void iniciarSimulacion();
    void detenerSimulacion();
    void actualizarSimulacion();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QTimer *timer;
    QVector<Planeta*> planetas;
    int cantidadCuerpos;
    int cuerposAgregados;

    void calcularGravedad();
    void limpiarCampos();
};

#endif // MAINWINDOW_H
