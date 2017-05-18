//
//  HelloWorldLayer.m
//  NBoom
//
//  Created by karaki on 12-11-28.
//  Copyright keydons 2012年. All rights reserved.
//
#define SOLID_SHARD_MASS      100
#define SMOKE_PARTICLE_MASS   1
#define FIRESTAR_MASS         10

// Import the interfaces
#import "HelloWorldLayer.h"

// Needed to obtain the Navigation Controller
#import "AppDelegate.h"

#pragma mark - HelloWorldLayer

// HelloWorldLayer implementation

@implementation HelloWorldLayer

// Helper class method that creates a Scene with the HelloWorldLayer as the only child.
+(CCScene *) scene
{
	CCScene *scene = [CCScene node];
	
	HelloWorldLayer *layer = [HelloWorldLayer node];
  [scene addChild: layer z:2 ];
  CGSize size = [[CCDirector sharedDirector] winSize];
  CCSprite *bg=[CCSprite spriteWithFile:@"bg.png"];
  bg.position=ccp(size.width/2,size.height/2);
  [scene addChild: bg z:0];
  
  CCSprite *btn=[CCSprite spriteWithFile:@"button.png"];
  CCSprite *btnp=[CCSprite spriteWithFile:@"buttonPressed.png"];
  CCMenuItemSprite *item1=[CCMenuItemSprite itemWithNormalSprite:btn selectedSprite:btnp target:layer selector:@selector(item1:)];
  CCMenu *menu =[CCMenu menuWithItems:item1, nil];
  menu.position=ccp(size.width / 2 ,  50 );
  [scene addChild:menu z:1 tag:2];
  
	return scene;
}
-(void)item1:(id)sender{
  NSLog(@"item1");
  [self boom];
  
}

-(id) init{
	if(self=[super init]) {
    CCLabelTTF *label=[CCLabelTTF labelWithString:@"NBoom by zerg3587" fontName:@"Arial" fontSize:20];
    [label setColor:ccc3(0, 0, 0)];
		CGSize size = [[CCDirector sharedDirector] winSize];
		label.position =  ccp( 95, size.height-10);
		[self addChild:label z:10];
    

	}
	return self;
}

-(void)onEnter{
  NSLog(@"(  ⨂ o⨂) |<-------KEEP DISTANCE------->|BOOM!");
  [super onEnter];
  [self setBox];

}


-(void)boom{
  NSLog(@"BOOM!");
  int q =arc4random()%12000;
  windForce_=q-6000;
  
  NSLog(@"WindForce=%f,q=%d",windForce_,q);
  if(ranBefore_)
  {
    for (int i=0; i<EMITTER_COUNT; i++)
    {
      [self setWindAcc:emitter_[i] n:i];      
      [emitter_[i] resetSystem];
    }
  }
  else
  {
    [self solidExplosion];
    [self fireExplosion];
    [self smoke];
    ranBefore_=YES;
    NSLog(@"particle init");
  }
  [self removeChildByTag:998];
  [self scheduleOnce:@selector(setBox) delay:4];
}

-(void)setBox{
  NSLog(@"adding box");
  CGSize size = [[CCDirector sharedDirector] winSize];  
  box_ =[CCSprite spriteWithFile:@"box.png"];
  box_.position=ccp(size.width/2,size.height*2/5);
  [self addChild:box_ z:0 tag:998];
}

-(void)setWindAcc:(CCParticleSystemQuad *)emitter n:(int)n{
  
  emitter.gravity=ccp(windForce_/mass_[n],emitter.gravity.y);
}

