// sanity - A library to help you retain your sanity.
// Copyright 2011 Sean Farrell

#include "trace.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <tuple>

#include "check.h"

namespace sanity
{
    // REVIEW: Currently we do not lock access to targets. This is done
    // for performance reasons; but I see ways where this could break
    // in a multi threaded environment.
    //
    // The basic idea is that add_trace_target is called before any
    // traces are done, at the beginning of main and after that only trace is 
    // called. The worst that can happen then is messages getting mixed up.
    ///std::vector<std::pair<TraceSeverity, std::ostream*> > targets;
    
    std::vector<std::tuple<TraceSeverity, TraceHandler, void*>> handlers;
    
//------------------------------------------------------------------------------
    std::ostream& operator << (std::ostream& os, TraceSeverity severity)
    {
        switch (severity)
        {
            case ERROR_TRACE:
                os << "ERROR";
                break;
            case WARNING_TRACE:
                os << "WARNING";
                break;
            case INFO_TRACE:
                os << "INFO";
                break;
            case DEBUG_TRACE:
                os << "DEBUG";
                break;
            default:
                FAIL("Unknown TraceSeverity.");
                break;
        }
        return os;
    }
    
//------------------------------------------------------------------------------
    void stream_handler(TraceSeverity severity, const char* function, const char* message, void* data)
    {
        std::ostream* os = reinterpret_cast<std::ostream*>(data);
        (*os) << severity << ": " << function << ": " << message << std::endl;
    }
    
//------------------------------------------------------------------------------
    void add_trace_target(TraceSeverity severity, std::ostream& target)
    {
        add_trace_handler(severity, stream_handler, &target);
    }

//------------------------------------------------------------------------------        
    void add_trace_handler(TraceSeverity severity, TraceHandler handler, void* data)
    {
        handlers.push_back(std::make_tuple(severity, handler, data));
    }
    
//------------------------------------------------------------------------------
    void do_trace(TraceSeverity severity, const char* function, const char* message)
    {
        for (auto h: handlers)
        {
            if (std::get<0>(h) >= severity)
            {
                TraceHandler handler = std::get<1>(h);
                void* data = std::get<2>(h);
                handler(severity, function, message, data);
            }
        }
    }
    
//------------------------------------------------------------------------------
    void do_trace(TraceSeverity severity, const char* function, const std::string& message)
    {
        do_trace(severity, function, message.c_str());    
    }    
}
