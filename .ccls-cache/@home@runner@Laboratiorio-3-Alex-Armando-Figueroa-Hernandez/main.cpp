/*
3.a Cree un proyecto en Dev C.

Dicho programa debe pedir lo siguiente:
Resolución (8, 10 o 12 bits).
Frecuencia de muestreo.
Cantidad de canales a leer.
Definir cuales canales se va a leer (los canales son AN1, …, AN32).
La configuración se hace solo con una lectura para cada canal.
Una vez configurado el canal ADC, se puede realizar lo siguiente:
  - Hacer una lectura de un canal del ADC. Este punto se hace colocando un dato
en consola, el cual se introduce con valores de 0 a 3.3 Volts. Una vez que se
introduce dicho valor, se genera el dato que se convirtió con base en la
resolución.
  - Imprimir el valor de la lectura del ADC.
  - Si se configuró hacer la lectura con más de un canal, se hace la lectura de
los canales activados en la configuración.
  - Imprimir el valor de las lecturas de los canales del ADC activos.

3.b Cree un repositorio en GIT para el control de versiones de su proyecto y
genere al menos un commit (versión inicial).
*/

#include <iostream>
#include <math.h>
#include <stdlib.h>
#define ANMAX 32 // número máximo de canales
using namespace std;

class ADC {
private:
  int Resolucion;
  float Vref;
  float voltaje[ANMAX];
  static int n_can; // Cantidad de canales a leer.
  int num;
  int fo[ANMAX]; // Definir cuales canales se va a leer (los canales son AN1, …,
                 // AN32).
  int valor[ANMAX];

public:
  ADC();
  void capturaDatos();
  void config();
  void muestraDatos();
  void portada();
  void selector(ADC);
  void capturaDatosOpcion();
};

/************************************************
    DECLARACION DEL CONSTRUCTOR (INICIALIZA ATRIBUTOS DEL OBJETO)
************************************************/
ADC::ADC() {
  system("cls");
  std::cout << std::endl << "Se ha creado un objeto ADC" << endl;
  this->Resolucion = 0;
  this->Vref = 0;
}

/************************************************
    METODOS
************************************************/
void ADC::capturaDatos() {
  int i = 0;
  cout << endl << "** Introduce Datos **" << endl;
  cout << "Ingrese Resolucion (8,12,14 bits): ";
  cin >> Resolucion;
  // validacion de resolucion
  while (Resolucion != 8 && Resolucion != 12 && Resolucion != 14) {
    cout << "Resolucion no valida!" << endl;
    cout << "Ingrese Resolucion (8,12,14 bits): ";
    cin >> Resolucion;
  }
  cout << "Ingrese Voltaje Ref: ";
  cin >> Vref;
  cout << "Cantidad de canales a leer: ";
  cin >> n_can;
  while (n_can < 1 || n_can > 32) { // validacion  de numero de canales
    cout << "Cantidad no valida! Rango [1-32]" << endl;
    cout << "Cantidad de canales a leer: ";
    cin >> n_can;
  }

  for (i; i < n_can; i++) {
    cout << "Frecuencia de muestreo del canal: ";
    cin >> fo[i];
  }
}

void ADC::config() {
  int i = 0;
  for (i; i < n_can; i++) {
    cout << endl << "Canal N" << fo[i] << endl;
    cout << "Voltaje: ";
    cin >> voltaje[i];
    while (voltaje[i] < 0 || voltaje[i] > 3.3) { // validacion de voltaje
      cout << "Valor de voltaje no valido! Rango [0-3.3]" << endl;
      cout << "Voltaje: ";
      cin >> voltaje[i];
    }
    valor[i] = (pow(2, Resolucion) * voltaje[i]) / Vref; // formula
  }
}

void ADC::muestraDatos() {
  int i = 0;
  system("cls");
  cout << endl << "** Imprimiendo Datos **" << endl;

  cout << "Resolucion: " << Resolucion << "BITS" << endl;
  cout << "Voltaje ref: " << Vref << endl;
  cout << "Cantidad de canales: " << n_can << endl;
  for (i; i < n_can; i++) {
    cout << endl << "Frecuencia de muestreo del canal" << fo[i] << endl;
    cout << "Voltaje: " << voltaje[i] << endl;
    cout << "Salida: " << valor[i] << endl;
  }
}

/************************************************
    Inicializacion de cuenta
************************************************/
int ADC::n_can = 0;
/************************************************
   MAIN
************************************************/
int main(int argc, char **argv) {

  ADC var;
  var.portada();
  cout << "Selecciona un opcion 3 o 4: " << endl;
  var.selector(var);
  return 0;
}

void ADC::portada() { cout << "Laboratorio 3" << endl; }

/*
4. Cambie el programa para implementar esta parte con polimorfismo y con
herencia. (3 puntos)

nota: Deberá añadir un menú al principio del programa para  seleccionar esta
opción o la del punto3.

Suponga ahora que la configuración de la frecuencia de muestreo se realiza de la
siguiente manera: Fs = f_osc / ack. Donde fosc es de 8 MHz y ack es un factor
que tiene valores de 2, 4, 8, 16, 32 y 64.
*/
void ADC::capturaDatosOpcion() {
  float fs;
  int i = 0, f_osc = 8, ack, selector;
  cout << endl << "** Introduce Datos **" << endl;
  cout << "Ingrese Resolucion (8,12,14 bits): ";
  cin >> Resolucion;
  // validacion de resolucion
  while (Resolucion != 8 && Resolucion != 12 && Resolucion != 14) {
    cout << "Resolucion no valida!" << endl;
    cout << "Ingrese Resolucion (8,12,14 bits): ";
    cin >> Resolucion;
  }
  cout << "Ingrese Voltaje Ref: ";
  cin >> Vref;
  cout << "Cantidad de canales a leer: ";
  cin >> n_can;
  while (n_can < 1 || n_can > 32) { // validacion  de numero de canales
    cout << "Cantidad no valida! Rango [1-32]" << endl;
    cout << "Cantidad de canales a leer: ";
    cin >> n_can;
  }

  for (i; i < n_can; i++) {
    cout << "Frecuencia de muestreo del canal: " << endl;
    cout << "Seleccione divisor de reloj" << endl;
    cout << "2" << endl;
    cout << "4" << endl;
    cout << "8" << endl;
    cout << "16" << endl;
    cout << "32" << endl;
    cout << "64" << endl;
    cin >> ack;
    switch (ack) {
    case 2:
      fs = f_osc / ack;
      break;
    case 4:
      fs = f_osc / ack;
      break;
    case 8:
      fs = f_osc / ack;
      break;
    case 16:
      fs = f_osc / ack;
      break;
    case 32:
      fs = f_osc / ack;
      break;
    case 64:
      fs = f_osc / ack;
      break;
    default:
      cout << "Opcion de divisor no disponible, ack = 2" << endl;
      ack = 2;
      fs = f_osc / ack;
      break;
    }
  }
}

void ADC::selector(ADC var) {
  int s;
  cin >> s;
  switch (s) {
  case 3:
    var.capturaDatos();
    var.config();
    var.muestraDatos();
    break;
  case 4:
    var.capturaDatosOpcion();
    var.config();
    var.muestraDatos();
    break;
  default:
    cout << "Opcion no disponible" << endl;
    break;
  }
}