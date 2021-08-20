# ===============================================================
# 
# Release under GPLv-3.0.
# 
# @file    Makefile.am
# @brief   
# @author  gnsyxiang <gnsyxiang@163.com>
# @date    24/02 2021 10:39
# @version v0.0.1
# 
# @since    note
# @note     note
# 
#     change log:
#     NO.     Author              Date            Modified
#     00      zhenquan.qiu        24/02 2021      create the file
# 
#     last modified: 24/02 2021 10:39
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
                           arm_common_tables.h \
                           arm_const_structs.h \
                           arm_math.h \
                           cmsis_armcc.h \
                           cmsis_armcc_V6.h \
                           cmsis_iar.h

_install_headers_com    += \
                           core_cmSimd.h \
                           core_cmFunc.h \
                           cmsis_gcc.h \
                           core_cmInstr.h \
                           core_cm4.h

# ------------------
# make install files
# ------------------
noinst_HEADERS          = $(_no_install_headers_com)
install_include_HEADERS = $(_install_headers_com)

