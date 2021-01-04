submain1: submain1.c ../bin/calorie.o ../bin/saved_route.o
	gcc -Wall -o submain1.o -c submain1.c
	gcc submain1.o -o ../bin/submain1 ../bin/calorie.o ../bin/saved_route.o -lmysqlclient -L/usr/lib64/mysql
	rm submain1.o

submain.o: submain.c
	gcc -Wall -o ../bin/queue.o -c queue.c
	gcc -Wall -o ../bin/submain.o -c submain.c

queue.o: queue.c
	gcc -Wall -o queue.o -c queue.c

