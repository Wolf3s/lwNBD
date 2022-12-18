#include <lwnbd.h>
#include <lwnbdsvr.h>

nbd_context *nbd_contexts[10];
#include "drivers/hdd_d.h"


#ifdef _IOP
#include "irx_imports.h"
#include "drivers/atad_d.h"
#include "drivers/ioman_d.h"
#include "drivers/mcman_d.h"

IRX_ID(APP_NAME, 1, 1);
static int nbd_tid;
extern struct irx_export_table _exp_lwnbdsvr;

//need to be global to be accessible from thread
//TODO: modload.h
atad_driver hdd[2]; // could have 2 ATA disks
ioman_driver iodev[32];
mcman_driver mc[2]; // For two MC ports

int _start(int argc, char **argv)
{
    iop_device_t **dev_list = GetDeviceList();
    iop_thread_t nbd_thread;
    int i, j, ret, successed_exported_ctx = 0;

    if (argc > 1) {
        strcpy(gdefaultexport, argv[1]);
        LOG("default export : %s\n", gdefaultexport);
    }

    for (i = 0; i < 2; i++) {
        ret = atad_ctor(&hdd[i], i);
        if (ret == 0) {
            nbd_contexts[successed_exported_ctx] = &hdd[i].super;
            successed_exported_ctx++;
        }
    }

    for (int i = 0; i < 2; i++) {
        ret = mcman_ctor(&mc[i], i);
        if (ret == 0) {
            nbd_contexts[successed_exported_ctx] = &mc[i].super;
            successed_exported_ctx++;
        }
    }

    j = 0;
    for (i = 0; i < MAX_DEVICES; i++) {
        if (dev_list[i] != NULL) {
            ret = ioman_ctor(&iodev[j], dev_list[i]);
            if (ret == 0) {
                nbd_contexts[successed_exported_ctx] = &iodev[j].super;
                successed_exported_ctx++;
                j++;
            }
        }
    }

    nbd_contexts[successed_exported_ctx] = NULL;
    if (!successed_exported_ctx) {
        LOG("nothing to export.\n");
        return -1;
    }

    LOG("init %d exports.\n", successed_exported_ctx);

    // register exports
    RegisterLibraryEntries(&_exp_lwnbdsvr);

    nbd_thread.attr = TH_C;
    nbd_thread.thread = (void *)nbd_init;
    nbd_thread.priority = 0x10;
    nbd_thread.stacksize = 0x800;
    nbd_thread.option = 0;
    nbd_tid = CreateThread(&nbd_thread);

    // int StartThreadArgs(int thid, int args, void *argp);
    StartThread(nbd_tid, (struct nbd_context **)nbd_contexts);
    return MODULE_RESIDENT_END;
}

int _shutdown(void)
{
    DeleteThread(nbd_tid);
    return 0;
}
#endif

hdd_driver hdd[2]; // could have 2 ATA disks

int lwnbd_init()
{
    int ret, successed_exported_ctx = 0;

    ret = hdd_ctor(&hdd[0], 0);
    if (ret == 0) {
        nbd_contexts[successed_exported_ctx] = &hdd[0].super;
        successed_exported_ctx++;
    }

    nbd_contexts[successed_exported_ctx] = NULL;
    if (!successed_exported_ctx) {
        LOG("nothing to export.\n");
        return -1;
    }

    LOG("init %d exports.\n", successed_exported_ctx);
    nbd_init(nbd_contexts);    
    return 0;
}
