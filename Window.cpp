//
// Created by Maciej on 25/07/2024.
//

#include "Window.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"

Window::Window() {
    setup("Window", sf::Vector2u(640, 480));
}

Window::Window(const std::string &l_title, const sf::Vector2u &l_size) {
    setup(l_title, l_size);
}

Window::~Window() {
    destroy();
}

void Window::beginDraw() {
    m_window.clear(sf::Color::Black);
}

void Window::endDraw() {
    m_window.display();
}

void Window::update() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_isDone = true;
        } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5) {
            toggleFullScreen();
        }
    }
}

bool Window::isDone() const {
    return m_isDone;
}

bool Window::isFullScreen() const {
    return m_isFullscreen;
}

void Window::draw(sf::Drawable &l_drawable) {
    m_window.draw(l_drawable);
}

void Window::setup(const std::string &l_title, const sf::Vector2u &l_size) {
    m_windowTitle = l_title;
    m_windowSize = l_size;
    m_isFullscreen = false;
    m_isDone = false;
    create();
}

void Window::destroy() {
    m_window.close();
}

void Window::create() {
    auto style = (m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
    m_window.create( { m_windowSize.x, m_windowSize.y}, m_windowTitle, style);
}

sf::Vector2u Window::getWindowSize() {
    return m_windowSize;
}

void Window::toggleFullScreen() {
    m_isFullscreen = !m_isFullscreen;
    destroy();
    create();
}

sf::RenderWindow* Window::getRenderWindow() {
    return &m_window;
}
