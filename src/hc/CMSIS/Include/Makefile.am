# ===============================================================
# 
# Release under GPLv-3.0.
# 
# @file    Makefile.am
# @brief   
# @author  gnsyxiang <gnsyxiang@163.com>
# @date    17/08 2021 20:00
# @version v0.0.1
# 
# @since    note
# @note     note
# 
#     change log:
#     NO.     Author              Date            Modified
#     00      zhenquan.qiu        17/08 2021      create the file
# 
#     last modified: 17/08 2021 20:00
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
                           cmsis_armcc.h \
                           cmsis_armclang.h \
                           cmsis_armclang_ltm.h \
                           cmsis_compiler.h \
                           cmsis_gcc.h \
                           cmsis_iccarm.h \
                           cmsis_version.h \
                           core_armv81mml.h \
                           core_armv8mbl.h \
                           core_armv8mml.h \
                           core_cm0.h \
                           core_cm0plus.h \
                           core_cm1.h \
                           core_cm23.h \
                           core_cm33.h \
                           core_cm35p.h \
                           core_cm3.h \
                           core_cm4.h \
                           core_cm7.h \
                           core_sc000.h \
                           core_sc300.h \
                           mpu_armv7.h \
                           mpu_armv8.h \
                           tz_context.h

# ------------------
# make install files
# ------------------
noinst_HEADERS          = $(_no_install_headers_com)
install_include_HEADERS = $(_install_headers_com)

