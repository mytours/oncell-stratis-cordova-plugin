// -----------------------------------------------------------------------------
// Copyright© 2017 LEGIC® Identsystems AG, CH-8623 Wetzikon
// Confidential. All rights reserved!
// -----------------------------------------------------------------------------

#ifndef LegicMobileSdkRfInterface_h
#define LegicMobileSdkRfInterface_h

#import <Foundation/Foundation.h>

/**
 * Enum value to identify a RF interface.
 */
typedef NS_ENUM(NSInteger, E_LegicMobileSdkRfInterface) {
    /**
     * The interface identified is a Bluetooth (BLE) interface
     */
    E_LegicMobileSdkRfInterface_BLE = 0
    
} NS_SWIFT_NAME(E_RfInterface);

/**
 * Object that encapsulates E_LegicMobileSdkRfInterface so that it can be
 * used inside containers
 */
NS_SWIFT_NAME(RfInterface)
@interface LegicMobileSdkRfInterface : NSObject

- (instancetype _Nonnull)initWithValue:(E_LegicMobileSdkRfInterface)value;

/**
 * The interface identified is a Bluetooth (BLE) interface
 */
@property (readonly) E_LegicMobileSdkRfInterface value
NS_SWIFT_NAME(value);

/**
 * The interface identified is a Bluetooth (BLE) interface
 * @return an object that symbolizes a BLE value
 */
@property (class, readonly) LegicMobileSdkRfInterface* _Nonnull BLE
NS_SWIFT_NAME(BLE);

@end

#endif /* LegicMobileSdkRfInterface_h */
