#include <string>
#include <fstream>
#include <typeinfo>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "test_method_base.h"

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



class Test1 : public TestMethodBase
{
public:
    Test1() = delete;
    Test1(Test1&& orig) = delete;
    Test1& operator=(Test1&& rhs) = delete;

    Test1(std::string name, std::string in, std::string expected)
        : TestMethodBase(name), m_in(in), m_expected(expected) {}
    Test1(std::string name, std::string in, std::string expected, PTESTDecorator pDecorator)
        : TestMethodBase(name, pDecorator), m_in(in), m_expected(expected) {}
    Test1(const Test1& orig) : TestMethodBase(orig.name()), m_in(orig.in()), m_expected(orig.expected()) {}
    Test1& operator=(const Test1& rhs) { return *this; }
    virtual ~Test1() {}

    std::string in() const { return m_in; }
    std::string expected() const { return m_expected; }

    bool operator()() const {
        return m_in == m_expected;
    }

private:
    std::string m_in;
    std::string m_expected;
};

void ColTest(ConsoleDisplay::eColours val)
{
    std::cerr << "Test [" /*<< std::setw(12)*/ << ConsoleDisplay::ColourStr(val) << "]" << std::endl;
    std::cerr << "\t - fore [ win : " << std::setw(3) << static_cast<int32_t>(ConsoleDisplay::GetColValue(val, true)) <<
        ", ansi : " << std::setw(3) << static_cast<int32_t>(ConsoleDisplay::GetColValue(val, false)) << "] -> ["; 
    ConsoleDisplay::colText(val, ConsoleDisplay::Black, "**", std::cerr, true, true);
    std::cerr << " , ";
    ConsoleDisplay::colText(val, ConsoleDisplay::Black, "**", std::cerr, true, false);
    std::cerr << "]" << std::endl;

    std::cerr << "\t - back [ win : ";
    std::cerr << std::setw(3) << static_cast<int32_t>(ConsoleDisplay::GetBGColValue(val, true)) << ", ansi : ";
    std::cerr << std::setw(3) << static_cast<int32_t>(ConsoleDisplay::GetBGColValue(val, false)) << "] -> [";
    ConsoleDisplay::colText(ConsoleDisplay::White, val, "**", std::cerr, true, true);
    std::cerr << " , ";
    ConsoleDisplay::colText(ConsoleDisplay::White, val, "**", std::cerr, true, false);
    std::cerr << "]" << std::endl;
}

void lookupTests()
{
    ColTest(ConsoleDisplay::None);
    ColTest(ConsoleDisplay::Black);
    ColTest(ConsoleDisplay::Red);
    ColTest(ConsoleDisplay::Green);
    ColTest(ConsoleDisplay::Yellow);
    ColTest(ConsoleDisplay::Blue);
    ColTest(ConsoleDisplay::Magenta);
    ColTest(ConsoleDisplay::Cyan);
    ColTest(ConsoleDisplay::White);

    std::cerr << std::endl;

    ColTest(ConsoleDisplay::B_Black);
    ColTest(ConsoleDisplay::B_Red);
    ColTest(ConsoleDisplay::B_Green);
    ColTest(ConsoleDisplay::B_Yellow);
    ColTest(ConsoleDisplay::B_Blue);
    ColTest(ConsoleDisplay::B_Magenta);
    ColTest(ConsoleDisplay::B_Cyan);
    ColTest(ConsoleDisplay::B_White);

    std::cerr << std::endl;

    //ColTest(11);  // should ccause commpile errors
    //ColTest(27);

    //std::cerr << std::endl;
}

#define FOO(fname)  Foo foo(fname, __FUNCTION__)

// __FOO_USE_STD_STRING__    // use std:;string instead of a string stream to marshall data
// __FOO_USE_STD_OFSTREAM__  // use std::ofstream instead of a FILE pointer

class Foo
{
public:
    enum eMarker
    {
        endOfLine,
        flushLine
    };

    Foo(std::string fname, std::string name) : m_fname(fname), m_name(name), m_newline(true)
    {
#ifdef __FOO_USE_STD_OFSTREAM__
        //m_file.open(fname, std::ios::app);
        m_file.open(fname);
        if (m_file.good())
        {
            doNewLine();
#ifdef __FOO_USE_STD_STRING__
            m_line.append("Begin function");
#else
            m_line << "Begin function";
#endif
            doEndLine();
        }
#else
#endif
    }

    virtual ~Foo()
    {
#ifdef __FOO_USE_STD_OFSTREAM__
        if (m_file.good())
        {
            doFlush();
            doNewLine();
#ifdef __FOO_USE_STD_STRING__
            m_line.append("End function");
#else
            m_line << "End function";
#endif
            doEndLine();
            m_file.close();
        }
#else
#endif
    }

    friend std::ostream& operator<<(const Foo& foo, std::ostream& os);

    std::string name() const { return m_name; }

#ifdef __FOO_USE_STD_STRING__
    std::string str() const { return m_line; }
#else
    std::string str() const { return m_line.str(); }
#endif
    operator const std::string() const { return this->str(); }

#ifdef __FOO_USE_STD_OFSTREAM__
    std::ofstream& file() { return m_file; }
#else
#endif

