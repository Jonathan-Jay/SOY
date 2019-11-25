#include <Windows.h>
#include <conio.h>
#include <string>
#pragma comment(lib, "winmm.lib")
//To use this function call a sound file from assets/Audio_Files/ in the brackets
//Example Usage:
// PlaySingleSound("Jumpscare.mp3")
void PlaySingleSound(std::string Filename);