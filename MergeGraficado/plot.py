import math
from pathlib import Path

import pandas as pd
import matplotlib.pyplot as plt        # es pyplot, no "pylot"


if __name__ == "__main__":

    # Ruta del CSV relativa a ESTE archivo, no a la carpeta desde donde se ejecuta
    # ... así funciona igual desde Algoritmos/, desde MergeGraficado/ o con el botón Run
    ruta_csv = Path(__file__).resolve().parent / "merge.csv"

    # Cargar archivo. header=None porque el CSV no tiene fila de títulos:
    # ... cada línea es "cantidad_de_datos,comparaciones"
    datos = pd.read_csv(ruta_csv, header=None, names=["n", "comparaciones"])

    # Ordenamos por tamaño para que la línea se dibuje de izquierda a derecha
    # ... aunque los casos se hayan escrito en otro orden
    datos = datos.sort_values(by="n")

    x = datos["n"].tolist()             # eje X: cantidad de datos (n)
    y = datos["comparaciones"].tolist() # eje Y: comparaciones que hizo el merge sort

    # Curva teórica n*log2(n), escalada para que coincida con el último punto medido.
    # Sirve para comprobar visualmente que lo medido crece igual que la teoría
    ref = [n * math.log2(n) for n in x]
    escala = y[-1] / ref[-1]
    ref = [r * escala for r in ref]

    plt.plot(x, y, "-b", label="Comparaciones medidas")
    plt.plot(x, ref, "--r", label="n·log₂(n) (referencia)")

    # NO se usa plt.xticks(x): con decenas de valores de 6 o 7 dígitos las etiquetas
    # ... se encinan y no se lee nada. Matplotlib elige solas unas pocas marcas
    plt.xlabel("Cantidad de datos (n)")
    plt.ylabel("Comparaciones")
    plt.title("Merge Sort: comparaciones vs. tamaño de la entrada")
    plt.legend()
    plt.grid(True, linestyle=":", alpha=0.5)
    plt.tight_layout()
    plt.show()
