# Tengin
Personal practice project which includes example usage of the beautifully written modern RAII SDL abstraction (src/sdl.hpp).
Includes SDL, SDL_image, SDL_ttf.

## Supported OS:

- MacOS
- Windows (MSYS2)
- Linux
- FreeBSD

## Clone

```sh
git clone https://github.com/TejasPersonal/Tengin.git
cd Tengin
```

## Dependencies

- C/C++ toolchain
- SDL (version 3.x.x)
- SDL_image (version 3.x.x)
- SDL_ttf (version 3.x.x)

### Dependency installation examples:

- Arch Linux:
  ```sh
  sudo pacman -S clang sdl3 sdl3-image sdl3-ttf --noconfirm
  sudo pacman -S pkgconf # for static linking
  ```

- Windows (MSYS2):
  - CLANG*:
    ```sh
    pacman -S pactoys --noconfirm
    pacboy -S clang sdl3 sdl3-image sdl3-ttf --noconfirm
    pacboy -S pkgconf # for static linking
    ```
  - MSYS:
    ```sh
    pacman -S clang sdl3 sdl3-image sdl3-ttf --noconfirm
    pacman -S pkgconf # for static linking
    ```

- MacOS:

  Install Homebrew if not installed
  ```sh
  /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
  ```
  Then:
  ```sh
  xcode-select --install
  brew install sdl3 sdl3_image sdl3_ttf
  brew install pkgconf # for static linking
  ```

## Unix Compilation using clang

- Dynamic Linking
  ```sh
  clang++ -o build/totpad src/main.cpp -lSDL3 -lSDL3_image -lSDL3_ttf
  ```

- Static Linking
  ```sh
  clang++ -o build/totpad src/main.cpp -static $(pkg-config --libs --static sdl3 sdl3-image sdl3-ttf)
  ```

Note: clang++ can be used interchangeably with g++ if available

## Run

```sh
cd build
./totpad
```

https://github.com/user-attachments/assets/0bbdd572-481e-4184-9616-21a6e765872e
