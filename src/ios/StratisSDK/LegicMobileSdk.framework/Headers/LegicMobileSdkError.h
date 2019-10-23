// -----------------------------------------------------------------------------
// Copyright© 2017 LEGIC® Identsystems AG, CH-8623 Wetzikon
// Confidential. All rights reserved!
// -----------------------------------------------------------------------------

#ifndef LegicMobileSdkError_h
#define LegicMobileSdkError_h

#import <Foundation/Foundation.h>
#import "LegicMobileSdkStatus.h"

/**
 * Information if any communication error occurred in the SDK
 */
NS_SWIFT_NAME(LegicMobileSdkError)
@interface LegicMobileSdkError : NSError

/**
 * Gets the status of the error
 *
 * @return The status, containing further information of the error
 */
- (LegicMobileSdkStatus* _Nonnull const)getStatus
NS_SWIFT_NAME(getStatus());

@end

#endif /* LegicMobileSdkError_h */
