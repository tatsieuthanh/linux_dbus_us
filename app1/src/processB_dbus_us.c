#include<stdio.h>
#include<unistd.h>
#include "processB_dbus_us.h"

void *hello_processB() {
    while (1) {
        printf("Hello from process B\n");
        sleep(1);
    }
    return NULL;
}