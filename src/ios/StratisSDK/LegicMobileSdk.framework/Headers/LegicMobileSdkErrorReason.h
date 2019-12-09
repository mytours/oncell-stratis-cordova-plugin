// -----------------------------------------------------------------------------
// Copyright© 2017 LEGIC® Identsystems AG, CH-8623 Wetzikon
// Confidential. All rights reserved!
// -----------------------------------------------------------------------------

#ifndef E_LegicMobileSdkErrorReason_h
#define E_LegicMobileSdkErrorReason_h

#import <Foundation/Foundation.h>

/**
 * Enum value to classify the error status.<br>
 * Used in LegicMobileSdkExceptions.
 */
typedef NS_ENUM(NSInteger, E_LegicMobileSdkErrorReasonType) {
    /**
     * Signals success (no error)
     */
    E_LegicMobileSdkErrorReasonType_OK = 0,
	
    /**
     * An error occurred within the SDK
     */
    E_LegicMobileSdkErrorReasonType_SDK_ERROR = 1,
	
    /**
     * An error occurred related to HTTP
     */
    E_LegicMobileSdkErrorReasonType_HTTP_ERROR = 2,
	
    /**
     * An error occurred within the used back-end
     */
    E_LegicMobileSdkErrorReasonType_BACKEND_ERROR = 3
	
} NS_SWIFT_NAME(LegicMobileSdkErrorReasonType);

/**
 * Enum value classifying the error reason.
 */
typedef NS_ENUM(NSInteger, E_LegicMobileSdkErrorReasonSdkError) {
    /**
     * Signals success (no error)
     */
    E_LegicMobileSdkErrorReasonSdkError_OK = 0,
	
    /**
     * SDK has detected an error
     */
    E_LegicMobileSdkErrorReasonSdkError_GENERAL_ERROR = 1,
	
    /**
     * SDK can not handle the parameter
     */
    E_LegicMobileSdkErrorReasonSdkError_WRONG_PARAMETER = 2,
	
    
    /**
     * SDK has not been started
     */
    E_LegicMobileSdkErrorReasonSdkError_NOT_STARTED = 5,
	
    
    /**
     * The LEGIC neon file was not found
     */
    E_LegicMobileSdkErrorReasonSdkError_FILE_NOT_FOUND = 10,
	
    /**
     * The LEGIC neon file has a wrong state (e.g. not activated)
     */
    E_LegicMobileSdkErrorReasonSdkError_FILE_IN_WRONG_STATE = 11,
	
    /**
     * The RF interface is not registered for this LC Mobile App ID
     */
    E_LegicMobileSdkErrorReasonSdkError_INTERFACE_NOT_REGISTERED = 20,
	
	
    /**
     * The back-end detected a configuration error
     */
    E_LegicMobileSdkErrorReasonSdkError_BACKEND_CONFIGURATION_ERROR = 30,
	
    /**
     * The back-end had a communication error
     */
    E_LegicMobileSdkErrorReasonSdkError_BACKEND_COMMUNICATION_ERROR = 31,
	
	
    /**
     * The SDK is not registered to LEGIC Connect
     */
    E_LegicMobileSdkErrorReasonSdkError_SDK_NOT_REGISTERED = 40,
	
    
    /**
     * The SDK Queue for LC Message is full.
     */
    E_LegicMobileSdkErrorReasonSdkError_LC_MESSAGE_QUEUE_FULL = 50,
	
    /**
     * The SDK Queue for LC Message for Backend is full.
     */
    E_LegicMobileSdkErrorReasonSdkError_LC_MESSAGE_QUEUE_FOR_BACKEND_FULL = 51,
    
    /**
     * The SDK Queue for Passwords is full.
     */
    E_LegicMobileSdkErrorReasonSdkError_PASSWORD_QUEUE_FULL = 60
	
} NS_SWIFT_NAME(LegicMobileSdkErrorReasonSdkError);

/**
 * Reason why an error occured.
 */
NS_SWIFT_NAME(LegicMobileSdkErrorReason)
@interface LegicMobileSdkErrorReason : NSObject

/**
 * Returns the type of the error as enum.
 *
 * @return Enum describing the error reason.
 */
- (E_LegicMobileSdkErrorReasonType)getReasonType
NS_SWIFT_NAME(getReasonType());

/**
 * Returns the actual error code as integer.
 * The error code needs to be handled, depending on the type of the error.
 *
 * @return Error code as integer. Errors can be SDK error, HTTP error codes or LEGIC Connect error codes.
 */
- (NSInteger)getErrorCode
NS_SWIFT_NAME(getErrorCode());

/**
 * This helper functions tries to resolve the error code as SdkError code enum
 *
 * @return SdkError Enum or GENERAL Error if error reason is not SDK_ERROR
 */
- (E_LegicMobileSdkErrorReasonSdkError)getSdkErrorCode
NS_SWIFT_NAME(getSdkErrorCode());

/**
 * This method returns a string containing an error description.
 *
 * @return Description of the error
 */
- (NSString* _Nonnull const)getErrorDescription
NS_SWIFT_NAME(getErrorDescription());

@end


#endif /* E_LegicMobileSdkErrorReason_h */
