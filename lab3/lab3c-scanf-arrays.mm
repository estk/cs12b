.so Tmac.mm-etc
.if t .Newcentury-fonts
.TITLE CMPS-012M Winter\~2012 Lab\~2 "RPN, Stacks, and ANSI C"
.RCS "$Id: lab3c-scanf-arrays.mm,v 1.8 2012-01-24 20:58:22-08 - - $"
.PWD
.INITR* \n[.F]
In this lab, you will wrote a program in both Java and in ANSI C
that will interpret input as Reverse Polish Notation expressions.
.H 1 "Java version"
Write a program in Java called
.V= jrpn.java
that will do the following\(::
.ALX a ()
.LI
Create a stack represented as an array\(::
.VTCODE* 1 "final int EMPTY = -1;"
.VTCODE* 1 "int top = EMPTY;"
.VTCODE* 1 "double stack = new double[16];"
Of course, you will never use the number 16 anywhere else in the
program,
instead using
.V= stack.length .
.LI
Loop over the standard input reading words one at a time using
.V= hasNext()
and
.V= next().
Stop at end of file.
.LI
If this can be converted into a
.V= double 
by means of
.V= Double.parseDouble ,
push the number onto the stack.
If this causes tack overflow,
print an error message and discard the number.
.LI
Otherwise, the word is a single character operator.
Print an error message and discard it if it is not a single character.
If it is,
extract the first charcter from the string using
.V= charAt(0).
.LI
Use a 
.V= switch
statement to perform one of the following operations\(::
.ALX i ()
.LI
If it is a
.V= '+' ,
.V= '-' ,
.V= '*' ,
or 
.V= '/' ,
pop two numbers off the stack,
the right operand first, and the left operand next,
and push the value of the result back on the stack.
Print an error messwage and do nothing if there is tack underflow.
.LI
If the operator is a semi-colon
.=V ( ';' ),
print the stack elements, one per line, starting from bottom to top
(upside down),
using the format 
.V= \[Dq]%22.15g\[Dq] .
.LI
Otherwise print an error message.
.LE
.LI
Note that you do not need to do any checking concerning numbers
outside the range of IEEE-754 floating point arithmetic,
nor should you check for division by zero.
When your program is working,
try it and see.
.LE
.H 1 "C version"
Now translate your program into a C program called
.V= crpn.c .
Your program should follow roughly the same sequence of steps.
Some notes\(::
.ALX a ()
.LI
Study the example programs in this directory.
.LI
You can create the stack variables using the declarations
.VTCODE* 1 "#define STACK_SIZE 16"
.VTCODE* 1 "#define EMPTY (-1)"
.VTCODE* 1 "double stack[STACK_SIZE];
.VTCODE* 1 "int top = EMPTY;"
.LI
Study the program
.V= scanf.c
in this directory.
It reads words from
.V= stdin ,
prints the words and their lengths,
and then decides if the input contains a number.
.LI
Use
.V= strlen(3)
to determine the length of the string that was read,
and you can use the following statement to extract its first
character\(::
.VTCODE* 1 "char operator = buffer[0];"
.LE
.H 1 "What to submit"
Submit
.V= jrpn.java
and
.V= crpn.c ,
and the required pair programming files, if appropriate.
.FINISH
