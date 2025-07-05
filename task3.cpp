// task3_snake_game.cpp
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace sf;
using namespace std;

struct SnakeSegment {
    int x, y;
    SnakeSegment(int x = 0, int y = 0) : x(x), y(y) {}
};

int main() {
    srand(time(0));
    RenderWindow window(VideoMode(400, 400), "Snake Game");
    int size = 20, width = 20, height = 20;
    Vector2i dir(1, 0), food(rand() % width, rand() % height);

    vector<SnakeSegment> snake = { {10, 10} };

    Clock clock;
    float timer = 0, delay = 0.1;

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Up)) dir = {0, -1};
        if (Keyboard::isKeyPressed(Keyboard::Down)) dir = {0, 1};
        if (Keyboard::isKeyPressed(Keyboard::Left)) dir = {-1, 0};
        if (Keyboard::isKeyPressed(Keyboard::Right)) dir = {1, 0};

        if (timer > delay) {
            timer = 0;
            for (int i = snake.size() - 1; i > 0; --i)
                snake[i] = snake[i-1];
            snake[0].x += dir.x;
            snake[0].y += dir.y;

            if (snake[0].x == food.x && snake[0].y == food.y) {
                snake.push_back(SnakeSegment());
                food = {rand() % width, rand() % height};
            }
        }

        window.clear();
        RectangleShape square(Vector2f(size - 1, size - 1));
        square.setFillColor(Color::Green);

        for (auto& s : snake) {
            square.setPosition(s.x * size, s.y * size);
            window.draw(square);
        }

        square.setFillColor(Color::Red);
        square.setPosition(food.x * size, food.y * size);
        window.draw(square);

        window.display();
    }
    return 0;
}
