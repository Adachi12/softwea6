all: main.c DB/src/calorie.c DB/src/usedlog.c DB/src/user.c DB/src/saved_route.c 
	gcc -o DB/bin/calorie.o -c DB/src/calorie.c
	gcc -o DB/bin/usedlog.o -c DB/src/usedlog.c
	gcc -o DB/bin/user.o -c DB/src/user.c
	gcc -o DB/bin/saved_route.o -c DB/src/saved_route.c
	gcc -o main main.c DB/bin/* -lpthread -lmysqlclient -L/usr/lib64/mysql
