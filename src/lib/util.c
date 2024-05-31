#include "util.h"

void int_to_string(char *buf, int n) {
  int index = 0;

  while (n > 0) {
    int digit = n % 10;

    buf[index] = '0' + digit;
    index++;

    n /= 10;
  }

  buf[index] = '\0';
}
