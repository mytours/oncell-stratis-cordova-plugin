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
 * A LEGIC neon subfile is a generic representation of a subfile within the SDK.<br>
 * Such a file can be deployed by LEGIC Connect (LC) and modified by a LEGIC reader chip.
 */
NS_SWIFT_NAME(LegicNeonSubFile)
@interface LegicMobileSdkNeonSubFile : NSObject

/**
 * Returns the file ID of the current subfile.<br>
 * This file ID is only available if the file is deployed.
 *
 * @return  byte array representation of the file ID (12 bytes), if object represents a deployed file.
 *          (If object represents a non-deployed file, an empty data object will be returned.)
 */
- (NSData* _Nonnull const)getFileId
NS_SWIFT_NAME(getFileId());

//-----------------------------------------------------------------------------|

/**
 * Gets the LC Project ID of the current subfile.
 *
 * @return  The LC Project ID in which the file belongs
 */
- (NSUInteger)getLcProjectId
NS_SWIFT_NAME(getLcProjectId());

@end
