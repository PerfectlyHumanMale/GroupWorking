/*#include <SFML/Graphics.hpp> 
#include <iostream>
#include <sstream>
#include <iostream>

using namespace sf;
using namespace std;

int main() {
    Sprite sprite;
    sprite = CCSprite::spriteWithFile("Tank.png");
    sprite->circularHealthSheet = CCSpriteBatchNode::batchNodeWithTexture(CCTextureCache::sharedTextureCache()->addImage("healthBar.png"), 24);

    for (int i = 0; i < 24; i++) {
        CCSprite* healthBarNode = CCSprite::spriteWithTexture(sprite->circularHealthSheet->getTexture(), CCRectMake(0, 0, 8, 70));
        // setting rotation for sprite so that the sprite is arranged in circular manner
        healthBarNode->setRotation(i * 15);
        sprite->circularHealthSheet->addChild(healthBarNode, 99);
    }
    sprite->circularHealthSheet->setPosition(ccp(sprite->getContentSize().width / 2, sprite->getContentSize().height / 2));
    sprite->addChild(sprite->circularHealthSheet);
}
CCArray* nodes = this->circularHealthSheet->getDescendants();

int nodesToDeleteInHealthCircle = nodes->count() * (1.0 - (float)currentHealth / (float)totalHealth);

// calculating the percentage of health remaining
float healthPercentage = ((float)currentHealth / (float)totalHealth) * 100;

int stage = 0;

// calculating the stage
if (healthPercentage > 75.0 && healthPercentage <= 100)
stage = 0;
else if (healthPercentage > 50.0 && healthPercentage <= 75.0)
stage = 1;
else if (healthPercentage > 25.0 && healthPercentage <= 50.0)
stage = 2;
else if (healthPercentage >= 0.0 && healthPercentage <= 25.0)
stage = 3;


for (int i = 0; icount(); i++) {
    CCSprite* tmp = (CCSprite*)nodes->objectAtIndex(i);

    if (i < barsToDeleteInHealthCircle)
        tmp->setTextureRect(CCRectMake(8, stage * 70, 8, 70));
    else
        tmp->setTextureRect(CCRectMake(0, stage * 70, 8, 70));
}

sprite->setRotation(rotationAngle);
circularHealthSheet->setRotation(-rotationAngle);*/