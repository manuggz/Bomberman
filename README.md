# DestructionBombs

Remake del famoso Bomberman.
Se basa en la versión [Super Bomberman para SNES](https://www.youtube.com/watch?v=Xef0tkXmSp4).

### Proposito
Este proyecto es realizado y mantenido con la intención de formar parte del material educativo en la creación de Video Juegos 2D, sin ninguna intención comercial. 

### Estado actual del desarrollo
El proyecto comenzó a desarrollarse en C usando la librería [SDL 1.2](https://en.wikipedia.org/wiki/Simple_DirectMedia_Layer) hace más de 5 años.
Cuando se retomó su desarrollo que se había dejado en espera se encontró con el problema de que la nueva versión de SDL la 2.0 posee grandes cambios en sus funciones lo que obliga a cambiar el código para hacerlo SDL 2.0 compatible. 
Debido a esto, se decidió comentar todo el código y empezarlo de nuevo guiandose por el código anterior, todo esto mientras se realizaban refactorizaciones y se completaba la transición de C a C++11  que se había hecho a medias.

Actualmente se puede compilar y ejecutar el código en ubuntu 16.04. Las siguientes partes estan mayormente completadas:
- Menu Principal
- Menu De Modos de Juego
- Menu Para Configurar el Modo PvP de hasta 5 jugadores
- Modo de Juego PvP de hasta 5 Jugadores

### Vision
Primero se debe completar la transición de C-> C++11 y SDL 1.2 -> SDL 2.0 de Todas las caracteristicas que tenía el juego antes de comentarlo:
- Editor de Mapa
- Modo Historia de Hasta dos jugadores(Este no Estaba Completado)
- En la versión PvP había un contador parecido al de CS usando TAB
- Configuración del Teclado/Joystick de los 5 Jugadores
Después, agregarle:
- PvP Online
- Mapa Scrolleable para la versión PvP Online

Además, se está desarrollando como subproyecto un "motor" que facilita la creación de otros juegos parecidos y no a bomberman, por lo que se espera crear otros juegos utilizandolo.
### Descarga e Instalación
Instalar las librerias Necesarias SDL
SDL,SDL_Mixer,SDL_Image,SDL_Net,SDL_ttf
Instalar 
(Incompleto Googlealo por ahora)
#### Linux
(Incompleto Googlealo por ahora)
Clonar el Repositorio
```sh
$ git clone https://github.com/manuggz/bomberman.git
```
Aun no
#### Window
Aun no

## Capturas de Pantalla de algunas Escenas
### Menu Principal
![Menu Principal](http://i.imgur.com/VaqWWXf.png)
### Configuración del Mapa GUI (Aparece también cuando se elije crear una partida en RED)
![Configuración Mapa](http://i.imgur.com/gvRoRbw.png)
### Actualmente se puede crear el servidor y se muestrauna GUI a espera de los demás players(a medias)
![Game Server Creado](http://i.imgur.com/PV0362m.png)
### Game Play(Admite 5 jugadores con controles configurados en joysticks o teclado)
![Game Play](http://i.imgur.com/EzUM6PZ.png)
### Configurar Teclas de los 5 players
![Configurar Teclas](http://i.imgur.com/V1UpwgX.png)

### Versiones Anteriores
Si quieres ver el progreso de la versión anterior puedes navegar las entradas publicadas aquí:
https://baulprogramas.blogspot.com/search/label/bomberman
