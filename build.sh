#!/usr/bin/env bash

# set -x

help_info()
{
    echo "eg: ./build.sh mcu [_build]"
    exit
}

if [ $# -gt 2 -o $# -lt 1 ]; then
    help_info
fi

data_disk_path=/opt/data

if [ x$1 = x"mcu" ]; then
    vender=gnu_arm_embedded
    host=arm-none-eabi
    gcc_version=gcc-arm-none-eabi-5_4-2016q3
    gcc_prefix=arm-none-eabi
    cross_gcc_path=${data_disk_path}/opt/toolchains/${vender}/${gcc_version}/bin/${gcc_prefix}-
    _ldflag_com="-specs=nano.specs -specs=nosys.specs"

    # -----------
    # 华大芯片
    # -----------
    #
    # M0/M0+系列
    #
    # _cppflags_com=""
    # _cflags_com="-mcpu=cortex-m0 -mthumb"
    # _param_com="--with-mcu=hc32l13x"
    # _param_com="--with-mcu=hc32f003"

    # -----------
    # 雅特力
    # -----------
    #
    # M4系列
    #
    _cppflags_com="-DAT32F407VGT7 -DAT_START_F407_V1_0 -DUSE_STDPERIPH_DRIVER -DSYSCLK_FREQ_240MHz=240000000"
    _cflags_com="-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard"
    _param_com="--with-mcu=at32f4xx"
else
    help_info
fi

# 3rd_lib path
lib_3rd_path=${data_disk_path}/install/${vender}/${gcc_version}

# target
target_path=`pwd`
prefix_path=${lib_3rd_path}

cd ${target_path} && ./autogen.sh ${cross_gcc_path} && cd - >/dev/null 2>&1

if [ $# = 2 ]; then
    mkdir -p $2/${vender}
    cd $2/${vender}
fi

${target_path}/configure                                    \
    CC=${cross_gcc_path}gcc                                 \
    CXX=${cross_gcc_path}g++                                \
    CPPFLAGS="-I${lib_3rd_path}/include ${_cppflags_com}"   \
    CFLAGS="${_cflags_com}"                                 \
    CXXFLAGS=""                                             \
    LDFLAGS="-L${lib_3rd_path}/lib ${_ldflag_com}"          \
    LIBS=""                                                 \
    PKG_CONFIG_PATH="${lib_3rd_path}/lib/pkgconfig"         \
    --prefix=${prefix_path}                                 \
    --build=                                                \
    --host=${host}                                          \
    --target=${host}                                        \
    \
    ${_param_com}


thread_jobs=`getconf _NPROCESSORS_ONLN 2>/dev/null || echo 1`

make -j${thread_jobs}; make install

