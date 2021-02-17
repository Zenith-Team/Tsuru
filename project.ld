
MEMORY 
{
    codearea : origin = 0x2b01360, length = 0xd4feca0
    dataarea : origin = 0x10607d00, length = 0xaf9f8300
}

OPTION("-append")

SECTIONS 
{
    .text : > codearea
    .rodata : > dataarea
    .data : > dataarea
    .bss : > dataarea
}