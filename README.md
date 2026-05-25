# bsdinfo-macos

`bsdinfo-macos` is a macOS clone of the FreeBSD `bsdinfo` terminal system
information utility.

It keeps the same compact `bsdinfo`-style output, ordering, labels, and terminal
feel, but replaces the FreeBSD ASCII art with a classic rainbow Apple-style
terminal logo and reads system information from macOS/Darwin APIs.

## What It Shows

- Hostname
- Boot method
- macOS version and CPU architecture
- macOS build version
- CPU model
- RAM usage
- Process count
- Login shell
- Uptime

## Preview

```text
                 111111                    Hostname: MacBook.local
                111111                     Bootmethod: EFI
               111111                      OS: macOS 26.5 arm64
         111111111111111111111             Version: 25F71
     11111111111111111111111111111         CPU: Apple M1
   111111111111111111111111111111111       RAM: 15518M / 16384M
  1111111111111111111111111111111          Processes: 820
 11111111111111111111111111111             Shell: fish
 11111111111111111111111111111111          Uptime: 1:16
```

The real output is colorized in the terminal.

## Build

```sh
make
```

## Run

```sh
./bsdinfo
```

## Install

```sh
make install
```

By default this installs to `/usr/local/bin/bsdinfo`.

To install somewhere else, regenerate the Makefile with a custom prefix:

```sh
sh configure --prefix=/opt/local
make
make install
```

## Credits

Inspired by the FreeBSD `bsdinfo` utility by Jakub Szafranski.

This project is not FreeBSD `bsdinfo`; it is a macOS-focused clone that aims to
preserve the same spirit and terminal layout while using macOS system APIs.
