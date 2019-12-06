// -----------------------------------------------------------------------------
// Copyright© 2017 LEGIC® Identsystems AG, CH-8623 Wetzikon
// Confidential. All rights reserved!
// -----------------------------------------------------------------------------

#import <Foundation/Foundation.h>
#import "LegicMobileSdkErrorCode.h"
#import "LegicMobileSdkErrorReason.h"

/**
 * Container for information about the result of a call that was processed in the SDK.
 */
NS_SWIFT_NAME(LegicMobileSdkStatus)
@interface LegicMobileSdkStatus : NSObject

//-----------------------------------------------------------------------------|

/**
 * This method returns the SDK error field of the current <code>LegicMobileSdkStatus</code>
 *
 * @return  Enum to identify the error status.
 * @see LegicMobileSdkError
 */
- (E_LegicMobileSdkErrorCode)getError
NS_SWIFT_NAME(getError());

//-----------------------------------------------------------------------------|

/**
 * This method returns a classification of the error status.
 *
 * @return  Enum to classify the error status.
 */
- (LegicMobileSdkErrorReason* _Nonnull const)getReason
NS_SWIFT_NAME(getReason());

//-----------------------------------------------------------------------------|

/**
 * Helper method to distinguish errors from OK status.
 *
 * @return  <li><code>true</code>  if status represents a successful operation.</li>
 *          <li><code>false</code> if status represents an unsuccessful operation.</li>
 */
- (BOOL)isSuccess
NS_SWIFT_NAME(isSuccess());

@end
