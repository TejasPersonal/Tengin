# Tengin
Personal practice project which is example usage of the beautifully written modern RAII SDL abstraction (src/sdl.hpp).
Includes SDL, SDL_image, SDL_ttf.

# Clone

```sh
git clone https://github.com/TejasPersonal/Tengin.git
cd Tengin
```

## Dependencies

- SDL (version 3.x.x)
- SDL_image (version 3.x.x)
- SDL_ttf (version 3.x.x)

## Clone

## Unix Compilation

- Dynamic Linking
  ```sh
  clang++ -o build/totpad src/main.cpp -lSDL3 -lSDL3_image -lSDL3_ttf
    ```

- Static Linking
  ```sh
  clang++ -o build/totpad src/main.cpp -static $(pkg-config --libs --static SDL3 SDL3-image SDL3-ttf)
    ```

### Run

```sh
cd build
./totpad
```

https://github.com/user-attachments/assets/0bbdd572-481e-4184-9616-21a6e765872e
