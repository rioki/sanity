// sanity
// Copyright 2021-2023 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar. See
// http://www.wtfpl.net/ for more details.

#pragma once

#include <string_view>
#include <source_location>

#ifdef _WIN32
#define SANITY_EXPORT __declspec(dllexport)
#else
#define SANITY_EXPORT
#endif

namespace sanity
{
    //! Output Diagnostic Message
    //!
    //! @param message the message to trace
    //! @param location the source location
    SANITY_EXPORT
    void trace(const std::string_view msg, const std::source_location location = std::source_location::current()) noexcept;

    //! Notify a condition that is unrecoverable.
    //!
    //! The fail function should be used in situations where the program can not continue. For example a default branch
    //! in a switch that has all possible cases.
    //!
    //! The fail function will pull a stack dump and exit the process via std::terminate. If the fail function
    //! detects a debugger it will try to break into the debugger first.
    //!
    //! @param message the message to trace
    //! @param location the source location
    [[ noreturn ]] SANITY_EXPORT
    void fail(const std::string_view msg = "Unexpected failure.", const std::source_location location = std::source_location::current()) noexcept;

    //! Check if a given condition is true.
    //!
    //! The check function is used like assert, to ensure certain things are the way they are. If the given condition is false,
    //! fail will be called.
    //!
    //! @param condition the condition to check.
    //! @param message the message to trace
    //! @param location the source location
    SANITY_EXPORT
    void check(bool condition, const std::string_view msg = "Check failed.", const std::source_location location = std::source_location::current()) noexcept;
}
