# Air Traffic Sim

[![Action Status](https://github.com/icebox246/air-traffic-sim/actions/workflows/clang-format-check.yml/badge.svg)](https://github.com/icebox246/air-traffic-sim/actions)

## Building

Requirements:

- `raylib` (installed globally preferably)
- `g++`
- `make`
- `clang-format`

```console
make dev
make
./sim
```

## Running tests

Requirements - same as above

```console
make test
```

## Web build

To build for web you need to provide compiled raylib archive in
`thirdparty/libraylib.a` ([guide](http://localhost:3000)). Also because of
weird clang include priority it is best to provide `raylib.h` in
`thirdparty/raylib.h` (usually can be found in `/usr/include`).

Requirements:

- files mentioned above
- `emscripten` (`emcc` should be visible in `$PATH`)
- `make`
- some web server (`emrun` can be used)

```console
make web
emrun web
```

### Test online without building

Build of this application can be found here: [link](https://icebox246.itch.io/air-traffic-simulator).
Password is `12345678`.

## Credits

This package includes `raygui.h`, which is by raysan5:

raygui is licensed under an unmodified zlib/libpng license, which is an
OSI-certified, BSD-like license that allows static linking with closed source
software
