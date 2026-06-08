#include "game.h"

int main()
{
    int width=1000;
    int height=1000;
    Color primary;
    Color secondary;
    Color threat;
    Color Dot;
    //dark light blue and neon dot
    // primary   = (Color){230, 240, 255, 255};
    // secondary = (Color){30, 40, 60, 255};
    // threat    = (Color){255, 60, 90, 255};
    // Dot       = (Color){0, 255, 200, 255};

    //white purple and light light green dots
    //  primary   = (Color){240, 240, 240, 255};
    //  secondary = (Color){60, 60, 70, 255};
    //  threat    = (Color){220, 50, 50, 255};
    //  Dot       = (Color){120, 200, 120, 255};


    //White Black and Green Dot
    //  primary   = (Color){255, 255, 255, 255};
    //  secondary = (Color){20, 20, 20, 255};
    //  threat    = (Color){255, 0, 0, 255};
    //  Dot       = (Color){0, 255, 0, 255};

    //bluish and white and golden dot  
     primary   = (Color){245, 245, 235, 255};
     secondary = (Color){70, 85, 110, 255};
     threat    = (Color){190, 40, 60, 255};
     Dot       = (Color){255, 215, 90, 255};

    //purple and white and neon dots
    // primary   = (Color){255, 255, 255, 255};
    // secondary = (Color){60, 60, 90, 255};
    // threat    = (Color){255, 0, 120, 255};
    // Dot       = (Color){0, 255, 150, 255};


    Game G(width,height,primary,secondary,threat,Dot);
    G.gameloop();
    return 0;
}