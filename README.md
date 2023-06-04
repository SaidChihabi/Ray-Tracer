# Ray-Tracer

This is a simple ray tracing program written in C++, using the SFML library for graphics display. Ray tracing is a rendering technique for generating an image by tracing the path of light as pixels in an image plane and simulating the effects of its encounters with virtual objects. This project demonstrates a basic implementation of ray tracing, rendering a single sphere in a 3D space and an interactive light source.

## Dependencies

- C++17
- SFML 2.5.1 or higher
- CMake 3.10 or higher

## Building and Running the Project

### Building

This project uses CMake for building. To build the project, navigate to the project directory and run the following commands:

```sh
mkdir build
cd build
cmake ..
make
```
This will create the Ray-Tracer executable within the build directory.

## Running
To run the application, simply execute the binary:
```
./Ray-Tracer
```
## Controls

Move the mouse around the window to change the light source position. The lighting on the sphere will adjust accordingly.

## License

This project is open source, under the terms of [your license](./LICENSE).

## Contributing

Contributions, issues, and feature requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## Support

If you have any questions or need help with running the project, feel free to contact the project owner.
