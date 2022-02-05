#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x70035c2e, "module_layout" },
	{ 0x24563834, "class_unregister" },
	{ 0x33ec9110, "__class_register" },
	{ 0x196e27bf, "device_create_with_groups" },
	{ 0x5bbe49f4, "__init_waitqueue_head" },
	{ 0xe346f67a, "__mutex_init" },
	{ 0xd8072344, "gpiod_direction_output" },
	{ 0x7cf37efc, "gpiod_direction_input" },
	{ 0x42079654, "gpio_to_desc" },
	{ 0xf735a468, "kmem_cache_alloc_trace" },
	{ 0x59e7dbf3, "kmalloc_caches" },
	{ 0xbcab6ee6, "sscanf" },
	{ 0x2ad4234f, "put_device" },
	{ 0xc1aa8616, "device_unregister" },
	{ 0x37a0cba, "kfree" },
	{ 0xa4db956a, "class_find_device" },
	{ 0x3dcf1ffa, "__wake_up" },
	{ 0xf8d208ac, "gpiod_get_value" },
	{ 0x5e515be6, "ktime_get_ts64" },
	{ 0x86332725, "__stack_chk_fail" },
	{ 0x8ddd8aad, "schedule_timeout" },
	{ 0x49970de8, "finish_wait" },
	{ 0x647af474, "prepare_to_wait_event" },
	{ 0xfe487975, "init_wait_entry" },
	{ 0x3c3ff9fd, "sprintf" },
	{ 0xc1514a3b, "free_irq" },
	{ 0xa1c76e0a, "_cond_resched" },
	{ 0x4b2b6340, "gpiochip_lock_as_irq" },
	{ 0x1ec068c, "gpiod_to_chip" },
	{ 0x8e865d3c, "arm_delay_ops" },
	{ 0xa0ec3600, "gpiod_set_value" },
	{ 0xdbdb0e8b, "request_any_context_irq" },
	{ 0xef710e5d, "gpiod_to_irq" },
	{ 0xf9a482f9, "msleep" },
	{ 0x67ea780, "mutex_unlock" },
	{ 0xdd4ffa9b, "mutex_trylock" },
	{ 0xc271c3be, "mutex_lock" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "BB4ABFCCCC234A187E89FBB");
