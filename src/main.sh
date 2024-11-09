#!/bin/bash

# Biên dịch chương trình  ===> chmod +x main.sh
#make

# Thiết lập biến môi trường để tìm thư viện chia sẻ
export LD_LIBRARY_PATH=..:$LD_LIBRARY_PATH

# Thực thi chương trình
./main