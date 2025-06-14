#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

#ifdef CONFIG_UNWINDER_ORC
#include <asm/orc_header.h>
ORC_HEADER;
#endif

BUILD_SALT;
BUILD_LTO_INFO;

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



static const char ____versions[]
__used __section("__versions") =
	"\x10\x00\x00\x00\xd8\x7e\x99\x92"
	"_printk\0"
	"\x18\x00\x00\x00\xe1\xbe\x10\x6b"
	"_copy_to_user\0\0\0"
	"\x1c\x00\x00\x00\xcb\xf6\xfd\xf0"
	"__stack_chk_fail\0\0\0\0"
	"\x18\x00\x00\x00\xc2\x9c\xc4\x13"
	"_copy_from_user\0"
	"\x18\x00\x00\x00\x37\xc2\x7d\x28"
	"gpio_to_desc\0\0\0\0"
	"\x1c\x00\x00\x00\x3a\xc2\xde\x11"
	"gpiod_set_raw_value\0"
	"\x1c\x00\x00\x00\x21\xfa\xe9\x4d"
	"__register_chrdev\0\0\0"
	"\x18\x00\x00\x00\x5c\x9b\x22\x47"
	"gpio_request\0\0\0\0"
	"\x1c\x00\x00\x00\xc0\xfb\xc3\x6b"
	"__unregister_chrdev\0"
	"\x24\x00\x00\x00\x78\x5b\x1c\x26"
	"gpiod_direction_output_raw\0\0"
	"\x18\x00\x00\x00\x75\x8f\x79\x3e"
	"class_create\0\0\0\0"
	"\x14\x00\x00\x00\x52\x00\x99\xfe"
	"gpio_free\0\0\0"
	"\x18\x00\x00\x00\x2b\x2a\xef\xd9"
	"device_create\0\0\0"
	"\x18\x00\x00\x00\x11\xc3\x3c\x8f"
	"class_destroy\0\0\0"
	"\x18\x00\x00\x00\xbf\xc0\x95\x23"
	"device_destroy\0\0"
	"\x18\x00\x00\x00\xc7\xdf\x30\xcd"
	"module_layout\0\0\0"
	"\x00\x00\x00\x00\x00\x00\x00\x00";

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "CC6ADAAEED78BF850F42901");
