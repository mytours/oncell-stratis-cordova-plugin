// -----------------------------------------------------------------------------
// Copyright© 2017 LEGIC® Identsystems AG, CH-8623 Wetzikon
// Confidential. All rights reserved!
// -----------------------------------------------------------------------------

#import <Foundation/Foundation.h>

#import "LegicMobileSdkNeonFile.h"
#import "LegicMobileSdkLcConfirmationMethod.h"
#import "LegicMobileSdkPushType.h"
#import "LegicMobileSdkNeonFileParameter.h"
#import "LegicMobileSdkNeonFileDefaultMode.h"
#import "LegicMobileSdkLcMessageMode.h"
#import "LegicMobileSdkNeonFileEventDelegate.h"
#import "LegicMobileSdkReaderEventDelegate.h"
#import "LegicMobileSdkRegistrationEventDelegate.h"
#import "LegicMobileSdkEventDelegate.h"
#import "LegicMobileSdkSynchronizeEventDelegate.h"
#import "LegicMobileSdkPasswordEventDelegate.h"
#import "LegicMobileSdkRfInterface.h"
#import "LegicMobileSdkErrorCode.h"
#import "LegicMobileSdkError.h"

/**
 * Main SDK API,
 * LEGIC Mobile SDK enables customer-created mobile apps to communicate with<br>
 * the LEGIC Connect back-end system and with LEGIC reader chips.<br>
 * Furthermore, it provides some functionality to interact with certain features<br>
 * of the mobile device (e.g. its BLE functionality)
 */
NS_SWIFT_NAME(LegicMobileSdkManager)
@interface LegicMobileSdkManager : NSObject

/**
 * Checks whether the SDK is already started or not.
 *
 * @return  <code>true</code> if the SDK is started or <code>false</code> if not.
 * @throws  LegicMobileSdkError if any error occurs
 */
- (BOOL)getIsStarted:(BOOL* _Nonnull)isStarted
			   error:(NSError* _Nullable __autoreleasing * _Nullable)error
NS_SWIFT_NAME(getIsStarted(isStarted:));


/**
 * Starts the SDK. After the start, the SDK is fully functional.
 *
 * @param lcMobileAppId     Mobile App ID: The identification of your mobile app (collect from LC)
 * @param lcTechUsername    The tech user username of your mobile app (collect from LC)
 * @param lcTechPassword    The tech user password of your mobile app (collect from LC)
 * @param lcUrl             The LC server URL
 * @throws LegicMobileSdkError  if any error occurs during configuration of the SDK.
 */
- (BOOL)start:(NSUInteger)lcMobileAppId
lcTechUsername:(NSString* _Nonnull const)lcTechUsername
lcTechPassword:(NSString* _Nonnull const)lcTechPassword
         lcUrl:(NSString* _Nonnull const)lcUrl
         error:(NSError* _Nullable __autoreleasing * _Nullable)error
NS_SWIFT_NAME(start(lcMobileAppId:lcTechUsername:lcTechPassword:lcUrl:));

/**
 * Retrieves the version of the SDK as <code>String</code> with format a.b.c.d.
 *
 * @return the version of the SDK as <code>String</code> with format a.b.c.d.
 *          <li>a = Major Version</li>
 *          <li>b = Minor Version 1</li>
 *          <li>c = Minor Version 2</li>
 *          <li>d = Minor Version 3</li>
 */
- (NSString* _Nonnull const)getVersion
NS_SWIFT_NAME(getVersion());

/**
 * Allows to query the SDK for the current back-end registration status.
 *
 * @return  <code>true</code> if the SDK has been successfully registered.
 * @throws LegicMobileSdkError if any error occurs during the execution of this operation.
 */
- (BOOL)getIsRegisteredToBackend:(BOOL* _Nonnull)isRegistered
						   error:(NSError* _Nullable __autoreleasing * _Nullable)error
