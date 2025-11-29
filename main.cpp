#include <iostream>
#include <string>
#include <climits> // necesario para usar INT_MAX
#include <cfloat>  // necesario para usar FLT_MAX
using namespace std;

struct Producto
{
    string nombre;
    float precio;
    int cantidad;
};

Producto producto[100];   // array que almacena los productos
int cantidadProducto = 0; // inicializa la variable cantidad

// función para validar cin enteros (para evitar repetir código)
// pregunta: el mensaje para pedir el dato
// min: el valor minimo tipo int permitido. max: el valor maximo tipo int permitido
// mensajeError: mensaje de error si ingresa un número int fuera del Rango
int pedirEntero(string pregunta, int min, int max, string mensajeError)
{
    int valor;
    bool esInvalido = true;

    do
    {
        cout << pregunta; // mensaje que se usará para pedir el dato
        cin >> valor;

        if (cin.fail()) // si se ingresa un string en lugar de int
        {
            cin.clear();
            cin.ignore(1000, '\n');                                       // necesario para evitar un bucle infinito
            cout << "Error: Por favor ingrese un número entero." << endl; // mensaje si ingresa un string en lugar de int
            esInvalido = true;
        }
        else if (valor < min || valor > max)
        {
            cout << mensajeError << endl;
            esInvalido = true;
        }
        else
        {
            esInvalido = false; // si el mensaje es valido se cambia a false, lo que hace que se salga del while
        }

    } while (esInvalido);

    return valor; // devuelve el valor del cin
}

// función para validar cin tipo float para evitar repetir código
// mensaje: el mensaje para pedir el dato
// min: el valor minimo tipo float permitido. max: el valor maximo tipo float permitido
// mensajeError: mensaje de error si ingresa un número float fuera del Rango
float pedirFlotante(string pregunta, float min, float max, string mensajeError)
{
    float valor;
    bool esInvalido = true;

    do
    {
        cout << pregunta; // mensaje que se usará para pedir el dato
        cin >> valor;

        if (cin.fail()) // si se ingresa un string en lugar de int
        {
            cin.clear();
            cin.ignore(1000, '\n');                                       // necesario para evitar un bucle infinito
            cout << "Error: Por favor ingrese un número válido." << endl; // mensaje si ingresa un string en lugar de int
            esInvalido = true;
        }
        else if (valor < min || valor > max)
        {
            cout << mensajeError << endl;
            esInvalido = true;
        }
        else
        {
            esInvalido = false; // si el mensaje es valido se cambia a false, lo que hace que se salga del while
        }

    } while (esInvalido);

    return valor; // devuelve el valor del cin
}

void registrarProductos()
{
    cantidadProducto = pedirEntero("\n¿Cuántos productos desea registrar?: ", 1, 100,
                                   "Error: La cantidad debe ser entre 1 y 100. ");

    for (int i = 0; i < cantidadProducto; i++)
    {
        cout << "\nProducto " << i + 1 << ":";
        cout << "\nNombre: ";   // limpia el cin para evitar un bucle infinito si se equivoco de dato el usuario
        cin.ignore(1000, '\n'); // para que el getline funcione correctamente
        getline(cin, producto[i].nombre);

        producto[i].precio = pedirFlotante("Precio: ", 0.01, FLT_MAX,
                                           "Error: Ingrese un precio válido (número positivo). ");
        producto[i].cantidad = pedirEntero("Cantidad: ", 1, INT_MAX,
                                           "Error: Ingrese una cantidad válida (número positivo). ");
        cout << endl;
    }
    cout << "Productos registrados exitosamente." << endl;
}

void mostrarProductos()
{
    if (cantidadProducto == 0) // valida si ya se registraron productos
    {
        cout << "\nError: No hay productos registrados." << endl;
        return; // sale de la función
    }

    cout << "\n==== LISTA DE PRODUCTOS =====" << endl;
    cout << "Índice"
         << "      " << "Nombre"
         << "      " << "Precio"
         << "      " << "Cantidad" << endl;
    cout << "------------------------------------------" << endl;

    for (int i = 0; i < cantidadProducto; i++) // imprime el inventario
    {
        cout << i
             << "           " << producto[i].nombre
             << "      " << producto[i].precio
             << "      " << producto[i].cantidad << endl;
    }
}

void ordenarBurbuja() // método bubble sort
{
    for (int i = 0; i < cantidadProducto - 1; i++)
    {
        for (int j = 0; j < cantidadProducto - i - 1; j++)
        {
            if (producto[j].precio > producto[j + 1].precio)
            {
                Producto temp = producto[j];
                producto[j] = producto[j + 1];
                producto[j + 1] = temp;
            }
        }
    }
}

void ordenarSeleccion() // método selection
{
    for (int i = 0; i < cantidadProducto - 1; i++)
    {
        int k = i;
        for (int j = i + 1; j < cantidadProducto; j++)
        {
            if (producto[j].precio < producto[k].precio)
            {
                k = j;
            }
        }
        Producto temp = producto[i];
        producto[i] = producto[k];
        producto[k] = temp;
    }
}

void ordenarInsercion() // método insertion
{
    for (int i = 1; i < cantidadProducto; i++)
    {
        Producto key = producto[i];
        int j = i - 1;
        while (j >= 0 && key.precio < producto[j].precio)
        {
            producto[j + 1] = producto[j];
            j--;
        }
        producto[j + 1] = key;
    }
}

