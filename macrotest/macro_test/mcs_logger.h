#ifndef __MCS__MACRO_TEST__MCS_LOGGER_H__
#define __MCS__MACRO_TEST__MCS_LOGGER_H__

#pragma once

#include <stdint.h>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <memory>

#ifdef _MSC_VER
#include <windows.h>
uint32_t millis();
#else
#include <sys/time.h>
uint32_t millis();
#endif
std::string utc_now();

class Logger;

#ifndef _WIN32
#define GET_LOGGER(fname,var)  Logger var(__FUNCTION__)
#else
#define GET_LOGGER(fname,var)  Logger var(__func__)
#endif

std::ostream& operator<<(const Logger& Logger, std::ostream& os);

#if 0
class Logger
{
public:
    enum eMarker
    {
        endOfLine,
        flushLine
    };

    Logger(std::string fname, std::string name);

    virtual ~Logger();

    friend std::ostream& operator<<(const Logger& Logger, std::ostream& os);

    inline std::string name() const { return m_name; }
    inline std::string str() const { return m_line.str(); }
    inline operator const std::string() const { return this->str(); }

    Logger& clear();

    template<class T>
    void write(T const& val);

    template<eMarker T>
    Logger& operator<<(eMarker& marker);

    template<class T>
    Logger& operator<<(T const& val);

private:
    void persistLine();

    void prefixLine();

    void doEndLine();

    void doFlush();

    std::string m_name;
    std::string m_fname;
    std::stringstream m_line;

    bool m_newline;

    static uint32_t ms_counter;
};
#else

enum eLogLevels
{
    eLog_Critical = 0,
    eLog_Error    = (1 << 0),
    eLog_Warning  = (1 << 1),
    eLog_Info     = (1 << 2),
    eLog_Debug    = (1 << 3),
    eLog_Trace    = (1 << 4),
    eLog_DebugEx  = (1 << 5)
};

// per method interface to the log system
class Logger
{
public:
    Logger(std::string&& funcName);
    virtual ~Logger();

private:

    std::string m_funcName;
};

class ILogWriter
{
public:
    ILogWriter(std::string writerName) : m_writerName(writerName) {}

    virtual ~ILogWriter() {}

    bool init() { m_isInitialised = doInit(); }
    void finalise() { doFinalise(); m_isInitialised = false; }

    std::string name() const { return m_writerName; }
    
    virtual bool doInit() = 0;
    virtual void doFinalise() = 0;
    virtual void write(std::string funcName, const eLogLevels eLevel, std::string msg) = 0;

private:
    bool m_isInitialised;
    std::string m_writerName;
};

typedef std::map<std::string, std::shared_ptr<ILogWriter>> WriterMap;

// Log system gives a logger to a method
// manages the log writers
class LogSystem
{
public:
    LogSystem() {}
    virtual ~LogSystem() {}

    friend class Logger;

    bool registerWriter(std::shared_ptr<ILogWriter> pWriter)
    {
        if (pWriter == nullptr)
        {
            // TODO
        }
        else
        {
            if (m_writers.count(pWriter->name()))
            {
                m_writers.insert(std::pair<std::string, std::shared_ptr<ILogWriter>>(pWriter->name(), pWriter));
            }
        }
        return false;
    }

private:
    WriterMap m_writers;
};

#endif

#endif // __MCS__MACRO_TEST__MCS_LOGGER_H__ 

