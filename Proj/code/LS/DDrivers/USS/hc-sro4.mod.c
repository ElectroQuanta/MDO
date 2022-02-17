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
	{ 0x44afce, "module_layout" },
	{ 0x6bc8338f, "class_unregister" },
	{ 0x4b6e133b, "__class_register" },
	{ 0x9e09ee6e, "device_create_with_groups" },
	{ 0x5bbe49f4, "__init_waitqueue_head" },
	{ 0xe346f67a, "__mutex_init" },
	{ 0xe4a50be2, "gpiod_direction_output" },
	{ 0x54535e55, "gpiod_direction_input" },
	{ 0xead0d68d, "gpio_to_desc" },
	{ 0x902ae67c, "kmem_cache_alloc_trace" },
	{ 0xa190f184, "kmalloc_caches" },
	{ 0xbcab6ee6, "sscanf" },
	{ 0x1f583dc5, "put_device" },
	{ 0xce728e, "device_unregister" },
	{ 0x37a0cba, "kfree" },
	{ 0x4043d03c, "class_find_device" },
	{ 0x3dcf1ffa, "__wake_up" },
	{ 0x1cc79a22, "gpiod_get_value" },
	{ 0x5e515be6, "ktime_get_ts64" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0x86332725, "__stack_chk_fail" },
	{ 0x8ddd8aad, "schedule_timeout" },
	{ 0x49970de8, "finish_wait" },
	{ 0x647af474, "prepare_to_wait_event" },
	{ 0xfe487975, "init_wait_entry" },
	{ 0x3c3ff9fd, "sprintf" },
	{ 0xc1514a3b, "free_irq" },
	{ 0xa1c76e0a, "_cond_resched" },
	{ 0x463fad8b, "gpiochip_lock_as_irq" },
	{ 0x837d04c8, "gpiod_to_chip" },
	{ 0x8e865d3c, "arm_delay_ops" },
	{ 0x3eec4850, "gpiod_set_value" },
	{ 0xdbdb0e8b, "request_any_context_irq" },
	{ 0x72daeeb6, "gpiod_to_irq" },
	{ 0xf9a482f9, "msleep" },
	{ 0x67ea780, "mutex_unlock" },
	{ 0xdd4ffa9b, "mutex_trylock" },
	{ 0xc271c3be, "mutex_lock" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "BB4ABFCCCC234A187E89FBB");
