#include "test_method_base.h"

int foo = 42;

std::ostream& operator<< (std::ostream& os, const TestMethodBase& tmb)
{
    os << "Test [" << tmb.name() << "] --> [" << TestMethodBase::passFail(tmb()) << "]";
    return os;
}

std::shared_ptr<DefaultTestDecorator> g_pDefaultDecorator = std::make_shared<DefaultTestDecorator>();
