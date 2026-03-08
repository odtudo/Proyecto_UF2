#include <iostream>
#include <cstdlib>
#include <ctime>
#define MAX_ESTUDIANTES 10



using namespace std;


class Usuario {

public:
    int id;
    string nombre;
    string apellido;
    string rol;



    Usuario() {

        id = -1;
        nombre = "";
        apellido = "";
        rol = "";
    }
    Usuario(int i, string n, string a, string r) {

        id = i;
        nombre = n;
        apellido = a;
        rol = r;
    };

};


class Documento {


    public:

    string nombreArchivo;
    string contenido;

};

class Mochila {

public:
    Documento* documento[10];
    int numeroDeDocumentos;

  Mochila() {

      numeroDeDocumentos = 0;

  }


};



class Profesor {

    public:

    int idUsuario;

    int estudiantes[MAX_ESTUDIANTES];
    int numeroDeEstudiantes = 0;


    Profesor() {

        idUsuario = -1;
        numeroDeEstudiantes = 0;
    }

};

void menuEstudiantes();
void menuProfesor();
void menuAdministrador();
void calculadora();
double** crearMatriz(int filas, int columnas);
void llenarMatriz(double** matriz, int filas, int columnas);
void mostrarMatriz(double** matriz, int filas, int columnas);
double** sumarMatrices(double** A, double** B, int filas, int columnas);
void liberarMatriz(double** matriz, int filas);
double** restarMatrices(double** A, double** B, int filas, int columnas);
double** multiplicarMatrices(double** A, double** B, int filas, int columnas);


int siguienteID =1;

Usuario* usuarios[100];
int numeroDeUsuarios = 0;

Profesor* profesores[100];
int numeroDeProfesores = 0;

Mochila* mochilas[100];

int main() {

    srand(time(NULL));
    int opcion = 0;
    do {
        printf("== Sistema de Asignacion de roles ==\n");
        printf("Que rol tienes en la organizacion?\n");
        printf("1. Estudiante\n");
        printf("2. Profesor\n");
        printf("3. Administrador\n");
        printf("4. Calculadora\n");
        printf("5. Salir\n");

        cin >> opcion;
        switch (opcion) {

            case 1: {
                menuEstudiantes();
                break;
            }
            case 2: {
                menuProfesor();
                break;
            }
            case 3: {
                menuAdministrador();
                break;
            }
            case 4: {
                calculadora();
                break;
            }
        }
    }while (opcion != 5);

}


