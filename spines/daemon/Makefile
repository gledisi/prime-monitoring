include ../Makefile.general

.PHONY: all clean distclean


top_srcdir=..

OBJECTS=node.o link.o network.o reliable_datagram.o state_flood.o \
		link_state.o protocol.o hello.o kernel_routing.o route.o udp.o \
		reliable_udp.o realtime_udp.o session.o reliable_session.o \
		multicast.o intrusion_tol_udp.o priority_flood.o reliable_flood.o \
		multipath.o dissem_graphs.o lex.yy.o y.tab.o configuration.o spines.o \
		security.o

ifeq (1, $(WIRELESS_SUPPORT))
	LOCAL_CFLAGS += -DSPINES_WIRELESS
	OBJECTS += wireless.o
endif

all: spines 

spines: $(OBJECTS)
	$(CC) $(LDFLAGS) -o spines $(OBJECTS) $(LIBS) $(EXTRALIBS)

parser:
	$(YACC) -d config_parse.y
	$(LEX) config_gram.l

clean:
	rm -f *.o
	rm -f *.to
	rm -f spines
	rm -f spines.exe

distclean: clean
	rm -f *~
	rm -f core*
	rm -f config.h Makefile 
