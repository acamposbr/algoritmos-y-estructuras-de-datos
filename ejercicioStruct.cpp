/**
Mejora de AlumnosDelCurso, usando miembros con valores por default para ahorrar la función de inicialización

--CONSIGNA--
Extender el programa actual para que no se trate de cargar todos los Alumnos y luego se muestren algunos al final, sino que tenga un menú con las siguientes opciones:
    * Cargar un Alumno (si es que hay lugar -- porque hay una posición con un Alumno vacío)
    * Mostrar los Alumnos cargados (no vacíos!)
    * Mostrar los Alumnos en condición de Promoción
    * Buscar un Alumno por legajo y mostrar sus datos
    * Buscar un Alumno por legajo y vaciarlo (poner su legajo en 0!)
*/

#include <iostream>
#include <string>
#include <cstring>

#define N 5
#define LEGAJO_VACIO 0
#define MAX_LEN 40

struct Domicilio
{
    char calle[40];
    int altura;
    int codigoPostal;
};

struct Alumno
{
    char nombreApellido[40];
    int legajo;
    float notaPrimerParcial;
    float notaSegundoParcial;
    Domicilio domicilio;

    Alumno()
    {
        strcpy(nombreApellido, "");
        legajo = LEGAJO_VACIO;
    }
};


using namespace std;

int menu();
void cargarAlumno(Alumno alumnos[]);
void mostrarAlumnos(Alumno alumnos[], int tam);
void alumnosPromocionados(Alumno alumnos[], int tam);
void mostrarAlumnoPorLegajo(Alumno alumnos[], int tam);
void vaciarAlumno(Alumno alumnos[]);
int verificaPosicionLibre(Alumno alumnos[], int tam);
int buscaAlumnoPorLegajo(Alumno alumnos[], int tam, int legajo);
void grabarDatos(Alumno alumnos[], int tam);
void leerDatos(Alumno alumnos[], int tam);

int main()
{
    Alumno alumnos[N];
    leerDatos(alumnos, N); // Carga la data del archivo
    bool salir = 0;

    do
    {
        int opcionDeseada = menu();

        switch (opcionDeseada)
        {
        case 1:
            cargarAlumno(alumnos);
            break;
        case 2:
            mostrarAlumnos(alumnos, N);
            break;
        case 3:
            alumnosPromocionados(alumnos, N);
            break;
        case 4:
            mostrarAlumnoPorLegajo(alumnos, N);
            break;
        case 5:
            vaciarAlumno(alumnos);
            break;
        case 6:
            salir = 1;
            break;
        default:
            system("cls");
            cout << "Opcion invalida!" << endl;
        }
    } while (!salir);
}

int menu()
{
    system("cls");
    int opcion;

    cout << "Menu:" << endl;
    cout << "1. Cargar un Alumno" << endl;
    cout << "2. Mostrar los Alumnos" << endl;
    cout << "3. Mostrar los Alumnos en condicion de promocion" << endl;
    cout << "4. Buscar un Alumno" << endl;
    cout << "5. Vaciar alumno por legajo" << endl;
    cout << "6. Salir del programa" << endl;
    cout << "Digite la opcion: ";
    cin >> opcion;
    return opcion;
}

void cargarAlumno(Alumno alumnos[]){
    system("cls");
    int posicion = verificaPosicionLibre(alumnos, N);

    if (posicion == -1)
    {
        cout << "No fue posible cargar, todas las posiciones estan ocupadas!" << endl;
        return;
    }

    cout << endl << "** Alumno **" << endl;
    cout << "Nombre y apellido: ";
    fflush(stdin);
    cin.getline(alumnos[posicion].nombreApellido, MAX_LEN);
    cout << "Legajo (sin guiones ni puntos): ";
    cin >> alumnos[posicion].legajo;
    cout << "Nota del primer parcial: ";
    cin >> alumnos[posicion].notaPrimerParcial;
    cout << "Nota del segundo parcial: ";
    cin >> alumnos[posicion].notaSegundoParcial;
    cout << "Calle del domicilio: ";
    fflush(stdin);
    cin.getline(alumnos[posicion].domicilio.calle, MAX_LEN);
    cout << "Altura del domicilio: ";
    cin >> alumnos[posicion].domicilio.altura;
    cout << "Codigo postal: ";
    cin >> alumnos[posicion].domicilio.codigoPostal;

    grabarDatos(alumnos, N);
}

