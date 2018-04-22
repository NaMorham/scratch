#include <string>
#include <fstream>
#include <typeinfo>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "test_method_base.h"

#if 0
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
#endif // utc_now

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
    ConsoleDisplay::colText(ConsoleDisplay::eYellow, "Test [", std::cerr, true);
    std::cerr /*<< std::setw(12)*/ << ConsoleDisplay::ColourStr(val);
    ConsoleDisplay::colText(ConsoleDisplay::eYellow, "]", std::cerr, true);
    std::cerr << std::endl;

    ConsoleDisplay::colText(ConsoleDisplay::eYellow, "\t - fore [", std::cerr);
    std::cerr << " win : " << std::setw(3) << static_cast<int32_t>(ConsoleDisplay::GetColValue(val, true)) <<
        ", ansi : " << std::setw(3) << static_cast<int32_t>(ConsoleDisplay::GetColValue(val, false)) << "] -> ["; 
    ConsoleDisplay::colText(val, ConsoleDisplay::eBlack, "**", std::cerr, true, true);
    std::cerr << " , ";
    ConsoleDisplay::colText(val, ConsoleDisplay::eBlack, "**", std::cerr, true, false);
    std::cerr << "]" << std::endl;

    std::cerr << ConsoleDisplay::Yellow("\t - back [") << " win : ";
    std::cerr << std::setw(3) << static_cast<int32_t>(ConsoleDisplay::GetBGColValue(val, true)) << ", ansi : ";
    std::cerr << std::setw(3) << static_cast<int32_t>(ConsoleDisplay::GetBGColValue(val, false)) << "] -> [";
    ConsoleDisplay::colText(ConsoleDisplay::eWhite, val, "**", std::cerr, true, true);
    std::cerr << " , ";
    ConsoleDisplay::colText(ConsoleDisplay::eWhite, val, "**", std::cerr, true, false);
    std::cerr << "]" << std::endl;
}

void lookupTests()
{
    ColTest(ConsoleDisplay::eNone);
    ColTest(ConsoleDisplay::eBlack);
    ColTest(ConsoleDisplay::eRed);
    ColTest(ConsoleDisplay::eGreen);
    ColTest(ConsoleDisplay::eYellow);
    ColTest(ConsoleDisplay::eBlue);
    ColTest(ConsoleDisplay::eMagenta);
    ColTest(ConsoleDisplay::eCyan);
    ColTest(ConsoleDisplay::eWhite);

    std::cerr << std::endl;

    ColTest(ConsoleDisplay::eB_Black);
    ColTest(ConsoleDisplay::eB_Red);
    ColTest(ConsoleDisplay::eB_Green);
    ColTest(ConsoleDisplay::eB_Yellow);
    ColTest(ConsoleDisplay::eB_Blue);
    ColTest(ConsoleDisplay::eB_Magenta);
    ColTest(ConsoleDisplay::eB_Cyan);
    ColTest(ConsoleDisplay::eB_White);

    std::cerr << std::endl;

    //ColTest(11);  // should ccause commpile errors
    //ColTest(27);

    //std::cerr << std::endl;
}

#if 0
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
#if _MSC_VER < 1900
        FILE* f = nullptr;
        errno_t eno = fopen_s(&f, m_fname.c_str(), "at");
        if ((f != nullptr) && (eno != ERROR_SUCCESS))
#else
        FILE *f = std::fopen(m_fname.c_str(), "at");
        if (f != nullptr)
#endif
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
#else
//#define FOO(s)  std::cerr << s << std::endl
//class Foo
//{
//public:
//    enum eMarker
//    {
//        endOfLine = 42
//    };
//};
//#define foo std::cerr << std::endl; std::cerr
#endif // diable FOO class

#if _MSC_VER >= 1900
template<typename ...Args>
std::string concat(Args ...args) 
{
    return (std::tostring(args) + ... + "");
}
#else
std::string concat()
{
    return "";
}

