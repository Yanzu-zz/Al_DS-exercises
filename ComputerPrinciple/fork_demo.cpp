#include <iostream>
#include <cstring>
#include <stdio.h>
#include <unistd.h>

using namespace std;

int main()
{
  pid_t pid;

  pid = fork();
  if (pid == 0)
  {
    cout << "这是一个子进程" << endl;
  }
  else if (pid > 0)
  {
    cout << "这是一个父进程" << endl;
    cout << "子进程ID：" << pid << endl;
  }
  else if (pid < 0)
  {
    cout << "创建进程失败" << endl;
  }

  return 0;
}