# bsdinfo-macos

`bsdinfo-macos` is a macOS clone of the FreeBSD `bsdinfo` terminal system
information utility.

It keeps the same compact `bsdinfo`-style output, ordering, labels, terminal
feel, and FreeBSD-style binary logo while reading system information from
macOS/Darwin APIs.

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
        100010100111110111000        00
100001010101111010000000111110010001Hostname: MacBook.local
100011011001111100000011100100101101Bootmethod: EFI
100111001111011010101001101111001110OS: macOS 27.0 arm64
100000000110110011010111101100110111Version: 26A5353q
111001000100110011101110011100001111CPU: Apple M1
011010100001000010000010111000111011RAM: 15518M / 16384M
001101000100110001010011100010001101Processes: 820
101011100001011110011001001110110010Shell: fish
010100010010111101101111101100000011Uptime: 1:16
```

The real output is colorized in the terminal.

## Build

You need a C compiler. On macOS, installing the Xcode Command Line Tools is
enough:

```sh
xcode-select --install
```

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
./configure --prefix=/opt/local
make
make install
```

## Credits

Inspired by the FreeBSD `bsdinfo` utility by Jakub Szafranski.

This project is not FreeBSD `bsdinfo`; it is a macOS-focused clone that aims to
preserve the same spirit and terminal layout while using macOS system APIs.

## License

BSD 2-Clause. See [LICENSE](LICENSE).
