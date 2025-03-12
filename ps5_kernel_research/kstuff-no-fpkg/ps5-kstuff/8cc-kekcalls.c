#include <printf/printf.h>
#include <ps4/errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/filio.h>
#include <unistd.h>
#include <time.h>

uint64_t __builtin_gadget_addr(const char*);

int kekcall(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e, uint64_t f, uint64_t g)
{
    uint64_t rop[40] = {
        __builtin_gadget_addr("mov rax, [rdi]"),
        __builtin_gadget_addr("pop rcx"),
        (uint64_t)(rop+39),
        __builtin_gadget_addr("mov [rcx], rax"),
        __builtin_gadget_addr("pop rsi"),
        8,
        __builtin_gadget_addr("add rdi, rsi"),
        __builtin_gadget_addr("pop rcx"),
        (uint64_t)(rop+35),
        __builtin_gadget_addr("mov [rcx], rdi"),
        __builtin_gadget_addr("mov rax, r8"),
        __builtin_gadget_addr("pop rcx"),
        (uint64_t)(rop+37),
        __builtin_gadget_addr("mov [rcx], rax"),
        __builtin_gadget_addr("pop rdi"),
        a,
        __builtin_gadget_addr("pop rsi"),
        b,
        __builtin_gadget_addr("pop rdx"),
        c,
        __builtin_gadget_addr("pop rcx"),
        d,
        __builtin_gadget_addr("pop r8"),
        e,
        __builtin_gadget_addr("pop r9"),
        f,
        __builtin_gadget_addr("pop rax"),
        g,
        __builtin_gadget_addr("$getppid_addr + 7"),
        __builtin_gadget_addr("pop rcx"),
        (uint64_t)(rop+33),
        __builtin_gadget_addr("mov [rcx], rax"),
        __builtin_gadget_addr("pop rcx"),
        0,
        __builtin_gadget_addr("pop rdi"),
        0,
        __builtin_gadget_addr("pop r8"),
        0,
        __builtin_gadget_addr("pop rsp"),
        0,
    };
    return ((uint64_t(*)(void))rop)();
}

#define KEKCALL_GETPPID  __builtin_gadget_addr("dq 0x000000027")
#define KEKCALL_READ_DR  __builtin_gadget_addr("dq 0x100000027")
#define KEKCALL_WRITE_DR __builtin_gadget_addr("dq 0x200000027")

int main(void)
{
    printf("%d\n", kekcall(0, 0, 0, 0, 0, 0, KEKCALL_GETPPID));
    uint64_t dr[6] = {0};
    printf("%d\n", kekcall((uint64_t)dr, 0, 0, 0, 0, 0, KEKCALL_READ_DR));
    printf("%p %p %p %p %p %p\n", dr[0], dr[1], dr[2], dr[3], dr[4], dr[5]);
    dr[0] = 0x41414141;
    dr[1] = 0x42424242;
    dr[2] = 0x43434343;
    dr[3] = 0x44444444;
    dr[4] |= 3;
    dr[5] = 0x401;
    printf("%d\n", kekcall((uint64_t)dr, 0, 0, 0, 0, 0, KEKCALL_WRITE_DR));
    printf("%d\n", kekcall((uint64_t)dr, 0, 0, 0, 0, 0, KEKCALL_READ_DR));
    printf("%p %p %p %p %p %p\n", dr[0], dr[1], dr[2], dr[3], dr[4], dr[5]);
    for(int i = 0; i < 10; i++)
    {
        nanosleep(&(const struct timespec){1, 0}, 0);
        printf("%d\n", kekcall((uint64_t)dr, 0, 0, 0, 0, 0, KEKCALL_READ_DR));
        printf("%p %p %p %p %p %p\n", dr[0], dr[1], dr[2], dr[3], dr[4], dr[5]);
    }
    /*int sock = socket(AF_UNIX, SOCK_DGRAM, 0);
    int q = 0;
    printf("%d", ioctl(sock, 0x40045145, &q));
    printf(" %d %d\n", errno, q);
    q = 1;
    printf("%d", ioctl(sock, FIONBIO, &q));
    printf(" %d %d\n", errno, q);
    printf("%d", ioctl(0, 0x40045145, &q));
    printf(" %d %d\n", errno, q);*/
    printf("%d\n", kekcall((uint64_t)dr, 0, 0, 0, 0, 0, KEKCALL_READ_DR));
    printf("%p %p %p %p %p %p\n", dr[0], dr[1], dr[2], dr[3], dr[4], dr[5]);
    return 0;
}
