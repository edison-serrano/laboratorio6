// planeta.h
#ifndef PLANETA_H
#define PLANETA_H

#include <QGraphicsEllipseItem>
#include <QVector2D>

class Planeta : public QGraphicsEllipseItem {
public:
    Planeta(double masa, double radio, const QVector2D &pos, const QVector2D &vel);

    void actualizarPosicion(double dt);
    void aplicarFuerza(const QVector2D &fuerza);

    double getMasa() const;
    QVector2D getPosicion() const;
    QVector2D getVelocidad() const;

private:
    double masa;
    QVector2D velocidad;
    QVector2D aceleracion;
};

#endif // PLANETA_H
