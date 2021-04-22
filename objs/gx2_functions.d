objs\gx2_functions.o: source/dynamic_libs/gx2_functions.cpp \
 ../files/include/dynamic_libs/os_functions.h \
 ../files/include/dynamic_libs/os_types.h \
 G:\Zenith\hacks\ghs\multi5327\ansi\stdio.h \
 G:\Zenith\hacks\ghs\multi5327\ansi\ghs_null.h \
 G:\Zenith\hacks\ghs\multi5327\ansi\stdarg.h \
 G:\Zenith\hacks\ghs\multi5327\ansi\ghs_valist.h \
 G:\Zenith\hacks\ghs\multi5327\ansi\stdlib.h \
 G:\Zenith\hacks\ghs\multi5327\ansi\ghs_wchar.h \
 G:\Zenith\hacks\ghs\multi5327\ansi\stdbool.h \
 G:\Zenith\hacks\ghs\multi5327\ansi\stdint.h \
 ../files/include/dynamic_libs/os_defs.h \
 ../files/include/dynamic_libs/gx2_types.h

:cmdList=cxppc  -c  -MD -I../files/include -bsp generic -cpu=espresso -object_dir=objs -Ospeed --g++ --no_debug --no_rtti -Omemfuncs -Ostrfuncs -DCemu -DREGION_NSMBU_US_Latest_Cemu -DCODE_ADDR=0x2b01360 -DDATA_ADDR=0x10607d00 -filetype.cc source/dynamic_libs/gx2_functions.cpp -o objs\gx2_functions.o ; 
:cmdHash=0x87190065
