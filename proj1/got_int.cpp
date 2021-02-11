/*
 * got_int.cpp
 *
 * Author:  Mark A. Sheldon, Tufts University, Fall 2016
 * Edited by Aubrey Anderson, Tufts University, Fall 2017
 *
 * A function that will tell you whether a string can be interpreted
 * as a integer number, and, if so, give the
 * value.
 *
 * There is a simple main program to illustrate the use of the
 * got_int() function.
 *
 * To use the function, you must include "cstdio" as shown.
 * Because the function uses C++ strings, you must include
 * "string" or something that includes "string", like "iostream".
 *
 * The got_int() function illustrates an interesting technique.  The
 * function needs to return two values, but in C/C++ a function can
 * only return one value.  What to do?  There are two choices:
 *
 *      a) Return a struct with two things in it.  We're not doing
 *         that here.
 *      b) Return one item via the normal return value, and get the
 *         other item to the caller by using call-by-reference (CBR).
 *         In C++, arguments to functions are generally passed by
 *         value, i. e., the argument value is *copied* into the
 *         parameter before the function body is run.
 *         With call-by-reference, the callee and caller actually
 *         share the same variable, which allows the called function
 *         to modify a variable in the caller.
 *
 *         CBR can be done in two ways in C++, but, because we're
 *         practicing with pointers, I'm doing it with pointers here.
 *         Besides, when you program in C, this is what you'll have to
 *         do.
 *
 * It is VERY important that you be able to draw an accurate stack
 * diagram that illustrates how this function works.  You don't have
 * to understand sscanf() beyond what is explained below.  If you have
 * any questions, please come talk to one of us.
 *
 * A more native C++ technique would use stringstreams, which is also
 * interesting.  This was what I wrote first.
 *
 */
#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

/*
 * Return true if the string s can be interpreted as an integer
 * number, placing the associated integer into the location pointed to by
 * resultp.
 *
 * Return false if s cannot be interpreted as an integer leaving the
 * location pointed to by resultp unmodified.
 *
 * Implementation note to students:
 *
 *     sscanf() reads characters from the first C string it's given
 *     trying to match them against the "format specifiers" in the
 *     second C string.  In the case below, "%d" means "decimal,"
 *     which is the format for base 10 integers.  It returns the
 *     number of successful matches, and stores the converted values
 *     in the locations pointed to by the remaining arguments.  In
 *     this case, if the C string from s can be interpreted as
 *     representing an integer, the integer value is placed in the
 *     location pointed to by resultp and sscanf() returns 1, which
 *     causes got_int() to return true.  If sscanf() does not get a
 *     successful match, it will return 0, which will cause got_int()
 *     to return false.
 */
bool got_int(string s, int *resultp)
{
        return sscanf(s.c_str(), "%d", resultp) == 1;
}

/*
 * This main function illustrates a way to use got_int() above.
 * If you compile this file and run the result, you can use the
 * program like this:
 *
 *      bash-3.2$ ./got_int 1 -2 lskdfj -1 0 b
 *      1 is an int with value 1
 *      -2 is an int with value -2
 *      lskdfj is not an int :-(
 *      -1 is an int with value -1
 *      0 is an int with value 0
 *      b is not an int :-(
 *      bash-3.2$
 *
 * Take note of the technique of using command line arguments to test
 * something.  It's very handy, because you can test the function on a
 * variety of inputs without recompiling or having to feed it inputs
 * from the keyboard.
 *
 * This was how I actually tested the function, though there were
 * quite a few tests before the one illustrated above.  The tests
 * above show numbers positive and negative numbers, non-numbers of
 * length 1 and 6, and zero.
 */

int main(int argc, char *argv[])
{
        int value;

        for (int i = 1; i < argc; ++i) {
                cout << argv[i] << " ";

                if (got_int(argv[i], &value))
                        cout << "is an int with value " << value;
                else
                        cout << "is not an int :-(";

                cout << endl;
        }
        return 0;
}