NS_SWIFT_NAME(getIsRegisteredToBackend(isRegistered:));

/**
 * Enables the LC project addressing mode,
 * which allows to access the services additionally via the LC Project ID.
 *
 * @param active    Indicates whether access via LC Project ID shall be activated
 * @throws LegicMobileSdkError if any error occurs during setting the project addressing mode.
 */
- (BOOL)setLcProjectAddressingMode:(BOOL)active
                             error:(NSError* _Nullable __autoreleasing * _Nullable)error
NS_SWIFT_NAME(setLcProjectAddressingMode(active:));

/**
 * Returns the current status for LC project addressing mode.
 *
 * @return  <li><code>true</code> if LC project addressing mode is active.</li>
 *          <li><code>false</code> if LC project addressing mode is not active.</li>
 * @throws LegicMobileSdkError  if any error occurs during getting the project addressing mode.
 */
- (BOOL)getLcProjectAddressingMode:(BOOL* _Nonnull)isActive
							 error:(NSError* _Nullable __autoreleasing * _Nullable)error
NS_SWIFT_NAME(getLcProjectAddressingMode(isActive:));

/**
 * Disables certificate pinning for SSL connections (certificate pinning is enabled by default)
 *
 * @throws LegicMobileSdkError  if any error occurs while disabling certificate pinning.
 */
- (BOOL)disableCertificatePinning:(NSError* _Nullable __autoreleasing * _Nullable)error
NS_SWIFT_NAME(disableCertificatePinning());

/**
 * Enables certificate pinning for SSL connections (certificate pinning is enabled by default)
 *
 * @throws LegicMobileSdkError  if any error occurs during enabling certificate pinning.
 */
- (BOOL)enableCertificatePinning:(NSError* _Nullable __autoreleasing * _Nullable)error
NS_SWIFT_NAME(enableCertificatePinning());

/**
 * Allows to query whether the certificate pinning functionality is enabled.
 *
 * @return  <code>true</code> if the SDK enforces certificate pinning for SSL connections.
 * @throws LegicMobileSdkError  if any error occurs while querying status of certificate pinning.
 */
- (BOOL)getIsCertificatePinningEnabled:(BOOL* _Nonnull)isEnabled
								 error:(NSError* _Nullable __autoreleasing * _Nullable)error
NS_SWIFT_NAME(getIsCertificatePinningEnabled(isEnabled:));

/**
 * Starts the registration process with LEGIC Connect (LC).<br>
 * If the push token is not present at registration time,<br>
 * it can be updated after the token is available.<br>
 * Use the setPushToken call to update the push token within LC.
 *
 * @param publicRegistrationId  ID used to identify the user’s installation.
 *                              This can be a phone number, an email address or a custom identifier.
 * @param rfInterfaces          List of RF interfaces that shall be available after the registration.
 * @param lcConfirmationMethod  Identifies the method to send out confirmation token.
 *                              This value must match the format of the publicRegistrationId.
 * @see LegicMobileSdkRegistrationEventListener
 */
- (void)initiateRegistration:(NSString* _Nonnull const)publicRegistrationId
				rfInterfaces:(NSArray< LegicMobileSdkRfInterface* >* _Nonnull const)rfInterfaces
		lcConfirmationMethod:(E_LegicMobileSdkLcConfirmationMethod)lcConfirmationMethod
NS_SWIFT_NAME(initiateRegistration(publicRegistrationId:rfInterfaces:lcConfirmationMethod:));

/**
 * Starts the registration process with LEGIC Connect (LC).<br>
 * If the push token is not present at registration time,<br>
 * it can be updated after the token is available.<br>
 * Use the setPushToken call to update the push token within LC.
 *
 * @param publicRegistrationId  ID used to identify the user’s installation.
 *                              This can be a phone number, an email address or a custom identifier.
 * @param rfInterfaces          List of RF interfaces that shall be available after the registration.
 * @param lcConfirmationMethod  Identifies the method to send out confirmation token.
 *                              This value must match the format of the publicRegistrationId.
 * @param pushToken             Token to be used to send out push notifications. This value may be null.
 *                              To update a pushToken after registration, use the function setPushToken.
 * @param pushType              Type of pushToken submitted.
 * @see LegicMobileSdkRegistrationEventListener
 */
