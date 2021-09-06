# ===============================================================
# 
# Release under GPLv-3.0.
# 
# @file    Makefile.am
# @brief   
# @author  gnsyxiang <gnsyxiang@163.com>
# @date    17/08 2021 15:51
# @version v0.0.1
# 
# @since    note
# @note     note
# 
#     change log:
#     NO.     Author              Date            Modified
#     00      zhenquan.qiu        17/08 2021      create the file
# 
#     last modified: 17/08 2021 15:51
# ===============================================================

# ------------------
# defining variables
# ------------------
_no_install_headers_com =
_install_headers_com    =

install_includedir      = $(includedir)/@project_name@

# ---------------------
# add necessary content
# ---------------------
_no_install_headers_com +=

_install_headers_com    += \
                           adc.h \
                           adt.h \
                           aes.h \
                           bgr.h \
                           bt.h \
                           crc.h \
                           ddl.h \
                           debug.h \
                           dmac.h \
                           flash.h \
                           gpio.h \
                           hdiv.h \
                           i2c.h \
                           lcd.h \
                           lpm.h \
                           lptim.h \
                           lpuart.h \
                           lvd.h \
                           opa.h \
                           pca.h \
                           pcnt.h \
                           ram.h \
                           reset.h \
                           rtc.h \
                           spi.h \
                           sysctrl.h \
                           timer3.h \
                           trim.h \
                           trng.h \
                           uart.h \
                           vc.h \
                           wdt.h

# ------------------
# make install files
# ------------------
noinst_HEADERS          = $(_no_install_headers_com)
install_include_HEADERS = $(_install_headers_com)

