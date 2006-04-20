########################################################################

CXX = g++ -O2 -mtune=pentium-m

########################################################################

HEADERS_INSTALL_LIST = *.h

INSTALL_ROOT = /usr/local

INCLUDE = -I/home/mbaptist/work/codes/devel/cat
LIB = -L.

all: test

%.o: %.C *.h
	$(CXX) $(INCLUDE) -c $<

clean:
	@rm -rfv *.dat *~ *.o *.so test_cgsolver

test: test_lass

test_lass:  test_lass.o *.h
	$(CXX) -o test_lass test_lass.o

install:
	install -c -m 644 $(HEADERS_INSTALL_LIST) $(INSTALL_ROOT)/include

uninstall:
	cd $(INSTALL_ROOT) && @rm -rfv include/$(HEADERS_INSTALL_LIST)

