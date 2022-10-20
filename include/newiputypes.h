#pragma once

#include <tamtypes.h>

namespace IPU
{
	namespace Options
	{
		namespace Registers
		{
			// Error code detected
			enum class ECD : u8
			{
				NotDetected = 0,
				Detected,
			};

			// Start code detected
			enum class SCD : u8
			{
				NotDetected = 0,
				Detected,
			};

			// Intra DC precision
			enum class IDP : u8
			{
				Eight = 0,
				Nine,
				Ten,
				Reserved,
			};

			// Alternate scan
			enum class AS : u8
			{
				Zigzag = 0,
				Alternate,
			};

			// Intra VLC format
			// MPEG1 -> MPEG1-compatible 2dimensional VLC table
			// INTRA_MACRO -> 2 dimensional VLC table for intra macro block
			enum class IVF : u8
			{
				MPEG1 = 0,
				INTRA_MACRO,
			};

			// Q scale step
			enum class QST : u8
			{
				Linear = 0,
				NonLinear,
			};

			// MPEG1 bit stream
			enum class MP1 : u8
			{
				MPEG2 = 0,
				MPEG1,
			};

			// Picture type
			enum class PCT : u8
			{
				Reserved = 0,
				IPICTURE,
				PPICTURE,
				BPICTURE,
				DPICTURE,
			};

			// Resets the IPU when set
			enum class RST : u8
			{
				NoReset = 0,
				Reset,
			};

			// Set to 1 when the IPU is busy (Processing command)
			enum class BUSY : u8
			{
				NotBusy = 0,
				Busy,
			};

			// The command code
			enum class CODE : u8
			{
				BCLR = 0,
				IDEC,
				BDEC,
				VDEC,
				FDEC,
				SETIQ,
				SETVQ,
				CSC,
				PACK,
				SETTH,
			};
		}; // namespace Registers

		namespace Commands
		{
			// DT Decode
			enum class DTD : u8
			{
				NoDecode = 0,
				DecodesDT
			};

			// Pseudo Sign Offset
			// AsIs -> Outputs RGB as it is
			// Decreasing -> Outputs RGB by decreasing by 128
			enum class SGN : u8
			{
				AsIs = 0,
				Decreasing
			};

			// Dither Enable
			// (Only used with RGB16 output format)
			enum class DTE : u8
			{
				NoDithering = 0,
				Dithering,
			};

			// Output format (IDEC and CSC)
			enum class OFM : u8
			{
				RGB32 = 0,
				RGB16,
			};

			// Output format (PACK)
			enum class OFM2 : u8
			{
				INDX4 = 0,
				RGB16
			};

			// DCT Type
			enum class DT : u8
			{
				Frame = 0,
				Field,
			};

			// DC Reset
			enum class DCR : u8
			{
				NoReset = 0,
				Reset,
			};

			// MacroBlock Intra
			enum class MBI : u8
			{
				NonIntra = 0,
				Intra
			};

			// VLC Table
			enum class TBL : u8
			{
				MacroBlockAddressIncrement = 0,
				MacroblockType,
				MotionCode,
				DMVector,
			};

			// Intra IQ Matrix
			enum class IQM : u8
			{
				Intra = 0,
				NonIntra,
			};
		} // namespace Commands
	} // namespace Options

	namespace Types
	{
		namespace Registers
		{
			union tIPU_CMD
			{
				struct // When writing
				{
					u32 option : 28;
					IPU::Options::Registers::CODE code : 4;
					u32 _pad1;
				};

				struct // When reading
				{
					u32 data;
					u32 _pad2 : 31;
					IPU::Options::Registers::BUSY busy : 1;
				};
				u64 _u64;
			};

			union tIPU_TOP
			{
				struct
				{
					u32 bstop;
					u32 _pad : 31;
					IPU::Options::Registers::BUSY busy : 1;
				};
				u64 _u64;
			};

