#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Definir constantes para los valores maximo y minimo de los pesos
#define MAX_VALUE 1.0
#define MIN_VALUE 0.0

#define input_neurons 5
#define hidden_neurons 3
#define output_layer 1

// Crear funciones para los pesos 
void weight(double w[][input_neurons]){
    srand(time(0));
    // Iterar sobre las filas y columnas de la matriz de pesos
    for (int i = 0, j = 0; i < hidden_neurons && j < input_neurons; ++i, ++j) {
        // Generar un número aleatorio entre MIN_VALUE y MAX_VALUE y asignarlo a la matriz de pesos
        double r = ((double) rand() / (double) RAND_MAX) * (MAX_VALUE - MIN_VALUE) + MIN_VALUE;
        w[i][j] = r;   
    }

    }   

void weight_transpose(double w[][input_neurons], double transpose[][hidden_neurons]) {
    for (int i = 0; i < input_neurons; i++) {
        for (int j = 0; j < hidden_neurons; j++) {
            transpose[i][j] = w[j][i];
        }
    }
}

void bias(double b[]){
    srand(time(0));
    // Iterate over the elements of the bias vector
    for (int i = 0; i < hidden_neurons; ++i) {
        // Generate a random number between MIN_VALUE and MAX_VALUE and assign it to the bias vector
        double r = ((double) rand() / (double) RAND_MAX) * (MAX_VALUE - MIN_VALUE) + MIN_VALUE;
        b[i] = r;  
        
    }
        
}

// Crear las funciones para los calculos de a y z
void Z(double num[][3], double z_result[][hidden_neurons], int size, double transpose[][hidden_neurons], double b[]) {
    double sum;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < hidden_neurons; j++) {
            sum = 0;
            for (int k = 0; k < input_neurons; k++) {
                z_result[i][j] = num[i][k] * transpose[k][j] + b[j];
                 
            }
    
           
        }
       
    }
}

void output_relu(double z_result[][hidden_neurons], int size, double relu_result[]) {
    for (int i = 0; i < size; i++) {
        relu_result[i] = fmax(0.0, z_result[0][i]);
        
    }
   
}

void output_sigmoid(double relu_result[], double output_result[], int size) { 
    for (int i = 0; i < size; ++i) {
        output_result[i] = 1 / (1 + exp(-relu_result[i])); 
        printf("%f ", output_result[i]);
    }
    printf("\n");
}

void loss_function(double output_result[], double predictions[], int size, double result[]) {
    for (int i = 0; i < size; ++i) {
        double intermediate_result = -(output_result[i]*log(predictions[i]) + (1-output_result[i])*log(1-predictions[i]));
        result[i] = intermediate_result;
        printf("%f ", result[i]);
    }
}

int main() {
    double num[5][3] = {{1.0, 2.0, 3.0},
                        {4.0, 5.0, 6.0},
                        {7.0, 8.0, 9.0},
                        {10.0, 11.0, 12.0},
                        {13.0, 14.0, 15.0}};
    double predictions[5] = {1.0, 1.0, 0.0, 0.0, 1.0};
    double w[hidden_neurons][input_neurons];
    double b[hidden_neurons];
    double z_result[5][hidden_neurons];
    double relu_result[hidden_neurons];
    double output_result[output_layer];
    double transpose[input_neurons][hidden_neurons];
    double result[5];

    weight(w);
    weight_transpose(w, transpose);
    bias(b);
    Z(num, z_result, 5, transpose, b);
    output_relu(z_result, hidden_neurons, relu_result);
    output_sigmoid(relu_result, output_result, 5);
    loss_function(output_result, predictions, 5, result);

    return 0;
}