#include <SFML/Graphics.hpp>
#include <complex>
#include <iostream>

const int renderWidth = 1280;
const int renderHeight = 720;

int mandelbrotAlgo(std::complex<double> point){
    const int maxIter = 250;
    int iters = 0;
    std::complex<double> z(0,0);

    for(iters; iters<maxIter; iters++)
    {
        z = z*z + point;
        if(abs(z)>2)
        {
            return iters;
        }
    }

}
int main()
{
    sf::RenderWindow window(sf::VideoMode(renderWidth, 
            renderHeight), "Mandelbrot");
 
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }

    return 0;
}