/*
 * bsdinfo-macos 1.0.2
 * macOS port copyright (c) 2026 Xodice.
 */

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

#include <sys/types.h>
#include <sys/sysctl.h>

#include <stdio.h>

#include "bsdinfo.h"

int main()
{
    int proc_count;

    proc_count = getprocesscount();
    
    printf("\n\n");
    printappleinfo("0000000000000000011111100000000000000000000", 82); printval("Hostname", "kern.hostname");  printf("\n");
    printappleinfo("0000000000000000111111000000000000000000000", 82); printbootmethod(); printf("\n");
    printappleinfo("0000000000000001111110000000000000000000000", 82); printf(LABEL "OS:" RESET " "); printos(); printf("\n");
    printappleinfo("0000000001111111111111111111110000000000000", 220); printf(LABEL "Version:" RESET " "); printversion(); printf("\n");
    printappleinfo("0000011111111111111111111111111111000000000", 220); printcpu();  printf("\n");
    printappleinfo("0001111111111111111111111111111111110000000", 208); printmem(); printf("\n");
    printappleinfo("0011111111111111111111111111111110000000000", 208); printf(LABEL "Processes:" RESET " %d\n", proc_count);
    printappleinfo("0111111111111111111111111111110000000000000", 196); printf(LABEL "Shell:" RESET " "); printshell(); printf("\n");
    printappleinfo("0111111111111111111111111111111110000000000", 196); printuptime(); printf("\n");
    printapplelinecolor("0111111111111111111111111111111111100000000", 129); printf("\n");
    printapplelinecolor("0011111111111111111111111111111111110000000", 27); printf("\n");
    printapplelinecolor("0001111111111111111111111111111111100000000", 27); printf("\n");
    printapplelinecolor("0000111111111111111111111111111110000000000", 27); printf("\n");
    printapplelinecolor("0000001111111111111111111111110000000000000", 27); printf("\n");
    printapplelinecolor("0000000011111111111111111100000000000000000", 27); printf("\n");
    printapplelinecolor("0000000000011111111111000000000000000000000", 27); printf("\n");
    printf("\n");
    return (0);
}