- (void)initiateRegistration:(NSString* _Nonnull const)publicRegistrationId
                rfInterfaces:(NSArray< LegicMobileSdkRfInterface* >* _Nonnull const)rfInterfaces
        lcConfirmationMethod:(E_LegicMobileSdkLcConfirmationMethod)lcConfirmationMethod
                   pushToken:(NSData* _Nullable const)pushToken
                    pushType:(E_LegicMobileSdkPushType)pushType
NS_SWIFT_NAME(initiateRegistration(publicRegistrationId:rfInterfaces:lcConfirmationMethod:pushToken:pushType:));

/**
 * Finalizes the registration by submitting the received token back to LEGIC Connect.<br>
 * Existing registrations remain valid until subsequent registrations are finalized with success.
 *
 * @param token Registration token as <code>String</code> received via the requested confirmation method
 * @see LegicMobileSdkRegistrationEventListener
 */
- (void)registerWithBackend:(NSString* _Nonnull const)token
NS_SWIFT_NAME(registerWithBackend(token:));

/**
 * Unregisters the SDK. All corresponding information<br>
 * (e.g. available or deployed files) is deleted from the mobile device.
 * @see LegicMobileSdkRegistrationEventListener
 */
- (void)unregister
NS_SWIFT_NAME(unregister());

/**
 * Synchronizes with LEGIC Connect server and performs operations<br>
 * (deployment or removal of files, update of meta information).
 * @see LegicMobileSdkSynchronizeEventListener
 */
- (void)synchronizeWithBackend
NS_SWIFT_NAME(synchronizeWithBackend());

/**
 * Informs LC that the user requests the deployment of a LEGIC neon file.
 *
 * @param file  LEGIC neon file that shall be deployed (requested by the user)
 * @see LegicNeonFileEventListener
 */
- (void)requestAddFile:(LegicMobileSdkNeonFile* _Nonnull const)file
NS_SWIFT_NAME(requestAddFile(_:));

/**
 * Informs LC that the user requests the deployment of a LEGIC neon file.
 *
 * @param file          LEGIC neon file that shall be deployed (requested by the user)
 * @param parameters    Parameters (key/value pairs) that shall be passed to LC server
 *                      with the RequestAddFile request. These parameters are passed through
 *                      to the customer back-end server, the values are neither validated nor handled by LC.
 * @see LegicNeonFileEventListener
 */
- (void)requestAddFile:(LegicMobileSdkNeonFile* _Nonnull const)file
            parameters:(NSArray< LegicMobileSdkNeonFileParameter* >* _Nullable const)parameters
NS_SWIFT_NAME(requestAddFile(_:parameters:));

/**
 * Informs LC that the user requests the removal of a currently deployed LEGIC neon file.
 *
 * @param file  LEGIC neon file that shall be removed (requested by the user)
 * @see LegicNeonFileEventListener
 */
- (void)requestRemoveFile:(LegicMobileSdkNeonFile* _Nonnull const)file
NS_SWIFT_NAME(requestRemoveFile(_:));

/**
 * Gets the list of all files, despite the current file state.
 * @return  List of all files.
 * @throws LegicMobileSdkError  if any error occurs during getting the files.
 */
- (NSArray< LegicMobileSdkNeonFile* >* _Nullable const)getAllFiles:(NSError* _Nullable __autoreleasing * _Nullable)error
NS_SWIFT_NAME(getAllFiles());

/**
 * Returns the list of all known files which have a certain file state.
 *
 * @param fileState State value to filter the files
 * @return  List of all files with the requested state.
 * @throws LegicMobileSdkError  if any error occurs during getting the files.
 */
