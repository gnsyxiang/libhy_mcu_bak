# ===============================================================
# 
# Release under GPLv-3.0.
# 
# @file    Makefile.am
# @brief   
# @author  gnsyxiang <gnsyxiang@163.com>
# @date    06/09 2021 08:45
# @version v0.0.1
# 
# @since    note
# @note     note
# 
#     change log:
#     NO.     Author              Date            Modified
#     00      zhenquan.qiu        06/09 2021      create the file
# 
#     last modified: 06/09 2021 08:45
# ===============================================================

SUBDIRS = driver mcu CMSIS

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
_include_com    += -I$(top_srcdir)/include

_sources_com    += hy_func_check.c

_cppflags_com   += \
                   $(CPPFLAGS_COM) \
                   $(_include_com)

_cflags_com     += $(CFLAGS_COM)

_cxxflags_com   += $(CXXFLAGS_COM)

_ldflags_com    += $(LIB_LDFLAGS_COM)

_ldadd_com      += \
                   $(top_builddir)/src/hc32f003/mcu/common/libcommon.la \
                   $(top_builddir)/src/hc32f003/driver/src/libdriver.la

libmcu_la_SOURCES    = $(_sources_com)
libmcu_la_CPPFLAGS   = $(_cppflags_com)
libmcu_la_CFLAGS     = $(_cflags_com)
libmcu_la_CXXFLAGS   = $(_cxxflags_com)
libmcu_la_LDFLAGS    = $(_ldflags_com)
libmcu_la_LIBADD     = $(_ldadd_com)