-(void)solidExplosion{
  
  CGSize size=[[CCDirector sharedDirector]winSize];
  //  float acc_windx= [self setWindForce:SOLID_SHARD_MASS];
  
  //n = 0 to 20 , 21 in total
  for (int i=0; i<3; i++) {
    int n=i*7;
    
    emitter_[n+0] = [CCParticleSystemQuad particleWithTotalParticles:20-i*8];
    emitter_[n+1] = [CCParticleSystemQuad particleWithTotalParticles:20-i*8];
    emitter_[n+2] = [CCParticleSystemQuad particleWithTotalParticles:15-i*7];
    emitter_[n+3] = [CCParticleSystemQuad particleWithTotalParticles:2-i];
    emitter_[n+4] = [CCParticleSystemQuad particleWithTotalParticles:15-i*7];
    emitter_[n+5] = [CCParticleSystemQuad particleWithTotalParticles:20-i*8];
    emitter_[n+6] = [CCParticleSystemQuad particleWithTotalParticles:1800-i*800];
    
    emitter_[n+0].texture=[[CCTextureCache sharedTextureCache]addImage:@"tri1.png"];
    emitter_[n+1].texture=[[CCTextureCache sharedTextureCache]addImage:@"tri2.png"];
    emitter_[n+2].texture=[[CCTextureCache sharedTextureCache]addImage:@"tri3.png"];
    emitter_[n+3].texture=[[CCTextureCache sharedTextureCache]addImage:@"rect1.png"];
    emitter_[n+4].texture=[[CCTextureCache sharedTextureCache]addImage:@"rect2.png"];
    emitter_[n+5].texture=[[CCTextureCache sharedTextureCache]addImage:@"shard2.png"];
    emitter_[n+6].texture=[[CCTextureCache sharedTextureCache]addImage:@"round1.png"];
  }//n + 6 is dust
  
  for (int i=0; i<3; i++) {
    for(int j = 0;j<7;j++){
      int n=i*7+j;
      emitter_[n].life           = 1.5;
      emitter_[n].lifeVar        = 0.5;
      emitter_[n].startSize      = 20+i*3;
      emitter_[n].startSizeVar   = 15+i*3;
      emitter_[n].endSizeVar     = 15+i*3;
      emitter_[n].angle          = 90;
      emitter_[n].angleVar       = 90;
      //
      emitter_[n].emitterMode    = kCCParticleModeGravity;
      
      emitter_[n].duration       = 0.01;
      emitter_[n].speed          = 400+i*100;
      emitter_[n].speedVar       = 400+i*100;
      emitter_[n].gravity        = ccp(0, -400);
      mass_[n]=SOLID_SHARD_MASS;
      [self setWindAcc:emitter_[n]n:n];
      emitter_[n].radialAccelVar = 400+i*100;
      emitter_[n].tangentialAccelVar = 100;
      emitter_[n].emissionRate   = 5000;
      emitter_[n].startSpin      = -200;
      emitter_[n].startSpinVar   = 1000;
      emitter_[n].endSpin        = -200;
      emitter_[n].endSpinVar     = 400;
      //
      
      emitter_[n].position       = ccp(size.width/2,size.height*2/5);
      emitter_[n].posVar         = ccp(120-i*30,80-i*20);
      emitter_[n].startColor     = ccc4f(0.4, 0.4, 0.4, 1);
      emitter_[n].endColor       = ccc4f(0.4, 0.4, 0.4, 0.6);
      
      emitter_[n].blendAdditive  = NO;
      
      [self addChild:emitter_[n] z:i*3];//0 && 3 && 6
    }
  }
  
  //special property for dust
  for (int i =0; i<3; i++) {
    int n= i*7+6;
    emitter_[n].emissionRate   = 10000;
    emitter_[n].startSpin      = 0;
    emitter_[n].startSpinVar   = 0;
    emitter_[n].endSpin        = 0;
    emitter_[n].endSpinVar     = 0;
    emitter_[n].startSize      = 2;
    emitter_[n].startSizeVar   = 1;
    emitter_[n].endSize        = 1;
    emitter_[n].endSizeVar     = 0.5;
    emitter_[n].speedVar       = 1000+i*200;
    emitter_[n].gravity        = ccp(windForce_/FIRESTAR_MASS, -400);
    
  }
  
}

