This gives hac2 optic packs the ability for more audio functionality through SDL2_mixer.  Including concurent audio playing.

Place 4 dll files in the halo directory:

hac2_SDL2_mixer.dll

SDL2.dll

SDL2_mixer.dll

lua52.dll

Always call these 3 functions before anything else:

local hac2lib = package.loadlib("hac2_SDL2_mixer.dll", "luaopen_hac2lib")()

SDLinit()

Mix_AllocateChannels(12) --number of channels available to the script, you can theoretically allocate as many as you need

You can create a new folder inside the halo directory to store the .wav files, and load them like:
Mix_LoadWAV("my_folder/soundfile1.wav")

or:

You can put the .wav files inside the halo directory and load them like:
Mix_LoadWAV("soundfile1.wav")

These are wrapped from SDL2_mixer to the optic lua script:

https://wiki.libsdl.org/SDL2_mixer/CategoryAPI -- I didn't wrap all of the functions, just these:

Mix_Chunk=Mix_LoadWAV("filename.wav")  --returns a pointer/handle for the file and loads the .wav file

Mix_HaltChannel(Channel_Number)  --stops playing any audio on this channel (-1 for all channels)

Mix_PlayChannel(Channel_number,Mix_Chunk) --plays a specific Mix_Chunk on a specific channel (-1 for any available channel)

Note:

If you're running this on wine, my system seemed to throw an WSAPI error unless the windows version was set to:

WINDOWS XP
