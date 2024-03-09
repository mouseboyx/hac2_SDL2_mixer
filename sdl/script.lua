api_version = "1.0.0"

some_global_var=""
local hac2lib = package.loadlib("hac2_SDL2_mixer.dll", "luaopen_hac2lib")()
SDLinit()
Mix_AllocateChannels(12)
mix_handle={Mix_LoadWAV("soundfile2.wav"),Mix_LoadWAV("soundfile1.wav"),Mix_LoadWAV("soundfile3.wav")}
--Mix_PlayChannel(1,mix_handle)


function register_callbacks()
    register_callback(cb['HIT_DETECT'], "hit_detect")
    register_callback(cb['PLAYER_ENVIRONMENTAL_DEATHS'], "player_environmental_death")
end

function player_environmental_death(event, victim, player, timestamp)
	if(victim == player) then
		if(event == 6) then
            hud_message(_VERSION)
			
		end
    end
end
hit_counter=0
channel_counter=1
file_counter=1
function hit_detect(event, killer, victim, player, timestamp)
    Mix_HaltChannel(channel_counter)
    Mix_PlayChannel(channel_counter,mix_handle[file_counter])
    hud_message(hit_counter)
    file_counter=file_counter+1
    if (file_counter>3) then
        file_counter=1
    end
    channel_counter=channel_counter+1
    if (channel_counter>12) then
        channel_counter=1
    end
    
    hit_counter=hit_counter+1
end