- (NSArray< LegicMobileSdkNeonFile* >* _Nullable const)getAllFilesWithState:(E_LegicMobileSdkNeonFileState)fileState
																	  error:(NSError* _Nullable __autoreleasing * _Nullable)error
NS_SWIFT_NAME(getAllFilesWithState(_:));

/**
 * Activates a specific file. By activating a file, it gets accessible<br>
 * by a LEGIC reader chip via the registered interfaces.
 *
 * @param file  File to be activated
 * @throws LegicMobileSdkError  if any error occurs during activating the file.
 */
- (BOOL)activateFile:(LegicMobileSdkNeonFile* _Nonnull const)file
               error:(NSError* _Nullable __autoreleasing * _Nullable)error
NS_SWIFT_NAME(activateFile(_:));

/**
 * Deactivates a specific file. By deactivating a file, the file is no longer<br>
 * accessible for the LEGIC reader chip
 *
 * @param file  File to be deactivated
 * @throws LegicMobileSdkError  if any error occurs during deactivating the file.
 */
- (BOOL)deactivateFile:(LegicMobileSdkNeonFile* _Nonnull const)file
				 error:(NSError* _Nullable __autoreleasing * _Nullable)error
NS_SWIFT_NAME(deactivateFile(_:));

/**
 * Adds or removes a default marker on the given file, depending on the value parameter.<br>
 * Depending on the mode parameter, the passed file becomes the <code>"</code>LC mobile app<code>"</code> default file<br>
 * or the <code>"</code>LC project<code>"</code> default file. The default files can be selected as follows:<br>
 * <ul>
 *     <li>MOBILE_APP_DEFAULT files can be selected with project ID and file ID consisting of all zeros (16 bytes).</li>
 *     <li>LC_PROJECT_DEFAULT files can be selected with the project ID (first 4 bytes) followed by zeros for the file ID (12 bytes).</li>
 * </ul>
 *
 * @param file  File that needs to be changed
 * @param mode  Mode to change (either <code>MOBILE_APP_DEFAULT</code> or <code>LC_PROJECT_DEFAULT</code>)
 * @param value <li><code>true</code>  if the mode shall be activated.</li>
 *              <li><code>false</code> if the mode shall be deactivated</li>
 * @throws LegicMobileSdkError  if any error occurs during changing the default marker.
 */
- (BOOL)setDefault:(LegicMobileSdkNeonFile* _Nonnull const)file
              mode:(E_LegicMobileSdkNeonFileDefaultMode)mode
             value:(BOOL)value
             error:(NSError* _Nullable __autoreleasing * _Nullable)error
NS_SWIFT_NAME(setDefault(file:mode:value:));

/**
 * Retrieves the current default status for the given file and mode.
 *
 * @param file  File to be queried
 * @param mode  Mode to check
 * @return   <li><code>true</code> if the file is marked as default file for the given mode.</li>
 *           <li><code>false</code> if the file is not marked as default file for the given mode.</li>
 */
- (BOOL)getIsDefault:(BOOL* _Nonnull)isDefault
				file:(LegicMobileSdkNeonFile* _Nonnull const)file
				mode:(E_LegicMobileSdkNeonFileDefaultMode)mode
			   error:(NSError* _Nullable __autoreleasing * _Nullable)error
NS_SWIFT_NAME(getIsDefault(isDefault:file:mode:));

/**
 * Allows to query whether an RF interface is supported by the platform.
 *
 * @param rfInterface   RF interface to be queried
 * @return  <li><code>true</code> if RF interface is supported.</li>
 *          <li><code>false</code> if RF interface is not supported.</li>
 * @throws LegicMobileSdkError  if any error occurs during checking the interface support.
 */
- (BOOL)getIsRfInterfaceSupported:(BOOL* _Nonnull)isSupported
					  rfInterface:(LegicMobileSdkRfInterface* _Nonnull)rfInterface
							error:(NSError* _Nullable __autoreleasing * _Nullable)error
