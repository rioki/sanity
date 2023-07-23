// sanity
// Copyright 2011-2023 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar. See
// http://www.wtfpl.net/ for more details.

#include "pch.h"

#include "sanity.h"

namespace sanity
{
    #ifndef MAX_PATH
    constexpr auto MAX_PATH = 256u;
    #endif

    std::string basename(const std::string& file) noexcept;

    #ifdef _WIN32
    // This code is mostly portable but is not needed as long as crash dumps are
    // not implemented. So don't bother making it perfectly portable.
    std::string get_env_variable(const std::string_view name) noexcept
    {
        #ifdef _WIN32
        auto buffer = std::array<char, MAX_PATH>{};
        auto len    = size_t{0};

        const auto err = getenv_s(&len, buffer.data(), buffer.size(), name.data());
        if (err == 0) // was found
        {
            return std::string(buffer.data(), len);
        }
        #else
        auto var = std::getenv(name.data());
        if (var != nullptr)
        {
            return std::string(var);
        }
        #endif

        return {};
    }

    std::filesystem::path get_temp_folder() noexcept
    {
        #ifdef _WIN32
        std::array<wchar_t, MAX_PATH> buff;
        const auto r = GetTempPathW(static_cast<DWORD>(buff.size()), buff.data());
        if (r != 0)
        {
            return buff.data();
        }
        #endif

        return get_env_variable("TEMP");
    }

    std::string get_module_filename()
    {
        #ifdef _WIN32
        auto handle = GetModuleHandleA(NULL);
        if (handle == NULL)
        {
            return "";
        }

        auto buff = std::array<char, MAX_PATH>{};
        auto r = GetModuleFileNameA(handle, buff.data(), buff.size());
        if (r == 0)
        {
            return "";
        }

        return std::string(buff.data(), r);
        #else
        return "sanity";
        #endif
    }

    std::filesystem::path create_crash_dump_name() noexcept
    {
        #if __cpp_lib_chrono >= 201907L
        const auto time     = std::chrono::current_zone()->to_local(std::chrono::system_clock::now());
        #else
        const auto time     = std::chrono::system_clock::now();
        #endif
        const auto exe_name = basename(get_module_filename());
        auto filename = std::format("{}.{:%Y-%m-%d_%H-%M-%S}.dmp", exe_name, time);
        return get_temp_folder() / filename;
    }
    #endif

    #ifdef _WIN32
    MINIDUMP_EXCEPTION_INFORMATION GetExceptionInfo(EXCEPTION_POINTERS* exceptionPointers) noexcept
    {
        auto exceptionInfo = MINIDUMP_EXCEPTION_INFORMATION{};
        exceptionInfo.ThreadId          = GetCurrentThreadId();
        exceptionInfo.ExceptionPointers = exceptionPointers;
        exceptionInfo.ClientPointers    = TRUE;
        return exceptionInfo;
    }

    std::string GetErrorMessage(int32_t errorid) noexcept
    {
        auto buffer = std::array<char, 1024>{};
        auto landId = MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT);
        auto flags = FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS;
        auto stringSize = FormatMessageA(flags, NULL, errorid, landId, buffer.data(), static_cast<DWORD>(buffer.size()), NULL);
        return std::string(buffer.data(), stringSize);
    }

    std::string GetLastErrorString() noexcept
    {
        auto error = ::GetLastError();
        return GetErrorMessage(error);
    }

    void write_crash_dump_win32(const std::filesystem::path& filename, EXCEPTION_POINTERS* exceptionPointers = nullptr) noexcept
    {
        const auto handle = CreateFileW(filename.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (handle == INVALID_HANDLE_VALUE)
        {
            trace(std::format("Failed to open {} for writing: {}", filename.string(), GetLastErrorString()));
            return;
        }

        const auto process   = GetCurrentProcess();
        const auto processId = GetCurrentProcessId();


        auto result = FALSE;
        if (exceptionPointers != nullptr)
        {
            auto exceptionInfo   = GetExceptionInfo(exceptionPointers);
            result = MiniDumpWriteDump(process, processId, handle, MiniDumpNormal, &exceptionInfo, 0, 0);
        }
        else
        {
            result = MiniDumpWriteDump(process, processId, handle, MiniDumpNormal, nullptr, 0, 0);
        }

        if (result == FALSE)
        {
            trace(std::format("Failed to write mini dump to {}", filename.string()));
        }

        CloseHandle(handle);
    }
    #endif

    void write_crash_dump() noexcept
    {
        #ifdef _WIN32
        write_crash_dump_win32(create_crash_dump_name());
        #else
        trace("write_crash_dump not implemented for this platform.");
        #endif
    }
}


