#include "karatsuba.hpp"
#include <iostream>

int main() {
    int opcion = -1;

    while (opcion != 0) {
        std::cout << "\n=============================================\n";
        std::cout << "   INTERFAZ DE OPERACIONES \n";
        std::cout << "=============================================\n";
        std::cout << "1. sumar(A, B)\n";
        std::cout << "2. restar(A, B) [Precondicion A >= B]\n";
        std::cout << "3. desplazar(A, k)\n";
        std::cout << "4. partir(A, m)\n";
        std::cout << "5. multiplicacionClasica(A, B)\n";
        std::cout << "6. karatsuba(A, B)\n";
        std::cout << "0. Salir\n";
        std::cout << "Seleccione una operacion: ";
        
        if (!(std::cin >> opcion)) break;

        if (opcion == 1) {
            std::string A, B;
            std::cout << "Ingrese A: "; std::cin >> A;
            std::cout << "Ingrese B: "; std::cin >> B;
            std::cout << "-> sumar(A, B) = " << sumar(A, B) << "\n";
        } 
        else if (opcion == 2) {
            std::string A, B;
            std::cout << "Ingrese A: "; std::cin >> A;
            std::cout << "Ingrese B: "; std::cin >> B;
            std::cout << "-> restar(A, B) = " << restar(A, B) << "\n";
        } 
        else if (opcion == 3) {
            std::string A;
            int k;
            std::cout << "Ingrese A: "; std::cin >> A;
            std::cout << "Ingrese k: "; std::cin >> k;
            std::cout << "-> desplazar(A, " << k << ") = " << desplazar(A, k) << "\n";
        } 
        else if (opcion == 4) {
            std::string A;
            int m;
            std::cout << "Ingrese A: "; std::cin >> A;
            std::cout << "Ingrese posicion m: "; std::cin >> m;
            Mitades mit = partir(A, m);
            std::cout << "-> Mitad alta (x1): " << mit.alta << "\n";
            std::cout << "-> Mitad baja (x0): " << mit.baja << "\n";
        } 
        else if (opcion == 5) {
            std::string A, B;
            std::cout << "Ingrese A: "; std::cin >> A;
            std::cout << "Ingrese B: "; std::cin >> B;
            std::cout << "-> multiplicacionClasica(A, B) = " << multiplicacionClasica(A, B) << "\n";
        } 
        else if (opcion == 6) {
            std::string A, B;
            std::cout << "Ingrese A: "; std::cin >> A;
            std::cout << "Ingrese B: "; std::cin >> B;
            std::cout << "-> karatsuba(A, B) = " << karatsuba(A, B) << "\n";
        }
    }

    return 0;
}