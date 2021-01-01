#include<stdio.h>
#include"jogging.h"

int main() {
    USER_TABLE ut = user_select();
    printf("%s\n");
    USEDLOG_TABLE ult = usedlog_select();
    printf("%s\n")
}