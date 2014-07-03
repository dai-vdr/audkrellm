#!/bin/sh

glib-gettextize -c -f
intltoolize -c -f --automake
autoreconf -i -f
