# Change Log vs Upstream

This summarizes the local branch compared with `pret/pokefirered` at
`upstream/master` (`037335f4`, the original common baseline), through commit
`aa7f07c83`.

## Main Changes

- **Portuguese localization:** Set Portuguese as the default game language and
  add its game code and language handling. Translate in-game text, map dialogue,
  item, move, species, trainer, and region names; update character, font, and
  interface graphics for localized text. Portuguese item and Pokémon messages
  select the appropriate definite or indefinite article, including gender and
  number, and clarify party prompts for teaching, using, and giving items.
  All 378 item records have Portuguese name and description fields; entries
  awaiting translation retain English placeholders. Rework naming-screen
  accent-mark handling and update the README
  to describe the Portuguese FireRed/LeafGreen project.
- **Gameplay and quality of life:**
  - Add Emerald-style inherited natures and replace the same-species breeding
    compatibility bonus with a bonus for Pokémon from the same evolution line,
    increasing their egg chances. Pokémon from the same evolution line could
    already breed before this change. The new bonus stacks with the existing
    different-Trainer bonus, allowing maximum compatibility.
  - Miltank and Tauros are now considered fully compatible when breeding, and
    breeding either with a Ditto, or Miltank with a compatible Pokémon, can yield
    an egg of either Miltank or Tauros.
  - Similarly, Nidoran Female (and evolution line) and Nidoran Male (and evolution
    line) can also yield each other, like in later generations, as opposed to only
    Nidoran Female being able to have both, as it was originally.
  - Make bred Pokémon start at level 1 and hatch faster when the party includes
    a Pokémon with Flame Body or Magma Armor, like it is in Emerald and onward.
  - Trainer Tower rewards are randomized from a pool specific to each challenge
    and can be received after every completion, not just the first.
  - Add Destiny Knot and the six Power items to the game, including their
    breeding effects and the Power items' EV-training effects. Add Focus Sash
    as a battle item. Breeding also supports inherited Poké Balls and the
    Masuda Method's extra shiny rolls. Most of these items are Trainer Tower
    rewards; Destiny Knot is found in Altering Cave.
  - Add the Shiny Charm as a reward. It adds 2 shiny rolls, with a second Charm
    adding 1 more (3 total). An active White Flute or a lead Pokémon with
    Illuminate or Arena Trap adds 1 roll; these two bonuses do not stack with
    each other. The Masuda Method adds 6 rolls to eggs from parents with
    different languages. Applicable bonuses stack.
  - Implement Emerald-style field ability effects, including encounter-rate
    and species-selection changes, Cute Charm favoring opposite-gender Pokémon
    of the same evolutionary line, and a small Lightning Rod bonus to VS Seeker
    matches.
  - Allow Teleport to be used anywhere and refine fishing encounter selection.
  - Prevent trades involving Pokémon holding restricted items until the held
    item is removed, those being the aforementioned newly added items; this
    is done to prevent invalid items being sent to versions without them.
  - Let Select swap Pokémon in the party as a shortcut.
  - Add recurring post-game Snorlax encounters and ambient-cry randomization,
    with special handling for legendary and static encounters.
  - Swarm retains its Emerald effect of making ambient cries occur more often,
    at a slightly higher rate than in Emerald. Any non-Egg Pokémon with Swarm
    in the party activates this effect; it need not be the lead Pokémon. There
    is also a very rare chance to hear the roaming Legendary's cry wherever it
    can roam, regardless of where it may actually be (1/1024; 1/512 with
    Swarm).
  - A wild cry heard after standing still for a while increases the chance of
    encountering that Pokémon next, including while fishing. Swarm raises the
    cry-based chance of selecting that species from 20% to 50% when a Pokémon
    with Swarm is in the party and that species is available in the encounter
    table. This applies to the roaming Legendary also, only it'll always have
    a 3/4 chance of appearing regardless of Swarm, along with having a much
    longer cooldown before the next cry when this happens.
  - In addition to Emerald's chance to select the highest level within a slot's
    level range, Pressure, Hustle, and Vital Spirit can now favor the
    highest-max-level entry for the selected species, and less often the
    highest-max-level entry in the whole encounter table. This gives them an
    effect in grass and cave encounters, where slots have fixed levels and
    Emerald's range-based effect does nothing. Ties among the highest-max-level
    entries are chosen at random.
  - Make Electric-type Pokémon immune to paralysis from all sources.
  - Revise Safari Zone turn handling: resolve flee checks when the wild Pokémon
    acts after the player's action, with Rock and Bait affecting the flee rate
    as usual. Also rebalance catch odds, add the Boosted Safari Ball selection,
    and keep Safari Balls in the bag during entry, throws, and exit.
  - Make Game Corner hidden coins renewable.
  - Add a warning before releasing Pokémon and prevent the release of Pokémon
    with Friendship of 250 or higher.
  - Revise the Celadon Department Store rooftop thirsty-girl event so each drink
    reward can be earned again after a 1,500-step cooldown; update its dialogue.
  - Prevent the Nugget Bridge exploit from awarding repeated Nuggets and add a
    pre-battle animation.
  - The Old Man's catching tutorial can be missed as a rare Easter egg gag.
