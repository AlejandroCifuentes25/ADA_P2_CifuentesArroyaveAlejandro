#ifndef KARATSUBA_HPP
#define KARATSUBA_HPP

#include <string>

// Estructura para almacenar el resultado de partir(A, m)
struct Mitades {
    std::string alta; // x1 (digitos mas significativos)
    std::string baja; // x0 (m digitos menos significativos)
};


std::string normalizar(const std::string& A);
void igualarLongitudPotencia2(std::string& A, std::string& B);

// Interfaz de operaciones auxiliares 
std::string sumar(const std::string& A, const std::string& B);
std::string restar(const std::string& A, const std::string& B);
std::string desplazar(const std::string& A, int k);
Mitades partir(const std::string& A, int m);

// Algoritmos de multiplicacion 
std::string multiplicacionClasica(const std::string& A, const std::string& B);
std::string karatsuba(const std::string& A, const std::string& B);

#endif // KARATSUBA_HPP