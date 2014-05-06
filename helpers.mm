//
//  helpers.mm
//  FlappingBird
//
//  Created by C0deH4cker on 5/5/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "helpers.h"
#include <Foundation/Foundation.h>

std::string resourcePath() {
	std::string ret;
	
	@autoreleasepool {
		NSBundle* bundle = [NSBundle mainBundle];
		if(bundle) {
			NSString* path = [bundle resourcePath];
			ret = [path UTF8String] + std::string("/");
		}
	}
    
    return ret;
}

