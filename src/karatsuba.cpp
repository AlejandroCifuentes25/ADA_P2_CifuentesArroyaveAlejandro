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
    return "0";
}

std::string karatsuba(const std::string& A, const std::string& B) {
    return "0";
}