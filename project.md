# Pokemon Emerald Decompilation Project

## Project Overview

**Project Name:** pokeemerald
**Type:** Complete decompilation of Pokemon Emerald Version for Game Boy Advance
**Organization:** pret (Pokemon Reverse Engineering Team)
**Purpose:** Reverse-engineers the original Pokemon Emerald binary ROM into human-readable C source code and assembly. When compiled, produces a byte-for-byte identical ROM to the original game.

**Target ROM SHA1:** `f3ae088181bf583e55daf962a92bb46f4f1d07b7`

**Repository Size:** ~227MB
**Lines of Code:** ~421,000+ lines of C code across 309 source files

---

## Platform & Architecture

### Hardware Target: Game Boy Advance (GBA)
- **Processor:** ARM7TDMI (32-bit RISC)
- **EWRAM:** 256KB external working RAM
- **IWRAM:** 32KB internal working RAM
- **ROM:** Up to 32MB ROM space
- **Display:** 240x160 pixels, tile-based rendering
- **Audio:** M4A/MP2K sound engine with 4 hardware channels + 2 DMA channels

### Core Architecture Pattern
Event-driven game loop with callback-based state management. The entire game operates through a two-callback system where states transition via `SetMainCallback2()`.

### Main Execution Loop
```
AgbMain() [src/main.c:89]
├── Hardware initialization (GPU, interrupts, sound, RTC, flash)
├── Main Loop (infinite):
    ├── ReadKeys() - Input handling
    ├── Soft reset check (A+B+Start+Select)
    ├── Link/multiplayer handling
    ├── UpdateLinkAndCallCallbacks()
    │   ├── callback1 (optional update function)
    │   └── callback2 (main state machine)
    ├── PlayTimeCounter_Update()
    ├── MapMusicMain()
    └── WaitForVBlank()
```

### Interrupt System
- **VBlank:** Graphics updates, sound, link sync, RNG
- **HBlank:** Scanline effects
- **VCount:** Line 150 timing
- **Serial:** Link cable communication
- **Timer:** Sound and timing

---

## Directory Structure & Organization

### `/src` - C Source Code (309 files, ~421K lines)

**Core Systems:**
- `main.c` - Entry point and main loop
- `overworld.c` - Overworld game state
- `event_object_movement.c` - NPC/player movement

**Battle System (66+ files):**
- `battle_script_commands.c` (10K+ lines) - Battle script interpreter
- `battle_main.c` - Core battle engine
- `battle_controllers.c` - Player/AI/partner controllers
- `battle_ai_*.c` - AI decision making
- `battle_anim_*.c` - Battle animations
- `battle_message.c` - Battle text system
- Battle logic for moves, abilities, items, status effects

**Pokemon System:**
- `pokemon.c` - Core Pokemon data and functions
- `pokemon_storage_system.c` - PC box system
- `pokemon_animation.c` - Pokemon sprite animations
- `egg.c` - Breeding system
- `daycare.c` - Daycare mechanics

**UI/Menu Systems:**
- `party_menu.c` - Party screen
- `pokedex.c` - Pokedex interface
- `start_menu.c` - Pause menu
- `option_menu.c` - Options screen
- `bag.c` - Inventory system

**Field/Overworld:**
- `field_weather.c` - Weather effects
- `field_effect.c` - Field animations
- `field_player_avatar.c` - Player sprite and movement
- `wild_encounter.c` - Random encounters

**Special Features:**
- Battle Frontier (7 facilities): `battle_tower.c`, `battle_dome.c`, etc.
- Contests: `contest.c`, `contest_painting.c`, `pokeblock.c`
- Secret Bases: `secret_base.c`
- Berry System: `berry.c`, `berry_crush.c`, `berry_blender.c`

**Multiplayer:**
- `link.c` - Link cable communication
- `record_mixing.c` - Record sharing
- `wireless_*` files - Wireless adapter (RFU) support
- `union_room.c` - Multiplayer lobby

**Save System:**
- `save.c` - Save data management
- `load_save.c` - Loading saves
- Checksum verification and flash memory interface

**Graphics Engine:**
- `graphics.c`, `sprite.c` - Sprite/OAM system
- `bg.c` - Background layer management
- `palette.c` - Color palette management
- `decompress.c` - LZ77/RLE decompression
- `tileset_anims.c` - Animated tiles

**Sound:**
- `m4a.c` - M4A sound engine
- `sound.c` - Sound effect playback
- `pokemon_cries.c` - Pokemon cry system

