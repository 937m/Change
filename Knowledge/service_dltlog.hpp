#ifndef _NAME_SERVICE_LOG_HPP_
#define _NAME_SERVICE_LOG_HPP_

#include <cstdint>
#include <sstream>
#include <cstdarg>
#include <dlt/dlt.h>
#include <dlt/dlt_types.h>

DLT_IMPORT_CONTEXT(NAME_SERVICE_CONTEXT)

#define UNUSED(x) (static_cast<void>(x))

//namespace xx{

inline void printDLTLog(DltLogLevelType level, const char* callerFunction, const int lineNumber, const char* fmt, ...) {
    if (fmt == nullptr) {
        DLT_LOG(NAME_SERVICE_CONTEXT, DLT_LOG_ERROR, DLT_STRING("plaintext log input is null\n"));
        return;
    }

    va_list args;
    va_start(args, fmt);

    std::ostringstream logStream;
    logStream << "[ModuleName][" << callerFunction << "][" << lineNumber << "] ";

    char buffer[1024];
    static_cast<void>(vsnprintf(buffer, sizeof(buffer), fmt, args));
    logStream << buffer;

    DLT_LOG(NAME_SERVICE_CONTEXT, level, DLT_STRING(logStream.str().c_str()));

    va_end(args);
}

#define DLT_NAME_LOG_WARN(fmt, ...) printDLTLog(DLT_LOG_WARN, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)


//} /* namespace service */

#endif /* _NAME_SERVICE_LOGHPP_ */
