txtc
==

Simple cross-platform command-line tool designed to convert C/C++ files to plain text (txt) files. 

[![License](https://img.shields.io/badge/license-BSD--2%20clause-blue.svg)](https://bkaradzic.github.io/bgfx/license.html)

Goals:

- Converts C/C++ files to plain text format.
- Minimalistic and straightforward tool focused solely on conversion.
- Free to use and modify according to your needs.

## Installation

You can get the compiled binary from latest release or clone the repository and build the tool using a C++ compiler.

```bash
git clone https://github.com/marcusmadland/txtc.git
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

Replace `input_folder` with the folder to your C/C++ files and `output_folder` with the desired name for the generated folder. Use the `-r` flag to recursively convert each child folder within the input folder.

Contact
-------

[marcus@madland.info](marcus@madland.info)  

Project page  
https://github.com/marcusmadland/txtc

[License (BSD 2-clause)](https://github.com/bkaradzic/bx/blob/master/LICENSE)
-----------------------------------------------------------------------------

<a href="http://opensource.org/licenses/BSD-2-Clause" target="_blank">
<img align="right" src="https://opensource.org/wp-content/uploads/2022/10/osi-badge-dark.svg" width="100" height="137">
</a>

	Copyright 2024 Marcus Madland
	
	Redistribution and use in source and binary forms, with or without modification,
	are permitted provided that the following conditions are met:
	
	   1. Redistributions of source code must retain the above copyright notice, this
	      list of conditions and the following disclaimer.
	
	   2. Redistributions in binary form must reproduce the above copyright notice,
	      this list of conditions and the following disclaimer in the documentation
	      and/or other materials provided with the distribution.
	
	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
	ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
	IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
	INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
	BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
	OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
	OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
	OF THE POSSIBILITY OF SUCH DAMAGE.
