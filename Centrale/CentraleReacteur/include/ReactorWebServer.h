#pragma once
#include "ReactorHeart.h"

class WebServer;

class ReactorWebServer
{
private:
    ReactorHeart *m_reactorHeart;
    WebServer *m_webServer;
    void handlePutRequest();
    void getState();
    String deserialiseJson(String const &p_request);
    String serialiseJson(String const &p_response);
    void sendCors() const;
    void corsOptions() const;

public:
    ReactorWebServer(ReactorHeart *p_reactorHeart);
    void tick();
};