### `/include` - Header Files (326 files)

**Key Directories:**
- `constants/` - Game constants (species, items, moves, abilities, maps, flags, etc.)
- `gba/` - GBA hardware register definitions
- Function declarations and data structure definitions for all systems

### `/data` - Game Data

**Major Components:**
- `maps/` - **519 map directories** with JSON definitions
- `layouts/` - Map layout binary data
- `scripts/` - Event and interaction scripts
- `text/` - All in-game text strings
- `battle_scripts_1.s`, `battle_scripts_2.s` - Battle logic scripts
- `battle_anim_scripts.s` - Battle animations (400K+ lines)
- Species data, item data, move data, trainer data
- Multiboot ROM data

### `/graphics` - Visual Assets (64 subdirectories)

**Contains:**
- Pokemon sprites (front, back, shiny, icons) for 386 species
- Trainer sprites and classes
- Battle interfaces and animations
- UI elements (menus, fonts, icons, windows)
- Field effects and object event sprites
- Title screen, intro sequences, credits
- Raw PNG files converted to GBA formats (.4bpp, .8bpp, .gbapal, .lz)

### `/sound` - Audio Assets

**Structure:**
- `songs/` - **420 MIDI music files** (game soundtrack)
- `direct_sound_samples/` - Sound effects and Pokemon cries
- `voicegroups/` - Instrument definitions
- M4A sound engine configuration

### `/asm` - Assembly Code

**Contains:**
- `macros/` - Assembly macros (events, battles, movements, maps, scripting)
- Low-level system code
- Constants shared between C and assembly

### `/tools` - Build Tools (13 custom tools)

**Key Tools:**
- `gbagfx` - Graphics format converter (PNG ↔ GBA formats)
- `mapjson` - Map JSON processor
- `mid2agb` - MIDI to GBA music converter
- `scaninc` - Dependency scanner for include files
- `preproc` - Preprocessor for text and charmap
- `gbafix` - ROM header fixer
- `wav2agb` - WAV to GBA sound converter
- `jsonproc` - JSON data processor
- `ramscrgen` - RAM script generator

### Other Important Directories
- `/constants` - Assembly constants
- `/libagbsyscall` - GBA BIOS syscall wrappers

---

## Technologies & Build System

### Languages
- **C (gnu89)** - Primary source language (~421K lines)
- **ARM Assembly** - Low-level code and data definitions
- **JSON** - Map and data definitions
- **GNU Make** - Build system orchestration

### Compilers

**1. agbcc (Primary)**
- Custom GBA C compiler based on GCC 2.95
- Required for matching builds (byte-perfect ROM)
- Produces identical code to original game
- Built from separate repository

**2. arm-none-eabi-gcc (Modern)**
- devkitARM toolchain
- For modern builds (not byte-perfect)
- Enabled with `make modern`
- Better optimization and warnings

### Build Commands
```bash
make                 # Build pokeemerald.gba (agbcc)
make compare         # Build and verify SHA1 match
make modern          # Build with modern GCC
make clean           # Clean build artifacts
make -j$(nproc)      # Parallel build
```

### Build Outputs
- `pokeemerald.gba` - Main ROM (non-modern)
- `pokeemerald_modern.gba` - Modern compiler build
- `pokeemerald.elf` - ELF binary with debug symbols
- `pokeemerald.map` - Link map
- `pokeemerald.sym` - Symbol file

### Build Process Flow
```
Source Files (.c, .s)
    ↓
[Compilation] → Object files (.o)
    ↓
Assets (PNG, MIDI, JSON, text)
    ↓
[Conversion Tools] → Binary data (.bin, .s)
    ↓
[Linking] → pokeemerald.elf
    ↓
[objcopy] → pokeemerald.gba
    ↓
[gbafix] → Fixed ROM header
    ↓
[SHA1 check] → Verify match
```

### Dependencies
**Required:**
- GCC/binutils
- arm-none-eabi-binutils
- libpng (graphics processing)
- git
- agbcc (built separately)

**Optional:**
- devkitARM (for modern builds)

---

## Major Game Systems

### 1. State Management System
- **Callback-based architecture** - Two callback system (callback1, callback2)
- **State transitions** via `SetMainCallback2(newStateFunction)`
- **Main states:** Title → Intro → Overworld → Battle → Menu → etc.
- Each major screen/mode has its own callback2 function

### 2. Overworld System
**Core Components:**
- Map rendering with tilemap system
- Object events (NPCs, items, player)
- Movement engine with collision detection
- Map connections and warping
- Field effects (weather, animations)
- Script event triggers

