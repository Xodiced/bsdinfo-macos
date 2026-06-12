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

struct artline {
    const char *bits;
    const char *colors;
};

static const struct artline art[] = {
    { "        100010100111110111000        00",
      "        kkkkkkkkkkkkkkkkkkkkk        kk" },
    { "100001010101111010000000111110010001",
      "rrrrrkkkkkkkkkkkkkkkkkkkkkkkkrrrrrrkk" },
    { "100011011001111100000011100100101101",
      "rrrrrrrrkkkkkkkkkkkkkkkkkkkkkkkkrrrrrr" },
    { "100111001111011010101001101111001110",
      "rrrkkkkkkkkkkkkkkkkkkkrrrrkkkkkkkkkrr" },
    { "100000000110110011010111101100110111",
      "kkkkkkkkkkkkkkkkkkrrrrrrrrrrrrrrrrrrrr" },
    { "111001000100110011101110011100001111",
      "kkkkkkkkkkkkkkrrrrrrrrrrrrrrrrrrrrrrrr" },
    { "011010100001000010000010111000111011",
      "kkkkkkkkkkkkkkrrrrrrrrrrrrrrrrrrrrrrrr" },
    { "001101000100110001010011100010001101",
      "kkkkkkkkkkkrrrrrrrrrrrrrrrrrrrrrrrrrrr" },
    { "101011100001011110011001001110110010",
      "kkkrrrrrrrrrrrrrrrrrrrrkkkkkkkkkkkkkkk" },
    { "010100010010111101101111101100000011",
      "kkrrrrrrrrrrrrrrrrrrrrkkkkkkkkkkkkkkkk" },
    { "110100001101100100100111100100000111",
      "kkkrrrrrrrrrrrrrrrrrrrrrrrrrkkkkkkkkkk" },
    { "001011110001010001001000111010111010",
      "kkkkkrrrrrrrrrrrrrrrrrrrrrrrrkkkkkkkkk" },
    { " 010100101100100101101110011011101",
      " kkkkkrrrrrrrrrrrrrrrrrrrrrrrrkkkkkk" },
    { "  000011100100000110011110100010101",
      "  kkkkrrrrrrrrrrrrrrrrrrrrrrrrkkkkkk" },
    { "   0001000001000100101011011110111",
      "   kkkkrrrrrrrrrrrrrrrrrryyyyyyyykk" },
    { "    101101111001011000010101011101",
      "    kkkkrrrrrrrrrrrrrrryyyyyyyyykk" },
    { "      0110001100111011001010000",
      "      kkkkrrrrrrrrrryyyyyyyykkk" },
    { "       000100011001110110010100",
      "       kkkkkrrrrrrrryyyyyyyykkk" },
    { "        0110001100011101001000",
      "        kkkkkrrrrrrryyyyyyykkk" },
    { "          101101111001000010101",
      "          kkkkkrrrrrryyyyyykkk" },
    { "           0110001100111011000",
      "           kkkkkrrrggggggkkk" },
    { "             000010110000000",
      "             kkkkkrrrggggkkk" },
};

int main()
{
    int proc_count;

    proc_count = getprocesscount();
    
    printf("\n");
    printbsdinfo(art[0].bits, art[0].colors); printf("\n");
    printbsdinfo(art[1].bits, art[1].colors); printval("Hostname", "kern.hostname");  printf("\n");
    printbsdinfo(art[2].bits, art[2].colors); printbootmethod(); printf("\n");
    printbsdinfo(art[3].bits, art[3].colors); printf(LABEL "OS:" RESET " "); printos(); printf("\n");
    printbsdinfo(art[4].bits, art[4].colors); printf(LABEL "Version:" RESET " "); printversion(); printf("\n");
    printbsdinfo(art[5].bits, art[5].colors); printcpu();  printf("\n");
    printbsdinfo(art[6].bits, art[6].colors); printmem(); printf("\n");
    printbsdinfo(art[7].bits, art[7].colors); printf(LABEL "Processes:" RESET " %d\n", proc_count);
    printbsdinfo(art[8].bits, art[8].colors); printf(LABEL "Shell:" RESET " "); printshell(); printf("\n");
    printbsdinfo(art[9].bits, art[9].colors); printuptime(); printf("\n");
    printbsdinfo(art[10].bits, art[10].colors); printf("\n");
    printbsdinfo(art[11].bits, art[11].colors); printf("\n");
    printbsdinfo(art[12].bits, art[12].colors); printf("\n");
    printbsdinfo(art[13].bits, art[13].colors); printf("\n");
    printbsdinfo(art[14].bits, art[14].colors); printf("\n");
    printbsdinfo(art[15].bits, art[15].colors); printf("\n");
    printbsdinfo(art[16].bits, art[16].colors); printf("\n");
    printbsdinfo(art[17].bits, art[17].colors); printf("\n");
    printbsdinfo(art[18].bits, art[18].colors); printf("\n");
    printbsdinfo(art[19].bits, art[19].colors); printf("\n");
    printbsdinfo(art[20].bits, art[20].colors); printf("\n");
    printbsdinfo(art[21].bits, art[21].colors); printf("\n");
    printf("\n");
    return (0);
}
