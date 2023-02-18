/*
Este programa es una calculadora de fuerzas y campos eléctricos. El menú le preguntará al usuario si quiere calcular fuerzas 
o campos eléctricos y, luego le preguntará el número de cargas y el punto en el que quiere calcular la fuerza. En caso de 
querer calcular la fuerza que sufre una carga se le preguntará de qué carga quiere calcular la fuerza. 
Por defecto se calculará la fuerza en 3 dimensiones. 
*Este programa calcula por defecto las fuerzas y los campos en 3 dimensiones, si quiere calcular en 1 o 2 dimensiones simplemente 
esceriba 0 en las coordenas z y/o y en ignórelos en el resultado.
*/

#include <iostream>
#include <cmath>
using namespace std;

// Definimos las constantes que vamos a utilizar en las operaciones
const int BASE = 10;
const float K = 8.99 * pow(BASE, 9);

void menu()
{
    cout << "Menú de opciones:" << endl;
    cout << "1. Calcular la fuerza que unas cargas ejercen sobre otra."  << endl;
    cout << "2. Calcular el campo eléctrico en 1 punto. " << endl;
    cout << "3. Calcular el potencial eléctrico. " << endl;
    cout << "4. Calcular la fuerza magnética. " << endl;
    cout << "5. Calcular flujo eléctrico. " << endl;
}

struct Carga
{
    float x;
    float y;
    float z;
    double carga;
};

struct Punto
{
    float x;
    float y;
    float z;
};

struct Vectores
{
    float i;
    float j;
    float k;
    float modulo; // En la función calcularFuerzaMagnética módulo va a significar módulo de velocidad 
};

/*
La siguiente función calcula las coordenadas de las cargas así como el valor de su carga, luego la pasa la información a la función
float vectores() que calculará los vctores de fuerza y los sumará. Por último, le mostrará al usuario la fuerza
*/
void CalculaFuerza()
{
    cout << "Indica cuántas cargas hay en el problema: ";
    int numCargas;
    cin >> numCargas;
    // Creamos numCargas + 1 vectores, siendo ese vector extra la suma de los demás
    Carga cargas[numCargas];
    Vectores vector[numCargas + 1];
    // En un bucle for le preguntamos al usuario que complete la información de cada una de las cargas
    for (int i = 0; i < numCargas; i++)
    {
        cout << "Introduce las coordendas x, y & z de la carga" << i << " seguido de Enter: " << endl;
        cin >> cargas[i].x >> cargas[i].y >> cargas[i].z; 
        cout << "Introduce 3 cifras significativas de la carga seguido de el exponente de base 10: " << endl;
        float cifras;
        int exponente;
        cin >> cifras >> exponente;
        cargas[i].carga = cifras * pow(BASE, exponente);
    }
    // Le pedimos al usuario que eliga la carga de la que quiere conocer la fuerza eléctrica
    cout << "Estas son tus cargas: " << endl;
    for (int i = 0; i < numCargas; i++)
    {
        cout << "Carga " << i << " "; 
    }
    cout << "¿De qué carga quieres conocer la fuerza?" << endl;
    int opcion;
    cin >> opcion;

    // Una vez tenemos la información calculamos en un bucle for cada uno de los vectores de la fuerza eléctrica
    for (int i = 0; i < numCargas; i++)
    {        
        // Forzamos al vectores que va de una carga a ella misma a que tenga el valor 0
        if (i == opcion)
        {
            vector[i].i = 0;
            vector[i].j = 0;
            vector[i].k = 0;
        }
        else 
        {
            vector[i].i = cargas[opcion].x - cargas[i].x;
            vector[i].j = cargas[opcion].y - cargas[i].y;
            vector[i].k = cargas[opcion].z - cargas[i].z;
            vector[i].modulo = sqrt(vector[i].i * vector[i].i + vector[i].j * vector[i].j + vector[i].k * vector[i].k); 
            // Ahora vamos ha hacer unitarios los vectores
            vector[i].i /= vector[i].modulo;
            vector[i].j /= vector[i].modulo;
            vector[i].k /= vector[i].modulo;
            // Ahora vamos a multiplicar los vectores unitarios por el módulo de la fuerza para hallar el vector fuerza
            float fuerza = (cargas[i].carga * cargas[opcion].carga * K) / pow(vector[i].modulo, 2);
            // Finalmente multiplicamos el módulo de la fuerza por el vector unitario
            vector[i].i *= fuerza;
            vector[i].j *= fuerza;
            vector[i].k *= fuerza;
        }        
    }
    
    // Ahora que tenemos todos los vectores los sumamos en un bucle
    // Primero inicializamos el vector suma en 0
    vector[numCargas + 1].i = 0;
    vector[numCargas + 1].j = 0;
    vector[numCargas + 1].k = 0;

    // Sumamos en un bucle for las coordenadas de cada unos de los vectores
    for (int i = 0; i < numCargas; i++)
    {
        vector[numCargas + 1].i += vector[i].i;
        vector[numCargas + 1].j += vector[i].j;
        vector[numCargas + 1].k += vector[i].k;
    }
    // Ahora que mostramos el resultado por pantalla
    cout << "F = " << vector[numCargas + 1].i << "i + " << vector[numCargas + 1].j << "j + " << vector[numCargas + 1].k << "k N/C" << endl;    
}

