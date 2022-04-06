#ifndef APPLE_OTG_H
#define APPLE_OTG_H

#include "hw/sysbus.h"
#include "qom/object.h"
#include "hw/arm/xnu_dtb.h"
#include "hw/usb/hcd-dwc2.h"
#include "hw/usb/hcd-tcp.h"
#include "hw/usb/hcd-fuzz.h"

#define TYPE_APPLE_OTG "apple.otg"
OBJECT_DECLARE_SIMPLE_TYPE(AppleOTGState, APPLE_OTG)

struct AppleOTGState {
    SysBusDevice parent_obj;
    MemoryRegion phy;
    uint8_t      phy_reg[0x20];
    MemoryRegion usbctl;
    uint8_t      usbctl_reg[0x1000];
    MemoryRegion dwc2_mr;
    MemoryRegion *dma_mr;
    DWC2State    *dwc2;
    union {
        struct USBTCPHostState *usbtcp;
        struct USBFuzzHostState *usbfuzz;
        DeviceState *usbhcd;
    };
    bool fuzz;
    char *fuzz_input;
};

DeviceState *apple_otg_create(DTBNode *node);
#endif
