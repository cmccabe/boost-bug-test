CC=g++
CFLAGS=-Wall -Wextra
BOOST_INSTALL_DIR=/opt/boost-trunk

boost-bug-test: boost-bug-test.cc
	$(CC) $(CFLAGS) boost-bug-test.cc -lboost_system -lboost_thread -lpthread \
		-L$(BOOST_INSTALL_DIR)/lib -I$(BOOST_INSTALL_DIR)/include \
		-o boost-bug-test

run: boost-bug-test
	LD_LIBRARY_PATH="$(LD_LIBRARY_PATH):$(BOOST_INSTALL_DIR)/lib" ./boost-bug-test

clean:
	rm -f boost-bug-test.o boost-bug-test
