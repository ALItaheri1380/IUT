enum
{
    Mute = _IO('M', 1),      // Mute
    Unmute = _IO('U', 1),    // Unmute
    setVolume = _IO('S', 1), // setVolume
    getVolume = _IO('G', 1), // getVolume
};

struct headset_data
{
    int volume;
    char message[128];
};