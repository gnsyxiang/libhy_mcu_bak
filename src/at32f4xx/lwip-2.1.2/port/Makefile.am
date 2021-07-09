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

noinst_LTLIBRARIES = libport.la

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

_at32f4xx_lib   = src/at32f4xx/AT32F4xx_StdPeriph_Lib_V1.3.0/Libraries
_lwip_lib       = src/at32f4xx/lwip-2.1.2

# ---------------------
# add necessary content
# ---------------------
_include_com    += \
                   -I$(top_srcdir)/$(_at32f4xx_lib)/CMSIS/CM4/CoreSupport \
                   -I$(top_srcdir)/$(_at32f4xx_lib)/CMSIS/CM4/DeviceSupport \
                   -I$(top_srcdir)/$(_at32f4xx_lib)/AT32F4xx_StdPeriph_Driver/inc \
                   -I$(top_srcdir)/$(_lwip_lib)/port \
                   -I$(top_srcdir)/$(_lwip_lib)/src/include

_sources_com    += \
                   sys_arch.c \
                   ethernetif.c

_cppflags_com   += \
                   $(CPPFLAGS_COM) \
                   $(_include_com)

_cflags_com     += $(CFLAGS_COM)

_cxxflags_com   += $(CXXFLAGS_COM)

_ldflags_com    += $(LIB_LDFLAGS_COM)

libport_la_SOURCES  = $(_sources_com)
libport_la_CPPFLAGS = $(_cppflags_com)
libport_la_CFLAGS   = $(_cflags_com)
libport_la_CXXFLAGS = $(_cxxflags_com)
libport_la_LDFLAGS  = $(_ldflags_com)
libport_la_LIBADD   = $(_ldadd_com)

