// -----------------------------------------------------------------------------
// Copyright© 2017 LEGIC® Identsystems AG, CH-8623 Wetzikon
// Confidential. All rights reserved!
// -----------------------------------------------------------------------------

#ifndef E_LegicMobileSdkNeonFileDefaultMode_h
#define E_LegicMobileSdkNeonFileDefaultMode_h

#import <Foundation/Foundation.h>

/**
 * The default marker on a Legic neon file.
 */
typedef NS_ENUM(NSInteger, E_LegicMobileSdkNeonFileDefaultMode) {
    /**
     * File can be selected with project ID and file ID consisting of all zeros (16 bytes).
     */
    E_LegicMobileSdkNeonFileDefaultMode_MOBILE_APP_DEFAULT = 0,
	
    /**
     * File can be selected with the project ID (first 4 bytes) followed by zeros for the file ID (12 bytes).
     */
    E_LegicMobileSdkNeonFileDefaultMode_LC_PROJECT_DEFAULT = 1
	
} NS_SWIFT_NAME(LegicNeonFileDefaultMode);

#endif /* E_LegicMobileSdkNeonFileDefaultMode_h */
