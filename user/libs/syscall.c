#include <unistd.h>
#include <stdarg.h>
d
#define MAX_ARGS   5

/* 系统调用入口 */
static int syscall(int num, ...) {
    va_list ap;
    va_start(ap, num);
    uint32_t a[MAX_ARGS];
    int i, ret;
    for (i = 0; i < MAX_ARGS; i ++) {
        a[i] = va_arg(ap, uint32_t);
    }
    va_end(ap);


	asm volatile (
		"int %1;"
		: "=a" (ret)
		: "i"  (T_SYSCALL),
		  "a"  (num),
		  "d"  (a[0]),
		  "c"  (a[1]),
		  "b"  (a[2]),
		  "D"  (a[3]),
		  "S"  (a[4])
		: "cc", "memory"
	);

	return ret;
}

int sys_exit(int error_code) {
	return syscall(SYS_exit, error_code);
}

int sys_fork(void) {
	return syscall(SYS_fork);
}

int sys_yield(void) {
	return syscall(SYS_yield);
}

int sys_getpid(void) {
	return syscall(SYS_getpid);
}

int sys_putc(int c) {
	return syscall(SYS_putc, c);
}

int sys_pgdir(void) {
	return syscall(SYS_pgdir);
}