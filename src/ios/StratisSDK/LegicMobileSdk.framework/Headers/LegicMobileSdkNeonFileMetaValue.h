// -----------------------------------------------------------------------------
// Copyright© 2017 LEGIC® Identsystems AG, CH-8623 Wetzikon
// Confidential. All rights reserved!
// -----------------------------------------------------------------------------

#import <Foundation/Foundation.h>
#import "LegicMobileSdkNeonFileMetaValueType.h"

/**
 * Container for system related (description, icon, display name) or customer defined meta data
 */
NS_SWIFT_NAME(LegicNeonFileMetaValue)
@interface LegicMobileSdkNeonFileMetaValue : NSObject

/**
 * Returns the type of this meta value.
 */
- (E_LegicMobileSdkNeonFileMetaValueType)getType
NS_SWIFT_NAME(getType());

/**
 * Returns a string value if the type is STRING_VALUE, and nil otherwise.
 */
- (NSString* _Nullable const)getStringValue
NS_SWIFT_NAME(getStringValue());

/**
 * Returns an NSNumber containing a long long (Int64) value if the type is LONG_VALUE,
 * and nil otherwise.
 */
- (NSNumber* _Nullable const)getLongValue
NS_SWIFT_NAME(getLongValue());

/**
 * Returns data encoded as a base64 encoded string if the type is
 * BASE64_VALUE, and nil otherwise.
 */
- (NSString* _Nullable const)getBase64binaryValue
NS_SWIFT_NAME(getBase64binaryValue());

@end
