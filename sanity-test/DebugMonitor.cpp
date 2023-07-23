// sanity
// Copyright 2011-2023 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar. See
// http://www.wtfpl.net/ for more details.

#include "pch.h"

#include "DebugMonitor.h"

#include <tlhelp32.h>

namespace test
{
#ifdef _WIN32
    [[nodiscard]]
    DWORD GetParentProcessId(DWORD pid) noexcept
    {
        auto ppid = DWORD{0};

        auto h = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        auto pe = PROCESSENTRY32{ 0 };
        pe.dwSize = sizeof(PROCESSENTRY32);

        if (Process32First(h, &pe))
        {
            do
            {
                if (pe.th32ProcessID == pid)
                {
                    ppid = pe.th32ParentProcessID;
                }
            }
            while (Process32Next(h, &pe));
        }

        CloseHandle(h);

        return ppid;
    }
#endif

    DebugMonitor::DebugMonitor()
    {
#ifdef _WIN32
        auto DBWIN_BUFFER_READY = L"DBWIN_BUFFER_READY";
        buffer_ready_event = OpenEventW(EVENT_ALL_ACCESS, FALSE, DBWIN_BUFFER_READY);
        if (buffer_ready_event == NULL)
        {
            buffer_ready_event = CreateEventW(NULL, FALSE, TRUE, DBWIN_BUFFER_READY);

            if (buffer_ready_event == NULL)
            {
                throw std::runtime_error("Failed to create buffer ready event.");
            }
        }

        auto DBWIN_DATA_READY = L"DBWIN_DATA_READY";
        data_ready_event = OpenEventW(EVENT_ALL_ACCESS, FALSE, DBWIN_DATA_READY);
        if (data_ready_event == NULL)
        {
            data_ready_event = CreateEventW(NULL, FALSE, FALSE, DBWIN_DATA_READY);

            if (data_ready_event == NULL)
            {
                throw std::runtime_error("Failed to create data ready event.");
            }
        }

        auto DBWIN_BUFFER = L"DBWIN_BUFFER";
        mapped_file = OpenFileMappingW(FILE_MAP_READ, FALSE, DBWIN_BUFFER);
        if (mapped_file == NULL)
        {
            mapped_file = CreateFileMappingW(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(struct dbwin_buffer), DBWIN_BUFFER);
            if (mapped_file == NULL)
            {
                throw std::runtime_error("Failed to open mapped DBWIN buffer.");
            }
        }

        buffer = reinterpret_cast<dbwin_buffer *>(MapViewOfFile(mapped_file, SECTION_MAP_READ, 0, 0, 0));
        if (buffer == NULL)
        {
            throw std::runtime_error("Faile to map DBWIN buffer.");
        }

        thread = std::jthread([this] (std::stop_token stoken)
        {
            while (!stoken.stop_requested())
            {
                auto ret = WaitForSingleObject(data_ready_event, 100);

                if (ret == WAIT_OBJECT_0)
                {
                    if (buffer->dwProcessId == GetCurrentProcessId() ||
                        GetParentProcessId(buffer->dwProcessId) == GetCurrentProcessId())
                    {
                        auto lk = std::scoped_lock{mutex};
                        output << buffer->data;
                    }

                    // signal buffer ready
                    SetEvent(buffer_ready_event);
                }
            }
        });
#endif
    }

    DebugMonitor::~DebugMonitor()
    {
#ifdef _WIN32
        thread.request_stop();
        thread.join();
        CloseHandle(buffer_ready_event);
        CloseHandle(data_ready_event);
        UnmapViewOfFile(buffer);
        CloseHandle(mapped_file);
#endif
    }

    std::string DebugMonitor::get_output() const noexcept
    {
        auto lk = std::scoped_lock{mutex};
        return output.str();
    }
}
