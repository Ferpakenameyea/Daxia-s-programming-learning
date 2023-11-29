#include <iostream>
#include <vector>
#include <math.h>
#include <limits>
#include <algorithm>

class Vector2;
class LineSegment;

class Vector2 {
    public: double x, y;

public: 
    const static Vector2 zero;
    const static Vector2 left;
    const static Vector2 right;
    const static Vector2 up;
    const static Vector2 down;

    double Length() const {
        return sqrt(x * x + y * y);
    }
    
    Vector2(double x, double y) : x(x), y(y) {}

    double operator * (const Vector2& v) const {
        return this->x * v.x + this->y * v.y;
    }

    Vector2 operator + (const Vector2& v) const {
        return Vector2(this->x + v.x, this->y + v.y);
    }

    Vector2 operator - (const Vector2& v) const {
        return Vector2(this->x - v.x, this->y - v.y);
    }

    bool operator == (const Vector2& v) {
        return std::abs(this->x - v.x) < std::numeric_limits<double>::epsilon() && std::abs(this->y - v.y) < std::numeric_limits<double>::epsilon();
    }

    static double GetCross(const Vector2& v1, const Vector2& v2) {
        return v1.x * v2.y - v2.x * v1.y;
    }

    static double GetAngleArc(const Vector2& v1, const Vector2& v2) {
        return acos((v1 * v2) / (v1.Length() * v2.Length()));
    }

    static double GetAngleCos(const Vector2& v1, const Vector2& v2) {
        return (v1 * v2) / (v1.Length() * v2.Length());
    }

    static std::vector<int> GrahamScan(const std::vector<Vector2>& points) {
        std::vector<int> result;
        std::vector<int> sortedCopy;
        int startIndex = 0;
        sortedCopy.reserve(points.size());
        for (int i = 0; i < points.size(); i++) {
            if(points[i].y < points[startIndex].y) {
                startIndex = i;
            }
        }
        sortedCopy.push_back(startIndex);
        for (int i = 0; i < points.size(); i++) {
            if(i != startIndex){
                sortedCopy.push_back(i);
            }
        }
        std::sort(sortedCopy.begin() + 1, sortedCopy.end(), [points, startIndex](const int& a, const int& b) {
            return Vector2::GetAngleCos(points[a] - points[startIndex], Vector2::right) > Vector2::GetAngleCos(points[b] - points[startIndex], Vector2::right);
        });
        result.push_back(0);
        result.push_back(1);
        result.push_back(2);
        for(int i = 3; i < points.size(); i++) {
            auto top = points.at(result[result.size() - 1]);
            auto nextTop = points.at(result[result.size() - 2]);
            const Vector2& newPoint = points.at(sortedCopy[i]);
            while(true){
                double dir = DirectionHelper(nextTop, top, newPoint);
                if(std::abs(dir - 0) < std::numeric_limits<double>::epsilon()) {
                    dir = 0;
                }
                if(!(std::abs(Vector2::GetCross(top - nextTop, newPoint - top)) < std::numeric_limits<double>::epsilon() || dir > 0)) {
                    break;
                }
                result.pop_back();
                top = points.at(result[result.size() - 1]);
                nextTop = points.at(result[result.size() - 2]);
            }
            result.push_back(sortedCopy[i]);
        }
        return result;
    }

    class AngleWithZeroException : public std::exception {
        public:
        const char* what() const noexcept override {
            return "Trying to get angle with a zero vector";
        };
    };
private:
    static double DirectionHelper(const Vector2& root, const Vector2& point1, const Vector2& point2) {
        return Vector2::GetCross(
            point2 - root,
            point1 - root
        );
    }
};

const Vector2 Vector2::zero(0, 0);
const Vector2 Vector2::up(0, 1);
const Vector2 Vector2::down(0, -1);
const Vector2 Vector2::left(-1, 0);
const Vector2 Vector2::right(1, 0);

class LineSegment {
public:
    Vector2 start, end;

    Vector2 DirectionVector() {
        return this->end - this->start;
    }

    LineSegment(const Vector2& start, const Vector2& end) : start(start), end(end) {}

    static bool SegmentsIntersect(const LineSegment& seg1, const LineSegment& seg2) {
        double d1 = Direction(seg2.start, seg2.end, seg1.start);
        double d2 = Direction(seg2.start, seg2.end, seg1.end);
        double d3 = Direction(seg1.start, seg1.end, seg2.start);
        double d4 = Direction(seg1.start, seg1.end, seg2.end);

        if(std::abs(d1 - 0) < std::numeric_limits<double>::epsilon()) d1 = 0;
        if(std::abs(d2 - 0) < std::numeric_limits<double>::epsilon()) d2 = 0;
        if(std::abs(d3 - 0) < std::numeric_limits<double>::epsilon()) d3 = 0;
        if(std::abs(d4 - 0) < std::numeric_limits<double>::epsilon()) d4 = 0;

        if(((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) && 
        ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))){
            return true;
        }

        if(d1 == 0 && OnSegment(seg2.start, seg2.end, seg1.start)){
            return true;
        }

        if(d2 == 0 && OnSegment(seg2.start, seg2.end, seg1.end)){
            return true;
        }

        if(d3 == 0 && OnSegment(seg1.start, seg1.end, seg2.start)){
            return true;
        }

        if(d4 == 0 && OnSegment(seg1.start, seg1.end, seg2.end)){
            return true;
        }

        return false;
    }
private:
    static double Direction(const Vector2& root, const Vector2& point1, const Vector2& point2) {
        return Vector2::GetCross(
            point2 - root,
            point1 - root
        );
    }

    static bool OnSegment(const Vector2& start, const Vector2& end, const Vector2& point) {
        if (((std::min(start.x, end.x) <= point.x) && (point.x <= std::max(start.x, end.x))) && ((std::min(start.y, end.y) <= point.y) && (point.y <= std::max(start.y, end.y)))) {
            return true;
        }
        return false;
    }
};

class AccodingSolution{
private:
    AccodingSolution() {}
public:
    static void DoSomethingNTimes(void (*Function)(void)){
        int dataCount;
        std::cin >> dataCount;
        for(int i = 0; i < dataCount; i++){
            Function();
        }
    }
};

void Function(){
    int xBuffer, yBuffer;
    std::cin >> xBuffer >> yBuffer;
    Vector2 P1(xBuffer, yBuffer);
    std::cin >> xBuffer >> yBuffer;
    Vector2 Q1(xBuffer, yBuffer);
    std::cin >> xBuffer >> yBuffer;
    Vector2 P2(xBuffer, yBuffer);
    std::cin >> xBuffer >> yBuffer;
    Vector2 Q2(xBuffer, yBuffer);
    LineSegment line1(P1, Q1);
    LineSegment line2(P2, Q2);
    Vector2 line1Vector = Q1 - P1;
    Vector2 line2Vector = Q2 - P2;
    bool intersect = LineSegment::SegmentsIntersect(line1, line2);
    if(intersect) {
        std::cout << "intersect" << '\n';
    } else {
        if(Vector2::GetCross(line1Vector, line2Vector) == 0) {
            std::cout << "parallel" << '\n';
        } else {
            std::cout << "neither" << '\n';
        }
    }
}

int main(){
    AccodingSolution::DoSomethingNTimes(Function);   
}