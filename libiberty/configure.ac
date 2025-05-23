dnl Process this file with autoconf to produce a configure script

AC_INIT
AC_CONFIG_SRCDIR([xmalloc.c])

# This works around the fact that libtool configuration may change LD
# for this particular configuration, but some shells, instead of
# keeping the changes in LD private, export them just because LD is
# exported.  We don't use libtool yet, but some day we might, so...
ORIGINAL_LD_FOR_MULTILIBS=$LD

dnl We use these options to decide which functions to include.
AC_ARG_WITH(target-subdir,
[  --with-target-subdir=SUBDIR      Configuring in a subdirectory for target])
AC_ARG_WITH(build-subdir,
[  --with-build-subdir=SUBDIR       Configuring in a subdirectory for build])
AC_ARG_WITH(cross-host,
[  --with-cross-host=HOST           Configuring with a cross compiler])
AC_ARG_WITH(newlib,
[  --with-newlib                    Configuring with newlib])

if test "${srcdir}" = "."; then
  if test -n "${with_build_subdir}"; then
    libiberty_topdir="${srcdir}/../.."
    with_target_subdir=
  elif test -z "${with_target_subdir}"; then
    libiberty_topdir="${srcdir}/.."
  else
    if test "${with_target_subdir}" != "."; then
      libiberty_topdir="${srcdir}/${with_multisrctop}../.."
    else
      libiberty_topdir="${srcdir}/${with_multisrctop}.."
    fi
  fi
else
  libiberty_topdir="${srcdir}/.."
fi
AC_SUBST(libiberty_topdir)
AC_CONFIG_AUX_DIR($libiberty_topdir)

dnl Very limited version of automake's enable-maintainer-mode

AC_MSG_CHECKING([whether to enable maintainer-specific portions of Makefiles])
  dnl maintainer-mode is disabled by default
  AC_ARG_ENABLE(maintainer-mode,
[  --enable-maintainer-mode
                          enable make rules and dependencies not useful
                          (and sometimes confusing) to the casual installer],
      maintainer_mode=$enableval,
      maintainer_mode=no)

AC_MSG_RESULT($maintainer_mode)

if test "$maintainer_mode" = "yes"; then
  MAINT=''
  NOTMAINT='#'
else
  MAINT='#'
  NOTMAINT=''
fi
AC_SUBST(MAINT)dnl
AC_SUBST(NOTMAINT)dnl

# Do we have a single-tree copy of texinfo?  Even if we do, we can't
# rely on it - libiberty is built before texinfo.
AC_CHECK_PROG(MAKEINFO, makeinfo, makeinfo, )
if test "x$MAKEINFO" = "x"; then
    MAKEINFO="@echo makeinfo missing; true"
    BUILD_INFO=
else
    BUILD_INFO=info
    case "$MAKEINFO" in
      */missing\ makeinfo*)
	BUILD_INFO=
	AC_MSG_WARN([
*** Makeinfo is missing. Info documentation will not be built.])
        ;;
      *)
	case x"`$MAKEINFO --version | grep 'GNU texinfo'`" in
	  x*\ [[1-3]].* )
	    MAKEINFO="@echo $MAKEINFO is too old, 4.0 or newer required; true"
	    BUILD_INFO=
	    AC_MSG_WARN([
*** Makeinfo is too old. Info documentation will not be built.])
	  ;;
	esac
	;;
    esac
fi
AC_SUBST(MAKEINFO)
AC_SUBST(BUILD_INFO)

AC_CHECK_PROG(PERL, perl, perl, )
if test x"$PERL" = x""; then
  HAVE_PERL='#'
else
  HAVE_PERL=''
fi
AC_SUBST(HAVE_PERL)

AC_CANONICAL_HOST

dnl When we start using automake:
dnl AM_INIT_AUTOMAKE(libiberty, 1.0)

dnl These must be called before AM_PROG_LIBTOOL, because it may want
dnl to call AC_CHECK_PROG.
AC_CHECK_TOOL(AR, ar)
AC_CHECK_TOOL(RANLIB, ranlib, :)

