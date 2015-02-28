//
//  ASDAppDelegate.h
//  RemoteSpotify
//
//  Created by Alex Schimp on 2/3/14.
//  Copyright (c) 2014 Alex Schimp. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ASDMainViewController.h"
#import "ASDPlaybackManager.h"
#import "CocoaLibSpotify.h"
#import "RFduino.h"
#import "RFduinoManagerDelegate.h"

@interface ASDAppDelegate : UIResponder <UIApplicationDelegate, SPSessionDelegate>

@property (strong, nonatomic) UIWindow *window;
@property (strong, nonatomic) ASDMainViewController *mainViewController;

@end
