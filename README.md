# Practice_SDL2-Library
Utilization of the SDL2 library and the SDL2_image extension for C/C++ game development practices

# Primitive Geometry
Demonstration of drawing rectangles, lines, dots, and manipulating colors inside of the renderer.

![GraphicDesignPashun](https://github.com/pigghead/Practice_SDL2-Library/blob/master/Practice_SDL2-Library/media/graphicdesignmypashun.PNG)

# Color Keying
Setting a particular pixel to be transparent when blitted onto the screen. This is done inside LTexture::loadFromFile() using SDL_SetColorKey. 

# Spritesheets/ Clipping
Specifying a particular space on a sprite sheet to be rendererd. This is done by using the SDL_RenderCopy() override that has the Renderer, Texture, srcrect (source), and dstrect (destination) parameters. Source rect specifies the space on the spritesheet we want to include in the texture, and destination is the space on the renderer we want the source to appear.