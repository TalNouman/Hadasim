#include <iostream>

#include "draft_music.hpp"

/* ----------------------------------------------------------------- */

Button::Button() : buttonShape(), buttonText() {}

void Button::SetButton(Button& button, const sf::Vector2f& position, const sf::Vector2f& size, 
        const sf::Color& color, const std::string& text, sf::Font& font) 
{
    button.buttonShape.setSize(size);
    button.buttonText.setString(text);
    button.buttonText.setFont(font);  
    button.buttonText.setCharacterSize(20);
    button.buttonShape.setPosition(position);
    button.buttonShape.setFillColor(color);
    button.buttonText.setPosition(position.x + 10, position.y + 5);
    button.buttonText.setFillColor(sf::Color::White);
}

bool Button::contains(const sf::Vector2f& point)
{
    return buttonShape.getGlobalBounds().contains(point);
}

void Button::draw(sf::RenderWindow& window)
{
    window.draw(buttonShape);
    window.draw(buttonText);
}

std::string Button::GetText()
{
    return buttonText.getString();
}

/* ----------------------------------------------------------------- */

SongOptions::SongOptions() {}

void SongOptions::Play()
{
    //song.play();
}

void SongOptions::AddSong()
{
    openTextInputWindow();
}

void SongOptions::Stop()
{
    //song.stop();
}

void SongOptions::openTextInputWindow()
{
    std::string songFilePath = getTextFromUser();
    std::cout << "Entered song file path: " << songFilePath << std::endl;

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(songFilePath))
    {
        std::cout << "Failed to load the song!" << std::endl;
    }
}

std::string SongOptions::getTextFromUser()
{
    sf::RenderWindow textWindow(sf::VideoMode(400, 100), "Text Input");
    sf::Font font;
    if (!font.loadFromFile("Arial.ttf"))
    {
        std::cout << "Failed to load font!" << std::endl;
        return "";
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);
    text.setPosition(10, 10);

    std::string inputText;

    while (textWindow.isOpen())
    {
        sf::Event event;
        while (textWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                textWindow.close();
            }
            else if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode == '\b' && !inputText.empty())
                {
                    inputText.pop_back();
                }
                else if (event.text.unicode < 128)
                {
                    inputText += static_cast<char>(event.text.unicode);
                }
            }
        }

        text.setString(inputText);
        textWindow.clear(sf::Color::White);
        textWindow.draw(text);
        textWindow.display();
    }

    return inputText;
}

/* ----------------------------------------------------------------- */

MediaPlayer::MediaPlayer() : window(sf::VideoMode(800, 600), "Song Options"), 
        font(), song(), m_option(), m_buttons(), m_actions({})
{
    if (!font.loadFromFile("Arial.ttf"))
    {
        std::cout << "Failed to load font!" << std::endl;
        return;
    }
    
    initializeButtons();
    initializeActions();
}

void MediaPlayer::run()
{
    while(window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void MediaPlayer::initializeButtons()
{
    std::vector<std::string> texts;
    texts.push_back("Add Song");
    texts.push_back("Play");
    texts.push_back("Stop");
    int pos_x = 320;
    int pos_y = 190;

    m_buttons.resize(texts.size());

    for(size_t i = 0; i < m_buttons.size(); ++i)
    {
        m_buttons[i].SetButton(m_buttons[i], sf::Vector2f(pos_x, pos_y), 
            sf::Vector2f(100, 30), sf::Color::Blue, texts[i], font);

        pos_y += 50;
    }
}

void MediaPlayer::initializeActions()
{
    m_actions[m_buttons[0].GetText()] = [&]() {m_option.AddSong();};
    m_actions[m_buttons[1].GetText()] = [&]() {m_option.Play();};
    m_actions[m_buttons[2].GetText()] = [&]() {m_option.Stop();};    
}

void MediaPlayer::processEvents()
{
    sf::Event event;
    while(window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                for(size_t i = 0; i < m_buttons.size(); ++i)
                {
                    if(m_buttons[i].contains(mousePos))
                    {
                        std::cout << "enter the song:" << i << std::endl;
                        m_actions[m_buttons[i].GetText()]();
                    }
                }
            }
        }
    }
}

void MediaPlayer::update()
{
    // Add your update logic here
}

void MediaPlayer::render()
{
    window.clear();
    for(size_t i = 0; i < m_buttons.size(); ++i)
    {
        m_buttons[i].draw(window);
    }
    window.display();
}
