# R(os) mini project

this is my toy os project made just for fun and learning purposes 

## video Preview

https://github.com/AlirezaRezaie/ros/assets/65468740/2e3e0af0-aeb5-4e30-ab51-1ce3505fee15

### < how to build >
```shell
make # (or make -B)
make run
```

## how to build gcc cross compiler 
<hr>

*first we need to know **1(what is a cross compiler)** and **2(why we need such a thing)**:*

1 - A cross compiler is a compiler capable of creating executable code for a platform other than the one on which the compiler is running.


2 - It is possible ask your compiler what target platform it is currently using by calling the command: 
```console
 gcc -dumpmachine
```

 If you are developing on 64-bit Linux, then you will get a response such as `x86_64-unknown-linux-gnu`. This means that the compiler thinks it is creating code for Linux. If you use this GCC to build your kernel, it will use your system libraries, headers, the Linux libgcc, and it will make a lot of problematic Linux assumptions. If you use a cross-compiler such as i686-elf-gcc, then you get a response back such as `i686-elf` that means the compiler knows it is doing something else and you can avoid a lot of problems easily and properly. 


how to make a gcc cross compiler (well it's hard)

first we intall dependencies:
```console
sudo apt install build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo libisl-dev
```

make a directory for binaries:
```console
mkdir cross/
```

and a directory for sources we download:
```console
mkdir src/
```
and two directories for builds:
```console
mkdir binutils-build gcc-build
```

cd to sources folder to download the source files:
```console
cd src/
```

then we download binutils and gcc source (from official gnu mirrors [WEBSITE](https://ftp.gnu.org/gnu/)): <br>


### http://ftp.gnu.org/gnu/binutils/binutils-x.y.z.tar.gz
tar xf binutils-x.y.z.tar.gz


### https://ftp.gnu.org/gnu/gcc/gcc-10.2.0/gcc-x.y.z.tar.gz
tar xf gcc-x.y.z.tar.gz


#### directory tree looks like this:
* src/ <br>
    gcc-build/ <br>
    binutils-build/ <br>

<br>

### build(GCC):

```console
cd gcc-build
../gcc-12.2.0/contrib/download_prerequisites

../gcc-12.2.0/configure --target="i686-elf" --prefix="$HOME/cross" --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc
```

<br>

### build(BINUTILS):

```console
../binutils-2.39/configure --target="i686-elf" --prefix="$HOME/cross" --with-sysroot --disable-nls --disable-werror
cd binutils-build
make 
make install
```

### done -_-
**now you should have your cross compiler and linker inside cross/bin :)**


## How Linker Scripts Work!!!
<hr>

```c
SECTIONS
{

    . = 0x10000;

    .text : { *(.text) }

    . = 0x8000000;

    .data : { *(.data) }

    .bss : { *(.bss) }

}
```

You write the ` SECTIONS ` command as the keyword ` SECTIONS `, followed by a series of symbol assignments and output section descriptions enclosed in curly braces. The first line in the above example sets the special symbol ` . `, which is the location counter. If you do not specify the address of an output section in some other way (other ways are described later), the address is set from the current value of the location counter. The location counter is then incremented by the size of the output section. The second line defines an output section, ` .text `. The colon is required syntax, which may be ignored for now. Within the curly braces after the output section name, you list the names of the input sections, which should be placed into this output section. The ` * ` is a wildcard which matches any file name. The expression ` *(.text) ` means all ` .text ` input sections in all input files.
Since the location counter is ` 0x10000 ` when the output section ` .text ` is defined, the linker will set the address of the ` .text ` section in the output file to be ` 0x10000 `. The remaining lines define the ` .data ` and ` .bss ` sections in the output file. The ` .data ` output section will be at address ` 0x8000000 `. When the ` .bss ` output section is defined, the value of the location counter will be ` 0x8000000 ` plus the size of the ` .data ` output section. The effect is that the ` .bss ` output section will follow immediately after the ` .data ` output section in memory.
That's it! That's a simple and complete linker script. ([source](https://users.informatik.haw-hamburg.de/~krabat/FH-Labor/gnupro/5_GNUPro_Utilities/c_Using_LD/ldLinker_scripts.html#example)) 


## useful links

<hr>

[ CS crash course youtube ]

https://youtube.com/playlist?list=PL8dPuuaLjXtNlUrzyH5r6jN9ulIgZBpdo


[operating system videos]

https://youtu.be/9GDX-IyZ_C8 <br>
https://www.youtube.com/playlist?list=PLEJxKK7AcSEGPOCFtQTJhOElU44J_JAun <br>
https://www.youtube.com/playlist?list=PLBlnK6fEyqRiVhbXDGLXDk_OQAeuVcp2O

*[ how cpu works (very good videos should be watched multiple times!) ]*<br>
|fetch-decode-execute cycle|

https://youtu.be/cNN_tTXABUA<br>
https://youtu.be/Z5JC9Ve1sfI


Refrence website ==> https://wiki.osdev.org


[ os dev playlists ] <br>
1 - https://www.youtube.com/playlist?list=PLm3B56ql_akNcvH8vvJRYOc7TbYhRs19M ( Daedalus Community )<br>
2 - https://www.youtube.com/playlist?list=PLFjM7v6KGMpiH2G-kT781ByCNC_0pKpPN ( nanobyte )<br>
3 - https://www.youtube.com/playlist?list=PLHh55M_Kq4OApWScZyPl5HhgsTJS9MZ6M ( Write your own Operating System )<br>

why protected mode =>
https://stackoverflow.com/questions/48743371/why-do-we-need-to-enter-32-bit-protected-mode-anyway

[ good channels ]
* https://www.youtube.com/channel/UCKS34cSMNaXaySe2xgXH-3A 
* https://www.youtube.com/watch?v=Z5JC9Ve1sfI
