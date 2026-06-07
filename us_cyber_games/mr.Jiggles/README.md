# Mr. Jiggles (Forensics)

## Steps:
1. Open the file, check it is actually a JPEG with `file`
```
$ file TheCatMrJiggles.jpg 
TheCatMrJiggles.jpg: JPEG image data, Exif Standard: [TIFF image data, big-endian, direntries=6, orientation=upper-left, xresolution=86, yresolution=94, resolutionunit=2], progressive, precision 8, 2359x2613, components 3
```
2. Use `Exiftool` to read meta information
```
$ exiftool TheCatMrJiggles.jpg 
ExifTool Version Number         : 13.55
File Name                       : TheCatMrJiggles.jpg
Directory                       : .
File Size                       : 1595 kB
File Modification Date/Time     : 2026:06:06 22:51:29-04:00
File Access Date/Time           : 2026:06:06 22:52:11-04:00
File Inode Change Date/Time     : 2026:06:06 22:52:09-04:00
File Permissions                : -rw-rw-r--
File Type                       : JPEG
File Type Extension             : jpg
MIME Type                       : image/jpeg
Comment                         : U1ZJQlJHe1kwdV9GMHVuRF9Ncl9KMUdnTDMkIX0=
Exif Byte Order                 : Big-endian (Motorola, MM)
Orientation                     : Horizontal (normal)
X Resolution                    : 72
Y Resolution                    : 72
Resolution Unit                 : inches
Y Cb Cr Positioning             : Centered
Exif Version                    : 0232
Components Configuration        : Y, Cb, Cr, -
Flashpix Version                : 0100
Color Space                     : sRGB
Profile CMM Type                : Little CMS
Profile Version                 : 4.4.0
Profile Class                   : Display Device Profile
Color Space Data                : RGB
Profile Connection Space        : XYZ
Profile Date Time               : 2026:05:13 04:39:32
Profile File Signature          : acsp
Primary Platform                : Microsoft Corporation
CMM Flags                       : Not Embedded, Independent
Device Manufacturer             : 
Device Model                    : 
Device Attributes               : Reflective, Glossy, Positive, Color
Rendering Intent                : Perceptual
Connection Space Illuminant     : 0.9642 1 0.82491
Profile Creator                 : Little CMS
Profile ID                      : 0
Profile Description             : GIMP built-in sRGB
Profile Copyright               : Public Domain
Media White Point               : 0.9642 1 0.82491
Chromatic Adaptation            : 1.04788 0.02292 -0.05022 0.02959 0.99048 -0.01707 -0.00925 0.01508 0.75168
Red Matrix Column               : 0.43604 0.22249 0.01392
Blue Matrix Column              : 0.14305 0.06061 0.71393
Green Matrix Column             : 0.38512 0.7169 0.09706
Red Tone Reproduction Curve     : (Binary data 32 bytes, use -b option to extract)
Green Tone Reproduction Curve   : (Binary data 32 bytes, use -b option to extract)
Blue Tone Reproduction Curve    : (Binary data 32 bytes, use -b option to extract)
Chromaticity Channels           : 3
Chromaticity Colorant           : Unknown
Chromaticity Channel 1          : 0.64 0.33002
Chromaticity Channel 2          : 0.3 0.60001
Chromaticity Channel 3          : 0.15001 0.06
Device Mfg Desc                 : GIMP
Device Model Desc               : sRGB
Image Width                     : 2359
Image Height                    : 2613
Encoding Process                : Progressive DCT, Huffman coding
Bits Per Sample                 : 8
Color Components                : 3
Y Cb Cr Sub Sampling            : YCbCr4:4:4 (1 1)
Image Size                      : 2359x2613
Megapixels                      : 6.2
```
3. Notice the strange line as the comment, it looks like its encrypted. Likely base64 because of the `=`, use `cyberchef` to decrypt

## Solution:
```
SVIBRG{Y0u_F0unD_Mr_J1GgL3$!}
```
