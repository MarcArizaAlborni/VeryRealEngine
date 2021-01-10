# **_VeryRealEngine_** 

This is a university project made by two students of [CITM](https://www.citm.upc.edu/), 
in Barcelona. We made a 3D Game Engine in C & C++ during our 3rd year of Game Development Bachelor’s Degree. In our case we also used Wwise to implement our High Level Audio System.

# **_The Team_**

- **Gerard Romeu**
  - Github: [Gromeu2000](https://github.com/Gromeu2000)
  - Linkedin [HERE](https://www.linkedin.com/in/gerard-romeu-vidal/)
 
 - **Marc Ariza**
   - Github: [MarcArizaAlborni](https://github.com/MarcArizaAlborni)
   - Linkedin [HERE](https://www.linkedin.com/in/marc-ariza-alborni-0b2b431a2/)
   
![](https://raw.githubusercontent.com/MarcArizaAlborni/VeryRealEngine/main/Team_Picture.png)
_On the left Gerard, on the right Marc_
 
### **_Tasks Completed_**
 
#### **_Gerard Romeu_**
 
 - Mesh Loading
 - Textures Loading
 - Camera Controls
 - UI with ImGui
 - Time Management
 - Camera Component (Camera & Culling)
 - AABB and OBB
 - Wwise Implementation in code
 - Component Audio Source
 - Audio Play/Stop & Volume
 - Audio Reverb
 
#### **_Marc Ariza_**
 
 - Mesh Loading
 - Textures Loading
 - Image Loading
 - GameObjects
 - GameObjects Herarchy
 - Inspector
 - Resource Manager
 - Texture, Mesh, Transforms Components
 - Wwise Implementation in code
 - Spatial Audio (panning)
 - Component Audio Listener

# **_Core Subsystems_**

### UI

The UI was done using ImGui. The different menus are: Herarchy Menu, Inspector Menu, Time Management Menu, Resource Manager Menu and Console with Logs.

### GameObjects

GameObjects are are the fundamental objects that can represent meshes, cameras, audios, etc. They can have the following components:

#### Transform

Allows the user to change the position, rotation and scaling fo a certain Game Object.

#### Mesh

A simple 3D mesh that can be in screen.

#### Camera

A culling camera customizable.

#### Audio Source

A GameObject that has a source with an audio file to listen to.

#### Audio Listener

This Game Object allows all the audio source to be heared. It represents the ears of the users.

### Audio Subsystem

Our Audio System is implemented using and supporting Wwise. To make It work, you have to import a an audio file in Wwise and vinculate an event to It. Once this is done, you can assign to any GameObject (except the camera, as this most of the times will be the listener) an Audio Source. In the inspector you can change the volume of the source and decide if you want that audio to be an spatial or non-spatial audio (depends if It's a song or sfx). If it is spatial, the volume will change depending on the distance of the listener from the specific audio source. That distance can be changed varying in inspector the radius of the spatial sphere inside the Audio Source. 

You can also apply any effect you want in a Game Paremeter. Inside Wwise you can create a Game Paremeter and assign It to an audio. Then, changing the RTPC value at your convinience, you can modify the instensity of the effect you chose. In our case, the value changes when the tunnel OBB detects that the fish OBB is inside, an there the audio distorts and creates the tunnel effect.

![](https://raw.githubusercontent.com/MarcArizaAlborni/VeryRealEngine/main/web%20source/1.gif)
![](https://raw.githubusercontent.com/MarcArizaAlborni/VeryRealEngine/main/web%20source/2.gif)
![](https://raw.githubusercontent.com/MarcArizaAlborni/VeryRealEngine/main/web%20source/3.gif)

# **_Engine Showcase_**

[![Engine Showcase](https://img.youtube.com/vi/sLM0ee8CiKk/0.jpg)](https://youtu.be/sLM0ee8CiKk)



# **_Libraries Used_**

- [Assimp](https://www.assimp.org/)
- [DevIl](http://openil.sourceforge.net/)
- [Glew](http://glew.sourceforge.net/)
- [ImGui](https://github.com/ocornut/imgui)
- [Json](https://www.json.org/json-es.html)
- [MathGeoLib](https://github.com/juj/MathGeoLib)
- [Parson](https://github.com/kgabis/parson)
- [PhysFS](https://icculus.org/physfs/docs/html/)
- [SDL](https://www.libsdl.org/)
- [Wwise](https://www.audiokinetic.com/products/wwise/)

# **_Installation Process_**

Download the last Release [HERE](https://github.com/MarcArizaAlborni/VeryRealEngine/releases) file and unzip it. Open the folder, execute the .exe and enjoy!*

_IMPORTANT: do not modify, change or add any folder or file as you might not be able to execute the game._

# **_License & Copyright_**

[MIT License](https://github.com/MarcArizaAlborni/VeryRealEngine/blob/main/LICENSE.md)

Copyright (c) <Gerard Romeu Vidal & Marc Ariza Alborni>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
