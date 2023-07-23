// sanity
// Copyright 2011-2023 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar. See
// http://www.wtfpl.net/ for more details.

#include "pch.h"

#include <sanity/sanity.h>
#include "DebugMonitor.h"

using namespace std::chrono_literals;

#ifndef __linux__
TEST(trace, trace)
{
    auto debug_monitor = test::DebugMonitor{};

    sanity::trace("Ups! Did I do that?");
    sanity::trace("Ok... So, what now?");

    sleep_for(50ms);
    const auto ref = "trace_test.cpp(21): TestBody: Ups! Did I do that?\n"
                     "trace_test.cpp(22): TestBody: Ok... So, what now?\n";
    EXPECT_EQ(ref, debug_monitor.get_output());
}
#endif
