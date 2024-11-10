#include <stdio.h>
#include "processC_dbus_us.h"
#include "processD_dbus_us.h"

int main() {
    // Gọi các hàm từ thư viện chia sẻ
    hello_processA();
    hello_processB();
    return 0;
}