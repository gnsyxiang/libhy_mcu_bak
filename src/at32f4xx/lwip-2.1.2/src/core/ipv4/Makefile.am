# ===============================================================
# 
# Release under GPLv-3.0.
# 
# @file    Makefile.am
# @brief   
# @author  gnsyxiang <gnsyxiang@163.com>
# @date    07/07 2021 19:53
# @version v0.0.1
# 
# @since    note
# @note     note
# 
#     change log:
#     NO.     Author              Date            Modified
#     00      zhenquan.qiu        07/07 2021      create the file
# 
#     last modified: 07/07 2021 19:53
# ===============================================================

noinst_LTLIBRARIES = libipv4.la

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
_include_com    += \
                   -I$(top_srcdir)/$(_lwip_lib)/port \
                   -I$(top_srcdir)/$(_lwip_lib)/src/include

_sources_com    += \
                   dhcp.c \
                   autoip.c \
                   etharp.c \
                   icmp.c \
                   igmp.c \
                   ip4.c \
                   ip4_addr.c \
                   ip4_frag.c

_cppflags_com   += \
                   $(CPPFLAGS_COM) \
                   $(_include_com)

_cflags_com     += $(CFLAGS_COM)

_cxxflags_com   += $(CXXFLAGS_COM)

_ldflags_com    += $(LIB_LDFLAGS_COM)

_ldadd_com      +=

libipv4_la_SOURCES  = $(_sources_com)
libipv4_la_CPPFLAGS = $(_cppflags_com)
libipv4_la_CFLAGS   = $(_cflags_com)
libipv4_la_CXXFLAGS = $(_cxxflags_com)
libipv4_la_LDFLAGS  = $(_ldflags_com)
libipv4_la_LIBADD   = $(_ldadd_com)

