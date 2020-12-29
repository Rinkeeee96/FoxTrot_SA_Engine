#include "pch.h"
#include "AdvertisementHandler.h"

AdvertisementHandler::AdvertisementHandler(unique_ptr<Engine>& _engine) : engine(_engine)
{

}

AdvertisementHandler::~AdvertisementHandler()
{

}

void AdvertisementHandler::getLatestAdvertisements()
{
    // Get Json
    // https://jsonkeeper.com/b/6H3R




    string url = "https://i.ibb.co/92qrP5f/coke-logo.png";
    string path = "C:\\Users\\Rinke\\Desktop\\foto.png";
    fileLoader.downloadFile(url,path);
    // Parse Json 
}

