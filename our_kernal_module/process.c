#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/cred.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Event-Triggered Message Kernel Module");

static int task_create_event(struct notifier_block *nb, unsigned long action, void *data)
{
    struct task_struct *task = (struct task_struct *)data;

    if (action == TASK_NEW) {
        printk(KERN_INFO "New Process Created: %s (PID: %d)\n", task->comm, task->pid);
    }

    return NOTIFY_OK;
}

static struct notifier_block nb = {
    .notifier_call = task_create_event,
};

static int __init event_init(void)
{
    register_module_notifier(&nb);
    printk(KERN_INFO "Event-Triggered Messages Module Loaded\n");
    return 0;
}

static void __exit event_exit(void)
{
    unregister_module_notifier(&nb);
    printk(KERN_INFO "Event-Triggered Messages Module Unloaded\n");
}

module_init(event_init);
module_exit(event_exit);