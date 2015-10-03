#include "AgentFactory.h"
#include "ichigo.h"

#include "States/DirectorMainState.h"

#include "Agents/DreamKoala.h"
#include "Agents/EnergyGauge.h"
#include "Agents/Office.h"
#include "Agents/Item.h"
#include "Agents/Tree.h"

#include "States/KoalaSwitchState.h"
#include "States/DreamKoalaStandState.h"
#include "States/DreamKoalaWalkState.h"
#include "States/DreamKoalaLiftState.h"
#include "States/DreamKoalaDoorState.h"
#include "States/OfficeMgrState.h"
#include "States/OfficeStretchingState.h"
#include "States/EnergyGaugeDecliningState.h"
#include "States/ItemOnTableState.h"
#include "States/ItemDragState.h"
#include "States/NatureDefaultState.h"
#include "States/BeetleSwarmClimbingState.h"
#include "States/BeetleSwarmEatingState.h"


#include "CocosDirectorView.h"
#include "CocosSceneView.h"
#include "CocosLayerView.h"
#include "CocosColorLayerView.h"
#include "CocosActorView.h"
#include "CocosSpriteActorView.h"
#include "CocosClippedActorView.h"
#include "CocosTileMapView.h"
#include "CocosLabelView.h"
#include "CocosLuaScriptingEngine.h"


namespace ichigo
{
    Agent *AgentFactory::createAgent(std::string type)
    {
        if (type == "Director")
        {
            Director *director = Director::getInstance();
            
            // Game's view layer
            director->setView(new CocosDirectorView(director));
                        
            // Scripting engine
            director->setScriptingEngine(new CocosLuaScriptingEngine());
            
            // A Main Director state            
            director->getFSM()->addState(new koala::DirectorMainState(), true);
                        
            return director;
        }
        else if (type == "MainScene")
        {
            Scene *scene = new Scene();
            scene->setView(new CocosSceneView(scene));            
            
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
        else if (type == "RealityLayer")
        {
            Layer *layer = new Layer();
            layer->setView(new CocosColorLayerView(layer));
                       
            return layer;
        }
        else if (type == "KoalaOverlay")
        {
            Layer *layer = new Layer();
            layer->setView(new CocosLayerView(layer));
            
            layer->getFSM()->addState(new koala::KoalaSwitchState(), true);
            
            return layer;
        }
        else if (type == "Sprite")
        {
            Actor *sprite = new Actor();            
            sprite->setView(new CocosSpriteActorView(sprite));
            
            return sprite;
        }
        else if (type == "DreamKoala")
        {
            koala::DreamKoala *koala = new koala::DreamKoala();
            
            CocosSpriteActorView *view = new CocosSpriteActorView(koala);
            koala->setView(view);
            
            koala->getFSM()->addState(new koala::DreamKoalaStandState(), true);
            koala->getFSM()->addState(new koala::DreamKoalaWalkState(), false);
            koala->getFSM()->addState(new koala::DreamKoalaLiftState(), false);
            koala->getFSM()->addState(new koala::DreamKoalaDoorState(), false);
            
            return koala;
        }
        else if (type == "OfficeMap")
        {
            koala::Office *office = new koala::Office();
            office->setView(new CocosActorView(office));
            
            office->getFSM()->addState(new koala::OfficeMgrState(), true);
            koala::OfficeStretchingState *stretchingState = new koala::OfficeStretchingState();
            office->getFSM()->addState(stretchingState, false);
            
            return office;
        }
        else if (type == "AreaMap")
        {
            Actor *area = new Actor();
            area->setView(new CocosTileMapView(area));
            
            return area;
        }
        else if (type == "Tree")
        {
            koala::Tree *tree = new koala::Tree();
            tree->setView(new CocosTileMapView(tree));
                        
            return tree;
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
        else if (type == "Label")
        {
            ichigo::Actor *label = new ichigo::Actor();
            ichigo::LabelState *labelState = new ichigo::LabelState();
            label->setView(new CocosLabelView(label));
            
            label->getFSM()->addState(labelState, true);                        

            
            return label;
        }
        else if (type == "Item")
        {
            koala::Item *item = new koala::Item();
            CocosSpriteActorView *view = new CocosSpriteActorView(item);
            item->setView(view);
            
            item->getFSM()->addState(new koala::ItemOnTableState(), true);
            item->getFSM()->addState(new koala::ItemDragState(), false);
            
            return item;
        }
        else if (type == "EnergyGauge") 
        {
            koala::EnergyGauge *energyGauge = new koala::EnergyGauge();
            
            CocosClippedActorView *view = new CocosClippedActorView(energyGauge);
            energyGauge->setView(view);
            
            energyGauge->getFSM()->addState(new koala::EnergyGaugeDecliningState(), true);
            
            return energyGauge;
        }
        else if (type == "Nature") 
        {
            koala::Nature *nature = new koala::Nature();            
            nature->getFSM()->addState(new koala::NatureDefaultState(), true);            
            nature->setView(new CocosActorView(nature));
            
            return nature;
        }
        else if (type == "BeetleSwarm") 
        {
            koala::BeetleSwarm *swarm = new koala::BeetleSwarm();       
            swarm->setView(new CocosSpriteActorView(swarm));     
            swarm->getFSM()->addState(new koala::BeetleSwarmEatingState(), false);
            swarm->getFSM()->addState(new koala::BeetleSwarmClimbingState(), true);
            
            return swarm;
        }

        // Else
        return NULL;
    }
}
