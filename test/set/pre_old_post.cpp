
// Test all pre, old, and post (for free func, but same for all contracts).

#include "../aux_/oteststream.hpp"
#include <boost/contract/function.hpp>
#include <boost/contract/guard.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

boost::contract::test::aux::oteststream out;

void f() {
    boost::contract::guard c = boost::contract::function()
        .precondition([] { out << "f::pre" << std::endl; })
        .old([] { out << "f::old" << std::endl; })
        .postcondition([] { out << "f::post" << std::endl; })
    ;
    out << "f::body" << std::endl;
}

int main() {
    std::ostringstream ok;

    out.str("");
    f();
    ok.str("");
    ok
        #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
            << "f::pre" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            << "f::old" << std::endl
        #endif
        << "f::body" << std::endl
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            << "f::post" << std::endl
        #endif
    ;
    BOOST_TEST(out.eq(ok.str()));

    return boost::report_errors();
}