template<typename T1, typename... T>
std::string concat(T1 s, T... ts)
{
    std::stringstream ss;
    ss << s << concat(ts...);
    return ss.str();
}
#endif

#define CONCAT_TEST(a, b, c) concat_test(a, #c, c, b)

class PassFail
{
public:
    PassFail(bool val) : m_val(val) {}
    virtual ~PassFail() {}

    friend std::ostream& operator<<(std::ostream& os, const PassFail& pf);

    bool v() const { return m_val; }

    bool operator()() const { return m_val; }

private:
    bool m_val;
};

std::ostream& operator<<(std::ostream& os, const PassFail& pf)
{
    ConsoleDisplay::colText((pf.v() ? ConsoleDisplay::eGreen : ConsoleDisplay::eRed), ConsoleDisplay::eNone, (pf.v() ? "Passed" : "Failed"), os, true);
    return os;
}

bool concat_test(std::string exp, std::string testCall, std::string testRes, std::string testName)
{
    bool result = (exp.compare(testRes) == 0);

    ConsoleDisplay::colText(ConsoleDisplay::eYellow, ConsoleDisplay::eNone, "Test", std::cerr, true);
    std::cerr << " [" << testName << "] -> ";
    ConsoleDisplay::colText(ConsoleDisplay::eCyan, ConsoleDisplay::eNone, testCall, std::cerr, true);
    std::cerr << " --> " << std::endl << "       got [" << testRes << "], expected [" << exp << "] --> " << PassFail(result) << std::endl;
    return result;
}

const std::string DEFAULT_PROMPT("Press <enter>:");
std::string getString(const char* prompt = DEFAULT_PROMPT.c_str(), std::ostream& os = std::cout)
{
    std::string _prompt(prompt == nullptr ? DEFAULT_PROMPT : prompt);
    os << _prompt;
    std::string val;
    std::getline(std::cin, val, '\n');

    return val;
}

