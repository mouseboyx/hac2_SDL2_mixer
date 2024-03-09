// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

using namespace std;
#include <windows.h>
#include <iostream>
#include "SDL2/include/SDL.h"
#include "SDL2_mixer/include/SDL_mixer.h"


extern "C"
{
#include "Lua524/include/lua.h"
#include "Lua524/include/lauxlib.h"
#include "Lua524/include/lualib.h"

}

/*
// Example C++ class
class MyClass {
public:
    int data;

    MyClass(int value) : data(value) {}

    int returnData() {
        // Just a simple method to return the data
        return data;
    }
};

extern "C" MyClass * createMyClass(int value) {
    return new MyClass(value);
}

// C++ function to delete an instance of MyClass
extern "C" void deleteMyClass(MyClass * instance) {
    delete instance;
}

// C++ function to access a method of MyClass
extern "C" void printData(MyClass * instance) {
    instance->returnData();
}

/*
// Proper wrapper function for createMyClass
int l_createMyClass(lua_State* L) {
    int value = luaL_checkinteger(L, 1);
    MyClass* instance = createMyClass(value);
    lua_pushlightuserdata(L, instance);
    return 1;
}

// Proper wrapper function for deleteMyClass
int l_deleteMyClass(lua_State* L) {
    MyClass* instance = static_cast<MyClass*>(lua_touserdata(L, 1));
    deleteMyClass(instance);
    return 0;
}

// Proper wrapper function for returnData
int l_returnData(lua_State* L) {
    MyClass* instance = static_cast<MyClass*>(lua_touserdata(L, 1));
    int result = instance->returnData();
    lua_pushinteger(L, result);
    return 1;
}
*/

// Proper wrapper function for SDLinit
int l_SDLinit(lua_State* L) {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {

        HWND hWnd = NULL;  // Handle to the owner window (NULL for no owner)
        LPCWSTR text = L"SDL initialization failed";  // Message to be displayed
        LPCWSTR caption = L"Error";  // Title of the message box
        UINT type = MB_OK;  // Type of the message box (OK button and Error icon)
        // Display the message box
        MessageBox(hWnd, text, caption, type);

        return 0;
    }

    // Initialize SDL_mixer
    // If you experience errors with wine, windows version to WINDOWS XP
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::string narrowString = Mix_GetError();
        std::wstring wideString(narrowString.begin(), narrowString.end());

        // Access LPCWSTR using c_str() method
        LPCWSTR wideCharString = wideString.c_str();
        HWND hWnd = NULL;  // Handle to the owner window (NULL for no owner)
        LPCWSTR text = wideCharString;  // Message to be displayed
        LPCWSTR caption = L"Error";  // Title of the message box
        UINT type = MB_OK;  // Type of the message box (OK button and Error icon)
        // Display the message box
        MessageBox(hWnd, text, caption, type);
        
        SDL_Quit();
        return 0;
    } else {
        /*
        HWND hWnd = NULL;  // Handle to the owner window (NULL for no owner)
        LPCWSTR text = L"SDL_mixer initialization success";  // Message to be displayed
        LPCWSTR caption = L"Success";  // Title of the message box
        UINT type = MB_OK;  // Type of the message box (OK button and Error icon)
        // Display the message box
        MessageBox(hWnd, text, caption, type);
        */
    }
    /*
    // Load the first sound file
    Mix_Chunk* sound1 = Mix_LoadWAV("soundfile1.wav");
    if (!sound1) {
        HWND hWnd = NULL;  // Handle to the owner window (NULL for no owner)
        LPCWSTR text = L"Failed to load sound1";  // Message to be displayed
        LPCWSTR caption = L"Error";  // Title of the message box
        UINT type = MB_OK;  // Type of the message box (OK button and Error icon)
        // Display the message box
        MessageBox(hWnd, text, caption, type);

        Mix_CloseAudio();
        SDL_Quit();
        return 0;
    }


    // Play the first sound
    if (Mix_PlayChannel(-1, sound1, 0) == -1) {

        HWND hWnd = NULL;  // Handle to the owner window (NULL for no owner)
        LPCWSTR text = L"Failed to play sound1";  // Message to be displayed
        LPCWSTR caption = L"Error";  // Title of the message box
        UINT type = MB_OK;  // Type of the message box (OK button and Error icon)
        // Display the message box
        MessageBox(hWnd, text, caption, type);


        Mix_FreeChunk(sound1);
        Mix_CloseAudio();
        SDL_Quit();
        return 0;
    }
    */
    
    return 0;
}

int l_Mix_LoadWAV(lua_State* L) {
    const char* file = lua_tostring(L, 1);
    Mix_Chunk* sound = Mix_LoadWAV(file);
    lua_pushlightuserdata(L, sound);
    return 1;
}

int l_Mix_PlayChannel(lua_State* L) {
    int channel = (int)luaL_checknumber(L, 1);
    Mix_Chunk* instance = static_cast<Mix_Chunk*>(lua_touserdata(L, 2));
    if (Mix_PlayChannel(channel, instance, 0) == -1) {

        HWND hWnd = NULL;  // Handle to the owner window (NULL for no owner)
        LPCWSTR text = L"Mix_PlayChannel failed";  // Message to be displayed
        LPCWSTR caption = L"Error";  // Title of the message box
        UINT type = MB_OK;  // Type of the message box (OK button and Error icon)
        // Display the message box
        MessageBox(hWnd, text, caption, type);
        return 0;
    }
}

int l_Mix_HaltChannel(lua_State* L) {
    int channel = (int)luaL_checknumber(L, 1);
    Mix_HaltChannel(channel);
    return 0;
}

int l_Mix_AllocateChannels(lua_State* L) {
    int channels = (int)luaL_checknumber(L, 1);
    Mix_AllocateChannels(channels);
    return 0;
}


extern "C" int __declspec(dllexport) __cdecl luaopen_hac2lib(lua_State * L) {


    /*
    lua_register(L, "createMyClass", l_createMyClass);
    lua_register(L, "deleteMyClass", l_deleteMyClass);
    lua_register(L, "returnData", l_returnData);*/
    lua_register(L, "SDLinit", l_SDLinit);
    lua_register(L, "Mix_LoadWAV", l_Mix_LoadWAV);
    lua_register(L, "Mix_PlayChannel", l_Mix_PlayChannel);

    lua_register(L, "Mix_HaltChannel",l_Mix_HaltChannel);

    lua_register(L, "Mix_AllocateChannels",l_Mix_AllocateChannels);
    return 0;
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

