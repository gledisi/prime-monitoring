include ../Makefile.general


top_srcdir=..

all: setlink setdissem

setlink: setlink.o 
	$(CC) $(LDFLAGS) -o setlink setlink.o $(LIBS) 

setdissem: setdissem.o 
	$(CC) $(LDFLAGS) -o setdissem setdissem.o $(LIBS) 

clean:
	rm -f *.o
	rm -f setlink
	rm -f setdissem

distclean: clean
	rm -f *~
	rm -f core*
	rm -f Makefile 
