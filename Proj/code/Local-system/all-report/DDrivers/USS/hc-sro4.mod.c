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
	{ 0x8ed3ed4c, "module_layout" },
	{ 0x32f74305, "class_unregister" },
	{ 0xc88c3f2f, "__class_register" },
	{ 0x970dc5f5, "device_create_with_groups" },
	{ 0xd9a5ea54, "__init_waitqueue_head" },
	{ 0x977f511b, "__mutex_init" },
	{ 0xd1c27bf5, "gpiod_direction_output" },
	{ 0x54f55b00, "gpiod_direction_input" },
	{ 0xc9ba9118, "gpio_to_desc" },
	{ 0xedb53acc, "kmem_cache_alloc_trace" },
	{ 0x709f74d4, "kmalloc_caches" },
	{ 0xbcab6ee6, "sscanf" },
	{ 0x4c60e236, "put_device" },
	{ 0x2dddab57, "device_unregister" },
	{ 0x37a0cba, "kfree" },
	{ 0xd95ad64e, "class_find_device" },
	{ 0x3eeb2322, "__wake_up" },
	{ 0x66778c5e, "gpiod_get_value" },
	{ 0x5e515be6, "ktime_get_ts64" },
	{ 0x9f49dcc4, "__stack_chk_fail" },
	{ 0x92540fbf, "finish_wait" },
	{ 0x8ddd8aad, "schedule_timeout" },
	{ 0x8c26d495, "prepare_to_wait_event" },
	{ 0xfe487975, "init_wait_entry" },
	{ 0x3c3ff9fd, "sprintf" },
	{ 0xc1514a3b, "free_irq" },
	{ 0x28b168e0, "gpiochip_lock_as_irq" },
	{ 0x931fa801, "gpiod_to_chip" },
	{ 0xeae3dfd6, "__const_udelay" },
	{ 0x3ac96a8d, "gpiod_set_value" },
	{ 0xdbdb0e8b, "request_any_context_irq" },
	{ 0x17a27346, "gpiod_to_irq" },
	{ 0xf9a482f9, "msleep" },
	{ 0x409bcb62, "mutex_unlock" },
	{ 0xf21017d9, "mutex_trylock" },
	{ 0x2ab7989d, "mutex_lock" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "BB4ABFCCCC234A187E89FBB");
