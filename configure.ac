#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([jsonval], [0.0.2], [https://github.com/dangerousben/jsonval/issues])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_YACC
AM_PROG_LEX

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL

# Checks for library functions.

AM_INIT_AUTOMAKE

AC_REQUIRE_AUX_FILE([tap-driver.sh])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
