PREFIX?=/usr/local
CFLAGS=-g -Wall -I${PREFIX}/apr/include/apr-1 -I${PREFIX}/apr/include/apr-util-1
LDFLAGS=-L${PREFIX}/apr/lib
LDLIBS=-lapr-1 -pthread -laprutil-1

all: devpkg

devpkg: bstrlib.o db.o shell.o cmds.o


install: all
	install -d $(DESTDIR)/$(PREFIX)/bin/
	install devpkg $(DESTDIR)/$(PREFIX)/bin/

clean:
	rm -r *.o
	rm -f devpkg
	rm -rf *.dSYM

uninstall:
	make clean
	sudo rm /usr/local/bin/devpkg