dnl When switching to automake, replace the following with AM_ENABLE_MULTILIB.
# Add --enable-multilib to configure.
# Default to --enable-multilib
AC_ARG_ENABLE(multilib,
[  --enable-multilib       build many library versions (default)],
[case "$enableval" in
  yes) multilib=yes ;;
  no)  multilib=no ;;
  *)   AC_MSG_ERROR([bad value $enableval for multilib option]) ;;
 esac],
	      [multilib=yes])

# Even if the default multilib is not a cross compilation,
# it may be that some of the other multilibs are.
if test $cross_compiling = no && test $multilib = yes \
   && test "x${with_multisubdir}" != x ; then
   cross_compiling=maybe
fi

# We may wish to install the target headers somewhere.
AC_MSG_CHECKING([whether to install libiberty headers and static library])
dnl install-libiberty is disabled by default

AC_ARG_ENABLE(install-libiberty,
[  --enable-install-libiberty       Install headers and library for end users],
enable_install_libiberty=$enableval,
enable_install_libiberty=no)dnl

# Option parsed, now set things appropriately.
case x"$enable_install_libiberty" in
  xyes|x)
    target_header_dir=libiberty
    ;;
  xno)   
    target_header_dir=
    ;;
  *) 
    # This could be sanity-checked in various ways...
    target_header_dir="${enable_install_libiberty}"
    ;;
esac
AC_MSG_RESULT($enable_install_libiberty)
AC_MSG_NOTICE([target_header_dir = $target_header_dir])

GCC_NO_EXECUTABLES
AC_PROG_CC
AC_GNU_SOURCE
AC_SYS_LARGEFILE
AC_PROG_CPP_WERROR

ACX_PROG_CC_WARNING_OPTS([-W -Wall -Wwrite-strings -Wc++-compat \
			  -Wstrict-prototypes \
			  -Wshadow=local], [ac_libiberty_warn_cflags])
ACX_PROG_CC_WARNING_ALMOST_PEDANTIC([], [ac_libiberty_warn_cflags])

AC_PROG_CC_C_O
# autoconf is lame and doesn't give us any substitution variable for this.
if eval "test \"`echo '$ac_cv_prog_cc_'${ac_cc}_c_o`\" = no"; then
  NO_MINUS_C_MINUS_O=yes
else
  OUTPUT_OPTION='-o $@'
fi
AC_SUBST(NO_MINUS_C_MINUS_O)
AC_SUBST(OUTPUT_OPTION)

AC_C_CONST
AC_C_INLINE
AC_C_BIGENDIAN

dnl When we start using libtool:
dnl Default to a non shared library.  This may be overridden by the
dnl configure option --enable-shared.
dnl AM_DISABLE_SHARED

dnl When we start using libtool:
dnl AM_PROG_LIBTOOL

dnl When we start using automake:
dnl AM_CONFIG_HEADER(config.h:config.in)
AC_CONFIG_HEADER(config.h:config.in)

dnl When we start using automake:
dnl AM_MAINTAINER_MODE
dnl AC_EXEEXT

dnl When we start using automake:
dnl AM_PROG_INSTALL
AC_PROG_INSTALL

# Don't build the shared library for build.
if [[ -n "${with_build_subdir}" ]]; then
  enable_shared=no
fi

frag=
case "${host}" in
  rs6000-ibm-aix3.1 | rs6000-ibm-aix)
                        frag=mh-aix ;;
  *-*-cxux7*)		frag=mh-cxux7 ;;
  *-*-freebsd2.1.*)	frag=mh-fbsd21 ;;
  *-*-freebsd2.2.[[012]])	frag=mh-fbsd21 ;;
  i370-*-opened*)       frag=mh-openedition ;;
  i[[34567]]86-*-windows*)	frag=mh-windows ;;
esac

if [[ -n "${frag}" ]]; then
  frag=${libiberty_topdir}/libiberty/config/$frag
fi

GCC_PICFLAG

# If they didn't specify --enable-shared, don't generate shared libs.
case "${enable_shared}" in
  yes) shared=yes ;;
  no) shared=no ;;
  "") shared=no ;;
  *) shared=yes ;;
esac

# ...unless --enable-host-shared was passed from top-level config:
if [[ "${enable_host_shared}" = "yes" ]]; then
  shared=yes
