#pragma once

class ReactorHeart;
class SpecificCommandInterpretator;
class ReactorWebServer;
class LED;

class Program
{
public:
    Program();
    void loop();

private:
    void networkConnection();
    ReactorWebServer *m_webServer;
    ReactorHeart *m_reactorHeart;
    SpecificCommandInterpretator *m_specificCommandInterpretator;
};