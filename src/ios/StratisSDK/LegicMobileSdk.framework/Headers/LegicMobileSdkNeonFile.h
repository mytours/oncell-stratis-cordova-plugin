// -----------------------------------------------------------------------------
// Copyright© 2017 LEGIC® Identsystems AG, CH-8623 Wetzikon
// Confidential. All rights reserved!
// -----------------------------------------------------------------------------

#import <Foundation/Foundation.h>
#import "LegicMobileSdkNeonFileState.h"
#import "LegicMobileSdkNeonFileMetaValueType.h"
#import "LegicMobileSdkNeonFileMetaValue.h"
#import "LegicMobileSdkRfInterface.h"

/**
 * A LEGIC neon file is a generic representation of a file within the SDK.<br>
 * Such a file can be deployed by LEGIC Connect (LC) and modified by a LEGIC reader chip.
 */
NS_SWIFT_NAME(LegicNeonFile)
@interface LegicMobileSdkNeonFile : NSObject

//-----------------------------------------------------------------------------|

/**
 * Checks, if the file contains a file ID
 *
 * @return  <li><code>true</code> if the file contains a file ID.</li>
 *          <li><code>false</code> if the file does not contain a file ID</li>
 */
- (BOOL)hasFileId
NS_SWIFT_NAME(hasFileId());

//-----------------------------------------------------------------------------|

/**
 * Checks if the file contains a file definition name.
 *
 * @return  <li><code>true</code> if the file contains a file definition name.</li>
 *          <li><code>false</code> if the file does not contain a file definition name.</li>
 */
- (BOOL)hasFileDefinitionName
NS_SWIFT_NAME(hasFileDefinitionName());

//-----------------------------------------------------------------------------|

/**
 * Returns the file ID of the current file.<br>
 * This file ID is only available if the file is deployed.
 *
 * @return  byte array representation of the file ID (12 bytes), if object represents a deployed file.
 *          (If object represents a non-deployed file, an empty data object will be returned.)
 */
- (NSData* _Nonnull const)getFileId
NS_SWIFT_NAME(getFileId());

//-----------------------------------------------------------------------------|

/**
 * Returns the file definition name of the file.<br>
 * This file definition name is only available if the file is not deployed.
 *
 * @return  Name of the file definition of the file as String, if the object represents a non- deployed file.
 *          (If object represents a deployed file, an empty String will be returned.)
 */
- (NSString* _Nonnull const)getFileDefinitionName
NS_SWIFT_NAME(getFileDefinitionName());

//-----------------------------------------------------------------------------|

/**
 * Gets the LC Project ID of the current file.
 *
 * @return  The LC Project ID in which the file belongs
 */
- (NSUInteger)getLcProjectId
NS_SWIFT_NAME(getLcProjectId());

//-----------------------------------------------------------------------------|

/**
 * Gets the state of the current file
 *
 * @return  State of the file.
 */
- (E_LegicMobileSdkNeonFileState)getFileState
NS_SWIFT_NAME(getFileState());

//-----------------------------------------------------------------------------|

/**
 * Returns the value of the system parameter named <code>displayName</code>.<br>
 * This value is optional.
 *
 * @return  Value of system parameter <code>displayName</code>, or empty <code>String</code> if not defined.
 */
- (NSString* _Nonnull const)getDisplayName
NS_SWIFT_NAME(getDisplayName());

//-----------------------------------------------------------------------------|

/**
 * Returns the value of the system parameter named <code>description</code>.<br>
 * This value is optional.
 *
 * @return  Value of system parameter <code>description</code>, or empty <code>String</code> if not defined.
 */
- (NSString* _Nonnull const)getDescription
NS_SWIFT_NAME(getDescription());

//-----------------------------------------------------------------------------|

/**
 * Gets the value of the system parameter named <code>icon</code>.<br>
 * This value is optional. As the icon represents an image, the String value is expected to be<br>
 * a base64 encoded binary value. Decoding the base64-encoded data is left to the user.
 *
 * @return  Value of system parameter <code>icon</code>, or empty <code>String</code> if not defined.
 */
- (NSString* _Nonnull const)getIconData
NS_SWIFT_NAME(getIconData());

//-----------------------------------------------------------------------------|

/**
 * Checks if the current file contains a VCP.
 *
 * @return  <li><code>true</code>  if the file contains a VCP.</li>
 *          <li><code>false</code>  if the file does not contain a VCP.</li>
 */