-(void)fireExplosion{
  //Exploding Fire
  CGSize size=[[CCDirector sharedDirector]winSize];
  //  float acc_windx=[self setWindForce: FIRESTAR_MASS];
  CCTexture2D *td=[[CCTextureCache sharedTextureCache]addImage:@"round6b1.png"];
  
  for (int i=0; i<2; i++) {
    int n =21+i;
    
    emitter_[n] = [CCParticleSystemQuad particleWithTotalParticles:100-i*50];
    emitter_[n].texture=td;
    emitter_[n].life           = 1.7+i*0.5;
    emitter_[n].lifeVar        = 0.5;
    emitter_[n].startSize      = 160+i*40;
    emitter_[n].startSizeVar   = 100+i*30;
    emitter_[n].endSize        = 360+i*60;
    emitter_[n].endSizeVar     = 180+i*40;
    emitter_[n].angle          = 90;
    emitter_[n].angleVar       = 180;
    //
    emitter_[n].emitterMode    = kCCParticleModeGravity;
    
    emitter_[n].duration       = 0.2;//0.08
    emitter_[n].speed          = 300;
    emitter_[n].speedVar       = 225;
    emitter_[n].gravity        = ccp(0, 200);
    mass_[n]=FIRESTAR_MASS;
    [self setWindAcc:emitter_[n]n:n];
    emitter_[n].radialAccel    = -450;
    emitter_[n].radialAccelVar = 50;
    emitter_[n].tangentialAccelVar = 100;
    emitter_[n].emissionRate   = 3000;
    
    
    emitter_[n].position       = ccp(size.width/2,size.height*2/5);
    emitter_[n].posVar         = ccp(100-i*50,70-i*40);
    emitter_[n].startSpinVar   = 300;
    emitter_[n].endSpinVar     =300;
    //    emitter[n].startColor=ccc4f(1.0, 1.0, 1, 1);
    emitter_[n].startColor     = ccc4f(   1,   0.7,   0,   1);
    emitter_[n].startColorVar  = ccc4f(0.05, 0.4, 0.3, 0.25);
    //
    emitter_[n].endColor       = ccc4f(0.5, 0.25, 0, 0.3);
    emitter_[n].endColorVar    = ccc4f(0, 0, 0, 0.2);
    
    
    [self addChild:emitter_[n] z:i*3+1];//1 and 4
  }
}


-(void)smoke{
  //SMOKE
  CGSize size=[[CCDirector sharedDirector]winSize];
  //  float acc_windx= [self setWindForce: FIRESTAR_MASS];
  CCTexture2D *td=[[CCTextureCache sharedTextureCache]addImage:@"round6b1.png"];
  
  for (int i=0; i<1; i++) {
    int n =23+i;
    
    emitter_[n] = [CCParticleSystemQuad particleWithTotalParticles:100-i*80];
    emitter_[n].texture=td;
    emitter_[n].life           = 3;
    emitter_[n].lifeVar        = 0.5;
    emitter_[n].startSize      = 280-i*100;
    emitter_[n].startSizeVar   = 80;
    emitter_[n].endSize        = 512;
    emitter_[n].endSizeVar     = 180;
    emitter_[n].angle          = 90;
    emitter_[n].angleVar       = 120;
    //
    emitter_[n].emitterMode    = kCCParticleModeGravity;
    
    emitter_[n].duration       = 1;//0.08
    emitter_[n].speed          = 0;
    emitter_[n].speedVar       = 2;
    emitter_[n].gravity        = ccp(0, 100);
    mass_[n]=FIRESTAR_MASS;
    [self setWindAcc:emitter_[n]n:n];
    emitter_[n].radialAccel    = -50;
    emitter_[n].radialAccelVar = 0;
    emitter_[n].tangentialAccelVar = 200;
    emitter_[n].emissionRate   = 100;
    
    
    emitter_[n].position       = ccp(size.width/2,size.height/2);
    emitter_[n].posVar         = ccp(100,50);
    emitter_[n].startColor     = ccc4f(0.1 ,0.1,0.1, 0.2);
    emitter_[n].startColorVar  = ccc4f(0   , 0  , 0  , 0.2);
    
    emitter_[n].endColor       = ccc4f(0.2 , 0.2, 0.2,  0 );
    emitter_[n].endColorVar    = ccc4f(0   , 0   ,  0, 0.4);
    
    
    [self addChild:emitter_[n] z:i*3+2];//2
  }
  
}



- (void) dealloc{
	[super dealloc];
}


@end
