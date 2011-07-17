// sanity - A library to help you retain your sanity.
// Copyright 2011 Sean Farrell

#include "trace.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <utility>

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
    std::vector<std::pair<TraceSeverity, std::ostream*> > targets;
    
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
    void add_trace_target(TraceSeverity severity, std::ostream& target)
    {
        targets.push_back(std::make_pair(severity, &target));
    }
    
//------------------------------------------------------------------------------    
    std::string build_trace_line(TraceSeverity severity, const char* function, const char* message)
    {
        std::stringstream buff;
        buff << severity << ": " << function << ": " << message << std::endl;
        return buff.str();
    }
    
//------------------------------------------------------------------------------
    void do_trace(TraceSeverity severity, const char* function, const char* message)
    {
        std::string line = build_trace_line(severity, function, message);
        
        std::vector<std::pair<TraceSeverity, std::ostream*> >::const_iterator iter;        
        iter = targets.begin();        
        while (iter != targets.end())
        {
            if (iter->first >= severity)
            {
                *(iter->second) << line;
            }
            ++iter;
        }
    }
    
//------------------------------------------------------------------------------
    void do_trace(TraceSeverity severity, const char* function, const std::string& message)
    {
        do_trace(severity, function, message.c_str());    
    }    
}
