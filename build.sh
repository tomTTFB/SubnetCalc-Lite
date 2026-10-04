gcc -Os -s -fno-asynchronous-unwind-tables -fno-stack-protector -no-pie -Wl,--gc-sections -Wl,-z,noseparate-code -o main main.c
ls -l main