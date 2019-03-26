#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <sys/stat.h>
#include <fcntl.h>
#include "../lib/tlpi_hdr.h"
#include "sys/uio.h"

#ifndef BUF_SIZE        /* Allow "cc -D" to override definition */
#define BUF_SIZE 1024
#endif

int
main(int argc, char *argv[])
{
    int fd1, fd2,size1,size2, outputFd, openFlags;
    mode_t filePerms;
    ssize_t numRead1,nr1,nr2;
    char buf[BUF_SIZE];
    struct iovec iov[40];
    struct iovec iov1[2];
    struct iovec iov2[2];
    char foo[BUF_SIZE], bar[BUF_SIZE];

    if (argc != 4 || strcmp(argv[1], "--help") == 0)
        usageErr("%s old-file new-file\n", argv[0]);

    /* Open input and output files */

    fd1 = open(argv[1], O_RDONLY);

    if (fd1 == -1)
        errExit("opening file %s", argv[1]);

    fd2 = open(argv[2], O_RDONLY);
    if (fd2 == -1)
        errExit("opening file %s", argv[2]);

    openFlags = O_CREAT | O_WRONLY | O_TRUNC;
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                S_IROTH | S_IWOTH;      /* rw-rw-rw- */
    
    outputFd = open(argv[3], openFlags, filePerms);
    if (outputFd == -1)
        errExit("opening file %s", argv[3]);     
   
    FILE *fd101 = fopen(argv[1],"r");
    fseek(fd101, 0, SEEK_END);    // 파일 포인터를 파일의 끝으로 이동시킴
    size1 = ftell(fd101); 
    
    FILE *fd102 = fopen(argv[2],"r");
    fseek(fd102, 0, SEEK_END);    // 파일 포인터를 파일의 끝으로 이동시킴
    size2 = ftell(fd102); 

    iov1[0].iov_base = foo;
    //iov1[0].iov_len = sizeof (size1);
    iov1[0].iov_len = size1;

    iov2[0].iov_base = bar;
    //iov2[0].iov_len = sizeof (fd2);
    iov2[0].iov_len = size2;


    nr1 = readv (fd1, iov1, 1);
    nr2 = readv (fd2, iov2, 1); 
    
    iov[0] = iov1[0];
    iov[1] = iov2[0];
 
    writev(outputFd,iov,2);


    if (numRead1 == -1)
        errExit("read");

    if (close(fd1) == -1)
        errExit("close readFd1");
    if (close(fd2) == -1)
        errExit("close readFd2");
    if (close(outputFd) == -1)
        errExit("close output");

    exit(EXIT_SUCCESS);
}
