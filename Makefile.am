
ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}

if ENABLE_DOCUMENTATION
doc_subdirs = doc
else
doc_subdirs =
endif

SUBDIRS = simdpp test perf $(doc_subdirs)

#dist_noinst_SCRIPTS = autogen.sh

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libsimdpp.pc
