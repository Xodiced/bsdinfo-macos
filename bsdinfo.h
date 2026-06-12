/*-
 * Copyright (c) 2012, Jakub Szafrański <samu@pirc.pl>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */


#include <errno.h>
#include <libproc.h>
#include <mach/mach.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sysctl.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#define LABEL "\033[1;31m"
#define RESET "\033[0;0m"
#define ART_WIDTH 43

int printapplelinecolor(const char *line, int stripe)
{
    int i;

    for (i = 0; line[i] != '\0'; ++i) {
        int color;

        if (line[i] == ' ' || line[i] == '0') {
            putchar(' ');
            continue;
        }

        color = stripe;
        printf("\033[38;5;%dm%c" RESET, color, line[i]);
    }

    return (i);
}

int printappleline(const char *line)
{
    return (printapplelinecolor(line, 196));
}

void printappleinfo(const char *line, int stripe)
{
    int width;

    width = printapplelinecolor(line, stripe);
    while (width < ART_WIDTH) {
        putchar(' ');
        ++width;
    }
}

int printstring(const char *value)
{
    if (value == NULL || value[0] == '\0') {
        printf("unknown");
    } else {
        printf("%s", value);
    }

    return (0);
}


int psysctl(const char *name)
{
    char buf[256];
    size_t size = sizeof(buf);
    
    memset(buf, 0, sizeof(buf));
    if (sysctlbyname(name, buf, &size, NULL, 0) != 0) {
        printstring(NULL);
        return (1);
    }
    printstring(buf);
    return (0);
}

int printval(const char *val, const char *name) 
{
    printf(LABEL "%s:" RESET " ", val);
    psysctl(name);
    return (0);
}

int printarch()
{
    char buf[256];
    size_t size = sizeof(buf);

    memset(buf, 0, sizeof(buf));
    if (sysctlbyname("hw.machine", buf, &size, NULL, 0) != 0) {
        return (psysctl("hw.machine_arch"));
    }

    printstring(buf);
    return (0);
}

int printos()
{
    char version[256];
    size_t size = sizeof(version);

    memset(version, 0, sizeof(version));
    printf("macOS ");
    if (sysctlbyname("kern.osproductversion", version, &size, NULL, 0) == 0) {
        printstring(version);
    } else {
        printstring(NULL);
    }
    printf(" ");
    printarch();
    return (0);
}

int printversion()
{
    char build[256];
    size_t size = sizeof(build);

    memset(build, 0, sizeof(build));
    if (sysctlbyname("kern.osversion", build, &size, NULL, 0) == 0) {
        printstring(build);
        return (0);
    }

    return (psysctl("kern.osrelease"));
}

int printuptime() 
{
    struct timeval boot_time;
    struct timespec tp;
    size_t size;
    time_t uptime;
    int days, hrs, mins;

    if (clock_gettime(CLOCK_UPTIME_RAW, &tp) == 0) {
        uptime = tp.tv_sec;
    } else {
        size = sizeof(boot_time);
        if (sysctlbyname("kern.boottime", &boot_time, &size, NULL, 0) == -1) {
            uptime = 0;
        } else {
            uptime = time(NULL) - boot_time.tv_sec;
        }
    }

    if (uptime > 60)
        uptime += 30;
    days = (int)(uptime / 86400);
    uptime %= 86400;
    hrs = (int)(uptime / 3600);
    uptime %= 3600;
    mins = (int)(uptime / 60);

    (void)printf(LABEL "Uptime: " RESET);
    if (days > 0)
        (void)printf("%d day%s ", days, days > 1 ? "s" : "");
    if (hrs > 0 && mins > 0)
        (void)printf("%d:%02d", hrs, mins);
    else if (hrs == 0 && mins > 0) 
        (void)printf("0:%02d", mins);
    else 
        (void)printf("0:00");

    return (0);
}

