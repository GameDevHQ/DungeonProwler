#include "PCH.h"
#include "Game.h"


// http://www.concentric.net/~Ttwang/tech/inthash.htm
unsigned int mix(unsigned long a, unsigned long b, unsigned long c)
{
    a=a-b;  a=a-c;  a=a^(c >> 13);
    b=b-c;  b=b-a;  b=b^(a << 8);
    c=c-a;  c=c-b;  c=c^(b >> 13);
    a=a-b;  a=a-c;  a=a^(c >> 12);
    b=b-c;  b=b-a;  b=b^(a << 16);
    c=c-a;  c=c-b;  c=c^(b >> 5);
    a=a-b;  a=a-c;  a=a^(c >> 3);
    b=b-c;  b=b-a;  b=b^(a << 10);
    c=c-a;  c=c-b;  c=c^(b >> 15);
    return static_cast<unsigned int>(c);
}


// Entry point of the application.
int main()
{
    // Set a random seed.
    unsigned int seed = mix(clock(), time(NULL), 1024);
    srand(42);

    // Create the main game object.
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Dungeon prowler", sf::Style::Fullscreen);
    Game game(&window);

    // Initialize and run the game object.
    game.Initialize();
    game.Run();

    // Exit the application.
    return 0;
}
