// -----------------------------------------------------------------------------
// Copyright© 2017 LEGIC® Identsystems AG, CH-8623 Wetzikon
// Confidential. All rights reserved!
// -----------------------------------------------------------------------------

#import "LegicMobileSdkNeonFileEventDelegate.h"
#import "LegicMobileSdkBaseEventDelegate.h"
#import "LegicMobileSdkStatus.h"
#import "LegicMobileSdkRfInterface.h"
#import "LegicMobileSdkNeonFile.h"
#import "LegicMobileSdkNeonSubFile.h"

/**
 * Handles LEGIC neon File related events
 */
NS_SWIFT_NAME(LegicNeonFileEventDelegate)
@protocol LegicMobileSdkNeonFileEventDelegate <LegicMobileSdkBaseEventDelegate>
@optional
/**
 * Callback gets invoked whenever a new LEGIC neon file appears or
 * an existing one gets updated (either content or meta data).
 *
 * @param file  LEGIC neon file that got updated/added during synchronize operation
 */
- (void)backendFileChangedEvent:(LegicMobileSdkNeonFile* _Nonnull const)file
NS_SWIFT_NAME(backendFileChangedEvent(file:));

/**
 * Callback gets invoked when the back-end response to a requestAddFile call is received.
 *
 * @param sdkStatus Detailed information about the result of the back-end call
 */
- (void)backendRequestAddFileDoneEvent:(LegicMobileSdkStatus* _Nonnull const)sdkStatus
NS_SWIFT_NAME(backendRequestAddFileDoneEvent(sdkStatus:));

/**
 * Callback gets invoked when the back-end response to a requestRemoveFile call is received.
 *
 * @param sdkStatus Detailed information about the result of the back-end call
 */
- (void)backendRequestRemoveFileDoneEvent:(LegicMobileSdkStatus* _Nonnull const)sdkStatus
NS_SWIFT_NAME(backendRequestRemoveFileDoneEvent(sdkStatus:));

/**
 * Callback gets invoked when a LEGIC neon file is read by the LEGIC reader chip.
 *
 * @param file          LEGIC neon file that was accessed (read access)
 * @param rfInterface   RF interface that was used to access the LEGIC neon file
 */
- (void)readerReadFileEvent:(LegicMobileSdkNeonFile* _Nonnull const)file
                rfInterface:(LegicMobileSdkRfInterface* _Nonnull const)rfInterface
NS_SWIFT_NAME(readerReadFileEvent(file:rfInterface:));


/**
 * Callback gets invoked when a LEGIC neon file is written by the LEGIC reader chip.
 *
 * @param file          LEGIC neon file that was accessed (write access)
 * @param rfInterface   RF interface that was used to access the LEGIC neon file
 */
- (void)readerWriteFileEvent:(LegicMobileSdkNeonFile* _Nonnull const)file
                 rfInterface:(LegicMobileSdkRfInterface* _Nonnull const)rfInterface
NS_SWIFT_NAME(readerWriteFileEvent(file:rfInterface:));

/**
 * Callback gets invoked when a LEGIC neon sub file is read by the LEGIC reader chip.
 *
 * @param subfile       LEGIC neon sub file that was accessed (read access)
 * @param mainfile      LEGIC neon main file
 * @param rfInterface   RF interface that was used to access the LEGIC neon file
 */
- (void)readerReadSubFileEvent:(LegicMobileSdkNeonSubFile* _Nonnull const)subfile
                      mainfile:(LegicMobileSdkNeonFile* _Nonnull const)mainfile
                   rfInterface:(LegicMobileSdkRfInterface* _Nonnull const)rfInterface
NS_SWIFT_NAME(readerReadSubFileEvent(subfile:mainfile:rfInterface:));


/**
 * Callback gets invoked when a LEGIC neon sub file is written by the LEGIC reader chip.
 *
 * @param subfile       LEGIC neon sub file that was accessed (write access)
 * @param mainfile      LEGIC neon main file
 * @param rfInterface   RF interface that was used to access the LEGIC neon file
 */
- (void)readerWriteSubFileEvent:(LegicMobileSdkNeonSubFile* _Nonnull const)subfile
                       mainfile:(LegicMobileSdkNeonFile* _Nonnull const)mainfile
                    rfInterface:(LegicMobileSdkRfInterface* _Nonnull const)rfInterface
NS_SWIFT_NAME(readerWriteSubFileEvent(subfile:mainfile:rfInterface:));


@end
