// -----------------------------------------------------------------------------
// Copyright© 2017 LEGIC® Identsystems AG, CH-8623 Wetzikon
// Confidential. All rights reserved!
// -----------------------------------------------------------------------------

#import "LegicMobileSdkBaseEventDelegate.h"
#import "LegicMobileSdkRfInterfaceState.h"
#import "LegicMobileSdkRfInterface.h"
#import "LegicMobileSdkFileAddressingMode.h"

/**
 * Handles SDK related events
 */
NS_SWIFT_NAME(LegicMobileSdkEventDelegate)
@protocol LegicMobileSdkEventDelegate <LegicMobileSdkBaseEventDelegate>
@optional
/**
 * Callback gets invoked when the SDK activates a service on any RF interface
 *
 * @param identifier    Identification of the activated service.
 * @param mode          Indicates whether the reported identifier is a LC Mobile App ID or a LC Project ID.
 * @param rfInterface   RF interface where the service got activated.
 */
- (void)sdkActivatedEvent:(NSUInteger)identifier
                     mode:(E_LegicMobileSdkFileAddressingMode)mode
              rfInterface:(LegicMobileSdkRfInterface* _Nonnull const)rfInterface
NS_SWIFT_NAME(sdkActivatedEvent(identifier:mode:rfInterface:));

/**
 * Callback gets invoked when the SDK deactivates a service on any RF interface.
 *
 * @param identifier    Identification of the activated service.
 * @param mode          Indicates whether the reported identifier is a LC Mobile App ID or a LC Project ID.
 * @param rfInterface   RF interface where the service got deactivated.
 */
- (void)sdkDeactivatedEvent:(NSUInteger)identifier
                       mode:(E_LegicMobileSdkFileAddressingMode)mode
                rfInterface:(LegicMobileSdkRfInterface* _Nonnull const)rfInterface
NS_SWIFT_NAME(sdkDeactivatedEvent(identifier:mode:rfInterface:));

/**
 * Callback gets invoked when the SDK detects changes on any RF interface.
 *
 * @param rfInterface   RF interface where the state change was detected.
 * @param state         New state of the reported RF interface.
 */
- (void)sdkRfInterfaceChangeEvent:(LegicMobileSdkRfInterface* _Nonnull const)rfInterface
                          state:(E_LegicMobileSdkRfInterfaceState)state
NS_SWIFT_NAME(sdkRfInterfaceChangeEvent(rfInterface:state:));

@end
