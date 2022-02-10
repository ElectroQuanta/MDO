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
	{ 0xab2e3178, "module_layout" },
	{ 0xdbc282d, "class_unregister" },
	{ 0x8f33b672, "__class_register" },
	{ 0xf0e76320, "device_create_with_groups" },
	{ 0xd9a5ea54, "__init_waitqueue_head" },
	{ 0x977f511b, "__mutex_init" },
	{ 0xeb0cfe01, "gpiod_direction_output" },
	{ 0xc7524234, "gpiod_direction_input" },
	{ 0x53722970, "gpio_to_desc" },
	{ 0xacd593b3, "kmem_cache_alloc_trace" },
	{ 0xb038da91, "kmalloc_caches" },
	{ 0xbcab6ee6, "sscanf" },
	{ 0x8df99d71, "put_device" },
	{ 0xc7514ac1, "device_unregister" },
	{ 0x37a0cba, "kfree" },
	{ 0x84524457, "class_find_device" },
	{ 0x3eeb2322, "__wake_up" },
	{ 0xe14709c3, "gpiod_get_value" },
	{ 0x5e515be6, "ktime_get_ts64" },
	{ 0x9f49dcc4, "__stack_chk_fail" },
	{ 0x92540fbf, "finish_wait" },
	{ 0x8ddd8aad, "schedule_timeout" },
	{ 0x8c26d495, "prepare_to_wait_event" },
	{ 0xfe487975, "init_wait_entry" },
	{ 0x3c3ff9fd, "sprintf" },
	{ 0xc1514a3b, "free_irq" },
	{ 0xcd11c172, "gpiochip_lock_as_irq" },
	{ 0x6fa17dd5, "gpiod_to_chip" },
	{ 0xeae3dfd6, "__const_udelay" },
	{ 0x92b063e6, "gpiod_set_value" },
	{ 0xdbdb0e8b, "request_any_context_irq" },
	{ 0x2a3e761a, "gpiod_to_irq" },
	{ 0xf9a482f9, "msleep" },
	{ 0x409bcb62, "mutex_unlock" },
	{ 0xf21017d9, "mutex_trylock" },
	{ 0x2ab7989d, "mutex_lock" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "BB4ABFCCCC234A187E89FBB");
