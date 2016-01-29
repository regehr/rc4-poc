#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "check.h"
#include <openssl/rc4.h>

#define data_len 100

struct stuff {
  unsigned char data[data_len];
  int important;
} * src, *dst;

volatile int stop = 0;

void *thread1(void *arg) {
  int x = 0;
  while (!stop) {
    dst->important = ++x;
    check(&dst->important, x);
  }
  return 0;
}

void *thread2(void *arg) {
  RC4_KEY key;
  const char *key_data = "Hello there.";
  RC4_set_key(&key, strlen(key_data), (const unsigned char *)key_data);
  while (!stop) {
    RC4(&key, data_len, src->data, dst->data);
  }
  return 0;
}

int main(void) {
  src = calloc(1, sizeof(struct stuff));
  assert(src);
  dst = calloc(1, sizeof(struct stuff));
  assert(dst);
  pthread_t t1, t2;
  int ret;
  ret = pthread_create(&t1, 0, thread1, 0);
  assert(ret == 0);
  ret = pthread_create(&t2, 0, thread2, 0);
  assert(ret == 0);
  sleep(10);
  stop = 1;
  pthread_join(t1, 0);
  pthread_join(t2, 0);
  printf("Normal termination.\n");
  return 0;
}
