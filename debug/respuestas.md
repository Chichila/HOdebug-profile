# Debug

## Floating point exception 
(El 'floating point exception' es un erorr que ocurre cuando se intenta hacer 
algo que es imposible con un número de punto flotante, como dividir por cero)


En la carpeta `fpe/` hay tres códigos de C, independientes, para compilar. 
Cada uno de estos códigos genera un ejecutable. Hay además una carpeta que
define la función `set_fpe_x87_sse_`. Una vez compilados los tres ejecutables
sin la opción `-DTRAPFPE`, responder las siguientes preguntas:

- ¿Qué función requiere agregar `-DTRAPFPE`? ¿Cómo pueden hacer que el
programa *linkee* adecuadamente?
- Para cada uno de los ejecutables, ¿qué hace agregar la opción `-DTRAPFPE` al 
compilar? ¿En qué se diferencian los mensajes de salida con y sin esa opción?


La función que requiere agregar -DTRAPFPE es la raíz cuadrada (sqrtf) que se
encuentra en el código test_fpe3. 
Cuando quiero compilar con el comando 'gcc -c test_fpe3.c' tira 
un mensaje de warning que dice lo siguiente: 'incompatible implicit declaration 
of built-in function ‘sqrtf’ tmp = sqrtf(a / b);' Sin embargo genera un archivo
binario. De todos modos si uno lo quisiera linkear así como está haciendo:
gcc test_fpe3.o no lo permite, y tira otro mensaje de error donde dice que la 
función sqrtf está indefinida.


Luego, hice lo siguiente:
1.Generé el objeto para test_fpe3.c haciendo: gcc -c test_fpe3.c -DTRAPFPE -lm
me sigue apareciendo el mismo cartel de antes, pero seguía generando el objeto.
2. Hice el linkeo con: gcc test_fpe3.o fpe_x87_sse.o -DTRAPFPE -lm y generó un
ejecutable.
3. Hice unas pruebas: 
    si a=1 y b=2, c=0.707107
    si a=1 y b=0, Floating Point Exception
    si a=0 y b=0, Floating Point Exception
    
También probé compilando del siguiente modo:
1.Generé el objeto para test_fpe3.c haciendo: gcc -c test_fpe3.c
me sigue apareciendo el mismo cartel de antes, pero seguía generando el objeto.
2. Hice el linkeo con: gcc test_fpe3.o fpe_x87_sse.o -DTRAPFPE -lm y generó un
ejecutable.
3. Hice unas pruebas: 
    si a=1 y b=2, c=0.707107
    si a=1 y b=0, c=inf
    si a=0 y b=0, c=-nan


Por lo que veo en el código test_fpe3.c creo entender que cuando se escribe
-DTRAPFPE -lm el preprocesador entra en el if y toma el set_fpe_x87_sse_ donde
debería darle información de como tratar los problemas de Floating Point 
Exception.



## Segmentation Fault
(Violación de acceso en español: es un intento fallido de acceder a información
a la que no se tiene permiso para ver o modificar. Ocurre cuando un proceso
intenta acceder a una parte de la memoria a la que no tiene permiso)

En la carpeta `sigsegv/` hay códigos de C y de FORTRAN. Elijan alguno
y compilen y corren el programa de acuerdo a los comentarios en el código,
para obtener los ejecutables `small.x` y `big.x`.
Identifiquen los errores que devuelven (¡si devuelven alguno!) los ejecutables.
Ahora ejecuten `ulimit -s unlimited` en la terminal y vuelvan a correrlo. Luego
responder las siguientes preguntas:

- ¿Devuelven el mismo error que antes?
- Averigüen qué hicieron al ejecutar la sentencia `ulimit -s unlimited`. Algunas pistas
son: abran otra terminal distinta y fíjense si vuelve al mismo error, fíjense la diferencia
entre `ulimit -a` antes y después de ejecutar `ulimit -s unlimited`, googleen, etcétera.
- La "solución" anterior, ¿es una solución en el sentido de debugging?


Hice lo siguiente:
1. Compilé los código en C (en Fortran no pude con las sentecias que aparecían)
y generé los ejecutables small.x y big.x sin problemas haciendo:
    gcc source.c -o small.x -D__SMALL -O0 -g
    gcc source.c -o big.x -O0 -g 
2. Los ejecuté y el archivo small.x no generó ninguna salida, pero tampoco tiró
ningún error. El ejecutable big.x tiró el error por pantalla 'Segmentation 
fault (core dumped)'
3. Si ejecuto la sentencia `ulimit -s unlimited` en la terminal y ejecuto 
nuevamente big.x el ejecutable corre, pero tarda mucho.
4. Lo que hice ejecutando esa sentencia es autorizar que no tenga límite en el 
stack size. Antes de ejecutar la sentencia el tamaño disponible es de 8192 y 
luego, ilimitada.
5. No creo que sea una solución en el sentido de debugging porque no arreglo
ningún error solo incremento el espacio disponible para que pueda ejecutar el
programa. De todos modos no estoy segura de entender si esta es la idea.



## Valgrind

En la carpeta `valgrind/` hay ejemplos en C y FORTRAN que se pueden ejecutar
con valgrind. Describan el error y por qué sucede


Para este ejercicio hice lo siguiente:
1. Compilé el código test_oob4.c haciendo: gcc test_oob4 -g
2. Corrí el ejecutable con valgrind haciendo: valgrind -v ./a.out y me tiró el
siguiente resumen de la corrida:

==3229==HEAP SUMMARY:
==3229==     in use at exit: 80,000,000 bytes in 2 blocks
==3229==   total heap usage: 2 allocs, 0 frees, 80,000,000 bytes allocated
==3229== 
==3229== Searching for pointers to 2 not-freed blocks
==3229== Checked 80,074,504 bytes
==3229== 
==3229== LEAK SUMMARY:
==3229==    definitely lost: 0 bytes in 0 blocks
==3229==    indirectly lost: 0 bytes in 0 blocks
==3229==      possibly lost: 80,000,000 bytes in 2 blocks
==3229==    still reachable: 0 bytes in 0 blocks
==3229==         suppressed: 0 bytes in 0 blocks
==3229== Rerun with --leak-check=full to see details of leaked memory
==3229== 
==3229== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==3229== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

Hice lo mismo con el otro archivo:
3. Primero compilé source1.c haciendo: gcc source1.c -O3 -g
4. Luego corrí el ejecutable con valgrind: valgrind -v ./a.out
5. Comienza bien y luego queda parado sin hacer nada. No se bien que es lo que
debo hacer. No termino de entender la herramienta.



## Funny

En la carpeta `funny/` hay un código de C. Describan las diferencias de los ejecutables
al compilar con y sin el flag `-DDEBUG`. ¿De dónde vienen esas diferencias?

Hice lo siguiente:
1. Compilé el código con: gcc test_oob2.c
2. Luego corrí el ejecutable generado y me salió un cartel que decía:
Segmentation fault (core dumped)
3. Después compilé haciendo: gcc -test_oob2.c -DDEBUG y al correr el ejecutable
se agregó un texto que decía: 'I'm HERE !!!!' y luego 'Segmentation fault 
(core dumped)'

4. Mirando el código veo que existen unos ifdef que cuando aparece -DDEBUG
imprime el mensaje de error. Sin embargo no termino de entender la funcionalidad
del código ni de lo que queremos ver en este ejercicio.





