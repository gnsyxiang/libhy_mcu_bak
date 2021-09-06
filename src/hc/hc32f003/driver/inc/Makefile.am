# ===============================================================
# 
# Release under GPLv-3.0.
# 
# @file    Makefile.am
# @brief   
# @author  gnsyxiang <gnsyxiang@163.com>
# @date    06/09 2021 08:50
# @version v0.0.1
# 
# @since    note
# @note     note
# 
#     change log:
#     NO.     Author              Date            Modified
#     00      zhenquan.qiu        06/09 2021      create the file
# 
#     last modified: 06/09 2021 08:50
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
                           bt.h \
                           clk.h \
                           crc.h \
                           ddl.h \
                           flash.h \
                           gpio.h \
                           i2c.h \
                           lpm.h \
                           lvd.h \
                           pca.h \
                           reset.h \
                           spi.h \
                           trim.h \
                           uart.h \
                           vc.h \
                           wdt.h

# ------------------
# make install files
# ------------------
noinst_HEADERS          = $(_no_install_headers_com)
install_include_HEADERS = $(_install_headers_com)

