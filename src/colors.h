#ifndef COLORS_H
#define COLORS_H

#include <GL/glew.h>
#include <map>
#include <string>

struct Color{

    float r, g, b, a;


    Color()
    {
        r = 0.0;  
        g = 0.0;
        b = 0.0;
        a = 1.0; 
    }

    Color(float red, float green, float blue)
    {
        r = red;
        g = green;
        b = blue;
        a = 1.0;
    }

    Color(float red, float green, float blue, float alpha)
    {
        r = red;
        g = green;
        b = blue;
        a = alpha;
    }
    

    Color(std::string hexstring)
    {

        r = (float)std::stoul(hexstring.substr(0,2),nullptr,16)/255.0;
        g = (float)std::stoul(hexstring.substr(2,2),nullptr,16)/255.0;
        b = (float)std::stoul(hexstring.substr(4,2),nullptr,16)/255.0;
        a = 1.0f;

    }
};


Color fromInt(int r, int g, int b)
{
    return Color( ((float)r )/255.0, g/255.0, b/255.0);
}

std::map<std::string,Color> colors = {
    {"black",           Color(0.0f, 0.0f, 0.0f)},
    {"white",           Color(1.0f, 1.0f, 1.0f)},
    {"red",             Color(1.0f, 0.0f, 0.0f)},
    {"green",           Color(0.0f, 1.0f, 0.0f)},
    {"blue",            Color(0.0f, 0.0f, 1.0f)},
    {"magicmint",       fromInt(170, 250, 200)},
    {"aeroblue",        fromInt(199, 255, 237)},
    {"spanishblue",     fromInt(36, 110, 185)},
    {"nadeshikopink",   Color("EFAAC4")}
};

#endif