fi

if [[ "${shared}" != "yes" ]]; then
  PICFLAG=
fi
AC_SUBST(PICFLAG)

NOASANFLAG=
case " ${CFLAGS} " in
  *\ -fsanitize=address\ *) NOASANFLAG=-fno-sanitize=address ;;
esac
AC_SUBST(NOASANFLAG)

echo "# Warning: this fragment is automatically generated" > temp-frag

if [[ -n "${frag}" ]] && [[ -f "${frag}" ]]; then
  echo "Appending ${frag} to xhost-mkfrag"
  echo "# Following fragment copied from ${frag}" >> temp-frag
  cat ${frag} >> temp-frag
fi

# record if we want to build shared libs.
if [[ "${shared}" = "yes" ]]; then
  echo enable_shared = yes >> temp-frag
else
  echo enable_shared = no >> temp-frag
fi

frag=xhost-mkfrag
${CONFIG_SHELL-/bin/sh} ${libiberty_topdir}/move-if-change temp-frag xhost-mkfrag

host_makefile_frag=${frag}
AC_SUBST_FILE(host_makefile_frag)

# It's OK to check for header files.  Although the compiler may not be
# able to link anything, it had better be able to at least compile
# something.
AC_CHECK_HEADERS(sys/file.h sys/param.h limits.h stdlib.h malloc.h string.h unistd.h strings.h sys/time.h time.h sys/resource.h sys/stat.h sys/mman.h fcntl.h alloca.h sys/pstat.h sys/sysmp.h sys/sysinfo.h machine/hal_sysinfo.h sys/table.h sys/sysctl.h sys/systemcfg.h stdint.h stdio_ext.h process.h sys/prctl.h)
AC_HEADER_SYS_WAIT
AC_HEADER_TIME

libiberty_AC_DECLARE_ERRNO

# Determine sizes of some types.
AC_CHECK_SIZEOF([int])
AC_CHECK_SIZEOF([long])
AC_CHECK_SIZEOF([size_t])

