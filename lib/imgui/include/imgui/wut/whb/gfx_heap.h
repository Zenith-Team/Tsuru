#pragma once

#include <stdint.h>

void* GfxHeapAllocMEM2(uint32_t size,uint32_t alignment);
void GfxHeapFreeMEM2(void* block);
