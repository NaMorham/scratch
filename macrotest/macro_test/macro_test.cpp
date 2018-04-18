#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "test_method_base.h"

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

#include <fstream>
#include <typeinfo>

#define FOO(fname)  Foo foo(fname, __FUNCTION__)

class Foo
{
public:
    enum eMarker
    {
        endl
    };

    Foo(std::string fname, std::string name) : m_name(name), m_file(fname, std::ofstream::app), m_newline(true)
    {
        if (m_file.good())
        {
            m_file << "[" << m_name << "] Begin" << std::endl;
        }
    }
    virtual ~Foo()
    {
        if (m_file.good())
        {
            m_file << "[" << m_name << "] End" << std::endl;
            m_file.close();
        }
    }

    friend std::ostream& operator<<(const Foo& foo, std::ostream& os);

    std::string name() { return m_name; }

    std::ofstream& file() { return m_file; }

    Foo& clear() { m_line.str(""); m_newline = true; return *this; }

    operator const std::string() { return m_line.str(); }

    template<class T>
    void write(T const& val)
    {
        if (typeid(val).hash_code() == typeid(Foo::endl).hash_code())
        {
            endLine();
        }
        else
        {
            if (m_line.good())
            {
                if (m_newline)
                {
                    m_newline = false;
                    m_line << "[" << m_name << "] ";
                }
                m_line << val;
            }
        }
    }

    template<eMarker T>
    Foo& operator<<(eMarker& marker)
    {
        switch (marker)
        {
        case Foo::endl:
            endLine();
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
    void endLine()
    {
        if (m_file.good())
        {
            m_file << m_line.str() << std::endl;
            m_line.str("");
            m_newline = true;
        }
    }

    std::string m_name;
    std::stringstream m_line;
    std::ofstream m_file;
    bool m_newline;
};

std::ostream& operator<<(const Foo& foo, std::ostream& os)
{
    return os;
}


int main(int argc, char ** argv, char **env)
{
    FOO("c:\\temp\\test.foo.log");
    foo << "Hello" << " " << "World" << Foo::endl << 42 << Foo::endl;

    return 0;

    std::cout << "Press <enter>:";
    std::string val;
    std::getline(std::cin, val, '\n');

    //PConsoleDisplay pConsole = ConsoleDisplay::get();
    ConsoleDisplay& theConsole = ConsoleDisplay::get();

    std::printf("Tests built: " __DATE__ ", " __TIME__ "\n");

    Test1 t1("t1", "foo", "bar");
    std::cerr << t1 << std::endl;

    ConsoleDisplay::allColours();

    ConsoleDisplay::eColours fore(ConsoleDisplay::B_White);
    ConsoleDisplay::eColours back(ConsoleDisplay::Red);
    std::cout << std::endl << "Test: fore [" << fore << ": " << ConsoleDisplay::ColourStr(fore);
    std::cout << "], back [" << back << ": " << ConsoleDisplay::ColourStr(back) << "] --> [";
    //ConsoleDisplay::winCol(7, 4, "Hello", std::cout);
    ConsoleDisplay::colText(fore, back, "Hello", std::cout);

    //ConsoleDisplay::winCol(7, 2, " World", std::cerr);
    ConsoleDisplay::colText(ConsoleDisplay::Black, ConsoleDisplay::B_Cyan, " World", std::cerr);
    std::cout << "]" << std::endl << std::endl;

    lookupTests();

    return 0;
}
