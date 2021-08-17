dnl ===============================================================
dnl 
dnl Release under GPLv-3.0.
dnl 
dnl @file    select_mcu_cortex.m4
dnl @brief   
dnl @author  gnsyxiang <gnsyxiang@163.com>
dnl @date    17/08 2021 15:03
dnl @version v0.0.1
dnl 
dnl @since    note
dnl @note     note
dnl 
dnl     change log:
dnl     NO.     Author              Date            Modified
dnl     00      zhenquan.qiu        17/08 2021      create the file
dnl 
dnl     last modified: 17/08 2021 15:03
dnl ===============================================================

# SELECT_MCU_CORTEX()
# --------------------------------------------------------------
# select mcu cortex

AC_DEFUN([SELECT_MCU_CORTEX],
    [
        AC_ARG_WITH([mcu_cortex],
            [AS_HELP_STRING([--with-mcu_cortex=@<:@m0|m4@:>@], [select mcu cortex about @<:@m0|m4@:>@ @<:@default=m4@:>@])],
            [],
            [with_mcu_cortex=m4])

        case "$with_mcu_cortex" in
            m0*)    M0_CFLAGS="-mcpu=cortex-m0 -mthumb -ffunction-sections -fdata-sections" 
                    AC_SUBST(M0_CFLAGS)
            ;;
            m4)     M4_CFLAGS="-mcpu=cortex-m4 -mthumb -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=hard"
                    AC_SUBST(M4_CFLAGS)
            ;;
            *)      AC_MSG_ERROR([bad value ${with_mcu_cortex} for --with-mcu_cortex=@<:@m0|m4@:>@]) ;;
        esac

        AM_CONDITIONAL([COMPILE_SELECT_MCU_CORTEX_M0],      [test "x$with_mcu_cortex" = "xm0"])
        AM_CONDITIONAL([COMPILE_SELECT_MCU_CORTEX_M4],      [test "x$with_mcu_cortex" = "xm4"])
    ])

