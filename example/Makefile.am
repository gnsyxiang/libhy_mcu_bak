# ===============================================================
# 
# Release under GPLv-3.0.
# 
# @file    Makefile.am
# @brief   
# @author  gnsyxiang <gnsyxiang@163.com>
# @date    05/03 2021 10:38
# @version v0.0.1
# 
# @since    note
# @note     note
# 
#     change log:
#     NO.     Author              Date            Modified
#     00      zhenquan.qiu        05/03 2021      create the file
# 
#     last modified: 05/03 2021 10:38
# ===============================================================

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
bin_PROGRAMS    =

_install_com    =
exampledir      = $(prefix)/example

# ---------------------
# add necessary content
# ---------------------
_include_com    += -I$(top_srcdir)/include

_sources_com    +=

_cppflags_com   += \
                   $(CPPFLAGS_COM) \
                   $(_include_com)

_cflags_com     += $(CFLAGS_COM)

_cxxflags_com   += $(CXXFLAGS_COM)

_ldflags_com    += \
                   $(BIN_LDFLAGS_COM) \
                   $(top_builddir)/src/lib@project_name@.la

if COMPILE_MCU_AT32F407VGT7
_ldflags_com    += -T$(top_srcdir)/src/at32f4xx/Libraries/CMSIS/CM4/DeviceSupport/startup/gcc/linker/AT32F407xG_FLASH.ld
endif

bin_PROGRAMS        += main.elf
main_elf_SOURCES    = $(_sources_com) main.c
main_elf_CPPFLAGS   = $(_cppflags_com)
main_elf_CFLAGS     = $(_cflags_com)
main_elf_CXXFLAGS   = $(_cxxflags_com)
main_elf_LDFLAGS    = $(_ldflags_com) -Wl,--gc-sections,-Map=main.map,-cref,-u,Reset_Handler
main_elf_LDADD      = $(_ldadd_com)

