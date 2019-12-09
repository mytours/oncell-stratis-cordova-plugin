// -----------------------------------------------------------------------------
// Copyright© 2017 LEGIC® Identsystems AG, CH-8623 Wetzikon
// Confidential. All rights reserved!
// -----------------------------------------------------------------------------

#import "LegicMobileSdkBaseEventDelegate.h"
#import "LegicMobileSdkStatus.h"

/**
 * Handles backend registration events
 */
NS_SWIFT_NAME(LegicMobileSdkRegistrationEventDelegate)
@protocol LegicMobileSdkRegistrationEventDelegate <LegicMobileSdkBaseEventDelegate>
@optional
/**
 * Callback gets invoked when the back-end response to a initiateRegistration call is received.
 *
 * @param sdkStatus Detailed information about the result of the back-end call
 */
- (void)backendRegistrationStartDoneEvent:(LegicMobileSdkStatus* _Nonnull const)sdkStatus
NS_SWIFT_NAME(backendRegistrationStartDoneEvent(sdkStatus:));

/**
 * Callback gets invoked when the back-end response to a register call is received.
 *
 * @param sdkStatus Detailed information about the result of the back-end call
 */
- (void)backendRegistrationFinishedDoneEvent:(LegicMobileSdkStatus* _Nonnull const)sdkStatus
NS_SWIFT_NAME(backendRegistrationFinishedDoneEvent(sdkStatus:));

/**
 * Callback gets invoked when the backend response to a unregister call is received.
 *
 * @param sdkStatus Detailed information about the result of the back-end call
 */
- (void)backendUnregisterDoneEvent:(LegicMobileSdkStatus* _Nonnull const)sdkStatus
NS_SWIFT_NAME(backendUnregisterDoneEvent(sdkStatus:));

@end
