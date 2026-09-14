# MergeSort.c vs MergeMedioInverso.c

Comparación estructural entre el MergeSort iterativo base (`MergeSort/MergeSort.c`) y su variante (`Ejercicios/MergeMedioInverso.c`), que ordena la primera mitad del arreglo de forma ascendente y la segunda mitad de forma descendente.

## 1. Estado compartido

| | MergeSort.c | MergeMedioInverso.c |
|---|---|---|
| Variables globales/estáticas | Ninguna | `static int mediana` (declarada en el `.h`) |
| Acoplamiento `main()` ↔ `merge()` | Ninguno — `merge()` es puro, depende solo de sus parámetros | `merge()` depende de `mediana`, una variable externa a sus parámetros |

## 2. `main()`: construcción del árbol de recursión

- **MergeSort.c** hace un único `push` que cubre todo el arreglo:
  ```c
  push(&pila, 0, argc-1, DIVIDIR);
  ```
  Esto genera un único árbol de recursión, cuyo nodo raíz termina en un `merge()` final que combina ambas mitades.

- **MergeMedioInverso.c** calcula el punto medio y hace **dos pushes independientes**:
  ```c
  mediana = argc/2;
  push(&pila, mediana+1, argc-1, DIVIDIR); // segunda mitad
  push(&pila, 0, mediana, DIVIDIR);        // primera mitad
  ```
  Esto genera **dos árboles de recursión separados**, por lo que nunca se ejecuta un `merge()` que combine elementos de ambas mitades entre sí.

## 3. `merge()`: lógica de combinación

- **MergeSort.c** tiene una única rama de comparación, siempre ascendente:
  ```c
  temp[k++] = (arr[i] <= arr[j]) ? arr[i++] : arr[j++];
  ```

- **MergeMedioInverso.c** bifurca según a qué mitad pertenece el rango (`izq < mediana` vs `izq >= mediana`):
  ```c
  if (izq < mediana)       // ascendente: arr[i] <= arr[j]
  else if (izq >= mediana) // descendente: arr[i] >= arr[j]
  ```
  Ambas ramas conservan la misma estructura de bucles (avance de `i`/`j` con `<=`); solo cambia el operador de comparación de valores.

## 4. Resultado final

- **MergeSort.c**: arreglo completo ordenado ascendente.
- **MergeMedioInverso.c**: primera mitad ascendente + segunda mitad descendente, sin que ambas mitades se mezclen entre sí en ningún `merge()`.
