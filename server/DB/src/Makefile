submain:
	gcc -Wall -c -o ../bin/calorie.o calorie.c -lmysqlclient -L/usr/lib64/mysql
	gcc -Wall -c -o ../bin/saved_route.o saved_route.c -lmysqlclient -L/usr/lib64/mysql
	gcc -Wall -c -o ../bin/usedlog.o usedlog.c -lmysqlclient -L/usr/lib64/mysql
	gcc -Wall -c -o ../bin/user.o user.c -lmysqlclient -L/usr/lib64/mysql
	gcc -Wall -o ../bin/submain submain1.c
	gcc -Wall -o ../bin/submain submain2.c

# カロリーテーブル
calorie.o: calorie_set.c
	gcc -Wall -c -o ../bin/calorie.o calorie.c -lmysqlclient -L/usr/lib64/mysql

# 保存したルートテーブル
saved_route.o: saved_route_set.c
	gcc -Wall -c -o ../bin/saved_route.o saved_route.c -lmysqlclient -L/usr/lib64/mysql

# 利用履歴テーブル
usedlog.o: usedlog_set.c
	gcc -Wall -c -o ../bin/usedlog.o usedlog.c -lmysqlclient -L/usr/lib64/mysql

# ユーザテーブル
user.o: user_set.c
	gcc -Wall -c -o ../bin/user.o user.c -lmysqlclient -L/usr/lib64/mysql