# ===============================================================
# 
# Release under GPLv-3.0.
# 
# @file    Makefile.am
# @brief   
# @author  gnsyxiang <gnsyxiang@163.com>
# @date    17/08 2021 15:50
# @version v0.0.1
# 
# @since    note
# @note     note
# 
#     change log:
#     NO.     Author              Date            Modified
#     00      zhenquan.qiu        17/08 2021      create the file
# 
#     last modified: 17/08 2021 15:50
# ===============================================================

SUBDIRS = driver mcu

noinst_LTLIBRARIES = libmcu.la

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
                   -I$(top_srcdir)/include

_sources_com    += \
                   hy_system.c \
                   hy_time.c \
                   hy_uart.c

_cppflags_com   += \
                   $(CPPFLAGS_COM) \
                   $(_include_com)

_cflags_com     += $(CFLAGS_COM)

_cxxflags_com   += $(CXXFLAGS_COM)

_ldflags_com    += $(LIB_LDFLAGS_COM)

_ldadd_com      += \
                   $(top_builddir)/src/hc32l13x/mcu/common/libcommon.la \
                   $(top_builddir)/src/hc32l13x/driver/src/libdriver.la

libmcu_la_SOURCES    = $(_sources_com)
libmcu_la_CPPFLAGS   = $(_cppflags_com)
libmcu_la_CFLAGS     = $(_cflags_com)
libmcu_la_CXXFLAGS   = $(_cxxflags_com)
libmcu_la_LDFLAGS    = $(_ldflags_com)
libmcu_la_LIBADD     = $(_ldadd_com)