void menuEstudiantes() {

    int opcion =0;
    do {

        printf("== Menu de Estudiantes ==\n");
        printf("1. Subir Documento\n");
        printf("2. Ver Documnetos\n");
        printf("3. Ver contenido de Documentos\n");
        printf("4. Salir");
        cin >> opcion;


    }while (opcion != 4);


};
void menuProfesor() {

    int ID;
    bool existe = false;

    Profesor* profesorAhora;

    printf("== Menu de Profesor ==\n");
    printf("Escribe tu ID de profesor: ");
    cin >> ID;

        for (int i =0; i<numeroDeProfesores; i++) {

            if (profesores[i]->idUsuario == ID) {

                profesorAhora = profesores[i];
                existe = true;
                break;
            }
        }

    if (existe == false) {

        printf("Profesor no encontrado\n");
        return;
    }

    int opcion;
    do {

        printf("== Menu de profesores ==\n");
        printf("1. Añadir Estudiante\n");
        printf("2. Ver estudiantes\n");
        printf("3. Numero de inscritos\n");
        printf("4. Salir\n");
        cin >> opcion;

        switch (opcion) {

            case 1: {

                int idEstudiante = 0;
                bool existe = false;

                printf("Escribe el ID del estudiante: ");
                cin >> idEstudiante;

                for (int i = 0; i < numeroDeUsuarios && existe == false; i++) {

                    if (usuarios[i]->id == idEstudiante && usuarios[i]->rol == "estudiante") {

                        existe = true;
                    }
                }

                if (existe == true) {

                    bool duplicado = false;

                    for (int i = 0; i < profesorAhora->numeroDeEstudiantes && duplicado == false; i++) {

                        if (profesorAhora->estudiantes[i] == idEstudiante) {

                            duplicado = true;
                        }
                    }

                    if (duplicado == true) {

                        printf("Ese estudiante ya esta en la clase\n");
                    }
                    else {

                        if (profesorAhora->numeroDeEstudiantes < MAX_ESTUDIANTES) {

                            profesorAhora->estudiantes[profesorAhora->numeroDeEstudiantes] = idEstudiante;
                            profesorAhora->numeroDeEstudiantes++;

                            printf("Estudiante añadido\n");
                        }
                        else {

                            printf("La clase esta llena\n");
                        }
                    }
                }
                else {

                    printf("Estudiante no encontrado\n");
                }

                break;
            }
            case 2: {

                for (int i = 0; i < profesorAhora->numeroDeEstudiantes; i++) {

                    int id = profesorAhora->estudiantes[i];

                    for (int j = 0; j < numeroDeUsuarios; j++) {

                        if (usuarios[j]->id == id) {

                            cout << usuarios[j]->nombre << " "
                                 << usuarios[j]->apellido << endl;
                        }
                    }
                }

                break;
            }
            case 3: {

                printf("Numero de estudiantes inscritos: %d ",profesorAhora->numeroDeEstudiantes);
                break;
            }

        }
    }while (opcion != 4);



}
void menuAdministrador() {

    int opcion = 0;
    do {
        printf("== Menu de Administradores ==\n");
        printf("1. Crear Usuario\n");
        printf("2. Ver Usuarios\n");
        printf("3. Eliminar usuario\n");
        printf("4. Salir\n");

        cin >> opcion;

        switch (opcion) {

            case 1: {
                string nombre;
                string apellido;
                string rol;
                printf("\nEscribe el nombre: ");
                cin >> nombre;
                printf("\nEscribe el apellido: ");
                cin >> apellido;
                printf("\nEscribe el rol: ");
                cin >> rol;

                usuarios[numeroDeUsuarios] = new Usuario(siguienteID, nombre, apellido, rol);
                siguienteID++;
                numeroDeUsuarios++;

                if (rol == "profesor") {

                    profesores[numeroDeProfesores] = new Profesor();
                    profesores[numeroDeProfesores]->idUsuario = usuarios[numeroDeUsuarios -1]->id;
                    numeroDeProfesores++;
                }
                else if (rol == "estudiante") {

                    mochilas[usuarios[numeroDeUsuarios-1]->id] = new Mochila();

                }

                break;
            }
            case 2: {

                for (int i =0; i < numeroDeUsuarios; i++) {

                    printf("ID: %d \n", usuarios[i]->id);
                    cout << "Apellido: " << usuarios[i]->apellido << endl;
                    cout << "\nNombre: " << usuarios[i]->nombre << endl;
                    cout << "\nRol: " << usuarios[i]->rol << endl;
                    printf("======================\n");
                }
                break;
            }
            case 3: {

                int id =0;
                printf("Id de usuario a eliminar: ");
                cin >> id;

                for (int i = 0; i < numeroDeUsuarios; i++) {

                    if (id == usuarios[i]->id) {
                        delete usuarios[i];

                        for (int j = i; j < numeroDeUsuarios -1; j++) {

                            usuarios[j] = usuarios[j + 1];
                        }
                        numeroDeUsuarios--;

                        printf("Usuario %d eliminado correctamente\n", id);

                        break;
                    }

                }

            }

        }

    }while (opcion != 4);



}
void calculadora() {

    int opcion = 0;
    do {

        printf("== Menu Calculadora ==");
        printf("1. Suma\n");
        printf("2. Resta\n");
        printf("3. Multiplicacion\n");
        printf("4. Division\n");
        printf("5. Matrices\n");
        printf("6. Salir\n");
        cin >> opcion;

        double a,b;
        switch (opcion) {
            case 1: {

                printf("Numero 1: ");
                cin >> a;
                printf("\nNumero 2: ");
                cin >> b;

                printf("Resultado: %f",a+b);

                break;
            }

            case 2: {

                printf("Numero 1: ");
                cin >> a;
                printf("\nNumero 2: ");
                cin >> b;
                printf("Resultado: %f",a-b);
                break;
            }
            case 3: {
                printf("Numero 1: ");
                cin >> a;
                printf("\nNumero 2: ");
                cin >> b;
                printf("Resultado: %f",a*b);

                break;
            }
            case 4: {

                printf("Numero 1: ");
                cin >> a;
                printf("\nNumero 2: ");
                cin >> b;

                if (b== 0) {

                    printf("Error de division");
                }
                else {
                    printf("Resultado: %f",a/b);
                }
                break;
            }
            case 5: {

                int filas, columnas;

                printf("Filas: ");
                cin >> filas;

                printf("Columnas: ");
                cin >> columnas;

                if(filas <= 0 || columnas <= 0){
                    printf("Dimensiones invalidas\n");
                    return;
                }

                double** A = crearMatriz(filas,columnas);
                double** B = crearMatriz(filas,columnas);

                printf("\nMatriz A:\n");
                llenarMatriz(A,filas,columnas);

                printf("\nMatriz B\n");
                llenarMatriz(B,filas,columnas);


                int op;

                printf("\n1. Sumar matrices\n");
                printf("2. Restar matrices\n");
                printf("3. Restar matrices\n");
                cin >> op;

                double** R;

                if(op == 1){

                    R = sumarMatrices(A,B,filas,columnas);
                }

                if(op == 2){

                    R = restarMatrices(A,B,filas,columnas);
                }

                if (op ==3) {

                    R = multiplicarMatrices(A,B,filas,columnas);
                }

                printf("\nResultado\n");
                mostrarMatriz(R,filas,columnas);

                liberarMatriz(A,filas);
                liberarMatriz(B,filas);
                liberarMatriz(R,filas);

                break;

            }
        }

    }while (opcion != 6);



}


