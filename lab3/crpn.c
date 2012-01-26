
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 16
#define EMPTY (-1)
double stack[STACK_SIZE];
int top = EMPTY;

void
push(double num) {
    stack[top+1] = num;
    top += 1;
}

int
pop() {
    double res = stack[top];
    top -= 1;
    return res;
}

void
add() {
    double a = pop();
    double b = pop();
    push ( b + a );
}

void
sub() {
    double a = pop();
    double b = pop();
    push ( b - a );
}

void
mul() {
    double a = pop();
    double b = pop();
    push ( b * a );
}

void
divi() {
    double a = pop();
    double b = pop();
    push ( b / a );
}

int
show() {
    int i;
    for (i=0 ; i <= top ; i++)
        printf( "%22.15g\n", stack[i] );
}

void
operate(size_t len, char buf[]) {
    if (len != 1) return;
    switch (buf[0]) {
        case '+': add();  break;
        case '-': sub();  break;
        case '*': mul();  break;
        case '/': divi();  break;
        case ';': show(); break;
    }
}

int
main(int argc, char const *argv[])
{
    assert (argc == 1);
    while(1) {
      char buffer[1024];

      // Read in a word and stop at EOF.
      int scanct = scanf ("%1023s", buffer);
      if (scanct == EOF) {
         break;
      }
      assert (scanct == 1);
      size_t length = strlen (buffer);

      // dispatch if string is a number
      char *endptr;
      double number = strtod (buffer, &endptr);
      if (*endptr == '\0') {
          push (number);
      }else {
          operate (length, buffer);
      }
    }
    return 0;
}