NS_SWIFT_NAME(getIsRfInterfaceSupported(isSupported:rfInterface:));

/**
 * Allows to query the current setting of the RF interface status.<br>
 * The response depends on the status of the interface on operating system level<br>
 * (can be influenced by the user, e.g. by switching BLE off).
 *
 * @param rfInterface   RF interface to be queried
 * @return  <li><code>true</code> if RF interface has been enabled by the user.</li>
 *          <li><code>false</code> if RF interface has not been enabled by the user.</li>
 * @throws LegicMobileSdkError  if any error occurs during checking the interface state.
 */
- (BOOL)getIsRfInterfaceHardwareEnabled:(BOOL* _Nonnull)isEnabled
							rfInterface:(LegicMobileSdkRfInterface* _Nonnull const)rfInterface
								  error:(NSError* _Nullable __autoreleasing * _Nullable)error
NS_SWIFT_NAME(getIsRfInterfaceHardwareEnabled(isEnabled:rfInterface:));

/**
 * Allows to query the current status of the RF interface within the mobile app.<br>
 * The status can be changed by calling activateRfInterface or deactivateRfInterface.
 *
 * @param rfInterface RF interface to be queried
 * @return  <li><code>true</code> if RF interface has been activated in the mobile app.</li>
 *          <li><code>false</code> if RF interface has not been activated in the mobile app.</li>
 * @throws LegicMobileSdkError if any error occurs during checking the interface activation state.
 */
- (BOOL)getIsRfInterfaceActive:(BOOL* _Nonnull)isActive
				   rfInterface:(LegicMobileSdkRfInterface* _Nonnull const)rfInterface
						 error:(NSError* _Nullable __autoreleasing * _Nullable)error
NS_SWIFT_NAME(getIsRfInterfaceActive(isActive:rfInterface:));

/**
 * Activates the requested RF interface on the mobile app.<br>
 * RF interfaces can only be activated after successful registration,<br>
 * and only if the corresponding interface was requested during initiateRegistration call.
 *
 * @throws LegicMobileSdkError  if any error occurs during the interface activation process.
 * @see LegicMobileSdkEventListener
 */
- (BOOL)activateRfInterface:(LegicMobileSdkRfInterface* _Nonnull const)rfInterface
                      error:(NSError* _Nullable __autoreleasing * _Nullable)error
NS_SWIFT_NAME(activateRfInterface(_:));

/**
 * Deactivate the requested RF interface on the mobile app.<br>
 * RF interfaces can only be deactivated after successful registration,<br>
 * and only if the corresponding interface was requested during initiateRegistration call.
 *
 * @throws LegicMobileSdkError  if any error occurs during the interface deactivation process.
 * @see LegicMobileSdkEventListener
 */
- (BOOL)deactivateRfInterface:(LegicMobileSdkRfInterface* _Nonnull const)rfInterface
                        error:(NSError* _Nullable __autoreleasing * _Nullable)error
NS_SWIFT_NAME(deactivateRfInterface(_:));

/**
 * Sends a message to the host system (via the LEGIC reader chip) using the LC message channel.
 *
 * @param lcMessage     Message to transmit to host system (via the reader chip).
 * @param mode          The message is sent via the given mode.
 *                      Usually, mode and interface correspond with the previously received message.
 * @param rfInterface   The message is sent via the given interface.
 *                      Usually, mode and interface correspond with the previously received message.
 * @throws LegicMobileSdkError  if any error occurs during the message transmission.
 * @see LegicReaderEventListener
 * @see
 * <p>
 * The message can be arbitrary formatted as this is a contract between
 * the host system (connected to the reader) and the mobile app.
 * The message is transported as-is, no validation takes place.
 * The message can be send encrypted or plain.
 * LcMessageMode parameter controls how the message should be sent/received by the SDK/reader
 * </p>
 */
