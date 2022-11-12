#include <omp.h> 	 //Llamado al encabezado que incluye las funciones de OpenMP
#include <iostream>
#include <iomanip>
#define NUM_HILOS 4   // Declaracion del maximo de hilos a utilizar 

constexpr long nsteps = 10000000; 	// Valor que determina las iteraciones del primer for
double step = 1.0 / double(nsteps);

int main() {
using namespace std;

	double pi = 0.0;
	double ini, tiempo, sum[NUM_HILOS];
	ini = omp_get_wtime(); 				// Funcion que retorna el tiempo transcurrido en segundos
	omp_set_num_threads(NUM_HILOS);		// Funcion que establece el numero de subprocesos en las regiones paralelas, a menos que sea invalidado
										// Por una clasula NUM_THREADS, en este caso NUM_HILOS.

#pragma omp parallel
	{
		int hilo, i;
		hilo = omp_get_thread_num(); 	// Funcion que retorna el numero de subproceso.
		for (i = hilo, sum[hilo] = 0.0; i < nsteps; i = i + NUM_HILOS) {
			double x = (i + 0.5) * step;
			//array de hilos para la suma paralela
			sum[hilo] += 4.0 / (1.0 + x * x);
		}
	}
	for (int i = 0; i < NUM_HILOS; i++) {
		pi += sum[i] * step;     
	}
	tiempo = omp_get_wtime() - ini;				// Se resta el tiempo al momento de finalizar con el tiempo de inicio, para saber cuanto tiempo se tardo.
	cout<< "PI = "<<setprecision(10)<< pi<< endl; 		//Impresion del valor de Pi con el metodo setprecisio(), el cual establece la precision de un punto flotante
	cout<< "Ejecutado en "<<tiempo<< " segundos con " << NUM_HILOS<< " hilos" << endl;
}