# Check for presense of long long
AC_CHECK_TYPE([long long],
  [AC_DEFINE(HAVE_LONG_LONG, 1, [Define if you have the `long long' type.]) AC_CHECK_SIZEOF([long long])],
  [])

# Look for a 64-bit type.
AC_MSG_CHECKING([for a 64-bit type])
AC_CACHE_VAL(liberty_cv_uint64,
[AC_TRY_COMPILE(
[#ifdef HAVE_STDINT_H
#include <stdint.h>
#endif],
[extern uint64_t foo;],
liberty_cv_uint64=uint64_t,
[AC_TRY_COMPILE(
[#ifdef HAVE_LIMITS_H
#include <limits.h>
#endif
#ifndef CHAR_BIT
#define CHAR_BIT 8
#endif],
[extern char foo[sizeof(long) * CHAR_BIT >= 64 ? 1 : -1];],
liberty_cv_uint64="unsigned long",
[AC_TRY_COMPILE(
[#ifdef HAVE_LIMITS_H
#include <limits.h>
#endif
#ifndef CHAR_BIT
#define CHAR_BIT 8
#endif],
[extern char foo[sizeof(long long) * CHAR_BIT >= 64 ? 1 : -1];],
liberty_cv_uint64="unsigned long long", liberty_cv_uint64=none)])])])
AC_MSG_RESULT($liberty_cv_uint64)
if test "$liberty_cv_uint64" != none; then
  AC_DEFINE_UNQUOTED(UNSIGNED_64BIT_TYPE, $liberty_cv_uint64,
                     [Define to an unsigned 64-bit type available in the compiler.])
fi

AC_TYPE_INTPTR_T
AC_TYPE_UINTPTR_T
AC_TYPE_SSIZE_T

# Given the above check, we always have uintptr_t or a fallback
# definition.  So define HAVE_UINTPTR_T in case any imported code
# relies on it.
AC_DEFINE(HAVE_UINTPTR_T, 1, [Define if you have the \`uintptr_t' type.])

AC_TYPE_PID_T

# This is the list of functions which libiberty will provide if they
# are not available on the host.

funcs="asprintf"
funcs="$funcs atexit"
funcs="$funcs basename"
funcs="$funcs bcmp"
funcs="$funcs bcopy"
funcs="$funcs bsearch"
funcs="$funcs bzero"
funcs="$funcs calloc"
funcs="$funcs clock"
funcs="$funcs ffs"
funcs="$funcs getcwd"
funcs="$funcs getpagesize"
funcs="$funcs gettimeofday"
funcs="$funcs index"
funcs="$funcs insque"
funcs="$funcs memchr"
funcs="$funcs memcmp"
funcs="$funcs memcpy"
funcs="$funcs memmem"
funcs="$funcs memmove"
funcs="$funcs mempcpy"
funcs="$funcs memset"
funcs="$funcs mkstemps"
funcs="$funcs putenv"
funcs="$funcs random"
funcs="$funcs rename"
funcs="$funcs rindex"
funcs="$funcs setenv"
funcs="$funcs snprintf"
funcs="$funcs sigsetmask"
funcs="$funcs stpcpy"
funcs="$funcs stpncpy"
funcs="$funcs strcasecmp"
funcs="$funcs strchr"
funcs="$funcs strdup"
funcs="$funcs strncasecmp"
funcs="$funcs strndup"
funcs="$funcs strnlen"
funcs="$funcs strrchr"
funcs="$funcs strstr"
funcs="$funcs strtod"
funcs="$funcs strtol"
funcs="$funcs strtoul"
funcs="$funcs strtoll"
funcs="$funcs strtoull"
funcs="$funcs strverscmp"
funcs="$funcs tmpnam"
funcs="$funcs vasprintf"
funcs="$funcs vfprintf"
funcs="$funcs vprintf"
funcs="$funcs vsnprintf"
funcs="$funcs vsprintf"
funcs="$funcs waitpid"
funcs="$funcs setproctitle"

# Also in the old function.def file: alloca, vfork, getopt.

vars="sys_errlist sys_nerr sys_siglist"

checkfuncs="__fsetlocking canonicalize_file_name dup3 getrlimit getrusage \
 getsysinfo gettimeofday on_exit pipe2 psignal pstat_getdynamic pstat_getstatic \
 realpath setrlimit sbrk spawnve spawnvpe strerror strsignal sysconf sysctl \
 sysmp table times wait3 wait4"

# These are neither executed nor required, but they help keep
# autoheader happy without adding a bunch of text to acconfig.h.
if test "x" = "y"; then
  AC_CHECK_FUNCS(asprintf atexit \
    basename bcmp bcopy bsearch bzero \
    calloc canonicalize_file_name clock \
    dup3 \
    ffs __fsetlocking \
    getcwd getpagesize getrlimit getrusage getsysinfo gettimeofday \
    index insque \
    memchr memcmp memcpy memmem memmove memset mkstemps \
    on_exit \
    pipe2 psignal pstat_getdynamic pstat_getstatic putenv \
    random realpath rename rindex \
    sbrk setenv setproctitle setrlimit sigsetmask snprintf spawnve spawnvpe \
     stpcpy stpncpy strcasecmp strchr strdup \
     strerror strncasecmp strndup strnlen strrchr strsignal strstr strtod \
     strtol strtoul strtoll strtoull strverscmp sysconf sysctl sysmp \
    table times tmpnam \
    vasprintf vfprintf vprintf vsprintf \
    wait3 wait4 waitpid)
  AC_CHECK_DECLS([basename(char *), ffs, asprintf, vasprintf, snprintf, vsnprintf, strtol, strtoul, strtoll, strtoull, strnlen])
  AC_DEFINE(HAVE_SYS_ERRLIST, 1, [Define if you have the sys_errlist variable.])
  AC_DEFINE(HAVE_SYS_NERR,    1, [Define if you have the sys_nerr variable.])
  AC_DEFINE(HAVE_SYS_SIGLIST, 1, [Define if you have the sys_siglist variable.])
fi

# For each of these functions, if the host does not provide the
# function we want to put FN.o in LIBOBJS, and if the host does
# provide the function, we want to define HAVE_FN in config.h.

setobjs=
CHECK=
if test -n "${with_target_subdir}"; then

  # We are being configured as a target library.  AC_REPLACE_FUNCS
  # may not work correctly, because the compiler may not be able to
  # link executables.  Note that we may still be being configured
  # native.

  # If we are being configured for newlib, we know which functions
  # newlib provide and which ones we will be expected to provide.

  if test "x${with_newlib}" = "xyes"; then
    AC_LIBOBJ([asprintf])
    AC_LIBOBJ([basename])
    AC_LIBOBJ([insque])
    AC_LIBOBJ([random])
    AC_LIBOBJ([strdup])
    AC_LIBOBJ([vasprintf])

    for f in $funcs; do
      case "$f" in
	asprintf | basename | insque | random | strdup | vasprintf)
	  ;;
	*)
	  n=HAVE_`echo $f | tr 'abcdefghijklmnopqrstuvwxyz' 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'`
	  AC_DEFINE_UNQUOTED($n)
	  ;;
      esac
    done

    # newlib doesnt provide any of the variables in $vars, so we
    # dont have to check them here.

    # Of the functions in $checkfuncs, newlib only has strerror.
    AC_DEFINE(HAVE_STRERROR)

    setobjs=yes

  fi

  # If we are being configured for Mingw, we know which functions
  # Mingw provides and which ones we will be expected to provide.

  case "${host}" in
  *-*-mingw*)
    AC_LIBOBJ([asprintf])
    AC_LIBOBJ([basename])
    AC_LIBOBJ([bcmp])
    AC_LIBOBJ([bcopy])
    AC_LIBOBJ([bzero])
    AC_LIBOBJ([clock])
    AC_LIBOBJ([ffs])
    AC_LIBOBJ([getpagesize])
    AC_LIBOBJ([index])
    AC_LIBOBJ([insque])
    AC_LIBOBJ([mempcpy])
    AC_LIBOBJ([mkstemps])
    AC_LIBOBJ([random])
    AC_LIBOBJ([rindex])
    AC_LIBOBJ([sigsetmask])
    AC_LIBOBJ([stpcpy])
    AC_LIBOBJ([stpncpy])
    AC_LIBOBJ([strndup])
    AC_LIBOBJ([strnlen])
    AC_LIBOBJ([strverscmp])
    AC_LIBOBJ([vasprintf])
    AC_LIBOBJ([waitpid])

    for f in $funcs; do
      case "$f" in
	asprintf | basename | bcmp | bcopy | bzero | clock | ffs | getpagesize | index | insque | mempcpy | mkstemps | random | rindex | sigsetmask | stpcpy | stpncpy | strdup | strndup | strnlen | strverscmp | vasprintf | waitpid)
	  ;;
	*)
	  n=HAVE_`echo $f | tr 'abcdefghijklmnopqrstuvwxyz' 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'`
	  AC_DEFINE_UNQUOTED($n)
	  ;;
      esac
    done

    # Mingw doesnt provide any of the variables in $vars, so we
    # dont have to check them here.

    # Of the functions in $checkfuncs, Mingw only has strerror.
    AC_DEFINE(HAVE_STRERROR)

    setobjs=yes
    ;;

  *-*-msdosdjgpp)
    AC_LIBOBJ([vasprintf])
    AC_LIBOBJ([vsnprintf])
    AC_LIBOBJ([snprintf])
    AC_LIBOBJ([asprintf])

    for f in atexit basename bcmp bcopy bsearch bzero calloc clock ffs \
             getcwd getpagesize getrusage gettimeofday \
             index insque memchr memcmp memcpy memmove memset psignal \
             putenv random rename rindex sbrk setenv stpcpy strcasecmp \
             strchr strdup strerror strncasecmp strrchr strstr strtod \
             strtol strtoul sysconf times tmpnam vfprintf vprintf \
             vsprintf waitpid
    do
      n=HAVE_`echo $f | tr 'abcdefghijklmnopqrstuvwxyz' 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'`
      AC_DEFINE_UNQUOTED($n)
    done


    setobjs=yes
    ;;

  esac

