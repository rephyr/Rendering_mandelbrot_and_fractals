#include <SFML/Graphics.hpp>
#include <complex>
#include <iostream>
const sf::Color white(255, 255, 255);
const sf::Color blue(0, 0, 255);
const sf::Color red(255, 0, 0);
const sf::Color black(0, 0, 0);
const int renderWidth = 1280;
const int renderHeight = 720;
const int MAX_ITERATIONS = 1000;
sf::Color lerpColor(const sf::Color& start, const sf::Color& end, double t) {
    // Clamp the value of t between 0.0 and 1.0
    t = std::max(0.0, std::min(1.0, t));

    int r = static_cast<int>(start.r + t * (end.r - start.r));
    int g = static_cast<int>(start.g + t * (end.g - start.g));
    int b = static_cast<int>(start.b + t * (end.b - start.b));

    return sf::Color(r, g, b);
}
sf::Color getSmoothColor(double smoothValue, int maxIter) {
    // Normalize the smooth value between 0.0 and 1.0
    double t = smoothValue / maxIter;

    // You'll need to adjust these ranges if you add more colors.
    if (t < 0.33) {
        // Transition from white to blue
        return lerpColor(white, blue, t / 0.33);
    } else if (t < 0.66) {
        // Transition from blue to red
        return lerpColor(blue, red, (t - 0.33) / 0.33);
    } else {
        // Transition from red to black
        return lerpColor(red, black, (t - 0.66) / 0.34);
    }
}
double mandelbrotAlgo(const std::complex<double>& point, int maxIter){
    std::complex<double> z = 0;
    int iter = 0;

    while (iter < maxIter && std::norm(z) <= 4.0) {
        z = z * z + point;
        iter++;
    }

    if (iter == maxIter) return static_cast<double>(maxIter);

    // Smooth coloring algorithm
    return iter + 1 - std::log(std::log2(std::abs(z)));
}
void renderImage(sf::Image& image) {
    sf::Color startColor = sf::Color::Blue; 
    sf::Color endColor = sf::Color::Red; 
    // Values for x- and y-axis
    const float minX = -2.0f, maxX = 0.47f;
    const float minY = -1.12f, maxY = 1.12f;
    // Scale to fit the Mandelbrot set within the window dimensions
    const double scaleX = (maxX - minX) / renderWidth;  
    const double scaleY = (maxY - minY) / renderHeight;
    for (int pixelY = 0; pixelY < renderHeight; ++pixelY) {
        for (int pixelX = 0; pixelX < renderWidth; ++pixelX) {
            double xAxis = minX + pixelX * scaleX;
            double yAxis = minY + pixelY * scaleY;
            std::complex<double> point(xAxis, yAxis);
        double smoothValue = mandelbrotAlgo(point, MAX_ITERATIONS);
        sf::Color color = getSmoothColor(smoothValue, MAX_ITERATIONS);
        image.setPixel(pixelX, pixelY, color);

        }
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(renderWidth, renderHeight), "Mandelbrot");
    sf::Texture texture;
    texture.create(renderWidth, renderHeight);
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
            window.draw(sprite);
            window.display();
        }

    return 0;
}
