#include "scene.hpp"
#include "game.hpp"
#include "audio.hpp"
#include "toolbox.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

Scene::Scene(std::string n)
{
    scenetime = 0;
    aspect_ratio = 1.77; // 16:9 ratio
    name = n;
    initialized = false;
}

void Scene::work()
{
    scenetime++;

    game.getRenderWindow()->setView(*mainview);

    // Do things that the game does on each loop
    for (auto iter = graphics.begin(); iter != graphics.end(); iter++)
    {
        // random movement code to give an idea on updating stuff
        sf::Vector2f tempPos = (*iter)->getPosition();
        tempPos.x = sin(((float)scenetime)*0.01)*10;
        (*iter)->setPosition(tempPos);
    }

    // Then render
    render();
}

void Scene::init()
{
    mainview = ViewPtr(new sf::View(sf::FloatRect(0, 0,  600.0*aspect_ratio, 600)));
    initialized = true;

    // For derps, play a sound
    game.getAudioHandler()->playsound("biisi");
}

void Scene::render()
{
    // March through the graphics container and render graphics
    for (auto iter = graphics.begin(); iter != graphics.end(); iter++)
    {
        if (*iter == nullptr)
            continue;
        SpritePtr temp = *iter;
        // Don't render what is outside the render area
        if (((*iter)->getPosition().x - (*iter)->getTexture()->getSize().x > mainview->getCenter().x + mainview->getSize().x/2)
            ||
            ((*iter)->getPosition().x + (*iter)->getTexture()->getSize().x < mainview->getCenter().x - mainview->getSize().x/2)
            ||
            
            ((*iter)->getPosition().y + (*iter)->getTexture()->getSize().y < mainview->getCenter().y - mainview->getSize().y/2)
            ||
            ((*iter)->getPosition().y - (*iter)->getTexture()->getSize().y > mainview->getCenter().y + mainview->getSize().y/2)
            )
        {
            continue;
        }
        game.getRenderWindow()->draw(*(*iter));
    }
}

/**
* Add some graphics to this scene
*/
void Scene::appendGraphics(SpritePtr s)
{
    graphics.push_back(s);
}

/**
* When the window is resized, also tweak our sf::view
*/
void Scene::onWindowResize()
{
    /**
    * Manage aspect ratio. As the user resizes the window, we still want to display only
    * what is supposed to be seen. Resizing the window should not to:
    * 1) stretch pixels
    * 2) show more scene
    *
    * The first problem is obvious - it's ugly
    * The second is to make sure that any display area related things such as secrets hidden a few blocks
    * outside the usual "view area" won't be spoiled
    */

    display_area.y = game.getRenderWindow()->getSize().y;
    display_area.x = display_area.y*aspect_ratio;

    display_ratio.x = display_area.x/game.getRenderWindow()->getSize().x;
    display_ratio.y = display_area.y/game.getRenderWindow()->getSize().y;
    display_offset.y = -1 * display_ratio.x + 1;
    display_offset.y = -1 * display_ratio.y + 1;   

    mainview->setViewport(sf::FloatRect(display_offset.x/2.0, display_offset.y/2.0, 1.0 - display_offset.x, 1.0 - display_offset.y));
}


std::string Scene::getName() { return name; }
ViewPtr Scene::getView() { return mainview; }
Vector2fPtr Scene::getCameraTarget() { return camera_target; }
long long Scene::getTime() { return scenetime; }
bool Scene::hasInitialized() { return initialized; }
