#include<stdio.h>
#include<linux/kernel.h>
#include<sys/syscall.h>
#include<unistd.h>
#include<string.h>
#define MAX_SIZE 32
int main(){
    char name[64];
    puts("Enter process name to find: ");
    scanf("%s",name);
    long status = syscall(377, name);
    if(status == -1)
        printf("Process with inputted name is not found\n");
    else
        printf("Pid of this process: %ld\n", status);
    return 0;
}