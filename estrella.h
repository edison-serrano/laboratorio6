#ifndef ESTRELLA_H
#define ESTRELLA_H

#include "planeta.h"
#include <algorithm> // Para usar std::min_element y std::max_element

class Estrella {
public:
    Estrella(); // Constructor por defecto
    Estrella(Planeta* centro);

    void agregarPlaneta(Planeta* planeta); // Método para agregar un planeta al sistema
    void establecerCentro(); // Método para establecer el centro de la estrella
    void iniciarOrbita(); // Método para iniciar la simulación de la órbita

private:
    Planeta* centro; // Puntero al planeta más pequeño (con menor radio)
    QList<Planeta*> planetas; // Lista de planetas orbitando alrededor de la estrella
};

#endif // ESTRELLA_H
