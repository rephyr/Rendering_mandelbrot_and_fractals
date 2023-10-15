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
    return maxIter;
}
void renderImage(){

}
int main()
{
    sf::RenderWindow window(sf::VideoMode(renderWidth, renderHeight), "Mandelbrot");
    sf::Texture texture;
    texture.create(renderWidth, renderHeight);
    // Placeholder sprite while rendering the image
    sf::Sprite sprite(texture);
    // Assign x- and y-axis
    const float minX = -2.0f, maxX = 2.0f;
    const float minY = -2.0f, maxY = 2.0f;
    // To scale the screen resolution to use desired axis
    const float scaleX = (maxX - minX) / renderWidth;
    const float scaleY = (maxY - minY) / renderHeight;
    float xAxis;
    float yAxis;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Image image;
        image.create(renderWidth, renderHeight, sf::Color::Black);

        // Iterate through every pixel in our window
        for (int pixelX = 0; pixelX < renderWidth; ++pixelX)
        {
            for (int pixelY = 0; pixelY < renderHeight; ++pixelY)
            {
                xAxis = minX + pixelX * scaleX;
                yAxis = maxY - pixelY * scaleY; 
            }
        }
        window.display();
    }

    return 0;
}