- (BOOL)sendLcMessage:(NSData* _Nonnull const)lcMessage
                 mode:(E_LegicMobileSdkLcMessageMode)mode
          rfInterface:(LegicMobileSdkRfInterface* _Nonnull const)rfInterface
                error:(NSError* _Nullable __autoreleasing * _Nullable)error
NS_SWIFT_NAME(sendLcMessage(_:mode:rfInterface:));

/**
 * Sends a message to a LEGIC Connect Project, where the file belongs to.
 * @param lcMessage     Message to transmit to the LEGIC Connect Project.
 * @param file          The file points to the project intended for the message.
 * @throws LegicMobileSdkError  if any error occurs during the message transmission.
 * <p>
 * The message is sent plain.
 * </p>
 */
- (BOOL)sendLcMessageThroughLcProject:(NSData* _Nonnull const)lcMessage
                                 file:(LegicMobileSdkNeonFile* _Nullable  const) file
                                error:(NSError* _Nullable __autoreleasing * _Nullable)error

NS_SWIFT_NAME(sendLcMessageThroughLcProject(_:file:));

/**
 * Sends a message the registered LEGIC Connect Mobile App.
 * @param lcMessage     Message to transmit to the LEGIC Connect Mobile App.
 * @throws LegicMobileSdkError  if any error occurs during the message transmission.
 * <p>
 * The message is sent plain.
 * </p>
 */
- (BOOL)sendLcMessageThroughLcMobileApp:(NSData* _Nonnull const)lcMessage
                             error:(NSError* _Nullable __autoreleasing * _Nullable)error

NS_SWIFT_NAME(sendLcMessageThroughLcMobileApp(_:));


/**
 * Allows to query how many messages are queued for the backend.
 *
 * @return Number of queued messages for the backend.
 * @throws LegicMobileSdkError  if any error occurs during counting the messages.
 */
- (NSNumber*  _Nullable const)getNumberOfLcMessagesForBackend:(NSError* _Nullable __autoreleasing * _Nullable)error
NS_SWIFT_NAME(getNumberOfLcMessagesForBackend());


/**
 * Sends an entered password back to the host system (via the LEGIC reader chip) using the LC message channel.
 *
 * @param password  Password to transmit to host system (via the reader chip).
 * @throws LegicMobileSdkError  if any error occurs during the password transmission.
 * @see LegicMobileSdkPasswordEventListener
 * @see
 * <p>
 * The mode to transmit the password is predefined (always <code>ENCRYPTED_MACED_FILE_KEYS</code>),
 * therefore an authenticated session is required.
 * </p>
 */
- (BOOL)sendPassword:(NSData* _Nonnull const)password
         rfInterface:(LegicMobileSdkRfInterface* _Nonnull const)rfInterface
               error:(NSError* _Nullable __autoreleasing * _Nullable)error
NS_SWIFT_NAME(sendPassword(_:rfInterface:));

/**
 * Passes a push token to LEGIC Connect.<br>
 * This token is required/used to notify the mobile app about pending operations.<br>
 * This function can be used to set or update the push token after registration with the back-end.
 *
 * @param pushToken New or updated push token that needs to be sent to LEGIC Connect
 * @param pushType  Type of push token provided (depends on project used to register)
 * @throws LegicMobileSdkError  if any error occurs during the pushToken transmission.
 */
- (BOOL)setPushToken:(NSData* _Nullable const)pushToken
            pushType:(E_LegicMobileSdkPushType)pushType
               error:(NSError* _Nullable __autoreleasing * _Nullable)error
NS_SWIFT_NAME(setPushToken(_:pushType:));

/**
 * Handles received push messages from Apple Push Notification Service (APNS).<br>
 * If the push message contains a certain key/value pair which is set by LC,<br>
 * the SDK starts synchronizing with the back-end.
 *
 * @param userInfo    UserInfo received with push notification must be passed as parameter
 * @throws LegicMobileSdkError  if any error occurs during the handling of the push message.
 */