**Key Files:**
- `src/overworld.c` - Main overworld state
- `src/event_object_movement.c` - Movement system
- `src/field_effect.c` - Visual effects
- `src/field_weather.c` - Weather system

### 3. Battle System
**Architecture:**
- Turn-based combat engine
- Battle controllers: Player, Opponent, Partner, Recorded
- Battle script interpreter (domain-specific language)
- Move effect system (354 moves with unique effects)
- AI decision engine
- Battle animations

**Battle Types:**
- Single battles (1v1)
- Double battles (2v2)
- Multi battles (2v2 with partner)
- Link battles (multiplayer)
- Wild encounters
- Trainer battles

**Key Components:**
- `src/battle_main.c` - Core battle loop
- `src/battle_script_commands.c` - Script interpreter (10K+ lines)
- `src/battle_controllers.c` - Controller system
- `src/battle_ai_*.c` - AI logic
- `data/battle_scripts_*.s` - Battle logic scripts

### 4. Pokemon System
**Data Structure:**
```c
struct Pokemon {
    personality    // Determines nature, gender, ability, shininess
    otId           // Original trainer ID
    nickname       // Custom name
    language       // Origin language
    otName         // Original trainer name
    markings       // Player markings
    checksum       // Data integrity

    // Encrypted data:
    species, item, experience, ppBonuses
    friendship, moves[4], pp[4]
    hp, attack, defense, speed, spAttack, spDefense
    evs[6], ivs[6], condition, pokerus
    ribbons, status, level, mail, etc.
}
```

**Key Features:**
- 386 Pokemon species (Gen 1-3)
- Personality value system
- IV/EV stat system
- Nature system (25 natures)
- Ability system (77 abilities)
- Evolution system with multiple methods
- Storage system (PC boxes: 14 boxes × 30 Pokemon = 420 slots)

**Key Files:**
- `src/pokemon.c` - Core Pokemon logic
- `src/pokemon_storage_system.c` - PC system
- `include/constants/species.h` - All species constants

### 5. Graphics Engine
**Tile-Based System:**
- 8×8 pixel tiles as base unit
- 4 background layers (BG0-BG3)
- Hardware sprites (OAM - Object Attribute Memory)
- Multiple color modes (4bpp = 16 colors, 8bpp = 256 colors)
- Compression support (LZ77, RLE)

**Key Components:**
- Background management (scrolling, priority)
- Sprite/OAM system (128 hardware sprites max)
- Palette management (16 palettes × 16 colors)
- Metatile system (2×2 or 4×4 tile groups)
- Animation system

**Key Files:**
- `src/sprite.c` - Sprite management
- `src/bg.c` - Background layers
- `src/palette.c` - Color palettes
- `src/graphics.c` - Graphics utilities

### 6. Sound Engine (M4A/MP2K)
**Nintendo's MusicPlayer2000:**
- Sequenced music playback from MIDI
- Direct sound samples (22KHz, 8-bit)
- 4 hardware channels + 2 DMA channels
- Pokemon cry synthesis
- Sound effects mixing

**Key Files:**
- `src/m4a.c` - Sound engine core
- `src/sound.c` - Sound effect playback
- `sound/songs/` - 420 MIDI files
- `sound/direct_sound_samples/` - Audio samples

### 7. Menu/UI System
**Components:**
- Window system with customizable frames
- Text rendering with special characters
- List menus with cursor navigation
- Context-sensitive menus

**Major Menus:**
- Party Menu - Pokemon management
- Bag - Inventory system (5 pockets: Items, Key Items, Poke Balls, TMs/HMs, Berries)
- Pokedex - Pokemon encyclopedia
- Start Menu - Main pause menu
- Options - Game settings
- Trainer Card - Player info

### 8. Save System
**Architecture:**
- Three save blocks:
  - **SaveBlock1** - Player data, party, PC, items, gameplay state
  - **SaveBlock2** - Options, Pokedex, trainer info, statistics
  - **PokemonStorage** - PC boxes (separate due to size)
- Checksum verification for data integrity
- Flash memory interface (128KB save data)
- Multiple save sectors for redundancy

**Key Files:**
- `src/save.c` - Save operations
- `src/load_save.c` - Load operations
- `include/global.h` - SaveBlock structures

### 9. Multiplayer System
**Features:**
- Link cable communication (4-player support)
- Wireless adapter (RFU) support
- Record mixing (share achievements, trainer info)
- Link battles and trades
- Union Room (multiplayer lobby)

