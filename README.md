# Práctica 3 - Contador BCD Ascendente/Descendente con FreeRTOS

## Integrante

- Eduardo Cerón

# Introducción

FreeRTOS es un sistema operativo en tiempo real ampliamente utilizado en sistemas embebidos debido a su capacidad para administrar múltiples tareas de manera eficiente. En esta práctica se implementó un contador BCD ascendente y descendente sobre una tarjeta ESP32 utilizando FreeRTOS. El sistema permite controlar la dirección de conteo, la velocidad de actualización y el estado de ejecución mediante botones físicos. Además, se emplearon conceptos importantes como TaskHandle_t, estados de tareas, suspensión y reanudación de tareas, así como el uso de parámetros mediante pvParameters para mejorar la reutilización del código.

# Conceptos a investigar

## TaskHandle_t

Es un identificador que FreeRTOS utiliza para referirse a una tarea específica. Permite suspender, reanudar, eliminar o consultar el estado de una tarea desde otra parte del programa.

## eTaskState

Es un tipo de dato enumerado que representa el estado actual de una tarea dentro de FreeRTOS. Algunos estados son Running, Ready, Blocked, Suspended y Deleted.

## eTaskGetState()

Es una función que devuelve el estado actual de una tarea utilizando su TaskHandle_t. Se emplea para supervisar el comportamiento del sistema y realizar tareas de diagnóstico.

## xTaskCreate()

Es la función utilizada para crear una nueva tarea en FreeRTOS. Permite definir la función de la tarea, su tamaño de pila, prioridad y parámetros de entrada.

## vTaskDelay()

Es una función que bloquea una tarea durante un tiempo determinado expresado en ticks del sistema. Mientras la tarea está bloqueada, el procesador puede ejecutar otras tareas.

## vTaskSuspend()

Es una función que suspende una tarea. Una tarea suspendida deja de ser planificada por el sistema hasta que sea reanudada explícitamente.

## vTaskResume()

Es una función que reanuda una tarea previamente suspendida mediante vTaskSuspend().

## Idle Task

Es una tarea interna creada automáticamente por FreeRTOS. Se ejecuta cuando ninguna otra tarea está lista para utilizar el procesador.

## Tick del sistema

Es la interrupción periódica que utiliza FreeRTOS para medir el tiempo y administrar los cambios de estado de las tareas.

## Round Robin

Es un mecanismo de planificación utilizado por FreeRTOS para repartir el tiempo de ejecución entre tareas que tienen la misma prioridad.

# Preguntas guía

## 1. ¿Qué diferencia existe entre BLOCKED y SUSPENDED?

Una tarea en estado BLOCKED está esperando que ocurra algún evento o que transcurra un tiempo determinado para volver a ejecutarse. Una tarea en estado SUSPENDED permanece detenida indefinidamente y solo puede volver a ejecutarse mediante una llamada explícita a vTaskResume().

## 2. ¿Por qué vTaskDelay() coloca una tarea en estado BLOCKED?

Porque la función indica al planificador que la tarea debe esperar un tiempo determinado antes de volver a ejecutarse. Durante ese periodo la tarea permanece bloqueada y no consume tiempo de CPU.

## 3. ¿Qué diferencia existe entre vTaskDelay() y un Software Timer?

vTaskDelay() bloquea únicamente a la tarea que lo ejecuta. Un Software Timer es un mecanismo independiente que ejecuta una función de callback cuando expira un tiempo determinado sin necesidad de bloquear una tarea específica.

## 4. ¿Qué función cumple el Idle Task?

El Idle Task utiliza el procesador cuando ninguna otra tarea está lista para ejecutarse. Además, permite que FreeRTOS realice tareas internas de mantenimiento del sistema.

## 5. ¿Cómo decide FreeRTOS cuál tarea ejecutar cuando varias tienen la misma prioridad?

FreeRTOS utiliza un esquema Round Robin. Cada tarea recibe una porción de tiempo de ejecución y el planificador alterna entre ellas de manera equitativa.

## 6. ¿Qué ventajas aporta pvParameters?

Permite reutilizar una misma función de tarea para diferentes dispositivos o configuraciones. Esto reduce la duplicación de código y mejora la modularidad del programa.

## 7. ¿Qué ventajas aporta TaskHandle_t?

Permite controlar tareas de forma individual. Gracias a TaskHandle_t es posible suspender, reanudar, eliminar o consultar el estado de una tarea específica.

## 8. ¿Qué ocurriría si el contador se implementara con variables globales únicamente?

El programa sería menos modular y más difícil de mantener. Además, aumentaría el riesgo de errores por acceso concurrente a las variables compartidas y sería más complicado reutilizar el código en otros proyectos.

# Conclusión

Durante esta práctica se comprobó el funcionamiento del planificador de FreeRTOS mediante la implementación de un contador BCD controlado por múltiples tareas. Se utilizó TaskHandle_t para administrar la ejecución de tareas mediante suspensión y reanudación, mientras que el uso de pvParameters permitió reutilizar funciones de tarea sin duplicar código. También se observó cómo FreeRTOS administra los estados de las tareas y distribuye el tiempo de ejecución entre ellas. En general, la práctica permitió comprender de manera práctica los mecanismos fundamentales de gestión de tareas en sistemas embebidos basados en FreeRTOS.
