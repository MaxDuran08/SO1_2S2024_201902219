#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/sysinfo.h>
#include <linux/proc_fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tu Nombre");
MODULE_DESCRIPTION("Un módulo del kernel que imprime información del sistema");

static int __init info_init(void) {
    struct sysinfo info;
    si_meminfo(&info);
    struct task_struct *task;
    int padre = 0;
    int hijo = 0;

    printk(KERN_INFO "Total RAM: %lu MB\n", info.totalram * info.mem_unit / (1024 * 1024));
    printk(KERN_INFO "Free RAM: %lu MB\n", info.freeram * info.mem_unit / (1024 * 1024));

    for_each_process(task) {
        if (task->pid == 1) {
            padre++;
        } else if (task->parent->pid == 1) {
            hijo++;
        }
    }

    printk(KERN_INFO "Procesos Padre: %d\n", padre);
    printk(KERN_INFO "Procesos Hijos: %d\n", hijo);

    return 0;
}

static void __exit info_exit(void) {
    printk(KERN_INFO "Módulo descargado\n");
}

module_init(info_init);
module_exit(info_exit);
