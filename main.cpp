// PRCS-PI -- Demonstrates how to use "my" method to compute the value of π
// By: zxunge, 2025

#if __cplusplus < 202302L
#error "This program needs a C++ standard higher than C++23."
#endif

#include <ranges>
#include <cctype>
#include <print>
#include <vector>
#include <sstream>
#include <string_view>
#include <mp++/mp++.hpp>

using std::vector;
using std::println;
using std::string_view;
using std::stringstream;
using real = mppp::real;

// Represents a point in Plane Rectangular Coordinate System.
class Point
{
public:
    Point(real x, real y) : px(x), py(y) {}
    
    real x() const { return px; }
    real y() const { return py; }
    
    real distance(const Point & p2) const
    {
        return sqrt((px - p2.x()) * (px - p2.x()) + (py - p2.y()) * (py - p2.y()));
    }

private:
    real px {"0.0", 512};
    real py {"0.0", 512};
};

// Represents a line in Plane Rectangular Coordinate System.
// Note that we use the form of 'y = kx + b'.
class Line
{
public:
    Line(const Point &p1, const Point &p2)
    {
        // We assume they are not the same point.
        lk = (p1.y() - p2.y()) / (p1.x() - p2.x());
        lb = p1.y() - lk * p1.x();
    }
    
    real k() const { return lk; }
    real b() const { return lb; }
    
    Point intersects(const Line &l2) const
    {
        return Point((l2.b() - lb) / (lk - l2.k()),
                     (l2.k() * lb - lk * l2.b()) / (l2.k() - lk));
    }
    
    
private:
    real lk {"0.0", 512};
    real lb {"0.0", 512};
};

int main(int argc, char *argv[])
{
    int precision {};
    // Parse program arguments.
    vector<string_view> args;
    
    // Enpty arguments?
    if (argc == 1)
    {
        precision = 1;
        goto compute;
    }
    
    for (int i { 1 }; i != argc; ++i)
        args.push_back(string_view(argv[i]));

    if (std::ranges::all_of(args[0],
                            [](char c) { return (isdigit(c) != 0) && (c != '-'); }))
    {
        stringstream ss;
        ss << args[0];
        ss >> precision;
        goto compute;
    }
    else if (args[0].starts_with("-h"))
    {
        println("PRCS-PI -- Demonstrates how to use \"my\" method to compute the value of π.");
        println("By: zxunge, 2025");
        println("\nUsage: prcspi [precision]");
        println("where \'precision\' is the number of points held in 1 unitized length.");
        println("\nUsage: prcspi -h");
        println("to print this help.");
        return 0;
    }
    else
    {
        println("Bad arguments.");
        println("\nUsage: prcspi [precision]");
        println("where \'precision\' is the number of points held in 1 unitized length.");
        println("\nUsage: prcspi -h");
        println("to print this help.");
        return 0;
    }
    
compute:
    // Real computing stage.
    // Constructs the square, with the default size of 10 x 10.
    vector<Line> bottomLeft, bottomRight, topLeft, topRight;
    for (int i {}; i != 5 * precision; ++i)
    {
        bottomLeft.push_back(Line(Point(0, real("1.0", 512) / precision * (i + 1)), 
                                  Point(5.0 - real("1.0", 512) / precision * i, 0)));
        bottomRight.push_back(Line(Point(5.0 + real("1.0", 512) / precision * i, 0),
                                   Point(0, real("1.0", 512) / precision * (i + 1))));
        topRight.push_back(Line(Point(5.0 + real("1.0", 512) / precision * i, 10),
                                Point(10, 10.0 - real("1.0", 512) / precision * (i + 1))));
        topLeft.push_back(Line(Point(0, 10.0 - real("1.0", 512) / precision * (i + 1)),
                               Point(5.0 - real("1.0", 512) / precision * i, 10)));
    }
    // Compute the intersection group.
    vector<Point> blInter, brInter, tlInter, trInter;
    blInter.push_back(Point(5, 0));
    brInter.push_back(Point(5, 0));
    tlInter.push_back(Point(5, 10));
    trInter.push_back(Point(5, 10));
    for (int i {}; i != 5 * precision - 1; ++i)
    {
        blInter.push_back(bottomLeft[i].intersects(bottomLeft[i + 1]));
        brInter.push_back(bottomRight[i].intersects(bottomRight[i + 1]));
        tlInter.push_back(topLeft[i].intersects(topLeft[i + 1]));
        trInter.push_back(topRight[i].intersects(topRight[i + 1]));
    }
    blInter.push_back(Point(0, 5));
    brInter.push_back(Point(10, 5));
    tlInter.push_back(Point(0, 5));
    trInter.push_back(Point(10, 5));
    
    // Accumulate the distance.
    real circumference { "1.0", 512 };
    for (int i {}; i != 5 * precision; ++i)
    {
        circumference += blInter[i].distance(blInter[i + 1]);
        circumference += brInter[i].distance(brInter[i + 1]);
        circumference += tlInter[i].distance(tlInter[i + 1]);
        circumference += trInter[i].distance(trInter[i + 1]);
    }
    
    // Now compute the final result.
    real pi { circumference / 10.0, 512 };
    
    println("The final result of Pi is {}.", pi.to_string());
    
    return 0;
}