#include<unistd.h>

//printf()を使わずにシステムコールwrite()を使って
//Hello, world!を表示させる

int main(){

//write(int fd, const void *buf, size_t count);
//fd = file descriptor
write(1, "Hello World!\n", 13);

return 0;

}