int main(int argc, char ** argv, char **env)
{
    //GET_LOGGER("c:\\temp\\test.logger.log", foo);
    //FOO("c:\\temp\\test.foo.log");

    //Foo foo("c:\\temp\\test.foo.log", __FUNCTION__);
    //foo << "Hello" << " " << "World" << Foo::endOfLine << 42 << Foo::endOfLine;

    /*
    std::cout << "Press <enter>:";
    std::string val;
    std::getline(std::cin, val, '\n');
    /*/
    getString();
    //*/

    //foo << "Set up the console" << Foo::endOfLine;

    //PConsoleDisplay pConsole = ConsoleDisplay::get();
    ConsoleDisplay& theConsole = ConsoleDisplay::get();

    std::cerr << "Tests built: " << __DATE__ << ", " << __TIME__ << std::endl << std::endl;

    CONCAT_TEST("", "simple test 2", concat());
    CONCAT_TEST("Hello World", "simple test 1", concat("Hello", " ", "World"));

    //Test1 t1("t1", "foo", "bar");
    //std::cerr << t1 << std::endl;

    //foo << "Display all colour values" << Foo::endOfLine;

    ConsoleDisplay::allColours(std::cerr);

    //foo << "Test colour string evaluation" << Foo::endOfLine;

    ConsoleDisplay::eColours fore(ConsoleDisplay::eB_White);
    ConsoleDisplay::eColours back(ConsoleDisplay::eRed);
    //foo << "Display colour text" << Foo::endOfLine;

    std::cerr << ConsoleDisplay::Green("Please be green") << std::endl;

    std::cout << std::endl << ConsoleDisplay::Yellow("Test:") << " fore " << ConsoleDisplay::Yellow("[") << std::setw(2) << fore
        << ConsoleDisplay::Yellow(": ") << std::setw(12) << ConsoleDisplay::ColourStr(fore) << ConsoleDisplay::Yellow("]")
        << ", back " << ConsoleDisplay::Yellow("[") << std::setw(2) << back << ConsoleDisplay::Yellow(": ") << std::setw(12)
        << ConsoleDisplay::ColourStr(back) << ConsoleDisplay::Yellow("]") << " -->" << std::endl << "           [";
    ConsoleDisplay::colText(fore, back, "Hello", std::cout);
    ConsoleDisplay::colText(ConsoleDisplay::eBlack, ConsoleDisplay::eB_Cyan, " World", std::cout);
    std::cout << "]" << std::endl;

    {
        ConsoleDisplay::eColours b_yel(ConsoleDisplay::eB_Yellow);
        ConsoleDisplay::eColours grn(ConsoleDisplay::eGreen);
        ConsoleDisplay::eColours blk(ConsoleDisplay::eBlack);
        ConsoleDisplay::eColours none(ConsoleDisplay::eNone);
        ConsoleDisplay::eColours yel(ConsoleDisplay::eYellow);
        ConsoleDisplay::eColours b_red(ConsoleDisplay::eB_Red);

        std::cout << std::endl << ConsoleDisplay::Yellow("Test:") << " fore " << ConsoleDisplay::Yellow("[") << std::setw(2)
            << b_yel << ConsoleDisplay::Yellow(": ") << std::setw(12) << ConsoleDisplay::ColourStr(b_yel)
            << ConsoleDisplay::Yellow("]") << ", back " << ConsoleDisplay::Yellow("[") << std::setw(2) << grn
            << ConsoleDisplay::Yellow(": ") << std::setw(12)<< ConsoleDisplay::ColourStr(grn) << ConsoleDisplay::Yellow("]")
            << " -->" << std::endl;
        std::cout << ConsoleDisplay::Yellow("    :") << " fore " << ConsoleDisplay::Yellow("[") << std::setw(2) << blk
            << ConsoleDisplay::Yellow(": ") << std::setw(12) << ConsoleDisplay::ColourStr(blk) << ConsoleDisplay::Yellow("]")
            << ", back " << ConsoleDisplay::Yellow("[") << std::setw(2) << none << ConsoleDisplay::Yellow(": ") << std::setw(12)
            << ConsoleDisplay::ColourStr(none) << ConsoleDisplay::Yellow("]") << " -->" << std::endl;
        std::cout << ConsoleDisplay::Yellow("    :") << " fore " << ConsoleDisplay::Yellow("[") << std::setw(2) << none
            << ConsoleDisplay::Yellow(": ") << std::setw(12) << ConsoleDisplay::ColourStr(none) << ConsoleDisplay::Yellow("]")
            << ", back " << ConsoleDisplay::Yellow("[") << std::setw(2) << yel << ConsoleDisplay::Yellow(": ") << std::setw(12)
            << ConsoleDisplay::ColourStr(yel) << ConsoleDisplay::Yellow("]") << " -->" << std::endl;
        std::cout << ConsoleDisplay::Yellow("    :") << " fore " << ConsoleDisplay::Yellow("[") << std::setw(2) << b_red
            << ConsoleDisplay::Yellow(": ") << std::setw(12) << ConsoleDisplay::ColourStr(b_red) << ConsoleDisplay::Yellow("]")
            << ", back " << ConsoleDisplay::Yellow("[") << std::setw(2) << none << ConsoleDisplay::Yellow(": ") << std::setw(12)
            << ConsoleDisplay::ColourStr(none) << ConsoleDisplay::Yellow("]") << " -->" << std::endl;

        std::cout << "           [";
        ConsoleDisplay::colText(b_yel, grn, " Col 1 ", std::cout, false);
        ConsoleDisplay::colText(blk, none, " Col 2 ", std::cout, false);
        ConsoleDisplay::colText(none, yel, " Col 3 ", std::cout, false);
        ConsoleDisplay::colText(b_red, none, " Col 4 ", std::cout);
        std::cout << "]" << std::endl << std::endl;
    }

    //foo << "Run lookup tests" << Foo::endOfLine;

    lookupTests();

    getString("Test run complete, press <enter> to exit", std::cerr);

    return 0;
}
