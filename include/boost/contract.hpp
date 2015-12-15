
#ifndef BOOST_CONTRACT_HPP_
#define BOOST_CONTRACT_HPP_

/** @file */

#include <boost/contract/public_function.hpp>
#include <boost/contract/function.hpp>
#include <boost/contract/destructor.hpp>
#include <boost/contract/constructor.hpp>
#include <boost/contract/guard.hpp>
#include <boost/contract/override.hpp>
#include <boost/contract/base_types.hpp>
#include <boost/contract/old.hpp>
#include <boost/contract/assert.hpp>
#include <boost/contract/call_if.hpp>
#include <boost/contract/config.hpp>

// TODO: Consider renaming all/most *.i to *.hpp.

// TODO: Should C++11 move preserve class invariants at exit and/or on throw? Maybe not because after move no other public member can be called (but dtor can... so dtor should not check inv at that time...). If so, users could use an internal moved_ data member to guard class invariant checking and set that after the move operation... How can I program C++11 move operations with this lib? Should I used boost::contract::function instead of public_function? (But probably not because that does not subcontract and does not check inv at entry...)

// TODO: What shall I do with unions? Can/shall I contract them? Double check which members C++11 unions can have (ctor, dtor, etc?).

// TODO: Document that there is a MSVC 2010 bug for which lambdas cannot be used in template constructor intialization list (this was fixed in MSVC 2013). Therefore, an external (static member) function must be used (possibly with bind and cref) to program constructor preconditions on MSVC 2010 instead of using lambdas.

// TODO: Test failure handlers, throw on contract failure, and throw user-defined exceptions: (1) Add a test for throwing exception handlers (somewhat similar to stroustrup97/string.cpp but more comprehensive); (2) Test what happens if bodies throw (e.g., public function should still check inv, dtor too, but ctor should not, etc.)... test all contract types when bodies throw; (3) Test what happens if old expression copies throw (with OLDOF and with .old()).

// TODO: Test contract assertion disabled while checking assertions adding a test to disable/ similar to n1962/factorial.cpp, where contract recursively calls the function itself in the assertions.

// TODO: Test overloading for all contract types. Also test subcontracting of overloaded virtual functions (overload both overridden and overriding functions).

// TODO: Test what this lib does when derived public function overrides base's protected virtual function (substitution principle does not apply here because base's protected virtual functions cannot be called by users so it should not be subcontracted...).

// TODO: Test with function and array argument types like `void f(int x[2][3], int (*g)(int))`. This should work... but it might require to specialize some of this lib's internal templates...

// TODO: Test there is never ambiguity in resolving calls to public_function overloads (e.g., between public_function(v, some_func_ptr, this) and public_function<O>(v, &a::f, this)...).

// TODO: Document that users could program (scoped) locks at top of function definitions and before the contract code so to deal with contracts in multi-threaded situations. Would these locks need to be recursive for virtual calls? Test that...

// TODO: Look at Andrzej's discussion on preconditions and either support that in this lib or at least mention/compare it in the docs: https://akrzemi1.wordpress.com/2013/01/04/preconditions-part-i/

// TODO: Document pre > old > post are all optional but when they are specified they must be specified in this order (rationale: this is the logical order in which to specify them, other contract programming framework allow to mix this order, that could have been implemented in this lib too but it would complicated a bit the implementation to then allow for mixed orders that will be less clear logically).

#endif // #include guard

