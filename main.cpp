#include <iostream> 
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>

bool readImageFile(const std::string& filename, sf::Image& image);

int main(int argc, char* argv[]) {
    sf::Image image;

    if (argc != 2) {
        std::cout << "Invalid number of arguments\n";
        return 1;
    }

    std::string filename = argv[1];
    if (!readImageFile(filename, image)) {
        std::cout << "Error reading file\n";
        return 1;
    }

    sf::Vector2u sizeVec = image.getSize();
    sf::RenderWindow window(sf::VideoMode({sizeVec.x, sizeVec.y}), "SFML window");

    sf::Texture texture;
    texture.loadFromImage(image);

    sf::Sprite sprite(texture);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}

bool readImageFile(const std::string& filename, sf::Image& image) {
    unsigned width{}, height{};

    std::ifstream file(filename, std::ios::binary); 
    if (file.is_open()) {
        std::string line;

        // skip first two lines
        std::getline(file, line);
        std::getline(file, line);

        // read in dimensions
        std::getline(file, line);
        std::stringstream ss(line);

        ss >> width;
        ss >> height;

        // skip next line and whitespace
        std::getline(file, line);

        // get RGB data - use char to avoid reinterpret_cast (file.read() requires char* pointer)
        const std::size_t rgbSize = static_cast<std::size_t>(width) * height * 3;
        std::vector<char> rgb(rgbSize);
        file.read(rgb.data(), rgb.size());

        if (file.gcount() != static_cast<std::streamsize>(rgb.size())) {
            std::cout << "Error reading RGB values";
            return false;
        }

        // convert to RGBA
        std::vector<sf::Uint8> rgba(static_cast<std::size_t>(width) * height * 4);

        for (std::size_t i = 0, j = 0; i < rgb.size(); i += 3, j += 4) {
            rgba[j] = rgb[i];
            rgba[j + 1] = rgb[i + 1];
            rgba[j + 2] = rgb[i + 2];
            rgba[j + 3] = 255; // max opacity;
        }

        image.create(width, height, rgba.data());

        file.close();
    }
    return true;
}
