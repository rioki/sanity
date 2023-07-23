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

TEST(fail, fail_dies)
{
    EXPECT_DEATH(sanity::fail(), "");
}

#ifdef _WIN32
TEST(fail, traces)
{
    auto debug_monitor = test::DebugMonitor{};

    EXPECT_DEATH(sanity::fail("Oh No!"), "");

    sleep_for(10ms);
    const auto ref = "check_test.cpp(27): TestBody: Oh No!\n";
    EXPECT_EQ(ref, debug_monitor.get_output());
}

TEST(fail, traces_default)
{
    auto debug_monitor = test::DebugMonitor{};

    EXPECT_DEATH(sanity::fail(), "");

    sleep_for(10ms);
    const auto ref = "check_test.cpp(38): TestBody: Unexpected failure.\n";
    EXPECT_EQ(ref, debug_monitor.get_output());
}
#endif

TEST(check, true_passes)
{
    sanity::check(true);
}

TEST(check, false_dies)
{
    EXPECT_DEATH(sanity::check(false), "");
}

TEST(check, true_no_trace)
{
    auto debug_monitor = test::DebugMonitor{};

    sanity::check(true, "Something Aweful!");

    sleep_for(10ms);
    EXPECT_EQ("", debug_monitor.get_output());
}

#ifdef _WIN32
TEST(check, traces)
{
    auto debug_monitor = test::DebugMonitor{};

    EXPECT_DEATH(sanity::check(false, "Something Aweful!"), "");

    sleep_for(10ms);
    const auto ref = "check_test.cpp(71): TestBody: Something Aweful!\n";
    EXPECT_EQ(ref, debug_monitor.get_output());
}


TEST(check, traces_default)
{
    auto debug_monitor = test::DebugMonitor{};

    EXPECT_DEATH(sanity::check(false), "");

    sleep_for(10ms);
    const auto ref = "check_test.cpp(83): TestBody: Check failed.\n";
    EXPECT_EQ(ref, debug_monitor.get_output());
}
 #endif