void ordenarProductos()
{
    if (cantidadProducto == 0) // valida que ya se hayan registrado productos
    {
        cout << "\nError: No hay productos registrados." << endl;
        return; // sale de la función
    }
    cout << "\n===== ORDENAR POR PRECIO =====";
    cout << "\nSeleccione método de ordenamiento:" << endl
         << "1. Burbuja" << endl
         << "2. Selección " << endl
         << "3. Inserción " << endl;
    int opcionOrdenar = pedirEntero("Opción: ", 1, 3,
                                    "Error: Por favor ingresa una opción válida (1-3)");

    switch (opcionOrdenar) // no es necesario default, porque se válida la opción
    {
    case 1:
        ordenarBurbuja();
        cout << "Productos ordenados por precio (ascendente) mediante el método de Burbuja." << endl;
        break;
    case 2:
        ordenarSeleccion();
        cout << "Productos ordenados por precio (ascendente) mediante el método de Selección." << endl;
        break;
    case 3:
        ordenarInsercion();
        cout << "Productos ordenados por precio (ascendente) mediante el método de Inserción." << endl;
        break;
    }
    mostrarProductos();
}

void buscarProductos()
{
    if (cantidadProducto == 0) // valida si hay productos registrados
    {
        cout << "\nError: No hay productos registrados." << endl;
        return; // sale de la función
    }

    string busqueda;
    cout << "\nIngrese el nombre a buscar: "; // solicita el nombre del producto a buscar
    cin.ignore(1000, '\n');                   // para que el getline funcione correctamente
    getline(cin, busqueda);

    for (int i = 0; i < cantidadProducto; i++)
    {
        if (busqueda == producto[i].nombre) // compara busqueda con el nombre del producto
        {
            cout << "\nProducto encontrado:" << endl
                 << "Nombre: " << producto[i].nombre << endl
                 << "Precio: " << producto[i].precio << endl
                 << "Cantidad: " << producto[i].cantidad << endl;
            return; // como ya encontro el producto se sale de la función
        }
    }
    cout << "\nError: Producto no encontrado. " << endl;
}

void actualizarProducto()
{
    if (cantidadProducto == 0) // valida que ya hayan productos regitrados
    {
        cout << "\nError: No hay productos registrados." << endl;
        return; // sale de la función
    }

    cout << "\nMonstrando lista de productos actual" << endl;
    mostrarProductos(); // llama la función mostrar productos
    // validación del índice
    int indice = pedirEntero("\nIngrese el índice del producto a actualizar: ", 0, cantidadProducto - 1,
                             "Error: Índice fuera de rango.");

    cout << "\n¿Qué desea actualizar?" << endl
         << "1. Precio" << endl
         << "2. Cantidad" << endl;

    int opcionActualizar = pedirEntero("Opción: ", 1, 2, "Error: Opción no válida."); // validación de la opción

    if (opcionActualizar == 1)
    {
        producto[indice].precio = pedirFlotante("Nuevo precio: ", 0.01, FLT_MAX,
                                                "Error: Ingrese un precio válido."); // validación del nuevo precio
        cout << "Producto actualizado. " << endl;
    }
    if (opcionActualizar == 2)
    {
        producto[indice].cantidad = pedirEntero("Nueva cantidad: ", 1, INT_MAX,
                                                "Error: Ingrese una cantidad válida."); // Validación de la nueva cantidad
        cout << "Producto actualizado. " << endl;
    }
    cout << "\nLista de productos actualizada. " << endl;
    mostrarProductos();
}

void generarReporte()
{
    if (cantidadProducto == 0)
    {
        cout << "\nError: No hay productos registrados." << endl;
        return; // sale de la función
    }
    float inventarioTotal = 0; // inicializamos en 0
    int mayorCantidad = 0;
    string productoMayor = "";

    cout << "\n===== REPORTE FINAL =====" << endl;
    cout << "Total de productos registrados: " << cantidadProducto << endl;

    // inicializa con los datos del primer elemento
    mayorCantidad = producto[0].cantidad;
    productoMayor = producto[0].nombre;

    for (int i = 0; i < cantidadProducto; i++)
    {
        inventarioTotal += (producto[i].precio * producto[i].cantidad); // suma el inventario total

        if (producto[i].cantidad > mayorCantidad) // busca el producto con mayor cantidad
        {
            mayorCantidad = producto[i].cantidad;
            productoMayor = producto[i].nombre;
        }
    }

    cout << "Valor total en inventario: $" << inventarioTotal << endl;
    cout << "Producto con mayor cantidad: " << productoMayor << " (" << mayorCantidad << ")" << endl;
}

int main()
{
    bool menu = true;
    int opcion;
    while (menu == true)
    {
        cout << "\n===== SISTEMA BÁSICO DE GESTIÓN DE PRODUCTOS =====" << endl
             << "1. Registrar productos" << endl
             << "2. Mostrar productos" << endl
             << "3. Ordenar productos" << endl
             << "4. Buscar producto" << endl
             << "5. Actualizar producto" << endl
             << "6. Generar reporte final" << endl
             << "7. Salir" << endl;
        // valida la variable opcion
        opcion = pedirEntero("Seleccione una opción: ", 1, 7,
                             "Error: Por favor ingresa una opción válida del menú.");

        switch (opcion)
        {
        case 1:
            registrarProductos();
            break;
        case 2:
            mostrarProductos();
            break;
        case 3:
            ordenarProductos();
            break;
        case 4:
            buscarProductos();
            break;
        case 5:
            actualizarProducto();
            break;
        case 6:
            generarReporte();
            break;
        case 7:
            menu = false;
            cout << "Saliendo del programa" << endl;
            break;
        }
    }
}