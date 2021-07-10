# ===============================================================
# 
# Release under GPLv-3.0.
# 
# @file    Makefile.am
# @brief   
# @author  gnsyxiang <gnsyxiang@163.com>
# @date    05/03 2021 10:35
# @version v0.0.1
# 
# @since    note
# @note     note
# 
#     change log:
#     NO.     Author              Date            Modified
#     00      zhenquan.qiu        05/03 2021      create the file
# 
#     last modified: 05/03 2021 10:35
# ===============================================================

if COMPILE_MCU_AT32F4XX
SUBDIRS = at32f4xx
select_mcu_platform = at32f4xx
endif

lib_LTLIBRARIES = lib@project_name@.la

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
                   -I$(top_srcdir)/$(_lwip_lib)/src/include \
                   -I$(top_srcdir)/include

_sources_com    += \
                   hy_timer.c \
                   hy_uart.c \
                   hy_system.c

_cppflags_com   += \
                   $(CPPFLAGS_COM) \
                   $(_include_com)

_cflags_com     += $(CFLAGS_COM)

_cxxflags_com   += $(CXXFLAGS_COM)

_ldflags_com    += \
                   -export-symbols-regex 'Hy*' \
                   -version-info @current@:@revision@:@age@ \
                   $(LIB_LDFLAGS_COM)

_ldadd_com      += $(top_builddir)/src/$(select_mcu_platform)/libmcu.la

lib@project_name@_la_SOURCES    = $(_sources_com)
lib@project_name@_la_CPPFLAGS   = $(_cppflags_com)
lib@project_name@_la_CFLAGS     = $(_cflags_com)
lib@project_name@_la_CXXFLAGS   = $(_cxxflags_com)
lib@project_name@_la_LDFLAGS    = $(_ldflags_com)
lib@project_name@_la_LIBADD     = $(_ldadd_com)

