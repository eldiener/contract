
// Test all derived and base classes without exit static invariants.

#define BOOST_CONTRACT_TEST_NO_A_STATIC_INV
#define BOOST_CONTRACT_TEST_NO_B_STATIC_INV
#define BOOST_CONTRACT_TEST_NO_C_STATIC_INV
#include "decl.hpp"

#include <boost/preprocessor/control/iif.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

int main() {
    std::ostringstream ok; ok // Test nothing fails.
        #if BOOST_CONTRACT_PRECONDITIONS
            << "a::ctor::pre" << std::endl
            << "b::ctor::pre" << std::endl
            << "c::ctor::pre" << std::endl
        #endif
        
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "c::ctor::old" << std::endl
        #endif
        << "c::ctor::body" << std::endl
        #if BOOST_CONTRACT_EXIT_INVARIANTS
            << "c::inv" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "c::ctor::post" << std::endl
        #endif
        
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "b::ctor::old" << std::endl
        #endif
        << "b::ctor::body" << std::endl
        #if BOOST_CONTRACT_EXIT_INVARIANTS
            << "b::inv" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "b::ctor::post" << std::endl
        #endif

        #if BOOST_CONTRACT_POSTCONDITIONS
            << "a::ctor::old" << std::endl
        #endif
        << "a::ctor::body" << std::endl
        #if BOOST_CONTRACT_EXIT_INVARIANTS
            << "a::inv" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "a::ctor::post" << std::endl
        #endif
    ;
    
    a_exit_static_inv = true;
    b_exit_static_inv = true;
    c_exit_static_inv = true;
    a_entering_static_inv = b_entering_static_inv = c_entering_static_inv =
            BOOST_PP_IIF(BOOST_CONTRACT_ENTRY_INVARIANTS, true, false);
    {
        out.str("");
        a aa;
        BOOST_TEST(out.eq(ok.str()));
    }
    
    a_exit_static_inv = false;
    b_exit_static_inv = true;
    c_exit_static_inv = true;
    a_entering_static_inv = b_entering_static_inv = c_entering_static_inv =
            BOOST_PP_IIF(BOOST_CONTRACT_ENTRY_INVARIANTS, true, false);
    {
        out.str("");
        a aa;
        BOOST_TEST(out.eq(ok.str()));
    }
    
    a_exit_static_inv = true;
    b_exit_static_inv = false;
    c_exit_static_inv = true;
    a_entering_static_inv = b_entering_static_inv = c_entering_static_inv =
            BOOST_PP_IIF(BOOST_CONTRACT_ENTRY_INVARIANTS, true, false);
    {
        out.str("");
        a aa;
        BOOST_TEST(out.eq(ok.str()));
    }
    
    a_exit_static_inv = true;
    b_exit_static_inv = true;
    c_exit_static_inv = false;
    a_entering_static_inv = b_entering_static_inv = c_entering_static_inv =
            BOOST_PP_IIF(BOOST_CONTRACT_ENTRY_INVARIANTS, true, false);
    {
        out.str("");
        a aa;
        BOOST_TEST(out.eq(ok.str()));
    }
    
    a_exit_static_inv = false;
    b_exit_static_inv = false;
    c_exit_static_inv = false;
    a_entering_static_inv = b_entering_static_inv = c_entering_static_inv =
            BOOST_PP_IIF(BOOST_CONTRACT_ENTRY_INVARIANTS, true, false);
    {
        out.str("");
        a aa;
        BOOST_TEST(out.eq(ok.str()));
    }

    return boost::report_errors();
}