else

   # Not a target library, so we set things up to run the test suite.
   CHECK=really-check

fi

AC_SUBST(CHECK)
AC_SUBST(target_header_dir)

case "${host}" in
  *-*-cygwin* | *-*-mingw*)
    AC_DEFINE(HAVE_SYS_ERRLIST)
    AC_DEFINE(HAVE_SYS_NERR)
    ;;
esac

if test -z "${setobjs}"; then
  case "${host}" in

  *-*-vxworks*)
    # Handle VxWorks configuration specially, since on VxWorks the
    # libraries are actually on the target board, not in the file
    # system.
    AC_LIBOBJ([basename])
    AC_LIBOBJ([getpagesize])
    AC_LIBOBJ([insque])
    AC_LIBOBJ([random])
    AC_LIBOBJ([strcasecmp])
    AC_LIBOBJ([strncasecmp])
    AC_LIBOBJ([strdup])
    AC_LIBOBJ([vfork])
    AC_LIBOBJ([waitpid])
    AC_LIBOBJ([vasprintf])
    for f in $funcs; do
      case "$f" in
	basename | getpagesize | insque | random | strcasecmp)
	  ;;
	strncasecmp | strdup | vfork | waitpid | vasprintf)
	  ;;
	*)
	  n=HAVE_`echo $f | tr 'abcdefghijklmnopqrstuvwxyz' 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'`
	  AC_DEFINE_UNQUOTED($n)
	  ;;
      esac
    done

    # VxWorks doesn't provide any of the variables in $vars, so we
    # don't have to check them here.

    # Of the functions in $checkfuncs, VxWorks only has strerror.
    AC_DEFINE(HAVE_STRERROR)

    setobjs=yes
    ;;

  esac
