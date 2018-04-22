#include "mcs_logger.h"


#ifdef _MSC_VER
#include <windows.h>
uint32_t millis()
{
    SYSTEMTIME time;
    GetSystemTime(&time);
    return static_cast<uint32_t>(time.wMilliseconds - (time.wMilliseconds / 1000));
}
#else
#include <sys/time.h>
uint32_t millis()
{
    timeval time;
    gettimeofday(&time, NULL);
    return static_cast<uint32_t>((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
#endif

std::string utc_now()
{
    std::stringstream ss;

    std::time_t t = std::time(nullptr);
#ifdef _MSC_VER
    std::tm t2;
    errno_t err = gmtime_s(&t2, &t);
    if (err == 0)
    {
        ss << std::put_time(&t2, "%Y-%m-%d %H:%M:%S.") << std::setw(3) << std::setfill('0') << millis();
    }
    else
    {
        ss << "0000-00-00 00:00:00." << std::setw(3) << std::setfill('0') << millis();
    }
#else
    ss << std::put_time(std::gmtime(&t), "%Y-%m-%d %H:%M:%S.") << std::setw(3) << std::setfill('0') << millis();
#endif
    return ss.str();
}

#if 0
Logger::Logger(std::string fname, std::string name) : m_fname(fname), m_name(name), m_newline(true)
{
    prefixLine();
    m_line << "Begin function";
    doEndLine();
}

Logger::~Logger()
{
    doFlush();
    prefixLine();
    m_line << "End function";
    doEndLine();
}

Logger& Logger::clear()
{
    m_line.str("");
    m_newline = true;
    return *this;
}

template<class T>
void Logger::write(T const& val)
{
    if (typeid(val).hash_code() == typeid(Logger::endOfLine).hash_code())
    {
        doEndLine();
    }
    else
    {
        if (m_line.good())
        {
            if (m_newline)
            {
                prefixLine();
            }
            m_line << val;
        }
    }
}

template<Logger::eMarker T>
Logger& Logger::operator<<(Logger::eMarker& marker)
{
    switch (marker)
    {
    case Logger::endOfLine:
        this->doEndLine();
        break;
    case Logger::flushLine:
        this->doFlush();
        break;
    default:
        int unhandled = 42;
    };
    return *this;
}

template<class T>
Logger& Logger::operator<<(T const& val)
{
    write(val);
    return *this;
}

void Logger::persistLine()
{
    FILE* f = nullptr;
    errno_t eno = fopen_s(&f, m_fname.c_str(), "at");
    if ((f != nullptr) && (eno != 0))
    {
        std::fprintf(f, this->str().c_str()); std::fflush(f);
        std::fclose(f);
        f = nullptr;
    }
    else
    {
        std::cerr << this->str();
        std::cerr.flush();
    }
}

void Logger::prefixLine()
{
    ++ms_counter;
    m_newline = false; m_line.str("");
    m_line << "[" << m_name << "][" << utc_now() << "][" << std::setw(16) << std::setfill('0') << ms_counter << "] ";
}

void Logger::doEndLine()
{
    m_line << std::endl;
    persistLine();
    clear();
}

void Logger::doFlush()
{
    persistLine();
    m_line.str("");
}

uint32_t Logger::ms_counter = 0ul;

std::ostream& operator<<(const Logger& Logger, std::ostream& os)
{
    os << Logger.str(); return os;
}
#else
Logger::Logger(std::string&& funcName) : m_funcName(funcName)
{
}

Logger::~Logger()
{
}


#endif