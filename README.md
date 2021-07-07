# README

## 依赖

* `autotools`
* `java`
* `doxygen`
* `graphviz`

> 安装方法，详见[README.md](https://github.com/gnsyxiang/autotools_demo_lib/blob/main/README.md)

## 使用说明

* 执行`./autogen.sh`，生成`configure`脚本

* 三部曲编译源码并生成对应文件

```shell
$ ./configure CC=xxxx --enable-at32f407vgt7
$ make
$ make install
```

> note:
> 1, 需要设置交叉编译工具链，不能在pc机器上编译
>
> 2, 需要指定特定的mcu型号


详见`build.sh`


## 配置相关选项

* `--prefix=PREFIX`: 指定安装路径

* `--enable-doxygen-doc`: 生成html帮助文档

* `--enable-at32f407vgt7`: 选择`at32f407vgt7`，默认为关闭

