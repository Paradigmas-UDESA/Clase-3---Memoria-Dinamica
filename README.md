# Taller de Memoria Dinamica - Paradigmas de Programacion

## Consigna
Estas trabajando en un prototipo inicial para un sistema de Machine Learning que debe cargar un dataset desde un archivo CSV. Sin embargo, el codigo actual está "roto": tiene problemas de gestion de memoria (memory leaks, accesos a memoria liberada y *segfaults*).

Objetivos:
1. Compilar y ejecutar los tests usando el `Makefile`.
2. Identificar los bugs usando los tests y el debugger. Anoten cuantos encontraron y de que tipo de error se trata.
    - Bug1: ej memory leak 
    - Bug2:
    ...
3. Arreglar todos los bugs y lograr pasar los tests con exito.
4. Refactorizar el manejo de memoria usando **Smart Pointers (`std::unique_ptr`)**.
5. Asegurarse de que **Valgrind** reporte cero memory leaks al final del ejercicio.

## Comandos de Make
- `make TYPE=Base / make TYPE=RawPtr / make TYPE=Smart`: Compila el proyecto base, solucion con raw pointer y solucion con smart pointers.
- `make test`: Ejecuta la test suite compilada.
- `make valgrind`: Ejecuta los tests buscando memory leaks con Valgrind.
- `make clean`: Limpia los archivos binarios.



### Flashcards sobre la clase:
(Requiere login)
https://knowt.com/flashcards/f3855265-3d3c-4970-ad9f-cf855a25bc23