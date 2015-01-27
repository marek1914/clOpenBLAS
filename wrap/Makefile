TOPDIR  = ../..
include $(TOPDIR)/Makefile.system

# PFLAG=-DDEBUG

All: libopenblas_wrap.so

test: test-sgemm-wrap test-sgemm test-sgemm-cblas test-sgemm-cblas-wrap

install:
	 install libopenblas*.so ../lib


wrap.o: wrap.c
	gcc $(CFLAGS) -fPIC -c $(PFLAG) -I$(TOPDIR)  -o wrap.o wrap.c

libopenblas_wrap.so: wrap.o
	gcc $(CFLAGS) -shared -fPIC -o libopenblas_wrap.so wrap.o -L$(TOPDIR) -lopenblas -ldl

test-sgemm-wrap: test-sgemm.c $(TOPDIR)/libopenblas.so libopenblas_wrap.so
	gcc $(CFLAGS) -o test-sgemm-wrap test-sgemm.c -L. -lopenblas_wrap

test-sgemm: test-sgemm.c $(TOPDIR)/libopenblas.so
	gcc $(CFLAGS) -o test-sgemm test-sgemm.c -L$(TOPDIR) -lopenblas

test-sgemm-cblas: test-sgemm-cblas.c $(TOPDIR)/libopenblas.so
	gcc $(CFLAGS) -o test-sgemm-cblas test-sgemm-cblas.c -L$(TOPDIR) -lopenblas

test-sgemm-cblas-wrap: test-sgemm-cblas.c $(TOPDIR)/libopenblas.so libopenblas_wrap.so
	gcc $(CFLAGS) -o test-sgemm-cblas-wrap test-sgemm-cblas.c -L. -lopenblas_wrap





clean:
	rm -f *.o
	rm -f *.so
	rm -f test-sgemm
	rm -f test-sgemm-wrap
	rm -f test-sgemm-cblas
	rm -f test-sgemm-cblas-wrap