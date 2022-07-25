# gdb-msvc

This is a fork of https://github.com/lesderid/gdb-msvc. Basically it hosts patches for GDB that consumes PDB debug symbols.  The purpose is to enable GDB supporting source level debugging for executables that compiled by MSVC and LLVM compilers on Windows.

## NOTES

It introduce dependencies on 
1. Radare2
2. llvm

## Building

* `mkdir build && cd build`
* `../configure --target=i686-w64-mingw32 --host=i686-w64-mingw32 <other configure flags>`
* `make` (and `make install`)

## Tips
1. [mingw cross compile](https://stackoverflow.com/questions/15986715/how-do-i-invoke-the-mingw-cross-compiler-on-linux)
it could utilize mingw on Linux that generate executable for windows
2. some LLVM CXXflags will have '-fno-exceptions' which conflict with gdb/ada-lang.c compilation (it requires exception support)
   workaround to change it to '-fexceptions'
  > llvm-config --cxxflags  
   -I/usr/lib/llvm-14/include -std=c++14   -fno-exceptions -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS
   

## License

Most of the code is available under the terms of the [GNU GPLv3 license](/gdb/COPYING). See [the original README](/README-GDB) and license notices in source files for details.

By contributing you agree to make your code available under the same license.
