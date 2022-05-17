#include <iostream>
#include <hdd.hpp>
#include <string>
#include <vector>

using namespace std;

int lba2chs(tLBA orig, tCHS *dest)
{
    dest->cyl = orig.lba / 15 / 63;
    dest->head = orig.lba / 15 % 63;
    dest->sec = orig.lba % 63 + 1;
    return 0;
}

int lba2large(tLBA orig, tLARGE *dest)
{
    dest->cyl = orig.lba / 63 / 255;
    dest->head = orig.lba / 63 % 255;
    dest->sec = orig.lba % 255 + 1;
    return 0;
}

int lba2idechs(tLBA orig, tIDECHS *dest)
{
    dest->cyl = orig.lba / 16 / 256;
    dest->head = orig.lba / 16 % 256;
    dest->sec = orig.lba % 256 + 1;
    return 0;
}

int chs2large(tCHS orig, tLARGE *dest)
{
    tLBA tmp;
    chs2lba(orig, &tmp);
    lba2large(tmp, dest);
    return 0;
}

int chs2idechs(tCHS orig, tIDECHS *dest)
{
    tLBA tmp;
    chs2lba(orig, &tmp);
    lba2idechs(tmp, dest);
    return 0;
}

int chs2lba(tCHS orig, tLBA *dest)
{
    dest->lba = (orig.head + 15 * orig.cyl) * 63 + orig.sec - 1;
    return 0;
}

int large2chs(tLARGE orig, tCHS *dest)
{
    tLBA tmp;
    large2lba(orig, &tmp);
    lba2chs(tmp, dest);
    return 0;
}

int large2idechs(tLARGE orig, tIDECHS *dest)
{
    tLBA tmp;
    large2lba(orig, &tmp);
    lba2idechs(tmp, dest);
    return 0;
}

int large2lba(tLARGE orig, tLBA *dest)
{
    dest->lba = (orig.head + 256 * orig.cyl) * 63 + orig.sec - 1;
    return 0;
}

int idechs2chs(tIDECHS orig, tCHS *dest)
{
    tLBA tmp;
    idechs2lba(orig, &tmp);
    lba2chs(tmp, dest);
    return 0;
}

int idechs2large(tIDECHS orig, tLARGE *dest)
{
    tLBA tmp;
    idechs2lba(orig, &tmp);
    lba2large(tmp, dest);
    return 0;
}

int idechs2lba(tIDECHS orig, tLBA *dest)
{
    dest->lba = (orig.head + 15 * orig.cyl) * 255 + orig.sec - 1;
    return 0;
}

int a_lba2chs (tCHS geometry, tLBA orig, tCHS *dest)
{
	int tmp;
	dest->cyl = (orig.lba / geometry.sec) / geometry.head;
    if (dest->cyl > geometry.cyl) {
        dest->cyl = geometry.cyl;
        dest->head = geometry.head;
        dest->sec = geometry.sec;
        return 0;
    }
	tmp = orig.lba % (geometry.head * geometry.sec);
	dest->head = tmp / geometry.sec;
	dest->sec = tmp % geometry.sec + 1;
	return 0;
}

int split(string str, unsigned short &c, unsigned short &h, unsigned short &s){
    char separator = '-';
    int lastIndex = 0;
    size_t firstSep = str.find(separator);
    size_t secondSep = str.find(separator, firstSep + 1);
    if(firstSep == string::npos || secondSep == string::npos){
        return -1;
    }
    try{
        c = stoi(str.substr(0, firstSep));
        h = stoi(str.substr(firstSep + 1, secondSep - firstSep - 1));
        s = stoi(str.substr(secondSep + 1));
    }
    catch(...){
        return -1;
    }
    
    return 0;
}

void createDisks(vector<tPART> &disks, tCHS geo, double size){
    bool haveActive = false;
    int count = 0;
    for(int i = 0; i < disks.size(); i++){
        if(!haveActive){
            cout << "Is this part is active? (y/n):";
            string activeAnswer;
            cin >> activeAnswer;
            if(activeAnswer[0] == 'y'){
                disks[i].activ = 1;
                haveActive = true;
            }
        }
        if (i == 0)
            disks[i].lba_beg.lba = 1;
        else {
            tLBA lba_tmp = {disks[i - 1].lba_beg.lba + disks[i - 1].size};
            disks[i].lba_beg = lba_tmp;
        }

        cout <<  "Enter size: ";
        cin >> disks[i].size;

        if (disks[i].size == 0)
        {
            disks[i].size = size;
            count++;
            a_lba2chs(geo, disks[i].lba_beg, &disks[i].beg);
            tLBA lba_tmp = {disks[i].lba_beg.lba + disks[i].size - 1};
            a_lba2chs(geo, lba_tmp, &disks[i].end);
            break;
        }

        size -= disks[i].size;
        count++;

        if (size <= 0){
            break;
        }
        a_lba2chs(geo, disks[i].lba_beg, &disks[i].beg);
        tLBA lba_tmp = {disks[i].lba_beg.lba + disks[i].size - 1};
        a_lba2chs(geo, lba_tmp, &disks[i].end);
    }
    if (!haveActive){
        disks[count-1].activ = 1;
    }
}

void printDisks(vector<tPART> disks){
    for(int i = 0; i < disks.size(); i++){
        cout << disks[i].activ << "\t";
        cout << disks[i].beg.cyl << "-" << disks[i].beg.head << "-" << disks[i].beg.sec << "\t";
        cout << disks[i].end.cyl << "-" << disks[i].end.head << "-" << disks[i].end.sec << "\t";
        cout << disks[i].lba_beg.lba << "\t";
	    cout << disks[i].size << endl;
    }
}

int hdd(){

    cout << "Input geometry (c-h-s): ";
    string inputStr;
    cin >> inputStr;

    tCHS geo;

    //Если не равно -1 (~(-1) = 0)
    if(~split(inputStr, geo.cyl, geo.head, geo.sec)){
        cout << "cyl = " << geo.cyl << endl;
        cout << "head = " << geo.head << endl;
        cout << "sec = " << geo.sec << endl;
    }
    else{
        cout << "Invalid input" << endl;
    }
    
    double size = geo.head * geo.cyl * geo.sec;
    cout << "Size: " << size / 2 / 1024 / 1024 << " GB" << endl;

    cout << "Input num of parts: " << endl;
    int numParts;
    cin >> numParts;

    vector<tPART> parts(numParts);

    createDisks(parts, geo, size);
    printDisks(parts);

    return 0;
}