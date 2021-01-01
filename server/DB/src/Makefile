submain:
	gcc -Wall -o ../bin/calorie.o -c calorie.c
	gcc -Wall -o ../bin/saved_route.o -c saved_route.c
	gcc -Wall -o ../bin/usedlog.o -c usedlog.c
	gcc -Wall -o ../bin/user.o -c user.c
	gcc -Wall -o ../bin/submain1 submain1.c ../bin/calorie.o ../bin/saved_route.o \
	-lmysqlclient -L/usr/lib64/mysql
	gcc -Wall -o ../bin/submain2 submain2.c ../bin/user.o ../bin/usedlog.o \
	-lmysqlclient -L/usr/lib64/mysql

# カロリーテーブル
calorie.o: calorie_set.c
	gcc -Wall -o ../bin/calorie.o -c calorie.c -lmysqlclient -L/usr/lib64/mysql

# 保存したルートテーブル
saved_route.o: saved_route_set.c
	gcc -Wall -o ../bin/saved_route.o -c saved_route.c -lmysqlclient -L/usr/lib64/mysql

# 利用履歴テーブル
usedlog.o: usedlog_set.c
	gcc -Wall -o ../bin/usedlog.o usedlog.c -c -lmysqlclient -L/usr/lib64/mysql

# ユーザテーブル
user.o: user_set.c
	gcc -Wall -o ../bin/user.o user.c -c -lmysqlclient -L/usr/lib64/mysql

submain1:
	gcc -Wall -o ../bin/submain1 submain1.c

submain2:
	gcc -Wall -o ../bin/submain2 submain2.c