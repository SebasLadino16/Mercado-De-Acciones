# Mercado de Acciones (Stock Trading Application)

## Descripción
Este es un programa de compra y venta de acciones que permite a los usuarios conectarse a un servidor y realizar operaciones de compra y venta de acciones de diferentes empresas. El programa utiliza sockets para la comunicación entre el cliente y el servidor, permitiendo a los usuarios interactuar en tiempo real.

## Estructura del Proyecto
El proyecto está compuesto por los siguientes archivos:

- **mercado.h**: Define las estructuras de datos y las funciones relacionadas con las ofertas y los clientes.
- **mercado.cpp**: Implementa la lógica para procesar las ofertas de compra y venta, así como para mostrar el historial de transacciones.
- **servidor.cpp**: Implementa el servidor que maneja las conexiones de los clientes y procesa las ofertas.
- **cliente.cpp**: Implementa el cliente que permite a los usuarios realizar operaciones de compra y venta.

## Características
- Selección de acciones disponibles (Apple, Google, Amazon, Tesla).
- Realización de operaciones de compra y venta.
- Visualización de notificaciones de operaciones.
- Interfaz de usuario simple en la consola.

## Tecnologías Utilizadas
- Lenguaje de programación: C++
- Biblioteca de sockets: Winsock (Windows)
- Entorno de desarrollo: Visual Studio Code
- Compilador: g++

## Requisitos
- Un sistema operativo Windows.
- Compilador compatible con C++ (como MinGW o Visual Studio).
- Conexión a un servidor que ejecute el componente del servidor del programa.

## Cómo Compilar y Ejecutar

1. Si usas Visual Studio Code, crea un nuevo proyecto y agrega los archivos del proyecto a él o puedes bajar el repositorio de Github
2. Instala las bibliotecas necesarias (Winsock) si no las tienes instaladas.
3. Compila el proyecto con el comando `g++ -o servidor servidor.cpp mercado.cpp client
4. Ejecuta el servidor con el comando `./servidor` en la terminal.
5. En otra terminal, ejecuta el cliente con el comando `./cliente` y sigue las instrucciones en la pantalla.
6. Puedes conectarte a diferentes acciones y realizar operaciones de compra y venta.
7. Para cerrar el servidor, presiona `Ctrl+C` en la terminal del servidor.
8. Para cerrar el cliente, presiona `Ctrl+C` en la terminal del cliente.
