# Práctica 2: Multiplicación Rápida de Enteros (Algoritmo de Karatsuba)

Este repositorio contiene la implementación, validación de casos de borde, experimentación de tiempos e informe final correspondientes a la **Práctica 2** del curso **Análisis y Diseño de Algoritmos (ADA)**.

---

## Autor

* **Alejandro Cifuentes Arroyave**

---

## Organización del Proyecto

```text
ADA_P2_CifuentesArroyaveAlejandro/
├── src/
│   ├── karatsuba.hpp          # Declaración de la interfaz
│   ├── karatsuba.cpp          # Implementación de operaciones auxiliares, clásica y Karatsuba
│   └── main.cpp               # Interfaz interactiva de las operaciones en consola
├── tests/
│   ├── test_validacion.cpp    # Pruebas de correctitud y casos de borde
│   └── test_benchmark.cpp     # Protocolo de medición con steady_clock
├── results/
│   └── tiempos.csv            # Tabla de tiempos experimentales (2 a 4096 dígitos)
├── report/
│   └── Informe.pdf            # Informe académico en PDF
├── .gitignore
└── README.md
```

---

## Requisitos de Compilación

* **Lenguaje:** C++17
* **Compilador:** `g++` 9.0 o superior (compatible con Windows MinGW / WSL2 / Linux)
* **Flags de compilación obligatorias:** `-std=c++17 -O2`

### Comando de Compilación Unificado

Ejecute desde la raíz del repositorio:

```bash
g++ -std=c++17 -O2 -o ada_p2 src/*.cpp
g++ -std=c++17 -O2 -o test_validacion src/karatsuba.cpp tests/test_validacion.cpp
g++ -std=c++17 -O2 -o test_benchmark src/karatsuba.cpp tests/test_benchmark.cpp
```

En Windows:

```bash
g++ -std=c++17 -O2 -o ada_p2.exe src/*.cpp
g++ -std=c++17 -O2 -o test_validacion.exe src/karatsuba.cpp tests/test_validacion.cpp
g++ -std=c++17 -O2 -o test_benchmark.exe src/karatsuba.cpp tests/test_benchmark.cpp
```

---

## Reproducción de experimentos

### 1. Ejecutar Interfaz de Operaciones

```bash
./ada_p2
```

En Windows:

```bash
.\ada_p2.exe
```

### 2. Ejecutar Validación de Casos de Borde

```bash
./test_validacion
```

En Windows:

```bash
.\test_validacion.exe
```

### 3. Ejecutar Medición de Tiempos

```bash
./test_benchmark
```

En Windows:

```bash
.\test_benchmark.exe
```