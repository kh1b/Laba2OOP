#include <iostream>
#include <vector>

// Базовый класс Shape
class Shape {
protected:
    int x, y;

public:
    // Конструктор по умолчанию
    Shape() {
        x = 0;
        y = 0;
        std::cout << "Конструктор по умолчанию Shape вызван. Позиция: (" << x << ", " << y << ")" << std::endl;
    }

    // Конструктор с параметрами
    Shape(int xVal, int yVal){
        x = xVal;
        y = yVal;
        std::cout << "Конструктор с параметрами Shape вызван. Позиция: (" << x << ", " << y << ")" << std::endl;
    }

    // Конструктор копирования
    Shape(const Shape &other){
        x = other.x;
        y = other.y;
        std::cout << "Конструктор копирования Shape вызван." << std::endl;
    }

    // Метод для перемещения
    void move(int dx, int dy) {
        x += dx;
        y += dy;
        std::cout << "Фигура перемещена в (" << x << ", " << y << ")" << std::endl;
    }

    // Чисто виртуальный метод draw
    virtual void draw() const = 0;

    // Деструктор
    virtual ~Shape() {
        std::cout << "Деструктор Shape вызван." << std::endl;
    }
};

// Производный класс Circle
class Circle : public Shape {
private:
    int radius; // Инициализация по умолчанию

public:
    // Конструктор по умолчанию
    Circle() {
        radius = 0;
        std::cout << "Конструктор по умолчанию Circle вызван. Радиус: " << radius << std::endl;
    }

    // Конструктор с параметрами
    Circle(int xVal, int yVal, int r) : Shape(xVal, yVal){
        radius = r;
        std::cout << "Конструктор с параметрами Circle вызван. Радиус: " << radius << std::endl;
    }

    // Конструктор копирования
    Circle(const Circle& other) : Shape(other){
        radius = other.radius;
        std::cout << "Конструктор копирования Circle вызван." << std::endl;
    }

    // Переопределение метода draw
    void draw() const override {
        std::cout << "Рисуем круг в точке (" << x << ", " << y << ") с радиусом " << radius << std::endl;
    }

    // Деструктор
    ~Circle() override {
        std::cout << "Деструктор Circle вызван." << std::endl;
    }
};

// Производный класс Square
class Square : public Shape {
private:
    int side;

public:
    // Конструктор по умолчанию
    Square() {
        side = 0;
        std::cout << "Конструктор по умолчанию Square вызван. Сторона: " << side << std::endl;
    }

    // Конструктор с параметрами
    Square(int xVal, int yVal, int s) : Shape(xVal, yVal) { // Вызов конструктора базового класса
        side = s;
        std::cout << "Конструктор с параметрами Square вызван. Сторона: " << side << std::endl;
    }

    // Конструктор копирования
    Square(const Square& other) : Shape(other) { // Вызов конструктора копирования базового класса
        side = other.side;
        std::cout << "Конструктор копирования Square вызван." << std::endl;
    }

    // Переопределение метода draw
    void draw() const override {
        std::cout << "Рисуем квадрат в точке (" << x << ", " << y << ") со стороной " << side << std::endl;
    }

    // Деструктор
    ~Square() override {
        std::cout << "Деструктор Square вызван." << std::endl;
    }
};

// Класс Canvas (холст)
class Canvas {
private:
    std::vector<Shape*> shapes; // Коллекция фигур

public:
    // Добавление фигуры на холст
    void addShape(Shape* shape) {
        shapes.push_back(shape);
        std::cout << "Фигура добавлена на холст." << std::endl;
    }

    // Рисование всех фигур
    void drawAll() const {
        for (const auto& shape : shapes) {
            shape->draw();
        }
    }

    // Перемещение всех фигур
    void moveAll(int dx, int dy) {
        for (auto& shape : shapes) {
            shape->move(dx, dy);
        }
    }

    // Очистка холста
    void clear() {
        for (auto& shape : shapes) {
            delete shape;
        }
        shapes.clear();
        std::cout << "Холст очищен." << std::endl;
    }

    // Деструктор
    ~Canvas() {
        clear();
    }
};

// Класс Group (группа фигур)
class Group {
private:
    Circle circleDirect;   // Композиция через объект
    Circle* circlePointer; // Композиция через указатель

public:
    // Конструктор
    Group(int x1, int y1, int r1, int x2, int y2, int r2): circleDirect(x1, y1, r1), circlePointer(new Circle(x2, y2, r2)) {
        std::cout << "Конструктор Group вызван." << std::endl;
    }

    // Метод для рисования всех фигур в группе
    void drawAll() const {
        circleDirect.draw();
        circlePointer->draw();
    }

    // Деструктор
    ~Group() {
        delete circlePointer; // Удаляем объект, созданный через указатель
        std::cout << "Деструктор Group вызван." << std::endl;
    }
};

int main() {
    setlocale(LC_ALL, "RU");

    std::cout << "=== Создание фигур ===" << std::endl;
    Circle c1(10, 20, 5); // Статический объект
    Square s1(30, 40, 10); // Статический объект

    std::cout << "\n=== Добавление фигур на холст ===" << std::endl;
    Canvas canvas; // Создаем холст
    canvas.addShape(new Circle(50, 60, 7)); // Динамический объект
    canvas.addShape(new Square(70, 80, 15)); // Динамический объект

    std::cout << "\n=== Рисуем все фигуры ===" << std::endl;
    canvas.drawAll();

    std::cout << "\n=== Перемещаем все фигуры на (5, 5) ===" << std::endl;
    canvas.moveAll(5, 5);

    std::cout << "\n=== Очищаем холст ===" << std::endl;
    canvas.clear();

    std::cout << "\n=== Пример композиции ===" << std::endl;
    Group group(100, 200, 15, 300, 400, 25); // Создаем группу с двумя кругами

    std::cout << "\n=== Рисуем все фигуры в группе ===" << std::endl;
    group.drawAll();

    return 0;

}