**Key Files:**
- `src/link.c` - Link cable system
- `src/record_mixing.c` - Record sharing
- `src/union_room.c` - Multiplayer lobby
- `src/wireless_*.c` - Wireless adapter support

### 10. Scripting System
**Event Scripts:**
- Custom bytecode scripting language
- Used for NPCs, events, cutscenes
- Commands for: text display, item giving, Pokemon battles, warps, etc.
- Compiled from `data/scripts/`

**Battle Scripts:**
- Separate scripting system for battle logic
- Handles: move effects, status conditions, weather, abilities
- Located in `data/battle_scripts_*.s`

---

## Special Game Features

### Battle Frontier (Post-Game Content)
**7 Major Facilities:**
1. **Battle Tower** - Standard battles, rental Pokemon
2. **Battle Dome** - Tournament-style battles
3. **Battle Factory** - Rental Pokemon with swapping
4. **Battle Palace** - Pokemon battle autonomously based on nature
5. **Battle Arena** - Timed battles with point system
6. **Battle Pike** - Adventure with random rooms
7. **Battle Pyramid** - Maze exploration with items

**Supporting Areas:**
- Ranking Hall - View records
- Exchange Service Corner - Trade Battle Points for items

**Key Files:**
- `src/battle_tower.c`, `src/battle_dome.c`, etc.
- `src/frontier_util.c` - Shared utilities

### Contest System
**Features:**
- 5 contest types: Cool, Beauty, Cute, Smart, Tough
- 4 ranks per type: Normal, Super, Hyper, Master
- Contest appeal system with move combos
- Contest AI opponents
- Pokeblock creation (Berry Blender minigame)

**Key Files:**
- `src/contest.c` - Main contest logic
- `src/pokeblock.c` - Pokeblock system
- `src/berry_blender.c` - Berry Blender minigame

### Berry System
**Features:**
- Plant and grow berries (real-time with RTC)
- 43 berry types
- Berry Blender - Make Pokeblocks for contests
- Berry Crush - Multiplayer minigame
- Berry Powder shop

**Key Files:**
- `src/berry.c` - Berry growth system
- `src/berry_crush.c` - Multiplayer minigame
- `src/berry_blender.c` - Pokeblock creation

### Secret Bases
**Features:**
- Player-customizable hideouts
- Furniture and decoration system
- Sharable via record mixing
- Located in special trees/cave indents

**Key Files:**
- `src/secret_base.c` - Secret base system
- `src/decoration.c` - Furniture system

### Other Features
- **Pokenav** - In-game device (Map, Match Call, Condition Graph)
- **Mystery Events/Mystery Gift** - Event distribution system
- **E-Reader** support - Scan cards for content
- **TV Shows** - In-game TV programming based on player actions
- **Game Corner** - Slots, roulette gambling
- **Lottery** - Daily lottery drawing
- **Cycling Road** - Time trial records
- **Trick House** - Puzzle challenges

---

## Key Game Content

### Pokemon
- **386 Species** (Generations 1-3 complete)
- **354 Moves** with unique effects
- **77 Abilities**
- **25 Natures** affecting stat growth
- Shiny variants (1/8192 chance)

### World
- **519 Maps** including:
  - 16 cities/towns
  - 34 routes
  - Dungeons, caves, towers
  - Underwater areas
  - Battle Frontier
  - Secret locations
- Dynamic weather (rain, sandstorm, drought, etc.)
- Day/night events (RTC-based)

### Items
**Categories:**
- General items (Potions, status healers, etc.)
- Poke Balls (various types)
- TMs/HMs (50 TMs + 8 HMs)
- Berries (43 types)
- Key Items (story and special items)
- Hold items (battle effects)

### Trainers
- Multiple trainer classes
- Gym Leaders (8)
- Elite Four (4) + Champion
- Team Aqua/Magma (villains)
- Battle Frontier Brains
- Rival battles

---

## Configuration & Settings

### Build Configuration

**Makefile Variables:**
- `MODERN` (0/1) - Compiler selection
- `COMPARE` (0/1) - Enable SHA1 comparison
- `O_LEVEL` - Optimization level
- `GAME_VERSION` - EMERALD
- `GAME_LANGUAGE` - ENGLISH

**include/config.h:**
- `NDEBUG` - Disable debugging features
- Language selection
- Unit system (IMPERIAL/METRIC)
- `BUGFIX` - Enable bug fixes from original game

