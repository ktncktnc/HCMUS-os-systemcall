#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/tty.h>
#include <linux/string.h>
#include "pidtoname.h"
asmlinkage long sys_pidtoname(int pid, char* buf, int len){
    struct task_struct *task;
    struct pid *pid_struct;

    printk("Pidtoname: input from user: %d\n", pid);
    //Wrong pid, return -1
    if(pid < 1) return -1;

    //find pid
    pid_struct = find_get_pid(pid);

    //get task with this pid
    task = pid_task(pid_struct, PIDTYPE_PID);

    //if no task found, return -1
    if(task == NULL) return -1;
    
    if(strlen(task->comm) > len - 1) return strlen(task->comm);

    //write to buf with size = len 01
    long written_len = copy_to_user(buf, task->comm, len);

    if(written_len == 0) return 0;

    else return -1;
    
}