#include "../src/karatsuba.hpp"
#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <iomanip>

// Genera un numero aleatorio de n digitos en base 10 (el primero entre 1 y 9)
std::string generarNumeroAleatorio(int n, std::mt19937& gen) {
    std::uniform_int_distribution<int> distPrimero(1, 9);
    std::uniform_int_distribution<int> distResto(0, 9);

    std::string num = "";
    num.reserve(n);
    num.push_back('0' + distPrimero(gen));
    for (int i = 1; i < n; ++i) {
        num.push_back('0' + distResto(gen));
    }
    return num;
}

// Repeticiones suficientes para superar la resolucion del reloj
int obtenerRepeticiones(int n) {
    if (n <= 32) return 200;
    if (n <= 256) return 30;
    if (n <= 1024) return 5;
    return 3;
}

int main() {
    std::mt19937 gen(12345); // Semilla fija para reproducibilidad
    std::ofstream csv("results/tiempos.csv");
     csv << std::fixed << std::setprecision(2);
    csv << "n,repeticiones,tiempo_clasica_us,tiempo_karatsuba_us\n";

    // Variable volatile para consumir el resultado y evitar que -O2 elimine el calculo
    volatile size_t consumidor = 0;
    int punto_de_cruce = -1;

    std::cout << "MEDICION DE TIEMPOS \n\n";
    std::cout << std::left << std::setw(10) << "Digitos"
              << std::setw(10) << "Reps"
              << std::setw(22) << "Clasica (us)"
              << std::setw(22) << "Karatsuba (us)" << "\n";
    std::cout << std::string(64, '-') << "\n";

    for (int n = 2; n <= 4096; n *= 2) {
        std::string A = generarNumeroAleatorio(n, gen);
        std::string B = generarNumeroAleatorio(n, gen);
        int reps = obtenerRepeticiones(n);

        std::string resClasica, resKaratsuba;

        // 1. Medir Multiplicacion Clasica
        auto inicioC = std::chrono::steady_clock::now();
        for (int r = 0; r < reps; ++r) {
            resClasica = multiplicacionClasica(A, B);
            consumidor += resClasica[0];
        }
        auto finC = std::chrono::steady_clock::now();
        double tiempoClasica_us = std::chrono::duration<double, std::micro>(finC - inicioC).count() / reps;

        // 2. Medir Karatsuba
        auto inicioK = std::chrono::steady_clock::now();
        for (int r = 0; r < reps; ++r) {
            resKaratsuba = karatsuba(A, B);
            consumidor += resKaratsuba[0];
        }
        auto finK = std::chrono::steady_clock::now();
        double tiempoKaratsuba_us = std::chrono::duration<double, std::micro>(finK - inicioK).count() / reps;

        // Verificar que ambos dieron el mismo producto
        if (resClasica != resKaratsuba) {
            std::cerr << "Error: discrepancia en n = " << n << "\n";
            return 1;
        }

        // Registrar punto de cruce si Karatsuba supera al clasico
        if (tiempoKaratsuba_us < tiempoClasica_us && punto_de_cruce == -1) {
            punto_de_cruce = n;
        }

        std::cout << std::left << std::setw(10) << n
                  << std::setw(10) << reps
                  << std::fixed << std::setprecision(2)
                  << std::setw(22) << tiempoClasica_us
                  << std::setw(22) << tiempoKaratsuba_us << "\n";

        csv << n << "," << reps << "," << tiempoClasica_us << "," << tiempoKaratsuba_us << "\n";
    }

    std::cout << std::string(64, '-') << "\n";
    if (punto_de_cruce != -1) {
        std::cout << "Punto de cruce detectado en n = " << punto_de_cruce << " digitos.\n";
    } else {
        std::cout << "Punto de cruce: No alcanzado en el rango [2, 4096].\n";
    }
    std::cout << "Archivo 'results/tiempos.csv' generado correctamente.\n";

    csv.close();
    return 0;
}