### Game Settings (Options Menu)
- Text speed (Slow, Mid, Fast)
- Battle scene (On/Off)
- Battle style (Shift/Set)
- Sound (Mono/Stereo)
- Button mode (Normal/LR/L=A)
- Frame type (window graphics)

### Important Files
- `charmap.txt` - Character encoding map
- `rom.sha1` - Expected ROM checksum
- `ld_script.ld` - Memory layout linker script
- `midi.cfg` - MIDI conversion configuration
- Map JSONs (`data/maps/*/map.json`) - Individual map configs

---

## Testing & Verification

### Primary Testing Method
**Binary Comparison:**
```bash
make compare
```
- Compiles ROM and compares SHA1 hash
- Goal: Byte-perfect match with original (f3ae088181bf583e55daf962a92bb46f4f1d07b7)
- Output: "pokeemerald.gba: OK" if matching

### No Traditional Unit Tests
- No formal test suite (no pytest, jest, etc.)
- Verification through:
  1. Successful compilation
  2. Matching binary output
  3. Manual playtesting in emulators
  4. Community testing and bug reports

### CI/CD
**GitHub Actions** (`.github/workflows/build.yml`):
- Runs on: pushes to master, pull requests
- Builds both compare and modern versions
- Generates symbol files
- Ensures builds remain stable

### Debugging Support
- Symbol files (.sym) for debugger integration
- Debug builds: `make modern DINFO=1`
- AGBPrint/mGBA print logging (when NDEBUG undefined)
- ELF files with debug symbols

---

## Development Workflow

### Typical Modification Flow
1. **Read existing code** - Understand current implementation
2. **Make changes** - Modify C/assembly source files
3. **Build** - `make -j$(nproc)`
4. **Test** - Run in emulator (mGBA, VBA, etc.)
5. **Verify** - `make compare` (may not match if adding features)
6. **Debug** - Use symbol files with debugger if needed

### Common Tasks

**Adding a Pokemon:**
1. Modify species constants
2. Add sprite graphics (front, back, icon, palette)
3. Add base stats, type, abilities
4. Add Pokedex entry
5. Update evolution/encounter tables if needed

**Adding a Move:**
1. Add move constant
2. Define move data (power, accuracy, type, PP)
3. Implement move effect if unique
4. Add battle animation
5. Add to level-up/TM/tutor tables

**Modifying Maps:**
1. Edit map JSON (`data/maps/*/map.json`)
2. Modify tileset if needed
3. Add/edit object events (NPCs, items)
4. Edit map scripts (`data/scripts/`)
5. Rebuild map data

### Modding Community
This decompilation serves as the **primary base** for Pokemon Emerald ROM hacks, enabling:
- Source-level modifications
- Type-safe changes
- Better debugging
- Feature additions
- Bug fixes
- Quality-of-life improvements
- Complete ROM hacks

---

## Technical Deep Dive

### Memory Layout (ld_script.ld)
```
0x02000000: EWRAM (256KB) - Main working RAM
0x03000000: IWRAM (32KB) - Fast working RAM
0x08000000: ROM (32MB max) - Game code and data
0x0E000000: SRAM (64KB) - Save data
```

### Callback System Details
The game's state machine operates through two callback pointers:
- `gMain.callback1` - Optional first update (rarely used)
- `gMain.callback2` - Main state function (always active)

**State Transition:**
```c
SetMainCallback2(CB2_Overworld);  // Switch to overworld
```

Each callback runs once per frame (60 FPS).

### Battle Script Language
Custom bytecode language for battle logic:
```
callnative BS_ItemRestoreHP
various BS_ATTACKER, VARIOUS_CONSUME_BERRY
removeitem BS_ATTACKER
printstring STRINGID_PKMNCHOSENITEMBERRY
waitmessage
```

Commands handle: damage, status, stat changes, weather, abilities, etc.

### Graphics Data Flow
```
PNG files (graphics/)
    ↓ [gbagfx tool]
.4bpp/.8bpp (tile graphics)
.gbapal (palette data)
    ↓ [compression]
.lz (compressed data)
    ↓ [linked into ROM]
Binary data in ROM
    ↓ [runtime decompression]
VRAM (tile/sprite rendering)
```

### Save Data Encryption
Pokemon data is encrypted using XOR with personality value and OT ID:
- Prevents casual hex editing
- Allows validation via checksum
- Compatible with official games

---

## Project Goals & Philosophy

