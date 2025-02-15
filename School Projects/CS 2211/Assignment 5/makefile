movieTheaterDB: movieTheaterDB.o movieTheaterDB_movie.o movieTheaterDB_actor.o
	gcc -o movieTheaterDB movieTheaterDB.o movieTheaterDB_movie.o movieTheaterDB_actor.o

movieTheaterDB.o: movieTheaterDB.c movieTheaterDB.h movieTheaterDB_movie.h movieTheaterDB_actor.h
	gcc -c movieTheaterDB.c

movieTheaterDB_movie.o: movieTheaterDB_movie.c movieTheaterDB_movie.h
	gcc -c movieTheaterDB_movie.c
	
movieTheaterDB_actor.o: movieTheaterDB_actor.c movieTheaterDB_actor.h
	gcc -c movieTheaterDB_actor.c