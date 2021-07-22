// -----------------------------------------------------------------------------
// Copyright© 2017 LEGIC® Identsystems AG, CH-8623 Wetzikon
// Confidential. All rights reserved!
// -----------------------------------------------------------------------------

#import <Foundation/Foundation.h>

#import "LegicMobileSdkManager.h"
#import "LegicMobileSdkError.h"

NS_SWIFT_NAME(LegicMobileSdkManagerFactory)
@interface LegicMobileSdkManagerFactory : NSObject

/**
 * Factory function that returns a reference to an LegicMobileSdkManager singleton.
 *
 * @return Reference to a LegicMobileSdkManager singleton
 * @throws LegicMobileSdkError if an error occurs
 */
+ (LegicMobileSdkManager* _Nullable const)getInstance:(NSError* _Nullable __autoreleasing * _Nullable)error
NS_SWIFT_NAME(getInstance());

@end
