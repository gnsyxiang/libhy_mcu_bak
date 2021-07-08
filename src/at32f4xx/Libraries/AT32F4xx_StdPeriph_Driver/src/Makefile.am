# ===============================================================
# 
# Release under GPLv-3.0.
# 
# @file    Makefile.am
# @brief   
# @author  gnsyxiang <gnsyxiang@163.com>
# @date    24/02 2021 10:34
# @version v0.0.1
# 
# @since    note
# @note     note
# 
#     change log:
#     NO.     Author              Date            Modified
#     00      zhenquan.qiu        24/02 2021      create the file
# 
#     last modified: 24/02 2021 10:34
# ===============================================================

noinst_LTLIBRARIES = libStdPeriph_Driver.la

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
                   -I$(top_srcdir)/include \
                   -I$(top_srcdir)/src/at32f4xx/Libraries/CMSIS/CM4/CoreSupport \
                   -I$(top_srcdir)/src/at32f4xx/Libraries/CMSIS/CM4/DeviceSupport \
                   -I$(top_srcdir)/src/at32f4xx/Libraries/AT32F4xx_StdPeriph_Driver/inc

_sources_com    += \
                   at32f4xx_acc.c \
                   at32f4xx_adc.c \
                   at32f4xx_bkp.c \
                   at32f4xx_can.c \
                   at32f4xx_comp.c \
                   at32f4xx_crc.c \
                   at32f4xx_dac.c \
                   at32f4xx_dbgmcu.c \
                   at32f4xx_dma.c \
                   at32f4xx_ertc.c \
                   at32f4xx_eth.c \
                   at32f4xx_exti.c \
                   at32f4xx_flash.c \
                   at32f4xx_gpio.c \
                   at32f4xx_i2c.c \
                   at32f4xx_iwdg.c \
                   at32f4xx_pwr.c \
                   at32f4xx_rcc.c \
                   at32f4xx_rtc.c \
                   at32f4xx_sdio.c \
                   at32f4xx_spi.c \
                   at32f4xx_tim.c \
                   at32f4xx_usart.c \
                   at32f4xx_wwdg.c \
                   at32f4xx_xmc.c \
                   misc.c

_cppflags_com   += \
                   $(CPPFLAGS_COM) \
                   $(_include_com)

_cflags_com     += $(CFLAGS_COM)

_cxxflags_com   += $(CXXFLAGS_COM)

_ldflags_com    += $(LIB_LDFLAGS_COM)

libStdPeriph_Driver_la_SOURCES  = $(_sources_com)
libStdPeriph_Driver_la_CPPFLAGS = $(_cppflags_com)
libStdPeriph_Driver_la_CFLAGS   = $(_cflags_com)
libStdPeriph_Driver_la_CXXFLAGS = $(_cxxflags_com)
libStdPeriph_Driver_la_LDFLAGS  = $(_ldflags_com)
libStdPeriph_Driver_la_LIBADD   = $(_ldadd_com)

