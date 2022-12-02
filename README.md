# **World cup dataminer**

## Descripción del problema
Este programa es un software tanto servidor como cliente que obtiene información de datos seleccionado, para este fin se estará empleando el protocolo HTTP y un protocolo de comunicación definido por todos los estudiantes del curso en conjunto. Los datos obtenidos servirán para mostrar la ruta de una selección determinada en el mundial de fútbol, empezando por sus resultados en fase de grupos y mostrando además, los resultados de sus juegos en etapas más avanzadas como octavos, cuartos, semifinal y final en el caso que dicha selección las halla disputado. La visualización de los datos se hará mediante la interfaz de consola, la cual será capaz de mostrar los resultados de los equipos que el usuario indique. Los datos a utilizar están basados en las estadísticas que dejó el mundial de fútbol de Rusia 2018.

<center>

  ![Grupos](design/worldcup-groups.jpg)

</center>

## Manual de uso

El usuario podrá introducir el nombre del país del que desea saber sus estadísticas, el programa desplegará en la consola el recorrido de la selección en el mundial abarcando todas sus participaciones en fase de grupos y en instancias eliminatorias si aplicara. En el caso de que el equipo introducido no contara con particiáciones en el mundial, se desplegará un mensaje de error.

### Librerías

Para la realización de este proyecto fue necesario el uso de librerías de C++ externas, es necesario tenerlas instaladas para poder compilar exitosamente el código, las librerías utilizadas son las siguientes:

* OpenSSL
* nlohmann-json3-dev

Para instalar estas librerías utilice los siguientes comandos respectivamente:

```
sudo apt-get install openssl
sudo apt-get install nlohmann-json3-dev
```

### Compilación y ejecución

Para compilar el nachOS debe ejecutarse debe dirigirse a la carpeta ```test``` y ejecutar el siguiente comando:
```
make socket
```

En el caso que se quiere compilar y ejecutar el servidor se utilizará el siguiente comando:
```
make server
```

Por otro lado, para compilar y ejecutar el servidor se utilizará el siguiente comando:
```
make router
```

Si por el contrario se quiere compilar y ejecutar el cliente se se utilizará el siguiente comando:
```
make client
```
Ambos comandos generarán una carpeta ```bin``` en la cual se guardará el archivo ```WorldCup-DataMiner.o```

## Créditos

Proyecto desarrollado por:
* Michelle Fonseca Carrillo, correo: michelle.fonsecacarrillo@ucr.ac.cr
* Esteban Castañeda Blanco, correo: esteban.castaneda@ucr.ac.cr
* Daniel Lizano Morales, correo: daniel.lizanomorales@ucr.ac.cr
* Jorge Loría López, correo: jorge.lorialopez@ucr.ac.cr