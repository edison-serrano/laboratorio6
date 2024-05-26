#include "planeta.h"
#include <cmath>

Planeta::Planeta(double masa, double radio, QVector2D posicion, QVector2D velocidad, QColor color)
    : masa(masa), radio(radio), posicion(posicion), velocidad(velocidad), color(color), posicionAnterior(posicion) {
    setRect(-radio, -radio, 2 * radio, 2 * radio);
    setBrush(color);
    setPen(QPen(color));
}

double Planeta::getMasa() const {
    return masa;
}

QVector2D Planeta::getPosicion() const {
    return posicion;
}

void Planeta::aplicarFuerza(const QVector2D &fuerza) {
    fuerzaAcumulada += fuerza;
}

void Planeta::actualizarPosicion(double dt) {
    QVector2D aceleracion = fuerzaAcumulada / masa;
    velocidad += aceleracion * dt;
    posicionAnterior = posicion; // Almacenar la posición anterior
    posicion += velocidad * dt + 0.5 * aceleracion * dt * dt;
    setPos(posicion.toPointF());
    fuerzaAcumulada = QVector2D(); // Resetear fuerza acumulada
}

double Planeta::getRadio() const {
    return radio;
}

QColor Planeta::getColor() const {
    return color;
}
