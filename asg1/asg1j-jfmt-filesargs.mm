.so Tmac.mm-etc
.if t .Newcentury-fonts
.INITR* \n[.F]
.TITLE CMPS-012B Winter\~2012 Assignment\~1 \
"Format utility, files, args"
.RCS "$Id: asg1j-jfmt-filesargs.mm,v 1.12 2012-01-05 19:33:40-08 - - $"
.PWD
.INITR* \n[.F]
.H 1 "Overview"
In this assignment, you will learn how to access files,
and make use of command line arguments by writing a utility similar to
the program
.V= fmt (1).
Read the man page for 
.V= fmt
by typeing the command\(::
.VTCODE* 1 "man -s 1 fmt"
Whenever you see the name of a command in bold face followed by a
number in parentheses, it refers to a command in a certain section of
the Unix man pages.
In this case, section 1 contains the documentation for the program
.V= fmt .
Your program will be similar but not identical.
Follow the specification given here.
There is also a reference implementation written in Perl.
.H 1 "Program Specification"
We present the program specification in the form of a Unix
.V= man (1)
page.
.SH=BVL
.MANPAGE=LI "NAME"
jfmt \[em] simple text formatter
.MANPAGE=LI "SYNOPSIS"
.V= jfmt
\|[\f[CB]\-\f[P]\f[I]width\f[P]]
\|[\f[I]filename\f[P]\|.\|.\|.]
.MANPAGE=LI "DESCRIPTION"
The format utility reads in text lines from all of its input files and
writes its output to stdout.
Error messages are written to stderr.
Each file is handled separately, and within each file,
all consecutive sequences of lines containing non-whitespace characters
are considered as a single paragraph.
A paragraph is written out with a maximal sequence of words not to
exceed the specified output line width.
It is then followed by one empty line.
.MANPAGE=LI "OPTIONS"
.VL \n[Pi]
.MANOPT=LI "-\f[I]width\f[P]"
.br
The specified width is the maximum number of characters in an output
line.
If a word that is longer than width is found,
it is printed on a line by itself.
The default width is 65 characters.
.LE
.MANPAGE=LI "OPERANDS"
Each operand is a file name, and they are read in sequence.
An option is recognized as such only if it begins with a minus sign
and precedes all operands.
If any operand is specified as a single minus sign
.=V ( - ),
then stdin is read at that point.
.MANPAGE=LI "EXIT STATUS"
.VL \n[Pi]
.LI 0
All files were read successfully,
output was sucessfully generated,
and no errors were detected.
.LI 1
Errors were detected and messages were written to stderr.
.LE
.MANPAGE=LI "SEE ALSO"
.V= fmt (1),
.V= pfmt.perl .
.LE
.H 1 "Implementation Sequence"
Whenever your write a program that is non-trivial, 
you should follow some iplementation sequence that develops a program
a little bit at a time,
keeping a working program and adding to it little by little.
Make backups frequently.
.ALX 1 ()
.LI
Start with the given code\(::
The
.V= code/
subdirectory contains some starter code for yor project.
The
.V= misc/
subdirectory contains some examples you should study, but which
are not directly useable in your code.
.LI
Make sure
.V= checksource
and
.V= cid
are in your path.
The first checks on basic formatting, and the second will check your
code into an 
.V= RCS
archive.
.LI
Play around with
.V= pfmt.perl
to see what your program should do.
If you copy this file into your development directory,
make sure the 
.V= x -bit
is on.
.LI
The program
.V= jfmt.java ,
as given, merely cycles through the files and prints debug code.
Each line is printed as it is read, 
and each word within that line is read.
Note that words are selected from a line with a white space
regular expression passed to
.V= split .
.V= \[Dq]\[rs]\[rs]s+\[Dq]
is a string representing the regular expression 
.V= \[rs]s+ ,
which matches any sequence of white space.
.LI
As you are developing Java code,
you should have your browser pointed at
.VTCODE* 1  http://download.oracle.com/javase/6/docs/api/index.html ,
which is the
.E= "Java\[tm] Platform, Standard Edition 6 API Specification" .
.LI
Your program should have the following import statements at the
beginning\(::
.VTCODE* 1 "import java.io.*;"
.VTCODE* 1 "import java.util.Iterator;"
.VTCODE* 1 "import java.util.LinkedList;"
.VTCODE* 1 "import java.util.List;"
.VTCODE* 1 "import java.util.Scanner;"
.VTCODE* 1 "import static java.lang.System.*;"
.E= "Important note\(::"
In this assignment, you may use anything in
.V= java.util ,
but in general in this course you are
.E= prohibited
from using anything from that package except when explicitly authorized.
See the syllabus for a list of classes in 
.V= java.util
that you may always use.
.LI
Read about interface
.V= java.util.List
and class
.V= java.util.LinkedList .
Then, at the beginning of the function
.V= format ,
add in the following declaration\(::
.VTCODE* 1 "List<String> words = new LinkedList<String> ();"
Delete the line that echos input lines and instead of printing
the words found in each line, 
.V= add
them to the list of words.
Note that you need to take special care not to add an empty leading
word to the list of words.
(What does
.V= split
do when there is a space ahead of the first word\(??)
.LI
Create a function
.V= printparagraph
which is called whenever you see the end of a paragraph.
This function removes and prints each word in the list.
The end of a paragraph occurs at end of file.
It also occurs with an empty line, i.e., a line that
contains only spaces and tabs or nothing at all.
Sequences of empty lines produce the same output as a single empty
line.
.LI
Look at interface
.V= java.util.Iterator .
The function
.V= printparagraph
should create an iterator over the list\(::
.VTCODE* 1 "for (String word: words)"
As you iterate over each word, print it, with a space between
words, but not before the first word, nor after the last word
of the line.
Whenever printing a word would exceed the line length,
print a newline character.
Note that the first word on a line is printed whether or not it
exceeds the line length.
.LI
When you are finished with the list, empty it\(::
.VTCODE* 1 "words.clear ();"
.LI
An alternative method is to create a
.V= StringBuffer
to accumulate words until the line is full.
In this case, don't use string concatenation
.RB ( + ).
Use 
.V= StringBuffer\^.\^append .
This is what the inner loop of the Perl code does.
Study it an duplicate its functionality.
Use
.V= diff (1)
to check the output of your program against that of
.V= pfmt.perl .
.LI
Add code to examine 
.V= args
to see if there is a maximum line length parameter,
and if so, keep it in a variable.
If
.V= args[0]
exists, it is a valid option if
.V= "args[0]\^.\^matches (\[Dq]\-\[rs]\[rs]d+\[Dq])" ,
an invalid option if
.V= "args[0]\^.\^matches (\[Dq]\-\^.\^+\[Dq])" ,
and otherwise not an option at all.
.LI
A string may be converted to an integer by using
.V= Integer.parseInt
(see the Java 1.5 API documentation for
.V= java.lang.Integer ).
You can either use
.V= substring
to ignore the minus sign, or negate the result after conversion.
Note that any word from the command line that
.V= equals\~(\[Dq]\-\[Dq])
is not an option, but an operand.
Instead of bothering to check for formatting using the
.V= matches
function in the previous point,
You could just assume it is valid,
but use a 
.V= try - catch
construct to catch a
.V= NumberFormatException
if not.
.LE
.H 1 "Scripts"
There are scripts
.V= cid ,
.V= testsubmit ,
and
.V= checksource
in my course 
.V= bin
directory.
To make them available for your use without typing in the full
pathname,
add them to your path.
.P
.ds BINDIR /afs/cats.ucsc.edu/courses/cmps012b-wm/bin
If you use
.V= bash ,
add the following line to
.V= \[ti]/.bashrc \(::
.VTCODE* 1 "export PATH=\[Dq]\[Do]PATH:\*[BINDIR]\[Dq]"
To make sure this also happens with a login shell,
type the following in at the command line\(::
.VTCODE* 1 "cd"
.VTCODE* 1 "ln -s .bashrc .bash_profile"
.VTCODE* 1 ". .bashrc"
.P
If you use
.V= csh
or
.V= tcsh ,
add the following to 
.V= \[ti]/.cshrc \(::
.VTCODE* 1 "set path=(\[Do]path \*[BINDIR])"
After you do that, source the file from the command line\(::
.VTCODE* 1 "source \[ti]/.cshrc"
For either shell, you need to do that only once.
Next time you log in,
you will automatically get my directory in your path.
.H 1 "Program Testing"
It is extremely important to test your program and verify that
it works under all possible circumstances.
The subdirectory
.V= \&.score
contains some files\(::
.V= SCORE
is the grader's score sheet, to be used to evaluate your program.
After submitting your code, run
.V= testsubmit
and then
.V= cd
into the directory.
Copy the files
.V= mk.build
and
.V= mk.test
and run them to verify that your program works.
.P
To see exactly what testing should look like,
copy the input files into your baseline directory
(separate from your development directory),
make a symbolic link to make
.V= jfmt
point at
.V= pfmt.perl
and see what output the Perl program produces.
Your output should be identical,
including
.V= stdin ,
.V= stdout ,
and the exit status.
.H 1 "What to Submit"
Submit the files
.V= README ,
.V= Makefile ,
.V= jfmt.java .
If you are doing pair programming, 
be sure to edit your
.V= README ,
as required in the pair programming directory,
and add the
.V= PARTNER
file to your submit list.
.P
.E= "Verify the submit\(!!"
This is explained in
.V= lab1 .
If you don't submit all of the necessary code, you will
lose many points.
Do not submit the jar file or any class files.
Make sure your
.V= Makefile
works.
Do a pre-grade using the information in the
.V= \&.score
subdirectory.
.FINISH
