#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/uaccess.h>
#include <linux/errno.h>
#include <linux/mm.h>

struct process_info {
    char state[16];
    unsigned long memory_usage;
    char name[TASK_COMM_LEN];
};

SYSCALL_DEFINE2(get_process_details, pid_t, pid, void __user *, user_info) {
    struct task_struct *task;
    struct process_info info;

    task = pid_task(find_vpid(pid), PIDTYPE_PID);
    if (!task) return -ESRCH;

    if (task->__state == TASK_RUNNING) 			  strncpy(info.state, "RUNNING", sizeof(info.state) - 1);
    else if (task->__state == TASK_INTERRUPTIBLE) strncpy(info.state, "SLEEPING", sizeof(info.state) - 1);
    else 								 	      strncpy(info.state, "UNKNOWN", sizeof(info.state) - 1);
    info.state[sizeof(info.state) - 1] = '\0';
    
    info.memory_usage = task->mm ? task->mm->total_vm * PAGE_SIZE : 0;
    strncpy(info.name, task->comm, TASK_COMM_LEN);
    info.name[TASK_COMM_LEN - 1] = '\0';

    if (copy_to_user(user_info, &info, sizeof(info))) return -EFAULT;

    return 0;
}
