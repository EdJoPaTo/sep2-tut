#include <dirent.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

using namespace std;

//! check the current working directory (qnx: /tmp) for existing files. If there is another one file than the current running one -> something squishy
int checkWorkingDir( char* currentProcessName ) {
    char cCurrentPath[FILENAME_MAX];
    int error = 0;

    if (!getcwd(cCurrentPath, sizeof(cCurrentPath))) {
        cout << "get current dir failed!" << endl;
        return -1;
    }

    cout << "The current working directory is " << cCurrentPath << endl;


    DIR* dirp = opendir(cCurrentPath);
    dirent* dp;
    while ((dp = readdir(dirp)) != NULL) {
        if (!strcmp(dp->d_name, currentProcessName)) {
            // Found myself -> ignore
        } else if (!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, "..")) {
            // ignore
        } else {
            // found something else
            cout << "Found something squishy: " << cCurrentPath << "/" << dp->d_name << "!!!" << endl;
            error = -1;
        }
    }

    closedir(dirp);
    return error;
}

int main(int argc, char *argv[]) {
    if (checkWorkingDir( argv[ 0 ] ) != 0) {
        perror( "working Dir is strange" );
        return -1;
    }

    cout << "running" << endl;

    // never use a while (true) on a realtime system
    while (true) { }

    return 0;
}
