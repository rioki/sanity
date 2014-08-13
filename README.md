
Sanity
======

About
-----

Sanity is a library that helps you retain your sanity while programming. This
is done with two features, tracing and checking. 

Tracing
-------

Tracing helps you keep track if what happens in your application and 
especially what goes wrong. To use the trace feature you simply need to
include <sanity/trace.h> and use the TRACE_ERROR, TRACE_WARNING, TRACE_INFO
and TRACE_DEBUG macros. To specify where the trace goes you need to use the 
add_trace_taget function. As an example:

    #include <iostream>
    #include <fstream>
    #include <sanity/trace.h>
    #include "Reactor.h"

    int main()
    {
        // All traces go to STDERR.
        sanity::add_trace_target(sanity::DEBUG_TRACE, std::cerr);
        
        // ERROR, WARNING and INFO traces go into "myapp.log".
        std::ofstream log_file("myapp.tog");
        sanity::add_trace_target(sanity::DEBUG_TRACE, log_file);
        
        Reactor reactor;
        TRACE_INFO("Powering up the reactor.");
        reactor.power_up();
        TRACE_INFO("The reactor is powered up.");
        
        if (reactor.is_melting())
        {
            TRACE_ERROR("The reactor core is melting!");
        }
    }

Checking
--------

Checking helps you ensure that your code or other peoples code behaves as 
expected. Sanity provides the basic contract checks REQUIRE and ENSURE and the 
state check ASSERT. If the given condition is not meat an exception will be 
raised. These macros are intended to be removed for release builds if desired.
As an example:

    void do_it(int a)
    {
        REQUIRE(a > 3);
        ASSERT(v1 > 0);
        v2 = v1 + a;
        ENSURE(v2 == v1 + a);
        v1 = v2;
        ENSURE(v2 == v1);
    }

For convenience the CHECK_ARGUMENT macro can be used as a shorthand for argument 
checks that throw a invalid argument function. For example:

    void do_it(int a)
    {
        CHECK_ARGUMENT(a > -23);
        // do something with a
    }

is equivalent to:

    void do_it(int a)
    {
        if (!(a > -23))
        {
            throw std::invalid_argument("The argument a is invalid.");
        }        
        // do something with a
    }

License
-------

Copyright (c) 2011 Sean Farrell

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