### Primary Goals
1. **Preservation** - Document Pokemon Emerald's code for posterity
2. **Education** - Teach GBA game development and reverse engineering
3. **Modding Base** - Provide foundation for ROM hacks
4. **Accuracy** - Achieve byte-perfect match with original ROM

### Development Philosophy
- **Readability over cleverness** - Code should be understandable
- **Matching first** - Prioritize matching original binary
- **Document everything** - Comments explain non-obvious code
- **Community-driven** - Open to contributions and improvements

### Non-Goals
- Not a remake or remaster
- Not an emulator
- Not legal advice (users must own original game)
- Not adding new features (that's for forks/ROM hacks)

---

## Common Patterns & Conventions

### Naming Conventions
- **Functions:** `PascalCase` - e.g., `CreateMonWithNature()`
- **Constants:** `SCREAMING_SNAKE_CASE` - e.g., `SPECIES_PIKACHU`
- **Structs:** `PascalCase` - e.g., `struct Pokemon`
- **Global vars:** `gCamelCase` - e.g., `gPlayerParty`
- **Static vars:** `sCamelCase` - e.g., `sBackupMap`
- **Macros:** `SCREAMING_SNAKE_CASE` or `PascalCase`

### Code Organization
- Related functionality grouped in single files
- Clear header/source separation
- Constants in `include/constants/`
- Data in `src/data/` or `data/`

### Common Macros
- `ARRAY_COUNT(arr)` - Get array length
- `min(a, b)`, `max(a, b)` - Math utilities
- `T1_READ_*`, `T2_READ_*` - Read from different save blocks

---

## Relationships to Other Projects

### pret Organization Projects
- **pokered** - Pokemon Red/Blue decompilation
- **pokeyellow** - Pokemon Yellow decompilation
- **pokegold** - Pokemon Gold/Silver decompilation
- **pokecrystal** - Pokemon Crystal decompilation
- **pokefirered** - Pokemon FireRed/LeafGreen decompilation
- **pokeruby** - Pokemon Ruby/Sapphire decompilation
- **pokeemerald** - This project

All share similar:
- Build systems and tools
- Coding conventions
- Documentation practices
- Community members

### Dependencies on Other Repos
- **agbcc** - Separate compiler repository
- Uses base devkitARM tools

---

## Quick Reference

### File Location Quick Guide
- **Main loop:** `src/main.c`
- **Battle engine:** `src/battle_main.c`, `src/battle_script_commands.c`
- **Overworld:** `src/overworld.c`, `src/event_object_movement.c`
- **Pokemon data:** `src/pokemon.c`, `src/data/pokemon/`
- **Items:** `src/item.c`, `src/data/items.h`
- **Moves:** `src/data/battle_moves.h`
- **Maps:** `data/maps/*/map.json`
- **Scripts:** `data/scripts/`
- **Graphics:** `graphics/` (PNG sources)
- **Music:** `sound/songs/` (MIDI files)
- **Species constants:** `include/constants/species.h`
- **Map constants:** `include/constants/map_groups.h`

### Important Symbols
- `gMain` - Main game state structure
- `gPlayerParty` - Player's party (array of 6 Pokemon)
- `gSaveBlock1Ptr` - Pointer to main save data
- `gSaveBlock2Ptr` - Pointer to options/Pokedex
- `gBattleScriptCurrInstr` - Current battle script pointer
- `gSpecialVar_Result` - Script return value
- `gTasks` - Task system array

### Build Troubleshooting
- **"pokeemerald.gba: FAILED"** - Binary doesn't match, intentional if you modified code
- **Missing agbcc** - Build agbcc from separate repository
- **"cannot find -lc"** - Install arm-none-eabi-newlib
- **Slow build** - Use `make -j$(nproc)` for parallel build
- **Graphics errors** - Check libpng installation

---

## Summary

Pokemon Emerald is a **complex, feature-rich GBA game** with:
- **10+ major interconnected systems** (battle, overworld, Pokemon, graphics, sound, save, multiplayer, etc.)
- **519 unique maps** with events and scripts
- **386 Pokemon species** with full battle mechanics
- **Extensive post-game content** (Battle Frontier, contests, etc.)
- **Robust multiplayer features** (battles, trading, record mixing)

This decompilation represents **years of reverse engineering work** by the Pokemon ROM hacking community, providing a **complete, buildable source code** that exactly matches the original commercial release when compiled with the appropriate tools.

The codebase demonstrates **excellent organization**, **comprehensive documentation**, and serves as both a **preservation effort** and a **foundation for the modding community** to create enhanced versions and complete ROM hacks at the source code level.
