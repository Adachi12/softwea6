all:
	gcc -Wall -o ../bin/calorie_set calorie_set.c -lmysqlclient -L/usr/lib64/mysql
	gcc -Wall -o ../bin/calorie_get calorie_get.c -lmysqlclient -L/usr/lib64/mysql
	gcc -Wall -o ../bin/saved_route_set saved_route_set.c -lmysqlclient -L/usr/lib64/mysql
	gcc -Wall -o ../bin/saved_route_get saved_route_get.c -lmysqlclient -L/usr/lib64/mysql
	gcc -Wall -o ../bin/usedlog_set usedlog_set.c -lmysqlclient -L/usr/lib64/mysql
	gcc -Wall -o ../bin/usedlog_get usedlog_get.c -lmysqlclient -L/usr/lib64/mysql
	gcc -Wall -o ../bin/user_set user_set.c -lmysqlclient -L/usr/lib64/mysql
	gcc -Wall -o ../bin/user_get user_get.c -lmysqlclient -L/usr/lib64/mysql

# カロリーテーブル
calorie_set: calorie_set.c
	gcc -Wall -o ../bin/calorie_set calorie_set.c -lmysqlclient -L/usr/lib64/mysql
calorie_get: calorie_get.c
	gcc -Wall -o ../bin/calorie_get calorie_get.c -lmysqlclient -L/usr/lib64/mysql


# 保存したルートテーブル
saved_route_set: saved_route_set.c
	gcc -Wall -o ../bin/saved_route_set saved_route_set.c -lmysqlclient -L/usr/lib64/mysql
saved_route_get: saved_route_get.c
	gcc -Wall -o ../bin/saved_route_get saved_route_get.c -lmysqlclient -L/usr/lib64/mysql

# 利用履歴テーブル
uselog_set: uselog_set.c
	gcc -Wall -o ../bin/usedlog_set usedlog_set.c -lmysqlclient -L/usr/lib64/mysql
uselog_get: uselog_get.c
	gcc -Wall -o ../bin/usedlog_get usedslog_get.c -lmysqlclient -L/usr/lib64/mysql

# ユーザテーブル
user_set: user_set.c
	gcc -Wall -o ../bin/user_set user_set.c -lmysqlclient -L/usr/lib64/mysql
user_get: user_get.c
	gcc -Wall -o ../bin/user_get user_get.c -lmysqlclient -L/usr/lib64/mysql