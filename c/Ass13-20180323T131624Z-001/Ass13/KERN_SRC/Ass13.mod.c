#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xfa306cac, "module_layout" },
	{ 0x7485e15e, "unregister_chrdev_region" },
	{ 0xe1c3d8df, "cdev_del" },
	{ 0x37a0cba, "kfree" },
	{ 0xa51c4419, "cdev_add" },
	{ 0x68dfc59f, "__init_waitqueue_head" },
	{ 0x86ece38a, "kmem_cache_alloc_trace" },
	{ 0x600d419, "kmalloc_caches" },
	{ 0x41004cca, "cdev_init" },
	{ 0x29537c9e, "alloc_chrdev_region" },
	{ 0x2f287f0d, "copy_to_user" },
	{ 0x75bb675a, "finish_wait" },
	{ 0x622fa02a, "prepare_to_wait" },
	{ 0x4292364c, "schedule" },
	{ 0xc8b57c27, "autoremove_wake_function" },
	{ 0xb8dcb2, "current_task" },
	{ 0xe45f60d8, "__wake_up" },
	{ 0x362ef408, "_copy_from_user" },
	{ 0xc6cbbc89, "capable" },
	{ 0x50eedeb8, "printk" },
	{ 0xb4390f9a, "mcount" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "027A62271690262E16F8350");