    //Foo& clear() { m_line.str(""); m_newline = true; return *this; }
    Foo& clear() { m_line.clear(); m_newline = true; return *this; }

    template<class T>
    void write(T const& val)
    {
        if (typeid(val).hash_code() == typeid(Foo::endOfLine).hash_code())
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
#ifdef __FOO_USE_STD_STRING__
                m_line.append(std::to_string(val));
#else
                m_line << val;
#endif
            }
        }
    }

    template<eMarker T>
    Foo& operator<<(eMarker& marker)
    {
        switch (marker)
        {
        case Foo::endOfLine:
            this->doEndLine();
            break;

        case Foo::flushLine:
            this->doFlush();
            break;

        default:
            int unhandled = 42;
        };
        return *this;
    }

    //Foo& operator<<(std::ostream&(*f)(std::ostream&))
    //{

    //    return *this;
    //}

    template<class T>
    Foo& operator<<(T const& val)
    {
        write(val);

        return *this;
    }

private:
    void persistLine()
    {
#ifdef __FOO_USE_STD_OFSTREAM__
        std::ofstream of(m_fname, ios::app);
        if (of.good())
        {
            of << this->str();
            of.close();
        }
#else
        FILE *f = std::fopen(m_fname.c_str(), "at");
        if (f != nullptr)
        {
            std::fprintf(f, this->str().c_str());
            std::fflush(f);
            std::fclose(f);
            f = nullptr;
        }
#endif
        else
        {
            std::cerr << this->str();
            std::cerr.flush();
        }
    }

    void prefixLine()
    {
        ++ms_counter;
        m_newline = false;
#ifdef __FOO_USE_STD_STRING__
        m_line.clear();
        m_line.append("[").append(m_name).append("][").append(utc_now()).append("][").append(std::to_string(ms_counter)).append("] ");
#else
        m_line.str("");
        m_line << "[" << m_name << "][" << utc_now() << "][" << std::setw(16) << std::setfill('0') << ms_counter << "] ";
#endif
    }

    void doEndLine()
    {
#ifdef __FOO_USE_STD_STRING__
        m_line << m_line << std::endl;
#else
        m_line << std::endl;
        m_line.str("");
#endif
        persistLine();
        clear();
    }

    void doFlush()
    {
#ifdef __FOO_USE_STD_OFSTREAM__
        if (m_file.good())
        {
#ifdef __FOO_USE_STD_STRING__
            m_file << m_line << std::fflush;
            m_line.clear();
#else
            //m_file << m_line.str() << std::flush;
            //m_line.str("");
#endif
            m_newline = true;
        }
#else
#endif
    }

    std::string m_name;
#ifdef __FOO_USE_STD_STRING__
    std::string m_line;
#else
    std::stringstream m_line;
#endif
#ifdef __FOO_USE_STD_OFSTREAM__
    std::ofstream m_file;
#else
    std::string m_fname;
#endif
    bool m_newline;

    static uint32_t ms_counter;
};

uint32_t Foo::ms_counter = 0ul;

std::ostream& operator<<(const Foo& foo, std::ostream& os)
{
    os << foo.str();
    return os;
}


int main(int argc, char ** argv, char **env)
{
    FOO("c:\\temp\\test.foo.log");

    //Foo foo("c:\\temp\\test.foo.log", __FUNCTION__);
    //foo << "Hello" << " " << "World" << Foo::endl << 42 << Foo::endl;

    std::cout << "Press <enter>:";
    std::string val;
    std::getline(std::cin, val, '\n');

    //foo << "Set up the console" << Foo::endl;

    //PConsoleDisplay pConsole = ConsoleDisplay::get();
    ConsoleDisplay& theConsole = ConsoleDisplay::get();

    std::printf("Tests built: " __DATE__ ", " __TIME__ "\n");

    //Test1 t1("t1", "foo", "bar");
    //std::cerr << t1 << std::endl;

    //foo << "Display all colour values" << Foo::endl;

    ConsoleDisplay::allColours();

    //foo << "Test colour string evaluation" << Foo::endl;

    //ConsoleDisplay::eColours fore(ConsoleDisplay::B_White);
    //ConsoleDisplay::eColours back(ConsoleDisplay::Red);
    //std::cout << std::endl << "Test: fore [" << fore << ": " << ConsoleDisplay::ColourStr(fore);
    //std::cout << "], back [" << back << ": " << ConsoleDisplay::ColourStr(back) << "] --> [";

    //foo << "Display colour text" << Foo::endl;

    //ConsoleDisplay::winCol(7, 4, "Hello", std::cout);
    //ConsoleDisplay::colText(fore, back, "Hello", std::cout);

    //ConsoleDisplay::winCol(7, 2, " World", std::cerr);
    //ConsoleDisplay::colText(ConsoleDisplay::Black, ConsoleDisplay::B_Cyan, " World", std::cerr);
    //std::cout << "]" << std::endl << std::endl;

    //foo << "Run lookup tests" << Foo::endl;

    //lookupTests();

    return 0;
}
