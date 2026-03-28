🎧 MP3 Tag Reader in C
📌 Overview

The MP3 Tag Reader is a C-based application designed to extract and modify metadata from MP3 files without using any external libraries. This project demonstrates low-level file handling and binary data processing, making it ideal for understanding how real-world file formats are structured.

🚀 Features
📖 Read MP3 metadata (ID3 tags)
✏️ Edit existing tag information
⚡ Works directly with binary data
🔍 No external libraries required
🎵 Extracted Metadata

The program retrieves the following details from an MP3 file:

Song Title
Artist Name
Album Name
Year of Release
Genre

🛠️ Technologies Used
C Programming
File Handling (fopen, fread, fseek, ftell)
Structures
Pointers
String Manipulation

⚙️ How It Works
Opens the MP3 file in binary mode
Navigates through the file using file pointers
Locates ID3 tag sections
Extracts metadata fields using structured parsing
Allows modification of selected fields

💡 Key Concepts Learned
Understanding binary file formats
Efficient use of pointers in C
Memory handling and data parsing
Debugging file-related issues
Real-world application of embedded C concepts

3️⃣ Available Operations

View MP3 metadata

Edit tag information

