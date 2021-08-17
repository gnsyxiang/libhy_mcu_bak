# ===============================================================
# 
# Release under GPLv-3.0.
# 
# @file    Makefile.am
# @brief   
# @author  gnsyxiang <gnsyxiang@163.com>
# @date    05/03 2021 10:32
# @version v0.0.1
# 
# @since    note
# @note     note
# 
#     change log:
#     NO.     Author              Date            Modified
#     00      zhenquan.qiu        05/03 2021      create the file
# 
#     last modified: 05/03 2021 10:32
# ===============================================================

include res/doxygen.am

SUBDIRS = \
          include \
          src \
          example \
          doc \
          res

# ------------------
# defining variables
# ------------------
_no_error_com       =
_remove_unuse_func  =
_install_files_com  =
_dist_files_com     =

CPPFLAGS_COM        =
CFLAGS_COM          =
CXXFLAGS_COM        =
LIB_LDFLAGS_COM     =
BIN_LDFLAGS_COM     =

ACLOCAL_AMFLAGS     = -I m4
pkgconfigdir        = $(libdir)/pkgconfig

# ---------------------
# add necessary content
# ---------------------
_no_error_com       += \
                       -W -Wall -Werror \
                       -Wno-error=unused-but-set-variable \
                       -Wno-error=unused-variable \
                       -Wno-error=unused-function \
                       -Wno-error=unused-parameter

CPPFLAGS_COM        += \
                       -pipe \
                       $(_no_error_com) \
                       $(ACLOCAL_AMFLAGS)

LIB_LDFLAGS_COM     += -rdynamic

_remove_unuse_func  += \
                       -ffunction-sections \
                       -fdata-sections
CFLAGS_COM          += $(_remove_unuse_func)
CXXFLAGS_COM        += $(_remove_unuse_func)
BIN_LDFLAGS_COM     += -Wl,--gc-sections

if COMPILE_SELECT_MCU_CORTEX_M0
CFLAGS_COM          += $(M0_CFLAGS)
endif

if COMPILE_SELECT_MCU_CORTEX_M4
CFLAGS_COM          += $(M4_CFLAGS)

if COMPILE_MCU_AT32F407VGT7
CPPFLAGS_COM    += -DSYSCLK_FREQ_200MHz=200000000
# CPPFLAGS_COM    += -DSYSCLK_FREQ_240MHz=240000000
CFLAGS_COM      += $(AT32F407VGT7_CFLAGS)
endif

endif

if COMPILE_LIBPROTOBUF_C
CPPFLAGS_COM        += $(LIBPROTOBUF_C_INCS)
endif

if COMPILE_LIBHY_UTILS
CPPFLAGS_COM        += $(HY_UTILS_INCS)
endif

export CPPFLAGS_COM
export CFLAGS_COM
export CXXFLAGS_COM
export LIB_LDFLAGS_COM
export BIN_LDFLAGS_COM

# ------------------
# make install files
# ------------------
_install_files_com  += \
                       LICENSE \
                       README.md
dist_doc_DATA       = $(_install_files_com)
pkgconfig_DATA      = @project_name@.pc

# ---------------
# make dist files
# ---------------
_dist_files_com     += \
                       autogen.sh \
                       build.sh \
                       @project_name@.pc.in
EXTRA_DIST          = $(_dist_files_com)

DISTCLEANFILES      = @project_name@.pc

