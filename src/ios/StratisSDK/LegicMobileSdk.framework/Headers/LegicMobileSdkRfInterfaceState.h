// -----------------------------------------------------------------------------
// Copyright© 2017 LEGIC® Identsystems AG, CH-8623 Wetzikon
// Confidential. All rights reserved!
// -----------------------------------------------------------------------------

#ifndef E_LegicMobileSdkRfInterfaceState_h
#define E_LegicMobileSdkRfInterfaceState_h

#import <Foundation/Foundation.h>

/**
 * Enum value to identify the state of the RF interface.
 */
typedef NS_ENUM(NSInteger, E_LegicMobileSdkRfInterfaceState) {
    /**
     * RF interface state is unknown (e.g. when starting the mobile app)
     */
    E_LegicMobileSdkRfInterfaceState_UNKNOWN = 0,
	
    /**
     * RF interface is not supported by the operating system
     */
    E_LegicMobileSdkRfInterfaceState_NOT_SUPPORTED = 1,
	
    /**
     * RF interface has been disabled by the user<br>
     * (on operating system level, e.g. by disabling BLE)
     */
    E_LegicMobileSdkRfInterfaceState_NOT_HARDWARE_ENABLED = 2,
	
    /**
     * RF interface has been enabled by the user<br>
     * (on operating system level, e.g. by enabling BLE)
     */
    E_LegicMobileSdkRfInterfaceState_HARDWARE_ENABLED = 3,
	
    /**
     * RF interface has been activated<br>
     * (by calling the corresponding SDK function)
     */
    E_LegicMobileSdkRfInterfaceState_ACTIVATED = 4,
	
    /**
     * RF interface has been deactivated<br>
     * (by calling the corresponding SDK function)
     */
    E_LegicMobileSdkRfInterfaceState_DEACTIVATED = 5
	
} NS_SWIFT_NAME(RfInterfaceState);

#endif /* E_LegicMobileSdkRfInterfaceState_h */
