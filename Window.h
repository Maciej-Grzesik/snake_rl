//
// Created by Maciej on 25/07/2024.
//

#ifndef MOUNTAINCAR_WINDOW_H
#define MOUNTAINCAR_WINDOW_H


#include <string>
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class Window {
public:
    Window();
    Window(const std::string& l_title, const sf::Vector2u& l_size);
    ~Window();

    void beginDraw();
    void endDraw();

    void update();

    bool isDone() const;
    bool isFullScreen() const;
    sf::Vector2u getWindowSize();

    void toggleFullScreen();
    sf::RenderWindow* getRenderWindow();

    void draw(sf::Drawable& l_drawable);
private:
    void setup(const std::string& l_title, const sf::Vector2u& l_size);
    void destroy();
    void create();

    sf::RenderWindow m_window;
    sf::Vector2u m_windowSize;
    std::string m_windowTitle;
    bool m_isDone;
    bool m_isFullscreen;
};


#endif //MOUNTAINCAR_WINDOW_H
