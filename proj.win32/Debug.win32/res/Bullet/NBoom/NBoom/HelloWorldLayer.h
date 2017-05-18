//
//  HelloWorldLayer.h
//  NBoom
//
//  Created by karaki on 12-11-28.
//  Copyright keydons 2012年. All rights reserved.
//


#import <GameKit/GameKit.h>

// When you import this file, you import all the cocos2d classes
#import "cocos2d.h"
#import "CCParticleSystemQuad.h"
// HelloWorldLayer

#define EMITTER_COUNT 30
@interface HelloWorldLayer : CCLayer{
  CCParticleSystemQuad *emitter_[EMITTER_COUNT];
  int mass_[EMITTER_COUNT];
  float windForce_;
  bool ranBefore_;
  CCSprite *box_;
}

// returns a CCScene that contains the HelloWorldLayer as the only child
+(CCScene *) scene;


@end
