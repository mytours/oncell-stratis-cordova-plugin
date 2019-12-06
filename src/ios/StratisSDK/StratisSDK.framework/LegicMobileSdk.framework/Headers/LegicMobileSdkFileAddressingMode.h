// -----------------------------------------------------------------------------
// Copyright© 2017 LEGIC® Identsystems AG, CH-8623 Wetzikon
// Confidential. All rights reserved!
// -----------------------------------------------------------------------------

#ifndef E_LegicMobileSdkFileAddressingMode_h
#define E_LegicMobileSdkFileAddressingMode_h

#import <Foundation/Foundation.h>

/**
 * Enum value to identify the addressing mode.
 */
typedef NS_ENUM(NSInteger, E_LegicMobileSdkFileAddressingMode) {
    /**
     * SDK exposes HCE and BLE services based on the LC Project IDs of the LEGIC neon files.
     */
    E_LegicMobileSdkFileAddressingMode_LC_PROJECT_ID = 0,
	
    /**
     * SDK exposes HCE and BLE services based on the configured LC Mobile App ID.
     */
    E_LegicMobileSdkFileAddressingMode_LC_MOBILE_APP_ID = 1
	
} NS_SWIFT_NAME(LegicMobileSdkFileAddressingMode);

#endif /* E_LegicMobileSdkFileAddressingMode_h */
