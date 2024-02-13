#include <iostream>
#include <Windows.h>
#include <WinUser.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>


//int main()
//{
//	INPUT ip;
//
//	ip.type = INPUT_KEYBOARD;
//    ip.ki.wScan = 0;
//    ip.ki.time = 0;
//    ip.ki.dwExtraInfo = 0;
//
//    ip.ki.wVk = 0x41;
//    ip.ki.dwFlags = 0;
//    SendInput(1, &ip, sizeof(INPUT));
//
//}

//#define X 123
//#define Y 123
//#define SCREEN_WIDTH 1920
//#define SCREEN_HEIGHT 1080
//
//
//void MouseSetup(INPUT* buffer)
//{
//    buffer->type = INPUT_MOUSE;
//    buffer->mi.dx = (0 * (0xFFFF / SCREEN_WIDTH));
//    buffer->mi.dy = (0 * (0xFFFF / SCREEN_HEIGHT));
//    buffer->mi.mouseData = 0;
//    buffer->mi.dwFlags = MOUSEEVENTF_MOVE;
//    buffer->mi.time = 0;
//    buffer->mi.dwExtraInfo = 0;
//}
//
//
////void MouseMoveAbsolute(INPUT* buffer, int x, int y)
////{
////    buffer->mi.dx = (x * (0xFFFF / SCREEN_WIDTH));
////    buffer->mi.dy = (y * (0xFFFF / SCREEN_HEIGHT));
////    buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE);
////
////    SendInput(1, buffer, sizeof(INPUT));
////}
//
//
//void MouseClick(INPUT* buffer)
//{
//    buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN);
//    SendInput(1, buffer, sizeof(INPUT));
//
//    Sleep(10);
//
//    buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP);
//    SendInput(1, buffer, sizeof(INPUT));
//}
//
//
//int main(int argc, char* argv[])
//{
//    INPUT buffer[1];
//
//    MouseSetup(buffer);
//    //MouseMoveAbsolute(buffer, X, Y);
//    //MouseClick(buffer);
//
//    Sleep(5000);
//
//    POINT p;
//
//    for (int i = 0; i < 100; i++) {
//        GetCursorPos(&p);
//        printf("%d, %d\n", p.x, p.y);
//        buffer->mi.dx = rand()%10;
//        buffer->mi.dy = 0;
//        SendInput(1, buffer, sizeof(INPUT));
//        Sleep(10);
//    }
//
//    return 0;
//}

#include <vhf.h>


UCHAR HeadSetReportDescriptor[] = {
    0x05, 0x01,         // USAGE_PAGE (Generic Desktop Controls)
    0x09, 0x0D,         // USAGE (Portable Device Buttons)
    0xA1, 0x01,         // COLLECTION (Application)
    0x85, 0x01,         //   REPORT_ID (1)
    0x05, 0x09,         //   USAGE_PAGE (Button Page)
    0x09, 0x01,         //   USAGE (Button 1 - HeadSet : middle button)
    0x09, 0x02,         //   USAGE (Button 2 - HeadSet : volume up button)
    0x09, 0x03,         //   USAGE (Button 3 - HeadSet : volume down button)
    0x15, 0x00,         //   LOGICAL_MINIMUM (0)
    0x25, 0x01,         //   LOGICAL_MAXIMUM (1)
    0x75, 0x01,         //   REPORT_SIZE (1)
    0x95, 0x03,         //   REPORT_COUNT (3)
    0x81, 0x02,         //   INPUT (Data,Var,Abs)
    0x95, 0x05,         //   REPORT_COUNT (5)
    0x81, 0x03,         //   INPUT (Cnst,Var,Abs)
    0xC0,               // END_COLLECTION
};

NTSTATUS
VhfSourceCreateDevice(
    _Inout_ PWDFDEVICE_INIT DeviceInit
)
{
    WDF_OBJECT_ATTRIBUTES   deviceAttributes;
    PDEVICE_CONTEXT deviceContext;
    VHF_CONFIG vhfConfig;
    WDFDEVICE device;
    NTSTATUS status;

    PAGED_CODE();

    WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE(&deviceAttributes, DEVICE_CONTEXT);
    deviceAttributes.EvtCleanupCallback = VhfSourceDeviceCleanup;

    status = WdfDeviceCreate(&DeviceInit, &deviceAttributes, &device);

    if (NT_SUCCESS(status))
    {
        deviceContext = DeviceGetContext(device);

        VHF_CONFIG_INIT(&vhfConfig,
            WdfDeviceWdmGetDeviceObject(device),
            sizeof(VhfHeadSetReportDescriptor),
            VhfHeadSetReportDescriptor);

        status = VhfCreate(&vhfConfig, &deviceContext->VhfHandle);

        if (!NT_SUCCESS(status)) {
            TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE, "VhfCreate failed %!STATUS!", status);
            goto Error;
        }

        status = VhfStart(deviceContext->VhfHandle);
        if (!NT_SUCCESS(status)) {
            TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE, "VhfStart failed %!STATUS!", status);
            goto Error;
        }

    }

Error:
    return status;
}

VOID
MY_SubmitReadReport(
    PMY_CONTEXT  Context,
    BUTTON_TYPE  ButtonType,
    BUTTON_STATE ButtonState
)
{
    PDEVICE_CONTEXT deviceContext = (PDEVICE_CONTEXT)(Context);

    if (ButtonState == ButtonStateUp) {
        deviceContext->VhfHidReport.ReportBuffer[0] &= ~(0x01 << ButtonType);
    }
    else {
        deviceContext->VhfHidReport.ReportBuffer[0] |= (0x01 << ButtonType);
    }

    status = VhfReadReportSubmit(deviceContext->VhfHandle, &deviceContext->VhfHidReport);

    if (!NT_SUCCESS(status)) {
        TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE, "VhfReadReportSubmit failed %!STATUS!", status);
    }
}

VOID
VhfSourceDeviceCleanup(
    _In_ WDFOBJECT DeviceObject
)
{
    PDEVICE_CONTEXT deviceContext;

    PAGED_CODE();

    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DEVICE, "%!FUNC! Entry");

    deviceContext = DeviceGetContext(DeviceObject);

    if (deviceContext->VhfHandle != WDF_NO_HANDLE)
    {
        VhfDelete(deviceContext->VhfHandle, TRUE);
    }

}

int main()
{

}