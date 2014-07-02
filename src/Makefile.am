plugin_PROGRAMS = audkrellm.so

plugindir = $(libdir)/gkrellm2/plugins/

audkrellm_so_SOURCES = audkrellm.c \
	\
	audkrellm-playlist.c \
	\
	audkrellm-scroll-panel.c \
	audkrellm-tooltip.c \
	\
	audkrellm-control-panel.c \
	audkrellm-led.c \
	audkrellm-button-bar.c \
	\
	audkrellm-popup-menu.c \
	\
	audkrellm-options.c \
	audkrellm-options-entries.c \
	audkrellm-options-toggles.c \
	audkrellm-options-switches.c \
	audkrellm-options-info.c

AM_CFLAGS = -fPIC @GKRELLM_CFLAGS@ @AUDACIOUS_CFLAGS@ @AUDCLIENT_CFLAGS@ @DBUS_CFLAGS@
AM_LDFLAGS = -Wl -shared @GKRELLM_LIBS@ @AUDACIOUS_LIBS@ @AUDCLIENT_LIBS@ @DBUS_LIBS@
