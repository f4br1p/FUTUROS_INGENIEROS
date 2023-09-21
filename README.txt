Nuestro proyecto tiene 2 bloques de codigo, uno para el Rasbperry y otro para el Arduino.
La parte del rasbperry se encarga, mediante la IA, de detectar el color y enviarselo a través del puerto serial al arduino.
El bloque del arduino consta de distintas partes:
En base al color que envía el rasbperry esquivará debidamente haciendo accionar de las funciones definidas.
En base a la detección del sensor rgb detectará el sentido y momento en que tenga que doblar por cuestiones de la pista.
En base a la detección del sensor óptico detectará un objeto enfrete y determinará el camino seguro.

// Por cuestiones de tiempo algunas funciones pueden verse limitadas-incompletas. //

Los movimientos son ejecutados mediante un puente H L298N que nos permite dar cantidad de velocidad y dirección a las ruedas.
La dirección consta de un motor paso a paso con un driver ULN2003 que nos permite darle energía y sus respectivos pasos. 
Gracias a los diseños en fusios y la impresión 3D se logró una dirección que se acopla al motor paso a paso.


Todo esto es ejecutado de manera independiente, el arduino es el gestor de señales y controlador principal del auto.