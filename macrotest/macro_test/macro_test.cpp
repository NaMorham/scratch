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

int main(int argc, char ** argv, char **env)
{
    std::cout << "Press <enter>:";
    std::string val;
    std::getline(std::cin, val, '\n');

    //PConsoleDisplay pConsole = ConsoleDisplay::get();
    ConsoleDisplay& theConsole = ConsoleDisplay::get();

    std::printf("Tests built: " __DATE__ ", " __TIME__ "\n");

    Test1 t1("t1", "foo", "bar");
    std::cerr << t1 << std::endl;

    ConsoleDisplay::allColours();

    std::cerr << std::endl << "Test [";
    ConsoleDisplay::winCol(7, 4, "Hello", std::cerr);

    ConsoleDisplay::winCol(7, 2, " World", std::cerr);
    std::cerr << "]" << std::endl;

    return 0;
}