void calculaCampo()
{
    cout << "Indica cuántas cargas hay en el problema: ";
    int numCargas;
    cin >> numCargas;
    cout << "Introduce las coordenadas del punto en el que quieres calcular el campo seguido de Enter: " << endl;
    Punto punto;
    cin >> punto.x >> punto.y >> punto.z;
    // Creamos numCargas + 1 vectores, siendo ese vector extra la suma de los demás
    Carga cargas[numCargas];
    Vectores vector[numCargas];
    for (int i = 0; i < numCargas; i++)
    {
        cout << "Introduce las coordendas x, y & z de la carga " << i << " seguido de Enter: " << endl;
        cin >> cargas[i].x >> cargas[i].y >> cargas[i].z; 
        cout << "Introduce 3 cifras significativas de la carga seguido de el exponente de base 10: " << endl;
        float cifras;
        int exponente;
        cin >> cifras >> exponente;
        cargas[i].carga = cifras * pow(BASE, exponente);
    }

    // Ahora cremos los vectores del campo, tantos como cargas
    for (int i = 0; i < numCargas; i++)
    {        
        vector[i].i = punto.x - cargas[i].x;
        vector[i].j = punto.y - cargas[i].y;
        vector[i].k = punto.z - cargas[i].z;
        vector[i].modulo = sqrt(vector[i].i * vector[i].i + vector[i].j * vector[i].j + vector[i].k * vector[i].k); 
        // Ahora vamos ha hacer unitarios los vectores
        vector[i].i /= vector[i].modulo;
        vector[i].j /= vector[i].modulo;
        vector[i].k /= vector[i].modulo;
        // Ahora vamos a multiplicar los vectores unitarios por el módulo de la fuerza para hallar el vector fuerza
        float fuerza = (cargas[i].carga * K) / pow(vector[i].modulo, 2);
        // Finalmente multiplicamos el módulo de la fuerza por el vector unitario
        vector[i].i *= fuerza;
        vector[i].j *= fuerza;
        vector[i].k *= fuerza;              
    }

    // Ahora que tenemos todos los vectores los sumamos en un bucle
    // Primero inicializamos el vector suma en 0
    vector[numCargas + 1].i = 0;
    vector[numCargas + 1].j = 0;
    vector[numCargas + 1].k = 0;

    for (int i = 0; i < numCargas; i++)
    {
        vector[numCargas + 1].i += vector[i].i;
        vector[numCargas + 1].j += vector[i].j;
        vector[numCargas + 1].k += vector[i].k;
    }
    // Ahora que mostramos el resultado por pantalla
    cout << "E = " << vector[numCargas + 1].i << "i + " << vector[numCargas + 1].j << "j + " << vector[numCargas + 1].k << "k N/C" << endl;  
}

void calcularPotencialElectrico()
{
    /*
    El potencial eléctrico es la medida asociada con el nivel de energía potencial de un punto en un campo eléctrico1. 
    Se define como el trabajo que un campo electrostático tiene que realizar para mover una carga positiva unitaria de 
    un punto de referencia hasta el punto considerado234. También se puede expresar como la energía potencial eléctrica 
    que adquiere una unidad de carga positiva situada en dicho punto5. El potencial eléctrico se mide en voltios (V), 
    que equivalen a julios por culombio (J/C)4. V = k * q / r
    */
   cout << "Introduce el número de cargas que intervienen en el problema: ";
   int numCargas;
   cin >> numCargas;
   cout << "Introduce las coordenadas del punto en el que quieres calcular el campo seguido de Enter: " << endl;
   Punto punto;
   cin >> punto.x >> punto.y >> punto.z;
   // Creamos numCargas + 1 vectores, siendo ese vector extra la suma de los demás
   Carga cargas[numCargas];
   Vectores vector[numCargas];
   float potencial[numCargas];
   for (int i = 0; i < numCargas; i++)
   {
       cout << "Introduce las coordendas x, y & z de la carga " << i << " seguido de Enter: " << endl;
       cin >> cargas[i].x >> cargas[i].y >> cargas[i].z; 
       cout << "Introduce 3 cifras significativas de la carga seguido de el exponente de base 10: " << endl;
       float cifras;
       int exponente;
       cin >> cifras >> exponente;
       cargas[i].carga = cifras * pow(BASE, exponente);
   }
   // Ahora cremos los vectores del campo, tantos como cargas
   for (int i = 0; i < numCargas; i++)
   {        
       vector[i].i = punto.x - cargas[i].x;
       vector[i].j = punto.y - cargas[i].y;
       vector[i].k = punto.z - cargas[i].z;
       vector[i].modulo = sqrt(vector[i].i * vector[i].i + vector[i].j * vector[i].j + vector[i].k * vector[i].k);     
   }
   // Ahora vamos a multiplicar los vectores unitarios por el módulo de la fuerza para hallar el vector fuerza  
   for (int i = 0; i < numCargas; i++) potencial[i] = (cargas[i].carga * K) / vector[i].modulo;   
   // Finalmente sumamos todos los potenciales
   float Potencial = 0;
   for (int i = 0; i < numCargas; i++) Potencial += potencial[i];
   cout << "V = " << Potencial << " J/C" << endl;   
}

