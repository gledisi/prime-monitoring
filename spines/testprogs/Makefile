include ../Makefile.general

.PHONY: all clean distclean


top_srcdir=..

TESTPROGS=sp_tflooder sp_uflooder sp_bflooder sp_xcast sp_ping sping t_flooder u_flooder g_flooder mcast_recv port2spines spines2port new_t_flooder

all: $(TESTPROGS)

sp_ping: sp_ping.o $(LIBSPINES_LIB_FILE)
	$(CC) $(LDFLAGS) -o sp_ping sp_ping.o $(LIBS)

sp_tflooder: sp_tflooder.o $(LIBSPINES_LIB_FILE)
	$(CC) $(LDFLAGS) -o sp_tflooder sp_tflooder.o $(LIBS)

sp_uflooder: sp_uflooder.o $(LIBSPINES_LIB_FILE)
	$(CC) $(LDFLAGS) -o sp_uflooder sp_uflooder.o $(LIBS)

sp_bflooder: sp_bflooder.o $(LIBSPINES_LIB_FILE)
	$(CC) $(LDFLAGS) -o sp_bflooder sp_bflooder.o $(LIBSPINES_LIB_FILE) $(LIBS)

port2spines: port2spines.o $(LIBSPINES_LIB_FILE)
	$(CC) $(LDFLAGS) -o port2spines port2spines.o $(LIBSPINES_LIB_FILE) $(LIBS)

spines2port: spines2port.o $(LIBSPINES_LIB_FILE)
	$(CC) $(LDFLAGS) -o spines2port spines2port.o $(LIBSPINES_LIB_FILE) $(LIBS)

sp_xcast: sp_xcast.o $(LIBSPINES_LIB_FILE)
	$(CC) $(LDFLAGS) -o sp_xcast sp_xcast.o $(LIBS)

sping: sping.o
	$(CC) $(LDFLAGS) -o sping sping.o $(LIBS)

t_flooder: t_flooder.o
	$(CC) $(LDFLAGS) -o t_flooder t_flooder.o $(LIBS)

new_t_flooder: new_t_flooder.o
	$(CC) $(LDFLAGS) -o new_t_flooder new_t_flooder.o $(LIBS)

u_flooder: u_flooder.o
	$(CC) $(LDFLAGS) -o u_flooder u_flooder.o $(LIBS)

g_flooder: g_flooder.o
	$(CC) $(LDFLAGS) -o g_flooder g_flooder.o $(LIBS)

mcast_recv: mcast_recv.o
	$(CC) $(LDFLAGS) -o mcast_recv mcast_recv.o $(LIBS)

clean:
	rm -f *.o
	rm -f $(TESTPROGS)

distclean: clean
	rm -f *~
	rm -f core*
	rm -f Makefile 
