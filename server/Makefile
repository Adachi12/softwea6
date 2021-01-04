submain1: submain1.c ../bin/calorie.o ../bin/saved_route.o
	gcc -Wall -o submain1.o -c submain1.c
	gcc submain1.o -o ../bin/submain1 ../bin/calorie.o ../bin/saved_route.o -lmysqlclient -L/usr/lib64/mysql
	rm submain1.o

queue.o: queue.c
	gcc -Wall -o queue.o -c queue.c

