#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// recursive factorial function
int factorial(int n) {
  if (n == 0) {
    return 1;
  } else {
    return n * factorial(n - 1);
  }
}

int main() {
  char input[100];
  int result;
  for (;;) {
    scanf("%s", input);

    if (strcmp(input, "#") == 0) {
      break;
    } else if (atoi(input) > 10 || atoi(input) < 1) {
      printf("Error!\n");
      continue;
    }

    result = factorial(atoi(input));
    printf("%d\n", result);
  }
}
