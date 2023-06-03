#include <SFML/Graphics.hpp>
#include <cmath>

struct Vec3 {
    float x, y, z;

    Vec3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}
    Vec3 operator+(const Vec3& v) const { return Vec3(x + v.x, y + v.y, z + v.z); }
    Vec3 operator-(const Vec3& v) const { return Vec3(x - v.x, y - v.y, z - v.z); }
    Vec3 operator*(float f) const { return Vec3(x * f, y * f, z * f); }
    float dot(const Vec3& v) const { return x * v.x + y * v.y + z * v.z; }
    Vec3 normalize() const {
        float mag = std::sqrt(x * x + y * y + z * z);
        return Vec3(x / mag, y / mag, z / mag);
    }
};

struct Ray {
    Vec3 orig, dir;
    Ray(const Vec3& orig, const Vec3& dir) : orig(orig), dir(dir) {}
};

struct Sphere {
    Vec3 center;
    float radius;
    sf::Color color;

    Sphere(const Vec3& center, float radius, const sf::Color& color) : center(center), radius(radius), color(color) {}

    bool intersect(const Ray& ray, float& t) const {
        Vec3 oc = ray.orig - center;
        float a = ray.dir.dot(ray.dir);
        float b = 2 * oc.dot(ray.dir);
        float c = oc.dot(oc) - radius * radius;
        float discriminant = b * b - 4 * a * c;
        if (discriminant < 0) return false;
        else {
            discriminant = sqrt(discriminant);
            float t0 = (-b - discriminant) / (2.0 * a);
            float t1 = (-b + discriminant) / (2.0 * a);
            t = (t0 < t1) ? t0 : t1;
            return true;
        }
    }
};

int main() {
    const int W = 800;
    const int H = 600;
    sf::RenderWindow window(sf::VideoMode(W, H), "Ray Tracer");

    Vec3 camera(0, 0, -1);
    Sphere sphere(Vec3(0, 0, 1), 0.5, sf::Color::Red);
    Vec3 light(0, 0, -1);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseMoved) {
                light.x = (event.mouseMove.x - W / 2.0f) / (W / 2.0f);
                light.y = -(event.mouseMove.y - H / 2.0f) / (H / 2.0f);
            }
        }

        sf::Image image;
        image.create(W, H, sf::Color::Black);
        for (int y = 0; y < H; y++) {
            for (int x = 0; x < W; x++) {
                Vec3 dir((x - W / 2.0f) / (W / 2.0f), -(y - H / 2.0f) / (H / 2.0f), 1);
                dir = dir.normalize();
                Ray ray(camera, dir);
                float t;
                if (sphere.intersect(ray, t)) {
                    Vec3 hit = ray.orig + ray.dir * t;
                    Vec3 normal = (hit - sphere.center).normalize();
                    Vec3 toLight = (light - hit).normalize();
                    float brightness = std::max(0.f, normal.dot(toLight));
                    sf::Color color(sphere.color.r * brightness, sphere.color.g * brightness, sphere.color.b * brightness);
                    image.setPixel(x, y, color);
                }
            }
        }

        sf::Texture texture;
        texture.loadFromImage(image);
        sf::Sprite sprite;
        sprite.setTexture(texture);

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}