INSTALL=	install
INSTALL_EXEC=	$(INSTALL) -m 0755
CC=	gcc

target all:
	${CC} ${CFLAGS} bsdinfo.c -o bsdinfo

install:
	${INSTALL_EXEC} bsdinfo /usr/local/bin/bsdinfo

deinstall:
	rm /usr/local/bin/bsdinfo

clean:
	rm -f bsdinfo
