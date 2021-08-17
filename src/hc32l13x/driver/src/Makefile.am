# ===============================================================
# 
# Release under GPLv-3.0.
# 
# @file    Makefile.am
# @brief   
# @author  gnsyxiang <gnsyxiang@163.com>
# @date    17/08 2021 16:23
# @version v0.0.1
# 
# @since    note
# @note     note
# 
#     change log:
#     NO.     Author              Date            Modified
#     00      zhenquan.qiu        17/08 2021      create the file
# 
#     last modified: 17/08 2021 16:23
# ===============================================================

noinst_LTLIBRARIES = libdriver.la

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
                   -I$(top_srcdir)/src/hc32l13x/CMSIS/Include \
                   -I$(top_srcdir)/src/hc32l13x/driver/inc \
                   -I$(top_srcdir)/src/hc32l13x/mcu/common

_sources_com    += \
                   adc.c \
                   adt.c \
                   aes.c \
                   bgr.c \
                   bt.c \
                   crc.c \
                   ddl.c \
                   debug.c \
                   dmac.c \
                   flash.c \
                   gpio.c \
                   hdiv.c \
                   i2c.c \
                   lcd.c \
                   lpm.c \
                   lptim.c \
                   lpuart.c \
                   lvd.c \
                   opa.c \
                   pca.c \
                   pcnt.c \
                   ram.c \
                   reset.c \
                   rtc.c \
                   spi.c \
                   sysctrl.c \
                   timer3.c \
                   trim.c \
                   trng.c \
                   uart.c \
                   vc.c \
                   wdt.c

_cppflags_com   += \
                   $(CPPFLAGS_COM) \
                   $(_include_com)

_cflags_com     += $(CFLAGS_COM)

_cxxflags_com   += $(CXXFLAGS_COM)

_ldflags_com    += $(LIB_LDFLAGS_COM)

_ldadd_com      +=

libdriver_la_SOURCES  = $(_sources_com)
libdriver_la_CPPFLAGS = $(_cppflags_com)
libdriver_la_CFLAGS   = $(_cflags_com)
libdriver_la_CXXFLAGS = $(_cxxflags_com)
libdriver_la_LDFLAGS  = $(_ldflags_com)
libdriver_la_LIBADD   = $(_ldadd_com)

