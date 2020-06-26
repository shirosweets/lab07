# Makefile del Laboratorio 7

C = gcc
TARGET = knapsack
# CFLAGS sirve para usarlo como $(CFLAGS) para usarlo como una variable
# y no repetir todo el tiempo escrito todo eso
CFLAGS = -Werror -Wall -Wextra -pedantic -std=c99 -g
SOURCES = $(wildcard *.c)
HEADERS = $(wildcard *.h)
OBJECTS = $(SOURCES:.c=.o)
VFLAGS = --leak-check=full --show-reachable=yes
AUTOR = Valentina Solange Vispo
NUM_LAB = 7
MAT = Algoritmos y Estructura de Datos II - FAMAF - 2020

.PHONY: clean

$(TARGET):
	$(C) $(CFLAGS) -c $(SOURCES)
	$(C) $(CFLAGS) -o $(TARGET) $(OBJECTS)
	
valgrind: dictionary
	valgrind $(VFLAGS) ./knapsack

clean : # Se usa con $ make clean
	rm -f $(TARGET) $(OBJECTS)

autor: # Imprime el nombre del autor # Se usa con $ make autor # @echo silencia el echo en consola
	@echo $(AUTOR)

lab: # Imprime el número del laboratorio # Se usa con $ make lab
	@echo $(NUM_LAB)

materia: # Imprime el nombre de la materia, junto con su facultad y año # Se usa con $ make materia
	@echo $(MAT)