void mostrarAlumnos(Alumno alumnos[], int tam)
{
    system("cls");
    int contador = 0;

    for (int i = 1; i <= tam; i++){
        if (alumnos[i-1].legajo != 0){
            cout << "Alumno: ";
            cout << alumnos[i-1].nombreApellido;
            cout << " - Legajo: " << alumnos[i - 1].legajo << endl;
            contador++;
        }
    }

    if(!contador)
        cout << "No hay alumnos cargados! " << endl;
    system("pause");
}

void alumnosPromocionados(Alumno alumnos[], int tam)
{
    system("cls");
    for (int i = 0; i < tam; i++){
        if(alumnos[i].notaPrimerParcial >= 8 && alumnos[i].notaSegundoParcial >= 8){
            cout << "Aluno: " << alumnos[i].nombreApellido << " apto a promocionar!" << endl;
        }
    }
    system("pause");
}

void mostrarAlumnoPorLegajo(Alumno alumnos[], int tam)
{
    system("cls");
    int legajo, posicionAlumno;
    cout << "Digite el legajo del alumno: ";
    cin >> legajo;

    posicionAlumno = buscaAlumnoPorLegajo(alumnos, N, legajo);
    if(posicionAlumno == -1){
        cout << "Alumno no encontrado! " << endl;
    }

    else{
        cout << "*** Alumno ***" << endl;
        cout << "Nombre: " << alumnos[posicionAlumno].nombreApellido << endl;
        cout << "Legajo: " <<alumnos[posicionAlumno].legajo << endl;
        cout << endl << "Domicilio: ";
        cout << alumnos[posicionAlumno].domicilio.calle << " ";
        cout << alumnos[posicionAlumno].domicilio.altura << ", ";
        cout << alumnos[posicionAlumno].domicilio.codigoPostal << endl;
    }
    system("pause");
}

void vaciarAlumno(Alumno alumnos[])
{
    system("cls");
    int legajo, posicionAlumno;
    cout << "Digite el legajo del alumno a vaciar: ";
    cin >> legajo;

    posicionAlumno = buscaAlumnoPorLegajo(alumnos, N, legajo);

    if (posicionAlumno == -1)
        cout << "Alumno no encontrado! " << endl;
    else{
        alumnos[posicionAlumno].legajo = 0;
        cout << "*** Alumno vaciado !!! ***" << endl;
    }
}

int verificaPosicionLibre(Alumno alumnos[], int tam)
{
    for (int i = 0; i < tam; i++)
    {
        if (!alumnos[i].legajo)
            return i;
    }

    return -1;
}

int buscaAlumnoPorLegajo(Alumno alumnos[], int tam, int legajo){
    for (int i = 0; i < tam; i++)
    {
        if (alumnos[i].legajo == legajo)
            return i;
    }

    return -1;
}

void grabarDatos(Alumno alumnos[], int tam){
    FILE* f = fopen("data", "ab");

    if (f == NULL){
        cout << "No se puede crear el archivo!" << endl;
        return;
    }

    for (int i = 0; i < tam; i++){
        fwrite(&alumnos[i], sizeof(Alumno[i]), 1, f);
    }
    fclose(f);
}

void leerDatos(Alumno alumnos[], int tam){
    FILE *f = fopen("data", "rb");

    if (f == NULL){
        cout << "No se pudo leer el archivo!" << endl;
        return;
    }

    for (int i = 0; i < tam; i++){
        fread(&alumnos[i], sizeof(alumnos[i]), 1, f);
    }
    fclose(f);

    cout << "Se ha leido el archivo!" << endl;
}
