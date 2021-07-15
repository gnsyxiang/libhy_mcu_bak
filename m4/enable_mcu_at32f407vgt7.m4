dnl ===============================================================
dnl 
dnl Release under GPLv-3.0.
dnl 
dnl @file    enable_mcu_at32f407vgt7.m4
dnl @brief   
dnl @author  gnsyxiang <gnsyxiang@163.com>
dnl @date    19/03 2021 08:16
dnl @version v0.0.1
dnl 
dnl @since    note
dnl @note     note
dnl 
dnl     change log:
dnl     NO.     Author              Date            Modified
dnl     00      zhenquan.qiu        19/03 2021      create the file
dnl 
dnl     last modified: 19/03 2021 08:16
dnl ===============================================================

# ENABLE_MCU_AT32F407VGT7()
# --------------------------------------------------------------
# enable mcu at32f407vgt7

AC_DEFUN([ENABLE_MCU_AT32F407VGT7],
    [
        AC_ARG_ENABLE([at32f407vgt7],
            [AS_HELP_STRING([--enable-at32f407vgt7], [enable mcu at32f407vgt7] [[default=no]])],
            [AC_DEFINE(HAVE_MCU_AT32F4XX, 1, [enable mcu at32f4xx])
             AC_DEFINE(HAVE_MCU_AT32F407VGT7, 1, [enable mcu at32f407vgt7])
             AT32F407VGT7_CFLAGS="-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -ffunction-sections -fdata-sections -DAT32F407VGT7 -DAT_START_F407_V1_0 -DUSE_STDPERIPH_DRIVER"
             AC_SUBST(AT32F407VGT7_CFLAGS)
            ])

        AM_CONDITIONAL([COMPILE_MCU_AT32F4XX], [test "x$enable_at32f407vgt7" = "xyes"])
        AM_CONDITIONAL([COMPILE_MCU_AT32F407VGT7], [test "x$enable_at32f407vgt7" = "xyes"])

    ])

