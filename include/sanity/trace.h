// sanity - A library to help you retain your sanity.
// Copyright 2011 Sean Farrell

#ifndef _SANITY_TRACE_H_
#define _SANITY_TRACE_H_

#include <iosfwd>
#include <string>

#include "defines.h"

namespace sanity
{
    /**
     * SEVERITY 
     **/
    enum TraceSeverity
    {
        ERROR_TRACE,
        WARNING_TRACE,
        INFO_TRACE,
        DEBUG_TRACE
    };
    
    /**
     * Stream operator for TraceSeverity.
     **/
    _SANITY_EXPORT
    std::ostream& operator << (std::ostream& os, TraceSeverity severity);  
    
    /**
     * Handler function for tracing.
     **/    
    typedef void (*TraceHandler)(TraceSeverity severity, const char* function, const char* message, void* data);
    
    /**
     * Add a trace target. 
     * 
     * @param severity the minimum severity for that target
     * @param target the stream to trace to
     **/
    _SANITY_EXPORT
    void add_trace_target(TraceSeverity severity, std::ostream& target);
    
    /**
     * Add a trace target. 
     * 
     * @param severity the minimum severity for that hadler
     * @param handler the trace handler
     * @param data user data for the handler
     **/
    _SANITY_EXPORT
    void add_trace_handler(TraceSeverity severity, TraceHandler handler, void* data);
    
    /**
     * Trace a message.
     *
     * @param severity the severity of the trace
     * @param function the function the trace comes from
     * @param message the message to trace
     * 
     * @{
     **/
    _SANITY_EXPORT
    void do_trace(TraceSeverity severity, const char* function, const char* message);    
    _SANITY_EXPORT
    void do_trace(TraceSeverity severity, const char* function, const std::string& message);
    /** @} **/
}

#define TRACE_ERROR(MSG) ::sanity::do_trace(::sanity::ERROR_TRACE, _SANITY_FUNCTION_, MSG)
#define TRACE_WARNING(MSG) ::sanity::do_trace(::sanity::WARNING_TRACE, _SANITY_FUNCTION_, MSG)
#define TRACE_INFO(MSG) ::sanity::do_trace(::sanity::INFO_TRACE, _SANITY_FUNCTION_, MSG)
#define TRACE_DEBUG(MSG) ::sanity::do_trace(::sanity::DEBUG_TRACE, _SANITY_FUNCTION_, MSG)

#endif
