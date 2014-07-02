#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.65)

AC_INIT([audkrellm], 0.2.0, [d+audacious@vdr.jp])
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
AC_PROG_INTLTOOL([0.41.1])
GETTEXT_PACKAGE=$PACKAGE_NAME
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE, "$GETTEXT_PACKAGE", [gettext domains])
ALL_LINGUAS="ja"
AM_GLIB_GNU_GETTEXT
localedir='${prefix}/share/locale'
AC_SUBST(localedir)

# pkg-config
PKG_CHECK_MODULES(GKRELLM, gkrellm >= 2.3.5)
AC_SUBST(GKRELLM_CFLAGS)
AC_SUBST(GKRELLM_LIBS)
#
PKG_CHECK_MODULES(AUDACIOUS, audacious >= 2.4.3)
AC_SUBST(AUDACIOUS_CFLAGS)
AC_SUBST(AUDACIOUS_LIBS)
#
PKG_CHECK_MODULES(AUDCLIENT, audclient >= 2.4.3)
AC_SUBST(AUDCLIENT_CFLAGS)
AC_SUBST(AUDCLIENT_LIBS)
#
PKG_CHECK_MODULES(DBUS, [dbus-1 >= 1.4.6 dbus-glib-1 >= 0.92])
AC_SUBST(DBUS_CFLAGS)
AC_SUBST(DBUS_LIBS)

AC_OUTPUT([Makefile src/Makefile po/Makefile.in])
