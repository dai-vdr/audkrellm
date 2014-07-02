#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)

AC_INIT([audkrellm], 0.0.2, [d+audacious@vdr.jp])
AM_INIT_AUTOMAKE($PACKAGE_NAME, $PACKAGE_VERSION, no-define)

AC_CONFIG_SRCDIR([src/audkrellm.c],
[src/audkrellm-button-bar.c],
[src/audkrellm-control-panel.c],
[src/audkrellm-led.c],
[src/audkrellm-options-entries.c],
[src/audkrellm-options-info.c],
[src/audkrellm-options-switches.c],
[src/audkrellm-options-toggles.c],
[src/audkrellm-options.c],
[src/audkrellm-popup-menu.c],
[src/audkrellm-scroll-panel.c],
[src/audkrellm-tooltip.c])

# config.h
AC_CONFIG_HEADER(src/config.h)

# Checks for programs.
AC_PROG_CC

# gettext
ALL_LINGUAS="ja"
AM_GNU_GETTEXT
LDFLAGS="$LDFLAGS $INTLLIBS"
localedir='${prefix}/share/locale'
AC_SUBST(localedir)

# pkg-config
PKG_CHECK_MODULES(GKRELLM, gkrellm >= 2.2.10)
AC_SUBST(GKRELLM_CFLAGS)
AC_SUBST(GKRELLM_LIBS)
#
PKG_CHECK_MODULES(AUDACIOUS, audacious >= 1.4.0)
AC_SUBST(AUDACIOUS_CFLAGS)
AC_SUBST(AUDACIOUS_LIBS)
#
PKG_CHECK_MODULES(DBUS, [dbus-1 >= 1.1.1 dbus-glib-1 >= 0.74])
AC_SUBST(DBUS_CFLAGS)
AC_SUBST(DBUS_LIBS)

AC_OUTPUT([Makefile src/Makefile intl/Makefile po/Makefile.in])
