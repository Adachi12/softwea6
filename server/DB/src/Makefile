submain:
	gcc -Wall -o calorie.o -c calorie.c
	gcc -Wall -o saved_route.o -c saved_route.c
	gcc -Wall -o usedlog.o -c usedlog.c
	gcc -Wall -o user.o -c user.c
	gcc -Wall -o ../bin/submain1 submain1.c calorie.o saved_route.o \
	-lmysqlclient -L/usr/lib64/mysql
	gcc -Wall -o ../bin/submain2 submain2.c user.o usedlog.o \
	-lmysqlclient -L/usr/lib64/mysql

# カロリーテーブル
calorie.o: calorie.c
	gcc -Wall -o calorie.o -c calorie.c

# 保存したルートテーブル
saved_route.o: saved_route.c
	gcc -Wall -o saved_route.o -c saved_route.c

# 利用履歴テーブル
usedlog.o: usedlog.c
	gcc -Wall -o usedlog.o  -c usedlog.c

# ユーザテーブル
user.o: user.c
	gcc -Wall -o user.o -c user.c

submain1: submain1.c calorie.o saved_route.o
	gcc -Wall -o ../bin/submain1 submain1.c calorie.o saved_route.o \
	-lmysqlclient -L/usr/lib64/mysql

submain2: submain2.c user.o usedlog.o
	gcc -Wall -o ../bin/submain2 submain2.c user.o usedlog.o \
	-lmysqlclient -L/usr/lib64/mysql

.PHONY: run_sub1 run_sub2

run_sub1:
	make submain1
	../bin/submain1
run_sub2:
	make submain2
	../bin/submain2