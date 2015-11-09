Ejercicio de Profiling

Compilé el código profile_me_1.c con las opciones -01, -02, -O3 y obtuve los 
siguientes tiempos:
Para todos me da Segmentation fault.

1. Con la opción O0: 
    real	0m0.222s
    user	0m0.000s
    sys	0m0.000s
2. Con la opción O1:
    real	0m0.219s
    user	0m0.004s
    sys	0m0.000s
3. Con la opción O2:
    real	0m0.001s
    user	0m0.000s
    sys	0m0.000s

Quisiera ver que es lo que hizo en cada caso, pero no encuentro como hacer esto.

Intenté usar el gprof compilando el programa así: gcc -pg profile_me_1.c, pero
no me generó el fichero gmon.out.
Intenté usar perf, pero me dice que no está instalada.

Con más tiempo podré seguir indagando como funciona para cada programa.
