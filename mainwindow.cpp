#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVector2D>
#include <cmath>
#include <QColor>
#include <algorithm>

const double G = 6.6738e-11;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    timer(new QTimer(this)),
    cantidadCuerpos(0),
    cuerposAgregados(0) {
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    connect(ui->spinBoxCantidadCuerpos, QOverload<int>::of(&QSpinBox::valueChanged), [this](int value) {
        cantidadCuerpos = value;
        cuerposAgregados = 0;
        planetas.clear();
        scene->clear();
        ui->pushButtonIniciarSimulacion->setEnabled(false);
    });
    connect(ui->pushButtonAgregarCuerpo, &QPushButton::clicked, this, &MainWindow::agregarCuerpo);
    connect(ui->pushButtonIniciarSimulacion, &QPushButton::clicked, this, &MainWindow::iniciarSimulacion);
    connect(ui->pushButtonDetenerSimulacion, &QPushButton::clicked, this, &MainWindow::detenerSimulacion);
    connect(timer, &QTimer::timeout, this, &MainWindow::actualizarSimulacion);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::agregarCuerpo() {
    if (cuerposAgregados < cantidadCuerpos) {
        double masa = ui->lineEditMasa->text().toDouble();
        double radio = ui->lineEditRadio->text().toDouble();
        QVector2D pos(ui->lineEditPosX->text().toDouble(), ui->lineEditPosY->text().toDouble());
        QVector2D vel(ui->lineEditVelX->text().toDouble(), ui->lineEditVelY->text().toDouble());

        // Lista de colores predefinidos
        QList<QColor> colores = {Qt::red, Qt::green, Qt::blue, Qt::yellow, Qt::cyan, Qt::magenta};
        QColor color = colores[cuerposAgregados % colores.size()];

        Planeta *planeta = new Planeta(masa, radio, pos, vel, color);
        planetas.append(planeta);
        scene->addItem(planeta);

        cuerposAgregados++;
        limpiarCampos(); // Limpiar los campos después de agregar un cuerpo

        if (cuerposAgregados == cantidadCuerpos) {
            ui->pushButtonIniciarSimulacion->setEnabled(true);
        }
    }
}

void MainWindow::limpiarCampos() {
    ui->lineEditMasa->clear();
    ui->lineEditRadio->clear();
    ui->lineEditPosX->clear();
    ui->lineEditPosY->clear();
    ui->lineEditVelX->clear();
    ui->lineEditVelY->clear();
}

void MainWindow::iniciarSimulacion() {
    if (planetas.isEmpty()) return;

    // Identificar la estrella
    Planeta* estrella = *std::max_element(planetas.begin(), planetas.end(), [](Planeta* p1, Planeta* p2) {
        if (p1->getMasa() == p2->getMasa()) {
            return p1->getRadio() > p2->getRadio(); // Menor radio
        }
        return p1->getMasa() < p2->getMasa();
    });

    // Ajustar las velocidades de los demás cuerpos para que orbiten alrededor de la estrella
    for (Planeta* planeta : planetas) {
        if (planeta != estrella) {
            QVector2D dir = planeta->getPosicion() - estrella->getPosicion();
            double distancia = dir.length();
            double velocidadOrbital = std::sqrt(G * estrella->getMasa() / distancia);

            // Vector velocidad perpendicular al vector dirección
            QVector2D velPerpendicular(-dir.y(), dir.x());
            velPerpendicular.normalize();
            velPerpendicular *= velocidadOrbital;

            planeta->aplicarFuerza(planeta->getMasa() * velPerpendicular / 0.016); // Ajustar la velocidad inicial
        }
    }

    timer->start(16);  // Aproximadamente 60 FPS
}

void MainWindow::detenerSimulacion() {
    timer->stop();
    // Limpiar la escena y resetear la simulación
    scene->clear();
    planetas.clear();
    cuerposAgregados = 0;
    ui->pushButtonIniciarSimulacion->setEnabled(false);
}

void MainWindow::actualizarSimulacion() {
    calcularGravedad();
    for (Planeta* planeta : planetas) {
        // Dibujar la estela
        scene->addLine(planeta->getPosicion().x(), planeta->getPosicion().y(),
                       planeta->pos().x(), planeta->pos().y(),
                       QPen(planeta->getColor()));

        planeta->actualizarPosicion(0.016);  // Aproximadamente 60 FPS
    }
}

void MainWindow::calcularGravedad() {
    for (Planeta* p1 : planetas) {
        QVector2D fuerzaTotal;
        for (Planeta* p2 : planetas) {
            if (p1 != p2) {
                QVector2D dir = p2->getPosicion() - p1->getPosicion();
                double distancia = dir.length();
                if (distancia == 0) continue;
                double fuerzaMag = (G * p1->getMasa() * p2->getMasa()) / (distancia * distancia);
                QVector2D fuerza = fuerzaMag * dir.normalized();
                fuerzaTotal += fuerza;
            }
        }
        p1->aplicarFuerza(fuerzaTotal);
    }
}
