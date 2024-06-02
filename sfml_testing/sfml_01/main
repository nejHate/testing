#include <SFML/Graphics.hpp>
#include <array>

const int CHUNK_SIZE = 16;

// Define block types
enum BlockType {
    AIR = 0,
    GRASS,
    DIRT,
    // Add more block types as needed
};

// Function to create a quad for a block face
void addFace(sf::VertexArray& vertexArray, int x, int y, int z, const sf::Texture& texture, BlockType type) {
    // Size of each block
    float blockSize = 1.0f;

    // Example: add front face of the block
    sf::Vertex quad[4];
    
    quad[0].position = sf::Vector2f(x * blockSize, y * blockSize);
    quad[1].position = sf::Vector2f((x + 1) * blockSize, y * blockSize);
    quad[2].position = sf::Vector2f((x + 1) * blockSize, (y + 1) * blockSize);
    quad[3].position = sf::Vector2f(x * blockSize, (y + 1) * blockSize);
    
    // Set texture coordinates based on block type
    // Assuming a 16x16 texture for each block type in a texture atlas
    float texSize = 16.0f;
    float texX = (type % 16) * texSize;
    float texY = (type / 16) * texSize;
    
    quad[0].texCoords = sf::Vector2f(texX, texY);
    quad[1].texCoords = sf::Vector2f(texX + texSize, texY);
    quad[2].texCoords = sf::Vector2f(texX + texSize, texY + texSize);
    quad[3].texCoords = sf::Vector2f(texX, texY + texSize);
    
    for (int i = 0; i < 4; ++i) {
        vertexArray.append(quad[i]);
    }
}

int main() {
    // Create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Subchunk Renderer");

    // Load texture atlas
    sf::Texture texture;
    if (!texture.loadFromFile("block_textures.png")) {
        return -1;
    }

    // Example subchunk data (replace with actual data)
    std::array<std::array<std::array<BlockType, CHUNK_SIZE>, CHUNK_SIZE>, CHUNK_SIZE> subchunk = { AIR };
    subchunk[0][0][0] = GRASS;
    subchunk[1][0][0] = DIRT;

    // Create a vertex array
    sf::VertexArray vertexArray(sf::Quads);

    // Iterate through the subchunk and add faces
    for (int x = 0; x < CHUNK_SIZE; ++x) {
        for (int y = 0; y < CHUNK_SIZE; ++y) {
            for (int z = 0; z < CHUNK_SIZE; ++z) {
                if (subchunk[x][y][z] != AIR) {
                    // Add faces for visible sides of the block
                    addFace(vertexArray, x, y, z, texture, subchunk[x][y][z]);
                }
            }
        }
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(vertexArray, &texture);
        window.display();
    }

    return 0;
}