fi

if test -z "${setobjs}"; then

  case "${host}" in

  *-*-android*)
    # On android, getpagesize is defined in unistd.h as a static inline
    # function, which AC_CHECK_FUNCS does not handle properly.
    ac_cv_func_getpagesize=yes
    ;;

  *-*-mingw32*)
    # Under mingw32, sys_nerr and sys_errlist exist, but they are
    # macros, so the test below won't find them.
    libiberty_cv_var_sys_nerr=yes
    libiberty_cv_var_sys_errlist=yes
    ;;

  *-*-msdosdjgpp*)
    # vfork and fork are stubs.
    ac_cv_func_vfork_works=no
    ;;

  *-*-uwin*)
    # Under some versions of uwin, vfork is notoriously buggy and the test 
    # can hang configure; on other versions, vfork exists just as a stub.
    # FIXME: This should be removed once vfork in uwin's runtime is fixed.
    ac_cv_func_vfork_works=no
    # Under uwin 2.0+, sys_nerr and sys_errlist exist, but they are
    # macros (actually, these are imported from a DLL, but the end effect 
    # is the same), so the test below won't find them.
    libiberty_cv_var_sys_nerr=yes
    libiberty_cv_var_sys_errlist=yes
    ;;

  *-*-*vms*)
    # Under VMS, vfork works very different than on Unix. The standard test 
    # won't work, and it isn't easily adaptable. It makes more sense to
    # just force it.
    ac_cv_func_vfork_works=yes
    ;;

  esac

  # We haven't set the list of objects yet.  Use the standard autoconf
  # tests.  This will only work if the compiler works.
  AC_ISC_POSIX
  AC_REPLACE_FUNCS($funcs)
  libiberty_AC_FUNC_C_ALLOCA
  AC_FUNC_FORK
  if test $ac_cv_func_vfork_works = no; then
    AC_LIBOBJ([vfork])
  fi
  # We only need _doprnt if we might use it to implement v*printf.
  if test $ac_cv_func_vprintf != yes \
     || test $ac_cv_func_vfprintf != yes \
     || test $ac_cv_func_vsprintf != yes; then
    AC_REPLACE_FUNCS(_doprnt)
  else
    AC_CHECK_FUNCS(_doprnt)
  fi

  for v in $vars; do
    AC_MSG_CHECKING([for $v])
    AC_CACHE_VAL(libiberty_cv_var_$v,
      [AC_LINK_IFELSE([AC_LANG_PROGRAM([[int *p;]],[[extern int $v []; p = $v;]])],
		      [eval "libiberty_cv_var_$v=yes"],
		      [eval "libiberty_cv_var_$v=no"])])
    if eval "test \"`echo '$libiberty_cv_var_'$v`\" = yes"; then
      AC_MSG_RESULT(yes)
      n=HAVE_`echo $v | tr 'abcdefghijklmnopqrstuvwxyz' 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'`
      AC_DEFINE_UNQUOTED($n)
    else
      AC_MSG_RESULT(no)
    fi
  done

  # special check for _system_configuration because AIX <4.3.2 do not
  # contain the `physmem' member.
  AC_MSG_CHECKING([for external symbol _system_configuration])
  AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include <sys/systemcfg.h>]],
			[[double x = _system_configuration.physmem;]])],
    [AC_MSG_RESULT([yes])
    AC_DEFINE(HAVE__SYSTEM_CONFIGURATION, 1,
	      [Define if you have the _system_configuration variable.])],
    [AC_MSG_RESULT([no])])

  AC_CHECK_FUNCS($checkfuncs)
  AC_CHECK_DECLS([basename(char *), ffs, asprintf, vasprintf, snprintf, vsnprintf])
  AC_CHECK_DECLS([calloc, getenv, getopt, malloc, realloc, sbrk])
  AC_CHECK_DECLS([strtol, strtoul, strtoll, strtoull])
  AC_CHECK_DECLS([strverscmp])
  AC_CHECK_DECLS([strnlen])
  libiberty_NEED_DECLARATION(canonicalize_file_name)