// Esta función al final no la vamos a utilizar 
float seno(Vectores vector[])
{
    /*El ángulo formado por 2 vectores es igual al arcocoseno del producto escalar
    de esos 2 vectores partido del producto del módulo de los 2 vectores. sen(arccos(x)) = sqrt(1 - x^2) atilizamos la función abs() 
    para calcular el valor absoluto*/
    float productoEscalar = abs(vector[0].i * vector[1].i + vector[0].j * vector[1].j + vector[0].k * vector[1].k);
    float moduloVector1 = sqrt(pow(vector[0].i, 2) + pow(vector[0].j, 2) + pow(vector[0].k, 2));
    float moduloVector2 = sqrt(pow(vector[1].i, 2) + pow(vector[1].j, 2) + pow(vector[1].k, 2));
    float x = productoEscalar / (moduloVector1 * moduloVector2);
    return sqrt(1 - pow(x, 2));
}

// Calcula el producto vectorial del vector velocidad y el vector campo magnético
Vectores productoVectorial(Vectores vector[])
{
    // Le pasamos por referencia la variable vector a esta función para calcualr el producto vectorial de los vectores v y B
    vector[3].i = vector[0].j * vector[1].k - vector[0].k * vector[1].j;
    vector[3].j = vector[0].k * vector[1].i - vector[0].i * vector[1].k;
    vector[3].k = vector[0].i * vector[1].j - vector[0].j * vector[1].i;
    
    return vector[3];
}

void calcularFuerzaMagnetica()
{
   // Lo primero es calcular el valor de la carga
   cout << "Introduce 3 cifras significativas de la carga seguido de el exponente de base 10: " << endl;
   float cifras;
   int exponente;
   cin >> cifras >> exponente;
   double carga = cifras * pow(BASE, exponente);
   // El segundo paso es conocer la magnitud de la velocidad y las 3 coordenadas del vector velocidad 
   // Creamos 3 vectores, v, B, (v x B)
   Vectores vector[3];
   cout << "Introduce el módulo de la velocidad a la que viaja la partícula: ";
   cin >> vector[0].modulo;
   cout << "Introduce las coordendas i, j & k del vector velocidad seguido de Enter: " << endl;
   cin >> vector[0].i >> vector[0].j >> vector[0].k;
   cout << "Introduce las coordendas i, j & k del vector campo seguido de Enter: " << endl;
   cin >> vector[1].i >> vector[1].j >> vector[1].k;
   // Ahora pasamos por referencia los 2 vectores para calcular el producto vectorial
   // Ahora llamamos a la función seno() para calcular el valor del seno del ángulo formado entre estos 2 vectores
   // Por último multiplicamos cada coordenada del vector resultante del producto vectorial por la carga
   vector[3] = productoVectorial(vector);
   vector[3].i *= carga;
   vector[3].j *= carga;
   vector[3].k *= carga;
   // Ahora que tenemos todos los valores que necesitamos, imprimimos el resultado en pantalla
   cout << "Fm = " << vector[3].i << "i " << vector[3].j << "j " << vector[3].k << "k N/C" << endl;  
}

void calcularFlujoElectrico()
{
    /*El flujo elétrico es igual al producto escalar del vector campo eléctrico y el vector normal a la superficie,
    viene dado por la siguiente expresión: ΦE = E·S*/
    // En primer lugar creamos una lista con 2 vectores
    Vectores vector[2];
    // Le pedimos al usuario que complete la información del vector campo elétrico
    float modulo;
    cout << "Introduce las coordenadas del vector del campo elétrico seguido de la tecla Enter: " << endl;
    cin >> vector[0].i >> vector[0].j >> vector[0].k;
    cout << "Introduce el módulo del vector del campo elétrico: ";
    cin >> modulo;
    vector[0].i *= modulo;
    vector[0].j *= modulo;
    vector[0].k *= modulo;
    // Ahora completamos la información del segundo vector
    cout << "Introduce las coordenadas del vector del normal a la superficie seguido de la tecla Enter: " << endl;
    cin >> vector[1].i >> vector[1].j >> vector[1].k;
    // Ahora calculamos el producto escalar de estos 2 vectores
    float productoEscalar = vector[0].i * vector[1].i + vector[0].j * vector[1].j + vector[0].k * vector[1].k;
    cout << "ΦE = " << productoEscalar << " N·m²/C" << endl;
}

void calcularCapacidadCondensador()
{
    // Código
}

int main()
{
    menu();
    int option;
    cin >> option;

    switch (option)
    {
    case 1:
    CalculaFuerza();
        break;
    case 2:
    calculaCampo();
        break;
    case 3:
        calcularPotencialElectrico();
        break;
    case 4:
        calcularFuerzaMagnetica();
    case 5:
        calcularFlujoElectrico();
    default:
    cout << "Esa opción no está en el menú, reinicie el programa para volver." << endl;
        break;
    }
}