- (BOOL)handlePushMessage:(NSDictionary* _Nonnull const)userInfo
                    error:(NSError* _Nullable __autoreleasing * _Nullable)error
NS_SWIFT_NAME(handlePushMessage(userInfo:));

/**
 * Excludes the internal data from backup.
 * The internally stored data is included in the backup by default (for the current device only),
 * but can be excluded if desired.
 * @param exclude	should the internal data be excluded or included in the backup?
 */
- (BOOL)excludeFromBackup:(BOOL)exclude
					error:(NSError* _Nullable __autoreleasing * _Nullable)error
NS_SWIFT_NAME(excludeFromBackup(_:));


/**
 * Registers a listener to receive callbacks whenever a LEGIC neon file related operation occurs in the SDK.
 *
 * @param delegate  Delegate to receive events regarding LEGIC neon file operations
 * @throws LegicMobileSdkError  if any error occurs during the registration of the listener.
 * @see LegicNeonFileEventListener
 */
- (BOOL)registerForFileEvents:(id<LegicMobileSdkNeonFileEventDelegate> _Nonnull)delegate
                        error:(NSError* _Nullable __autoreleasing * _Nullable)error
NS_SWIFT_NAME(registerForFileEvents(delegate:));

/**
 * Removes a previously registered listener from the SDK.<br>
 * Callbacks for file related events will no longer occur.
 *
 * @param delegate  Delegate that shall be removed from the SDK <code>LegicNeonFileEventListener</code> list.
 * @see LegicNeonFileEventListener
 */
-(void)unregisterForFileEvents:(id<LegicMobileSdkNeonFileEventDelegate> _Nonnull)delegate
NS_SWIFT_NAME(unregisterForFileEvents(delegate:));

/**
 * Registers a listener to receive callbacks whenever a LEGIC reader chip related operation occurs in the SDK.
 *
 * @param delegate  Delegate to receive events regarding reader chip operations
 * @throws LegicMobileSdkError    if any error occurs during the registration of the listener.
 * @see LegicReaderEventListener
 */
- (BOOL)registerForReaderEvents:(id<LegicMobileSdkReaderEventDelegate> _Nonnull)delegate
                          error:(NSError* _Nullable __autoreleasing * _Nullable)error
NS_SWIFT_NAME(registerForReaderEvents(delegate:));

/**
 * Removes a previously registered listener from the SDK.<br>
 * Callbacks for reader chip related events will no longer occur.
 *
 * @param delegate  Delegate that shall be removed from the SDK <code>LegicReaderEventListener</code> list.
 * @see LegicReaderEventListener
 */
- (void)unregisterForReaderEvents:(id<LegicMobileSdkReaderEventDelegate> _Nonnull)delegate
NS_SWIFT_NAME(unregisterForReaderEvents(delegate:));

/**
 * Registers a delegate to receive callbacks whenever a registration related operation occurs in the SDK.
 *
 * @param delegate  Delegate to receive events regarding registration related operations.
 * @throws LegicMobileSdkError  if any error occurs during the registration of the listener.
 * @see LegicMobileSdkRegistrationEventListener
 */
- (BOOL)registerForRegistrationEvents:(id<LegicMobileSdkRegistrationEventDelegate> _Nonnull)delegate
                                error:(NSError* _Nullable __autoreleasing * _Nullable)error
NS_SWIFT_NAME(registerForRegistrationEvents(delegate:));

/**
 * Removes a previously registered delegate from the SDK.<br>
 * Callbacks for registration related events will no longer occur.
 *
 * @param delegate  Delegate that shall be removed from the SDK <code>LegicMobileSdkRegistrationEventListener</code> list.
 * @see LegicMobileSdkRegistrationEventListener
 */
