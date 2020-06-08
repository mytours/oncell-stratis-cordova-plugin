// -----------------------------------------------------------------------------
// Copyright© 2017 LEGIC® Identsystems AG, CH-8623 Wetzikon
// Confidential. All rights reserved!
// -----------------------------------------------------------------------------

#import <UIKit/UIKit.h>

//! Project version number for LegicSdk.
FOUNDATION_EXPORT double LegicSdkVersionNumber;

//! Project version string for LegicSdk.
FOUNDATION_EXPORT const unsigned char LegicSdkVersionString[];

#import <LegicMobileSdk/LegicMobileSdkManagerFactory.h>
#import <LegicMobileSdk/LegicMobileSdkManager.h>

// types
#import <LegicMobileSdk/LegicMobileSdkLcConfirmationMethod.h>
#import <LegicMobileSdk/LegicMobileSdkError.h>
#import <LegicMobileSdk/LegicMobileSdkErrorReason.h>
#import <LegicMobileSdk/LegicMobileSdkFileAddressingMode.h>
#import <LegicMobileSdk/LegicMobileSdkLcMessageMode.h>
#import <LegicMobileSdk/LegicMobileSdkNeonFile.h>
#import <LegicMobileSdk/LegicMobileSdkNeonFileDefaultMode.h>
#import <LegicMobileSdk/LegicMobileSdkNeonFileMetaValue.h>
#import <LegicMobileSdk/LegicMobileSdkNeonFileMetaValueType.h>
#import <LegicMobileSdk/LegicMobileSdkNeonFileParameter.h>
#import <LegicMobileSdk/LegicMobileSdkNeonFileState.h>
#import <LegicMobileSdk/LegicMobileSdkPushType.h>
#import <LegicMobileSdk/LegicMobileSdkRfInterface.h>
#import <LegicMobileSdk/LegicMobileSdkRfInterfaceState.h>
#import <LegicMobileSdk/LegicMobileSdkStatus.h>

// delegates
#import <LegicMobileSdk/LegicMobileSdkBaseEventDelegate.h>
#import <LegicMobileSdk/LegicMobileSdkEventDelegate.h>
#import <LegicMobileSdk/LegicMobileSdkNeonFileEventDelegate.h>
#import <LegicMobileSdk/LegicMobileSdkPasswordEventDelegate.h>
#import <LegicMobileSdk/LegicMobileSdkReaderEventDelegate.h>
#import <LegicMobileSdk/LegicMobileSdkRegistrationEventDelegate.h>
#import <LegicMobileSdk/LegicMobileSdkSynchronizeEventDelegate.h>
