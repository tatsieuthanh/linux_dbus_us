// processA_dbus_us.h
#ifndef PROCESSA_DBUS_US_H
#define PROCESSA_DBUS_US_H

#include <dbus/dbus.h>

// Hàm tính tổng hai số
int hello_processA();

DBusConnection* setup_dbus_connection() ;

void send_message(int n, DBusConnection *conn) ;

void* send_message_thread(void *arg) ;

#endif // PROCESSA_DBUS_US_H