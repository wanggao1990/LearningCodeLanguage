#include <stdio.h>
#include <sys/uio.h>

int test_readv() 
{
    struct iovec vec[2];
    char buf1[] = "ABCDEFG";
    char buf2[] = "1234567";
  
    vec[0].iov_base = buf1;
    vec[0].iov_len = 3;
    vec[1].iov_base = buf2;
    vec[1].iov_len = 4;

    size_t iovLen= sizeof(vec)/sizeof(vec[0]);
    
    // 多个缓冲中的数据一次写出
    int str_len = writev(1, vec, iovLen); // fileno(stdout) = 1 ,是系统标准输出文件描述符
    puts("");
    printf("Write bytes: %d \n", str_len);

    return 0;
}

int test_writev() 
{
    struct iovec vec[2];
    char buf1[100] = {};
    char buf2[100] = {};
    
    vec[0].iov_base = buf1;
    vec[0].iov_len = 2;     
    vec[1].iov_base = buf2;
    vec[1].iov_len = 3;

    size_t iovLen= sizeof(vec)/sizeof(vec[0]);

    //把数据放到多个缓冲中储存
    int str_len = readv(2, vec, iovLen);  // fileno(stdout) =2 是从标准输入接收数据
    printf("Read bytes: %d \n", str_len);
    printf("First message: %s \n", buf1);
    printf("Second message: %s \n", buf2);

    return 0;
}

int main()
{
  test_readv();
  test_writev();
}