- **Controls, menus, and text display:**
  - Add Normal, B=Walk, and One-Hand button modes. B=Walk reverses the usual
    run-button behavior; One-Hand maps L to A and Select to Start/menu actions,
    and supports canceling evolutions with Select.
  - Use L+R together for the Help System shortcut in Normal and B=Walk modes,
    leaving L and R available individually for their usual functions.
  - Add gender-specific dialogue fonts and options for colors, fonts, both, or
    inverted gender colors. Apply the selected style to dialogue, menus, shops,
    and related map messages.
  - Set the Bill's PC "Move Pokémon" and "Move Items" options as the default top
    entries instead of "Withdraw" and "Deposit", which are now at the bottom.
  - Allow faster left/right scrolling in the item bag and related menu views.
  - Allow Start to skip battle intros and transitions.
  - Update male/female shop-clerk text styling and add female clerks to several
    shops.
  - A handful of oversights have been revised and fixed. The build now defaults
    the BUGFIX and UBFIX settings to be turned on.
- **Battle fixes and rules:** Resolve the remaining Generation III battle
  glitches, including the Focus Punch and Mail cases, visual glitches, lingering
  LightningRod, a broad set of move-logic issues, and several double-battle AI
  issues; battle-record layout, Quest Log entries,
  and associated battle messages were revised, and a special message was added
  for a Pokémon hitting itself via Disobedience. Improve several HM moves: Flash
  now always hits, including midair, and lowers accuracy by two stages instead of
  one; Cut deals double damage to Grass-types and has 25 PP, Fly has 90 power,
  Strength has a 25% chance to raise the user's Attack, Waterfall can cause flinching,
  and Rock Smash has 40 power with a 65% chance to lower Defense.
- **Faraway Island and Mew:** Complete the Old Sea Map event: after Mewtwo is
  caught, an NPC in the Lavender Town Pokémon Center gives the map to unlock the
  ship route to Faraway Island. Add the island's exterior, harbor, and interior,
  along with Mew's step-driven hide-and-seek movement and encounter. Supporting
  assets include map layouts, tilesets, character and Old Sea Map graphics, and
  island and Mew music. (Map preview pending, using Seafoam Islands as placeholder)
- **Maps and game data:** Update map layouts, definitions, scripts, and text
  across Kanto and the Sevii Islands. Add stone-evolution Pokémon to wild
  encounter tables at a 1% rate (excluding Eeveelutions), and revise item data,
  regional map data, trainer/Pokédex text, and event encounters. Add
  gender-specific Pokémon sprite assets and display the gender-dependent forms
  in-game. Add the cloud weather effect on Celadon rooftops, and add a Cinnabar
  Island fisherman who gives the player the Good Rod if they do not already
  have it, preventing a possible softlock. Revise other map details and event
  dialogue, including the S.S. Anne ticket and Daisy's grooming messages to
  match text styles. The Pokédex treats gender-difference forms as the same
  entry; other event content was also revised. Add a post-game Pewter Museum
  Pikachu scene and expand Two Island's shop stock with Dive Balls.
- **Audio:** Update song and voice-group registrations. Add Mew battle music and
  Faraway Island music (uses the Abandoned Ship theme from RSE).
- **Build and tooling:** Add Poryscript build integration and its tool/config
  files, update Portuguese linker-symbol generation and related build
  configuration, adjust spritesheet/build rules, ignore additional save-slot
  backup extensions, and enable `BUGFIX` and `UBFIX` by default.

## To-do

- Continue the translation work.
- Allow the L and R buttons to be used for field item shortcuts, like Select.
- Update the move relearner to include moves from a Pokémon's pre-evolutions.

## File Areas

- `config.mk`, `Makefile`, `constants/`, `README.md`, `.github/`, linker scripts
- `data/maps/`, `data/layouts/`, `data/scripts/`, `data/text/`, `data/tilesets/`,
  `data/event_scripts.s`, and game-data tables under `src/data/`
- `src/`, especially battle, daycare, field, menu, naming screen, Quest Log,
  storage, and Faraway Island code
- `graphics/`, including UI/font assets, map assets, Pokémon sprites, and Mew
- `sound/`, including `direct_sound_samples/`, `songs/`, song tables, and voice
  groups
- `tools/` and `spritesheet_rules.mk`
