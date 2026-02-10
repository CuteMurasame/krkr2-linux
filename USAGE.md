# Usage Guide

## Running Kirikiroid2 Games

Kirikiroid2 is a game engine for running visual novel games that use the KiriKiri engine format.

### Game Data

To run a game, you need:

1. **Game data files** - Usually in `.xp3` archive format or unpacked directories
2. **Game executable** - The `kirikiroid2` binary you compiled

### Basic Usage

```bash
# Run from a directory containing game data
cd /path/to/game/directory
kirikiroid2

# Or specify the game data path as an argument
kirikiroid2 /path/to/game/directory
```

### Game Data Structure

A typical game directory looks like this:
```
game_directory/
├── data.xp3          # Main game archive
├── patch.xp3         # Optional patch archive
├── scenario.xp3      # Scenario/script archive
└── startup.tjs       # Main script file
```

Or unpacked:
```
game_directory/
├── data/
│   ├── bgm/          # Background music
│   ├── bgv/          # Background voices
│   ├── image/        # Images and sprites
│   └── ...
├── scenario/         # Game scripts
└── startup.tjs       # Main script file
```

### Controls

Default keyboard controls (game-specific controls may vary):

- **Enter/Space** - Advance text, confirm
- **Escape** - Cancel, menu
- **Arrow Keys** - Navigate menus
- **Ctrl** - Skip text
- **Alt+Enter** - Toggle fullscreen

### Supported Formats

- **Archives**: XP3 format
- **Images**: PNG, JPEG, TLG (KiriKiri format), WebP
- **Audio**: Ogg Vorbis, WAV, Opus
- **Video**: MPEG, WebM (depending on FFmpeg support)
- **Scripts**: TJS (TJS2/KAG3 scripting language)

### Configuration

Configuration files are typically stored in:
- `~/.config/kirikiroid2/` (Linux standard)
- Or in the game directory

### Troubleshooting

**Game doesn't start:**
1. Check that game data files exist
2. Verify `startup.tjs` or equivalent entry point exists
3. Check console output for error messages

**No audio:**
1. Ensure OpenAL is installed
2. Check that audio files are in supported formats
3. Verify system audio is working

**Graphics issues:**
1. Update graphics drivers
2. Check OpenGL support (`glxinfo | grep "OpenGL version"`)
3. Try running with environment variables:
   ```bash
   LIBGL_ALWAYS_SOFTWARE=1 kirikiroid2
   ```

**Performance issues:**
1. Ensure you compiled with Release mode (`-DCMAKE_BUILD_TYPE=Release`)
2. Close other applications
3. Check system resources with `htop` or `top`

### Legal Notice

- You must own legitimate copies of games you run with Kirikiroid2
- Game data is copyrighted by respective developers/publishers
- Kirikiroid2 is for running games you legally own, not for piracy

### Getting Games

Compatible games are typically:
- Japanese visual novels using KiriKiri2/KirikiriZ engine
- Fan-made games using the KiriKiri engine
- Commercial games that you own

**Where to find compatible games:**
- Steam (some visual novels use KiriKiri)
- DLsite
- Official publisher websites
- Fan game communities (for free games)

**Note:** Always verify the game uses KiriKiri/KirikiriZ engine before purchasing.

### Resources

- Original KiriKiri: http://kikyou.info/tvp/
- KirikiriZ: https://github.com/krkrz/krkrz
- TJS2 Documentation: http://kikyou.info/tvp/docs/tjs2doc/

### Example Games

Some well-known games that may work with Kirikiroid2:
- Fate/stay night
- Clannad
- Steins;Gate (some versions)
- Many other visual novels

**Important:** Verify game compatibility before purchase.
