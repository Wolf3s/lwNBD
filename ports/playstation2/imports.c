#include "irx_imports.h"

/* clang-format off */

atad_IMPORTS_start
I_ata_get_devinfo
I_ata_device_sector_io
I_ata_device_flush_cache
atad_IMPORTS_end

iomanX_IMPORTS_start
I_GetDeviceList
I_close
I_getstat
I_open
I_write
iomanX_IMPORTS_end

intrman_IMPORTS_start
I_CpuEnableIntr
I_CpuSuspendIntr
I_CpuResumeIntr
intrman_IMPORTS_end

loadcore_IMPORTS_start
I_RegisterLibraryEntries
loadcore_IMPORTS_end

ps2ip_IMPORTS_start
I_lwip_accept
I_lwip_bind
I_lwip_close
I_lwip_listen
I_lwip_recv
I_lwip_send
I_lwip_socket
ps2ip_IMPORTS_end

thbase_IMPORTS_start
I_CreateThread
I_DeleteThread
I_StartThread
thbase_IMPORTS_end

ssbusc_IMPORTS_start
I_GetBaseAddress
I_GetDelay
ssbusc_IMPORTS_end


sysmem_IMPORTS_start
I_AllocSysMemory
I_FreeSysMemory
I_QueryMemSize
sysmem_IMPORTS_end

sysclib_IMPORTS_start
I_memcpy
I_memset
I_sprintf
I_strcpy
I_strlen
I_strncmp
I_strncpy
I_strcmp
sysclib_IMPORTS_end

stdio_IMPORTS_start
I_printf
stdio_IMPORTS_end

xmcman_IMPORTS_start
I_McDataChecksum
I_McDetectCard2
I_McEraseBlock2
I_McFlushCache
I_McGetCardSpec
I_McGetMcType
I_McReadCluster
I_McReadPage
I_McWritePage
xmcman_IMPORTS_end
