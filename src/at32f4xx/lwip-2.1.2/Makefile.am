# ===============================================================
# 
# Release under GPLv-3.0.
# 
# @file    Makefile.am
# @brief   
# @author  gnsyxiang <gnsyxiang@163.com>
# @date    07/07 2021 19:45
# @version v0.0.1
# 
# @since    note
# @note     note
# 
#     change log:
#     NO.     Author              Date            Modified
#     00      zhenquan.qiu        07/07 2021      create the file
# 
#     last modified: 07/07 2021 19:45
# ===============================================================

SUBDIRS = src port

noinst_LTLIBRARIES = liblwip.la

# ------------------
# defining variables
# ------------------
_include_com    =
_sources_com    =
_cppflags_com   =
_cflags_com     =
_cxxflags_com   =
_ldflags_com    =
_ldadd_com      =

_lwip_lib       = src/at32f4xx/lwip-2.1.2

# ---------------------
# add necessary content
# ---------------------
_include_com    += $(top_srcdir)/$(_lwip_lib)/src/include

_sources_com    +=

_cppflags_com   += \
                   $(CPPFLAGS_COM) \
                   $(_include_com)

_cflags_com     += $(CFLAGS_COM)

_cxxflags_com   += $(CXXFLAGS_COM)

_ldflags_com    += $(LIB_LDFLAGS_COM)

_ldadd_com      += \
				   $(top_builddir)/$(_lwip_lib)/port/libport.la \
				   $(top_builddir)/$(_lwip_lib)/src/api/libapi.la \
				   $(top_builddir)/$(_lwip_lib)/src/core/ipv4/libipv4.la \
				   $(top_builddir)/$(_lwip_lib)/src/core/libcore.la \
				   $(top_builddir)/$(_lwip_lib)/src/netif/libnetif.la

liblwip_la_SOURCES  = $(_sources_com)
liblwip_la_CPPFLAGS = $(_cppflags_com)
liblwip_la_CFLAGS   = $(_cflags_com)
liblwip_la_CXXFLAGS = $(_cxxflags_com)
liblwip_la_LDFLAGS  = $(_ldflags_com)
liblwip_la_LIBADD   = $(_ldadd_com)

