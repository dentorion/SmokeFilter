#include "FileSystemDebug.h"

#include <Arduino.h>
#include <LittleFS.h>

void FileSystemDebug::printFiles()
{
    Serial.println();
    Serial.println("========== LittleFS ==========");

    Dir dir = LittleFS.openDir("/icons");

    if (!dir.next())
    {
        Serial.println("Folder /icons is empty or not found.");
        Serial.println("==============================");
        return;
    }

    do
    {
        Serial.print("/icons/");
        Serial.print(dir.fileName());

        File file = dir.openFile("r");

        Serial.print("   ");

        if (file)
        {
            Serial.print(file.size());
            Serial.println(" bytes");
            file.close();
        }
        else
        {
            Serial.println("ERROR");
        }

    } while (dir.next());

    Serial.println("==============================");
}