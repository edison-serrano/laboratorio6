#ifndef PLANETA_H
#define PLANETA_H

#include <QGraphicsEllipseItem>
#include <QVector2D>
#include <QPen>
#include <QColor>

class Planeta : public QGraphicsEllipseItem {
public:
    Planeta(double masa, double radio, QVector2D posicion, QVector2D velocidad, QColor color);

    double getMasa() const;
    QVector2D getPosicion() const;
    void aplicarFuerza(const QVector2D &fuerza);
    void actualizarPosicion(double dt);
    double getRadio() const;
    QColor getColor() const; // Método para obtener el color

private:
    double masa;
    double radio;
    QVector2D posicion;
    QVector2D velocidad;
    QVector2D fuerzaAcumulada;
    QVector2D posicionAnterior; // Posición anterior para dibujar la estela
    QColor color;
};

#endif // PLANETA_H
