#pragma once


#include <Windows.h>
#include <string>
#include <list>
#include <iostream>
#include <functional>

using namespace std;
#define BUFFER_SIZE 128

bool getDevcieInfo(char* cmd, list<string> &resultList)
{
    char buffer[BUFFER_SIZE];
    bool ret = false;
    FILE* pipe = _popen(cmd, "r"); //�򿪹ܵ�����ִ������ 
    if(!pipe)
        return ret;

    char *name[20] = {"UUID","ProcessorId","SerialNumber"};
    int len0 = strlen(name[0]), len1 = strlen(name[1]), len2 = strlen(name[2]);
    bool isOk = false;
    while(!feof(pipe)) {
        if(fgets(buffer, BUFFER_SIZE, pipe)) {
            if(strncmp(name[0], buffer, len0) == 0
               || strncmp(name[1], buffer, len1) == 0
               || strncmp(name[2], buffer, len2) == 0) // �ܹ���ȷ��ȡ��Ϣ
            {
                isOk = true;
                continue;
            }
            if(isOk == false
               || strcmp("\r\n", buffer) == 0) //ȥ��windows���õĿ���
            {
                continue;
            }
            ret = true;
            resultList.push_back(string(buffer));
        }
    }
    _pclose(pipe); // �رչܵ� 
    return ret;
}



string getDeviceFingerPrint()
{
    list<string> strList;
    list<string>::iterator it;
    hash<string> str_hash;
    size_t num;
    char tmp[11] = {0};

    // ����UUID���ڣ���ʹ������UUID���ɻ���ָ��
    if(getDevcieInfo("wmic csproduct get UUID", strList)
       && (*strList.begin()).compare("FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF\r\n") != 0) {
        cout << *strList.begin();
        //cout << str_hash(*strList.begin()) << endl;
        num = str_hash(*strList.begin());
        sprintf(tmp, "%u", num);
        cout << string(tmp) << endl;
        //return string(tmp);
    }

    // ����UUID�����ڣ�ʹ��CPUID��BIOS���кš�Ӳ�����к����ɻ���ָ��
    string otherStr("");
    strList.clear();
    if(getDevcieInfo("wmic cpu get processorid", strList)) {
        otherStr.append(*strList.begin());
    }
    strList.clear();
    if(getDevcieInfo("wmic bios get serialnumber", strList)) {
        otherStr.append(*strList.begin());
    }
    strList.clear();
    if(getDevcieInfo("wmic diskdrive get serialnumber", strList)) {
        string allDiskNum("");
        // Ӳ�̿����ж��
        for(it = strList.begin(); it != strList.end(); it++) {
            allDiskNum.append(*it);
        }
        //cout << allDiskNum ;
        //cout << str_hash(allDiskNum) << endl;
        otherStr.append(*strList.begin());
    }
    cout << str_hash(otherStr) << endl;
    //memset(tmp,0,11);
    num = str_hash(otherStr);
    sprintf(tmp, "%u", num);
    //cout << string(tmp) << endl;
    return string(tmp);
}

int test_pipe_guid()
{
    std::hash<size_t> sz_hash;
    auto szz = sz_hash(4580540057644164606);




    string deviceFingerPrint = getDeviceFingerPrint();
    cout << deviceFingerPrint << endl;

    system("pause");
    return 0;
}

