/** A Reverse Polish Notation Calculator implemented in Java
*/

import java.util.Scanner;
import static java.lang.System.*;

class jrpn {
    final int EMPTY = -1;
    int top = EMPTY;
    double[] stack = new double[16];

    public static void main(String[] args) {
        Scanner scan = new Scanner (in);
        jrpn calc = new jrpn();
        while ( scan.hasNext() ) {
            String str = scan.next();
            calc.push(str);
            calc.show();
        }
    }
    
    // static Boolean isOperator(String str) {
    //     if (str.length() != 0)
    //     return (  str.equals("+")
    //            || str.equals("-")
    //            || str.equals("*")
    //            || str.equals("/") );
    //     // bahahah its almost like we're using haskell
    //     // ... but we're not (frowny face).
    // }

    void push(String str) {
        // try interpreting it as a double
        try {
            this.concat(str);
            return;
        }
        catch (StackOverflowError e) {
            err.println( e.getMessage() );
            err.println("The stack is full, pass an operator to reduce!");
            return;
        }
        catch (NumberFormatException e) {}

        // try interpreting it as an operator
        try {
            this.operate(str);
        }
        catch (OperatorFormatException e) {
            err.println("The input was not recognized.");
        }
    }
    
    void concat(String str) {
        stack[top+1] = Double.parseDouble(str);
        top += 1;
        // out.printf("Got: %s%n", str); // debug
    }

    void operate(String str)
    throws OperatorFormatException {
        if (str.length() != 1) throw new OperatorFormatException();
        char c = str.charAt(0);
        switch (c) {
            case '+': add();  break;
            case '-': sub();  break;
            case '*': mul(); break;
            case '/': div();  break;
            default: throw new OperatorFormatException();
        }
        // out.printf("Got: %s%n", str); // debug
    }

    void add() {
        double a = stack[top];
        top -= 1;
        double b = stack[top];
        stack[top] = a + b;
    }

    void sub() {
        double a = stack[top];
        top -= 1;
        double b = stack[top];
        stack[top] = b - a;
    }

    void mul() {
        double a = stack[top];
        top -= 1;
        double b = stack[top];
        stack[top] = a * b;
    }

    void div() {
        double a = stack[top];
        top -= 1;
        double b = stack[top];
        stack[top] = b / a;
    }

    void show() {
        out.print("Stack: ");
        for (int i=0 ; i <= top ; i++) out.print(stack[i] + " ");
        out.println();
    }

    static class OperatorFormatException extends Exception {
        public OperatorFormatException() 
            { super("An operator must be one of the following: +, -, *, /."); }
    }
}
