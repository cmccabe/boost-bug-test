#include <boost/thread.hpp>
#include <boost/thread/condition_variable.hpp>
#include <memory>
#include <stdio.h>

using std::auto_ptr;

boost::mutex *g_mutex;

boost::condition_variable *g_cvar;

void run_thread() {
  printf("run_thread...\n");
  boost::mutex::scoped_lock lock(*g_mutex);
  g_cvar->wait(lock);
  printf("thread exiting.\n");
}

int main() {
  g_mutex = new boost::mutex();
  g_cvar = new boost::condition_variable();
  printf("starting thread...\n");
  auto_ptr<boost::thread> thread(new boost::thread(run_thread));
  boost::mutex::scoped_lock lock(*g_mutex);
  g_cvar->notify_one();
  return 0;
}