			union tIPU_CTRL
			{
				struct
				{
					u8 ifc : 4;
					u8 ofc : 4;
					u8 cbp : 6;
					IPU::Options::Registers::ECD ecd : 1;
					IPU::Options::Registers::SCD scd : 1;
					IPU::Options::Registers::IDP idp : 2;
					u8 _pad1 : 2;
					IPU::Options::Registers::AS as : 1;
					IPU::Options::Registers::IVF ivf : 1;
					IPU::Options::Registers::QST qst : 1;
					IPU::Options::Registers::MP1 mp1 : 1;
					IPU::Options::Registers::PCT pct : 3;
					u8 _pad2 : 3;
					IPU::Options::Registers::RST rst : 1;
					IPU::Options::Registers::BUSY busy : 1;
				};
				u32 _u32;
			};

			union tIPU_BP
			{
				struct
				{
					u8 BP : 7;
					u8 _pad1 : 1;
					u8 IFC : 4;
					u8 _pad2 : 4;
					u8 FP : 2;
					u32 _pad3 : 17;
				};
				u32 _u32;
			};

		}; // namespace Registers

		namespace Commands
		{
			using namespace IPU::Options::Commands;

			union tIPU_BCLR
			{
				struct
				{
					u8 BP : 7;
					u32 _pad1 : 25;
				};
				u32 _u32;
			};

			union tIPU_IDEC
			{
				struct
				{
					u8 fb : 6;
					u32 _pad1 : 9;
					u8 qsc : 4;
					u8 _pad2 : 3;
					DTD dtd : 1;
					SGN sgn : 1;
					DTE dte : 1;
					OFM ofm : 1;
					u8 _cmd : 4;
				};
				u32 _u32;
			};

			union tIPU_BDEC
			{
				struct
				{
					u8 fb : 6;
					u32 _pad1 : 9;
					u8 qsc : 4;
					u8 _pad2 : 3;
					DT dt : 1;
					DCR dcr : 1;
					MBI mbi : 1;
					u8 _cmd : 4;
				};
				u32 _u32;
			};

			union tIPU_VDEC
			{
				struct
				{
					u8 fb : 6;
					u32 _pad1 : 19;
					u8 tbl : 2;
					u8 _cmd : 4;
				};
				u32 _u32;
			};

			union tIPU_FDEC
			{
				struct
				{
					u8 fb : 6;
					u32 _pad1 : 21;
					u8 _cmd : 4;
				};
				u32 _u32;
			};

			union tIPU_SETIQ
			{
				struct
				{
					u8 fb : 6;
					u32 _pad : 20;
					IQM iqm : 1;
					u8 _cmd : 4;
				};
				u32 _u32;
			};

			union tIPU_SETVQ
			{
				struct
				{
					u32 _pad1 : 28;
					u8 _cmd : 4;
				};
				u32 _u32;
			};

			union tIPU_CSC
			{
				struct
				{
					u16 mbc : 11;
					u16 _pad1 : 15;
					DTE dte : 1;
					OFM ofm : 1;
					u8 _cmd : 4;
				};
				u32 _u32;
			};

			union tIPU_PACK
			{
				struct
				{
					u16 mbc : 11;
					u16 _pad1 : 15;
					DTE dte : 1;
					OFM2 ofm : 1;
					u8 _cmd : 4;
				};
				u32 _u32;
			};

			union tIPU_SETTH
			{
				struct
				{
					u16 th0 : 9;
					u16 _pad1 : 7;
					u16 th1 : 9;
					u8 _pad2 : 3;
					u8 _cmd : 4;
				};
				u32 _u32;
			};
		}; // namespace Commands

		namespace Data
		{
			typedef u128 BS128;

			alignas(16) typedef union
			{
				struct
				{
					u8 R;
					u8 G;
					u8 B;
					u8 A;
				};
				u32 _u32;
			} RGBA32[16][16];

			alignas(16) typedef union
			{
				struct
				{
					u8 R : 5;
					u8 G : 5;
					u8 B : 5;
					u8 A : 1;
				};
				u16 _u16;
			} RGB16[16][16];

			struct alignas(16) MACROBLOCK8
			{
				u8 Y[16][16];
				u8 Cb[8][8];
				u8 Cr[8][8];
			};

			struct alignas(16) MACROBLOCK16
			{
				u16 Y[16][16];
				u16 Cb[8][8];
				u16 Cr[8][8];
			};

			// Unsure how to represent INDX4
		}; // namespace Data

		namespace DMA
		{
			struct IPUDMA
			{
				bool SPR;
				u32 MADR;
				u32 QWC;
			};

		} // namespace DMA
	} // namespace Types
} // namespace IPU
