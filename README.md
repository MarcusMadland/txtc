# txtc

txtc is a simple command-line tool designed to convert C/C++ files to plain text (txt) files. This utility is particularly useful for those who wish to add their source code repositories as training data for [RTX Chat AI](https://github.com/rtx-ai) or similar projects.

## Features

- Converts C/C++ files to plain text format.
- Minimalistic and straightforward tool focused solely on conversion.
- Free to use and modify according to your needs.

## Installation

You can clone this repository and build the tool using a C++ compiler.

```bash
git clone https://github.com/your_username/txtc.git
cd txtc
mkdir build
cd build
cmake ..
```

## Usage

Once compiled, you can use txtc from the command line:

```bash
./txtc input_folder output_folder -r 
```

Replace `input_file` with the folder to your C/C++ files and `output_file` with the desired name for the generated folder. Use the `-r` flag to recursively convert each child folder within the input folder.

## Contribution

Contributions are welcome! If you have any suggestions, bug fixes, or feature requests, feel free to open an issue or submit a pull request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgements

Special thanks to [RTX Chat AI](https://github.com/rtx-ai) for inspiring this project and providing the motivation to create a simple conversion tool.

## Disclaimer

This tool is provided as-is, without any warranties. Use it at your own risk.
