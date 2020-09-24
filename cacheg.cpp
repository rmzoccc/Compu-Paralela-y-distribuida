#include <iostream>
#include<stdlib.h>
#include<time.h>
#include <ctime>

#define MAX 2000

using namespace std;



void random(int ** & matriz_a){

	for(int i=0;i<MAX;i++)
	{
		for(int j=0;j<MAX;j++){
			int num=1+rand()%(101-1);
			matriz_a[i][j]=num;

		}
	}
}

void mostrar_matris(int ** & matriz_a){
	for(int i=0;i<MAX;i++)
	{
		for(int j=0;j<MAX;j++){
			cout<<matriz_a[i][j]<<" ";
		}
		cout<<endl;
	}
}


void multiplicacion(int ** & matriz_result,int ** matriz_a,int ** matriz_b){
	for(int i=0;i<MAX;i++){
		for(int j=0;j<MAX;j++){
			for(int k=0;k<MAX;k++){
				matriz_result[i][j]+=matriz_a[i][k]*matriz_b[k][j];
			}
			//cout<<"multiplicacion sub deveras"<<matriz_result[i][j]<<endl;
		}
	}
}

void multiplicacionbloques(int ** A,int ** B,int **C, int n)
    {

        const int BLOCK = 10;
        for (int I = 0; I < n; I += BLOCK) {//completa las filas a llenarse
            for (int J = 0; J < n; J += BLOCK) {//completa la columna
                for (int K = 0; K < n; K += BLOCK) {//usada para multiplicar con los cuadros pequeños
                	//LO QUE HACE ES COMPLETAR LA MULTIPLICACION FILA COLUMNA

                    for (int i = I; i < I + BLOCK && i < n; ++i) {
                        for (int j = J; j < J + BLOCK &&  j< n; ++j) {
                        	int suma=0;

                            for (int k= K; k <K+BLOCK && k<n ; ++k) {
                                suma=suma+A[i][k]*B[k][j];
                            }
                            C[i][j] = C[i][j] + suma;
                        }
                    }
                }
            }
        }
    }

void bucles(){


	///Bucles ejercicio1

	//int fil, col;
	//fil=100;
	//col=100;
	unsigned t0,t1;
	srand(time(NULL));
	int **matriz_a=new int*[MAX];
	for(int i=0;i<MAX;i++){
		matriz_a[i]=new int [MAX];
	}

	random(matriz_a);
	//mostrar_matris(matriz_a);

	int x[MAX];
	int y[MAX];
	int num;

	for(int j=0;j<MAX;j++){

		num=1+rand()%(101-1);
		x[j]=num;
	}

	for(int j=0;j<MAX;j++){
		num=1+rand()%(101-1);
		y[j]=num;
	}

	t0=clock();
	//mejor
	for(int i=0;i<MAX;i++){
		for(int j=0;j<MAX;j++){
			y[i]+=matriz_a[i][j]*x[j];
		}
	}
	t1=clock();

	double time = (double(t1-t0)/CLOCKS_PER_SEC);
	cout << "Tiempo de ejecución del primer for: " << time << endl;



	//esto es el peor caso por
	//cache de espacial y temporal
	t0=clock();
	for(int j=0;j<MAX;j++){
		for(int i=0;i<MAX;i++){
			y[i]+=matriz_a[i][j]*x[j];
		}
	}
	t1=clock();

	time = (double(t1-t0)/CLOCKS_PER_SEC);
	cout << "Tiempo de ejecución del segundo for: " << time << endl;
}

int main(){
	//bucles();
	//Multiplicación clasica de matrices

	unsigned t0,t1;


	int **matriz_a=new int*[MAX];
	for(int i=0;i<MAX;i++){
		matriz_a[i]=new int [MAX];
	}

	int **matriz_b=new int*[MAX];
	for(int i=0;i<MAX;i++){
		matriz_b[i]=new int [MAX];
	}


	int **resultado=new int*[MAX];
	for(int i=0;i<MAX;i++){
		resultado[i]=new int [MAX];
	}

	for(int i=0;i<MAX;i++){
		for(int j=0;j<MAX;j++){
			resultado[i][j]=0;
		}
	}

	random(matriz_a);
	random(matriz_b);

	t0=clock();
	multiplicacionbloques(matriz_a,matriz_b,resultado,MAX);
	t1=clock();
	double time = (double(t1-t0)/CLOCKS_PER_SEC);
	cout << "Ejecucion mediante multiplicacion por bloques " << time << endl;
	//cout<<"Mostrando la matriz A"<<endl;
	//mostrar_matris(matriz_a);
	//cout<<"Mostrando la matriz B"<<endl;
	//mostrar_matris(matriz_b);

	//mostrar_matris(resultado,fil,col);
	/*
	for(int i=0;i<MAX;i++){
		for(int j=0;j<MAX;j++){
			resultado[i][j]=0;
		}
	}
	//cout<<"Mostrando la resultado"<<endl;
	//mostrar_matris(resultado,fil,col);

	t0=clock();
	multiplicacion(resultado,matriz_a,matriz_b);
	t1=clock();
	double time = (double(t1-t0)/CLOCKS_PER_SEC);
	cout << "Ejecucion mediante multiplicacion tipica " << time << endl;

	//mostrar_matris(resultado,fil,col);

	//cout<<"resultado"<<endl;
	*/
	return 0;
}
