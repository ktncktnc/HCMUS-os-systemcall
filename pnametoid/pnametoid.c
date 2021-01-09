#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/tty.h>
#include <linux/string.h>
#include "pnametoid.h"
asmlinkage long sys_pnametoid(char* process_name){
    char buf[64];
    strncpy_from_user(buf, process_name, sizeof(buf));
    printk("Pnametoid: input from user: %s\n", buf);
    struct task_struct *task;
    long pid = -1;
    for_each_process(task){
        if(strcmp(task->comm,buf) == 0){
            pid = task->pid;                 
        }
    }
    return pid;
}