fi

# Figure out which version of pexecute to use.
case "${host}" in
     *-*-mingw* | *-*-winnt*)	pexecute=pex-win32  ;;
     *-*-msdosdjgpp*)		pexecute=pex-djgpp  ;;
     *-*-msdos*)		pexecute=pex-msdos  ;;
     *)				pexecute=pex-unix   ;;
esac
AC_SUBST(pexecute)

libiberty_AC_FUNC_STRNCMP

# Install a library built with a cross compiler in $(tooldir) rather
# than $(libdir).
if test -z "${with_cross_host}"; then
  INSTALL_DEST=libdir
else
  INSTALL_DEST=tooldir
fi
AC_SUBST(INSTALL_DEST)

m4_pattern_allow(LIBOBJS)
L=""
for l in x $LIBOBJS; do
  case $l in
    x) ;;
    *) L="$L ./$l" ;;
  esac
done
LIBOBJS="$L"

dnl Required by html and install-html
AC_SUBST(datarootdir)
AC_SUBST(docdir)
AC_SUBST(htmldir)
AC_CHECK_PROG(LLVM_CONFIG_FOUND, llvm-config, yes)
AS_IF([test x"$LLVM_CONFIG_FOUND" != x"yes"], [AC_MSG_ERROR([Please make sure llvm-config is in your PATH.])])
AC_SUBST([LLVM_CXXFLAGS], [$(llvm-config --cxxflags)])
AC_SUBST([LLVM_CFLAGS], [$(llvm-config --cflags)])
AC_SUBST([LLVM_LDFLAGS], [$(llvm-config --ldflags)])
AC_SUBST([LLVM_LIBS], [$(llvm-config --libs)])

# We need multilib support, but only if configuring for the target.
AC_CONFIG_FILES([Makefile testsuite/Makefile])
AC_CONFIG_COMMANDS([default],
  [[test -z "$CONFIG_HEADERS" || echo timestamp > stamp-h
if test -n "$CONFIG_FILES"; then
  if test -n "${with_target_subdir}"; then
    # FIXME: We shouldn't need to set ac_file
    ac_file=Makefile
    LD="${ORIGINAL_LD_FOR_MULTILIBS}"
    . ${libiberty_topdir}/config-ml.in
  fi
fi]],
[[srcdir=${srcdir}
host=${host}
target=${target}
with_target_subdir=${with_target_subdir}
with_multisubdir=${with_multisubdir}
ac_configure_args="--enable-multilib ${ac_configure_args}"
CONFIG_SHELL=${CONFIG_SHELL-/bin/sh}
ORIGINAL_LD_FOR_MULTILIBS="${ORIGINAL_LD_FOR_MULTILIBS}"
libiberty_topdir=${libiberty_topdir}
]])
AC_OUTPUT
