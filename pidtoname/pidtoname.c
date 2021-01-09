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
    if(pid < 0) return -1;

    //find pid
    pid_struct = find_get_pid(pid);

    //get task with this pid
    task = pid_task(pid_struct, PIDTYPE_PID);

    //if no task found, return -1
    if(task == NULL) return -1;
    
    //write to buf with size = len 01
    long written_len = copy_to_user(buf, task->comm, len - 1);


    //If error, return -1
    if(written_len == 0) return 0;

    //Success
    if(written_len > 0) return (long)(len - 1 + written_len);

    
    else return -1;
    
}
