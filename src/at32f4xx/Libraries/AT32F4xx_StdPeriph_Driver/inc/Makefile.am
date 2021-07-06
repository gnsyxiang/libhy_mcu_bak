# ===============================================================
# 
# Release under GPLv-3.0.
# 
# @file    Makefile.am
# @brief   
# @author  gnsyxiang <gnsyxiang@163.com>
# @date    24/02 2021 10:25
# @version v0.0.1
# 
# @since    note
# @note     note
# 
#     change log:
#     NO.     Author              Date            Modified
#     00      zhenquan.qiu        24/02 2021      create the file
# 
#     last modified: 24/02 2021 10:25
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
_no_install_headers_com += \
                           at32f4xx_acc.h \
                           at32f4xx_adc.h \
                           at32f4xx_bkp.h \
                           at32f4xx_can.h \
                           at32f4xx_comp.h \
                           at32f4xx_crc.h \
                           at32f4xx_dac.h \
                           at32f4xx_dbgmcu.h \
                           at32f4xx_dma.h \
                           at32f4xx_ertc.h \
                           at32f4xx_eth.h \
                           at32f4xx_exti.h \
                           at32f4xx_flash.h \
                           at32f4xx_gpio.h \
                           at32f4xx_i2c.h \
                           at32f4xx_iwdg.h \
                           at32f4xx_pwr.h \
                           at32f4xx_rcc.h \
                           at32f4xx_rtc.h \
                           at32f4xx_sdio.h \
                           at32f4xx_spi.h \
                           at32f4xx_tim.h \
                           at32f4xx_usart.h \
                           at32f4xx_wwdg.h \
                           at32f4xx_xmc.h \
                           misc.h

_install_headers_com    +=

# ------------------
# make install files
# ------------------
noinst_HEADERS          = $(_no_install_headers_com)
install_include_HEADERS = $(_install_headers_com)

