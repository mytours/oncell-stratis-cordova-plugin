// -----------------------------------------------------------------------------
// Copyright© 2017 LEGIC® Identsystems AG, CH-8623 Wetzikon
// Confidential. All rights reserved!
// -----------------------------------------------------------------------------

#ifndef E_LegicMobileSdkNeonFileMetaValueType_h
#define E_LegicMobileSdkNeonFileMetaValueType_h

#import <Foundation/Foundation.h>

/**
 * Enum value to identity the value type of a <code>LegicNeonFileMetaValue</code>.
 */
typedef NS_ENUM(NSInteger, E_LegicMobileSdkNeonFileMetaValueType) {
    /**
     * The value type of the <code>LegicNeonFile</code> Meta is unknown.<br>
     * This type should not occur in normal operation, but might occur to handle future value types on older SDK versions.
     */
    E_LegicMobileSdkNeonFileMetaValueType_UNKNOWN_VALUE = 0,
	
    /**
     * The meta value is a regular <code>String</code> object.
     */
    E_LegicMobileSdkNeonFileMetaValueType_STRING_VALUE = 1,
	
    /**
     * The meta value is a regular <code>Long</code> object.
     */
    E_LegicMobileSdkNeonFileMetaValueType_LONG_VALUE = 2,
	
    /**
     * The meta value contains a base64 encoded binary value (array of bytes).<br>
     * It is represented as a <code>String</code> value. Decoding the base64 value is left to the user.
     */
    E_LegicMobileSdkNeonFileMetaValueType_BASE64_VALUE = 3
	
} NS_SWIFT_NAME(LegicNeonFileMetaValueType);

#endif /* E_LegicMobileSdkNeonFileMetaValueType_h */
