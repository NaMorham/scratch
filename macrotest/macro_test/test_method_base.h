#pragma once

#include <string>
#include <vector>
#include <memory>

#include "console_display.h"

typedef bool(*pfnTestFunc)(std::string in, std::string expected);

class ITestDecorator
{
public:
    virtual std::string name(std::string name) const = 0;
    virtual std::string result(std::string result) const = 0;
    virtual std::string label(std::string label) const = 0;
    virtual std::string value(std::string value) const = 0;
    virtual std::string test(std::string test) const = 0;
};

typedef std::shared_ptr<ITestDecorator> PTESTDecorator;

class DefaultTestDecorator : public ITestDecorator
{
public:
    virtual std::string name(std::string name) const { return name; };
    virtual std::string result(std::string result) const { return result; };
    virtual std::string label(std::string label) const { return label; }
    virtual std::string value(std::string value) const { return value; }
    virtual std::string test(std::string test) const { return ""; } // be default no wrapper
};

extern std::shared_ptr<DefaultTestDecorator> g_pDefaultDecorator;

class TestMethodBase
{
public:
    static std::string passFail(bool val) { return val ? "pass" : "fail"; }

    TestMethodBase() = delete;
    TestMethodBase(TestMethodBase&& orig) = delete;
    TestMethodBase& operator= (const TestMethodBase& rhs) = delete;
    TestMethodBase& operator= (TestMethodBase&& rhs) = delete;

    explicit TestMethodBase(std::string name, PTESTDecorator decorator = g_pDefaultDecorator) : m_name(name), m_pDecorator(decorator) {}
    //explicit TestMethodBase(std::string name, pfnTestFunc func) : m_name(name), m_func(func) {}
    TestMethodBase(const TestMethodBase& orig) : m_name(orig.name()), m_pDecorator(orig.decorator()) {}
    //TestMethodBase(const TestMethodBase& orig) : m_name(orig.name()), m_func(orig.func()) {}
    virtual ~TestMethodBase() { m_name.clear(); m_pDecorator.reset(); }
    //virtual ~TestMethodBase() { m_name.clear(); m_func = nullptr; }

    std::string name() const { return m_name; }
    //pfnTestFunc func() const { return m_func; }

    PTESTDecorator decorator() const { return m_pDecorator; }

    TestMethodBase& setDecorator(PTESTDecorator pDecorator) { m_pDecorator = pDecorator; }

    virtual bool operator()() const = 0;

private:
    std::string m_name;
//    pfnTestFunc m_func;

    PTESTDecorator m_pDecorator;
};

std::ostream& operator<< (std::ostream& os, const TestMethodBase& tmb);

typedef std::vector<std::shared_ptr<TestMethodBase>> MethodVec;
