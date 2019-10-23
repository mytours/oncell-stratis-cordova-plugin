// -----------------------------------------------------------------------------
// Copyright© 2017 LEGIC® Identsystems AG, CH-8623 Wetzikon
// Confidential. All rights reserved!
// -----------------------------------------------------------------------------

#import "LegicMobileSdkBaseEventDelegate.h"
#import "LegicMobileSdkLcMessageMode.h"
#import "LegicMobileSdkFileAddressingMode.h"
#import "LegicMobileSdkRfInterface.h"

/**
 * Handles reader related events
 */
NS_SWIFT_NAME(LegicReaderEventDelegate)
@protocol LegicMobileSdkReaderEventDelegate <LegicMobileSdkBaseEventDelegate>
@optional
/**
 * Callback gets invoked when the LEGIC reader chip sends a regular LC_MESSAGE command to the mobile app.
 *
 * @param data          Data that was sent within the LC_MESSAGE command
 * @param lcMessageMode 	Mode used to transmit the LC_MESSAGE command
 * @param rfInterface   RF interface where the LC_MESSAGE command was received
 */
- (void)readerLcMessageEvent:(NSData* _Nonnull const)data
               lcMessageMode:(E_LegicMobileSdkLcMessageMode)lcMessageMode
                 rfInterface:(LegicMobileSdkRfInterface* _Nonnull const)rfInterface
NS_SWIFT_NAME(readerLcMessageEvent(data:lcMessageMode:rfInterface:));

/**
 * Callback gets invoked when the LEGIC reader chip polls for responses to its last LC_MESSAGE command.
 *
 * @param lcMessageMode 	Mode used to transmit the LC_MESSAGE command
 * @param rfInterface   RF interface where the LC_MESSAGE command was received
 
 */
- (void)readerLcMessagePollingEvent:(E_LegicMobileSdkLcMessageMode)lcMessageMode
                        rfInterface:(LegicMobileSdkRfInterface* _Nonnull const)rfInterface
NS_SWIFT_NAME(readerLcMessagePollingEvent(lcMessageMode:rfInterface:));

/**
 * Callback gets invoked when the LEGIC reader chip has established a connection with a mobile app
 *
 * @param identifier    Identifier that was used to connect to the mobile app
 * @param mode          Mode to distinguish whether identifier is a Project ID or a Mobile App ID
 * @param readerType    Type of LEGIC reader chip connecting to the mobile app (e.g. 1 = SM-4300)
 * @param rfInterface   RF interface where the LC_MESSAGE command was received
 */
- (void)readerConnectEvent:(NSUInteger)identifier
                      mode:(E_LegicMobileSdkFileAddressingMode)mode
                readerType:(NSUInteger)readerType
               rfInterface:(LegicMobileSdkRfInterface* _Nonnull const)rfInterface
NS_SWIFT_NAME(readerConnectEvent(identifier:mode:readerType:rfInterface:));

/**
 * Callback gets invoked when the SDK has stored a complete message received from the LEGIC reader chip.
 *
 * @param messageCount  Number of stored messages in the buffer
 * @param rfInterface   RF interface where the LC_MESSAGE command was received
 */
- (void)readerAddedLcMessageEvent:(NSUInteger)messageCount
                      rfInterface:(LegicMobileSdkRfInterface* _Nonnull const)rfInterface
NS_SWIFT_NAME(readerAddedLcMessageEvent(messageCount:rfInterface:));

@end