int printshell()
{
    char* shell = getenv("SHELL");
    if (shell != NULL) {
        int slen = strlen(shell);
        for (; slen > 0; --slen) if (shell[slen] == '/') break;
        slen = slen+1;
        while(shell[slen] != '\0') {
            printf("%c", shell[slen]);
            ++slen;
        }
        if (slen == 1) printf("%s", shell);
    } else {
        printstring(NULL);
    }
    return (0);
}

int printmem()
{
    mach_msg_type_number_t count;
    vm_statistics64_data_t vmstat;
    uint64_t active;
    uint64_t compressed;
    uint64_t wired;
    uint64_t used;
    uint64_t total;
    int64_t page_size;
    size_t size;

    printf(LABEL "RAM:" RESET " ");

    page_size = sysconf(_SC_PAGESIZE);
    total = 0;
    size = sizeof(total);
    if (sysctlbyname("hw.memsize", &total, &size, NULL, 0) != 0) {
        total = 0;
    }

    count = HOST_VM_INFO64_COUNT;
    if (host_statistics64(mach_host_self(), HOST_VM_INFO64,
        (host_info64_t)&vmstat, &count) != KERN_SUCCESS || page_size <= 0) {
        printf("unknown");
        return (1);
    }

    active = (uint64_t)vmstat.active_count * (uint64_t)page_size;
    compressed = (uint64_t)vmstat.compressor_page_count * (uint64_t)page_size;
    wired = (uint64_t)vmstat.wire_count * (uint64_t)page_size;
    used = active + compressed + wired;

    printf("%lluM / ", used / 1024 / 1024);
    printf("%lluM", total / 1024 / 1024);
    return (0);
}

int printrmws(char *str) {
    short int space = 0;
    int i = 0;
    int s = strlen(str);
    for (; i < s; ++i) {
        if (str[i] != ' ') space = 0;
        if (space == 0) printf("%c", str[i]);
        if (str[i] == ' ') space = 1;
        else space = 0;
    }
    return (0);
}

int printcpu()
{
    printf(LABEL "CPU:" RESET " ");
    char buf[256];
    size_t size = sizeof(buf);

    memset(buf, 0, sizeof(buf));
    if (sysctlbyname("machdep.cpu.brand_string", buf, &size, NULL, 0) == 0) {
        printrmws(buf);
        return (0);
    }

    memset(buf, 0, sizeof(buf));
    size = sizeof(buf);
    if (sysctlbyname("hw.model", buf, &size, NULL, 0) != 0) {
        printstring(NULL);
        return (1);
    }
    printrmws(buf);
    return (0);
}

int printbootmethod()
{
    int arm64;
    char machine[256];
    size_t size;

    printf(LABEL "Bootmethod:" RESET " ");

    arm64 = 0;
    size = sizeof(arm64);
    if (sysctlbyname("hw.optional.arm64", &arm64, &size, NULL, 0) == 0 && arm64 == 1) {
        printf("iBoot");
        return (0);
    }

    memset(machine, 0, sizeof(machine));
    size = sizeof(machine);
    if (sysctlbyname("hw.machine", machine, &size, NULL, 0) == 0) {
        if (strncmp(machine, "arm64", 5) == 0) {
            printf("iBoot");
        } else if (strcmp(machine, "x86_64") == 0 || strcmp(machine, "i386") == 0) {
            printf("EFI");
        } else {
            printf("Unknown");
        }
        return (0);
    }

    printf("Unknown");
    return (0);
}

int getprocesscount()
{
    int mib[3];
    int proc_count;
    size_t size;

    mib[0] = CTL_KERN;
    mib[1] = KERN_PROC;
    mib[2] = KERN_PROC_ALL;
    size = 0;

    if (sysctl(mib, 3, NULL, &size, NULL, 0) == 0 && size > 0) {
        return ((int)(size / sizeof(struct kinfo_proc)));
    }

    proc_count = proc_listpids(PROC_ALL_PIDS, 0, NULL, 0);
    if (proc_count <= 0) {
        return (0);
    }

    return (proc_count / (int)sizeof(pid_t));
}
