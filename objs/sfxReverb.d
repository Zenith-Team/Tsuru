objs\sfxReverb.o: source/sfxReverb.cpp ../files/include/sound.h \
 ../files/include/nw/snd.h ../files/include/types.h

:cmdList=cxppc  -c  -MD -I../files/include -bsp generic -cpu=espresso -object_dir=objs -Ospeed --g++ --no_debug --no_rtti -Omemfuncs -Ostrfuncs -DCemu -DREGION_NSMBU_US_Latest_Cemu -DCODE_ADDR=0x2b01360 -DDATA_ADDR=0x10607d00 -filetype.cc source/sfxReverb.cpp -o objs\sfxReverb.o ; 
:cmdHash=0x5b086b55
