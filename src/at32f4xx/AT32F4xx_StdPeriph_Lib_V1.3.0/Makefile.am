# ===============================================================
# 
# Release under GPLv-3.0.
# 
# @file    Makefile.am
# @brief   
# @author  gnsyxiang <gnsyxiang@163.com>
# @date    09/07 2021 13:40
# @version v0.0.1
# 
# @since    note
# @note     note
# 
#     change log:
#     NO.     Author              Date            Modified
#     00      zhenquan.qiu        09/07 2021      create the file
# 
#     last modified: 09/07 2021 13:40
# ===============================================================

SUBDIRS = Libraries

noinst_LTLIBRARIES = libStdPeriph_Lib.la

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

_at32f4xx_lib   = $(top_builddir)/src/at32f4xx/AT32F4xx_StdPeriph_Lib_V1.3.0/Libraries

# ---------------------
# add necessary content
# ---------------------
_include_com    +=

_sources_com    +=

_cppflags_com   += \
                   $(CPPFLAGS_COM) \
                   $(_include_com)

_cflags_com     += $(CFLAGS_COM)

_cxxflags_com   += $(CXXFLAGS_COM)

_ldflags_com    += $(LIB_LDFLAGS_COM)

_ldadd_com      += \
                   $(_at32f4xx_lib)/AT32F4xx_StdPeriph_Driver/src/libdriver.la \
                   $(_at32f4xx_lib)/CMSIS/CM4/DeviceSupport/libDeviceSupport.la \
                   $(_at32f4xx_lib)/CMSIS/CM4/DeviceSupport/startup/gcc/libstartup.la

libStdPeriph_Lib_la_SOURCES  = $(_sources_com)
libStdPeriph_Lib_la_CPPFLAGS = $(_cppflags_com)
libStdPeriph_Lib_la_CFLAGS   = $(_cflags_com)
libStdPeriph_Lib_la_CXXFLAGS = $(_cxxflags_com)
libStdPeriph_Lib_la_LDFLAGS  = $(_ldflags_com)
libStdPeriph_Lib_la_LIBADD   = $(_ldadd_com)