- (BOOL)containsVcp
NS_SWIFT_NAME(containsVcp());

//-----------------------------------------------------------------------------|

/**
 * Returns the interfaces which are active for this file.
 *
 * @return <code>List<RfInterface></code> an array of active interfaces for this file.
 *
 */
- (NSArray<LegicMobileSdkRfInterface*>* _Nonnull const)getActiveRfInterfaces
NS_SWIFT_NAME(getActiveRfInterfaces());


//-----------------------------------------------------------------------------|

/**
 * Checks whether a meta data parameter with the given name exists.
 *
 * @param key   Name of the meta data parameter to look for.
 * @return  <li><code>true</code>  if the file contains MetaData for the given key.</li>
 *          <li><code>false</code>  if the file does not contain MetaData for the given key.</li>
 */
- (BOOL)hasMetaDataValue:(NSString* _Nonnull const)key
NS_SWIFT_NAME(hasMetaDataValue(_:));

//-----------------------------------------------------------------------------|

/**
 * Gets the type of the meta data.
 *
 * @param key   Name of the custom parameter to be queried
 * @return  LegicNeonFileMetaValueType
 */
- (E_LegicMobileSdkNeonFileMetaValueType)getMetaDataType:(NSString* _Nonnull const)key
NS_SWIFT_NAME(getMetaDataType(_:));

//-----------------------------------------------------------------------------|

/**
 * Gets the <code>String</code> value of the given custom parameter.
 *
 * @param key   Name of the custom parameter to be queried
 * @return  <code>String</code> value of the named custom parameter,
 *          or empty String if the parameter type is not <code>stringValue</code>.
 */
- (NSString* _Nonnull const)getMetaDataStringValue:(NSString* _Nonnull const)key
NS_SWIFT_NAME(getMetaDataStringValue(_:));

//-----------------------------------------------------------------------------|

/**
 * Gets the <code>Long</code> value of the given custom parameter.
 *
 * @param key   Name of the custom parameter to be queried
 * @return  <code>Long</code> (Int64) value of the named custom parameter,
 *          or 0L if the parameter type is not <code>longValue</code>.
 */
- (long long)getMetaDataLongValue:(NSString* _Nonnull const)key
NS_SWIFT_NAME(getMetaDataLongValue(_:));

//-----------------------------------------------------------------------------|

/**
 * Gets the base64-encoded <code>String</code> representation of the given custom parameter.
 *
 * @param key   ame of the custom parameter to be queried
 * @return  String value of the named custom parameter,
 *          or empty String if the parameter type is not <code>base64BinaryValue</code>.
 *          Decoding the base64-encoded data is left to the user.
 */
- (NSString* _Nonnull const)getMetaDataBase64BinaryValue:(NSString* _Nonnull const)key
NS_SWIFT_NAME(getMetaDataBase64BinaryValue(_:));

//-----------------------------------------------------------------------------|

/**
 * Gets an object containing all meta data of the current file.
 *
 * @return  All meta data for the current file.
 */
- (NSDictionary< NSString*, LegicMobileSdkNeonFileMetaValue* >* _Nonnull const)getMetaData
NS_SWIFT_NAME(getMetaData());

//-----------------------------------------------------------------------------|

/**
 * Allows to query whether the current file is marked as <code>Mobile App Default</code> file.
 *
 * @return  <li><code>true</code> if the file is marked as Mobile App Default file.</li>
 *          <li><code>false</code> if the file is not marked as Mobile App Default file.</li>
 */
- (BOOL)isMobileAppDefault
NS_SWIFT_NAME(isMobileAppDefault());

//-----------------------------------------------------------------------------|

/**
 * Allows to query whether the current file is marked as <code>LC project default</code> file within the project.
 *
 * @return  <li><code>true</code> if this file is the default file in a LC project</li>
 *          <li><code>false</code> if this file is not the default file in a LC project</li>
 */
- (BOOL)isLcProjectDefault
NS_SWIFT_NAME(isLcProjectDefault());

//-----------------------------------------------------------------------------|

/**
 * Allows to query whether the current file is activated.
 *
 * @return  <li><code>true</code> if this file is currently active and accessible by the LEGIC reader chip.</li>
 *          <li><code>false</code> if this file is currently not active and not accessible by the LEGIC reader chip.</li>
 */
- (BOOL)isActivated
NS_SWIFT_NAME(isActivated());

@end
