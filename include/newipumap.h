#pragma once
#include "newiputypes.h"

namespace IPU
{
	namespace IO
	{
		using namespace IPU::Types::Registers;

		volatile tIPU_CMD* const IPU_CMD = (volatile tIPU_CMD* const)0x10002000;
		volatile tIPU_CTRL* const IPU_CTRL = (volatile tIPU_CTRL* const)0x10002010;
		volatile tIPU_BP* const IPU_BP = (volatile tIPU_BP* const)0x10002020;
		volatile tIPU_TOP* const IPU_TOP = (volatile tIPU_TOP* const)0x10002030;

		volatile u32* const IPU0CHCR = (volatile u32* const)0x1000B000;
		volatile u32* const IPU0MADR = (volatile u32* const)0x1000B010;
		volatile u32* const IPU0QWC = (volatile u32* const)0x1000B020;
		volatile u32* const IPU0TADR = (volatile u32* const)0x1000B030;
		volatile u32* const IPU0ASR0 = (volatile u32* const)0x1000B040;
		volatile u32* const IPU0ASR1 = (volatile u32* const)0x1000B050;
		volatile u32* const IPU1CHCR = (volatile u32* const)0x1000B400;
		volatile u32* const IPU1MADR = (volatile u32* const)0x1000B410;
		volatile u32* const IPU1QWC = (volatile u32* const)0x1000B420;
		volatile u32* const IPU1TADR = (volatile u32* const)0x1000B430;
		volatile u32* const IPU1ASR0 = (volatile u32* const)0x1000B440;
		volatile u32* const IPU1ASR1 = (volatile u32* const)0x1000B450;
	} // namespace IO
} // namespace IPU
