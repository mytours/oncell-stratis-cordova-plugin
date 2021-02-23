// -----------------------------------------------------------------------------
// Copyright© 2017 LEGIC® Identsystems AG, CH-8623 Wetzikon
// Confidential. All rights reserved!
// -----------------------------------------------------------------------------

#import <Foundation/Foundation.h>

/**
 * This class is used to send custom key/value pairs with the
 * LegicNeonFileParameter command.
 */
NS_SWIFT_NAME(LegicNeonFileParameter)
@interface LegicMobileSdkNeonFileParameter : NSObject

//-----------------------------------------------------------------------------|
- (instancetype _Nonnull)initWithKey:(NSString* _Nonnull const)key
                      value:(NSString* _Nonnull const)value;

//-----------------------------------------------------------------------------|

/**
 * This method returns the currently set key
 *
 * @return The key as a <code>String</code>.
 */
- (NSString* _Nonnull const)getKey
NS_SWIFT_NAME(getKey());

//-----------------------------------------------------------------------------|

/**
 * This method returns the currently set value.
 *
 * @return The value as a <code>String</code>.
 */
- (NSString* _Nonnull const)getValue
NS_SWIFT_NAME(getValue());

@end
