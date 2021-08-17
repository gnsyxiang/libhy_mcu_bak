dnl ===============================================================
dnl 
dnl Release under GPLv-3.0.
dnl 
dnl @file    enable_mcu.m4
dnl @brief   
dnl @author  gnsyxiang <gnsyxiang@163.com>
dnl @date    17/08 2021 15:40
dnl @version v0.0.1
dnl 
dnl @since    note
dnl @note     note
dnl 
dnl     change log:
dnl     NO.     Author              Date            Modified
dnl     00      zhenquan.qiu        17/08 2021      create the file
dnl 
dnl     last modified: 17/08 2021 15:40
dnl ===============================================================

# ENABLE_MCU()
# --------------------------------------------------------------
# enable mcu

AC_DEFUN([ENABLE_MCU],
    [
        AC_ARG_ENABLE([at32f407vgt7],
            [AS_HELP_STRING([--enable-at32f407vgt7], [enable mcu at32f407vgt7] [[default=no]])],
            [AC_DEFINE(HAVE_MCU_AT32F4XX, 1, [enable mcu at32f4xx])
             AC_DEFINE(HAVE_MCU_AT32F407VGT7, 1, [enable mcu at32f407vgt7])
             AT32F407VGT7_CFLAGS="-DAT32F407VGT7 -DAT_START_F407_V1_0 -DUSE_STDPERIPH_DRIVER"
             AC_SUBST(AT32F407VGT7_CFLAGS)
            ])

        AM_CONDITIONAL([COMPILE_MCU_AT32F4XX], [test "x$enable_at32f407vgt7" = "xyes"])
        AM_CONDITIONAL([COMPILE_MCU_AT32F407VGT7], [test "x$enable_at32f407vgt7" = "xyes"])

        AC_ARG_ENABLE([hc32l13x],
            [AS_HELP_STRING([--enable-hc32l13x], [enable mcu hc32l13x] [[default=no]])],
            [AC_DEFINE(HAVE_MCU_HC32L13X, 1, [enable mcu hc32l13x])
            ])

        AM_CONDITIONAL([COMPILE_MCU_HC32L13X], [test "x$enable_hc32l13x" = "xyes"])
    ])

