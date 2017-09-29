# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002-2011.                             *
#  *     (C) Copyright Edward Diener 2011.                                    *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef SIMDPP_PREPROCESSOR_CONFIG_CONFIG_HPP
# define SIMDPP_PREPROCESSOR_CONFIG_CONFIG_HPP
#
# /* SIMDPP_PP_CONFIG_FLAGS */
#
# define SIMDPP_PP_CONFIG_STRICT() 0x0001
# define SIMDPP_PP_CONFIG_IDEAL() 0x0002
#
# define SIMDPP_PP_CONFIG_MSVC() 0x0004
# define SIMDPP_PP_CONFIG_MWCC() 0x0008
# define SIMDPP_PP_CONFIG_BCC() 0x0010
// not supported
# define SIMDPP_PP_CONFIG_EDG() 0x0020
// not supported
# define SIMDPP_PP_CONFIG_DMC() 0x0040
#
# ifndef SIMDPP_PP_CONFIG_FLAGS
#    if defined(__GCCXML__)
#        define SIMDPP_PP_CONFIG_FLAGS() (SIMDPP_PP_CONFIG_STRICT())
#    elif defined(__WAVE__)
#        define SIMDPP_PP_CONFIG_FLAGS() (SIMDPP_PP_CONFIG_STRICT())
#    elif defined(__MWERKS__) && __MWERKS__ >= 0x3200
#        define SIMDPP_PP_CONFIG_FLAGS() (SIMDPP_PP_CONFIG_STRICT())
#    elif defined(__EDG__) || defined(__EDG_VERSION__)
#        if defined(_MSC_VER) && (defined(__INTELLISENSE__) || __EDG_VERSION__ >= 308)
#            define SIMDPP_PP_CONFIG_FLAGS() (SIMDPP_PP_CONFIG_MSVC())
#        else
#            error Dispatching is not supported on this compiler
#        endif
#    elif defined(__MWERKS__)
#        define SIMDPP_PP_CONFIG_FLAGS() (SIMDPP_PP_CONFIG_MWCC())
#    elif defined(__DMC__)
#        error Dispatching is not supported on this compiler
#    elif defined(__BORLANDC__) && __BORLANDC__ >= 0x581
#        define SIMDPP_PP_CONFIG_FLAGS() (SIMDPP_PP_CONFIG_STRICT())
#    elif defined(__BORLANDC__) || defined(__IBMC__) || defined(__IBMCPP__) || defined(__SUNPRO_CC)
#        define SIMDPP_PP_CONFIG_FLAGS() (SIMDPP_PP_CONFIG_BCC())
#    elif defined(_MSC_VER) && !defined(__clang__)
#        define SIMDPP_PP_CONFIG_FLAGS() (SIMDPP_PP_CONFIG_MSVC())
#    else
#        define SIMDPP_PP_CONFIG_FLAGS() (SIMDPP_PP_CONFIG_STRICT())
#    endif
# endif
#
# /* SIMDPP_PP_CONFIG_EXTENDED_LINE_INFO */
#
# ifndef SIMDPP_PP_CONFIG_EXTENDED_LINE_INFO
#    define SIMDPP_PP_CONFIG_EXTENDED_LINE_INFO 0
# endif
#
# /* SIMDPP_PP_CONFIG_ERRORS */
#
# ifndef SIMDPP_PP_CONFIG_ERRORS
#    ifdef NDEBUG
#        define SIMDPP_PP_CONFIG_ERRORS 0
#    else
#        define SIMDPP_PP_CONFIG_ERRORS 1
#    endif
# endif
#
# /* SIMDPP_PP_VARIADICS */
#
# define SIMDPP_PP_VARIADICS_MSVC 0
# define SIMDPP_PP_VARIADICS 1
#
#    if defined _MSC_VER && _MSC_VER >= 1400 && (!defined __EDG__ || defined(__INTELLISENSE__)) && !defined __clang__
#        define SIMDPP_PP_VARIADICS 1
#        undef SIMDPP_PP_VARIADICS_MSVC
#        define SIMDPP_PP_VARIADICS_MSVC 1
#    endif
#
# endif
