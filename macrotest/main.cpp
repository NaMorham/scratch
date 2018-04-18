/**
 * Testing a preprocessor define
 *
 * compile using g++ main.cpp --std=c++11 -o macrotest
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>


void test1func(const char *name, int a) {
    std::cout << name << " = " << a << std::endl;
} 

struct ReplaceData { char find; std::string replace; };
const std::string replace(const std::string& str)
{
    static std::vector<ReplaceData> rd = { {'\b', "\\b"}, {'\t', "\\t"}, {'\n', "\\n"} };
    std::string result(str);
    int idx = 1;
    for (ReplaceData repd : rd)
    {
        std::stringstream ss;
        std::cerr << std::setw(2) << idx++ << ": [\"" << repd.find << "\":"
                  << std::hex << std::setw(2) << (int)repd.find << "] --> ["
                  << repd.replace << "]" << std::endl;
        //std::replace(result.begin(), result.end(), repd.find, repd.replace);
        for (char in : result)
        {
            if (in == repd.find)
                ss << repd.replace;
            else
                ss << in;
        }
        result.assign(ss.str());
        std::cerr << "result now == [" << result << "]" << std::endl;
    }
    return std::string("done");
}

#define TEST_1_FUNC(val) test1func(#val, (int)val)

int main(int argc, char * argv[])
{
    int v1 = 42;

    test1func("test1 direct, v1", v1);
    TEST_1_FUNC(v1);
    std::cerr << std::endl;

    std::string s1("abcdefg");
    std::string r1(replace(s1));
    std::cerr << std::endl;

    std::string s2(" a\tb\bc\nd");
    std::string r2(replace(s2));
    std::cerr << std::endl;

    return 0;
}

// EOF

