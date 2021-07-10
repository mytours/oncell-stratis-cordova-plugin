// -----------------------------------------------------------------------------
// Copyright© 2017 LEGIC® Identsystems AG, CH-8623 Wetzikon
// Confidential. All rights reserved!
// -----------------------------------------------------------------------------

#ifndef E_LegicMobileSdkLcMessageMode_h
#define E_LegicMobileSdkLcMessageMode_h

#import <Foundation/Foundation.h>

/**
 * Enum value to define/identify the mode for LC messages.
 */
typedef NS_CLOSED_ENUM(NSInteger, E_LegicMobileSdkLcMessageMode) {
    /**
     * LC messages are sent/received in plain (unencrypted).<br>
     * This mode is used prior to successful authentication against an existing file.
     */
    E_LegicMobileSdkLcMessageMode_PLAIN = 0,
	
    /**
     * LC messages are sent/received encrypted (and protected with a MAC).<br>
     * This mode is available after successful authentication against an existing file.
     */
    E_LegicMobileSdkLcMessageMode_ENCRYPTED_MACED_FILE_KEYS = 1
	
} NS_SWIFT_NAME(LcMessageMode);

#endif /* E_LegicMobileSdkLcMessageMode_h */
