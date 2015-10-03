//
//  koalaAppController.h
//  koala
//
//  Created by Avner Peled on 12/3/11.
//  Copyright EpiThoughts 2011. All rights reserved.
//

@class RootViewController;

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate> {
    UIWindow *window;
    RootViewController	*viewController;
}

@end

