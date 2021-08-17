# ===============================================================
# 
# Release under GPLv-3.0.
# 
# @file    Makefile.am
# @brief   
# @author  gnsyxiang <gnsyxiang@163.com>
# @date    17/08 2021 16:26
# @version v0.0.1
# 
# @since    note
# @note     note
# 
#     change log:
#     NO.     Author              Date            Modified
#     00      zhenquan.qiu        17/08 2021      create the file
# 
#     last modified: 17/08 2021 16:26
# ===============================================================

noinst_LTLIBRARIES = libcommon.la

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

_no_install_headers_com =
_install_headers_com    =

install_includedir      = $(includedir)/@project_name@

# ---------------------
# add necessary content
# ---------------------
_include_com    += \
                   -I$(top_srcdir)/src/hc32l13x/CMSIS/Include \
                   -I$(top_srcdir)/src/hc32l13x/driver/inc

_sources_com    += \
                   interrupts_hc32l13x.c \
                   system_hc32l13x.c

_cppflags_com   += \
                   $(CPPFLAGS_COM) \
                   $(_include_com)

_cflags_com     += $(CFLAGS_COM)

_cxxflags_com   += $(CXXFLAGS_COM)

_ldflags_com    += $(LIB_LDFLAGS_COM)

_ldadd_com      +=

libcommon_la_SOURCES  = $(_sources_com)
libcommon_la_CPPFLAGS = $(_cppflags_com)
libcommon_la_CFLAGS   = $(_cflags_com)
libcommon_la_CXXFLAGS = $(_cxxflags_com)
libcommon_la_LDFLAGS  = $(_ldflags_com)
libcommon_la_LIBADD   = $(_ldadd_com)

# ---------------------
# add necessary content
# ---------------------
_no_install_headers_com +=

_install_headers_com    += \
                           base_types.h \
                           board_stkhc32l13x.h \
                           ddl_device.h \
                           hc32l13x.h \
                           interrupts_hc32l13x.h \
                           system_hc32l13x.h

# ------------------
# make install files
# ------------------
noinst_HEADERS          = $(_no_install_headers_com)
install_include_HEADERS = $(_install_headers_com)

