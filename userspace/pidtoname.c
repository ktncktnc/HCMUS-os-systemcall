#include<stdio.h>
#include<linux/kernel.h>
#include<sys/syscall.h>
#include<unistd.h>
#include<string.h>
#define MAX_SIZE 32
int main(){
    int pid;
    char name[64];
    puts("Enter pid to find: ");
    scanf("%d",pid);
    long status = syscall(378, pid, name, 64);
    printf("Syscall pnametoid returned: name = %s with status code = %ld\n", name, status);
    return 0;
}