/*
**	Command & Conquer Generals(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : wwlib                                                        *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/wwlib/cpudetect.h                            $*
 *                                                                                             *
 *              Original Author:: Jani Penttinen                                               *
 *                                                                                             *
 *                      $Author:: Jani_p                                                      $*
 *                                                                                             *
 *                     $Modtime:: 3/29/02 4:09p                                               $*
 *                                                                                             *
 *                    $Revision:: 11                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef WWLIB_CPU_DETECT_H__
#define WWLIB_CPU_DETECT_H__

#include "WWLib/always.h"
#include "WWLib/wwstring.h"

#ifdef WIN32
typedef signed __int64 sint64;
#elif defined (_UNIX)
typedef signed long long sint64;
#endif

class CPUDetectInitClass;

class CPUDetectClass
{
public:
	typedef enum
	{
		MANUFACTURER_UNKNOWN = 0,
		MANUFACTURER_INTEL,		// alive
		MANUFACTURER_UMC,		// dead 
		MANUFACTURER_AMD,		// alive 
		MANUFACTURER_CYRIX,		// dead 
		MANUFACTURER_NEXTGEN,	// dead 
		MANUFACTURER_VIA,		// dead 
		MANUFACTURER_RISE,		// dead
		MANUFACTURER_TRANSMETA	// dead 
	} ProcessorManufacturerType;

	typedef enum
	{
		INTEL_PROCESSOR_UNKNOWN,
		INTEL_PROCESSOR_80386,
		INTEL_PROCESSOR_80486DX,
		INTEL_PROCESSOR_80486SX,
		INTEL_PROCESSOR_80486DX2,
		INTEL_PROCESSOR_80486SL,
		INTEL_PROCESSOR_80486SX2,
		INTEL_PROCESSOR_80486DX2_WB,
		INTEL_PROCESSOR_80486DX4,
		INTEL_PROCESSOR_80486DX4_WB,
		INTEL_PROCESSOR_PENTIUM,
		INTEL_PROCESSOR_PENTIUM_OVERDRIVE,
		INTEL_PROCESSOR_PENTIUM_MMX,
		INTEL_PROCESSOR_PENTIUM_PRO_SAMPLE,
		INTEL_PROCESSOR_PENTIUM_PRO,
		INTEL_PROCESSOR_PENTIUM_II_OVERDRIVE,
		INTEL_PROCESSOR_PENTIUM_II_MODEL_3,
		INTEL_PROCESSOR_PENTIUM_II_MODEL_4,
		INTEL_PROCESSOR_CELERON_MODEL_5,
		INTEL_PROCESSOR_PENTIUM_II_MODEL_5,
		INTEL_PROCESSOR_PENTIUM_II_XEON_MODEL_5,
		INTEL_PROCESSOR_CELERON_MODEL_6,
		INTEL_PROCESSOR_PENTIUM_III_MODEL_7,
		INTEL_PROCESSOR_PENTIUM_III_XEON_MODEL_7,
		INTEL_PROCESSOR_CELERON_MODEL_8,
		INTEL_PROCESSOR_PENTIUM_III_MODEL_8,
		INTEL_PROCESSOR_PENTIUM_III_XEON_MODEL_8,
		INTEL_PROCESSOR_PENTIUM_III_XEON_MODEL_A,
		INTEL_PROCESSOR_PENTIUM_III_MODEL_B,
		INTEL_PROCESSOR_PENTIUM4
	} IntelProcessorType;

	typedef enum
	{
		AMD_PROCESSOR_UNKNOWN,
		AMD_PROCESSOR_486DX2,
		AMD_PROCESSOR_486DX4,
		AMD_PROCESSOR_5x86,
		AMD_PROCESSOR_486,
		AMD_PROCESSOR_K5_MODEL0,
		AMD_PROCESSOR_K5_MODEL1,
		AMD_PROCESSOR_K5_MODEL2,
		AMD_PROCESSOR_K5_MODEL3,
		AMD_PROCESSOR_K6_MODEL6,
		AMD_PROCESSOR_K6_MODEL7,
		AMD_PROCESSOR_K6_2_3DNOW_MODEL8,
		AMD_PROCESSOR_K6_3_3DNOW_MODEL9,
		AMD_PROCESSOR_K6_3_PLUS,
		AMD_PROCESSOR_K6,
		AMD_PROCESSOR_ATHLON_025,
		AMD_PROCESSOR_ATHLON_018,
		AMD_PROCESSOR_DURON,
		AMD_PROCESSOR_ATHLON_018_IL2,
		AMD_PROCESSOR_ATHLON
	} AMDProcessorType;

	typedef enum
	{
		VIA_PROCESSOR_UNKNOWN,
		VIA_PROCESSOR_IDT_C6_WINCHIP,
		VIA_PROCESSOR_IDT_C6_WINCHIP2,
		VIA_PROCESSOR_IDT_C6_WINCHIP3,
		VIA_PROCESSOR_CYRIX_III_SAMUEL
	} VIAProcessorType;

	typedef enum
	{
		RISE_PROCESSOR_UNKNOWN,
		RISE_PROCESSOR_DRAGON_025,
		RISE_PROCESSOR_DRAGON_018,
		RISE_PROCESSOR_DRAGON2_025,
		RISE_PROCESSOR_DRAGON2_018
	} RiseProcessorType;

	inline static ProcessorManufacturerType Get_Processor_Manufacturer() {return ProcessorManufacturer;}
	static const char* Get_Processor_Manufacturer_Name();

	inline static bool Has_CPUID_Instruction( void ) { return HasCPUIDInstruction; }
	inline static bool Has_RDTSC_Instruction( void ) { return HasRDTSCInstruction; }
	inline static bool Has_CMOV_Instruction( void ) { return HasCMOVSupport; }
	inline static bool Has_MMX_Instruction_Set( void ) { return HasMMXSupport; }
	inline static bool Has_SSE_Instruction_Set( void ) { return HasSSESupport; }
	inline static bool Has_SSE2_Instruction_Set( void ) { return HasSSE2Support; }
	inline static bool Has_3DNow_Instruction_Set( void ) { return Has3DNowSupport; }
	inline static bool Has_Extended_3DNow_Instruction_Set( void ) { return HasExtended3DNowSupport; }

	// Call these functions after determining the manufacturer to find out which of the manufacturers processors
	// the system has.
	inline static IntelProcessorType Get_Intel_Processor( void ) { return IntelProcessor; }
	inline static AMDProcessorType Get_AMD_Processor( void ) { return AMDProcessor; }
	inline static VIAProcessorType Get_VIA_Processor( void ) { return VIAProcessor; }
	inline static RiseProcessorType Get_Rise_Processor( void ) { return RiseProcessor; }

	// Note that processor speed is only calculated at start and could change during execution, so
	// this number is not to be relied on!
	inline static int 		Get_Processor_Speed( void ) { return ProcessorSpeed; }
	inline static uint64_t	Get_Processor_Ticks_Per_Second( void ) { return ProcessorTicksPerSecond; }	// Ticks per second
	inline static double	Get_Inv_Processor_Ticks_Per_Second( void ) { return InvProcessorTicksPerSecond; }	// 1.0 / Ticks per second

	static uint32_t Get_Feature_Bits( void ) { return FeatureBits; }
	static uint32_t Get_Extended_Feature_Bits( void ) { return ExtendedFeatureBits; }

	// L2 cache
	static uint32_t Get_L2_Cache_Size( void ) { return L2CacheSize; }
	static uint32_t Get_L2_Cache_Line_Size( void ) { return L2CacheLineSize; }
	static uint32_t Get_L2_Cache_Set_Associative( void ) { return L2CacheSetAssociative; }

	// L1 data cache
	static uint32_t Get_L1_Data_Cache_Size( void ) { return L1DataCacheSize; }
	static uint32_t Get_L1_Data_Cache_Line_Size( void ) { return L1DataCacheLineSize; }
	static uint32_t Get_L1_Data_Cache_Set_Associative( void ) { return L1DataCacheSetAssociative; }

	// L1 instruction cache
	static uint32_t Get_L1_Instruction_Cache_Size( void ) { return L1InstructionCacheSize; }
	static uint32_t Get_L1_Instruction_Cache_Line_Size( void ) { return L1InstructionCacheLineSize; }
	static uint32_t Get_L1_Instruction_Cache_Set_Associative( void ) { return L1InstructionCacheSetAssociative; }

	// L1 instruction trace cache
	static uint32_t Get_L1_Instruction_Trace_Cache_Size( void ) { return L1InstructionTraceCacheSize; }
	static uint32_t Get_L1_Instruction_Trace_Cache_Set_Associative( void ) { return L1InstructionTraceCacheSetAssociative; }

	// System memory
	static uint32_t Get_Total_Physical_Memory( void ) { return TotalPhysicalMemory; }
	static uint32_t Get_Available_Physical_Memory( void ) { return AvailablePhysicalMemory; }
	static uint32_t Get_Total_Page_File_Size( void ) { return TotalPageMemory; }
	static uint32_t Get_Available_Page_File_Size( void ) { return AvailablePageMemory; }
	static uint32_t Get_Total_Virtual_Memory( void ) { return TotalVirtualMemory; }
	static uint32_t Get_Available_Virtual_Memory( void ) { return AvailableVirtualMemory; }

	static uint32_t Get_Processor_Type( void ) { return ProcessorType; }

	inline static const char* Get_Processor_String( void ) { return ProcessorString; }
	inline static const StringClass& Get_Processor_Log( void ) { return ProcessorLog; }
	inline static const StringClass& Get_Compact_Log( void ) { return CompactLog; }

	static bool CPUID( uint32_t& u_eax_, uint32_t& u_ebx_, uint32_t& u_ecx_, uint32_t& u_edx_, uint32_t cpuid_type );

private:
//	static void Detect_CPU_Type();
	static void Init_CPUID_Instruction( void );
	static void Init_Processor_Speed( void );
	static void Init_Processor_String( void );
	static void Init_Processor_Manufacturer( void );
	static void Init_Processor_Family( void );
	static void Init_Processor_Features( void );
	static void Init_Memory( void );
	static void Init_OS( void );

	static void Init_Intel_Processor_Type( void );
	static void Init_AMD_Processor_Type( void );
	static void Init_VIA_Processor_Type( void );
	static void Init_Rise_Processor_Type( void );

	static void Init_Cache( void );

	static void Init_Processor_Log( void );
	static void Init_Compact_Log( void );

	static void Process_Cache_Info( uint32_t value );
	static void Process_Extended_Cache_Info( void );

	friend class CPUDetectInitClass;

	static StringClass ProcessorLog;
	static StringClass CompactLog;

	static uint32_t	ProcessorType;
	static uint32_t	ProcessorFamily;
	static uint32_t	ProcessorModel;
	static uint32_t	ProcessorRevision;
	static uint32_t	ProcessorSpeed;
	static uint64_t	ProcessorTicksPerSecond;	// Ticks per second
	static double 	InvProcessorTicksPerSecond;	// 1.0 / Ticks per second

	static ProcessorManufacturerType	ProcessorManufacturer;
	static IntelProcessorType			IntelProcessor;
	static AMDProcessorType				AMDProcessor;
	static VIAProcessorType				VIAProcessor;
	static RiseProcessorType			RiseProcessor;

	static uint32_t						FeatureBits;
	static uint32_t						ExtendedFeatureBits;

	// L2 cache information
	static uint32_t						L2CacheSize;
	static uint32_t						L2CacheLineSize;
	static uint32_t						L2CacheSetAssociative;

	// L1 data cache information
	static uint32_t						L1DataCacheSize;
	static uint32_t						L1DataCacheLineSize;
	static uint32_t						L1DataCacheSetAssociative;

	// L1 instruction cache information
	static uint32_t						L1InstructionCacheSize;
	static uint32_t						L1InstructionCacheLineSize;
	static uint32_t						L1InstructionCacheSetAssociative;

	// L1 instruction trace cache information
	static uint32_t						L1InstructionTraceCacheSize;
	static uint32_t						L1InstructionTraceCacheSetAssociative;

	static uint32_t						TotalPhysicalMemory;
	static uint32_t						AvailablePhysicalMemory;
	static uint32_t						TotalPageMemory;
	static uint32_t						AvailablePageMemory;
	static uint32_t						TotalVirtualMemory;
	static uint32_t						AvailableVirtualMemory;

	static uint32_t						OSVersionNumberMajor;
	static uint32_t						OSVersionNumberMinor;
	static uint32_t						OSVersionBuildNumber;
	static uint32_t						OSVersionPlatformId;
	static StringClass 					OSVersionExtraInfo;

	static bool 						HasCPUIDInstruction;
	static bool 						HasRDTSCInstruction;
	static bool 						HasSSESupport;
	static bool 						HasSSE2Support;
	static bool 						HasCMOVSupport;
	static bool 						HasMMXSupport;
	static bool 						Has3DNowSupport;
	static bool 						HasExtended3DNowSupport;
	static char 						VendorID[20];
	static char 						ProcessorString[48];

};

struct CPUIDStruct
{
	uint32_t Eax;
	uint32_t Ebx;
	uint32_t Ecx;
	uint32_t Edx;
	CPUIDStruct( uint32_t cpuid_type )
	{
		if ( !CPUDetectClass::Has_CPUID_Instruction() ) 
		{
			Eax = Ebx = Ecx = Edx = 0;
			return;
		}

		CPUDetectClass::CPUID(Eax,Ebx,Ecx,Edx,cpuid_type);
	}
};

#endif // WWLIB_CPU_DETECT_H__
