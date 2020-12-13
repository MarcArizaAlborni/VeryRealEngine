# VeryRealEngine




 ## Welcome to Very Real Engine!





## DELIVERY 2:

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

- ImGuizmo

- Physfs


### Controls:

Camera Movement:

- W, A, S, D + left click to move the camera around, SHIFT to double movement speed.

- F when an object is selected to move next to it.

- Alt + left click to rotate around selected object

- Mouse wheel to zoom in/out

- Theres a checkbox in the inspector of the camera object to reset the camera to 0,0.

- C to center camera at 0,0

- Supr to delete a selected mesh from the hierarchy



### General

- Meshes/Textures can be imported with drag/drop from an external folder or through the assets window. (To Apply Textures make sure there's a mesh selected).




### Street Environment:

- The street is automatically loaded at the start, it loads the meshes/texture/transforms correctly without any input from the user.



### Inspector/Hierarchy:

- The user can use the inspector to modify any of the components in a certain game object (mesh,texture,camera,transform)

- The user can create empty childrens, empty parents or delete game objects through the Hierarchy or through the "Insert" tab.

- Reparent is available through the Hierarchy with drag & drop.

- Transforms are available through the inspector.


### Camera:

- Camera is now a component, the user is able to modify its settings.

- Settings:

  - Camera: 

       - Camera Speed
       - Wheel Speed Value 
       - Zoom Value

  - Frustum:
         
       - FOV
       - Near Plane Size
       - Far Plane Size

- Theres an option inside the camera component to enable/disable frustum culling which culls the meshes so they aren't drawn.

  

### Bounding Boxes:

- Each Mesh component has an AABB and an OBB which can be enabled/disabled in the inspector.



### Custom File Format:

- We weren't able to load properly meshes with textures/transforms, so we decided to discard them.
- Metas are created but as we don't have custom file format working, META files are usseles.



### Serialization:

- With the o Key or pressing the play button the scene is saved using JSON, but as we don't have custom file format working scene files can't be used to load the scene. 
- Scenes are stored inside the Library/Scenes folder.




### Play/Stop:

- Using the Play/Pause buttons enables the game timer.

- The next frame button goes forward one frame in the engine/ play time.

- Game/Real timers are functional.




### Resource Management:

- We have an assets window which shows all user assets (Assets & Library files).

- The window updates every 120 seconds or using the update button in the window.

- If the user moves a new folder/mesh/texture inside a folder in the file explorer of the pc , the window will update and display them.

- The user can delete any file/folder from the window and they will be also removed in the folder itself ( folders must be empty to be removed).

- The user can rename any file/folder from the window and they will be also renamed in the folder itself.

- Through the Assets window, the user can select a mesh/texture (selecting the button with the name of the file) and drag it to the screen. This will load the file into the scene. 

- If the dragged item is a texture, if theres a mesh selected, the texture will be applied to the mesh. If there isn't a mesh selected, a Texture Visualizer will be opened.

- Reference Counting works for textures, textures are only loaded once and if they are used multiple times it is shown in the resources menu inside configuration.




### Import Settings:


- The user can modify the options of the import of meshes/ textures through the configuration window and will be applied to the following imports thats the user does.

- Available Options:


      - Textures: Wrapping styles, Flip Texture 
      - Meshes: Set Scales to each axis, axis to import, ignore cameras/lights when a mesh is loaded
      - Import settings are stored in the meta file but they are not loaded properly.
          	
           


### Innovation:

-  Texture Visualizer when a texture is dragged without a mesh being selected.

- Hide the entire UI with a simple checkbox


### Comments: 

- Our main trouble has been to load models properly from the custom file format using meta files, which has made it impossible to have serialization & library loading working properly.




------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


## DELIVERY 1:
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






Important: When importing a texture with drag & drop, make sure the Draw on Inspector checkbox is selected for the mesh you want the texture to be applied to, if there are multople meshes that you want to be textured with the 
same texture, sadly the only curent way to do it is one by one selecting each mesh. (a fix will come in the following updates)

Enjoy :)



