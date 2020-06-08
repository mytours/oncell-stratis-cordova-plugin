// -----------------------------------------------------------------------------
// Copyright© 2017 LEGIC® Identsystems AG, CH-8623 Wetzikon
// Confidential. All rights reserved!
// -----------------------------------------------------------------------------

#ifndef E_LegicMobileSdkError_h
#define E_LegicMobileSdkError_h

#import <Foundation/Foundation.h>
#import "LegicMobileSdkStatus.h"

typedef NS_CLOSED_ENUM(NSInteger, E_LegicMobileSdkErrorCode) {
    /**
     * Signals success (no error)
     */
    E_LegicMobileSdkErrorCode_OK = 0,
	
    /**
     * This status is returned whenever no specific status code is available
     */
    E_LegicMobileSdkErrorCode_GENERAL_ERROR = 1,
	
	
    // Registration related errors
    /**
     * <code>initiateRegistration</code> or <code>register</code> call was not completed successfully
     */
    E_LegicMobileSdkErrorCode_REGISTRATION_FAILED = 10,
	
    /**
     * <code>unregistration</code> call was not completed successfully
     */
    E_LegicMobileSdkErrorCode_UNREGISTER_FAILED = 11,
	
    
    // File related errors
    /**
     * <code>requestAddFile</code> call was not completed successfully
     */
    E_LegicMobileSdkErrorCode_REQUEST_ADD_FILE_FAILED = 31,
	
    /**
     * <code>requestRemoveFile</code> call was not completed successfully
     */
    E_LegicMobileSdkErrorCode_REQUEST_REMOVE_FILE_FAILED = 32,
	
    /**
     * <code>synchronize</code> call was not completed successfully
     */
    E_LegicMobileSdkErrorCode_SYNCHRONIZE_FAILED = 33,
	
    /**
     * LEGIC neon file could not be activated
     */
    E_LegicMobileSdkErrorCode_ACTIVATE_FILE_FAILED = 34,
	
    /**
     * LEGIC neon file could not be deactivated
     */
    E_LegicMobileSdkErrorCode_DEACTIVATE_FILE_FAILED = 35,
	
    
    // Interface related errors
    /**
     * RF interface could not be activated
     */
    E_LegicMobileSdkErrorCode_ACTIVATE_RF_INTERFACE_FAILED = 50,
	
    /**
     * RF interface could not be deactivated
     */
    E_LegicMobileSdkErrorCode_DEACTIVATE_RF_INTERFACE_FAILED = 51,
	
    
    // Message or Password related errors
    /**
     * LC message could not be sent to the LEGIC reader chip
     */
    E_LegicMobileSdkErrorCode_LC_MESSAGE_SEND_FAILED = 70,
	
    /**
     * Password could not be sent to the LEGIC reader chip
     */
    E_LegicMobileSdkErrorCode_PASSWORD_SEND_FAILED = 71,
    
    /**
     * LC Message for Backend could not be stored.
     */
    E_LegicMobileSdkErrorCode_LC_MESSAGE_TO_BACKEND_FAILED = 72,

} NS_SWIFT_NAME(LegicMobileSdkErrorCode);


#endif /* E_LegicMobileSdkError_h */
