# ===============================================================
# 
# Release under GPLv-3.0.
# 
# @file    Makefile.am
# @brief   
# @author  gnsyxiang <gnsyxiang@163.com>
# @date    15/07 2021 13:36
# @version v0.0.1
# 
# @since    note
# @note     note
# 
#     change log:
#     NO.     Author              Date            Modified
#     00      zhenquan.qiu        15/07 2021      create the file
# 
#     last modified: 15/07 2021 13:36
# ===============================================================

if COMPILE_MCU_AT32F4XX
mcu_type = at32f4xx
endif

if COMPILE_MCU_HC32L13X
mcu_type = hc32l13x
endif

SUBDIRS = $(mcu_type)

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

_ldflags_com    += \
                   -export-symbols-regex 'Hy*' \
                   -version-info @current@:@revision@:@age@ \
                   $(LIB_LDFLAGS_COM)

_ldadd_com      += $(top_builddir)/src/$(mcu_type)/libmcu.la

lib@project_name@_la_SOURCES    = $(_sources_com)
lib@project_name@_la_CPPFLAGS   = $(_cppflags_com)
lib@project_name@_la_CFLAGS     = $(_cflags_com)
lib@project_name@_la_CXXFLAGS   = $(_cxxflags_com)
lib@project_name@_la_LDFLAGS    = $(_ldflags_com)
lib@project_name@_la_LIBADD     = $(_ldadd_com)

