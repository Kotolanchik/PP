#include <iostream>
#include <fstream>
#include <ctime>
#include <semaphore>
#include <thread>
#include <mutex>
#include <vector>
#include <string>
#include <chrono>
#include <condition_variable>

using namespace std;

void GenerateFile(int Count, int Size) {
    ofstream fout("V.txt");
    fout << Count << "\n";
    for (int i = 0; i < Count; i++) {
        for (int j = 0; j < Size; j++) {
            fout << rand() % 100 << ' ';
        }
        fout << "\n";
    }
}


int N;
condition_variable cv;
bool _var = false;
bool ret() { return _var; }

void  Func(mutex& mx, vector<int>& Array, string FileArr)
{
    ifstream fin(FileArr);
    string s;
    int M;
    fin >> M;
    fin.ignore();
    vector<int> V;
    for (int i = 0; i < M; i++)
    {
        getline(fin, s);
        fin.ignore();
        this_thread::sleep_for(chrono::milliseconds(1000));
        mx.lock();
        Array.clear();
        mx.unlock();
        while (!s.empty())
        {
            string a = s.substr(0, s.find(' '));
            s.erase(0, s.find(' ') + 1);
            V.push_back(stoi(a));
        }
        mx.lock();
        Array = V;
        V.clear();
        _var = true;
        cv.notify_one();//уведомляем ожидающий поток
        mx.unlock();
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

void SumFunc(mutex& mx, vector<int>& Array) {

    ofstream fout;
    fout.open("output.txt", ofstream::out);

    for (int i = 0; i < N; i++)
    {
        if (Array.empty()) {
            unique_lock<mutex> ulArr(mx);
            cv.wait(ulArr, ret);//Ждем массив от первого потока
        }
        mx.lock();
        vector<int> tmp;
        tmp = Array;
        mx.unlock();
        int S = 0;
        for (int i = 0; i < tmp.size(); i++) {
            S += tmp[i];
        }
        mx.lock();
        tmp.clear();
        _var = false;
        fout << S << "\n";
        mx.unlock();
        this_thread::sleep_for(chrono::milliseconds(2000));
    }

    fout.close();
}

int main()
{
    mutex mx;
    srand(time(0));
    GenerateFile(5, 10);
    vector<int> Array;
    int Sum = 0;
    N = 5;
    thread Tread1 = thread(Func, ref(mx), ref(Array), "V.txt"),
        Tread2 = thread(SumFunc, ref(mx), ref(Array));
    Tread1.join();
    this_thread::sleep_for(chrono::milliseconds(100));
    Tread2.join();
