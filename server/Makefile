all: calorie.c saved_route.c usedlog.c user.c caster.c
	gcc -o calorie.o -c calorie.c
	gcc -o saved_route.o -c saved_route.c
	gcc -o usedlog.o -c usedlog.c
	gcc -o user.o -c user.c
	gcc -o caster.o -c caster.c
	gcc -o main calorie.o saved_route.o usedlog.o user.o caster.o test.c \
	-lmysqlclient -L/usr/lib64/mysql -pthread
	rm *.o

submain1: submain1.c calorie.c saved_route.c
	gcc -o calorie.o -c calorie.c
	gcc -o saved_route.o -c saved_route.c
	gcc -o submain1 submain1.c calorie.o saved_route.o \
	-lmysqlclient -L/usr/lib64/mysql -pthread

submain2: submain2.c user.c usedlog.c
	gcc -o user.o -c user.c
	gcc -o usedlog.o -c usedlog.c
	gcc -o submain1 submain1.c user.o usedlog.o \
	-lmysqlclient -L/usr/lib64/mysql -pthread