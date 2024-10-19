#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/timer.h>
#include <linux/init.h>
#include <linux/notifier.h>
#include <linux/cred.h>
#include <linux/sched/signal.h>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Kernel Module with Event-Triggered and Time-Based Messages");

static struct timer_list my_timer;

// Timer callback function
void timer_callback(struct timer_list *timer)
{
    printk(KERN_INFO "Welcome to the Kernel! Current time: %lu\n", jiffies);
    mod_timer(&my_timer, jiffies + msecs_to_jiffies(5000)); // Reschedule for 5 seconds
}

// Notifier for task creation events
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

// Module initialization
static int __init module_init_func(void)
{
    printk(KERN_INFO "Kernel Module Loaded\n");
   
    // Register module notifier for process creation
    register_module_notifier(&nb);

    timer_setup(&my_timer, timer_callback, 0);
    mod_timer(&my_timer, jiffies + msecs_to_jiffies(5000)); // Set timer to fire after 5 seconds
   
    return 0;
}

// Module exit
static void __exit module_exit_func(void)
{
    del_timer(&my_timer);
    unregister_module_notifier(&nb);
    printk(KERN_INFO "Kernel Module Unloaded\n");
}

module_init(module_init_func);
module_exit(module_exit_func);