- (void)unregisterForRegistrationEvents:(id<LegicMobileSdkRegistrationEventDelegate> _Nonnull)delegate
NS_SWIFT_NAME(unregisterForRegistrationEvents(delegate:));

/**
 * Registers a delegate to receive callbacks whenever a SDK related operation occurs in the SDK.
 *
 * @param delegate  Delegate to receive events regarding SDK operations.
 * @throws LegicMobileSdkError  if any error occurs during the registration of the listener.
 * @see LegicMobileSdkEventListener
 */
- (BOOL)registerForSdkEvents:(id<LegicMobileSdkEventDelegate> _Nonnull)delegate
                       error:(NSError* _Nullable __autoreleasing * _Nullable)error
NS_SWIFT_NAME(registerForSdkEvents(delegate:));

/**
 * Removes a previously registered delegate from the SDK.<br>
 * Callbacks for SDK related events will no longer occur.
 *
 * @param delegate  Delegate that shall be removed from the SDK <code>LegicMobileSdkEventListener</code> list.
 * @see LegicMobileSdkEventListener
 */
- (void)unregisterForSdkEvents:(id<LegicMobileSdkEventDelegate> _Nonnull)delegate
NS_SWIFT_NAME(unregisterForSdkEvents(delegate:));

/**
 * Registers a delegate to receive callbacks whenever a synchronization related event occurs in the SDK.
 *
 * @param delegate  Delegate to receive events regarding synchronization related operations.
 * @throws LegicMobileSdkError  if any error occurs during the registration of the listener.
 * @see LegicMobileSdkSynchronizeEventListener
 */
- (BOOL)registerForSynchronizeEvents:(id<LegicMobileSdkSynchronizeEventDelegate> _Nonnull)delegate
                               error:(NSError* _Nullable __autoreleasing * _Nullable)error
NS_SWIFT_NAME(registerForSynchronizeEvents(delegate:));

/**
 * Removes a previously registered listener from the SDK.<br>
 * Callbacks for synchronization related events will no longer occur.
 *
 * @param delegate  Delegate that shall be removed from the SDK <code>LegicMobileSdkSynchronizeEventListener</code> list.
 * @see LegicMobileSdkSynchronizeEventListener
 */
- (void)unregisterForSynchronizeEvents:(id<LegicMobileSdkSynchronizeEventDelegate> _Nonnull)delegate
NS_SWIFT_NAME(unregisterForSynchronizeEvents(delegate:));

/**
 * Registers a listener to receive callbacks whenever a password related operation occurs in the SDK.
 *
 * @param delegate  Delegate to receive events regarding password related operations.
 * @throws LegicMobileSdkError  if any error occurs during the registration of the listener.
 * @see LegicMobileSdkPasswordEventListener
 */
- (BOOL)registerForPasswordEvents:(id<LegicMobileSdkPasswordEventDelegate> _Nonnull)delegate
                            error:(NSError* _Nullable __autoreleasing * _Nullable)error
NS_SWIFT_NAME(registerForPasswordEvents(delegate:));

/**
 * Removes a previously registered listener from the SDK.<br>
 * Callbacks for password related events will no longer occur.
 *
 * @param delegate  Delegate that shall be removed from the SDK <code>LegicMobileSdkPasswordEventListener</code> list.
 * @see LegicMobileSdkPasswordEventListener
 */
- (void)unregisterForPasswordEvents:(id<LegicMobileSdkPasswordEventDelegate> _Nonnull)delegate
NS_SWIFT_NAME(unregisterForPasswordEvents(delegate:));

/**
 * Removes a previously registered listener from the SDK.<br>
 * Callbacks of any kind will no longer occur.
 * @param delegate  Delegate that shall be removed from all SDK event listener lists.
 * @see LegicMobileSdkBaseEventListener
 */
- (void)unregisterAnyEvents:(id _Nonnull)delegate
NS_SWIFT_NAME(unregisterAnyEvents(delegate:));

@end
