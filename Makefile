# Regola per il target principale main.exe
main.exe: main.o attivita.o utile.o
	gcc -o main.exe main.o attivita.o utile.o

# Regola per il file oggetto attivita.o
attivita.o: attivita.c attivita.h utile.h
	gcc -c attivita.c

# Regola per il file oggetto utile.o
utile.o: utile.c utile.h
	gcc -c utile.c

# Regola per il file oggetto main.o
main.o: main.c attivita.h
	gcc -c main.c

# Regola per la pulizia dei file oggetto e dell'eseguibile
clean:
	rm -f *.o main.exe test.exe

# Regola per eseguire il programma
run: main.exe
	./main.exe

# Regola per eseguire il file di test
test:
	gcc -o test1 test1.c attivita.c utile.c
	./test1
	gcc -o test2 test2.c attivita.c utile.c
	./test2
	gcc -o test3 test3.c attivita.c utile.c
	./test3

