#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(cgsolver, 0.1b, mbaptist@fc.up.pt)

AC_CONFIG_SRCDIR([lass.h])

AC_PROG_INSTALL
AC_PROG_RANLIB

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP

FORTRAN="ifort"
AC_SUBST(FORTRAN)

FORTRAN_PATH=`which ifort | perl -pi -e "s/\/bin\/ifort//g"`
AC_SUBST(FORTRAN_PATH)

# Checks for libraries.
AC_CHECK_LIB([fftw3],[fftw_destroy_plan])

# Checks for header files.


# Check for cat++
AC_ARG_WITH(cat,
    [ --with-cat=<path> prefix of MySQL installation. e.g. /usr/local or /usr],
    [CAT_PREFIX=$with_cat],
    AC_MSG_ERROR([You must call configure with the --with-cat option.
    This tells configure where to find the cat++ library and headers.
    e.g. --with-cat=/usr/local or --with-cat=/usr])
)
AC_SUBST(CAT_PREFIX)
CAT_CFLAGS="-I${CAT_PREFIX}/include"
AC_SUBST(CAT_CFLAGS)


# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_INLINE

# Checks for library functions.

AC_CONFIG_FILES([Makefile cgsolver/Makefile vzdeigen/Makefile testing/Makefile])
AC_OUTPUT

