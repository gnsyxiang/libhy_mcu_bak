# ===============================================================
# 
# Release under GPLv-3.0.
# 
# @file    Makefile.am
# @brief   
# @author  gnsyxiang <gnsyxiang@163.com>
# @date    07/07 2021 19:51
# @version v0.0.1
# 
# @since    note
# @note     note
# 
#     change log:
#     NO.     Author              Date            Modified
#     00      zhenquan.qiu        07/07 2021      create the file
# 
#     last modified: 07/07 2021 19:51
# ===============================================================

SUBDIRS = ipv4

noinst_LTLIBRARIES = libcore.la

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

# ---------------------
# add necessary content
# ---------------------
_include_com    += \
                   -I$(top_srcdir)/src/at32f4xx/3rd_lib/lwip-2.1.2/port \
                   -I$(top_srcdir)/src/at32f4xx/3rd_lib/lwip-2.1.2/src/include

_sources_com    += \
                   altcp.c \
                   altcp_alloc.c \
                   altcp_tcp.c \
                   def.c \
                   dns.c \
                   inet_chksum.c \
                   init.c \
                   ip.c \
                   mem.c \
                   memp.c \
                   netif.c \
                   pbuf.c \
                   raw.c \
                   stats.c \
                   sys.c \
                   tcp.c \
                   tcp_in.c \
                   tcp_out.c \
                   timeouts.c \
                   udp.c

_cppflags_com   += \
                   $(CPPFLAGS_COM) \
                   $(_include_com)

_cflags_com     += $(CFLAGS_COM)

_cxxflags_com   += $(CXXFLAGS_COM)

_ldflags_com    += $(LIB_LDFLAGS_COM) \
                   $(top_builddir)/src/at32f4xx/3rd_lib/lwip-2.1.2/src/core/ipv4/libipv4.la

libcore_la_SOURCES  = $(_sources_com)
libcore_la_CPPFLAGS = $(_cppflags_com)
libcore_la_CFLAGS   = $(_cflags_com)
libcore_la_CXXFLAGS = $(_cxxflags_com)
libcore_la_LDFLAGS  = $(_ldflags_com)
libcore_la_LIBADD   = $(_ldadd_com)

