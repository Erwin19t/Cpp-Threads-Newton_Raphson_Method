#include <iostream>
#include <mutex>
#include <thread>
#include <math.h>

using namespace std;

double Newton_Raphson(double, mutex*);		//Prototipo de funcion

int main()
{
	mutex m;
	
	thread t1(Newton_Raphson, -2.0, &m);
	thread t2(Newton_Raphson, -2.0, &m);
	thread t3(Newton_Raphson, -1.5, &m);
	thread t4(Newton_Raphson, -1.5, &m);
   	thread t5(Newton_Raphson, 1.0, &m);				
	thread t6(Newton_Raphson, 1.0, &m);
	
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	
	return 0;
}

double Newton_Raphson(double Xi, mutex *m)
{
	unsigned short int Counter = 0;	//Contador de iteraciones
	double Xi_aux;			//Variable Auxiliar
	double X_ant = 0.0; 		//Solucion anterior
	double Fx, D_Fx;		//Variables para F(Xi) y F'(Xi)
	double Error = 100.0;		//Error = abs(X_i - X_(i-1))
	
	Xi_aux = Xi;
	
	while(Error > pow(10,-9))
	{	
		Fx = pow(Xi_aux,7) - 2*pow(Xi_aux,5) + 4*pow(Xi_aux,4) - 3*pow(Xi_aux,2) - 1;//F(Xi)
		D_Fx = 7*pow(Xi_aux,6) - 10*pow(Xi_aux,4) + 16*pow(Xi_aux,3) - 6*Xi_aux;//F'(Xi)
		Xi_aux = Xi_aux - (Fx/D_Fx);	//Raiz estimada
		Error = abs(Xi_aux - X_ant);	//Calculo de Error
		X_ant = Xi_aux;			//Se actualiza la solucion anterior
		Counter++;			//Se aumenta el contador de iteraciones
	}
	m->lock();
	cout<<"La raiz estimada es:"<<Xi_aux<<endl;
	cout<<"La solucion se encontro en la iteracion: "<<Counter<<endl<<endl;
	m->unlock();
	
	return Xi_aux;
}
