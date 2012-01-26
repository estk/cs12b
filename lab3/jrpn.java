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
            if ( str.startsWith("#") ) continue;
            calc.evaluate(str);
        }
    }
    
    void evaluate(String str) {
        // try interpreting it as a double
        try {
            push ( Double.parseDouble(str) );
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
            operate(str);
        }
        catch (OperatorFormatException e) {
            err.println("The input was not recognized.");
        }
    }
    
    void push(double num) {
        stack[top+1] = num;
        top += 1;
    }

    double pop() {
        double res = stack[top];
        top -= 1;
        return res;
    }

    void operate(String str)
    throws OperatorFormatException {
        if (str.length() != 1) throw new OperatorFormatException();
        char c = str.charAt(0);
        switch (c) {
            case '+': add();  break;
            case '-': sub();  break;
            case '*': mul();  break;
            case '/': div();  break;
            case ';': show(); break;
            default: throw new OperatorFormatException();
        }
    }

    void add() {
        double a = pop();
        double b = pop();
        push ( b + a );
    }

    void sub() {
        double a = pop();
        double b = pop();
        push ( b - a );
    }

    void mul() {
        double a = pop();
        double b = pop();
        push ( b * a );
    }

    void div() {
        double a = pop();
        double b = pop();
        push ( b / a );
    }

    void show() {
        for (int i=0 ; i <= top ; i++) out.printf( "%22.15g%n", stack[i] );
    }

    static class OperatorFormatException extends Exception {
        public OperatorFormatException() 
            { super("An operator must be one of the following: +, -, *, /."); }
    }
}
