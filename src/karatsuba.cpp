#include "karatsuba.hpp"
#include <algorithm>

// Elimina ceros a la izquierda 
std::string normalizar(const std::string& A) {
    size_t pos = A.find_first_not_of('0');
    if (pos == std::string::npos) {
        return "0";
    }
    return A.substr(pos);
}

// Rellena ambos numeros con ceros a la izquierda hasta igualar a una potencia de 2
void igualarLongitudPotencia2(std::string& A, std::string& B) {
    size_t max_len = std::max(A.size(), B.size());
    size_t pot2 = 1;
    while (pot2 < max_len) {
        pot2 *= 2;
    }
    if (A.size() < pot2) {
        A = std::string(pot2 - A.size(), '0') + A;
    }
    if (B.size() < pot2) {
        B = std::string(pot2 - B.size(), '0') + B;
    }
}

// 1. sumar(A, B) 
std::string sumar(const std::string& A, const std::string& B) {
    std::string resultado = "";
    int i = (int)A.size() - 1;
    int j = (int)B.size() - 1;
    int carry = 0;

    while (i >= 0 || j >= 0 || carry > 0) {
        int d1 = (i >= 0) ? (A[i--] - '0') : 0;
        int d2 = (j >= 0) ? (B[j--] - '0') : 0;
        int suma = d1 + d2 + carry;
        resultado.push_back('0' + (suma % 10));
        carry = suma / 10;
    }

    std::reverse(resultado.begin(), resultado.end());
    return normalizar(resultado);
}

// 2. restar(A, B) 
std::string restar(const std::string& A, const std::string& B) {
    std::string a = normalizar(A);
    std::string b = normalizar(B);

    std::string resultado = "";
    int i = (int)a.size() - 1;
    int j = (int)b.size() - 1;
    int borrow = 0;

    while (i >= 0) {
        int d1 = a[i--] - '0';
        int d2 = (j >= 0) ? (b[j--] - '0') : 0;
        int diff = d1 - d2 - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        resultado.push_back('0' + diff);
    }

    std::reverse(resultado.begin(), resultado.end());
    return normalizar(resultado);
}

// 3. desplazar(A, k) 
std::string desplazar(const std::string& A, int k) {
    std::string a = normalizar(A);
    if (a == "0" || k <= 0) {
        return a;
    }
    return a + std::string(k, '0');
}

// 4. partir(A, m) 
Mitades partir(const std::string& A, int m) {
    if (m <= 0) {
        return {normalizar(A), "0"};
    }
    if ((size_t)m >= A.size()) {
        return {"0", normalizar(A)};
    }
    size_t corte = A.size() - m;
    std::string alta = A.substr(0, corte);
    std::string baja = A.substr(corte);
    return {alta, baja};
}


std::string multiplicacionClasica(const std::string& A, const std::string& B) {
   //  Multiplicacion clasica O(n^2) sobre cadenas de digitos en base 10
    std::string a = normalizar(A);
    std::string b = normalizar(B);

    if (a == "0" || b == "0") {
        return "0";
    }

    size_t n = a.size();
    size_t m = b.size();
    // El producto de n digitos por m digitos tiene a lo sumo n + m digitos
    std::string resultado(n + m, '0');

    // Multiplicamos cada digito de 'a' por cada digito de 'b' de derecha a izquierda
    for (int i = (int)n - 1; i >= 0; --i) {
        int carry = 0;
        int d1 = a[i] - '0';

        for (int j = (int)m - 1; j >= 0; --j) {
            int d2 = b[j] - '0';
            int suma = (resultado[i + j + 1] - '0') + (d1 * d2) + carry;
            resultado[i + j + 1] = '0' + (suma % 10);
            carry = suma / 10;
        }
        resultado[i] += carry;
    }

    return normalizar(resultado);
}

//  Multiplicacion rapida de Karatsuba recursiva (3 productos)
std::string karatsuba(const std::string& A, const std::string& B) {
    std::string a = normalizar(A);
    std::string b = normalizar(B);

    // Si alguno de los factores es 0, el producto es 0
    if (a == "0" || b == "0") {
        return "0";
    }

    //  Caso base de 1 digito resuelto con multiplicacion directa
    if (a.size() == 1 && b.size() == 1) {
        int prod = (a[0] - '0') * (b[0] - '0');
        return std::to_string(prod);
    }

    //  Igualar longitud a la misma potencia de 2 con ceros a la izquierda
    igualarLongitudPotencia2(a, b);
    int n = (int)a.size();
    int m = n / 2;

    // Separar en mitad alta y mitad baja respecto a m
    Mitades partA = partir(a, m);
    Mitades partB = partir(b, m);

    const std::string& x1 = partA.alta;
    const std::string& x0 = partA.baja;
    const std::string& y1 = partB.alta;
    const std::string& y0 = partB.baja;

    // Tres productos recursivos de Karatsuba:
    // P1 = x1 * y1
    // P2 = x0 * y0
    // P3 = (x1 + x0) * (y1 + y0)
    std::string P1 = karatsuba(x1, y1);
    std::string P2 = karatsuba(x0, y0);
    std::string P3 = karatsuba(sumar(x1, x0), sumar(y1, y0));

    //  Orden de resta para evitar negativos intermedios -> (P3 - P1) - P2
    std::string P3_menos_P1 = restar(P3, P1);
    std::string termino_central = restar(P3_menos_P1, P2);

    // Recomposicion: x * y = P1 * 10^(2m) + (P3 - P1 - P2) * 10^m + P2
    std::string parte1 = desplazar(P1, 2 * m);
    std::string parte2 = desplazar(termino_central, m);
    std::string resultado = sumar(sumar(parte1, parte2), P2);

    return normalizar(resultado);
}