#include "AgentFactory.h"
#include "ichigo.h"

#include "Item.h"
#include "DreamKoala.h"
#include "Office.h"
#include "States/MenuState.h"
#include "States/DirectorRunningState.h"
#include "States/CharacterStandingState.h"
#include "States/CharacterJumpingState.h"
#include "States/SafeIdleState.h"
#include "States/SafeActiveState.h"
#include "States/KoalaSwitchState.h"

#include "CocosDirectorView.h"
#include "CocosSceneView.h"
#include "CocosLayerView.h"
#include "CocosSpriteActorView.h"
#include "CocosTileMapView.h"
#include "CocosLuaScriptingEngine.h"


namespace ichigo
{
    Agent *AgentFactory::createAgent(std::string type)
    {
        if (type == "Director")
        {
            Director *director = Director::getInstance();
            director->setView(new CocosDirectorView(director));
            director->setScriptingEngine(new CocosLuaScriptingEngine());
            
            director->getFSM()->addState(new it::DirectorRunningState(), true);
            
            return director;
        }
        else if (type == "MenuScene")
        {
            Scene *scene = new Scene();
            scene->setView(new CocosSceneView(scene));
            
            scene->getFSM()->addState(new it::MenuState(), true);
            
            return scene;
        }
        else if (type == "MultitouchScene")
        {
            Scene *scene = new Scene();
            scene->setView(new CocosSceneView(scene));
            
            scene->getFSM()->addState(new StretchableState(), true);
            StretchingState *stretchingState = new StretchingState();
            stretchingState->setScaleLimits(6.0f, 0.2f);
            scene->getFSM()->addState(stretchingState, false);
            
            return scene;
        }
        else if (type == "ScrollingScene")
        {
            Scene *scene = new Scene();
            scene->setView(new CocosSceneView(scene));
            
            scene->getFSM()->addState(new DraggableState(), true);
            DraggingState *draggingState = new DraggingState();
            draggingState->setPositionBounds(-230, 310, -10, 105);
            scene->getFSM()->addState(draggingState, false);
            
            return scene;
        }
        else if (type == "KoalaScene")
        {
            Scene *scene = new Scene();
            scene->setView(new CocosSceneView(scene));
            
            return scene;
        }
        else if (type == "MainLayer")
        {
            Layer *layer = new Layer();
            layer->setView(new CocosLayerView(layer));
            
            return layer;
        }
        else if (type == "KoalaOverlay")
        {
            Layer *layer = new Layer();
            layer->setView(new CocosLayerView(layer));
            
            layer->getFSM()->addState(new it::KoalaSwitchState(), true);
            
            return layer;
        }
        else if (type == "Sprite")
        {
            Actor *sprite = new Actor();
            
            CocosSpriteActorView *view = new CocosSpriteActorView(sprite);
            sprite->setView(view);
            
            return sprite;
        }
        else if (type == "Item")
        {
            it::Item *item = new it::Item();

            CocosSpriteActorView *view = new CocosSpriteActorView(item);
            item->setView(view);
            
            item->getFSM()->addState(new StretchableState(), true);
            StretchingState *stretchingState = new StretchingState();
            stretchingState->setScaleLimits(2.0f, 0.15f);
            item->getFSM()->addState(stretchingState, false);
            
            return item;
        }
        else if (type == "Tzahi")
        {
            Actor *tzahi = new Actor();
            
            CocosSpriteActorView *view = new CocosSpriteActorView(tzahi);
            tzahi->setView(view);
            
            tzahi->getFSM()->addState(new it::CharacterStandingState(), true);
            tzahi->getFSM()->addState(new it::CharacterJumpingState(), false);
            
            return tzahi;
        }
        else if (type == "DreamKoala")
        {
            it::DreamKoala *koala = new it::DreamKoala();
            
            CocosSpriteActorView *view = new CocosSpriteActorView(koala);
            koala->setView(view);
            
            return koala;
        }
        else if (type == "Safe")
        {
            Actor *safe = new Actor();
            
            CocosSpriteActorView *view = new CocosSpriteActorView(safe);
            safe->setView(view);
            
            safe->getFSM()->addState(new it::SafeIdleState(), true);
            safe->getFSM()->addState(new it::SafeActiveState(), false);
            
            return safe;
        }
        else if (type == "Eucalyptus")
        {
            Actor *eucalyptus = new Actor();
            
            CocosSpriteActorView *view = new CocosSpriteActorView(eucalyptus);
            eucalyptus->setView(view);
            
            eucalyptus->getFSM()->addState(new StretchableState(), true);
            StretchingState *stretchingState = new StretchingState(true, true, false);
            stretchingState->setScaleLimits(1.0f, 0.75f);
            stretchingState->setTranslateLimits(true, 160, 320, 80, 240);
            stretchingState->setTranslateLimits(false, 240, 240, 140, 180);
            eucalyptus->getFSM()->addState(stretchingState, false);
            
            return eucalyptus;
        }
        else if (type == "OfficeMap")
        {
            it::Office *office = new it::Office();
            office->setView(new CocosTileMapView(office));
                        
            return office;
        }
        else if (type == "Button")
        {
            Actor *button = new Actor();
            
            CocosSpriteActorView *view = new CocosSpriteActorView(button);
            button->setView(view);
            
            ButtonState *buttonState = new ButtonState();
            buttonState->setUpAnimation("up");
            buttonState->setDownAnimation("down");
            button->getFSM()->addState(buttonState, true);
            
            return button;
        }

        // Else
        return NULL;
    }
}
