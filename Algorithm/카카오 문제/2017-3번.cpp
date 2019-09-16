//
//  main.cpp
//  0909_algorithm
//
//  Created by Hayeon Kim on 04/09/2019.
//  Copyright © 2019 Hayeon Kim. All rights reserved.
//카카오 2017 3

#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <string.h>
#include <algorithm>
#define    cacheHit    1
#define cacheMiss    5

using namespace std;
int cacheCheck(int cacheSize, int* cacheFrequency, vector<string> &cache, string data);
int solution(int cacheSize, vector<string> cities);
int main(void)
{
    int testCase;
    string arr[] = {"Jeju", "Pangyo", "Seoul", "NewYork", "LA", "Jeju", "Pangyo", "Seoul", "NewYork", "LA"};
    string arr1[] = {"Jeju", "Pangyo", "Seoul", "Jeju", "Pangyo", "Seoul", "Jeju", "Pangyo", "Seoul"};
    string arr2[] = {"Jeju", "Pangyo", "Seoul", "NewYork", "LA", "SanFrancisco", "Seoul", "Rome", "Paris", "Jeju", "NewYork", "Rome"};
    string arr3[] = {"Jeju", "Pangyo", "NewYork", "newyork"};
    string arr4[] = {"Jeju", "Pangyo", "Seoul", "NewYork", "LA"};
    vector<string> citi(arr, arr + (sizeof(arr) / sizeof(arr[0])));
    vector<string> citi1(arr1, arr1 + (sizeof(arr1) / sizeof(arr1[0])));
    vector<string> citi2(arr2, arr2 + (sizeof(arr2) / sizeof(arr2[0])));
    vector<string> citi3(arr3, arr3 + (sizeof(arr3) / sizeof(arr3[0])));
    vector<string> citi4(arr4, arr4 + (sizeof(arr4) / sizeof(arr4[0])));
    
    testCase = solution(3, citi);
    testCase = solution(3, citi1);
    testCase = solution(2, citi2);
    testCase = solution(5, citi2);
    testCase = solution(2, citi3);
    testCase = solution(0, citi4);
    
    return 0;
}

int solution(int cacheSize, vector<string> cities)
{
    int answer = 0;            // 실행 시간
    int *cacheFrequency = new int[cacheSize + 1]; // cache 발생빈도(사용시간)
    
    vector<string> cache(cacheSize);
    memset(cacheFrequency, 0, sizeof(cacheFrequency) * cacheSize);
    
    // string process
    int size = cities.size();
    for(int i = 0; i < size; i ++) {
        // cache안의 내용을 체크
        answer += cacheCheck(cacheSize, cacheFrequency, cache, cities[i]);
    }
    
    /************ 결과 확인하기 위한 코드 ************/
    cout << "citi size : " << size << endl;
    cout << "cache size : " << cache.size() << endl;
    cout << "runtime : " << answer << "\n" << endl;
    /*********************************************/
    
    delete cacheFrequency;
    
    return answer;
}

int cacheCheck(int cacheSize, int* cacheFrequency, vector<string> &cache, string data)
{
    unsigned int lowFreCache = 0; // 가장 빈도수가 낮은 캐시 순서
    int runTime = 0;               // cacheHit or Miss
    
    // 가장 사용 빈도수(시간)가 낮은 캐시 순서 체크
    for(int i = 0; i < cacheSize; i ++) {
        if(cache[i] == "") {
            lowFreCache = i;
            break;
        } else if(cacheFrequency[i] < cacheFrequency[lowFreCache]) {
            lowFreCache = i;
        }
    }
    
    //  Cache Hit
    for(int i = 0; i < cacheSize; i ++) {
        if(!stircmp(cache[i].c_str(), data.c_str())) { // 대소문자를 구분하지 않고 문자열 비교
            cacheFrequency[i] += 1; // cache 사용(빈도)수 증가
            runTime = cacheHit;
            return runTime;
        }
    }
    
    // Cache Miss
    if(cacheSize) { // cache가 1개라도 있을 경우만 새롭게 캐시 넣음
        for(int i = 0; i < cacheSize; i ++) {
            if(i != lowFreCache) cacheFrequency[i] -= 1;
        }
        cache[lowFreCache] = data;
        cacheFrequency[lowFreCache] = 1; // 빈도 증가
    }
    
    runTime = cacheMiss; // 캐시안에 문자열이 없으므로 cacheMiss
    
    return runTime;
}
