# Change Log vs Upstream

This is a workspace snapshot comparison against `pret/pokefirered` at
`upstream/master` (`c75f3523`, merge base with this branch). The local branch
contains 31 commits beyond that baseline. At the time of analysis, the
workspace differed in 1,109 tracked paths (845 added, 261 modified, 3 deleted)
and contained 42 untracked paths. This includes both committed fork changes and
current uncommitted workspace changes; it is not a clean-branch-only summary.

## Main Changes

- **Portuguese localization:** Set Portuguese as the default game language and
  add its game code/language handling. Translate in-game text, map dialogue,
  item, move, species, trainer, and region names; update character/font and
  interface graphics for localized text. The README now describes the
  Portuguese FireRed/LeafGreen project.
- **Gameplay and quality-of-life changes:** Add Emerald-style inherited-nature
  handling, allow the party Select button to swap Pokemon, add a
  recurring Snorlax encounter, adjust Hall of Fame PC behavior, and add special
  ambient-cry handling. Includes battle-message, daycare, field movement, and
  map/event fixes.
- **Faraway Island and Mew:** Add island map/event content and Mew encounter and
  overworld behavior, with supporting map layouts, tileset and character
  graphics, Old Sea Map item graphics, and island/Mew music. Some of the new
  map and graphics files are currently untracked in the workspace.
- **Maps and game data:** Update map layouts, map definitions, scripts, and text
  across Kanto and the Sevii Islands. Expand or revise wild encounters, item
  data, regional map data, trainer/Pokedex text, and gender-specific Pokemon
  sprite assets (so far not implemented in-game).
- **Audio:** Update song and voice-group registrations. Notable additions include Mew
  battle music and Faraway Island music.
- **Build and tooling:** Add Poryscript build integration and its tool/config
  files, update Portuguese linker-symbol generation and related build
  configuration, and adjust spritesheet/build rules.

## File Areas

- `config.mk`, `Makefile`, `constants/`, `README.md`, `.github/`, linker scripts
- `data/maps/`, `data/layouts/`, `data/scripts/`, `data/text/`, `data/tilesets/`,
  `data/event_scripts.s`, and game-data tables under `src/data/`
- `src/` and `include/`, especially battle, daycare, field, menu, storage, and
  Faraway Island code
- `graphics/`, including UI/font assets, map assets, Pokemon sprites, and Mew
- `sound/`, including `direct_sound_samples/`, `songs/`, song tables, and voice
  groups
- `tools/` and `spritesheet_rules.mk`

## Workspace-Only Files

The 42 untracked paths comprise 6 Faraway Island/HousePC layout files, 6 map
files for Faraway Island Exterior and Harbor, 19 Faraway Island tileset files,
6 graphics assets (Old Sea Map, map preview, and bike-stop sprites), 3 local
tool executables, one local ROM image, and `config error.txt`. The map, tileset,
and graphics files appear to be project content; the executables, ROM image,
and error text are local build or diagnostic artifacts. These files are not
part of the tracked history yet.

Three tracked files were removed: `.gitignore` files under `tools/gbafix`,
`tools/gbagfx`, and `tools/wav2agb`.