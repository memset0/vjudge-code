#include <algorithm>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string.h>
using namespace std;

const int Max = 20 + 10;
const int CityMax = 110;
const double PI = 3.1415926;
const double Radius = 6378.0;

struct City {
  char name[Max];
  double latitude, longitude;
  double x, y, z;

  friend bool operator==(const City &a, const City &b) {
    if (!strcmp(a.name, b.name)) return true;
    else
      return false;
  }
};

City c[CityMax];

struct Vector {
  double x, y, z;
};

double radian(double d) { return d * PI / 180.0; }

double square(double d) { return d * d; }

double angle(Vector &v, City &c) { return acos((v.x * c.x + v.y * c.y + v.z * c.z) / sqrt(square(v.x) + square(v.y) + square(v.z)) / sqrt(square(c.x) + square(c.y) + square(c.z))); }

City *findCity(City *first, City *end, City &c) {
  while (first != end) {
    if (!strcmp(first->name, c.name)) return first;
    first++;
  }
  return first;
}

int main() {
  int index = 0;
  City A, B, C;

  while (scanf("%s", c[index].name) && strcmp(c[index].name, "#") != 0) {
    scanf("%lf %lf", &c[index].latitude, &c[index].longitude);

    c[index].x = Radius * cos(radian(c[index].latitude)) * sin(radian(c[index].longitude));
    c[index].y = Radius * cos(radian(c[index].latitude)) * cos(radian(c[index].longitude));
    c[index].z = Radius * sin(radian(c[index].latitude));

    index++;
  }

  Vector vec;
  double ang, dist;
  while (scanf("%s", A.name) && strcmp(A.name, "#")) {
    scanf("%s %s", B.name, C.name);

    City *a, *b, *cen;
    // a = findCity(c, c+index, A), b = findCity(c, c+index, B), cen = findCity(c, c+index, C);//调用函数0MS通过
    a = find(c, c + index, A), b = find(c, c + index, B), cen = find(c, c + index, C); // 泛型花了16MS
    if (a == c + index || b == c + index || cen == c + index) {
      printf("%s is ? km off %s/%s equidistance.\n", C.name, A.name, B.name);
    } else {
      vec.x = a->x - b->x, vec.y = a->y - b->y, vec.z = a->z - b->z;
      if (vec.x == 0.0 && vec.y == 0.0 && vec.z == 0.0) dist = 0;
      else {
        ang = fabs(PI / 2 - angle(vec, *cen));
        dist = ang * Radius + 0.5;
      }
      printf("%s is %d km off %s/%s equidistance.\n", C.name, (int)(dist), A.name, B.name);
    }
  }
}