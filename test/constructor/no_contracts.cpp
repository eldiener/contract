
// Test contract compilation on/off.

#include "../aux_/oteststream.hpp"
#include <boost/contract/core/config.hpp>
#include <boost/contract/constructor.hpp> // Outside #if below for ctor pre.
#ifndef BOOST_CONTRACT_NO_CONSTRUCTORS
    #include <boost/contract/guard.hpp>
    #include <boost/contract/old.hpp>
#endif
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

boost::contract::test::aux::oteststream out;

struct b
    #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
        : private boost::contract::constructor_precondition<b>
    #endif
{
    #ifndef BOOST_CONTRACT_NO_INVARIANTS
        static void static_invariant() { out << "b::static_inv" << std::endl; }
        void invariant() const { out << "b::inv" << std::endl; }
    #endif

    explicit b(int x)
        #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
            : boost::contract::constructor_precondition<b>(
                [] { out << "b::ctor::pre" << std::endl; }
            )
        #endif
    {
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            boost::contract::old_ptr<int> old_x = BOOST_CONTRACT_OLDOF(x);
        #endif
        #ifndef BOOST_CONTRACT_NO_CONSTRUCTORS
            boost::contract::guard c = boost::contract::constructor(this)
                #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
                    .old([] { out << "b::f::old" << std::endl; })
                    .postcondition([] { out << "b::ctor::post" << std::endl; })
                #endif
            ;
        #endif
        out << "b::ctor::body" << std::endl;
    }
};

struct a :
    #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
        private boost::contract::constructor_precondition<a>,
    #endif
    public b
{
    #ifndef BOOST_CONTRACT_NO_INVARIANTS
        static void static_invariant() { out << "a::static_inv" << std::endl; }
        void invariant() const { out << "a::inv" << std::endl; }
    #endif

    explicit a(int x) :
        #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
            boost::contract::constructor_precondition<a>(
                [] { out << "a::ctor::pre" << std::endl; }
            ),
        #endif
        b(x)
    {
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            boost::contract::old_ptr<int> old_x = BOOST_CONTRACT_OLDOF(x);
        #endif
        #ifndef BOOST_CONTRACT_NO_CONSTRUCTORS
            boost::contract::guard c = boost::contract::constructor(this)
                #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
                    .old([] { out << "a::f::old" << std::endl; })
                    .postcondition([] { out << "a::ctor::post" << std::endl; })
                #endif
            ;
        #endif
        out << "a::ctor::body" << std::endl;
    }
};

int main() {
    std::ostringstream ok;
    out.str("");
    a aa(123);
    ok.str(""); ok
        #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
            << "a::ctor::pre" << std::endl
            << "b::ctor::pre" << std::endl
        #endif
        
        #ifndef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
            << "b::static_inv" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            << "b::f::old" << std::endl
        #endif
        << "b::ctor::body" << std::endl
        #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            << "b::ctor::post" << std::endl
        #endif

        #ifndef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
            << "a::static_inv" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            << "a::f::old" << std::endl
        #endif
        << "a::ctor::body" << std::endl
        #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
            << "a::static_inv" << std::endl
            << "a::inv" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            << "a::ctor::post" << std::endl
        #endif
    ;
    BOOST_TEST(out.eq(ok.str()));
    return boost::report_errors();
}

