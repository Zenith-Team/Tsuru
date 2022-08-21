MEMORY {
	text : origin = 0x2B01360, length = 0xD4FECA0
	data : origin = 0x10607D00, length = 0xAF9F8300
}

OPTION("-append")

SECTIONS {
	.text   : > text
	.rodata : > data
	.data   : > data
	.bss    : > data
}