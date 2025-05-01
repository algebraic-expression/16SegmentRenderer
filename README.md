# 16 Segment Renderer
A lightweight text renderer, designed for situations where using TTF fonts are overkill.

This software requires and uses SDL2, a cross-platform development library.
SDL2 is licensed under the zlib/libpng license.

This project does not use SDL_ttf, and is much more lightweight in code size as compared to SDL_ttf.
Short text may often be required for different kinds of cases, for instance, displaying of a number as
percentage, or maybe even a short product code. Such situations often do not require the use of a
complete font. In fact, font renderers are quite loaded in size and also require the font file itself
to be present on site of execution. The features a font provides are mostly unused in these situations
and adds up to redundant code. Font renderers also require some startup code for initialization.

Thus, to prevent inefficiencies, lightweight text renderers may be used. 16SegmentRenderer takes
inspiration from 16 segment displays for the text style that is displayed on-screen, and does not use
any fonts (TTFs, OTFs, etc.). Instead, the lines are directly rendered onto the current rendering
target (usually, the screen).

However, it is to be noted that the extensive usage of these rendering functions are discouraged,
since they do not utilize the hardware acceleration capabilities provided by SDL effectively (being
written for use with short texts, majorly). It would also be wise to use uppercase letters in such
constrained situations (such as displaying short product codes, as mentioned above) to work with the
ambiguity caused by the limitations of 16 segment displays.

If the extensive use of this text renderer cannot be avoided, it is recommended to render the
characters that are to be used into a texture, and can be rendered from the texture, as this approach
respects the hardware acceleration offered by the SDL API.
