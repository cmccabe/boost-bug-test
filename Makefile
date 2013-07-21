CC=clang++
CFLAGS=-fsanitize=thread -g -O0 -fPIE -pie -Wall -Wextra #-std=c++0x
#BOOST_INSTALL_DIR=/opt/boost_1_54_0/
BOOST_INSTALL_DIR=/usr

boost-bug-test: boost-bug-test.cc
	$(CC) $(CFLAGS) boost-bug-test.cc -lboost_system -lboost_thread -lpthread \
		-L$(BOOST_INSTALL_DIR)/lib64 -L$(BOOST_INSTALL_DIR)/lib \
		-I$(BOOST_INSTALL_DIR)/include -o boost-bug-test

run: boost-bug-test
	LD_LIBRARY_PATH="$(LD_LIBRARY_PATH):$(BOOST_INSTALL_DIR)/lib" ./boost-bug-test

clean:
	rm -f boost-bug-test.o boost-bug-test
