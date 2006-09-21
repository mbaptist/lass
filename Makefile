########################################################################

CXX = g++ -O3 -funroll-loops -fexpensive-optimizations  -mtune=opteron -fPIC

AR = ar rcs


########################################################################


HEADERS_INSTALL_LIST = *.h

INSTALL_ROOT = /usr/local

INCLUDE = -I/home/mbaptist/work/codes/devel/cat
LIB = -L.

OBJECTS=./vzdeigen/vzdeigen.o


########################################################################


all: liblass testing

%.o: %.C *.h
	$(CXX) $(INCLUDE) -c $<

clean:
	@rm -rfv *.dat *.o *.so *.a
	$(MAKE) -C testing distclean
	$(MAKE) -C cgsolver distclean
	$(MAKE) -C vzdeigen distclean

distclean: clean
	@rm -rfv *.dat *~	
	$(MAKE) -C testing distclean
	$(MAKE) -C cgsolver distclean
	$(MAKE) -C vzdeigen distclean
	
liblass:
	$(MAKE) -C vzdeigen
	$(CXX) -shared -o liblass.so $(OBJECTS) -L/opt/intel/fc/9.0/lib -lifcore
	$(AR) liblass.a $(OBJECTS)

testing:
	$(MAKE) -C testing

#install:
#	install -c -m 644 $(HEADERS_INSTALL_LIST) $(INSTALL_ROOT)/include
#
#uninstall:
#	cd $(INSTALL_ROOT) && @rm -rfv include/$(HEADERS_INSTALL_LIST)

