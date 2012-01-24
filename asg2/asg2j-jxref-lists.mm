.so Tmac.mm-etc
.if t .Newcentury-fonts
.INITR* \n[.F]
.TITLE CMPS-012B Winter\~2012 Program\~2 \
"Cross References and Linked Lists"
.RCS "$Id: asg2j-jxref-lists.mm,v 1.8 2012-01-20 14:40:28-08 - - $"
.PWD
.EQ
delim $$
.EN
.H 1 "Overview"
In this assignment you will implement a singly-linked linear list of
words to implement a cross referencing utility.
The words will be keys, and each will contain a queue of line numbers.
The queue will also be implemented as a linear linked list.
Your queue operations must run in $ O ( 1 ) $ time,
but your map (dictionary) operations will run in $ O ( n ) $
time instead of the usually-expected $ O ( log sub 2 n ) $ time.
Thus, if your entire program scans $n$ words in a file,
it will run at speed $ O ( n sup 2 ) $ instead of 
$ O ( n log sub 2 n ) $ time.
.H 1 "Program specification"
The program is specified in the form of a Unix
.V= man (1)
page.
.SH=BVL
.MANPAGE=LI "NAME"
jxref \(em cross referencing and word count utility
.MANPAGE=LI "SYNOPSIS"
.V= jxref
.RI \|[ filename \|.\|.\|.]
.MANPAGE=LI "DESCRIPTION"
Each file is read in sequence and words are extracted from the file.
At the end of each file, a table is printed,
sorted in lexicographic order with each word followed by a count of the
number of times it occurs and a list of the numbers of the lines where
it occurs.
Cross reference output is written to
.V= stdout
.=V ( System.out )
and error messages are written to 
.V= stderr 
.=V ( System.err ).
.MANPAGE=LI "OPTIONS"
None.
.MANPAGE=LI "OPERANDS"
Operands consist of the names of files to be read in sequence.
If no filenames are specified,
.V= stdin
is read.
If filenames are specified, each file is read in turn.
If a filename is specified as a single minus sign
.=V ( - )
.V= stdin
is read at that point.
In order to read a file whose name really is a minus sign,
it should be specified on the command line as
.=V `` ./- ''.
.MANPAGE=LI "EXIT STATUS"
.VL \n[Pi]
.LI 0
All input files were read successfully.
.LI 1
An error occurred and a message was printed to
.V= stderr .
.LE
.LE
.H 1 "Implementation sequence"
Again, follow an implementation sequence by developing your code
a little at a time.
The
.V= code/
subdirectory contains starter code.
.ALX a ()
.LI
Study the behavior of the program
.V= pxref.perl ,
which is a reference implementation of your program written in the Perl
programming language.
Delete references to that file from your
.V= Makefile
and do not submit the Perl program.
You need not understand Perl, but note how short the program is.
.LI
A partial main program in Java has been provided for you in
.V= jxref.java ,
which just reads in words from files and prints out those words.
You need to add in the data structures.
In your program you are prohibited from using anything from the
package
.V= java.util
except for those packages explicitly listed in the syllabus.
.LI
Implement your program in phases, not all at once\(::
.ALX i ()
.LI
Study the code provided,
and add code to it to insert each word into the 
.V= listmap ,
ensuring that duplicates are not entered.
Then add code to print the output in the required manner.
Ignore line numbers.
.LI
Add code to create an
.V= intqueue
whenever a new word is found,
and increment the count, but do not record line numbers.
Adjust the printing to print counts as well as words.
.LI
Complete the program by appending line numbers to each queue.
.LE
.LI
The main function iterates over each filename given in the argument
vector and uses 
.V= stdin
when required.
For scanning the file, it creates a pattern which describes a word
and then matches each word in sequence.
It also keeps track of line numbers.
These parts are as follows\(::
.ALX a ()
.LI
.V= \(Dq\(rs\(rsw+([-'.:/]\(rs\(rsw+)*\(Dq
is a pattern which matches any word character
.=V ( [a-zA-Z_0-9] ),
allowing any one of the characters in the set
.V= [-'.:/]
in the middle.
Just use it.
Regular expressions will be explained in detail in CMPS-104A.
.LI
.V= "wordpat.matcher\~(line)"
creates a pattern matcher for the line.
.LI
.V= "match.find()"
checks to see if there is an unscanned word left in the line.
.LI
.V= "match.group()"
returns it if there is.
.LE
.LI
The function
.V= main
is finished and iterates over each of the filenames
given on the command line.
The function
.V= xref_file
has stub code which just prints out the words as they are found.
It also prints out the line numbers.
This function must be changed to conform to the program specifications.
Leave in the debugging code until your program is finished.
Then delete it.
.LI
The function
.V= listmap.insert
currently does nothing.
Put code in this function to insert a new key in ascending
lexicographic order as sorted by
.V= compareTo .
Ignore the class
.V= intqueue
for now.
The insertion proceeds in two phases\(::
.ALX i ()
.LI
Searches down the list using a previous and current pointer,
as was done in class to locate the insertion point.
Quit the loop either at the end of the list or when the insertion
point is found.
.LI
If the word (key) is not already in the list,
allocate a new node and insert it in the correct position.
If it is in the list, do nothing.
.LE
.LI
The 
.V= Iterator
over the 
.V= listmap
is already written for you.
If your insertion code work, the foreach loop at the end of
.V= xref_file
will print out the words in lexicographic order.
If not, put debug statements in 
.V= listmap.insert
to find out why.
.LI
The class
.V= intqueue
is partially written for you.
It has its
.V= Iterator ,
but instead of actually inserting a line number into the queue,
it merely increments a count.
Modify 
.V= listmap.insert
to call 
.V= queue.insert
to increment the word count.
.LI
This will allow you to modify the printing loop so that it prints
a list of words followed by their count.
Verify that your program now works like
.V= pxref.perl ,
except that only words and counts are printed.
.LI
Now work on
.V= intqueue
to finish the
.V= insert
operation.
The implementation is a singly linked list of integers with a pointer
to the front of the list and the rear of the list..
Both operations must run in $ O ( 1 ) $ time.
Every insertion should increment the count and every deletion should
decrement the count.
.LI
Now go back to
.V= xref_file
and cause the words, counts, and line numbers all to be printed,
as does the Perl program.
Use the 
.V= Iterator- style
.V= for -loop.
.LI
If that works, delete the debug code and check your code agains
.V= pxref.perl .
Does your program produce identical output for valid filenames\(??
Almost identical error messages for invalid filenames\(??
Correct use of
.V= stdout
and
.V= stderr \(??
Correct exit status codes\(??
.ALX i ()
.LI
Error messages from
.V= pxref.perl
are printed in correct Unix format, e.g.\(::
.VCODE 0 "pxref.perl: foobar: No such file or directory"
.LI
The Java version prints out the name of the jar file,
as obtained from class
.V= auxlib ,
and also just uses the format returned by
.V= getMessage() ,
e.g.\(::
.VCODE 0 "jxref: foobar (No such file or directory)"
.LE
.LE
.H 1 "Interfaces"
This program uses three interfaces in an attempt to keep the various
classes from needing to know anything about their internal structure\(::
.ALX a ()
.LI
Interface
.V= Iterable<T>
allows collections to be accessed by Java's special iterator syntax.
.VTCODE* 0 \
http://docs.oracle.com/javase/6/docs/api/java/lang/Iterable.html
.ALX i ()
.LI
.V= "Iterator<T> iterator()
\[em] Returns an iterator over a set of elements of type T.
.LE
.LI
Interface
.V= Iterator<E>
allows an iterator to be used to access elements of the collection in a
sequential manner.
.VTCODE* 0 \
http://docs.oracle.com/javase/6/docs/api/java/util/Iterator.html
.ALX i ()
.LI
.V= "boolean haxNext()"
\[em] Returns true if the iteration has more elements.
.LI
.V= "E next()"
\[em] Returns the next element in the iteration.
.LE
.LI
Interface
.V= Map.Entry<K,V>
allows access to elements of a map without knowing the exact
structure of the node containing the elements.
.VTCODE* 0 \
http://docs.oracle.com/javase/6/docs/api/java/util/Map.Entry.html
.ALX i ()
.LI
.V= "K getKey()"
\[em] Returns the key corresponding to this entry.
.LI
.V= "V getValue()"
\[em] Returns the value corresponding to this entry.
.LE
.LE
.P
A
.V= NoSuchElementException
is thrown
for those operations that we don't want to bother to implement.
.H 1 "Makefile"
Graders will compile your code using
.V= make ,
so you need a working
.V= Makefile.
.ALX a ()
.LI
The
.V= Makefile
should have the following targets\(::
.nr TARGETPI \n[Pi]*2
.VL \n[TARGETPI]
.V=LI all:
the first target, which is also the default.
Builds the clases from the sources and puts them all,
including inner classes in the jar.
.V=LI ci:
which checks in all source files into the RCS subdirectory.
.V=LI clean:
which deletes all generated files except for the jar
.V= jxref .
.V=LI spotless:
which depends on clean and also deletes the jar.
.V=LI submit:
which submits all required code.
Do not submit the Perl program.
Delete it from the list of sources before submitting anything.
Also delete the
.V= lis
target.
.LE
.LI
Make sure your
.V= Makefile
can compile all of the Java code and put all classes into a jar.
Submit all Java source files, the
.V= Makefile
and the
.V= README
and verify the submit as you were told to do in Lab\~1.
The graders will be using
.V= unix.ic.ucsc.edu
exclusively,
when doing the grading.
.LE
.H 1 "What to submit"
Submit all necessary Java source files and the
.V= Makefile .
.E= "Submit early."
.E= "Submit often."
.E= "Verify your submit."
If you submit the wrong version or there are missing files,
you will lose many points.
.P
Read the pair programming description.
You may choose a partner or work alone.
If you work with a partner, submit a
.V= README
and a
.V= PARTNER
file as specified in that document.
.FINISH
