// -----------------------------------------------------------------------------
// Copyright© 2017 LEGIC® Identsystems AG, CH-8623 Wetzikon
// Confidential. All rights reserved!
// -----------------------------------------------------------------------------

#ifndef E_LegicMobileSdkLcConfirmationMethod_h
#define E_LegicMobileSdkLcConfirmationMethod_h

#import <Foundation/Foundation.h>

/**
 * Enum value to define the required confirmation method in the initiateRegistration call.
 */
typedef NS_CLOSED_ENUM(NSInteger, E_LegicMobileSdkLcConfirmationMethod) {
    /**
     * Confirmation token is sent via email.<br>
     * To be used when using an email address as public registration ID in the initiateRegistration call.
     */
    E_LegicMobileSdkLcConfirmationMethod_EMAIL = 0,
	
    /**
     * Confirmation token is sent via SMS.<br>
     * To be used when using a phone number as public registration ID in the initiateRegistration call.
     */
    E_LegicMobileSdkLcConfirmationMethod_SMS = 1,
	
    /**
     * Confirmation token is NOT sent from LEGIC Connect.<br>
     * To be used when using custom registration ID in the initiateRegistration call.
     */
    E_LegicMobileSdkLcConfirmationMethod_NONE = 2
	
} NS_SWIFT_NAME(LcConfirmationMethod);

#endif /* E_LegicMobileSdkConfirmationMethod_h */
