#include <SFML/Graphics.hpp>
#include <complex>

const int renderWidth = 1280;
const int renderHeight = 720;

int mandelbrotAlgo(std::complex<double> point)
{
    // Bigger number == more accurate picture.
    const int maxIter = 250;
    std::complex<double> z(0,0);

    for(int iters = 0; iters<maxIter; iters++)
    {
        z = z*z + point;
        if(abs(z)>2)
        {
            return iters;
        }
    }
    return maxIter;
}
void renderImage(sf::Image& image) {
    const float minX = -2.0f, maxX = 2.0f;  
    const float minY = -2.0f, maxY = 2.0f;
    const double scaledX = (maxX - minX) / renderWidth;  
    const double scaledY = (maxY - minY) / renderHeight;

    // Iterate through every pixel in our window
    for (int pixelY = 0; pixelY < renderHeight; ++pixelY) {
        for (int pixelX = 0; pixelX < renderWidth; ++pixelX) {
            double xAxis = minX + pixelX * scaledX;
            double yAxis = minY + pixelY * scaledY;  

            std::complex<double> point(xAxis, yAxis);
            int numIterations = mandelbrotAlgo(point);

            // Colorpicking here
        }
    }
}
int main() {
    sf::RenderWindow window(sf::VideoMode(renderWidth, renderHeight), "Mandelbrot");
    sf::Texture texture;
    texture.create(renderWidth, renderHeight);
    // Placeholder
    sf::Sprite sprite(texture);

    sf::Image image;
    image.create(renderWidth, renderHeight, sf::Color::Black);

    // Initial rendering of the image
    renderImage(image);
    texture.loadFromImage(image);
    sprite.setTexture(texture, true);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(sprite);  // Draw the texture
        window.display();
    }

    return 0;
}