#include <linux/kernel.h>
#include <linux/module.h>
//#include <linux/timekeeping.h>
//#include <linux/gpio/consumer.h>
//#include <linux/mutex.h>
#include <linux/device.h>
#include <linux/sysfs.h>
#include <linux/interrupt.h>
#include <linux/kdev_t.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/gpio/driver.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <sys/time.h>

struct hc_sro4 {
	int gpio_trig;
	int gpio_echo;
	struct gpio_desc *trig_desc;
	struct gpio_desc *echo_desc;
	struct timeval time_triggered;
	struct timeval time_echoed;
	int echo_received;
	int device_triggered;
	struct mutex measurement_mutex;
	wait_queue_head_t wait_for_echo;
	unsigned long timeout;
	struct list_head list;
};

int main() {

    return 0;
}