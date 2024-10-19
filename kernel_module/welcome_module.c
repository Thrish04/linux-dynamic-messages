#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/time.h>
static char *user_name="User";
module_param(user_name,charp,0000);
MODULE_PARM_DESC(user_name,"The name of the user");
static const char *welcome_messages[]={
"welcome aboard!, Linux is fun to learn",
"Greetings, let's have a productive day!"

};
static int msg_index=0;
static int __init welcome_init(void){
struct timespec64 ts;
ktime_get_real_ts64(&ts);
printk(KERN_INFO "Dynamic Welcome: %s\n",welcome_messages[msg_index]);
printk(KERN_INFO "Welcome, %s!\n",user_name);
msg_index=(msg_index+1)%ARRAY_SIZE(welcome_messages);
return 0;
}
static void __exit welcome_exit(void){
printk(KERN_INFO "Goodbye, %s! Module unloaded.\n",user_name);
}
module_init(welcome_init);
module_exit(welcome_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your name");
MODULE_DESCRIPTION("A simple kernel module that prints a welcome message");