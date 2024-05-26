// planeta.cpp
#include "planeta.h"

Planeta::Planeta(double masa, double radio, const QVector2D &pos, const QVector2D &vel)
    : QGraphicsEllipseItem(-radio, -radio, 2*radio, 2*radio),
    masa(masa), velocidad(vel) {
    setPos(pos.toPointF());
}

void Planeta::actualizarPosicion(double dt) {
    velocidad += aceleracion * dt;
    setPos(pos() + velocidad.toPointF() * dt);
    aceleracion = QVector2D();  // Resetear la aceleración para el próximo paso
}

void Planeta::aplicarFuerza(const QVector2D &fuerza) {
    aceleracion += fuerza / masa;
}

double Planeta::getMasa() const {
    return masa;
}

QVector2D Planeta::getPosicion() const {
    return QVector2D(pos());
}

QVector2D Planeta::getVelocidad() const {
    return velocidad;
}
