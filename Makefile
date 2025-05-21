# Regola per il target principale main.exe
main.exe: main.o attivita.o
	gcc -o main.exe main.o attivita.o

# Regola per il file oggetto attivita.o
attivita.o: attivita.c attivita.h
	gcc -c attivita.c

# Regola per il file oggetto main.o
main.o: main.c attivita.h
	gcc -c main.c

# Regola per la pulizia dei file oggetto e dell'eseguibile
clean:
	rm -f *.o main.exe

# Regola per eseguire il programma
run: main.exe
	./main.exe