# Change Log vs Upstream

This is a workspace snapshot comparison against `pret/pokefirered` at
`upstream/master` (`037335f4`, merge base with this branch). The local branch
contains 40 commits beyond that baseline. The workspace differs in 1,148
tracked paths (884 added, 261 modified, 3 deleted) and has no non-ignored
untracked paths. This includes both committed fork changes and current
uncommitted workspace changes; it is not a clean-branch-only summary.

## Main Changes

- **Portuguese localization:** Set Portuguese as the default game language and
  add its game code and language handling. Translate in-game text, map dialogue,
  item, move, species, trainer, and region names; update character/font and
  interface graphics for localized text. All 376 item records now have
  Portuguese name and description fields; entries awaiting translation retain
  the English text as a placeholder. The README now describes the Portuguese
  FireRed/LeafGreen project.
- **Gameplay and quality-of-life changes:** Add Emerald-style inherited-nature
  handling, let the party Select button swap Pokémon, add a recurring Snorlax
  encounter, and adjust Hall of Fame PC behavior. Add ambient-cry
  randomization with special handling for legendary and static encounters.
  Change the Help System shortcut to require L and R together. Expand Pokémon
  breeding compatibility to include Pokémon in the same evolution line, rather
  than just matching the specific species in the daycare center. Also update
  battle messages, field movement, maps/events, Poké Mart text colors for male
  and female shop clerks, and the Pokémon release flow, not allowing release when
  a Pokémon has Friendship of 250 or higher.
- **Faraway Island and Mew:** Complete the Old Sea Map event: after Mewtwo is
  caught, a mysterious NPC in the Lavender Town Pokémon Center appears and gives
  the map to unlock the ship route to Faraway Island. Add the island's exterior,
  harbor, and interior, along with Mew's step-driven hide-and-seek movement and
  encounter. Supporting assets include map layouts, tilesets, character and
  Old Sea Map graphics, and island/Mew music.
- **Maps and game data:** Update map layouts, map definitions, scripts, and text
  across Kanto and the Sevii Islands. Add stone-evolution Pokémon to wild
  encounter tables at a 1% rate, and revise item data, regional map data,
  trainer/Pokedex text, and event encounters. Add gender-specific Pokémon
  sprite assets; these are not yet used in-game.
- **Audio:** Update song and voice-group registrations. Notable additions include Mew
  battle music and Faraway Island music. Uses the Abandoned Ship theme from RSE, much
  like in Emerald.
- **Build and tooling:** Add Poryscript build integration and its tool/config
  files, update Portuguese linker-symbol generation and related build
  configuration, and adjust spritesheet/build rules.

## To-do

- Implement the gender-difference Pokémon sprites in-game.
- Add later-generation Poke Ball inheritance rules to the breeding system.
- Allow the L and R buttons to be used for field item shortcuts, like Select.
- Update the move relearner to include moves from a Pokémon's pre-evolutions.

## File Areas

- `config.mk`, `Makefile`, `constants/`, `README.md`, `.github/`, linker scripts
- `data/maps/`, `data/layouts/`, `data/scripts/`, `data/text/`, `data/tilesets/`,
  `data/event_scripts.s`, and game-data tables under `src/data/`
- `src/` and `include/`, especially battle, daycare, field, menu, storage, and
  Faraway Island code
- `graphics/`, including UI/font assets, map assets, Pokémon sprites, and Mew
- `sound/`, including `direct_sound_samples/`, `songs/`, song tables, and voice
  groups
- `tools/` and `spritesheet_rules.mk`

## Workspace Status

There are currently no non-ignored untracked paths. Three tracked files were
removed relative to the baseline: `.gitignore` files under `tools/gbafix`,
`tools/gbagfx`, and `tools/wav2agb`.