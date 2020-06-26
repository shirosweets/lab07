#include <stdbool.h> // Bool
#include <stdio.h> /* printf()...           */
#include <stdlib.h> // Calloc, malloc, free...

#include "knapsack.h"

/** Función máximo
* @param x Primer valor.
* @param y Segundo valor.
* @return El valor máximo entre los dos valores.
**/
static value_t funcion_max(value_t x, value_t y){
    value_t max;
    if(x>y){
        max = x;
    }
    else{
        max = y;
    }
    return max;
}

value_t knapsack_backtracking(item_t* items,
                              unsigned int array_length, weight_t max_weight){
    value_t valor_max; // Valor máximo que se puede alcanzar seleccionando ​items​ del arreglo sin sobrepasar la capacidad de la mochila
    if(max_weight==0 || array_length ==0){ // Caso base k=0 (el peso máximo es 0) y Caso inductivo con n=0 (Si el tamaño del arreglo es 0)
        valor_max = 0; // Retorno 0
    }
    // Caso inductivo k>=1 (el peso es mayor que 0)
    else{ // Caso n>0 (Si el tamaño del arreglo no es 0)
        // Sigo con el caso inductivo, aplico recursión
        if(item_weight(items[array_length-1])>max_weight){
            valor_max = knapsack_backtracking(items, array_length-1, max_weight);
        }
        else{
            valor_max = funcion_max(knapsack_backtracking(items, array_length-1, max_weight),  item_value(items[array_length-1]) + knapsack_backtracking(items, array_length-1, (max_weight-item_weight(items[array_length-1]) ) ) );
        }
    }
    return valor_max; // Retorno el valor máximo
}

value_t knapsack_dynamic(item_t* items,
                         unsigned array_length, weight_t max_weight){
    value_t valor_max; // Valor máximo que se puede alcanzar seleccionando ​items​ del arreglo sin sobrepasar la capacidad de la mochila
    // Inicializo la tabla
    value_t** table = calloc((array_length+1u), sizeof(value_t*)); // Empieza en 0
    for (unsigned int i = 0u; i <= array_length; i++){
        table[i] = calloc((max_weight+1u), sizeof(value_t));
    }
    // Lleno la tabla, debo recorrerla
    for(unsigned int i=1u; i<array_length+1; i++){
        for(unsigned int j=1u; j<max_weight+1; j++){
            weight_t w = item_weight(items[i-1]);
            value_t v = item_value(items[i-1]);
            if(w>j){
                table[i][j] = table[i-1][j];
            }
            else{
                table[i][j] = funcion_max( table[i-1][j], v + table[i-1][j-w] );
            }
        }
    }
    valor_max = table[array_length][max_weight]; // Asigno el valor máximo
    // Inicio de liberar la tabla
    for (unsigned int i=0u; i<array_length+1; i++){
        free(table[i]);
        table[i] = NULL;
    }
    free(table);
    table = NULL;
    // Fin de liberar la tabla
    return valor_max; // Retorno el valor máximo
}

value_t knapsack_dynamic_selection(item_t* items, bool* selected,
                                   unsigned int array_length,
                                   weight_t max_weight){
    // El arreglo de booleanos​ se utiliza para indicar cuáles son los ​items​ del arreglo que fueron seleccionados
    // para colocarse en la mochila.
    value_t valor_max; // Valor máximo que se puede alcanzar seleccionando ​items​ del arreglo sin sobrepasar la capacidad de la mochila
    // Inicializo la tabla
    value_t** table = calloc((array_length+1u), sizeof(value_t*)); // Empieza en 0
    for (unsigned int i = 0u; i <= array_length; i++){
        table[i] = calloc((max_weight+1u), sizeof(value_t));
    }
    // Lleno la tabla, debo recorrerla
    for(unsigned int i=1u; i<array_length+1; i++){
        for(unsigned int j=1u; j<max_weight+1; j++){
            weight_t w = item_weight(items[i-1]);
            value_t v = item_value(items[i-1]);
            if(w>j){
                table[i][j] = table[i-1][j];
            }
            else{
                table[i][j] = funcion_max( table[i-1][j], v + table[i-1][j-w] );
            }
        }
    }
    value_t r = array_length; // Auxiliar para el tamaño máximo del arreglo (sufre modificaciones)
    value_t s = max_weight; // Auxiliar para el peso máximo de la mochila (sufre modificaciones)
    while(table[r][s]>0){
        if(table[r][s]==table[r-1][s]){
            selected[r-1] = false;
        }
        else{
            selected[r-1] = true;
            s = s - item_weight(items[r-1]);
        }
        r = r-1;
    }
    valor_max = table[array_length][max_weight]; // Asigno el valor máximo
    // Inicio de liberar la tabla
    for (unsigned int i=0u; i<array_length+1; i++){
        free(table[i]);
        table[i] = NULL;
    }
    free(table);
    table = NULL;
    // Fin de liberar la tabla
    return valor_max; // Retorno el valor máximo
}