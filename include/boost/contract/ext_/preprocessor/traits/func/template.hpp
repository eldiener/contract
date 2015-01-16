
#ifndef BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_HPP_
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_HPP_

#include <boost/contract/ext_/preprocessor/traits/params.hpp>
#include <boost/contract/ext_/preprocessor/traits/adt.hpp>
#include <boost/contract/ext_/preprocessor/keyword/template.hpp>
#include <boost/contract/ext_/preprocessor/paren/front.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

/* PRIVATE */

// Precondition: decl = `(,,,) ...` from `template(,,,) ...` originally in decl.
// This macro will also parse `(,,,)` into a pp-list of template param traits.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_(decl, traits) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
                traits, \
                template BOOST_PP_EMPTY \
            ), \
            BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAMS_TRAITS( \
                    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
        ) \
    )

// Precondition: decl = `template(,,,) ...`.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_YES_(decl, traits) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_TEMPLATE_REMOVE_FRONT(decl), traits)

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_NO_(decl, traits) \
    ( \
        decl \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
                traits, \
                BOOST_PP_EMPTY \
            ), \
            BOOST_PP_NIL \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_PARSE_ARGS_(decl, traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TEMPLATE_FRONT(decl), \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_NO_ \
    )(decl, traits)

/* PUBLIC */

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_PARSE(decl_traits) \
    BOOST_CONTRACT_EXT_PP_EXPAND_ONCE( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_PARSE_ARGS_ decl_traits)

// Expand to `template | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_TEMPLATE_INDEX, traits)()

// Expand to pp-list of function template parameters. Each single template
// parameter in this pp-list can be inspected using PARAM_TRAITS macros.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_PARAMS(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_TEMPLATE_PARAMS_INDEX, \
        traits \
    )

#endif // #include guard

