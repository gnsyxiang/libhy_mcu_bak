# ===============================================================
# 
# Release under GPLv-3.0.
# 
# @file    Makefile.am
# @brief   
# @author  gnsyxiang <gnsyxiang@163.com>
# @date    06/07 2021 14:36
# @version v0.0.1
# 
# @since    note
# @note     note
# 
#     change log:
#     NO.     Author              Date            Modified
#     00      zhenquan.qiu        06/07 2021      create the file
# 
#     last modified: 06/07 2021 14:36
# ===============================================================

SUBDIRS = Libraries

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

_no_install_headers_com =
_install_headers_com    =

install_includedir      = $(includedir)/@project_name@

# ---------------------
# add necessary content
# ---------------------
_include_com    += \
                   -I$(top_srcdir)/include \
                   -I$(top_srcdir)/src/at32f4xx/Libraries/CMSIS/CM4/CoreSupport \
                   -I$(top_srcdir)/src/at32f4xx/Libraries/CMSIS/CM4/DeviceSupport \
                   -I$(top_srcdir)/src/at32f4xx/Libraries/AT32F4xx_StdPeriph_Driver/inc

_sources_com    +=

_cppflags_com   += \
                   $(CPPFLAGS_COM) \
                   $(_include_com)

_cflags_com     += $(CFLAGS_COM)

_cxxflags_com   += $(CXXFLAGS_COM)

_ldflags_com    += $(LIB_LDFLAGS_COM) \
                   $(top_builddir)/src/at32f4xx/Libraries/AT32F4xx_StdPeriph_Driver/src/libStdPeriph_Driver.la \
                   $(top_builddir)/src/at32f4xx/Libraries/CMSIS/CM4/DeviceSupport/libDeviceSupport.la \
                   $(top_builddir)/src/at32f4xx/Libraries/CMSIS/CM4/DeviceSupport/startup/gcc/libstartup.la

libmcu_la_SOURCES  = $(_sources_com)
libmcu_la_CPPFLAGS = $(_cppflags_com)
libmcu_la_CFLAGS   = $(_cflags_com)
libmcu_la_CXXFLAGS = $(_cxxflags_com)
libmcu_la_LDFLAGS  = $(_ldflags_com)
libmcu_la_LIBADD   = $(_ldadd_com)

