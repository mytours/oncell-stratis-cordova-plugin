// -----------------------------------------------------------------------------
// Copyright© 2017 LEGIC® Identsystems AG, CH-8623 Wetzikon
// Confidential. All rights reserved!
// -----------------------------------------------------------------------------

#import "LegicMobileSdkBaseEventDelegate.h"

/**
 * Handles password related events
 */
NS_SWIFT_NAME(LegicMobileSdkPasswordEventDelegate)
@protocol LegicMobileSdkPasswordEventDelegate <LegicMobileSdkBaseEventDelegate>
@optional
/**
 * Callback gets invoked when the LEGIC reader chip requests a password entry via an LC_MESSAGE command.
 *
 * @param data          Data that was sent within the LC_MESSAGE command
 * @param rfInterface   RF interface where the LC_MESSAGE command was received
 */
- (void)readerPasswordRequestEvent:(NSData* _Nullable const)data
                       rfInterface:(LegicMobileSdkRfInterface* _Nonnull const)rfInterface
NS_SWIFT_NAME(readerPasswordRequestEvent(data:rfInterface:));

@end
