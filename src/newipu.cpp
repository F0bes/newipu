#include "git.h"
#include "newipu.h"

int newipu_debugPrintf(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	char str[256];
	std::vsnprintf(str, sizeof(str), fmt, args);


	char final_str[512];
	std::snprintf(final_str, sizeof(final_str), "DEBUG_IPU -> %s", str);

	return puts(final_str);
	//	sio_puts(final_str, args);
}

using namespace IPU::Options;

// Reset IPU and clear IPU FIFO
void ipuInit()
{
	newipu_debugPrintf("ipuInit, commit / tag: %s\n", GIT_VERSION);
	ipuReset();
}

void ipuReset()
{
	IPU_DEBUG("ipuReset\n");
	IPU::IO::IPU_CTRL->rst = Registers::RST::Reset;
	ipuBCLR(0);
}

void ipuBCLR(u8 BP)
{
	IPU_DEBUG("ipuBCLR with BP %d\n", BP);
	IPU::IO::IPU_CMD->_u64 = (BP & 0x7F);
}

bool ipuIsBusy()
{
	return IPU::IO::IPU_CTRL->busy == Registers::BUSY::Busy;
}

bool ipuHasError()
{
	return IPU::IO::IPU_CTRL->ecd == Registers::ECD::Detected;
}

bool ipuWait(u32 timeout)
{
	IPU_DEBUG("ipuWait with timeout %d\n", timeout);
	bool do_timeout = timeout != 0;
	do
	{
		if (do_timeout)
		{
			timeout--;
			if (!timeout)
				break;
		}

	} while (IPU::IO::IPU_CTRL->busy == Registers::BUSY::Busy);

	if (!timeout && do_timeout)
	{
		IPU_DEBUG("Timed out waiting on the IPU\n");
		return false;
	}
	return true;
}

void ipuSetDMA(IPU::Types::DMA::IPUDMA* IPU_FROM, IPU::Types::DMA::IPUDMA* IPU_TO)
{
	IPU_DEBUG("ipuSetDMA\n");
	if (IPU_FROM != nullptr)
	{
		IPU_DEBUG("IPU0\n MADR -> 0x%08X\n QWC -> 0x%04X", IPU_FROM->MADR, IPU_FROM->QWC);
		if (IPU_FROM->MADR & 0xF)
			IPU_DEBUG("Warning. IPU_FROM MADR is unaligned\n");

		*IPU::IO::IPU0MADR = (IPU_FROM->MADR & ~(1 << 31)) | (IPU_FROM->SPR << 31);

		*IPU::IO::IPU0QWC = IPU_FROM->QWC & 0xFFFF;
	}

	if (IPU_TO != nullptr)
	{
		IPU_DEBUG("IPU1\n MADR -> 0x%08X\n QWC -> 0x%04X", IPU_TO->MADR, IPU_TO->QWC);
		if (IPU_TO->MADR & 0xF)
			IPU_DEBUG("Warning. IPU_TO MADR is unaligned\n");

		*IPU::IO::IPU1MADR = (IPU_TO->MADR & ~(1 << 31)) | (IPU_TO->SPR << 31);

		*IPU::IO::IPU1QWC = IPU_TO->QWC & 0xFFFF;
	}
}

void ipuSetDMAQWC(IPU::Types::DMA::IPUDMA* IPU_FROM, IPU::Types::DMA::IPUDMA* IPU_TO)
{
	IPU_DEBUG("ipuSetDMAQWC\n");
	if (IPU_FROM != nullptr)
	{
		IPU_DEBUG("IPU0\n QWC -> 0x%04X", IPU_FROM->QWC);
		*IPU::IO::IPU0QWC = IPU_FROM->QWC & 0xFFFF;
	}

	if (IPU_TO != nullptr)
	{
		IPU_DEBUG("IPU1\n QWC -> 0x%04X", IPU_TO->QWC);
		*IPU::IO::IPU1QWC = IPU_TO->QWC & 0xFFFF;
	}
}

void ipuCSC(IPU::Options::Commands::DTE dte, IPU::Options::Commands::OFM ofm, u16 mb_count)
{
	IPU_DEBUG("ipuCSC called. dithering:%s output:%s macroblocks:%d\n",
		dte == IPU::Options::Commands::DTE::Dithering ? "yes" : "no",
		ofm == IPU::Options::Commands::OFM::RGB32 ? "RGB32" : "RGB16",
		mb_count);
	// Wait for any pending IPU work
	ipuWait(10010);

	// Start up IPU0 to take from the output fifo
	*IPU::IO::IPU0CHCR = 0x100;

	// Start up IPU1 to put into the input fifo
	*IPU::IO::IPU1CHCR = 0x100;

	if (mb_count > 0x7FF)
		IPU_DEBUG("Macroblock count is overflowing (value:%03X,max:%03X)\n", mb_count, 0x7FF);

	IPU::Types::Commands::tIPU_CSC csc_command;
	csc_command.dte = dte;
	csc_command.ofm = ofm;
	csc_command.mbc = mb_count & 0x7FF;

	IPU::IO::IPU_CMD->_u64 = csc_command._u32 | (7 << 28);
}

void ipuSETTH(u32 TH0, u32 TH1)
{
	IPU_DEBUG("ipuSETTH called. TH0 %04X TH1 %04X\n", TH0, TH1);

	ipuWait(10010);

	IPU::Types::Commands::tIPU_SETTH setth_command;
	setth_command.th0 = TH0;
	setth_command.th1 = TH1;

	IPU::IO::IPU_CMD->_u64 = setth_command._u32 | (9 << 28);
}
