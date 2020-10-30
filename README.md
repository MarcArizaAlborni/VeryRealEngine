# VeryRealEngine




 ## Welcome to Very Real Engine!


 Very Real Engine (VRE) is an engine created using opengl as mainframe & other several external libraries for other functionalities.

This engine currently allows the user to import meshes and textures and visualize them inside the engine and several features like primitive model generation & mesh transformation.


Libraries used:

- Glew 

- SDL2.0

- ImGui

- DevIL

- Assimp

- Mathgeolib

- Json



 


 
Developed by : 

Marc Ariza Alborni: https://github.com/MarcArizaAlborni

Gerard Romeu Vidal: https://github.com/Gromeu2000

Camera Movement:

- W, A, S, D + left click to move the camera around, SHIFT to double movement speed.

- F when an object is selected to move next to it.

- Alt + left click to rotate around selected object

- Mouse wheel to zoom in/out


Information:

- Meshes should be .fbx to make sure they are loaded properly

- Textures should be .png to make sure they are loaded properly

- To see information about an object make sure the checkbox next to them in the inspector is selected

- No information will be displayed in the inspector if the selected item is an empty parent object, to see the information of its childs open child window (arrow) in the hierarchy for the parent object.

- Mesh transformation is available (position,rotation,scale) in the inspector and can be modified.






Innovation:

- In the hierarchy window, you can use the "eye" icon to enable/disable draw for a mesh to make it easier for the user.





Important: When importing a texture with drag & drop, make sure the Draw on Inspector checkbox is selected for the mesh you want the texture to be applied to, if there are multople meshes that you want to be textured with the 
same texture, sadly the only curent way to do it is one by one selecting each mesh. (a fix will come in the following updates)

Enjoy :)

