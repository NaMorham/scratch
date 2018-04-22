#include <string>
#include <fstream>
#include <typeinfo>
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
    /*
    std::cerr << ConsoleDisplay::Yellow("Test [") << ConsoleDisplay::ColourStr(val)
        << ConsoleDisplay::Yellow("]") << std::endl;

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
    /*/
    std::cerr << ConsoleDisplay::Yellow("| ") << std::setw(17) << " " << ConsoleDisplay::Yellow(" |")
        << " fg " << ConsoleDisplay::Yellow("|  ") << std::setw(3) << static_cast<int32_t>(ConsoleDisplay::GetColValue(val, true))
        << ConsoleDisplay::Yellow(" |  ") << std::setw(3) << static_cast<int32_t>(ConsoleDisplay::GetColValue(val, false))
        << ConsoleDisplay::Yellow("  | ");
    ConsoleDisplay::colText(val, "****", std::cerr, true, true);
    std::cerr << ConsoleDisplay::Yellow(" | ");
    ConsoleDisplay::colText(val, "****", std::cerr, true, false);
    std::cerr << ConsoleDisplay::Yellow(" | ") << std::endl;
    
    std::cerr << ConsoleDisplay::Yellow("| ") << std::setw(12) << ConsoleDisplay::ColourStr(val)
        << ConsoleDisplay::Yellow(" : ") << std::setw(2) << val
        << ConsoleDisplay::Yellow(" +----+------+-------+------+------+") << std::endl;

    std::cerr << ConsoleDisplay::Yellow("| ") << std::setw(17) << " " << ConsoleDisplay::Yellow(" |")
        << " bg " << ConsoleDisplay::Yellow("|  ") << std::setw(3) << static_cast<int32_t>(ConsoleDisplay::GetBGColValue(val, true))
        << ConsoleDisplay::Yellow(" |  ") << std::setw(3) << static_cast<int32_t>(ConsoleDisplay::GetBGColValue(val, false))
        << ConsoleDisplay::Yellow("  | ");
    ConsoleDisplay::colText(ConsoleDisplay::eNone, val, "****", std::cerr, true, true);
    std::cerr << ConsoleDisplay::Yellow(" | ");
    ConsoleDisplay::colText(ConsoleDisplay::eNone, val, "****", std::cerr, true, false);
    std::cerr << ConsoleDisplay::Yellow(" | ") << std::endl;
    
    std::cerr <<
        ConsoleDisplay::Yellow("+-------------------+----+------+-------+------+------+") << std::endl;
    //*/
}

void lookupTests()
{
    std::cerr << std::endl <<
        ConsoleDisplay::Yellow("+-------------------+----+------+-------+------+------+") << std::endl;

    std::cerr << ConsoleDisplay::Yellow("|") << ConsoleDisplay::B_White("        Test       ") << ConsoleDisplay::Yellow("|")
        << ConsoleDisplay::B_White(" ## ") << ConsoleDisplay::Yellow("|") << ConsoleDisplay::B_White(" win# ")
        << ConsoleDisplay::Yellow("|") << ConsoleDisplay::B_White(" ansi# ") << ConsoleDisplay::Yellow("|")
        << ConsoleDisplay::B_White("  win ") << ConsoleDisplay::Yellow("|") << ConsoleDisplay::B_White(" ansi ")
        << ConsoleDisplay::Yellow("|") << std::endl;

    std::cerr <<
        ConsoleDisplay::Yellow("+-------------------+----+------+-------+------+------+") << std::endl;
    //                          |         Blue :  5 | fg |  111 |  222  | **** | **** |
    ColTest(ConsoleDisplay::eNone);
    ColTest(ConsoleDisplay::eBlack);
    ColTest(ConsoleDisplay::eRed);
    ColTest(ConsoleDisplay::eGreen);
    ColTest(ConsoleDisplay::eYellow);
    ColTest(ConsoleDisplay::eBlue);
    ColTest(ConsoleDisplay::eMagenta);
    ColTest(ConsoleDisplay::eCyan);
    ColTest(ConsoleDisplay::eWhite);

    //std::cerr << std::endl <<
    //    ConsoleDisplay::Yellow("+-------------------+----+------+-------+------+------+") << std::endl;

    std::cerr << ConsoleDisplay::Yellow("|") << ConsoleDisplay::B_White("        Test       ") << ConsoleDisplay::Yellow("|")
        << ConsoleDisplay::B_White(" ## ") << ConsoleDisplay::Yellow("|") << ConsoleDisplay::B_White(" win# ")
        << ConsoleDisplay::Yellow("|") << ConsoleDisplay::B_White(" ansi# ") << ConsoleDisplay::Yellow("|")
        << ConsoleDisplay::B_White("  win ") << ConsoleDisplay::Yellow("|") << ConsoleDisplay::B_White(" ansi ")
        << ConsoleDisplay::Yellow("|") << std::endl;

    std::cerr <<
        ConsoleDisplay::Yellow("+-------------------+----+------+-------+------+------+") << std::endl;
    //                          | Bold Magenta : 14 | fg |  111 |  222  | **** | **** |
    ColTest(ConsoleDisplay::eB_Black);
    ColTest(ConsoleDisplay::eB_Red);
    ColTest(ConsoleDisplay::eB_Green);
    ColTest(ConsoleDisplay::eB_Yellow);
    ColTest(ConsoleDisplay::eB_Blue);
    ColTest(ConsoleDisplay::eB_Magenta);
    ColTest(ConsoleDisplay::eB_Cyan);
    ColTest(ConsoleDisplay::eB_White);

    std::cerr << ConsoleDisplay::Yellow("|") << ConsoleDisplay::B_White("        Test       ") << ConsoleDisplay::Yellow("|")
        << ConsoleDisplay::B_White(" ## ") << ConsoleDisplay::Yellow("|") << ConsoleDisplay::B_White(" win# ")
        << ConsoleDisplay::Yellow("|") << ConsoleDisplay::B_White(" ansi# ") << ConsoleDisplay::Yellow("|")
        << ConsoleDisplay::B_White("  win ") << ConsoleDisplay::Yellow("|") << ConsoleDisplay::B_White(" ansi ")
        << ConsoleDisplay::Yellow("|") << std::endl;

    std::cerr <<
        ConsoleDisplay::Yellow("+-------------------+----+------+-------+------+------+") << std::endl;

    std::cerr << std::endl;
}

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

    getString();

    //foo << "Set up the console" << Foo::endOfLine;

    ConsoleDisplay& theConsole = ConsoleDisplay::get();

    std::cerr << "Tests built: " << __DATE__ << ", " << __TIME__ << std::endl << std::endl;

    CONCAT_TEST("", "simple test 2", concat());
    CONCAT_TEST("Hello World", "simple test 1", concat("Hello", " ", "World"));

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

    //lookupTests();

    //getString("Test run complete, press <enter> to exit", std::cerr);

    return 0;
}
