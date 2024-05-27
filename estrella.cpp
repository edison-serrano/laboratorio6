#include "estrella.h"
#include "planeta.h"

#include "estrella.h"

Estrella::Estrella() {
    // Inicialización u otras operaciones necesarias
}

const double G = 6.674e-11;

Estrella::Estrella(Planeta* centro) : centro(centro) {
    // Asegúrate de que el centro no sea nulo
    if (centro != nullptr) {
        planetas.append(centro); // Agregar el centro a la lista de planetas
    }
}

void Estrella::agregarPlaneta(Planeta* planeta) {
    planetas.append(planeta);
}

void Estrella::establecerCentro() {
    // Encontrar el planeta con menor radio
    centro = *std::min_element(planetas.begin(), planetas.end(), [](Planeta* a, Planeta* b) {
        return a->getRadio() < b->getRadio();
    });
}

void Estrella::iniciarOrbita() {
    if (!centro) return;

    // Ajustar las velocidades de los demás cuerpos para que orbiten alrededor del centro
    for (Planeta* planeta : planetas) {
        if (planeta != centro) {
            QVector2D dir = centro->getPosicion() - planeta->getPosicion();
            double distancia = dir.length();
            double velocidadOrbital = std::sqrt(G * centro->getMasa() / distancia);

            // Vector velocidad perpendicular al vector dirección
            QVector2D velPerpendicular(-dir.y(), dir.x());
            velPerpendicular.normalize();
            velPerpendicular *= velocidadOrbital;

            // Asignar la velocidad tangencial al planeta
            planeta->setVelocidad(velPerpendicular);
        }
    }

    // Aquí deberías iniciar la simulación (por ejemplo, utilizando un bucle)
}
