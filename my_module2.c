#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sysfs.h>
#include <linux/kobject.h>
#include <linux/string.h>


static struct kobject *my_kobject;

int cat_calls = 0;

static ssize_t my_sys_show(struct kobject *kobj,
			   struct kobj_attribute *attr,
			   char *buf)
{
	cat_calls++;
	return sprintf(buf, "%d\n", cat_calls);
}

static ssize_t my_sys_store(struct kobject *kobj, struct kobj_attribute *attr, char *buf, size_t count)
{
	int tmp_int = 0;

	memcpy(&tmp_int, buf, count);
	cat_calls += tmp_int;

	return count;
}

static struct kobj_attribute my_sys_attr = __ATTR(my_sys, 0660, 
					my_sys_show, my_sys_store);

int init_module(void)
{
	int err;
	printk(KERN_INFO "Hello world\n");
	my_kobject = kobject_create_and_add("my_kobject", kernel_kobj);
	err = sysfs_create_file(my_kobject, &my_sys_attr.attr);
	return err;
}

void cleanup_module(void)
{
	sysfs_remove_file(my_kobject, &my_sys_attr.attr);
	kobject_del(my_kobject);
	printk(KERN_INFO "Goodbye world\n");
}

MODULE_LICENSE("GPL");
