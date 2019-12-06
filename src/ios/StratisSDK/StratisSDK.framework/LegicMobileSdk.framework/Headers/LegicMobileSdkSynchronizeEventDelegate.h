// -----------------------------------------------------------------------------
// Copyright© 2017 LEGIC® Identsystems AG, CH-8623 Wetzikon
// Confidential. All rights reserved!
// -----------------------------------------------------------------------------

#import "LegicMobileSdkBaseEventDelegate.h"
#import "LegicMobileSdkStatus.h"

/**
 * Handles backend - sdk synchronization events
 */
NS_SWIFT_NAME(LegicMobileSdkSynchronizeEventDelegate)
@protocol LegicMobileSdkSynchronizeEventDelegate <LegicMobileSdkBaseEventDelegate>
@optional
/**
 * Callback gets invoked when the SDK starts a synchronize process with the back-end.
 */
- (void)backendSynchronizeStartEvent
NS_SWIFT_NAME(backendSynchronizeStartEvent());

/**
 * Callback gets invoked when the back-end response to a synchronizeWithBackend call is received<br>
 * and the synchronize process is done.
 *
 * @param sdkStatus Detailed information about the result of the back-end call.
 */
- (void)backendSynchronizeDoneEvent:(LegicMobileSdkStatus* _Nonnull const)sdkStatus
NS_SWIFT_NAME(backendSynchronizeDoneEvent(sdkStatus:));

@end
