#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <functional>

/* ----------------------------------------------- */

class Button
{
public:
    Button();

    void SetButton(Button& button, const sf::Vector2f& position, const sf::Vector2f& size, 
        const sf::Color& color, const std::string& text, sf::Font& font);
    bool contains(const sf::Vector2f& point);
    void draw(sf::RenderWindow& window);
    std::string GetText();

private:
    sf::RectangleShape buttonShape;
    sf::Text buttonText;
};

/* ----------------------------------------------- */

class SongOptions
{
public: 
    SongOptions();

    void Play();
    void AddSong();
    void Stop();
    void openTextInputWindow();
    std::string getTextFromUser();

private:
    //sf::Music m_song;
};


/* ----------------------------------------------- */

class MediaPlayer
{
public:
    MediaPlayer();
    void run();

private:
    void initializeButtons();
    void initializeActions();
    void processEvents();
    void update();
    void render();

private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Sound song;
    SongOptions m_option;
    std::vector<Button> m_buttons;
    std::unordered_map<std::string, std::function<void()>> m_actions;
};


