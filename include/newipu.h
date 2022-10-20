#pragma once
#include "newiputypes.h"
#include "newipumap.h"

#include <sio.h>
#include <cstdarg>
#include <cstdio>

#define TOGGLE_DEBUG false

#define IPU_DEBUG TOGGLE_DEBUG && newipu_debugPrintf

void ipuInit();
void ipuReset();
void ipuBCLR(u8 BP);
bool ipuIsBusy();
bool ipuHasError();

// Set the IPU0/1 DMA channel settings
// Passing nullptr for IPU_FROM or IPU_TO will leave their respective channels alone
void ipuSetDMA(IPU::Types::DMA::IPUDMA* IPU_FROM, IPU::Types::DMA::IPUDMA* IPU_TO);

// Set the IPU0/1 DMA QWC setting
// This is if you want to keep MADR the same, but increase the QWC
// Passing nullptr for IPU_FROM or IPU_TO will leave their respective channels alone
void ipuSetDMAQWC(IPU::Types::DMA::IPUDMA* IPU_FROM, IPU::Types::DMA::IPUDMA* IPU_TO);

// Runs a CSC command for mb_count macroblocks
void ipuCSC(IPU::Options::Commands::DTE dte, IPU::Options::Commands::OFM ofm, u16 mb_count);

void ipuSETTH(u32 TH0, u32 TH1);

// Returns true on successful wait
// false if timed out.
bool ipuWait(u32 timeout);

int newipu_debugPrintf(const char* fmt, ...);
