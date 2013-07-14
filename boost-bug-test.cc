#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/condition_variable.hpp>
#include <tr1/memory>
#include <stdio.h>

#define NTHREADS 10

boost::mutex *g_mutex;

boost::condition_variable *g_cvar;

typedef std::vector<std::tr1::shared_ptr<boost::thread> > thread_vec_t;

void run_thread() {
  printf("run_thread...\n");
  while (true) {
    boost::mutex::scoped_lock lock(*g_mutex);
    g_cvar->wait(lock);
  }
}

int main() {
  thread_vec_t threads;
  g_mutex = new boost::mutex();
  g_cvar = new boost::condition_variable();
  for (int i = 0; i < NTHREADS; i++) {
    printf("starting thread...\n");
    threads.push_back(std::tr1::shared_ptr<boost::thread>(
        new boost::thread(run_thread)));
  }
  while (true) {
    boost::mutex::scoped_lock lock(*g_mutex);
    g_cvar->notify_one();
  }
  return 0;
}
