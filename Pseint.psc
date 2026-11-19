Algoritmo Pseint

	// Paso 1: pedir la cantidad de filas y columnas (menor a 20)
	Definir filas Como Entero
	Definir columnas Como Entero
	Definir i, j Como Entero

	Repetir
		Escribir "Cantidad de filas (Máximo 20): " Sin Saltar
		Leer filas
		Si filas > 20 O filas < 1 Entonces
			Escribir "No se puede: las filas deben estar entre 1 y 20. Intenta de nuevo."
		FinSi
	Hasta Que filas >= 1 Y filas <= 20

	Repetir
		Escribir "Cantidad de columnas (Máximo 20): " Sin Saltar
		Leer columnas
		Si columnas > 20 O columnas < 1 Entonces
			Escribir "No se puede: las columnas deben estar entre 1 y 20. Intenta de nuevo."
		FinSi
	Hasta Que columnas >= 1 Y columnas <= 20

	// Paso 2: pedir los datos de la matriz
	Definir matriz Como Real
	Dimension matriz[filas, columnas]
	Para i <- 1 Hasta filas Hacer
		Para j <- 1 Hasta columnas Hacer
			Escribir "Elemento [", i, "][", j, "]: " Sin Saltar
			Leer matriz[i, j]
		FinPara
	FinPara

	// Paso 3: mostrar la matriz original (antes de modificarla)
	Escribir ""
	Escribir "Matriz original:"
	Para i <- 1 Hasta filas Hacer
		Para j <- 1 Hasta columnas Hacer
			Escribir "    ", matriz[i, j] Sin Saltar
		FinPara
		Escribir ""
	FinPara

	// Paso 4: calcular la raíz de cada elemento
	raiz_matriz(filas, columnas, matriz)

	// Paso 5: mostrar la matriz raíz
	Escribir ""
	Escribir "Matriz raiz cuadrada:"
	Para i <- 1 Hasta filas Hacer
		Para j <- 1 Hasta columnas Hacer
			Escribir "    ", matriz[i, j] Sin Saltar
		FinPara
		Escribir ""
	FinPara

FinAlgoritmo

Funcion raiz_matriz(filas, columnas, matriz)
	Definir i, j Como Entero
	Definir margen, x, estimacion, cuadrado, cociente Como Real

	// variables para la estimación
	// no se puede usar sqrt para la raíz
	margen <- 0.0001

	Para i <- 1 Hasta filas Hacer
		Para j <- 1 Hasta columnas Hacer
			// Paso 1: tomar el número y dejarlo positivo
			x <- matriz[i, j]
			Si x < 0 Entonces
				x <- -x
			FinSi

			// Paso 2: empezar con una estimación
			estimacion <- 1
			// Paso 3: mejorar la estimación hasta que su cuadrado esté cerca de x
			cuadrado <- estimacion * estimacion
			Mientras (cuadrado - x > margen) O (x - cuadrado > margen) Hacer
				cociente <- x / estimacion
				estimacion <- (cociente + estimacion) / 2.0
				cuadrado <- estimacion * estimacion
			FinMientras
			// Paso 4: guardar el resultado en la matriz
			matriz[i, j] <- estimacion
		FinPara
	FinPara
FinFuncion
