#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Azot");
MODULE_DESCRIPTION("Lab 4 Kernel Test");
MODULE_VERSION("1.0");

// Масив чисел, який передається як параметр
static int numbers[100];
static int count = 0;

// Оголошення параметрів модуля
module_param_array(numbers, int, &count, 0444);
MODULE_PARM_DESC(numbers, "Array of integers to be inverted");

// Функція для інвертування списку
static void invert_array(int *arr, int len) {
    int i, temp;
    for (i = 0; i < len / 2; i++) {
        temp = arr[i];
        arr[i] = arr[len - i - 1];
        arr[len - i - 1] = temp;
    }
}

// Ініціалізація модуля
static int __init invert_module_init(void) {
    int i;

    pr_info("Invert Module Initialized\n");

    if (count <= 0) {
        pr_err("No elements provided for inversion.\n");
        return -EINVAL;
    }

    pr_info("Original list: ");
    for (i = 0; i < count; i++) {
        pr_cont("%d ", numbers[i]);
    }
    pr_cont("\n");

    invert_array(numbers, count);

    pr_info("Inverted list: ");
    for (i = 0; i < count; i++) {
        pr_cont("%d ", numbers[i]);
    }
    pr_cont("\n");

    return 0;
}

// Деініціалізація модуля
static void __exit invert_module_exit(void) {
    pr_info("Invert Module Exited\n");
}

module_init(invert_module_init);
module_exit(invert_module_exit);

