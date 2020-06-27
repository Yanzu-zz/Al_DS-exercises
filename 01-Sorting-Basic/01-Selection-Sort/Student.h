#include <iostream>
#include <string>

using namespace std;

struct Student
{
  string name;
  int score;

  bool operator<(const Student &otherStudent)
  {
    // 成绩相同时按照姓名排序，否则按照分数排序
    return score != otherStudent.score ? score < otherStudent.score : name < otherStudent.name;
  }

  friend ostream &operator<<(ostream &os, const Student &student)
  {
    os << "Student:" << student.name << " " << student.score << endl;
    return os;
  }
};