double** crearMatriz(int filas, int columnas) {

    double** matriz = new double*[filas];

    for(int i = 0; i < filas; i++) {

        matriz[i] = new double[columnas];
    }

    return matriz;
}

void llenarMatriz(double** matriz, int filas, int columnas) {

    int opcion;

    printf("1. Manual\n");
    printf("2. Aleatoria\n");
    cin >> opcion;

    if(opcion == 1){

        for(int i=0;i<filas;i++){
            for(int j=0;j<columnas;j++){

                printf("Elemento [%d][%d]: ", i, j);
                cin >> matriz[i][j];

            }
        }

    }

    if(opcion == 2){

        for(int i=0;i<filas;i++){
            for(int j=0;j<columnas;j++){

                matriz[i][j] = rand() % 100;

            }
        }

    }
}

void mostrarMatriz(double** matriz, int filas, int columnas){

    for(int i=0;i<filas;i++){

        for(int j=0;j<columnas;j++){

            printf("%f ",matriz[i][j]);

        }

        printf("\n");
    }
}

double** sumarMatrices(double** A, double** B, int filas, int columnas){

    double** R = crearMatriz(filas,columnas);

    for(int i=0;i<filas;i++){
        for(int j=0;j<columnas;j++){

            R[i][j] = A[i][j] + B[i][j];
        }
    }

    return R;
}


double** restarMatrices(double** A, double** B, int filas, int columnas){

    double** R = crearMatriz(filas,columnas);

    for(int i=0;i<filas;i++){
        for(int j=0;j<columnas;j++){

            R[i][j] = A[i][j] - B[i][j];
        }
    }

    return R;
}

double** multiplicarMatrices(double** A, double** B, int filas, int columnas){

    double** R = crearMatriz(filas,columnas);

    for(int i=0;i<filas;i++){
        for(int j=0;j<columnas;j++){

            R[i][j] = 0;

            for(int k=0;k<columnas;k++){

                R[i][j] += A[i][k] * B[k][j];

            }
        }
    }

    return R;
}

void liberarMatriz(double** matriz, int filas){

    for(int i=0;i<filas;i++){

        delete[] matriz[i];
    }

    delete[] matriz;
}
