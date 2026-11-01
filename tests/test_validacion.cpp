#include "../src/karatsuba.hpp"
#include <iostream>
#include <string>


bool verificarCaso(const std::string& nombre, const std::string& A, const std::string& B) {
    std::string esperado = multiplicacionClasica(A, B);
    std::string obtenido = karatsuba(A, B);

    std::cout << "  Caso: " << nombre << "\n";
    std::cout << "    Clasica  : " << esperado << "\n";
    std::cout << "    Karatsuba: " << obtenido << "\n\n";

    return esperado == obtenido;
}

int main() {
    int fallos = 0;
    std::cout << " VALIDACION DE CORRECTITUD Y CASOS DE BORDE \n\n";

    // Caso 1: Numeros de 1 digito
    std::cout << "[caso 1] Numeros de 1 digito\n";
    if (!verificarCaso("0 * 9", "0", "9")) fallos++;
    if (!verificarCaso("7 * 8", "7", "8")) fallos++;
    if (!verificarCaso("9 * 9", "9", "9")) fallos++;

    // Caso 2: Operandos con muchos ceros a la izquierda
    std::cout << "\n[caso 2] Operandos con muchos ceros a la izquierda\n";
    if (!verificarCaso("00000000012345 * 0000067890", "00000000012345", "0000067890")) fallos++;
    if (!verificarCaso("00000000000000 * 0000999999", "00000000000000", "0000999999")) fallos++;

    // Caso 3: Factores con ceros intercalados
    std::cout << "\n[caso 3] Factores con ceros intercalados\n";
    if (!verificarCaso("1000200030004 * 50000600007", "1000200030004", "50000600007")) fallos++;
    if (!verificarCaso("9000000000009 * 10000000001", "9000000000009", "10000000001")) fallos++;

    // Caso 4: Longitudes impares antes del relleno
    std::cout << "\n[caso 4] Longitudes impares antes del relleno\n";
    if (!verificarCaso("3 digitos * 5 digitos (987 * 12345)", "987", "12345")) fallos++;
    if (!verificarCaso("7 digitos * 9 digitos (1234567 * 987654321)", "1234567", "987654321")) fallos++;

    // Caso 5: Producto grande (varios cientos de digitos)
    std::cout << "\n[caso 5] Producto grande (300 digitos * 300 digitos)\n";
    std::string grandeA = "9";
    std::string grandeB = "8";
    for (int i = 1; i < 300; ++i) {
        grandeA.push_back('0' + ((i * 7 + 3) % 10));
        grandeB.push_back('0' + ((i * 3 + 7) % 10));
    }
    if (!verificarCaso("Producto de 300 digitos", grandeA, grandeB)) fallos++;

    std::cout << "\n================================================================\n";
    if (fallos == 0) {
        std::cout << "RESULTADO: TODOS LOS CASOS DE VALIDACION PASARON EXITOSAMENTE.\n";
    } else {
        std::cout << "RESULTADO: " << fallos << " CASO(S) FALLARON.\n";
    }

    return (fallos == 0) ? 0 : 1;
}